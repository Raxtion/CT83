//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fmMotorCheck.h"
#include "PCIM114GL.h"
#include "IniFile.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TfrmMotorCheck *frmMotorCheck;
extern PCIM114GL g_MNet;
extern CIniFile g_IniFile;
//---------------------------------------------------------------------------
__fastcall TfrmMotorCheck::TfrmMotorCheck(TComponent* Owner)
    : TForm(Owner)
{
    m_nActiveAxis=0;
    m_nMoveMode=0;
    m_nSpeedMode=1;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMotorCheck::SetActiveAxis(unsigned int value)
{
    if(m_nActiveAxis != value) {
        m_nActiveAxis = value;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMotorCheck::Timer1Timer(TObject *Sender)
{
        Timer1->Enabled=false;
    AnsiString strPos,strUnit;
    /*
    switch(m_nActiveAxis)
    {
        case Pick_Axis:strUnit="°";break;
        case Dot_Axis:
        case Wheel1_Axis:
        case Wheel2_Axis:strUnit="mm";break;
    }
    */
    strUnit="mm";
    m_dCurrPos=g_MNet.GetFeedbackPos(m_nActiveAxis);
    strPos.sprintf("%4.3f %s",m_dCurrPos,strUnit);
    labelPosition->Caption=strPos;

    //Axis Status
    if(g_MNet.GetAxisStatus(m_nActiveAxis,Axis_Const::PEL)) shapePL->Brush->Color=clLime;else shapePL->Brush->Color=clGreen;
    if(g_MNet.GetAxisStatus(m_nActiveAxis,Axis_Const::MEL)) shapeML->Brush->Color=clLime;else shapeML->Brush->Color=clGreen;
    if(g_MNet.GetAxisStatus(m_nActiveAxis,Axis_Const::ORG)) shapeOrg->Brush->Color=clLime;else shapeOrg->Brush->Color=clGreen;
    if(g_MNet.GetAxisStatus(m_nActiveAxis,Axis_Const::INP)) shapeInp->Brush->Color=clLime;else shapeInp->Brush->Color=clGreen;
    if(!g_MNet.GetAxisStatus(m_nActiveAxis,Axis_Const::ALM)) shapeAlarm->Brush->Color=clMaroon;else shapeAlarm->Brush->Color=clRed;

    btnServoOnOff->Down=g_MNet.GetAxisStatus(m_nActiveAxis,Axis_Const::SVON);
     Timer1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMotorCheck::btnStopClick(TObject *Sender)
{
    g_MNet.StopMove(m_nActiveAxis);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMotorCheck::btnJogClick(TObject *Sender)
{
    m_nMoveMode=((TSpeedButton *)Sender)->Tag;
}
//--------------------------------------------------------------------------- 
void __fastcall TfrmMotorCheck::btnFastSpeedClick(TObject *Sender)
{
     m_nSpeedMode=((TSpeedButton *)Sender)->Tag;    
}
//---------------------------------------------------------------------------

void __fastcall TfrmMotorCheck::btnHomeClick(TObject *Sender)
{      
    g_MNet.AxisHome(m_nActiveAxis,false);
    g_MNet.WaitMotionDone(m_nActiveAxis,10000,true);
    ::Sleep(100);
    g_MNet.SetFeedbackPos(m_nActiveAxis,0);
    g_MNet.SetCommandPos(m_nActiveAxis,0);
      
}
//---------------------------------------------------------------------------


void __fastcall TfrmMotorCheck::btnFWDMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    double dMovePitch,dMoveSpeed;

    switch(m_nMoveMode)
    {
    case 0:dMovePitch=0;break;
    case 1:dMovePitch=1;break;
    case 2:dMovePitch=0.1;break;
    case 3:dMovePitch=0.01;break;
    }

    switch(m_nSpeedMode)
    {
    case 0:dMoveSpeed=g_IniFile.m_dJogSpeed[m_nActiveAxis]*2;break;
    case 1:dMoveSpeed=g_IniFile.m_dJogSpeed[m_nActiveAxis]*1;break;
    case 2:dMoveSpeed=g_IniFile.m_dJogSpeed[m_nActiveAxis]*0.5;break;
    case 3:dMoveSpeed=g_IniFile.m_dJogSpeed[m_nActiveAxis]*0.1;break;
    }

    g_MNet.SetMoveSpeed(m_nActiveAxis,dMoveSpeed,g_IniFile.m_dACCSpeed[m_nActiveAxis],g_IniFile.m_dDECSpeed[m_nActiveAxis]);
    if(dMovePitch==0)
    {
        g_MNet.StartJog(m_nActiveAxis,true);
    }
    else
    {
        g_MNet.RelMove(m_nActiveAxis,dMovePitch);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMotorCheck::btnRWDMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    double dMovePitch,dMoveSpeed;

    switch(m_nMoveMode)
    {
    case 0:dMovePitch=0;break;
    case 1:dMovePitch=1;break;
    case 2:dMovePitch=0.1;break;
    case 3:dMovePitch=0.01;break;
    }

    switch(m_nSpeedMode)
    {
    case 0:dMoveSpeed=g_IniFile.m_dJogSpeed[m_nActiveAxis]*2;break;
    case 1:dMoveSpeed=g_IniFile.m_dJogSpeed[m_nActiveAxis]*1;break;
    case 2:dMoveSpeed=g_IniFile.m_dJogSpeed[m_nActiveAxis]*0.5;break;
    case 3:dMoveSpeed=g_IniFile.m_dJogSpeed[m_nActiveAxis]*0.1;break;
    }

    g_MNet.SetMoveSpeed(m_nActiveAxis,dMoveSpeed,g_IniFile.m_dACCSpeed[m_nActiveAxis],g_IniFile.m_dDECSpeed[m_nActiveAxis]);
    if(dMovePitch==0)
    {
        g_MNet.StartJog(m_nActiveAxis,false);
    }
    else
    {
        g_MNet.RelMove(m_nActiveAxis,-dMovePitch);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMotorCheck::btnFWDMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    g_MNet.StopMove(m_nActiveAxis);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMotorCheck::btnRWDMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    g_MNet.StopMove(m_nActiveAxis);
}
//---------------------------------------------------------------------------


void __fastcall TfrmMotorCheck::FormShow(TObject *Sender)
{

      /*
     switch(m_nActiveAxis)
    {
        case SSLoad_Y:
            Caption="馬達測試----取放料";
            btnPitch1->Caption="1°";
            btnPitch01->Caption="0.1°";
            btnPitch001->Caption="0.01°";
        break;

    }
    */
}
//---------------------------------------------------------------------------

void __fastcall TfrmMotorCheck::btnServoOnOffClick(TObject *Sender)
{
    g_MNet.ServoOn(m_nActiveAxis,btnServoOnOff->Down);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMotorCheck::BitBtn1Click(TObject *Sender)
{
    g_MNet.ServoOn(m_nActiveAxis,true);
}
//---------------------------------------------------------------------------




