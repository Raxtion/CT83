//---------------------------------------------------------------------------


#pragma hdrstop
#include <vcl>
#include "PCIM114GL.h"
//#include "PCI_M114GL.h"
#include "PCI_M114.h"
#include "MNet_m1a.h"
#include "MsgDev.h"
//#include "PM114GLErr.h"
#include "CMNet.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

PCIM114GL g_MNet;
//---------------------------------------------------------------------------

__fastcall PCIM114GL::PCIM114GL()
{
        m_byteDIPort=NULL;
        m_byteDOPort=NULL;

        m_bAutoMode=false;

        m_bInitOK=Initial(0);

        if(!m_bInitOK)
        {
                m_byteDIPort=new byte[12];
                m_byteDOPort=new byte[12];
        }

       
        m_dMMtoPLS[Axis_Const::LDY]=10000.0/10.0;
        m_dMMtoPLS[Axis_Const::LDZ]=10000.0/10.0;
        m_dMMtoPLS[Axis_Const::SPZ]=10000.0/5.0;
        m_dMMtoPLS[Axis_Const::MGZ]=10000.0/5.0;
        m_dMMtoPLS[Axis_Const::LLC]=10000.0/16.0;
        m_dMMtoPLS[Axis_Const::SPX]=10000.0/16.0;
        m_dMMtoPLS[Axis_Const::SPY]=10000.0/16.0;
        m_dMMtoPLS[Axis_Const::CDX]=10000.0/16.0;
        m_dMMtoPLS[Axis_Const::RLC]=10000.0/16.0;



        for(int nIndex=0;nIndex<AXIS_SIZE;nIndex++) m_dLastTargetPos[nIndex]=0.0;

        memset(m_byteDOPort,0,sizeof(byte)*m_vectDIOMap.size() * 2);

}
//---------------------------------------------------------------------------
__fastcall PCIM114GL::~PCIM114GL()
{
        delete m_byteDIPort;
        delete m_byteDOPort;
}
//---------------------------------------------------------------------------
void PASCAL ERR_Cbk(unsigned short RingNo, unsigned short SlaveIP, unsigned short Code)
{

//    Application->MessageBox("Error Connect!!", "Error", MB_OK);

//	static U32 cnt = 0;
//	TRACE("%5d. Error Callback of (Ring%d, Device%d, Code0x%02X)\n\n", ++cnt, RingNo, SlaveIP, Code);
}
//---------------------------------------------------------------------------
bool __fastcall PCIM114GL::Initial(unsigned short nCardNo)
{
         m_nExistCard = 0;
            m_nStartRingNo = 0;
            m_nCardNo = nCardNo;      //defaule 0

            short nStatus=0;

            nStatus = _m114_open(&m_nExistCard);
            if (nStatus != (int)ERR_NoError) return false;

            if (m_nExistCard == 0) return false;

            nStatus = _m114_initial(m_nCardNo);
            //----------------------------------------------------
            /*
            for (ushort AxisNo = 0; AxisNo < 4; AxisNo++)
            {
                nStatus = CPCI_M114GL.CS_m114_set_servo(m_nCardNo, AxisNo, 0);                
                
                CPCI_M114GL.CS_m114_set_pls_iptmode(0, AxisNo, 3, 0);
                CPCI_M114GL.CS_m114_set_pls_outmode(0, AxisNo, 4);
                CPCI_M114GL.CS_m114_set_feedback_src(0, AxisNo, 0);
                CPCI_M114GL.CS_m114_set_erc(0, AxisNo, 1, 0);
                CPCI_M114GL.CS_m114_set_sd(0, AxisNo, 0, 1, 0, 0);
                CPCI_M114GL.CS_m114_set_alm(0, AxisNo, 1, 0);
                CPCI_M114GL.CS_m114_set_ltc_logic(0, AxisNo, 0);
                
            }
            */

            /*
            nStatus = _m114_config_from_file(m_nCardNo, "C:\\AxisConfig.cfg");
            if (nStatus != (int)ERR_NoError) return false;
            */
             for(int nIndex=0;nIndex<4;nIndex++)
                _m114_set_home_config( m_nCardNo, nIndex, 11, 1,1, 0, 0 );

            //Motion Net initial           
            nStatus =_m114_open_mnet(m_nCardNo);
            nStatus = _m114_get_start_ring_num(m_nCardNo,&m_nStartRingNo);
            nStatus = _mnet_set_ring_config(m_nStartRingNo, 2);       //Baudrate 3 : 20MBps

            //watch dog event
           /*
            m_hEvent = CreateEvent(NULL, true, false, NULL);
            nStatus =_mnet_set_ring_quality_param(m_nStartRingNo, 50, 200);
            nStatus = _mnet_watchdog_link(m_nStartRingNo, SWD_Cbk_EIOE, ERR_Cbk);
            nStatus = _mnet_enable_soft_watchdog(m_nStartRingNo, &m_hEvent);
            */
            //bWatchDogTimeON = true;

            //
            nStatus = _mnet_reset_ring(m_nStartRingNo);

            unsigned long nATable[2]={0};
            nStatus = _mnet_get_ring_active_table(m_nStartRingNo,nATable);        ///Do Something
            m_nActiveTable = nATable[0] + (unsigned __int64)(nATable[1] << 32);
            nStatus = _mnet_start_ring(m_nStartRingNo);

            //Axis
            m_vectAxisMap.clear();
            m_vectDIOMap.clear();
             m_vectAIOMap.clear();
            AnsiString strMsg;

            for (unsigned short nIndex = 0; nIndex < 64; nIndex++)
            {

                if ((m_nActiveTable & (unsigned __int64)(0x01 << nIndex)) > 0)       //There's an active module
                {
                    nStatus = _mnet_get_slave_type(m_nStartRingNo, nIndex, &m_btSlaveType[nIndex]);
                    if (m_btSlaveType[nIndex] == 162)//0xa3)
                    {
                        m_vectAxisMap.push_back(nIndex);
                        nStatus = _mnet_m1a_initial(m_nStartRingNo, nIndex);

                       _mnet_m1a_recovery_from_EEPROM(m_nStartRingNo, nIndex );

                    }

                    if(m_btSlaveType[nIndex] ==178) //0xb2)       //DI16 DO16 module
                        m_vectDIOMap.push_back(nIndex);

                    if(m_btSlaveType[nIndex] ==224) //0xE0)      //Message Device
                    {
                        unsigned short msgtype;
                        _mnet_get_msg_slave_type(m_nStartRingNo, nIndex, &msgtype);
                        if (msgtype == 0x0122)//A122            //AI4 AO4 module
                        {
                                nStatus = _mnet_a122_initial(m_nStartRingNo, nIndex);
                                if (nStatus==0) m_vectAIOMap.push_back(nIndex);
                        }
                    }
                }
            }

            if (m_vectAxisMap.size() == 0 || m_vectDIOMap.size() == 0) return false;

            //
            //SetDefaultSpeed 

            for(unsigned short nIndex=0;nIndex<4;nIndex++)
            {
                m_dStartVal[nIndex] = 1000;
                m_dMaxVal[nIndex] = 10000;
                m_dTAcc[nIndex] = 0.1;
                m_dTDec[nIndex] = 0.1;
                m_dSVAcc[nIndex] = 1000; 
            }

            for(unsigned int nIndex=0;nIndex<m_vectAxisMap.size();nIndex++)
            {
                _mnet_m1a_set_tmove_speed(m_nStartRingNo,m_vectAxisMap[nIndex],1000,10000,0.1,0.1);
            }

            //_mnet_m1a_set_pls_iptmode(m_nStartRingNo, m_vectAxisMap[2], 2, 0);
            //_mnet_m1a_set_pls_outmode(m_nStartRingNo, m_vectAxisMap[2], 2 );

            //DI DO
            m_byteDIPort = new unsigned char[m_vectDIOMap.size() * 2];
            m_byteDOPort = new unsigned char[m_vectDIOMap.size() * 2];
                        
            return true;
}
//---------------------------------------------------------------------------
void PCIM114GL::ServoOn(unsigned short nAxis, unsigned short bOn)
{
        if(!m_bInitOK) return ;
        if (nAxis < 4) _m114_set_servo(m_nCardNo, nAxis, bOn);
            else _mnet_m1a_set_svon(m_nStartRingNo, m_vectAxisMap[nAxis - 4], bOn);
}
//---------------------------------------------------------------------------

void PCIM114GL::SetMoveSpeed(unsigned short nAxis, double dMaxVal, double dTAcc,double dTDec)
{
        if(!m_bInitOK) return;
        
        if(nAxis<4)
            {
                m_dStartVal[nAxis] = (dMaxVal/2.0)*m_dMMtoPLS[nAxis];
                m_dMaxVal[nAxis] = dMaxVal*m_dMMtoPLS[nAxis];
                m_dTAcc[nAxis] = dTAcc;
                m_dTDec[nAxis] = dTDec;
                //m_dSVAcc[nAxis] = 1000; 
            }
            else _mnet_m1a_set_tmove_speed(m_nStartRingNo,m_vectAxisMap[nAxis-4],(dMaxVal/2.0)*m_dMMtoPLS[nAxis],dMaxVal*m_dMMtoPLS[nAxis],dTAcc,dTAcc);

}
//---------------------------------------------------------------------------

void PCIM114GL::AxisHome(unsigned short nAxis, bool bDir)
{
        if(!m_bInitOK) return ;

        if (nAxis < 4)
        {
            _m114_home_move(m_nCardNo, nAxis,bDir, m_dStartVal[nAxis], m_dMaxVal[nAxis], m_dTAcc[nAxis]);

        }
        else
        {
            if(bDir) _mnet_m1a_start_home_move(m_nStartRingNo, m_vectAxisMap[nAxis - 4],1);
            else _mnet_m1a_start_home_move(m_nStartRingNo, m_vectAxisMap[nAxis - 4],0);
        }


}
//---------------------------------------------------------------------------

void PCIM114GL::RelMove(unsigned short nAxis, double dDis)
{
        if(!m_bInitOK) return ;
        if(m_bAutoMode)  m_dLastTargetPos[nAxis]=GetFeedbackPos(nAxis)+dDis;
        
        if (nAxis < 4) _m114_start_tr_move(m_nCardNo, nAxis, dDis*m_dMMtoPLS[nAxis],m_dStartVal[nAxis], m_dMaxVal[nAxis], m_dTAcc[nAxis], m_dTDec[nAxis]);
            else _mnet_m1a_start_r_move(m_nStartRingNo, m_vectAxisMap[nAxis - 4], dDis*m_dMMtoPLS[nAxis]);
}
//---------------------------------------------------------------------------

void PCIM114GL::AbsMove(unsigned short nAxis, double dDis)
{
        if(!m_bInitOK) return ;
        if(m_bAutoMode) m_dLastTargetPos[nAxis]=dDis;
        if (nAxis < 4) _m114_start_ta_move(m_nCardNo, nAxis, dDis*m_dMMtoPLS[nAxis],m_dStartVal[nAxis], m_dMaxVal[nAxis], m_dTAcc[nAxis], m_dTDec[nAxis]);
            else _mnet_m1a_start_a_move(m_nStartRingNo, m_vectAxisMap[nAxis - 4], dDis*m_dMMtoPLS[nAxis]);
}
//---------------------------------------------------------------------------

void PCIM114GL::AbsSMove(unsigned short nAxis, double dDis)
{
        if(!m_bInitOK) return ;
        double dSVel=(m_dMaxVal[nAxis]-m_dStartVal[nAxis])/2;
        
        if (nAxis < 4) _m114_start_sa_move(m_nCardNo, nAxis, dDis*m_dMMtoPLS[nAxis],m_dStartVal[nAxis], m_dMaxVal[nAxis], m_dTAcc[nAxis], m_dTDec[nAxis]);
            else _mnet_m1a_start_a_move(m_nStartRingNo, m_vectAxisMap[nAxis - 4], dDis*m_dMMtoPLS[nAxis]);
}
//---------------------------------------------------------------------------
bool PCIM114GL::IsMotionDone(unsigned short nAxis)
{
        short nStatus;
            unsigned short nStatusNet=0;

            if(!m_bInitOK) return false;

            if (nAxis < 4)
            {
                nStatus = _m114_motion_done(m_nCardNo, nAxis);
                if (nStatus == 0) return true;
                else return false;
            }
            else
            {
                _mnet_m1a_motion_done(m_nStartRingNo, m_vectAxisMap[nAxis - 4],&nStatusNet);
                if (nStatusNet == 0) return true;
                else return false;
            }
}
//---------------------------------------------------------------------------
bool PCIM114GL::IsPosDone(int nAxis,double dPos)
{
        double dP=GetFeedbackPos(nAxis);
        if(dP>dPos-0.1 && dP<dPos+0.1) return true;
        else return false;
}
//---------------------------------------------------------------------------
bool PCIM114GL::IsLastPosDone(int nAxis)
{
        double dPos=m_dLastTargetPos[nAxis];

        double dP=GetFeedbackPos(nAxis);
        if(dP>dPos-0.1 && dP<dPos+0.1) return true;
        else if(GetAxisStatus(nAxis,Axis_Const::INP)) AbsMove(nAxis,dPos);
        else return false;

        return false;
}
//---------------------------------------------------------------------------

double PCIM114GL::GetFeedbackPos(unsigned short nAxis)
{
            long nPulsePos=0;
            long nPos=0;

            if(!m_bInitOK) return 0x00;

            int nX=m_vectAxisMap.size();

            if (nAxis < 4) { _m114_get_position(m_nCardNo, nAxis,&nPulsePos); return nPulsePos/m_dMMtoPLS[nAxis]; }
            else {
            _mnet_m1a_get_position(m_nStartRingNo, m_vectAxisMap[nAxis - 4],&nPos);
            return nPos/m_dMMtoPLS[nAxis];
            }

}
//---------------------------------------------------------------------------

void PCIM114GL::SetFeedbackPos(unsigned short nAxis,double dPos)
{

            if(!m_bInitOK) return;

            if (nAxis < 4) { _m114_set_position(m_nCardNo, nAxis,dPos*m_dMMtoPLS[nAxis]);  }
            else { _mnet_m1a_set_position(m_nStartRingNo, m_vectAxisMap[nAxis - 4],(long)(dPos*m_dMMtoPLS[nAxis])); }

}
//---------------------------------------------------------------------------
double PCIM114GL::GetCommandPos(unsigned short nAxis)
{

    long nPos = 0;
    if(!m_bInitOK) return 0x00;
    if (nAxis < 4) _m114_get_command(m_nCardNo, nAxis,&nPos);
    else _mnet_m1a_get_command(m_nStartRingNo, m_vectAxisMap[nAxis - 4],&nPos);

    return nPos/m_dMMtoPLS[nAxis];
}
//---------------------------------------------------------------------------
void PCIM114GL::SetCommandPos(unsigned short nAxis,double dPos)
{
    if(!m_bInitOK) return;
    if (nAxis < 4) _m114_set_command(m_nCardNo, nAxis,dPos*m_dMMtoPLS[nAxis]);
    else _mnet_m1a_set_command(m_nStartRingNo, m_vectAxisMap[nAxis - 4],dPos*m_dMMtoPLS[nAxis]);

}
//---------------------------------------------------------------------------
void PCIM114GL::StartJog(unsigned short nAxis,bool bDir)
{
        if(!m_bInitOK) return;
    if (nAxis < 4)
    {
        _m114_tv_move(m_nCardNo, nAxis, bDir,m_dStartVal[nAxis], m_dMaxVal[nAxis], m_dTAcc[nAxis]);

    }
    else
    {
       if(bDir) _mnet_m1a_v_move(m_nStartRingNo, m_vectAxisMap[nAxis - 4], 1);
       else _mnet_m1a_v_move(m_nStartRingNo, m_vectAxisMap[nAxis - 4], 0);
    }
}
//---------------------------------------------------------------------------
void PCIM114GL::StopMove(unsigned short nAxis)
{
        if(!m_bInitOK) return;
    if (nAxis < 4) _m114_emg_stop(m_nCardNo, nAxis);
    else _mnet_m1a_emg_stop(m_nStartRingNo, m_vectAxisMap[nAxis - 4]);
}
//---------------------------------------------------------------------------
        //DIO
void PCIM114GL::SetDO(int nBitNo, bool bOnOff)     //for DI16 DO16
{
     int nIP= nBitNo / 16;
     int nPort = nBitNo / 8;
     int nPortNew=nPort % 2;
    int nBit= nBitNo % 8;

    if(!m_bInitOK) return ;

    int BYTE = m_byteDOPort[nPort];

    if (bOnOff) BYTE = BYTE | (0x01 << nBit);
    else BYTE = BYTE & ~(0x01 << nBit);

    m_byteDOPort[nPort] = (byte)BYTE;
    int nID=m_vectDIOMap[nIP];

    _mnet_io_output(m_nStartRingNo, m_vectDIOMap[nIP],(byte)nPortNew+2 ,m_byteDOPort[nPort]);

}
//---------------------------------------------------------------------------
void PCIM114GL::SetDOPort(int nPort, byte nValue)     //for DI16 DO16
{
     if(!m_bInitOK) return;
     
     int nPortNew=nPort % 2;

    m_byteDOPort[nPort] = nValue;

    _mnet_io_output(m_nStartRingNo, m_vectDIOMap[nPort],(byte)nPortNew+2 ,m_byteDOPort[nPort]);

}
//---------------------------------------------------------------------------

bool PCIM114GL::GetDO(int nBitNo)
{

  int nPort = nBitNo / 8;
  int nBit= nBitNo % 8;

  if(!m_bInitOK) return false;

  int BYTE = m_byteDOPort[nPort];

  BYTE = BYTE & (0x01 << nBit);

  return (BYTE>0) ? true : false;
}

//---------------------------------------------------------------------------
bool PCIM114GL::GetDI(int nBitNo)
{
    int nIP = nBitNo / 16;
    int nPort = nBitNo / 8;
    int nPortNew=nPort % 2;
    int nBit = nBitNo % 8;

    if(!m_bInitOK) return false;

    short nResult=_mnet_io_input(m_nStartRingNo, m_vectDIOMap[nIP],(byte) nPortNew);
    if (nResult < 0) return false;

    m_byteDIPort[nPort] = (byte)nResult;
    int BYTE = m_byteDIPort[nPort];

    BYTE = BYTE & (0x01 << nBit);

    return (BYTE > 0) ? true : false;


}
 //---------------------------------------------------------------------------
bool PCIM114GL::GetAxisStatus(unsigned short nAxis, Axis_Const::Axis_Status nStatus)
{
    unsigned short nResult=0;
    unsigned long nRes=0;

    if(!m_bInitOK) return false;

    int R;
    if (nAxis < 4)
    {
        _m114_get_io_status(m_nCardNo, nAxis, &nResult);
        R = nResult;
    }
    else
    {
        _mnet_m1a_get_io_status(m_nStartRingNo, m_vectAxisMap[nAxis - 4], &nRes);
        R = (int)nRes;
    }

    R = R & (0x01 << (int)nStatus);

    return R > 0 ? true : false;
}
 //---------------------------------------------------------------------------
byte PCIM114GL::GetDIPort(int nPort)
{
        if(!m_bInitOK) return 0x00;

    int nIP=nPort/2;
    int nPortNew=nPort % 2;


    short nResult=_mnet_io_input(m_nStartRingNo, m_vectDIOMap[nIP],(byte) nPortNew);
    if (nResult < 0) return false;

    m_byteDIPort[nPort] = (byte)nResult;

   return m_byteDIPort[nPort];
}
 //---------------------------------------------------------------------------
 byte PCIM114GL::GetDOPort(int nPort)
{
     if(!m_bInitOK) return 0x00;
    return m_byteDOPort[nPort];
}
 //---------------------------------------------------------------------------
void PCIM114GL::ProcessMessage()
{
        MSG msg;
  PeekMessage( &msg, NULL, 0, 0, PM_REMOVE );
  DispatchMessage( &msg );
  TranslateMessage( &msg ); 
  Sleep( 0 );
}
 //---------------------------------------------------------------------------
bool PCIM114GL::WaitMotionDone(int nAxis, DWORD nWaitTime, bool bProcessMessage)
{
        if(!m_bInitOK) return false;

	DWORD dwStartTime=GetTickCount();
	while(1)
	{
		if(IsMotionDone(nAxis)) break;
		if(GetTickCount()-dwStartTime>nWaitTime) return false;
                /*
                if(!GetDI(DI::SafetyDoor) )
                {
                        StopMove(nAxis);
                        return false;
                }
                */
                if(GetAxisStatus(nAxis,Axis_Const::ALM)) return false; 

		if(bProcessMessage) ProcessMessage();
                else ::Sleep(10);
	}
        
	return true;
}
//---------------------------------------------------------------------------
bool PCIM114GL::IsCommError(int nRingNo)
{
       unsigned short nStatus=0;
      // _mnet_get_ring_status(nRingNo,&nStatus);
       nStatus=_mnet_get_com_status(nRingNo);
       if(nStatus!=1) return true;
       else return false;
}
//---------------------------------------------------------------------------
void __fastcall PCIM114GL::SetAO(int nChannel,short nValue)
{
        int nIP=nChannel / 4;
        int nCH=nChannel % 4;
        try
        {
            _mnet_a122_set_output_channel_value(m_nStartRingNo, m_vectAIOMap[nIP], nCH, nValue);
        }
        catch (...) {}
}

//---------------------------------------------------------------------------
int __fastcall PCIM114GL::GetAI(int nChannel)
{
        short nValue=0;
        int nIP=nChannel / 4;
        int nCH=nChannel % 4;
        try
        {
            _mnet_a122_get_input_channel_value(m_nStartRingNo, m_vectAIOMap[nIP], nCH, &nValue);
        }
        catch (...) {}
        return nValue;
}
 
