//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#pragma package(smart_init)

#include "MainThread.h"
#include "C_GetTime.h"
#include "PCIM114GL.h"
#include "IniFile.h"
#include "math.h"
#include "CEVision.h"
#include <algorithm>
#include "NHB300.h"
#include "EQPXML.h"

extern PCIM114GL g_MNet;
extern CIniFile g_IniFile;
extern CEVision theVision;
extern CNHB300 g_Scale;
extern CEQPXML g_eqpXML;

bool g_bStopMainThread = false;


CMainThread *g_pMainThread;
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall CMainThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

#pragma region ThreadCommonFunction
__fastcall CMainThread::CMainThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	m_bIsHomeDone = false;
	m_bNeedHome = false;
	m_bSoftStart = false;
	m_bSoftStop = false;
    m_bSoftReset = false;
    m_bSoftInit = false;
    m_bIsSprayerAlarm = false;
    m_bIsSprayerWeightAlarm = false;
    m_bIsStopLoader = false;
    m_bIsNeedPreMoveSprayer = false;
    m_bIsNeedAutoWeightScale = false;                    
    m_bIsFluxLifetimeTimeUp = false;

    m_bIsStartProcessbyDIO = false;
	m_bIsStartProcessbyCIM = false;
	m_bIsStopProcessbyCIM = false;

    m_bStartAgain = false;
    m_bStopAgain = false;
    m_bResetAgain = false;
    m_bInitalAgain = true;

    m_nStripCount = 0;
    m_bIsStripCountNeedCopy = false;
	m_nStripCountForAutoFillFlux = 0;
	m_bIsStripCountNeedAutoFillFlux = false;
    //ShowNow
    for (int nX=0;nX<25;nX++)
    {
        m_arraybShape[nX] = false;
    }

    tm1MSFluxLifeTime.timeDevStart();
}
//---------------------------------------------------------------------------
void __fastcall CMainThread::Execute()
{
	//---- Place thread code here ----
	C_GetTime tmReset, tmAlarm, tmResetLamp, tmResetInitial, tmAgain;
    tmAgain.timeStart(800);
	g_bStopMainThread = false;

	bool bHomeDone = false;
	bool bAutoMode = false;
	bool bPreAuto = false;

	bool bLastStart = false;
	bool bLastReset = false;
    bool bLastResetInitial = false;
    bool bLastAgain = false;

	bool bAlarmLamp = false;
	bool bResetLamp = false;

	bool bStartMachineInit = false;

	while (1)
	{
		if (g_bStopMainThread) break;

		//Status
		m_bIsHomeDone = bHomeDone;
		m_bIsAutoMode = bAutoMode;
		//

		if (m_bNeedHome)
		{
			m_bNeedHome = false;
			bHomeDone = false;
		}

		g_Motion.m_bAutoMode = m_bIsAutoMode;

        //---Start Again
        if (tmAgain.timeUp())
        {
            m_bStartAgain = true;
            m_bStopAgain = true;
            m_bResetAgain = true;
            tmAgain.timeStart(800);
        }

		//---Start Homing
		if (g_DIO.ReadDIBit(DI::ResetBtn) && !bLastReset) tmReset.timeStart(3000);
		if (bLastReset && tmReset.timeUp() || m_bSoftInit)
		{
            m_bSoftInit = false;
			bStartMachineInit = true;
			nThreadIndex[0] = 0;
			bHomeDone = false;
		}
		bLastReset = g_DIO.ReadDIBit(DI::ResetBtn);

		//CheckAlarm();
		if (g_MNet.IsCommError(0)) g_IniFile.m_nErrorCode = 50;

		//----Alarm Occured
		//--Stop Auto
        if ((g_DIO.ReadDIBit(DI::StopBtn) && m_bStopAgain)
            || m_bIsStopProcessbyCIM
            || m_bSoftStop
            || (g_IniFile.m_nErrorCode>0 && g_IniFile.m_nErrorCode<1000))
		{
			m_bSoftStop = false;
            m_bIsStopProcessbyCIM = false;
            m_bStopAgain = false;
			bStartMachineInit = false;
			bAutoMode = false;
			bPreAuto = false;
			SetManualSpeed();

			//Stop motor or Output
			for (int nIndex = 0; nIndex<AXIS_SIZE; nIndex++)
			{
				if (nIndex != Axis_Const::SPX && nIndex != Axis_Const::SPY && nIndex != Axis_Const::SPZ) g_Motion.StopMove(nIndex);
			}

			//Stop AC Motor
			g_Motion.SetDO(DO::LoaderConveyerUp, false);
			g_Motion.SetDO(DO::LoaderConveyerDown, false);
			g_Motion.SetDO(DO::LeftLaneChangerMotor, false);
			g_Motion.SetDO(DO::RightLaneChangerMotor, false);
			g_Motion.SetDO(DO::FrontLaneSprayMotor, false);
			g_Motion.SetDO(DO::RearLaneSprayMotor, false);
			//g_Motion.SetDO(DO::OutConveyerMotor,false);

			//Stop Pusher
			g_Motion.SetDO(DO::LoaderPusher, false);
			g_Motion.SetDO(DO::RightLaneChangerPusher, false);
            g_Motion.SetDO(DO::LeftLaneChangerPress, false);

            //Clean Alarm
            m_bIsSprayerAlarm = false;
            m_bIsSprayerWeightAlarm = false;

            //Release Lock
            //m_bIsSprayerLock = false;

            //PreMove
            m_bIsNeedPreMoveSprayer = false;
		}
        
        //---Reset Alarm
		if ((g_DIO.ReadDIBit(DI::ResetBtn) && m_bResetAgain)|| m_bSoftReset)
		{
			g_IniFile.m_nErrorCode = 0;
            m_bSoftReset = false;
			g_DIO.SetDO(DO::RedLamp, false);
			g_DIO.SetDO(DO::Buzzer, false);
		}

        //---Reset Initmachine
        if (g_IniFile.m_nErrorCode == 1001 && !bLastResetInitial) tmResetInitial.timeStart(2000);
        if (tmResetInitial.timeUp() && bLastResetInitial)
        {
            g_IniFile.m_nErrorCode = 0;
            bLastResetInitial = false;
			g_DIO.SetDO(DO::RedLamp, false);
			g_DIO.SetDO(DO::Buzzer, false);
        }
        if (g_IniFile.m_nErrorCode == 1001) bLastResetInitial = true;
        else bLastResetInitial = false;

		//---Buzzer
		if (tmAlarm.timeUp() && g_IniFile.m_nErrorCode>0)
		{
			g_DIO.SetDO(DO::RedLamp, bAlarmLamp);
			g_DIO.SetDO(DO::Buzzer, bAlarmLamp);
			bAlarmLamp = !bAlarmLamp;
			tmAlarm.timeStart(500);
		}

		//---Homing Announce
		else if (tmAlarm.timeUp() && !bHomeDone)
		{
			g_DIO.SetDO(DO::StopBtnLamp, bAlarmLamp);
			g_DIO.SetDO(DO::StartBtnLamp, bAlarmLamp);
			g_DIO.SetDO(DO::ResetBtnLamp, bAlarmLamp);

			bAlarmLamp = !bAlarmLamp;
			tmAlarm.timeStart(500);
		}

		//---Homing Process
		if (!bHomeDone && !bAutoMode  && bStartMachineInit)
		{
			bHomeDone = InitialMachine(nThreadIndex[0]);
			if (bHomeDone)
			{

				for (int nIndex = 0; nIndex<MAX_PROCESS; nIndex++)
					nThreadIndex[nIndex] = 0;

				bStartMachineInit = false;
			}
			CheckAlarm();
		}
		else if (bAutoMode && bHomeDone)	                //AutoMode
		{
			g_DIO.SetDO(DO::StopBtnLamp, false);
			g_DIO.SetDO(DO::StartBtnLamp, true);
			g_DIO.SetDO(DO::GreenLamp, true);
			g_DIO.SetDO(DO::YellowLamp, false);
			g_DIO.SetDO(DO::RedLamp, false);

			CheckAlarm();
			SetWorkSpeed();

			//do Auto process
			//doBoatRail(nThreadIndex[11]);
			doLoadConveyerUp(nThreadIndex[1]);
			doLoadConveyerDown(nThreadIndex[2]);
            doLoadClamper(nThreadIndex[3]);
            doLeftLaneChanger(nThreadIndex[4]);
            doSprayerLane(nThreadIndex[5], true);
            doSprayerLane(nThreadIndex[6], false);
			doCCDBufferLane(nThreadIndex[7]);
		}
		else if (bHomeDone)			        //Manual Mode
		{
			g_DIO.SetDO(DO::StopBtnLamp, true);
			g_DIO.SetDO(DO::StartBtnLamp, false);
			g_DIO.SetDO(DO::ResetBtnLamp, false);

            //InitLoader need slow move not ManualSpeed
			if (!m_bStartInitLoader) SetManualSpeed();

			g_DIO.SetDO(DO::GreenLamp, false);
			g_DIO.SetDO(DO::YellowLamp, true);
			//g_DIO.SetDO(DO::RedLamp,false);

            //當start綠燈被壓下時，或者CIM觸發StartProcess function
			switch (g_eqpXML.m_CIMStatus.ToInt())
			{
			case 0:                                                                              //Offline
				if ((g_DIO.ReadDIBit(DI::StartBtn) && m_bStartAgain) || m_bSoftStart)
				{
					m_bIsStartProcessbyDIO = true;
                    m_listLog.push_back("機台啟動");
					m_bStartAgain = false;
                    m_bSoftStart = false;
				}
				break;
			case 1:                                                                              //online/local
				if ((g_DIO.ReadDIBit(DI::StartBtn) && m_bStartAgain) || m_bSoftStart)
                {
                    m_bIsStartProcessbyDIO = true;
					m_listLog.push_back("機台啟動");
					m_bStartAgain = false;
                    m_bSoftStart = false;
                }
				break;
			case 2:                                                                             //online/remote
				if ((g_DIO.ReadDIBit(DI::StartBtn) && m_bStartAgain) || m_bSoftStart)
                {
                    m_bIsStartProcessbyDIO = true;
					m_listLog.push_back("機台啟動");
					m_bStartAgain = false;
                    m_bSoftStart = false;
                }
				break;
			default:
				break;
            }
			if (m_bIsStartProcessbyDIO || m_bIsStartProcessbyCIM)
			{
                if (m_bIsStartProcessbyDIO == true) m_listLog.push_back("[Execute]由DIO啟動");
                else if (m_bIsStartProcessbyCIM == true) m_listLog.push_back("[Execute]由CIM啟動");

				bPreAuto = true;
				nThreadIndex[19] = 0;
				SetWorkSpeed();

                m_bIsStartProcessbyCIM = false;
				m_bIsStartProcessbyDIO = false;
            }
			if (bPreAuto)
			{
				g_DIO.SetDO(DO::StopBtnLamp, true);
				g_DIO.SetDO(DO::StartBtnLamp, true);
				g_DIO.SetDO(DO::GreenLamp, true);
				g_DIO.SetDO(DO::YellowLamp, false);
				g_DIO.SetDO(DO::RedLamp, false);

				bAutoMode = doPreAuto(nThreadIndex[19]);
				bPreAuto = !bAutoMode;
			}

			//Manual
			if (m_bStartReLoadClamper && bHomeDone) doReLoadClamper(nThreadIndex[8]);
			else if (m_bStartUnLoadClamper && bHomeDone) doUnLoadClamper(nThreadIndex[9]);
			else if (m_bStartInitLoader && bHomeDone) InitialLoader(nThreadIndex[10]);
		}
		else
		{
			if (!bHomeDone && g_DIO.ReadDIBit(DI::StartBtn)) g_IniFile.m_nErrorCode = 999;
			//Announce to Homing 
			if (tmResetLamp.timeUp())
			{
				g_DIO.SetDO(DO::ResetBtnLamp, bResetLamp);
				g_DIO.SetDO(DO::YellowLamp, bResetLamp);
				bResetLamp = !bResetLamp;
				tmResetLamp.timeStart(500);
			}
		}

		//Either Auto or Manual
		if (m_bStartFillFlux && bHomeDone) doFillFlux(nThreadIndex[18]);
		if (m_bStartSBTSprayF && bHomeDone) doSBTSpray(nThreadIndex[17], true);
		if (m_bStartSBTSprayR && bHomeDone) doSBTSpray(nThreadIndex[12], false);
		if (m_bStartCleanSpray && bHomeDone) doCleanSpray(nThreadIndex[16], true);
        if (m_bStartCleanSprayAir && bHomeDone) doCleanSpray(nThreadIndex[15], false);
		if (m_bStartDredgeScaleSpray && bHomeDone) doScaleSpray(nThreadIndex[14], true);
		if (m_bStartFluxScaleSpray && bHomeDone) doScaleSpray(nThreadIndex[13], false);

		::Sleep(10);
	}
}
//---------------------------------------------------------------------------
bool __fastcall CMainThread::InitialMachine(int &nThreadIndex)
{
	static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);


	switch (nThreadIndex)
	{
	case 0:
		if (!g_DIO.ReadDIBit(DI::MainAir)) g_IniFile.m_nErrorCode = 6;     //debug
		else if (!g_DIO.ReadDIBit(DI::LoaderPusherBwd)) g_IniFile.m_nErrorCode = 300;
		else if (g_DIO.ReadDIBit(DI::LoaderClamperMgzExist)) g_IniFile.m_nErrorCode = 301;
		else if (g_DIO.ReadDIBit(DI::LeftLaneChangerIn)) g_IniFile.m_nErrorCode = 302;
		else if (g_DIO.ReadDIBit(DI::LeftLaneChangerInp)) g_IniFile.m_nErrorCode = 303;
		else if (g_DIO.ReadDIBit(DI::LeftLaneChangerOut)) g_IniFile.m_nErrorCode = 304;
		else if (g_DIO.ReadDIBit(DI::RightLaneChangerIn)) g_IniFile.m_nErrorCode = 305;
		else if (g_DIO.ReadDIBit(DI::RightLaneChangerInp)) g_IniFile.m_nErrorCode = 306;
		else if (g_DIO.ReadDIBit(DI::RightLaneChangerOut)) g_IniFile.m_nErrorCode = 307;
		else if (!g_DIO.ReadDIBit(DI::RightPusherBwd)) g_IniFile.m_nErrorCode = 308;
		else if (g_DIO.ReadDIBit(DI::FrontLaneSprayIn)) g_IniFile.m_nErrorCode = 309;
		else if (g_DIO.ReadDIBit(DI::FrontLaneSprayInp)) g_IniFile.m_nErrorCode = 310;
		else if (g_DIO.ReadDIBit(DI::FrontLaneSprayOut)) g_IniFile.m_nErrorCode = 311;
		else if (g_DIO.ReadDIBit(DI::RearLaneSprayIn)) g_IniFile.m_nErrorCode = 312;
		else if (g_DIO.ReadDIBit(DI::RearLaneSprayInp)) g_IniFile.m_nErrorCode = 313;
		else if (g_DIO.ReadDIBit(DI::RearLaneSprayOut)) g_IniFile.m_nErrorCode = 314;
		else if (g_DIO.ReadDIBit(DI::UnLoaderMgzExist)) g_IniFile.m_nErrorCode = 315;
		//else if(!g_DIO.ReadDIBit()) g_IniFile.m_nErrorCode=;
		//else if(!g_DIO.ReadDIBit()) g_IniFile.m_nErrorCode=;
		else
		{
			for (int nIndex = 0; nIndex<DIO_SIZE; nIndex++) g_DIO.SetDO(nIndex, false);

			for (int nIndex = 0; nIndex<AXIS_SIZE; nIndex++) g_Motion.ServoOn(nIndex, true);

			nThreadIndex++;
		}
		break;
	case 1:

		//g_IniFile.m_nErrorCode=1000;    //Start Homing
		m_listLog.push_back("機台初始中,請稍后");
		//LDY=0,LDZ,SPZ,MGZ,LLC,SPX,SPY,CDX,RLC

		g_Motion.SetMoveSpeed(Axis_Const::LDY, 20, 0.01, 0.01);
		g_Motion.SetMoveSpeed(Axis_Const::LDZ, 10, 0.01, 0.01);
		g_Motion.SetMoveSpeed(Axis_Const::SPZ, 10, 0.01, 0.01);
		g_Motion.SetMoveSpeed(Axis_Const::MGZ, 10, 0.01, 0.01);
		g_Motion.SetMoveSpeed(Axis_Const::LLC, 20, 0.01, 0.01);
		g_Motion.SetMoveSpeed(Axis_Const::SPX, 20, 0.01, 0.01);
		g_Motion.SetMoveSpeed(Axis_Const::SPY, 20, 0.01, 0.01);
		g_Motion.SetMoveSpeed(Axis_Const::CDX, 20, 0.01, 0.01);
		g_Motion.SetMoveSpeed(Axis_Const::RLC, 20, 0.01, 0.01);

		for (int nAxis = 0; nAxis<AXIS_SIZE; nAxis++)
		{
			if (g_Motion.GetAxisStatus(nAxis, Axis_Const::MEL) ||
				g_Motion.GetAxisStatus(nAxis, Axis_Const::ORG))
				g_Motion.RelMove(nAxis, 10.0);
		}

		tm1MS.timeStart(500);

		nThreadIndex++;
	case 2:
		if (tm1MS.timeUp() && 
			g_Motion.IsMotionDone(0) &&
			g_Motion.IsMotionDone(1) &&
			g_Motion.IsMotionDone(2) &&
			g_Motion.IsMotionDone(3) &&
			g_Motion.IsMotionDone(4) &&
			g_Motion.IsMotionDone(5) &&
			g_Motion.IsMotionDone(6) &&
			g_Motion.IsMotionDone(7) &&
			g_Motion.IsMotionDone(8))
		{
			tm1MS.timeStart(500);
			nThreadIndex++;
		}
		break;
	case 3:
		if (tm1MS.timeUp())
		{
			g_Motion.AxisHome(Axis_Const::SPZ, false);
			g_Motion.AxisHome(Axis_Const::LDY, false);
			tm1MS.timeStart(500);
			nThreadIndex++;
		}
		break;
	case 4:
		if (tm1MS.timeUp() && g_Motion.IsMotionDone(Axis_Const::SPZ) &&
			g_Motion.IsMotionDone(Axis_Const::LDY))
		{
			g_Motion.AxisHome(Axis_Const::LDZ, false);
			g_Motion.AxisHome(Axis_Const::LLC, false);
			g_Motion.AxisHome(Axis_Const::SPX, false);
			g_Motion.AxisHome(Axis_Const::SPY, false);
			g_Motion.AxisHome(Axis_Const::RLC, false);
			g_Motion.AxisHome(Axis_Const::CDX, false);
			g_Motion.AxisHome(Axis_Const::MGZ, false);
			tm1MS.timeStart(500);
			nThreadIndex++;
		}
		break;
	case 5:
		if (tm1MS.timeUp() && g_Motion.IsMotionDone(Axis_Const::LDZ) &&
			g_Motion.IsMotionDone(Axis_Const::LLC) &&
			g_Motion.IsMotionDone(Axis_Const::SPX) &&
			g_Motion.IsMotionDone(Axis_Const::SPY) &&
			g_Motion.IsMotionDone(Axis_Const::RLC) &&
			g_Motion.IsMotionDone(Axis_Const::CDX) &&
			g_Motion.IsMotionDone(Axis_Const::MGZ))
		{
			tm1MS.timeStart(1000);
			nThreadIndex++;
		}
		break;
	case 6:
		if (tm1MS.timeUp())
		{
			for (int nAxis = 0; nAxis<AXIS_SIZE; nAxis++)
			{
				g_Motion.SetCommandPos(nAxis, 0.0);
				g_Motion.SetFeedbackPos(nAxis, 0.0);
				g_Motion.m_dLastTargetPos[nAxis] = 0.0;
			}

			nThreadIndex++;
		}
		break;
	case 7:
		g_Motion.SetDO(DO::LoaderClamper, true);            //un-Clamp
		g_Motion.SetDO(DO::LeftLaneChangerStopper, true);          //true: up  false: down
		g_Motion.SetDO(DO::RightLaneChangerStopper, true);          //true: up  false: down
		g_Motion.SetDO(DO::FrontLaneSprayStopper, true);          //true: up  false: down
		g_Motion.SetDO(DO::RearLaneSprayStopper, true);          //true: up  false: down
		//g_Motion.SetDO(DO::SprayerVacIn, false);          //true: Vac  false: Air
        g_Motion.SetDO(DO::SprayerPistonOn, false);         //true: Piston Layin false: LayOut
		g_Motion.SetDO(DO::CleanerWaterAirSwitch, false);          //true: Water  false: Air

		g_Motion.SetAO(0, g_IniFile.m_dFluxTankAirPressure);
		g_Motion.SetAO(1, g_IniFile.m_dSprayerAirPressure);

		m_listPickLane.clear();
		m_listUPUTime.clear();

		m_bConveyerMagazineReady = false;
		m_bConveyerMagazineOutReady = false;
		m_bLoaderClamperReady = false;
		m_bLoaderClamperChangeMgz = false;

		m_bLeftLaneChangerReady = false;
		n_bLaneSprayReady[0] = false;
		n_bLaneSprayReady[1] = false;

		m_bStartSBTSprayF = false;
		m_bStartSBTSprayR = false;
		m_bSBTSprayDoneF = false;
		m_bSBTSprayDoneR = false;
		m_bStartCleanSpray = false;
        m_bStartCleanSprayAir = false;
		m_bCleanSprayDone = false;
		m_bStartFluxScaleSpray = false;
		m_bStartDredgeScaleSpray = false;
		m_bScaleSprayDone = false;
        m_bIsSprayerLock = false;

		m_bStartReLoadClamper = false;
		m_bStartUnLoadClamper = false;

		m_nStripCountForAutoFillFlux = 0;

		m_listReaderTX.push_back("SHUTDOWN_1D_CODE");
        //ShowNow
        for (int nX = 0; nX<4; nX++)
		{
			m_arraybShape[nX] = false;
		}

		g_IniFile.m_nErrorCode = 1001;
		nThreadIndex++;
		break;
	default:
		nThreadIndex = 0;
		return true;
	}

	if (g_IniFile.m_nErrorCode>0 && g_IniFile.m_nErrorCode<1000)  nThreadIndex = 0;

	return false;
}
//---------------------------------------------------------------------------
bool __fastcall CMainThread::InitialLoader(int &nThreadIndex)
{
	static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

	switch (nThreadIndex)
	{
	case 0:
		if (!g_DIO.ReadDIBit(DI::LoaderPusherBwd)) g_IniFile.m_nErrorCode = 300;
		else if (g_DIO.ReadDIBit(DI::LoaderClamperMgzExist)) g_IniFile.m_nErrorCode = 301;
		else if (m_bStartInitLoader == true)
		{	
			nThreadIndex++;
		}
		break;
	case 1:
		m_listLog.push_back("Loader初始中,請稍后");
		//LDY=0,LDZ,SPZ,MGZ,LLC,SPX,SPY,CDX,RLC

		g_Motion.SetMoveSpeed(Axis_Const::LDY, 20, 0.01, 0.01);
		g_Motion.SetMoveSpeed(Axis_Const::LDZ, 10, 0.01, 0.01);

		if (g_Motion.GetAxisStatus(Axis_Const::LDY, Axis_Const::MEL) || g_Motion.GetAxisStatus(Axis_Const::LDY, Axis_Const::ORG))
			g_Motion.RelMove(Axis_Const::LDY, 10.0);
		if (g_Motion.GetAxisStatus(Axis_Const::LDZ, Axis_Const::MEL) || g_Motion.GetAxisStatus(Axis_Const::LDZ, Axis_Const::ORG))
			g_Motion.RelMove(Axis_Const::LDZ, 10.0);

		tm1MS.timeStart(500);

		nThreadIndex++;
	case 2:
		if (tm1MS.timeUp() && g_Motion.IsMotionDone(4) && g_Motion.IsMotionDone(5))
		{
			tm1MS.timeStart(500);
			nThreadIndex++;
		}
		break;
	case 3:
		if (tm1MS.timeUp())
		{
			g_Motion.AxisHome(Axis_Const::LDY, false);
			tm1MS.timeStart(500);
			nThreadIndex++;
		}
		break;
	case 4:
		if (tm1MS.timeUp() && g_Motion.IsMotionDone(Axis_Const::LDY))
		{
			g_Motion.AxisHome(Axis_Const::LDZ, false);
			tm1MS.timeStart(500);
			nThreadIndex++;
		}
		break;
	case 5:
		if (tm1MS.timeUp() && g_Motion.IsMotionDone(Axis_Const::LDZ))
		{
			tm1MS.timeStart(1000);
			nThreadIndex++;
		}
		break;
	case 6:
		if (tm1MS.timeUp())
		{
			g_Motion.SetCommandPos(Axis_Const::LDY, 0.0);
			g_Motion.SetFeedbackPos(Axis_Const::LDY, 0.0);
			g_Motion.m_dLastTargetPos[Axis_Const::LDY] = 0.0;
			g_Motion.SetCommandPos(Axis_Const::LDZ, 0.0);
			g_Motion.SetFeedbackPos(Axis_Const::LDZ, 0.0);
			g_Motion.m_dLastTargetPos[Axis_Const::LDZ] = 0.0;

			nThreadIndex++;
		}
		break;
	case 7:
		g_Motion.SetDO(DO::LoaderClamper, true);                //un-Clamp

		m_bConveyerMagazineReady = false;
		m_bConveyerMagazineOutReady = false;
		m_bLoaderClamperReady = false;
		m_bLoaderClamperChangeMgz = false;

		m_listReaderTX.push_back("SHUTDOWN_1D_CODE");
		m_listLog.push_back("Loader復歸完成.");
		nThreadIndex++;
		break;
	default:
		m_bStartInitLoader = false;
		nThreadIndex = 0;
        m_bLoaderClamperReady = false;
		return true;
	}

	if (g_IniFile.m_nErrorCode>0 && g_IniFile.m_nErrorCode<1000)  nThreadIndex = 0;

	return false;
}
//---------------------------------------------------------------------------
void __fastcall CMainThread::CheckAlarm()
{
	if (g_Motion.GetAxisStatus(Axis_Const::LDY, Axis_Const::ALM)) g_IniFile.m_nErrorCode = 201;
	else if (g_Motion.GetAxisStatus(Axis_Const::LDZ, Axis_Const::ALM)) g_IniFile.m_nErrorCode = 202;
	else if (g_Motion.GetAxisStatus(Axis_Const::SPZ, Axis_Const::ALM)) g_IniFile.m_nErrorCode = 203;
	else if (g_Motion.GetAxisStatus(Axis_Const::MGZ, Axis_Const::ALM)) g_IniFile.m_nErrorCode = 204;
	else if (g_Motion.GetAxisStatus(Axis_Const::LLC, Axis_Const::ALM)) g_IniFile.m_nErrorCode = 205;
	else if (g_Motion.GetAxisStatus(Axis_Const::SPX, Axis_Const::ALM)) g_IniFile.m_nErrorCode = 206;
	else if (g_Motion.GetAxisStatus(Axis_Const::SPY, Axis_Const::ALM)) g_IniFile.m_nErrorCode = 207;
	else if (g_Motion.GetAxisStatus(Axis_Const::CDX, Axis_Const::ALM)) g_IniFile.m_nErrorCode = 208;
	else if (g_Motion.GetAxisStatus(Axis_Const::RLC, Axis_Const::ALM)) g_IniFile.m_nErrorCode = 209;

    if (m_bIsFluxLifetimeTimeUp) g_IniFile.m_nErrorCode = 8;
	if (!g_DIO.ReadDIBit(DI::MainAir)) g_IniFile.m_nErrorCode = 6;
	if (!g_DIO.ReadDIBit(DI::SafetyDoor)) g_IniFile.m_nErrorCode = 7;
}
//---------------------------------------------------------------------------
bool __fastcall CMainThread::CheckRelMoveAlarm(unsigned short nAxis, bool bIsForward, double dMoveDistance)
{
	bool bIsPass = false;
	double dAxisNowPos = g_Motion.GetFeedbackPos(nAxis);

	if (nAxis == Axis_Const::SPX)
	{
		if (bIsForward && ((dAxisNowPos + dMoveDistance) <= g_IniFile.m_dSprayLaneAlarmX[1])) bIsPass = true;
		if (!bIsForward && ((dAxisNowPos - dMoveDistance) >= g_IniFile.m_dSprayLaneAlarmX[0])) bIsPass = true;
	}
	if (nAxis == Axis_Const::SPY)
	{
		if (bIsForward && ((dAxisNowPos + dMoveDistance) <= g_IniFile.m_dSprayLaneAlarmY[1])) bIsPass = true;
		if (!bIsForward && ((dAxisNowPos - dMoveDistance) >= g_IniFile.m_dSprayLaneAlarmY[0])) bIsPass = true;
	}
	return bIsPass;
}
//---------------------------------------------------------------------------
bool __fastcall CMainThread::CheckXYInSprayRange()
{
	bool bIsPass = false;
	double dXPos = g_Motion.GetFeedbackPos(Axis_Const::SPX);
	double dYPos = g_Motion.GetFeedbackPos(Axis_Const::SPY);
	if ((dXPos > g_IniFile.m_dSprayLaneAlarmX[0] && dXPos < g_IniFile.m_dSprayLaneAlarmX[1])
		&& (dYPos > g_IniFile.m_dSprayLaneAlarmY[0] && dYPos < g_IniFile.m_dSprayLaneAlarmY[1])) bIsPass = true;
	return bIsPass;
}
//---------------------------------------------------------------------------
bool __fastcall CMainThread::CheckXYZAtSprayReadyPos(bool bFront)
{
	bool bIsPass = false;
	double dXPos = g_Motion.GetFeedbackPos(Axis_Const::SPX);
	double dYPos = g_Motion.GetFeedbackPos(Axis_Const::SPY);
    double dZPos = g_Motion.GetFeedbackPos(Axis_Const::SPZ);
    if (bFront)
    {
        if (dXPos == g_IniFile.m_dStartSprayPosX[1] && dYPos == g_IniFile.m_dStartSprayPosY[1] && dZPos == g_IniFile.m_dSprayReadyPos) bIsPass = true;
    }
    else
    {
        if (dXPos == g_IniFile.m_dStartSprayPosX[0] && dYPos == g_IniFile.m_dStartSprayPosY[0] && dZPos == g_IniFile.m_dSprayReadyPos) bIsPass = true;
    }
	return bIsPass;
}
//---------------------------------------------------------------------------
void __fastcall CMainThread::SetWorkSpeed()
{
	for (int nIndex = 0; nIndex<AXIS_SIZE; nIndex++)
		g_Motion.SetMoveSpeed(nIndex, g_IniFile.m_dWorkSpeed[nIndex], g_IniFile.m_dACCSpeed[nIndex], g_IniFile.m_dDECSpeed[nIndex]);
}
//---------------------------------------------------------------------------
void __fastcall CMainThread::SetManualSpeed()
{
	for (int nIndex = 0; nIndex<AXIS_SIZE; nIndex++)
		g_Motion.SetMoveSpeed(nIndex, g_IniFile.m_dJogSpeed[nIndex], g_IniFile.m_dACCSpeed[nIndex], g_IniFile.m_dDECSpeed[nIndex]);
}
//---------------------------------------------------------------------------
bool __fastcall CMainThread::doPreAuto(int &nThreadIndex)
{
	static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

    const int nTagFinished = 1000;

	switch (nThreadIndex)
	{
	case 0:
        if (g_IniFile.m_bUsePreAutoWeightScale) nThreadIndex++;
        else nThreadIndex = nTagFinished;
        break;
    case 1:
        if (!m_bIsSprayerLock)
        {
            m_bIsSprayerLock = true;
            m_bStartFluxScaleSpray = true;
            CMainThread::nThreadIndex[13] = 0;
		    nThreadIndex++;
        }
        else g_IniFile.m_nErrorCode = 715;
		break;
    case 2:
        if (!m_bStartFluxScaleSpray)
        {
            m_bIsSprayerLock = false;
            g_IniFile.m_bUsePreAutoWeightScale = false;
            g_Motion.AbsMove(Axis_Const::SPZ, 0.0);
            nThreadIndex++;
        }
        break;
    case 3:
        if (g_Motion.IsPosDone(Axis_Const::SPZ, 0.0))
		{
            g_Motion.AbsMove(Axis_Const::SPX, g_IniFile.m_dStartSprayPosX[1]);
			g_Motion.AbsMove(Axis_Const::SPY, g_IniFile.m_dStartSprayPosY[1]);
			nThreadIndex++;
		}
		break;
	case 4:
		if (g_Motion.IsPosDone(Axis_Const::SPX, g_IniFile.m_dStartSprayPosX[1])
            && g_Motion.IsPosDone(Axis_Const::SPY, g_IniFile.m_dStartSprayPosY[1]))
		{
			nThreadIndex++;
		}
		break;
    case 5:
    case nTagFinished:nThreadIndex = 5;
        if (g_Motion.GetFeedbackPos(Axis_Const::SPZ) != g_IniFile.m_dSprayReadyPos) g_Motion.AbsMove(Axis_Const::SPZ, 0.0);
        nThreadIndex++;
        break;
	default:
        m_bIsNeedPreMoveSprayer = true;
		nThreadIndex = 0;
		return true;
		break;
	}
	return false;
}
//---------------------------------------------------------------------------
#pragma endregion

#pragma region ThreadAction
void __fastcall CMainThread::doLoadConveyerUp(int &nThreadIndex)
{
	static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

	switch (nThreadIndex)
	{
	case 0:
		if (!g_Motion.GetDI(DI::LoaderInMgzExist))
		{
			tm1MS.timeStart(30000);
			g_Motion.SetDO(DO::LoaderConveyerUp, true);
			nThreadIndex++;
		}
		else nThreadIndex++;
		break;
	case 1:
		if (g_Motion.GetDI(DI::LoaderInMgzExist))
		{
			tm1MS.timeStart(1000);
			nThreadIndex++;
		}
		else if (!g_Motion.GetDO(DO::LoaderConveyerUp))
		{
			tm1MS.timeStart(30000);
			g_Motion.SetDO(DO::LoaderConveyerUp, true);
		}
		else if (tm1MS.timeUp())
		{
			nThreadIndex = 0;
			//Warning
			m_listLog.push_back("料盒時間內沒有達定位");
			//g_IniFile.m_nErrorCode=401;
		}
		break;
	case 2:
		if (tm1MS.timeUp())
		{
			g_Motion.SetDO(DO::LoaderConveyerUp, false);

			//if(!g_Motion.GetDI(DI::LoaderInMgzDir))  //false: Direction OK
			if (g_Motion.GetDI(DI::LoaderInMgzDir))  //true: Direction OK
			{
				m_bConveyerMagazineReady = true;
				nThreadIndex++;
			}
			else
			{
				nThreadIndex = 0;
				g_IniFile.m_nErrorCode = 400;
			}
		}
		break;
	case 3:
		if (!m_bConveyerMagazineReady)
		{
			nThreadIndex++;
		}
		break;
	default:
		nThreadIndex = 0;
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall CMainThread::doLoadConveyerDown(int &nThreadIndex)
{
	static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

	switch (nThreadIndex)
	{
	case 0:
		if (!g_Motion.GetDI(DI::LoaderOutMgzFull))
		{
			m_bConveyerMagazineOutReady = true;
			nThreadIndex++;
		}
		else g_IniFile.m_nErrorCode = 402;
		break;
	case 1:
		if (!m_bConveyerMagazineOutReady)
		{
			g_Motion.SetDO(DO::LoaderConveyerDown, true);
			tm1MS.timeStart(10000);
			nThreadIndex++;
		}
		break;
	case 2:
		if (g_Motion.GetDI(DI::LoaderOutMgzStop))  nThreadIndex++;
        else if (!g_Motion.GetDI(DI::LoaderOutMgzStop) && !g_Motion.GetDI(DI::LoaderOutMgzIn)) nThreadIndex=0;
		else if (!g_Motion.GetDO(DO::LoaderConveyerDown))
		{
			g_Motion.SetDO(DO::LoaderConveyerDown, true);
			tm1MS.timeStart(10000);
		}
		else if (g_Motion.GetDI(DI::LoaderOutMgzFull)) g_IniFile.m_nErrorCode = 402;
		else if (tm1MS.timeUp()) g_IniFile.m_nErrorCode = 403;
		break;
	case 3:
		if (!g_Motion.GetDI(DI::LoaderOutMgzStop))
		{
			g_Motion.SetDO(DO::LoaderConveyerDown, false);
			nThreadIndex++;
		}
		else if (!g_Motion.GetDO(DO::LoaderConveyerDown))
		{
			g_Motion.SetDO(DO::LoaderConveyerDown, true);
			tm1MS.timeStart(10000);
		}
        else if (!g_Motion.GetDI(DI::LoaderOutMgzStop) && !g_Motion.GetDI(DI::LoaderOutMgzIn)) nThreadIndex=0;
		else if (g_Motion.GetDI(DI::LoaderOutMgzFull)) g_IniFile.m_nErrorCode = 402;
		else if (tm1MS.timeUp()) g_IniFile.m_nErrorCode = 404;
		break;
	default:
		nThreadIndex = 0;
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall CMainThread::doLoadClamper(int &nThreadIndex)
{
	const int nTagReRead1D = 1000;
    const int nTagClampMag = 2000;
	const int nTagPush = 3000;
	const int nTagUnClampMgz = 4000;

	
	static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);
	static int nMgzIndex = 0;

	switch (nThreadIndex)
	{
	case 0:
		if (!g_Motion.GetDI(DI::LoaderClamperUp)) g_IniFile.m_nErrorCode = 405;
		else if (g_Motion.IsMotionDone(Axis_Const::LDZ))
		{
			g_Motion.AbsMove(Axis_Const::LDY, 0.0);
			nThreadIndex++;
		}
		break;
	case 1:
		if (g_Motion.IsMotionDone(Axis_Const::LDY))
		{
			g_Motion.AbsMove(Axis_Const::LDZ, g_IniFile.m_dLoaderClampMgzPos[0]);
			nThreadIndex++;
		}
		break;
	case 2:
	case nTagReRead1D: nThreadIndex = 2;
		if (m_bConveyerMagazineReady && !g_Motion.GetDI(DI::LoaderInMgzExist))
		{
            g_Motion.AbsMove(Axis_Const::LDZ, 0.0);
			m_bConveyerMagazineReady = false;
			nThreadIndex = 0;
		}
		if (m_bConveyerMagazineReady && g_Motion.IsMotionDone(Axis_Const::LDZ))
		{
            if (!g_IniFile.m_bIsUse1DReader)
            {
                nThreadIndex = nTagClampMag;
            }
            else if (g_IniFile.m_bIsUse1DReader && g_eqpXML.m_CIMStatus.ToInt() == 2)
            {
			    m_list1DReaderRX.clear();
			    m_listReaderTX.push_back("READ_1D_CODE");

			    tm1MS.timeStart(10000);
			    nThreadIndex++;
            }
            else if (g_IniFile.m_bIsUse1DReader && g_eqpXML.m_CIMStatus.ToInt() < 2)
            {
                g_IniFile.m_nErrorCode = 805;
            }
		}
		break;
	case 3:
		if (m_list1DReaderRX.size()>0)
		{
			if (m_list1DReaderRX.back() == "READ_1D_CODE_OK")
			{
				tm1MS.timeStart(5000);
				nThreadIndex++;
			}
			else
			{
				m_listReaderTX.push_back("SHUTDOWN_1D_CODE");
				g_IniFile.m_nErrorCode = 802;
				nThreadIndex--;
			}
			m_list1DReaderRX.clear();
		}
		else if (tm1MS.timeUp())
		{
			m_listReaderTX.push_back("SHUTDOWN_1D_CODE");
			g_IniFile.m_nErrorCode = 801;
			nThreadIndex--;
		}
		break;
	case 4:
    case nTagClampMag:nThreadIndex = 4;
		if (g_eqpXML.m_strMagzin1DCodeRX == "Y" || g_eqpXML.m_strMagzin1DCodeRX == "N" || g_eqpXML.m_CIMStatus.ToInt() < 2 || !g_IniFile.m_bIsUse1DReader)
		{
            if (g_eqpXML.m_strMagzin1DCodeRX == "Y") g_eqpXML.m_strMagzin1DCodeRX = "";
			m_listReaderTX.push_back("SHUTDOWN_1D_CODE");
			m_listLog.push_back("Start Clamp Magazin");
			g_Motion.AbsMove(Axis_Const::LDY, g_IniFile.m_dLoaderClampMgzPos[1]);
			nThreadIndex++;
		}
		else if (tm1MS.timeUp())
		{
			g_IniFile.m_nErrorCode = 803;
            m_listReaderTX.push_back("SHUTDOWN_1D_CODE");
			nThreadIndex = nTagReRead1D;
		}
		break;
	case 5:
		if (g_Motion.IsMotionDone(Axis_Const::LDY))
		{
			g_Motion.AbsMove(Axis_Const::LDZ, g_IniFile.m_dLoaderClampMgzPos[2]);
			nThreadIndex++;
		}
		break;
	case 6:
		if (g_Motion.IsMotionDone(Axis_Const::LDZ))
		{
			g_Motion.SetDO(DO::LoaderClamper, false);        //Clamp sensor reversed
			tm1MS.timeStart(500);
			nThreadIndex++;
		}
		break;
	case 7:
        /* Error much
		if (g_Motion.GetDI(DI::LoaderClamperDown))
		{
			m_bConveyerMagazineReady = false;
			nThreadIndex = 0;
			g_IniFile.m_nErrorCode = 406;
		}
        */
		if (tm1MS.timeUp() && g_Motion.GetDI(DI::LoaderClamperDown))
		{
			nThreadIndex++;
		}
		break;
	case 8:
		if (!g_Motion.GetDI(DI::LoaderClamperMgzExist)) g_IniFile.m_nErrorCode = 407;
		else if (g_Motion.IsMotionDone(Axis_Const::LDZ) && g_Motion.IsMotionDone(Axis_Const::LDY))
		{
			g_Motion.AbsMove(Axis_Const::LDZ, 0.0);
			nThreadIndex++;
		}
		break;
	case 9:
		if (g_Motion.IsLastPosDone(Axis_Const::LDZ))
		{
			m_bConveyerMagazineReady = false;
			g_Motion.AbsMove(Axis_Const::LDY, g_IniFile.m_dMagazinePushPosY);
			nMgzIndex = 0;
			nThreadIndex++;
		}
		break;
	case 10:
	case nTagPush:nThreadIndex = 10;
        if (g_Motion.IsMotionDone(Axis_Const::LDY) && g_eqpXML.m_strMagzin1DCodeRX == "N")
        {
            nThreadIndex = nTagUnClampMgz;
        }
		else if (g_Motion.IsMotionDone(Axis_Const::LDY) && g_eqpXML.m_strMagzin1DCodeRX != "N")
		{
			if (!g_Motion.GetDI(DI::LeftLaneChangerIn))
			{
                if (!g_IniFile.m_bIsMagazineUpFirst)
				    g_Motion.AbsMove(Axis_Const::LDZ, g_IniFile.m_dMagazinePushPosZ + nMgzIndex*g_IniFile.m_dLoaderMgzPitch);
                else
                    g_Motion.AbsMove(Axis_Const::LDZ, g_IniFile.m_dMagazinePushPosUpFirstZ - nMgzIndex*g_IniFile.m_dLoaderMgzPitch);

				nThreadIndex++;
			}
			else g_IniFile.m_nErrorCode = 302;
		}
		break;
	case 11:
		if (g_Motion.IsMotionDone(Axis_Const::LDZ))
		{
			m_bLoaderClamperReady = true;
			nThreadIndex++;
		}
		break;
	case 12:
        if (!m_bLoaderClamperReady && !g_Motion.GetDI(DI::LeftLaneChangerIn) && !m_bLoaderClamperChangeMgz)
        {
            g_Motion.SetDO(DO::LoaderPusher, false);
            tm1MS.timeStart(3000);
            nThreadIndex++;
		}
		if (!m_bLoaderClamperReady && !g_Motion.GetDI(DI::LeftLaneChangerIn) && m_bLoaderClamperChangeMgz)
		{
			m_bLoaderClamperChangeMgz = false;
			nThreadIndex = nTagUnClampMgz;
		}
		break;
	case 13:
		if (g_Motion.GetDI(DI::LoaderPusherBwd))
		{
			nMgzIndex++;
			tm1MS.timeStart(100);
			if (nMgzIndex >= g_IniFile.m_nMgzSize) nThreadIndex++;
			else nThreadIndex = nTagPush;
		}
		else if (!g_Motion.GetDO(DO::LoaderPusher))
		{
			g_Motion.SetDO(DO::LoaderPusher, false);
			tm1MS.timeStart(3000);
		}
		else if (tm1MS.timeUp()) g_IniFile.m_nErrorCode = 414;
		break;
	case 14:
	case nTagUnClampMgz:nThreadIndex = 14;
		m_bLoaderClamperChangeMgz = false;
		m_bIsNeedAutoWeightScale = true;
		g_Motion.AbsMove(Axis_Const::LDZ, g_IniFile.m_dLoaderUnClampMgzPos[0]);
		nThreadIndex++;
        break;
	case 15:
		if (g_Motion.IsMotionDone(Axis_Const::LDZ))
		{
			nThreadIndex++;
		}
		break;
	case 16:
		if (m_bConveyerMagazineOutReady)
		{
			if (g_Motion.GetDI(DI::LoaderOutMgzIn)) m_bConveyerMagazineOutReady = false;
			else
			{
				g_Motion.AbsMove(Axis_Const::LDY, g_IniFile.m_dLoaderUnClampMgzPos[1]);
				nThreadIndex++;
			}
		}
		break;
	case 17:
		if (g_Motion.IsMotionDone(Axis_Const::LDY))
		{
			g_Motion.SetDO(DO::LoaderClamper, true);            //un-Clamp
			tm1MS.timeStart(5000);
			nThreadIndex++;
		}
		break;
	case 18:
		if (g_Motion.GetDI(DI::LoaderClamperUp))
		{
			g_Motion.AbsMove(Axis_Const::LDZ, g_IniFile.m_dLoaderUnClampMgzPos[2]);
			nThreadIndex++;
		}
		else if (tm1MS.timeUp()) g_IniFile.m_nErrorCode = 405;
		break;
	case 19:
		if (g_Motion.IsMotionDone(Axis_Const::LDZ))
		{
			g_Motion.AbsMove(Axis_Const::LDY, 0.0);
			nThreadIndex++;
		}
		break;
	case 20:
		if (g_Motion.IsMotionDone(Axis_Const::LDY))
		{
			m_bConveyerMagazineOutReady = false;
            if (g_eqpXML.m_strMagzin1DCodeRX == "N")
            {
                g_eqpXML.m_strMagzin1DCodeRX = "";
                g_IniFile.m_nErrorCode = 804;
            }
			nThreadIndex++;
		}
		break;
	default:
		nThreadIndex = 0;
		break;
	}
}
//---------------------------------------------------------------------------


void __fastcall CMainThread::doLeftLaneChanger(int &nThreadIndex)
{
	static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);
    static C_GetTime tm2MS(EX_SCALE::TIME_1MS, false);
	static int nReTryPushIndex = 0;

	const int nTagPushStrip = 1000;
	const int nTagContinue = 2000;

	switch (nThreadIndex)
	{
	case 0:
		if (g_Motion.GetDI(DI::LeftLaneChangerIn)) g_IniFile.m_nErrorCode = 409;
		else if (g_Motion.GetDI(DI::LeftLaneChangerOut)) g_IniFile.m_nErrorCode = 410;
		else if (g_Motion.GetDI(DI::FrontLaneSprayIn)) g_IniFile.m_nErrorCode = 500;
		else if (g_Motion.GetDI(DI::RearLaneSprayIn)) g_IniFile.m_nErrorCode = 501;
        else
		{
			//g_Motion.AbsMove(Axis_Const::LLC, g_IniFile.m_dLeftLaneChangerMgzPos);
			nThreadIndex++;
		}
		break;
	case 1:
		if (!g_Motion.GetDI(DI::LeftLaneChangerIn) && g_Motion.GetDI(DI::LeftLaneChangerInp) && !g_Motion.GetDI(DI::LeftLaneChangerOut))
		{
			nThreadIndex = nTagContinue;
		}
		else nThreadIndex++;
		break;
	case 2:
        g_Motion.AbsMove(Axis_Const::LLC, g_IniFile.m_dLeftLaneChangerMgzPos);
		nThreadIndex++;
		break;
	case 3:
		if (g_Motion.IsLastPosDone(Axis_Const::LLC))
		{
			nReTryPushIndex = 0;
			nThreadIndex++;
		}
		break;
	case 4:
	case nTagPushStrip:nThreadIndex = 4;
		if (m_bLoaderClamperReady && !g_IniFile.m_bStopLoader && ((int)g_Motion.GetFeedbackPos(Axis_Const::LLC) == (int)g_IniFile.m_dLeftLaneChangerMgzPos))
		{
			g_Motion.SetDO(DO::LoaderPusher, true);
			g_Motion.SetDO(DO::LeftLaneChangerMotor, true);
			g_Motion.SetDO(DO::LeftLaneChangerStopper, true);
			tm1MS.timeStart(5000);
			nThreadIndex++;
		}
		else if (g_Motion.GetDI(DI::LoaderPusherBwd)
			&& !g_Motion.GetDI(DI::LeftLaneChangerIn) && g_Motion.GetDI(DI::LeftLaneChangerInp) && !g_Motion.GetDI(DI::LeftLaneChangerOut))
		{
			nThreadIndex = 0;
		}
		else if ((int)g_Motion.GetFeedbackPos(Axis_Const::LLC) != (int)g_IniFile.m_dLeftLaneChangerMgzPos)
		{
			nThreadIndex = 0;
		}
		break;
    case 5:
        if (g_Motion.GetDI(DI::LeftLaneChangerIn) && tm2MS.timeUp())
        {
            g_Motion.SetDO(DO::LeftLaneChangerPress, !g_Motion.GetDO(DO::LeftLaneChangerPress));
            tm2MS.timeStart(1000);
        }

        if (g_Motion.GetDI(DI::LoaderPusherFwd))
        {
            g_Motion.SetDO(DO::LoaderPusher, false);
            tm1MS.timeStart(5000);
            nThreadIndex++;
        }
		if (!g_Motion.GetDI(DI::LoaderPusherFwd))
		{
			g_Motion.SetDO(DO::LoaderPusher, true);
            tm1MS.timeStart(3000);
		}
		else if (!g_Motion.GetDI(DI::LoaderPusherAlarm)) g_IniFile.m_nErrorCode = 411;
		else if (tm1MS.timeUp())  g_IniFile.m_nErrorCode = 412;
        break;
	case 6:
		if (g_Motion.GetDI(DI::LeftLaneChangerIn)) g_Motion.SetDO(DO::LeftLaneChangerPress, true);

		if (g_Motion.GetDI(DI::LoaderPusherBwd) && (g_Motion.GetDI(DI::LeftLaneChangerIn) || g_Motion.GetDI(DI::LeftLaneChangerInp)))
		{
            //ShowNow
			m_arraybShape[0] = true;
			tm1MS.timeStart(10000);
			nThreadIndex++;

            //If Push Substrate then to 0
            nReTryPushIndex = 0;
		}
		else if (!g_Motion.GetDO(DO::LoaderPusher) && !g_Motion.GetDO(DO::LeftLaneChangerMotor) && !g_Motion.GetDI(DI::LeftLaneChangerInp))
		{
            nThreadIndex = nTagPushStrip;
		}
		else if (g_Motion.GetDI(DI::LoaderPusherBwd)
			&& !g_Motion.GetDI(DI::LeftLaneChangerIn) && g_Motion.GetDI(DI::LeftLaneChangerInp) && !g_Motion.GetDI(DI::LeftLaneChangerOut))
		{
			nThreadIndex = 0;
		}
		else if (tm1MS.timeUp())
        {
            m_listLog.push_back("空推");
            nThreadIndex = nTagPushStrip;
            m_bLoaderClamperReady = false;
            //g_IniFile.m_nErrorCode = 412;
			nReTryPushIndex++;
			if (nReTryPushIndex >= 3) m_bLoaderClamperChangeMgz = true;
        }
		break;
	case 7:
		if (!g_Motion.GetDI(DI::LeftLaneChangerIn) && g_Motion.GetDI(DI::LeftLaneChangerInp) && !g_Motion.GetDI(DI::LeftLaneChangerOut))
		{
			tm1MS.timeStart(300);
			m_bLoaderClamperReady = false;
			nThreadIndex++;
		}
		else if (!g_Motion.GetDO(DO::LeftLaneChangerMotor))
		{
			g_Motion.SetDO(DO::LeftLaneChangerMotor, true);
			g_Motion.SetDO(DO::LeftLaneChangerStopper, true);
			tm1MS.timeStart(5000);
		}
        else if (tm1MS.timeUp())
        {
            g_IniFile.m_nErrorCode = 413;
        }
		break;
	case 8:
	case nTagContinue:nThreadIndex = 8;
		if (tm1MS.timeUp())
		{
			g_Motion.SetDO(DO::LeftLaneChangerMotor, false);
			g_Motion.SetDO(DO::LeftLaneChangerPress, false);
			m_bLeftLaneChangerReady = true;
			nThreadIndex++;
		}
		break;
	case 9:
		if (!m_bLeftLaneChangerReady)
		{
			//ShowNow
			m_arraybShape[0] = false;
			nThreadIndex++;
		}
		break;
	default:
		nThreadIndex = 0;
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall CMainThread::doSprayerLane(int &nThreadIndex, bool bFront)
{
	static C_GetTime tm1MSFront(EX_SCALE::TIME_1MS, false);
	static C_GetTime tm1MSRear(EX_SCALE::TIME_1MS, false);
	static double dTempLocFX = 0.0;
	static double dTempLocRX = 0.0;
	static double dTempLocFY = 0.0;
	static double dTempLocRY = 0.0;
	static int nStripCount = 0;

	const int nTagReadyWait = 1000;
	const int nTagReadyWork = 2000;
	const int nTagReadyOut = 3000;
	const int nTagAutoWeightScale = 4000;
	const int nTagReadyFinish = 5000;

	C_GetTime *p_tm1MS;

	int iLaneSprayIn, iLaneSprayInp, iLaneSprayOut, iLaneSprayStopDown;
	int oLaneSprayStopper, oLaneSprayMotor;

	if (bFront)
	{
		p_tm1MS = &tm1MSFront;
		iLaneSprayIn = DI::FrontLaneSprayIn;
		iLaneSprayInp = DI::FrontLaneSprayInp;
		iLaneSprayOut = DI::FrontLaneSprayOut;
		iLaneSprayStopDown = DI::FrontLaneSprayStopDown;

		oLaneSprayStopper = DO::FrontLaneSprayStopper;
		oLaneSprayMotor = DO::FrontLaneSprayMotor;

	}
	else
	{
		p_tm1MS = &tm1MSRear;
		iLaneSprayIn = DI::RearLaneSprayIn;
		iLaneSprayInp = DI::RearLaneSprayInp;
		iLaneSprayOut = DI::RearLaneSprayOut;
		iLaneSprayStopDown = DI::RearLaneSprayStopDown;

		oLaneSprayStopper = DO::RearLaneSprayStopper;
		oLaneSprayMotor = DO::RearLaneSprayMotor;

	}

	switch (nThreadIndex)
	{
	case 0:
		if (bFront)
		{
			if (m_bIsNeedPreMoveSprayer && !CheckXYZAtSprayReadyPos(bFront) && !m_bIsSprayerLock)
			{
                m_bIsSprayerLock = true;
				m_bIsNeedPreMoveSprayer = false;
				nThreadIndex++;
			}
			else nThreadIndex = nTagReadyWait;
		}
		else
		{
			if (m_bIsNeedPreMoveSprayer && !CheckXYZAtSprayReadyPos(bFront) && !m_bIsSprayerLock)
			{
                m_bIsSprayerLock = true;
				m_bIsNeedPreMoveSprayer = false;
				nThreadIndex++;
			}
			else nThreadIndex = nTagReadyWait;
		}
		break;
	case 1:
		g_Motion.AbsMove(Axis_Const::SPZ, 0.0);
        nThreadIndex++;
		break;
	case 2:
		if (g_Motion.IsPosDone(Axis_Const::SPZ, 0.0))
		{
			g_Motion.AbsMove(Axis_Const::SPX, g_IniFile.m_dStartSprayPosX[bFront]);
			g_Motion.AbsMove(Axis_Const::SPY, g_IniFile.m_dStartSprayPosY[bFront]);
            nThreadIndex++;
		}
		break;
	case 3:
		if (g_Motion.IsPosDone(Axis_Const::SPX, g_IniFile.m_dStartSprayPosX[bFront])
			&& g_Motion.IsPosDone(Axis_Const::SPY, g_IniFile.m_dStartSprayPosY[bFront]))
		{
            g_Motion.AbsSMove(Axis_Const::SPZ, g_IniFile.m_dSprayReadyPos);
			nThreadIndex++;
		}
		break;
    case 4:
        if (g_Motion.IsPosDone(Axis_Const::SPZ, g_IniFile.m_dSprayReadyPos))
		{	
            m_bIsSprayerLock = false;
			nThreadIndex++;
		}
		break;
	case 5:
	case nTagReadyWait:nThreadIndex = 5;
        int nRail; (bFront) ? nRail = 1: nRail = 2;
        if (!CheckXYInSprayRange()) nThreadIndex = 0;
        else if (g_IniFile.m_nRailOption == 0 || g_IniFile.m_nRailOption == nRail)
        {
		    if (m_bLeftLaneChangerReady && !m_bIsLeftLaneChangerLock)
		    {
			    m_bIsLeftLaneChangerLock = true;
			    nThreadIndex++;
            }
		}
		break;
	case 6:
		if (!g_Motion.GetDI(iLaneSprayIn) && g_Motion.GetDI(iLaneSprayInp) && !g_Motion.GetDI(iLaneSprayOut))
		{
			nThreadIndex = nTagReadyWork;
		}
		else nThreadIndex++;
		break;
	case 7:
		if (g_Motion.GetDI(iLaneSprayIn)) bFront ? g_IniFile.m_nErrorCode = 500 : g_IniFile.m_nErrorCode = 501;
		else if (g_Motion.GetDI(DI::LeftLaneChangerIn)) g_IniFile.m_nErrorCode = 409;
		else if (g_Motion.GetDI(DI::LeftLaneChangerOut)) g_IniFile.m_nErrorCode = 410;
		else
		{
			g_Motion.AbsMove(Axis_Const::LLC, g_IniFile.m_dLeftLaneChangerSprayPos[bFront]);
			nThreadIndex++;
		}
		break;
	case 8:
		if (g_Motion.IsLastPosDone(Axis_Const::LLC))
		{
			g_Motion.SetDO(DO::LeftLaneChangerStopper, false);          //true: up  false:down
			g_Motion.SetDO(oLaneSprayStopper, true);
			p_tm1MS->timeStart(3000);
			nThreadIndex++;
		}
		break;
	case 9:
		if (g_Motion.GetDI(DI::LeftLaneChangerStopDown))
		{
			g_Motion.SetDO(DO::LeftLaneChangerMotor, true);
			g_Motion.SetDO(oLaneSprayMotor, true);

			nThreadIndex++;
		}
		else if (p_tm1MS->timeUp()) g_IniFile.m_nErrorCode = 415;
		break;
    case 10:
        if (g_Motion.GetDI(iLaneSprayIn))
        {
            p_tm1MS->timeStart(10000);
            nThreadIndex++;
        }
        else nThreadIndex--;
        break;
	case 11:
        if (!g_Motion.GetDI(iLaneSprayIn) && g_Motion.GetDI(iLaneSprayInp))
		{
			p_tm1MS->timeStart(100); 
			nThreadIndex++;
		}
        else if (!g_Motion.GetDO(oLaneSprayMotor))
        {
            g_Motion.SetDO(DO::LeftLaneChangerMotor, true);
			g_Motion.SetDO(oLaneSprayMotor, true);
			p_tm1MS->timeStart(10000);
        }
		else if (p_tm1MS->timeUp()) bFront ? g_IniFile.m_nErrorCode = 502 : g_IniFile.m_nErrorCode = 503;
		break;
	case 12:
	case nTagReadyWork:nThreadIndex = 12;
		if (p_tm1MS->timeUp())
		{
			//ShowNow
			m_arraybShape[0] = false;
			if (bFront) m_arraybShape[1] = true;
			else m_arraybShape[2] = true;
			
			bFront ? m_listPickLane.push_back("FRONT") : m_listPickLane.push_back("REAR");

			g_Motion.SetDO(DO::LeftLaneChangerMotor, false);
			g_Motion.SetDO(oLaneSprayMotor, false);
			g_Motion.SetDO(DO::LeftLaneChangerStopper, true);
			//p_tm1MS->timeStart(1000); //for UPH
			nThreadIndex++;
		}
		break;
	case 13:
		if (p_tm1MS->timeUp())
		{   
			m_bLeftLaneChangerReady = false;
			m_bIsLeftLaneChangerLock = false;

			if (!g_IniFile.m_bUseSprayer) nThreadIndex++;
			else nThreadIndex = nTagReadyOut;
		}
		break;
	case 14:
		if (!m_bIsSprayerLock)
		{
			m_bIsSprayerLock = true;
			//g_Motion.AbsMove(Axis_Const::SPZ, 0.0);  //Not necessary go to 0.0 in AutoMode
			nThreadIndex++;
		}
		break;
	case 15:
		if (true) //(g_Motion.IsLastPosDone(Axis_Const::SPZ))               //I don't know where is it Last Pos, It is Damn.
		{
			g_Motion.AbsMove(Axis_Const::SPX, g_IniFile.m_dStartSprayPosX[bFront]);
			g_Motion.AbsMove(Axis_Const::SPY, g_IniFile.m_dStartSprayPosY[bFront]);
			nThreadIndex++;
		}
		break;
	case 16:
		if (g_Motion.IsPosDone(Axis_Const::SPX, g_IniFile.m_dStartSprayPosX[bFront])
            && g_Motion.IsPosDone(Axis_Const::SPY, g_IniFile.m_dStartSprayPosY[bFront]))
		{
			if (bFront)
			{
				m_bSBTSprayDoneF = false;
				m_bStartSBTSprayF = true;
			}
			else
			{
				m_bSBTSprayDoneR = false;
				m_bStartSBTSprayR = true;
			}
			nThreadIndex++;
		}
		break;
	case 17:
		if ((bFront && m_bSBTSprayDoneF) || (!bFront && m_bSBTSprayDoneR))
		{
			m_bIsSprayerLock = false;
			nThreadIndex++;
		}
		else if ((bFront && !m_bStartSBTSprayF) || (!bFront && !m_bStartSBTSprayR))
		{
			if (bFront)
			{
				m_bStartSBTSprayF = true;          //restart  again
				CMainThread::nThreadIndex[17] = 0;
			}
			else
			{
				m_bStartSBTSprayR = true;          //restart  again
				CMainThread::nThreadIndex[12] = 0;
			}
		}
		break;
	case 18:
	case nTagReadyOut:nThreadIndex = 18;
		n_bLaneSprayReady[bFront] = true;
        if (g_IniFile.m_nRailOption == 0)
        {
            g_Motion.AbsMove(Axis_Const::SPX, g_IniFile.m_dStartSprayPosX[!bFront]);
			g_Motion.AbsMove(Axis_Const::SPY, g_IniFile.m_dStartSprayPosY[!bFront]);
        }
        else
        {
            g_Motion.AbsMove(Axis_Const::SPX, g_IniFile.m_dStartSprayPosX[bFront]);
			g_Motion.AbsMove(Axis_Const::SPY, g_IniFile.m_dStartSprayPosY[bFront]);
        }
		nThreadIndex++;
		break;
	case 19:
		if (!n_bLaneSprayReady[bFront])
		{
			//ShowNow
			if (bFront) m_arraybShape[1] = false;
			else m_arraybShape[2] = false;

            if (g_IniFile.m_bUseUnClampAutoWeightScale) nThreadIndex++;
			else nThreadIndex = nTagReadyFinish;
		}
		break;
	case 20:
	case nTagAutoWeightScale:nThreadIndex = 20;
		if (bFront)
		{
			if (m_bIsNeedAutoWeightScale)
			{
				m_bIsNeedAutoWeightScale = false;
				nThreadIndex++;

			    dTempLocFX = g_Motion.GetFeedbackPos(Axis_Const::SPX);
			    dTempLocFY = g_Motion.GetFeedbackPos(Axis_Const::SPY);
            }
			else nThreadIndex = nTagReadyFinish;
		}
		else
		{
			if (m_bIsNeedAutoWeightScale)
			{
				m_bIsNeedAutoWeightScale = false;
				nThreadIndex++;

			    dTempLocRX = g_Motion.GetFeedbackPos(Axis_Const::SPX);
			    dTempLocRY = g_Motion.GetFeedbackPos(Axis_Const::SPY);
            }
			else nThreadIndex = nTagReadyFinish;
		}
		break;
	case 21:
		if (!m_bIsSprayerLock)
		{
			m_bIsSprayerLock = true;
			m_bStartFluxScaleSpray = true;
			CMainThread::nThreadIndex[13] = 0;
			nThreadIndex++;
		}
		break;
	case 22:
		if (!m_bStartFluxScaleSpray)
		{
			g_Motion.AbsMove(Axis_Const::SPZ, 0.0);
			nThreadIndex++;
		}
		break;
	case 23:
		if (g_Motion.IsPosDone(Axis_Const::SPZ, 0.0))
		{
			if (bFront)
			{
				g_Motion.AbsMove(Axis_Const::SPX, dTempLocFX);
				g_Motion.AbsMove(Axis_Const::SPY, dTempLocFY);
			}
			else
			{
				g_Motion.AbsMove(Axis_Const::SPX, dTempLocRX);
				g_Motion.AbsMove(Axis_Const::SPY, dTempLocRY);
			}
			nThreadIndex++;
		}
		break;
	case 24:
		if (bFront && g_Motion.IsPosDone(Axis_Const::SPX, dTempLocFX)
			&& g_Motion.IsPosDone(Axis_Const::SPY, dTempLocFY))
		{
			dTempLocFX = 0.0;
			dTempLocFY = 0.0;
			nThreadIndex++;
			m_bIsNeedPreMoveSprayer = true;
			m_bIsSprayerLock = false;
		}
		if (!bFront && g_Motion.IsPosDone(Axis_Const::SPX, dTempLocRX)
			&& g_Motion.IsPosDone(Axis_Const::SPY, dTempLocRY))
		{
			dTempLocRX = 0.0;
			dTempLocRY = 0.0;
			m_bIsNeedPreMoveSprayer = true;
			m_bIsSprayerLock = false;
			nThreadIndex++;
		}
		break;
	case 25:
	case nTagReadyFinish:nThreadIndex = 25;
		nThreadIndex++;
		break;
	default:
		nThreadIndex = 0;
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall CMainThread::doCCDBufferLane(int &nThreadIndex)
{
	static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);
	static C_GetTime tm2MS(EX_SCALE::TIME_1MS, false);

	static bool bFront = true;
	static bool bCCDCheckResult = false;
	static int nConveyerIndex = 0;
	static int nMgzIndex = 0;
	static int nCCDCheckPosIndex = 0;

	const int nTagReadyWork = 1000;
	const int nTagNextCCDCheckPos = 2000;
	const int nTagReadyOut = 3000;
	const int nTagNGMgz = 4000;
	
	switch (nThreadIndex)
	{
	case 0:
		if (g_Motion.GetDI(DI::FrontLaneSprayOut)) g_IniFile.m_nErrorCode = 700;
		else if (g_Motion.GetDI(DI::RearLaneSprayOut)) g_IniFile.m_nErrorCode = 701;
		else if (g_Motion.GetDI(DI::RightLaneChangerIn)) g_IniFile.m_nErrorCode = 702;
		else if (g_Motion.GetDI(DI::RightLaneChangerOut)) g_IniFile.m_nErrorCode = 703;
		else if (!g_Motion.GetDI(DI::RightPusherBwd)) g_IniFile.m_nErrorCode = 704;
		else if (g_Motion.IsLastPosDone(Axis_Const::RLC))
		{
			if (m_listPickLane.size()>0)
			{
				if ((m_listPickLane.front() == "FRONT")) bFront = true;
				else if ((m_listPickLane.front() == "REAR")) bFront = false;

				g_Motion.AbsMove(Axis_Const::RLC, g_IniFile.m_dRightLaneChangerSprayPos[bFront]);
				nThreadIndex++;
			}
		}
		break;
	case 1:
		if (g_Motion.GetDI(DI::FrontLaneSprayOut)) g_IniFile.m_nErrorCode = 700;
		else if (g_Motion.GetDI(DI::RearLaneSprayOut)) g_IniFile.m_nErrorCode = 701;
		else if (g_Motion.GetDI(DI::RightLaneChangerIn)) g_IniFile.m_nErrorCode = 702;
		else if (g_Motion.GetDI(DI::RightLaneChangerOut)) g_IniFile.m_nErrorCode = 703;
		else if (!g_Motion.GetDI(DI::RightPusherBwd)) g_IniFile.m_nErrorCode = 704;
		else if ((n_bLaneSprayReady[1] || n_bLaneSprayReady[0]) && g_Motion.IsLastPosDone(Axis_Const::RLC))
		{
			if (m_listPickLane.size() > 0)
			{
				if (n_bLaneSprayReady[1] && (m_listPickLane.front() == "FRONT")) bFront = true;
				else if (n_bLaneSprayReady[0] && (m_listPickLane.front() == "REAR")) bFront = false;

				m_listPickLane.pop_front();

				g_Motion.AbsMove(Axis_Const::RLC, g_IniFile.m_dRightLaneChangerSprayPos[bFront]);

				nThreadIndex++;
			}
		}
		else if (!g_Motion.GetDI(DI::RightLaneChangerIn) && g_Motion.GetDI(DI::RightLaneChangerInp) && !g_Motion.GetDI(DI::RearLaneSprayOut))
		{
			nThreadIndex = nTagReadyWork;
		}
		break;
	case 2:
		if (g_Motion.IsLastPosDone(Axis_Const::RLC))
		{
			bFront ? g_Motion.SetDO(DO::FrontLaneSprayStopper, false) : g_Motion.SetDO(DO::RearLaneSprayStopper, false);
			g_Motion.SetDO(DO::RightLaneChangerStopper, true);
			tm1MS.timeStart(1000);
			nThreadIndex++;
		}
		break;
	case 3:
		//if(g_Motion.GetDI(DI::RightLaneChangerStopUp))
		if (tm1MS.timeUp())
		{
			bFront ? g_Motion.SetDO(DO::FrontLaneSprayMotor, true) : g_Motion.SetDO(DO::RearLaneSprayMotor, true);
			g_Motion.SetDO(DO::RightLaneChangerMotor, true);
			tm1MS.timeStart(10000);
			nThreadIndex++;
		}
		//else if(tm1MS.timeUp()) g_IniFile.m_nErrorCode=705;
		break;
	case 4:
		if (g_Motion.GetDI(DI::RightLaneChangerInp) && !g_Motion.GetDI(DI::RightLaneChangerIn))
		{
			tm1MS.timeStart(300);
			nThreadIndex++;
		}
		else if (!g_Motion.GetDO(DO::RightLaneChangerMotor))
		{
			bFront ? g_Motion.SetDO(DO::FrontLaneSprayMotor, true) : g_Motion.SetDO(DO::RearLaneSprayMotor, true);
			g_Motion.SetDO(DO::RightLaneChangerMotor, true);
			tm1MS.timeStart(10000);
		}
		else if (tm1MS.timeUp()) g_IniFile.m_nErrorCode = 706;
		break;
	case 5:
	case nTagReadyWork:nThreadIndex = 5;
		if (tm1MS.timeUp())
		{
			//ShowNow
			if (bFront) m_arraybShape[1] = false;
			else m_arraybShape[2] = false;
			m_arraybShape[3] = true;

			bFront ? g_Motion.SetDO(DO::FrontLaneSprayMotor, false) : g_Motion.SetDO(DO::RearLaneSprayMotor, false);
			g_Motion.SetDO(DO::RightLaneChangerMotor, false);

			bFront ? n_bLaneSprayReady[1] = false : n_bLaneSprayReady[0] = false;

			bCCDCheckResult = false;
			if (g_IniFile.m_bUseCCD) { nCCDCheckPosIndex = 0; nThreadIndex++; }
			else nThreadIndex = nTagReadyOut;
		}
		break;
	case 6:
	case nTagNextCCDCheckPos:nThreadIndex = 6;
		if (g_IniFile.m_bIsUseCCDCheckPos[nCCDCheckPosIndex])
		{
			nThreadIndex++;
		}
		else
		{
			if (nCCDCheckPosIndex + 1 < 4) nThreadIndex = nTagNextCCDCheckPos;
			else nThreadIndex = nTagReadyOut;
			nCCDCheckPosIndex++;
		}
		break;
	case 7:
		if (nCCDCheckPosIndex >= 4) nCCDCheckPosIndex = 0;
		g_Motion.AbsMove(Axis_Const::CDX, g_IniFile.m_dCCDCheckPosX[nCCDCheckPosIndex]);
		g_Motion.AbsMove(Axis_Const::RLC, g_IniFile.m_dCCDCheckPosY[nCCDCheckPosIndex]);
		nThreadIndex++;
		break;
	case 8:
		if (g_Motion.IsLastPosDone(Axis_Const::CDX) && g_Motion.IsLastPosDone(Axis_Const::RLC))
		{
			tm1MS.timeStart(500);          //Stable Time
			nThreadIndex++;
		}
		break;
	case 9:
		if (tm1MS.timeUp())
		{
			m_listCCDRX.clear();
			m_listTX.push_back("PROCESS_CCD");
			tm1MS.timeStart(3000);
			nThreadIndex++;
		}
		break;
	case 10:
		if (m_listCCDRX.size()>0)
		{
			if (m_listCCDRX.front() == "PROCESS_CCD_OK")
			{
				m_listLog.push_back("Flux ("+IntToStr(nCCDCheckPosIndex)+")有無檢查-->OK");
				bCCDCheckResult = true;
			}
			else
			{
				m_listLog.push_back("Flux ("+IntToStr(nCCDCheckPosIndex)+")有無檢查-->NG");
                //20160704 bypass NGMgz If the NGMag be off line
                bCCDCheckResult = false;
                //bCCDCheckResult = true;
			}
			nThreadIndex++;
		}
		else if (tm1MS.timeUp())
		{
			g_IniFile.m_nErrorCode = 707;
			nThreadIndex--;
		}
		break;
	case 11:
	case nTagReadyOut:nThreadIndex = 11;
		if (!g_IniFile.m_bUseCCD)
		{
			//to conveyer
			nThreadIndex++;
		}
		else if (bCCDCheckResult)
		{
			if (nCCDCheckPosIndex + 1 < 4) nThreadIndex = nTagNextCCDCheckPos;		//to NextPos
			else nThreadIndex++;                                                    //to conveyer
			nCCDCheckPosIndex++;
		}
		else
		{
			//to NG Magazine
			nThreadIndex = nTagNGMgz;
		}
		break;
	case 12:
		if (g_Motion.GetDI(DI::RightLaneChangerIn)) g_IniFile.m_nErrorCode = 702;
		else if (g_Motion.GetDI(DI::RightLaneChangerOut)) g_IniFile.m_nErrorCode = 703;
		else if (!g_Motion.GetDI(DI::RightPusherBwd)) g_IniFile.m_nErrorCode = 704;
		else
		{
			if (nConveyerIndex >= 5) nConveyerIndex = 0;
            if (g_IniFile.m_dConveyerPos[nConveyerIndex] != 0.0)
            {
			    g_Motion.AbsMove(Axis_Const::RLC, g_IniFile.m_dConveyerPos[nConveyerIndex]);
			    nConveyerIndex++;
			    nThreadIndex++;
            }
            else
            {
                nConveyerIndex++;
                nThreadIndex = nTagReadyOut;
            }
		}
		break;
	case 13:
		//if ((g_Motion.GetDI(DI::ReadyOut) || g_IniFile.m_bForceEject) && g_Motion.IsLastPosDone(Axis_Const::RLC))           //bypass
        if (g_Motion.IsLastPosDone(Axis_Const::RLC))
		{
			g_Motion.SetDO(DO::OutConveyerMotor, true);
			g_Motion.SetDO(DO::RightLaneChangerStopper, false);     //Stoper down
            m_nStripCount++;
			m_nStripCountForAutoFillFlux++;
			//Check IsNeedToAutoFillFlux
			if ((m_nStripCountForAutoFillFlux % g_IniFile.m_nAutoFillFulxPerCount) == 0)
			{
				m_bIsStripCountNeedAutoFillFlux = true;
			}
			//Count UPU
			m_listUPUTime.push_back(tm2MS.timeDevEnd());
			tm2MS.timeDevStart();
			tm1MS.timeStart(3000);
			nThreadIndex++;
		}
		break;
    case 14:
        if (g_Motion.GetDI(DI::RightLaneChangerStopDown) || !g_IniFile.m_bUseCCD)
        {
            tm1MS.timeStart(g_IniFile.m_dRightLaneChangerDelayTime*1000);
            nThreadIndex++;
        }
        else if (tm1MS.timeUp()) g_IniFile.m_nErrorCode = 705;
		break;
	case 15:
		if (tm1MS.timeUp())
		{
			g_Motion.SetDO(DO::RightLaneChangerMotor, true);
			tm1MS.timeStart(3000);
			nThreadIndex++;
		}
		break;
	case 16:
		if (g_Motion.GetDI(DI::RightLaneChangerOut))
		{
			tm1MS.timeStart(2000);
			nThreadIndex++;
		}
		else if (!g_Motion.GetDO(DO::RightLaneChangerMotor))
		{
			g_Motion.SetDO(DO::RightLaneChangerMotor, true);
			g_Motion.SetDO(DO::OutConveyerMotor, true);
			tm1MS.timeStart(3000);
		}
		else if (tm1MS.timeUp()) g_IniFile.m_nErrorCode = 708;
		break;
	case 17:
		if (tm1MS.timeUp())
		{
			if (g_IniFile.m_bIsUseRightLCPusher) g_Motion.SetDO(DO::RightLaneChangerPusher, true);
			tm1MS.timeStart(5000);
			nThreadIndex++;
		}
		break;
	case 18:
		if (!g_IniFile.m_bIsUseRightLCPusher)
		{
			tm1MS.timeStart(5000);
			nThreadIndex++;
		}
		else if (g_Motion.GetDI(DI::RightPusherFwd))
		{
			g_Motion.SetDO(DO::RightLaneChangerPusher, false);
			tm1MS.timeStart(5000);
			nThreadIndex++;
		}
		else if (!g_Motion.GetDO(DO::RightLaneChangerPusher))
		{
			g_Motion.SetDO(DO::RightLaneChangerPusher, true);
			tm1MS.timeStart(5000);
		}
		else if (g_Motion.GetDI(DI::RightPusherAlarm)) g_IniFile.m_nErrorCode = 711;
		else if (tm1MS.timeUp()) g_IniFile.m_nErrorCode = 710;
		break;
	case 19:
		if (g_Motion.GetDI(DI::RightPusherBwd))
		{
			//ShowNow
			m_arraybShape[3] = false;
			g_Motion.SetDO(DO::RightLaneChangerStopper, true);
			g_Motion.SetDO(DO::RightLaneChangerMotor, false);
			nThreadIndex = 0;      // return
		}
		else if (tm1MS.timeUp()) g_IniFile.m_nErrorCode = 712;
		break;
	case 20:
	case nTagNGMgz:nThreadIndex = 20;
		if (g_Motion.GetDI(DI::RightLaneChangerIn)) g_IniFile.m_nErrorCode = 702;
		else if (g_Motion.GetDI(DI::RightLaneChangerOut)) g_IniFile.m_nErrorCode = 703;
		else if (!g_Motion.GetDI(DI::RightPusherBwd)) g_IniFile.m_nErrorCode = 704;
		else
		{
			g_Motion.AbsMove(Axis_Const::RLC, g_IniFile.m_dNGMagPos);
            if (!g_IniFile.m_bIsMgzUpFirst)
                g_Motion.AbsMove(Axis_Const::MGZ, g_IniFile.m_dMgzStartPos - g_IniFile.m_dMgzPitch*nMgzIndex);
            else
                g_Motion.AbsMove(Axis_Const::MGZ, g_IniFile.m_dMgzStartPosUpFirst + g_IniFile.m_dMgzPitch*nMgzIndex);
			nMgzIndex++;
			nThreadIndex++;
		}
		break;
	case 21:
		if (g_Motion.IsLastPosDone(Axis_Const::MGZ) && g_Motion.IsLastPosDone(Axis_Const::RLC))
		{
			tm1MS.timeStart(300);
			nThreadIndex++;
		}
		break;
	case 22:
		if (tm1MS.timeUp())
		{
			g_Motion.SetDO(DO::OutConveyerMotor, true);
			g_Motion.SetDO(DO::RightLaneChangerStopper, false);     //down
			tm1MS.timeStart(3000);
			nThreadIndex++;
		}
		break;
	case 23:
		if (g_Motion.GetDI(DI::RightLaneChangerStopDown))
		{
			g_Motion.SetDO(DO::RightLaneChangerMotor, true);
			tm1MS.timeStart(3000);
			nThreadIndex++;
		}
		else if (tm1MS.timeUp()) g_IniFile.m_nErrorCode = 705;
		break;
	case 24:
		if (g_Motion.GetDI(DI::RightLaneChangerOut))
		{
			tm1MS.timeStart(2000);
			nThreadIndex++;
		}
		else if (!g_Motion.GetDO(DO::RightLaneChangerMotor))
		{
			g_Motion.SetDO(DO::RightLaneChangerMotor, true);
			g_Motion.SetDO(DO::OutConveyerMotor, true);
			tm1MS.timeStart(3000);
		}
		else if (tm1MS.timeUp()) g_IniFile.m_nErrorCode = 708;
		break;
	case 25:
		if (tm1MS.timeUp())
		{
			g_Motion.SetDO(DO::RightLaneChangerPusher, true);
			tm1MS.timeStart(5000);
			nThreadIndex++;
		}
		break;
	case 26:
		if (g_Motion.GetDI(DI::RightPusherFwd))
		{
			g_Motion.SetDO(DO::RightLaneChangerPusher, false);
			tm1MS.timeStart(5000);
			nThreadIndex++;
		}
		else if (!g_Motion.GetDO(DO::RightLaneChangerPusher))
		{
			g_Motion.SetDO(DO::RightLaneChangerPusher, true);
			tm1MS.timeStart(5000);
		}
		else if (g_Motion.GetDI(DI::RightPusherAlarm)) g_IniFile.m_nErrorCode = 711;
		else if (tm1MS.timeUp()) g_IniFile.m_nErrorCode = 710;
		break;
	case 27:
		if (g_Motion.GetDI(DI::RightPusherBwd))
		{
			if (nMgzIndex <= g_IniFile.m_nMgzSize)
			{
				//ShowNow
				m_arraybShape[3] = false;
				g_Motion.SetDO(DO::RightLaneChangerStopper, true);
                g_Motion.SetDO(DO::RightLaneChangerMotor, false);
				nThreadIndex = 0;      // return
			}
			else g_IniFile.m_nErrorCode = 713;
		}
		else if (tm1MS.timeUp()) g_IniFile.m_nErrorCode = 712;
		break;
	default:
		nThreadIndex = 0;
		break;
	}
}
//---------------------------------------------------------------------------


void __fastcall CMainThread::doFillFlux(int &nThreadIndex)
{
	static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

	switch (nThreadIndex)
	{
	case 0:
		if (!g_Motion.GetDI(DI::FluxBoxLevel))   //Alarm and not Stop
		{
			g_IniFile.m_nErrorCode = 1002;
			nThreadIndex++;
		}
        else nThreadIndex++;
		break;
	case 1:
		//Protect Manual Control Error. >.< If Auto, be not happened
		if (!g_Motion.GetDI(DI::FluxTankLevelUp))
        {
            g_IniFile.m_nErrorCode = 602;
            m_bStartFillFlux = false;
        }
        else if (g_Motion.GetDI(DI::FluxTankLevelMid))
        {
            g_IniFile.m_nErrorCode = 603;
            m_bStartFillFlux = false;
        }
		else
		{
			nThreadIndex++;
		}
		break;
	case 2:
        if (m_bIsSprayerLock)
        {
            g_Motion.SetDO(DO::FluxTankVacuumIn, true);
            g_Motion.SetDO(DO::FluxTankVacOn, true);
            tm1MS.timeStart(500);
			nThreadIndex++;
		}
		break;
    case 3:
        if (tm1MS.timeUp())
        {
            g_Motion.SetDO(DO::FluxTankFluxIn, true);
            tm1MS.timeStart(g_IniFile.m_nAutoFillTime * 1000);
            nThreadIndex++;
        }
        break;
	case 4:
		//Protect Manual Control Error. >.< If Auto, be not happened
		if (g_Motion.GetDI(DI::FluxTankLevelMid) || !g_Motion.GetDI(DI::FluxTankLevelUp) || tm1MS.timeUp())
		{
            g_Motion.SetDO(DO::FluxTankFluxIn, false);
            g_Motion.SetDO(DO::FluxTankVacuumIn, false);
            g_Motion.SetDO(DO::FluxTankVacOn, false);
            m_bIsStripCountNeedCopy = true;
            tm1MSFluxLifeTime.timeDevStart();
			
			g_Motion.SetDO(DO::FluxTankAirOn, true); // For Fix the tank vaccum
			tm1MS.timeStart(8000);
			nThreadIndex++;
		}
		break;
	case 5:
		if (tm1MS.timeUp())
		{
			nThreadIndex++;
		}
		break;
	default:
		m_bStartFillFlux = false;
		nThreadIndex = 0;
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall CMainThread::doSBTSpray(int &nThreadIndex, bool bFront)
{
	static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

	static double dTempLocFX = 0.0;
    static double dTempLocRX = 0.0;
	static double dTempLocFY = 0.0;
    static double dTempLocRY = 0.0;
    static double dNextPos = 0.0;
	static int nMoveIndex = 0;
    static bool bCountTiime = false;

	const int nStartDredge = 1000;
	const int nStartWork = 2000;
	const int nNextMove = 3000;
    const int nFinished = 4000;

	switch (nThreadIndex)
	{
	case 0:
		if (!g_Motion.GetDI(DI::FluxBoxLevel))
		{
			g_IniFile.m_nErrorCode = 600;
			if (bFront) m_bStartSBTSprayF = false;
            else m_bStartSBTSprayR = false;
            if (bFront) m_bSBTSprayDoneF = false;
            else m_bSBTSprayDoneR = false;
		    nThreadIndex = 0;
		}
		//detect Tank Level here
		if ((m_bIsSprayerLock && !g_Motion.GetDI(DI::FluxTankLevelDown)) || m_bIsStripCountNeedAutoFillFlux == true)
		{
			if (m_bIsStripCountNeedAutoFillFlux == true) m_bIsStripCountNeedAutoFillFlux = false;
			m_listLog.push_back("警告! 高壓Flux桶不足 系統啟動自動補Fulx");
			m_bStartFillFlux = true;
			CMainThread::nThreadIndex[18] = 0;
			if (!bCountTiime)
            {
                tm1MS.timeStart(600000);
                bCountTiime = true;
            }
			nThreadIndex++;
		}
		else nThreadIndex = nStartWork;
		break;
	case 1:
		if (m_bStartFillFlux == false && g_Motion.GetDI(DI::FluxTankLevelDown))
		{
            bCountTiime = false;
			tm1MS.timeStart(300);
			nThreadIndex++;
		}
		else if (tm1MS.timeUp())
		{
			m_listLog.push_back("嚴重警告! 自動補Fulx超過10分鐘, 系統停機. 請確認底下Flux存量");
			g_IniFile.m_nErrorCode = 51;
			if (bFront)
			{
				m_bStartSBTSprayF = false;
				m_bSBTSprayDoneF = false;
			}
			else
			{
				m_bStartSBTSprayR = false;
				m_bSBTSprayDoneR = false;
			}

			m_bStartFillFlux = false;
            bCountTiime = false;
			nThreadIndex = 0;
		}
		else if (m_bStartFillFlux == false && !g_Motion.GetDI(DI::FluxTankLevelDown))
		{
			nThreadIndex = 0;
		}
		break;
	case 2:
	case nStartDredge:nThreadIndex = 2;
		if (tm1MS.timeUp())
		{
            if (bFront)
            {
			    dTempLocFX = g_Motion.GetFeedbackPos(Axis_Const::SPX);
			    dTempLocFY = g_Motion.GetFeedbackPos(Axis_Const::SPY);
            }
            else
            {
                dTempLocRX = g_Motion.GetFeedbackPos(Axis_Const::SPX);
			    dTempLocRY = g_Motion.GetFeedbackPos(Axis_Const::SPY);
            }

			m_bStartDredgeScaleSpray = true;
            m_bScaleSprayDone = false;
			CMainThread::nThreadIndex[14] = 0;
			nThreadIndex++;
		}
		break;
	case 3:
		if (m_bScaleSprayDone == true)
		{
			g_Motion.AbsMove(Axis_Const::SPZ, 0.0);
			nThreadIndex++;
		}
		break;
	case 4:
		if (g_Motion.IsPosDone(Axis_Const::SPZ, 0.0))
		{
            if (bFront)
            {
			    g_Motion.AbsMove(Axis_Const::SPX, dTempLocFX);
			    g_Motion.AbsMove(Axis_Const::SPY, dTempLocFY);
            }
            else
            {
                g_Motion.AbsMove(Axis_Const::SPX, dTempLocRX);
			    g_Motion.AbsMove(Axis_Const::SPY, dTempLocRY);
            }
			nThreadIndex++;
		}
		break;
	case 5:
		if (bFront && g_Motion.IsPosDone(Axis_Const::SPX, dTempLocFX)
			&& g_Motion.IsPosDone(Axis_Const::SPY, dTempLocFY))
		{
			dTempLocFX = 0.0;
			dTempLocFY = 0.0;
			nThreadIndex++;
		}
        if (!bFront && g_Motion.IsPosDone(Axis_Const::SPX, dTempLocRX)
			&& g_Motion.IsPosDone(Axis_Const::SPY, dTempLocRY))
		{
			dTempLocRX = 0.0;
			dTempLocRY = 0.0;
			nThreadIndex++;
		}
		break;
	case 6:
	case nStartWork:nThreadIndex = 6;
		if (m_bIsSprayerLock)
		{
			g_Motion.SetDO(DO::FluxTankFluxIn, false);
			g_Motion.SetDO(DO::FluxTankVacuumIn, false);
			g_Motion.SetDO(DO::FluxTankVacOn, false);
			g_Motion.SetDO(DO::CleanerWaterOn, false);
			tm1MS.timeStart(10);
            m_bIsSprayerAlarm = false;
			nThreadIndex++;
		}
		break;
	case 7:
		if (tm1MS.timeUp())
		{
            //At ReadyPos turn On
			//g_Motion.SetDO(DO::FluxTankAirOn, true);
            //g_Motion.SetDO(DO::SprayerFluxOn, true);
			//g_Motion.SetDO(DO::SprayerAirOn, true);
			//g_Motion.SetDO(DO::SprayerPistonOn, false);
			//g_Motion.SetDO(DO::SprayerVacOn, true);
			tm1MS.timeStart(5000);
			nThreadIndex++;
		}
		break;
	case 8:
		//if(g_Motion.GetAI(0)>0 && g_Motion.GetAI(0)<4095)       //temp pressure value          //debug
		if (true)
		{
			tm1MS.timeStart(10);
			nThreadIndex++;
		}
		else if (tm1MS.timeUp())
		{
			g_IniFile.m_nErrorCode = 602;
			if (bFront)
			{
				m_bStartSBTSprayF = false;
				m_bSBTSprayDoneF = false;
			}
			else
			{
				m_bStartSBTSprayR = false;
				m_bSBTSprayDoneR = false;
			}
		}
		break;
	case 9:
		if (tm1MS.timeUp())
		{
			tm1MS.timeStart(10);                      //delay Start
			nThreadIndex++;
		}
		break;
	case 10:
		if (tm1MS.timeUp())
		{
			g_Motion.AbsMove(Axis_Const::SPZ, g_IniFile.m_dSprayPosZ);
			nMoveIndex = 0;
			nThreadIndex++;
		}
		break;
	case 11:
		if (g_Motion.IsPosDone(Axis_Const::SPZ, g_IniFile.m_dSprayPosZ))
		{
            //Start and On
            g_Motion.SetDO(DO::FluxTankAirOn, true);
            g_Motion.SetDO(DO::SprayerFluxOn, true);
			g_Motion.SetDO(DO::SprayerAirOn, true);
            g_Motion.SetDO(DO::SprayerPistonOn, true);

			tm1MS.timeStart(g_IniFile.m_dSpraryDelayTimeB * 1000);
			nThreadIndex++;
		}
		break;
	case 12:
	case nNextMove:nThreadIndex = 12;
		if (tm1MS.timeUp())
		{
			//Set Spray Speed first
			if ((nMoveIndex % 2) == 0)
            {
                dNextPos = g_Motion.GetFeedbackPos(Axis_Const::SPX) + g_IniFile.m_dSprayDistance;
                if (CheckRelMoveAlarm(Axis_Const::SPX, true, g_IniFile.m_dSprayDistance))
                    g_Motion.RelMove(Axis_Const::SPX, g_IniFile.m_dSprayDistance);
                else
                {
                    m_listLog.push_back("噴嘴下一個X位置: "+FormatFloat("0.000", dNextPos));
                    m_bIsSprayerAlarm = true;
                    nThreadIndex = nFinished;
                }
            }
			else
            {
                dNextPos = g_Motion.GetFeedbackPos(Axis_Const::SPX) - g_IniFile.m_dSprayDistance;
                if (CheckRelMoveAlarm(Axis_Const::SPX, false, g_IniFile.m_dSprayDistance))
                    g_Motion.RelMove(Axis_Const::SPX, -g_IniFile.m_dSprayDistance);
                else
                {
                    m_listLog.push_back("噴嘴下一個X位置: "+FormatFloat("0.000", dNextPos));
                    m_bIsSprayerAlarm = true;
                    nThreadIndex = nFinished;
                }
            }
			nThreadIndex++;
		}
		break;
	case 13:
        if((nMoveIndex+1) == g_IniFile.m_nSprayTimes)
        {
            if (fabs(g_Motion.GetFeedbackPos(Axis_Const::SPX) - dNextPos) < 1.0)
            {
                g_Motion.SetDO(DO::FluxTankAirOn, false);
                g_Motion.SetDO(DO::SprayerFluxOn, false);
                nThreadIndex++;
            }
        }
        else nThreadIndex++;
        break;
    case 14:
		if (g_Motion.IsMotionDone(Axis_Const::SPX)
			|| g_Motion.GetAxisStatus(Axis_Const::SPX, Axis_Const::PEL)
			|| g_Motion.GetAxisStatus(Axis_Const::SPX, Axis_Const::MEL))
		{
			if((nMoveIndex+1) != g_IniFile.m_nSprayTimes)
            {
                if (CheckRelMoveAlarm(Axis_Const::SPY, true, g_IniFile.m_dSprayPitch))
                    g_Motion.RelMove(Axis_Const::SPY, g_IniFile.m_dSprayPitch);
                else
                {
                    double dNextPos = g_Motion.GetFeedbackPos(Axis_Const::SPY) + g_IniFile.m_dSprayPitch;
                    m_listLog.push_back("噴嘴下一個Y位置: "+FormatFloat("0.000", dNextPos));
                    m_bIsSprayerAlarm = true;
                    nThreadIndex = nFinished;
                }
            }
			nThreadIndex++;
		}
		break;
	case 15:
		if ((g_Motion.IsMotionDone(Axis_Const::SPX) && g_Motion.IsMotionDone(Axis_Const::SPY)) ||
			g_Motion.GetAxisStatus(Axis_Const::SPX, Axis_Const::PEL) ||
			g_Motion.GetAxisStatus(Axis_Const::SPX, Axis_Const::MEL))
		{
			nMoveIndex++;
			if (nMoveIndex >= g_IniFile.m_nSprayTimes) nThreadIndex++;
			else nThreadIndex = nNextMove;
		}
		break;
	case 16:
    case nFinished:nThreadIndex = 16;
        tm1MS.timeStart(g_IniFile.m_dSpraryDelayTimeA * 1000);
		nThreadIndex++;
		break;
	case 17:
		if (tm1MS.timeUp())
		{
            g_Motion.SetDO(DO::SprayerPistonOn, false);
			g_Motion.SetDO(DO::SprayerAirOn, false);
            g_Motion.SetDO(DO::SprayerFluxOn, false);
			g_Motion.SetDO(DO::FluxTankAirOn, false);
			g_Motion.AbsSMove(Axis_Const::SPZ, g_IniFile.m_dSprayReadyPos);
			tm1MS.timeStart(g_IniFile.m_dSuccBackDelayTime * 1000);
			nThreadIndex++;
		}
		break;
	case 18:
		if (tm1MS.timeUp() && g_Motion.IsPosDone(Axis_Const::SPZ, g_IniFile.m_dSprayReadyPos))
		{
			nThreadIndex++;
		}
		break;
	default:
        if (m_bIsSprayerAlarm)
        {
            g_IniFile.m_nErrorCode = 504;
            m_bIsSprayerLock = false;
        }
		if (bFront)
		{
			m_bStartSBTSprayF = false;
			m_bSBTSprayDoneF = true;
		}
		else
		{
			m_bStartSBTSprayR = false;
			m_bSBTSprayDoneR = true;
		}
        //m_bIsSprayerLock = false;                        // not off by self, off by doSprayerLane
		nThreadIndex = 0;
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall CMainThread::doCleanSpray(int &nThreadIndex, bool bWater)
{
	static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

	static int nMoveIndexX = 0;
	static int nMoveIndexY = 0;
    static int nFullMoveIndex = 0;

	const int nTagNextPos = 1000;
	const int nTagNextTimes = 2000;
    const int nTagFinished = 3000;

	switch (nThreadIndex)
	{
	case 0:
		if (m_bIsSprayerLock)
		{
            if (bWater) g_Motion.SetAO(1, g_IniFile.m_dSprayerCleanWaterPressure);
            else g_Motion.SetAO(1, g_IniFile.m_dSprayerCleanAirPressure);
			g_Motion.AbsMove(Axis_Const::SPZ, 0.0);
			nThreadIndex++;
		}
		break;
	case 1:
		if (g_Motion.IsPosDone(Axis_Const::SPZ, 0.0))
		{
            g_Motion.SetDO(DO::FrontLaneSprayMotor, true);
            g_Motion.SetDO(DO::RearLaneSprayMotor, true);
			g_Motion.SetDO(DO::SprayerFluxOn, false);
			g_Motion.SetDO(DO::SprayerAirOn, false);
			g_Motion.SetDO(DO::CleanerWaterOn, false);
			g_Motion.SetDO(DO::CleanerWaterAirSwitch, false);
			nMoveIndexX = 0;
			nMoveIndexY = 0;
            nFullMoveIndex = 0;
            m_bIsSprayerAlarm = false;
            nThreadIndex++;
		}
		break;
	case 2:
	case nTagNextPos:nThreadIndex = 2;
		g_Motion.AbsMove(Axis_Const::SPX, g_IniFile.m_dCleanSprayPosX[nMoveIndexY]);
		g_Motion.AbsMove(Axis_Const::SPY, g_IniFile.m_dCleanSprayPosY[nMoveIndexY]);
		nThreadIndex++;
		break;
	case 3:
		if (g_Motion.IsPosDone(Axis_Const::SPX, g_IniFile.m_dCleanSprayPosX[nMoveIndexY])
            && g_Motion.IsPosDone(Axis_Const::SPY, g_IniFile.m_dCleanSprayPosY[nMoveIndexY]))
		{	
            g_Motion.AbsMove(Axis_Const::SPZ, g_IniFile.m_dCleanSprayPosZ);
            nThreadIndex++;
		}
		break;
    case 4:
        if (g_Motion.IsPosDone(Axis_Const::SPZ, g_IniFile.m_dCleanSprayPosZ))
        {
			if (bWater)
			{
				g_Motion.SetDO(DO::CleanerWaterOn, true);
				g_Motion.SetDO(DO::CleanerWaterAirSwitch, true);
			}
			else
			{
				g_Motion.SetDO(DO::CleanerWaterOn, true);
				g_Motion.SetDO(DO::CleanerWaterAirSwitch, false);
			}
			nThreadIndex++;
        }
        break;
	case 5:
	case nTagNextTimes:nThreadIndex = 5;
        if (CheckRelMoveAlarm(Axis_Const::SPX, true, g_IniFile.m_dCleanSprayDistance))
        {
		    g_Motion.RelMove(Axis_Const::SPX, g_IniFile.m_dCleanSprayDistance);
            nThreadIndex++;
        }
        else
        {
            double dNextPos = g_Motion.GetFeedbackPos(Axis_Const::SPX) + g_IniFile.m_dSprayDistance;
            m_listLog.push_back("噴嘴下一個X位置: "+FormatFloat("0.00", dNextPos));
            m_bIsSprayerAlarm = true;
            nThreadIndex = nTagFinished;
        }
		break;
	case 6:
		if (g_Motion.IsMotionDone(Axis_Const::SPX))
		{
			g_Motion.RelMove(Axis_Const::SPX, -g_IniFile.m_dCleanSprayDistance);
			nThreadIndex++;
		}
		break;
	case 7:
		if (g_Motion.IsMotionDone(Axis_Const::SPX))
		{
			if (nMoveIndexX + 1 < g_IniFile.m_nCleanSprayTimes)
            {
                nMoveIndexX++;
                nThreadIndex = nTagNextTimes;
            }
			else if (nMoveIndexY + 1 < 4)
            {
                nMoveIndexY++;
                nMoveIndexX = 0;
                nThreadIndex = nTagNextPos;
            }
            else if (nFullMoveIndex + 1 < g_IniFile.m_nFullCleanSprayTimes)
            {
                nFullMoveIndex++;
                nMoveIndexX = 0;
                nMoveIndexY = 0;
                nThreadIndex = nTagNextPos;
            }
			else
			{
				g_Motion.SetDO(DO::CleanerWaterAirSwitch, false);
				tm1MS.timeStart(500);
				nThreadIndex++;
			}
		}
        break;
    case 8:
    case nTagFinished:nThreadIndex = 8;
		if (tm1MS.timeUp())
		{
			g_Motion.SetDO(DO::CleanerWaterOn, false);
			g_Motion.AbsMove(Axis_Const::SPZ, 0.0);
			nThreadIndex++;
		}
		break;
    case 9:
        if (g_Motion.IsPosDone(Axis_Const::SPZ, 0.0))
        {
            g_Motion.SetDO(DO::FrontLaneSprayMotor, false);
            g_Motion.SetDO(DO::RearLaneSprayMotor, false);
            nThreadIndex++;
        }
        break;
	default:
        if (m_bIsSprayerAlarm) g_IniFile.m_nErrorCode = 504;
        g_Motion.SetAO(1, g_IniFile.m_dSprayerAirPressure);
		if (bWater) m_bStartCleanSpray = false;
        else m_bStartCleanSprayAir = false;
		m_bCleanSprayDone = true;
        m_bIsSprayerLock = false;                        //off by self, in AutoCleanLane
		nThreadIndex = 0;
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall CMainThread::doScaleSpray(int &nThreadIndex, bool bDredge)
{
	static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);
	static C_GetTime tm2MS(EX_SCALE::TIME_1MS, false);

	static int nTimesIndex = 0;

	const int nTagStartWork = 1000;
	const int nTagNextTimes = 2000;
    const int nTagFinished = 3000;

	switch (nThreadIndex)
	{
	case 0:
		if (!bDredge && !g_Motion.GetDI(DI::FluxBoxLevel))
		{
			g_IniFile.m_nErrorCode = 600;
            m_bStartFluxScaleSpray = false;
            m_bScaleSprayDone = false;
            nThreadIndex = 0;
		}
		//detect Tank Level here
		if (m_bIsSprayerLock && !g_Motion.GetDI(DI::FluxTankLevelDown))
		{
			m_listLog.push_back("警告! 高壓Flux桶不足 系統啟動自動補Fulx");
			m_bStartFillFlux = true;
			CMainThread::nThreadIndex[18] = 0;
			tm1MS.timeStart(1200000);
			nThreadIndex++;
		}
		else nThreadIndex = nTagStartWork;
		break;
	case 1:
		if (m_bStartFillFlux == false && g_Motion.GetDI(DI::FluxTankLevelDown))
		{
			nThreadIndex++;
		}
		else if (m_bStartFillFlux == false && !g_Motion.GetDI(DI::FluxTankLevelDown))
		{
			nThreadIndex = 0;
		}
		else if (tm1MS.timeUp())
		{
			m_listLog.push_back("嚴重警告! 自動補Fulx超過20分鐘, 系統停機. 請確認底下Flux存量");
			g_IniFile.m_nErrorCode = 51;
			if (!bDredge) m_bStartFluxScaleSpray = false;
			else m_bStartDredgeScaleSpray = false;
			m_bScaleSprayDone = false;

			m_bStartFillFlux = false;
			nThreadIndex = 0;
		}
		break;
	case 2:
	case nTagStartWork:nThreadIndex = 2;
		if (m_bIsSprayerLock)
		{
            if (!g_Motion.GetDI(DI::FluxBoxLevel)) m_listLog.push_back("警告! 底下Flux桶量不足");
			g_Motion.AbsMove(Axis_Const::SPZ, 0.0);
			m_listScaleWeight.clear();
            m_bIsSprayerWeightAlarm = false;
            g_Motion.SetDO(DO::CleanerWaterOn, false);
			nThreadIndex++;
		}
		break;
	case 3:
		if (g_Motion.IsPosDone(Axis_Const::SPZ, 0.0))
		{
            //Close All
			g_Motion.SetDO(DO::SprayerFluxOn, false);
			g_Motion.SetDO(DO::SprayerAirOn, false);
			g_Motion.SetDO(DO::CleanerWaterOn, false);
			g_Motion.SetDO(DO::FluxTankAirOn, false);

			g_Motion.AbsMove(Axis_Const::SPX, g_IniFile.m_dScaleSprayPosX[bDredge]);
			g_Motion.AbsMove(Axis_Const::SPY, g_IniFile.m_dScaleSprayPosY[bDredge]);
			nThreadIndex++;
		}
		break;
	case 4:
		if (g_Motion.IsPosDone(Axis_Const::SPX, g_IniFile.m_dScaleSprayPosX[bDredge])
             && g_Motion.IsPosDone(Axis_Const::SPY, g_IniFile.m_dScaleSprayPosY[bDredge]))
		{
			g_Motion.AbsMove(Axis_Const::SPZ, g_IniFile.m_dScaleSprayPosZ[bDredge]);
			nThreadIndex++;
			nTimesIndex = 0;
		}
		break;
	case 5:
	case nTagNextTimes:nThreadIndex = 5;
		if (g_Motion.IsPosDone(Axis_Const::SPZ, g_IniFile.m_dScaleSprayPosZ[bDredge]))
		{
			//Reset Scale
			if (!bDredge) g_Scale.SetZero();
			tm1MS.timeStart(500);
			nThreadIndex++;
		}
		break;
	case 6:
		if (tm1MS.timeUp())
		{	//Reset OK
			nThreadIndex++;
		}
		break;
	case 7:
        /* //Not detect Level here. Just at Top.
		if (!g_Motion.GetDI(DI::FluxBoxLevel))
		{
			g_IniFile.m_nErrorCode = 600;
            if (!bDredge) m_bStartFluxScaleSpray = false;
			else m_bStartDredgeScaleSpray = false;
            m_bScaleSprayDone = false;
            nThreadIndex = 0;
		}
		if (!g_Motion.GetDI(DI::FluxTankLevelDown))
		{
			g_IniFile.m_nErrorCode = 601;
            if (!bDredge) m_bStartFluxScaleSpray = false;
			else m_bStartDredgeScaleSpray = false;
            m_bScaleSprayDone = false;
            nThreadIndex = 0;
		}
        */
		if (true)
		{
            if (!g_Motion.GetDI(DI::FluxBoxLevel)) m_listLog.push_back("警告! 底下Flux桶量不足");

			g_Motion.SetDO(DO::FluxTankFluxIn, false);
			g_Motion.SetDO(DO::FluxTankVacuumIn, false);
			g_Motion.SetDO(DO::FluxTankVacOn, false);

			if (!bDredge)
			{
				//Set AO Valve
				g_Motion.SetAO(0, g_IniFile.m_dFluxTankAirPressure);
				g_Motion.SetAO(1, g_IniFile.m_dSprayerAirPressure);
			}

			tm1MS.timeStart(100);
			nThreadIndex++;
		}
		break;
	case 8:
		if (tm1MS.timeUp())
		{
            //Start and On
			g_Motion.SetDO(DO::FluxTankAirOn, true);
			g_Motion.SetDO(DO::SprayerPistonOn, false);
            g_Motion.SetDO(DO::SprayerFluxOn, false);
			g_Motion.SetDO(DO::SprayerAirOn, false);
			tm1MS.timeStart(5000);
			nThreadIndex++;
		}
		break;
	case 9:
		//if (g_Motion.GetAI(0)>0 && g_Motion.GetAI(0)<4095)       //temp pressure value //need check full and empty Pressure RX
		if (true)
		{
			tm1MS.timeStart(500);
			nThreadIndex++;
		}
		else if (tm1MS.timeUp())
		{
			m_listScaleWeight.clear();
			g_IniFile.m_nErrorCode = 602;
			if (!bDredge) m_bStartFluxScaleSpray = false;
			else m_bStartDredgeScaleSpray = false;
			m_bScaleSprayDone = true;
			nThreadIndex = 0;
		}
		break;
	case 10:
		if (tm1MS.timeUp())
		{
			if (!bDredge)
			{
				g_Motion.SetDO(DO::SprayerFluxOn, true);
				g_Motion.SetDO(DO::SprayerAirOn, true);
                g_Motion.SetDO(DO::SprayerPistonOn, true);
			}
			else
			{
				g_Motion.SetDO(DO::SprayerFluxOn, true);
				g_Motion.SetDO(DO::SprayerAirOn, true);
                g_Motion.SetDO(DO::SprayerPistonOn, true);
			}
			tm1MS.timeStart(g_IniFile.m_dScaleSprayTime[bDredge]*1000);                      //delay Start
			nThreadIndex++;
		}
		break;
	case 11:
		if (tm1MS.timeUp())
		{
            //close All
            g_Motion.SetDO(DO::SprayerPistonOn, false);
			g_Motion.SetDO(DO::SprayerAirOn, false);
            g_Motion.SetDO(DO::SprayerFluxOn, false);

			tm2MS.timeStart(1000);
            tm1MS.timeStart(g_IniFile.m_dScaleSprayDelayTime*1000);
            nThreadIndex++;
		}
		break;
	case 12:
		if (tm2MS.timeUp() || tm1MS.timeUp())
		{
			//g_Motion.SetDO(DO::SprayerAirOn, false);
			//g_Motion.SetDO(DO::SprayerVacIn, false);
			//g_Motion.SetDO(DO::SprayerVacOn, false);
			nThreadIndex++;
		}
		break;
	case 13:
		if (tm1MS.timeUp())
		{
			if (!bDredge)
			{
				//Get Stable Weight
				double dWeight = g_Scale.GetWeight();
				m_listLog.push_back("重量=" + FormatFloat("0.000 g", dWeight));
				m_listScaleWeight.push_back(dWeight);
                if (dWeight >= g_IniFile.m_dWeightScaleAlarmUp || dWeight <= g_IniFile.m_dWeightScaleAlarmDown)
                {
                    m_bIsSprayerWeightAlarm = true;
                }
			}

			if (m_bIsSprayerWeightAlarm == true) nThreadIndex = nTagFinished;
			else if (nTimesIndex + 1 < g_IniFile.m_nScaleSprayTimes[bDredge]) { nTimesIndex++; nThreadIndex = nTagNextTimes; }
			else nThreadIndex++;
		}
		break;
	case 14:
    case nTagFinished: nThreadIndex = 14;
		if (!bDredge)
		{
			if (m_listScaleWeight.size() != 0)
			{
				double *maxValue = std::max_element(m_listScaleWeight.begin(), m_listScaleWeight.end());
				double *minValue = std::min_element(m_listScaleWeight.begin(), m_listScaleWeight.end());
				m_listLog.push_back("重量誤差= " + FormatFloat("0.0000 g", (*maxValue - *minValue)));
			}
			else { m_listLog.push_back("重量誤差 錯誤!!"); }
		}
		//g_Motion.SetDO(DO::SprayerVacOn, false);
		g_Motion.SetDO(DO::FluxTankAirOn, false);
		g_Motion.AbsMove(Axis_Const::SPZ, 0.0);
		nThreadIndex++;
		break;
	case 15:
		if (g_Motion.IsPosDone(Axis_Const::SPZ, 0.0))
		{
			nThreadIndex++;
		}
		break;
	default:
        if (m_bIsSprayerWeightAlarm == true)
        {
            g_IniFile.m_nErrorCode = 714;
            m_bIsSprayerLock = false;
        }
		if (!bDredge) m_bStartFluxScaleSpray = false;
		else
        {
            m_bStartDredgeScaleSpray = false;
            //Reset Scale
			g_Scale.SetZero();
        }
		m_bScaleSprayDone = true;
        //m_bIsSprayerLock = false;               // not off by self, off by doSprayerLane
		nThreadIndex = 0;
		break;
	}
}
//---------------------------------------------------------------------------


void __fastcall CMainThread::doUnLoadClamper(int &nThreadIndex)
{
	static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

	switch (nThreadIndex)
	{
	case 0:
		if (g_Motion.GetFeedbackPos(Axis_Const::LDY) > g_IniFile.m_dLDYUnLoadClamperAlarm) g_IniFile.m_nErrorCode = 416;
		else if (g_Motion.GetDI(DI::LoaderClamperUp)) g_IniFile.m_nErrorCode = 408;
		else
		{
			g_Motion.AbsMove(Axis_Const::LDY, 0.0);
			nThreadIndex++;
		}
		break;
	case 1:
		if (g_Motion.IsMotionDone(Axis_Const::LDY))
		{
			g_Motion.AbsMove(Axis_Const::LDZ, g_IniFile.m_dLoaderUnClampMgzPos[0]);
			nThreadIndex++;
		}
		break;
	case 2:
		if (g_Motion.IsMotionDone(Axis_Const::LDZ))
		{
			nThreadIndex++;
		}
		break;
	case 3:
		if (m_bConveyerMagazineOutReady)
		{
			if (g_Motion.GetDI(DI::LoaderOutMgzIn)) m_bConveyerMagazineOutReady = false;
			else
			{
				g_Motion.AbsMove(Axis_Const::LDY, g_IniFile.m_dLoaderUnClampMgzPos[1]);
				nThreadIndex++;
			}
		}
		break;
	case 4:
		if (g_Motion.IsMotionDone(Axis_Const::LDY))
		{
			g_Motion.SetDO(DO::LoaderClamper, true);            //un-Clamp sensor reversed
			tm1MS.timeStart(5000);
			nThreadIndex++;
		}
		break;
	case 5:
		if (g_Motion.GetDI(DI::LoaderClamperUp))
		{
			g_Motion.AbsMove(Axis_Const::LDZ, g_IniFile.m_dLoaderUnClampMgzPos[2]);
			nThreadIndex++;
		}
		else if (tm1MS.timeUp()) g_IniFile.m_nErrorCode = 405;
		break;
	case 6:
		if (g_Motion.IsMotionDone(Axis_Const::LDZ))
		{
			g_Motion.AbsMove(Axis_Const::LDY, 0.0);
			nThreadIndex++;
		}
		break;
	case 7:
		if (g_Motion.IsMotionDone(Axis_Const::LDY))
		{
			m_bConveyerMagazineOutReady = false;
			nThreadIndex++;
		}
		break;
	default:
		m_bStartUnLoadClamper = false;
		nThreadIndex = 0;
		break;
	}

    if (g_IniFile.m_nErrorCode > 0)
    {
        m_bStartUnLoadClamper = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall CMainThread::doReLoadClamper(int &nThreadIndex)
{
	static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

	switch (nThreadIndex)
	{
	case 0:
		if (!g_Motion.GetDI(DI::LoaderClamperUp))
        {
            g_IniFile.m_nErrorCode = 405;
            m_bStartReLoadClamper = false;
        }
		else
		{
			g_Motion.AbsMove(Axis_Const::LDY, 0.0);
			nThreadIndex++;
		}
		break;
	case 1:
		if (g_Motion.IsMotionDone(Axis_Const::LDY))
		{
			g_Motion.AbsMove(Axis_Const::LDZ, g_IniFile.m_dLoaderClampMgzPos[0]);
			nThreadIndex++;
		}
		break;
	case 2:
		if (m_bConveyerMagazineReady && g_Motion.IsMotionDone(Axis_Const::LDZ))
		{
			m_listLog.push_back("Start Clamp Magazin");
			g_Motion.AbsMove(Axis_Const::LDY, g_IniFile.m_dLoaderClampMgzPos[1]);
			nThreadIndex++;
		}
		break;
	case 3:
		if (g_Motion.IsMotionDone(Axis_Const::LDY))
		{
			g_Motion.AbsMove(Axis_Const::LDZ, g_IniFile.m_dLoaderClampMgzPos[2]);
			nThreadIndex++;
		}
		break;
	case 4:
		if (g_Motion.IsMotionDone(Axis_Const::LDZ))
		{
			g_Motion.SetDO(DO::LoaderClamper, false);        //Clamp
			tm1MS.timeStart(500);
			nThreadIndex++;
		}
		break;
	case 5:
		if (g_Motion.GetDI(DI::LoaderClamperDown))
		{
			m_bConveyerMagazineReady = false;
            m_bStartReLoadClamper = false;
			g_IniFile.m_nErrorCode = 406;
			nThreadIndex = 0;
		}
		else if (tm1MS.timeUp())
		{
			nThreadIndex++;
		}
		break;
	case 6:
		if (!g_Motion.GetDI(DI::LoaderClamperMgzExist))
        {
            g_IniFile.m_nErrorCode = 407;
            m_bStartReLoadClamper = false;
        }
		else
		{
			g_Motion.AbsMove(Axis_Const::LDZ, 0.0);
			nThreadIndex++;
		}
		break;
	case 7:
		if (g_Motion.IsMotionDone(Axis_Const::LDZ))
		{
            m_bConveyerMagazineReady = false;
			g_Motion.AbsMove(Axis_Const::LDY, g_IniFile.m_dMagazinePushPosY);
			nThreadIndex++;
		}
		break;
	case 8:
		if (g_Motion.IsMotionDone(Axis_Const::LDY))
		{
            if (!g_Motion.GetDI(DI::LeftLaneChangerIn))
			{
                if (!g_IniFile.m_bIsMagazineUpFirst)
				    g_Motion.AbsMove(Axis_Const::LDZ, g_IniFile.m_dMagazinePushPosZ);
                else
                    g_Motion.AbsMove(Axis_Const::LDZ, g_IniFile.m_dMagazinePushPosUpFirstZ);
				nThreadIndex++;
			}
			else
            {
                g_IniFile.m_nErrorCode = 302;
                m_bStartReLoadClamper = false;
            }
		}
		break;
    case 9:
		if (g_Motion.IsLastPosDone(Axis_Const::LDZ))
		{
			nThreadIndex++;
		}
		break;
	default:
		m_bStartReLoadClamper = false;
		nThreadIndex = 0;
		break;
	}

    if (g_IniFile.m_nErrorCode > 0)
    {
        m_bStartReLoadClamper = false;
    }
}
#pragma endregion






