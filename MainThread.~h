//---------------------------------------------------------------------------

#ifndef MainThreadH
#define MainThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <list>
#include <vector>
#include "C_GetTime.h"
#define MAX_PROCESS 20

#define InitialMachine_Index 0
#define DoTrayLoader_Index 1
#define DoStage_Index 2
#define DoHSLifter_Index 3
#define DoHSPicker_Index 4

#define g_Motion g_MNet
#define ReadDIBit GetDI
#define g_DIO g_MNet
#define ReadDOBit GetDO

//---------------------------------------------------------------------------
class CMainThread : public TThread
{
private:
        bool m_bSoftStart;
        bool m_bSoftStop;
        bool m_bSoftReset;
        bool m_bSoftInit;

protected:
        void __fastcall Execute();
public:
        C_GetTime tm1MSFluxLifeTime;

        std::list<AnsiString> m_listLog;
        std::list<AnsiString> m_listTX;     //for all serial command
        std::list<AnsiString> m_listCCDRX;
		std::list<AnsiString> m_listReaderTX;
		std::list<AnsiString> m_list1DReaderRX;
		std::list<AnsiString> m_list2DReaderRX;
		std::list<AnsiString> m_listPickLane;
		std::vector<double> m_listScaleWeight;

        int nThreadIndex[MAX_PROCESS];		//0:Inti 19:PreAuto

        bool m_bIsHomeDone;
        bool m_bIsAutoMode;
        bool m_bIsStartProcessbyDIO;            //Record for Strat Process by DI::StartBtn
        bool m_bIsStartProcessbyCIM;            //Record for Strat Process by CIM in CMainThread::Execute() not by DI::StartBtn
        bool m_bIsStopProcessbyCIM;             //Record for Stop Process by CIM in CMainThread::Execute() not by DI::StopBtn
        bool m_bNeedHome;
        bool m_bIsSprayerAlarm;
        bool m_bIsSprayerWeightAlarm;
        bool m_bIsStopLoader;
        bool m_bIsNeedPreMoveSprayer;
        bool m_bIsFluxLifetimeTimeUp;

        //Thread HandShake
        bool m_bConveyerMagazineReady;
        bool m_bConveyerMagazineOutReady;
        bool m_bLoaderClamperReady;

        bool m_bLeftLaneChangerReady;
        bool n_bLaneSprayReady[2];              //1: Front 0:Reard

		bool m_bStartFillFlux;
        bool m_bStartSBTSprayF;
		bool m_bStartSBTSprayR;
        bool m_bSBTSprayDoneF;
        bool m_bSBTSprayDoneR;
        bool m_bStartCleanSpray;
        bool m_bStartCleanSprayAir;         
        bool m_bCleanSprayDone;
		bool m_bStartFluxScaleSpray;
        bool m_bStartDredgeScaleSpray;
        bool m_bScaleSprayDone;
        
        bool m_bStartReLoadClamper;
        bool m_bStartUnLoadClamper;
		bool m_bStartInitLoader;

        //Lock
        bool m_bIsLeftLaneChangerLock;
        bool m_bIsSprayerLock;

        //IO Again
        bool m_bStartAgain;
        bool m_bStopAgain;
        bool m_bResetAgain;
        bool m_bInitalAgain;

        //Counter;
        int m_nStripCount;
        int m_nSprayTimes;

        __fastcall CMainThread(bool CreateSuspended);
        void __fastcall SetWorkSpeed();
        void __fastcall SetManualSpeed();

        //ShowNow
        bool m_arraybShape[25];

        //Manual Mode

        //Homing
        bool __fastcall InitialMachine(int &nThreadIndex);

        //Auto Mode
        //void __fastcall doLoadRail(int &nThreadIndex);
        void __fastcall doLoadConveyerUp(int &nThreadIndex);
        void __fastcall doLoadConveyerDown(int &nThreadIndex);
        void __fastcall doLoadClamper(int &nThreadIndex);
        void __fastcall doLeftLaneChanger(int &nThreadIndex);
        void __fastcall doSprayerLane(int &nThreadIndex,bool bFront);
        void __fastcall doCCDBufferLane(int &nThreadIndex);

        //Either Auto or Manual Mode
        void __fastcall doFillFlux(int &nThreadIndex);					//m_bIsSprayerLock
        void __fastcall doSBTSpray(int &nThreadIndex, bool bFront);		//m_bIsSprayerLock
        void __fastcall doCleanSpray(int &nThreadIndex, bool bWater);   //m_bIsSprayerLock
        void __fastcall doScaleSpray(int &nThreadIndex, bool bWater);	//m_bIsSprayerLock

		//Manual Mode
		void __fastcall doUnLoadClamper(int &nThreadIndex);
		void __fastcall doReLoadClamper(int &nThreadIndex);
		bool __fastcall InitialLoader(int &nThreadIndex);

        //PreAuto
        bool __fastcall doPreAuto(int &nThreadIndex);

        void __fastcall CheckAlarm();
        bool __fastcall CheckRelMoveAlarm(unsigned short nAxis, bool bIsForward, double dMoveDistance);
		bool __fastcall CheckXYInSprayRange();
        bool __fastcall CheckXYZAtSprayReadyPos(bool bFront);
        void __fastcall ThreadTrace();

        //Remote Command
        void __fastcall SoftStart(){m_bSoftStart=true;}
        void __fastcall SoftStop(){m_bSoftStop=true;}
        void __fastcall SoftReset(){m_bSoftReset=true;}
        void __fastcall SoftInit(){m_bSoftInit=true;}

};
//---------------------------------------------------------------------------
#endif





