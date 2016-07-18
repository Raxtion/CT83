//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmManual.h"
#include "fmMain.h"
#include "IniFile.h"
#include "MainThread.h"
#include "PCIM114GL.H"
#include "math.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
extern CIniFile g_IniFile;
extern TfrmMain *frmMain;
extern PCIM114GL g_MNet;
extern CMainThread *g_pMainThread;
TfmManual *fmManual;
//---------------------------------------------------------------------------
__fastcall TfmManual::TfmManual(TComponent* Owner)
    : TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TfmManual::EnableAllButton(bool bEnabled)
{
    for(int nIndex=0;nIndex<this->ControlCount;nIndex++)
    {
        if(this->Controls[nIndex]->ClassNameIs("TSpeedButton"))
        {
            TSpeedButton *pBtn=(TSpeedButton *)this->Controls[nIndex];
            pBtn->Enabled=bEnabled;
        }

        if (this->Controls[nIndex]->ClassNameIs("TPageControl"))
        {
            TPageControl *pPage = (TPageControl *)this->Controls[nIndex];
            for (int nIndex2=0;nIndex2<pPage->ControlCount;nIndex2++)
            {
                if (pPage->Controls[nIndex2]->ClassNameIs("TTabSheet"))
                {
                    TTabSheet *pSheet = (TTabSheet *)pPage->Controls[nIndex2];
                    for (int nIndex3=0;nIndex3<pPage->ControlCount;nIndex3++)
                    {

                        if(pSheet->Controls[nIndex3]->ClassNameIs("TGroupBox"))
                        {
                            TGroupBox *pGroup=(TGroupBox *)pSheet->Controls[nIndex3];
                            for(int nIndex4=0;nIndex4<pGroup->ControlCount;nIndex4++)
                            {
                                if(pGroup->Controls[nIndex4]->ClassNameIs("TSpeedButton"))
                                {
                                    TSpeedButton *pBtn=(TSpeedButton *)pGroup->Controls[nIndex4];
                                    pBtn->Enabled=bEnabled;
                                }
                            }
                        }

                    }
                }
            }

        }
    }
    this->btnLDZGo->Enabled = false;
    this->btnLDYGo->Enabled = false;
    this->SpeedButton2->Enabled = false;
    this->SpeedButton6->Enabled = false;
    this->SpeedButton7->Enabled = false;
    this->SpeedButton8->Enabled = false;
}
//---------------------------------------------------------------------------



void __fastcall TfmManual::btnLDZGoClick(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

    TSpeedButton *pBtn = (TSpeedButton *)Sender;


    double dPos[20]={0};

    dPos[0]=g_IniFile.m_dLoaderClampMgzPos[0];
    dPos[1]=g_IniFile.m_dLoaderClampMgzPos[2];
    if (!g_IniFile.m_bIsMagazineUpFirst) dPos[2]=g_IniFile.m_dMagazinePushPosZ;
    else dPos[2]=g_IniFile.m_dMagazinePushPosUpFirstZ;
    dPos[3]=g_IniFile.m_dLoaderUnClampMgzPos[0];
    dPos[4]=g_IniFile.m_dLoaderUnClampMgzPos[2];

    if (!g_Motion.GetDI(DI::LoaderPusherBwd))
    {
        Application->MessageBoxA("推桿未縮回!","Confirm",MB_OK);
        return;
    }
    if (g_DIO.ReadDIBit(DI::LeftLaneChangerIn))
    {
        Application->MessageBoxA("確認入料流道有東西!","Confirm",MB_OK);
        return;
    }

    tm1MS.timeStart(10000);
    EnableAllButton(false);

    g_Motion.AbsMove(Axis_Const::LDZ, dPos[pBtn->Tag]);

    while(1)
    {
        if(g_Motion.IsPosDone(Axis_Const::LDZ, dPos[pBtn->Tag])) break;
        if(tm1MS.timeUp()) break;
        Application->ProcessMessages();
    }

    EnableAllButton(true);
    if (pBtn->Tag == 1)
    {
        this->btnLDZGo->Enabled = false;
        this->btnLDYGo->Enabled = false;
        this->SpeedButton3->Enabled = false;
        this->SpeedButton4->Enabled = false;
        this->SpeedButton6->Enabled = false;
        this->SpeedButton7->Enabled = false;
        this->SpeedButton8->Enabled = false;
        this->btnLDZDown1Step->Enabled = false;
    }

    if (pBtn->Tag == 3)
    {
        this->btnLDZGo->Enabled = false;
        this->btnLDYGo->Enabled = false;
        this->SpeedButton2->Enabled = false;
        this->SpeedButton3->Enabled = false;
        this->SpeedButton4->Enabled = false;
        this->btnLDZDown1Step->Enabled = false;
    }

}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnLDYGoClick(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

    TSpeedButton *pBtn = (TSpeedButton *)Sender;

    double dPos[20]={0};

    dPos[0]=g_IniFile.m_dLoaderClampMgzPos[1];
    dPos[1]=g_IniFile.m_dMagazinePushPosY;
    dPos[2]=g_IniFile.m_dLoaderUnClampMgzPos[1];

    if (!g_Motion.GetDI(DI::LoaderPusherBwd))
    {
        Application->MessageBoxA("推桿未縮回!","Confirm",MB_OK);
        return;
    }
    if (g_DIO.ReadDIBit(DI::LeftLaneChangerIn))
    {
        Application->MessageBoxA("確認入料流道有東西!","Confirm",MB_OK);
        return;
    }

    tm1MS.timeStart(10000);
    EnableAllButton(false);

    g_Motion.AbsMove(Axis_Const::LDY, dPos[pBtn->Tag]);

    while(1)
    {
        if(g_Motion.IsPosDone(Axis_Const::LDY, dPos[pBtn->Tag])) break;
        if(tm1MS.timeUp()) break;
        Application->ProcessMessages();
    }

    EnableAllButton(true);
    if (pBtn->Tag == 1 && g_Motion.GetDI(DI::LoaderClamperDown))
    {
        this->btnLDZGo->Enabled = false;
        this->btnLDYGo->Enabled = false;
        this->SpeedButton2->Enabled = false;
    }
    if (pBtn->Tag == 2)
    {
        this->btnLDZGo->Enabled = false;
        this->btnLDYGo->Enabled = false;
        this->SpeedButton2->Enabled = false;
        this->SpeedButton3->Enabled = false;
        this->SpeedButton4->Enabled = false;
        this->btnLDZDown1Step->Enabled = false;
        this->btnLDZToHome->Enabled = false;
    }

}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnRLCGoClick(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

    TSpeedButton *pBtn = (TSpeedButton *)Sender;

    double dPos[20]={0};

    dPos[0]=g_IniFile.m_dLeftLaneChangerMgzPos;
    dPos[1]=g_IniFile.m_dLeftLaneChangerSprayPos[0];
    dPos[2]=g_IniFile.m_dLeftLaneChangerSprayPos[1];

    if (g_DIO.ReadDIBit(DI::LeftLaneChangerIn) 
        || g_DIO.ReadDIBit(DI::LeftLaneChangerOut)
        || g_DIO.ReadDIBit(DI::FrontLaneSprayIn)
        || g_DIO.ReadDIBit(DI::RearLaneSprayIn))
    {
        Application->MessageBoxA("確認入料流道有東西!","Confirm",MB_OK);
        return;
    }

    tm1MS.timeStart(10000);
    EnableAllButton(false);

    g_Motion.AbsMove(Axis_Const::LLC, dPos[pBtn->Tag]);

    while(1)
    {
        if(g_Motion.IsPosDone(Axis_Const::LLC, dPos[pBtn->Tag])) break;
        if(tm1MS.timeUp()) break;
        Application->ProcessMessages();
    }

    EnableAllButton(true);
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnLLCGoClick(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

    TSpeedButton *pBtn = (TSpeedButton *)Sender;

    double dPos[20]={0};

    dPos[0]=g_IniFile.m_dRightLaneChangerSprayPos[0];
    dPos[1]=g_IniFile.m_dRightLaneChangerSprayPos[1];
    dPos[2]=g_IniFile.m_dConveyerPos[0];
    dPos[3]=g_IniFile.m_dConveyerPos[1];
    dPos[4]=g_IniFile.m_dConveyerPos[2];
    dPos[5]=g_IniFile.m_dConveyerPos[3];
    dPos[6]=g_IniFile.m_dConveyerPos[4];
    dPos[7]=g_IniFile.m_dNGMagPos;

    if (!g_Motion.GetDI(DI::RightPusherBwd))
    {
        Application->MessageBoxA("推桿未縮回!","Confirm",MB_OK);
        return;
    }
    if (g_DIO.ReadDIBit(DI::FrontLaneSprayOut) 
        || g_DIO.ReadDIBit(DI::RearLaneSprayOut)
        || g_DIO.ReadDIBit(DI::RightLaneChangerIn)
        || g_DIO.ReadDIBit(DI::RightLaneChangerOut))
    {
        Application->MessageBoxA("確認出料流道有東西!","Confirm",MB_OK);
        return;
    }

    tm1MS.timeStart(10000);
    EnableAllButton(false);

    g_Motion.AbsMove(Axis_Const::RLC, dPos[pBtn->Tag]);

    while(1)
    {
        if(g_Motion.IsPosDone(Axis_Const::RLC, dPos[pBtn->Tag])) break;
        if(tm1MS.timeUp()) break;
        Application->ProcessMessages();
    }

    EnableAllButton(true);
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnCheckCCDClick(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);
    static int nMoveIndex = 0;

    TSpeedButton *pBtn = (TSpeedButton *)Sender;

    double dPos[20]={0};

    dPos[0]=g_IniFile.m_dCCDCheckPosX[0];
    dPos[1]=g_IniFile.m_dCCDCheckPosY[0];
    dPos[2]=g_IniFile.m_dCCDCheckPosX[1];
    dPos[3]=g_IniFile.m_dCCDCheckPosY[1];
    dPos[4]=g_IniFile.m_dCCDCheckPosX[2];
    dPos[5]=g_IniFile.m_dCCDCheckPosY[2];
    dPos[6]=g_IniFile.m_dCCDCheckPosX[3];
    dPos[7]=g_IniFile.m_dCCDCheckPosY[3];

    tm1MS.timeStart(10000);
    EnableAllButton(false);

    if (nMoveIndex > 7) nMoveIndex = 0;
    g_Motion.AbsMove(Axis_Const::CDX, dPos[nMoveIndex]);
    g_Motion.AbsMove(Axis_Const::RLC, dPos[nMoveIndex+1]);
    nMoveIndex++;
    nMoveIndex++;

    while(1)
    {
        if(g_Motion.IsPosDone(Axis_Const::CDX, dPos[0]) && g_Motion.IsPosDone(Axis_Const::RLC, dPos[1])) break;
        if(tm1MS.timeUp()) break;
        Application->ProcessMessages();
    }

    EnableAllButton(true);
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnSPXGoClick(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

    TSpeedButton *pBtn = (TSpeedButton *)Sender;

    double dPos[20]={0};

    dPos[0]=g_IniFile.m_dStartSprayPosX[0];
    dPos[1]=g_IniFile.m_dStartSprayPosX[1];
    dPos[2]=g_IniFile.m_dScaleSprayPosX[0];
    dPos[3]=g_IniFile.m_dScaleSprayPosX[1];
    dPos[4]=g_IniFile.m_dCleanSprayPosX[0];
    dPos[5]=g_IniFile.m_dCleanSprayPosX[1];
    dPos[6]=g_IniFile.m_dCleanSprayPosX[2];
    dPos[7]=g_IniFile.m_dCleanSprayPosX[3];

    if (g_Motion.GetFeedbackPos(Axis_Const::SPZ) != 0.0)
    {
        Application->MessageBoxA("噴嘴未縮回!","Confirm",MB_OK);
        return;
    }

    tm1MS.timeStart(10000);
    EnableAllButton(false);

    g_Motion.AbsMove(Axis_Const::SPX, dPos[pBtn->Tag]);

    while(1)
    {
        if(g_Motion.IsPosDone(Axis_Const::SPX, dPos[pBtn->Tag])) break;
        if(tm1MS.timeUp()) break;
        Application->ProcessMessages();
    }

    EnableAllButton(true);
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnSPYGoClick(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

    TSpeedButton *pBtn = (TSpeedButton *)Sender;

    double dPos[20]={0};

    dPos[0]=g_IniFile.m_dStartSprayPosY[0];
    dPos[1]=g_IniFile.m_dStartSprayPosY[1];
    dPos[2]=g_IniFile.m_dScaleSprayPosY[0];
    dPos[3]=g_IniFile.m_dScaleSprayPosY[1];
    dPos[4]=g_IniFile.m_dCleanSprayPosY[0];
    dPos[5]=g_IniFile.m_dCleanSprayPosY[1];
    dPos[6]=g_IniFile.m_dCleanSprayPosY[2];
    dPos[7]=g_IniFile.m_dCleanSprayPosY[3];
    
    if (g_Motion.GetFeedbackPos(Axis_Const::SPZ) != 0.0)
    {
        Application->MessageBoxA("噴嘴未縮回!","Confirm",MB_OK);
        return;
    }

    tm1MS.timeStart(10000);
    EnableAllButton(false);

    g_Motion.AbsMove(Axis_Const::SPY, dPos[pBtn->Tag]);

    while(1)
    {
        if(g_Motion.IsPosDone(Axis_Const::SPY, dPos[pBtn->Tag])) break;
        if(tm1MS.timeUp()) break;
        Application->ProcessMessages();
    }

    EnableAllButton(true);
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnSPZGoClick(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

    TSpeedButton *pBtn = (TSpeedButton *)Sender;

    double dPos[20]={0};

    dPos[0]=g_IniFile.m_dSprayPosZ;
    dPos[1]=g_IniFile.m_dScaleSprayPosZ[0];
    dPos[2]=g_IniFile.m_dScaleSprayPosZ[1];
    dPos[3]=g_IniFile.m_dCleanSprayPosZ;


    tm1MS.timeStart(10000);
    EnableAllButton(false);

    g_Motion.AbsMove(Axis_Const::SPZ, dPos[pBtn->Tag]);

    while(1)
    {
        if(g_Motion.IsPosDone(Axis_Const::SPZ, dPos[pBtn->Tag])) break;
        if(tm1MS.timeUp()) break;
        Application->ProcessMessages();
    }

    EnableAllButton(true);
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnMGZGoClick(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

    TSpeedButton *pBtn = (TSpeedButton *)Sender;

    double dPos[20]={0};

    dPos[0]=g_IniFile.m_dMgzStartPos;
    dPos[0]=g_IniFile.m_dMgzStartPosUpFirst;

    if (g_DIO.ReadDIBit(DI::RightLaneChangerOut))
    {
        Application->MessageBoxA("料片未完整送出 (X034 on)","Confirm",MB_OK);
        return;
    }
    if (!g_Motion.GetDI(DI::RightPusherBwd))
    {
        Application->MessageBoxA("推桿未縮回!","Confirm",MB_OK);
        return;
    }

    tm1MS.timeStart(10000);
    EnableAllButton(false);

    if (!g_IniFile.m_bIsMgzUpFirst)
        g_Motion.AbsMove(Axis_Const::MGZ, g_IniFile.m_dMgzStartPos);
    else
        g_Motion.AbsMove(Axis_Const::MGZ, g_IniFile.m_dMgzStartPosUpFirst);

    while(1)
    {
        if(g_Motion.IsPosDone(Axis_Const::MGZ, dPos[pBtn->Tag])) break;
        if(tm1MS.timeUp()) break;
        Application->ProcessMessages();
    }

    EnableAllButton(true);
}
//---------------------------------------------------------------------------


void __fastcall TfmManual::btnLDZDown1StepClick(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

    TSpeedButton *pBtn = (TSpeedButton *)Sender;

    double dPos[20]={0};

    dPos[0]=g_IniFile.m_dLoaderMgzPitch;

    if (g_Motion.GetFeedbackPos(Axis_Const::LDY) > g_IniFile.m_dLDYUnLoadClamperAlarm)
    {
        Application->MessageBoxA("LDY > 安全位置!","Confirm",MB_OK);
        return;
    }
    if (!g_Motion.GetDI(DI::LoaderPusherBwd))
    {
        Application->MessageBoxA("推桿未縮回!","Confirm",MB_OK);
        return;
    }
    if (g_DIO.ReadDIBit(DI::LeftLaneChangerIn))
    {
        Application->MessageBoxA("確認入料流道有東西!","Confirm",MB_OK);
        return;
    }

    tm1MS.timeStart(10000);
    EnableAllButton(false);

    if (!g_IniFile.m_bIsMagazineUpFirst)
        g_Motion.RelMove(Axis_Const::LDZ, g_IniFile.m_dLoaderMgzPitch);
    else
        g_Motion.RelMove(Axis_Const::LDZ, -g_IniFile.m_dLoaderMgzPitch);

    while(1)
    {
        if(g_Motion.IsMotionDone(Axis_Const::LDZ)) break;
        if(tm1MS.timeUp()) break;
        Application->ProcessMessages();
    }

    EnableAllButton(true);
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnLDYToHomeClick(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

    TSpeedButton *pBtn = (TSpeedButton *)Sender;

    double dPos[20]={0};

    if ((fabs(g_Motion.GetFeedbackPos(Axis_Const::LDZ) - g_IniFile.m_dLoaderClampMgzPos[0]) <= 1
        && fabs(g_Motion.GetFeedbackPos(Axis_Const::LDY) - g_IniFile.m_dLoaderClampMgzPos[1]) <= 1)
        || (fabs(g_Motion.GetFeedbackPos(Axis_Const::LDZ) - g_IniFile.m_dLoaderClampMgzPos[2]) <= 1
            && fabs(g_Motion.GetFeedbackPos(Axis_Const::LDY) - g_IniFile.m_dLoaderClampMgzPos[1]) <= 1))
    {
        Application->MessageBoxA("此位置不可以歸零LDY!","Confirm",MB_OK);
        return;
    }
    if (!g_Motion.GetDI(DI::LoaderPusherBwd))
    {
        Application->MessageBoxA("推桿未縮回!","Confirm",MB_OK);
        return;
    }
    if (g_DIO.ReadDIBit(DI::LeftLaneChangerIn))
    {
        Application->MessageBoxA("確認入料流道有東西!","Confirm",MB_OK);
        return;
    }

    
    tm1MS.timeStart(10000);
    EnableAllButton(false);

    g_Motion.AbsMove(Axis_Const::LDY, 0.0);

    while(1)
    {
        if(g_Motion.IsMotionDone(Axis_Const::LDY)) break;
        if(tm1MS.timeUp()) break;
        Application->ProcessMessages();
    }

    EnableAllButton(true);
}
//---------------------------------------------------------------------------




void __fastcall TfmManual::btnAutoStartReLoadClamperClick(TObject *Sender)
{
    frmMain->SpeedButton5Click(this);
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnAutoStartUnLoadClamperClick(TObject *Sender)
{
    frmMain->SpeedButton4Click(this);
}
//---------------------------------------------------------------------------


void __fastcall TfmManual::btnSimpleIOClick(TObject *Sender)
{
    TSpeedButton *pBtn=(TSpeedButton *)Sender;
    g_Motion.SetDO(pBtn->Tag, !g_MNet.GetDO(pBtn->Tag));
}
//---------------------------------------------------------------------------


void __fastcall TfmManual::btnRelMoveSPXClick(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

    TSpeedButton *pBtn = (TSpeedButton *)Sender;

    double dPos[20]={0};

    dPos[0]=g_IniFile.m_dSprayDistance;
    dPos[1]=-g_IniFile.m_dSprayDistance;
    dPos[2]=g_IniFile.m_dCleanSprayDistance;
    dPos[3]=-g_IniFile.m_dCleanSprayDistance;


    tm1MS.timeStart(10000);
    EnableAllButton(false);

    if (pBtn->Tag == 0 || pBtn->Tag == 2)
    {
        if (g_pMainThread->CheckRelMoveAlarm(Axis_Const::SPX, true, dPos[pBtn->Tag]))
            g_Motion.RelMove(Axis_Const::SPX, dPos[pBtn->Tag]);
        else
        {
            Application->MessageBoxA("噴嘴超出移動範圍!","Confirm",MB_OK);
            EnableAllButton(true);
            return;
        }
    }
    else
    {
        if (g_pMainThread->CheckRelMoveAlarm(Axis_Const::SPX, false, -dPos[pBtn->Tag]))
            g_Motion.RelMove(Axis_Const::SPX, dPos[pBtn->Tag]);
        else
        {
            Application->MessageBoxA("噴嘴超出移動範圍!","Confirm",MB_OK);
            EnableAllButton(true);
            return;
        }
    }

    while(1)
    {
        if(g_Motion.IsMotionDone(Axis_Const::SPX)) break;
        if(tm1MS.timeUp()) break;
        Application->ProcessMessages();
    }

    EnableAllButton(true);
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnRelMoveSPYClick(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

    TSpeedButton *pBtn = (TSpeedButton *)Sender;

    double dPos[20]={0};

    dPos[0]=g_IniFile.m_dSprayPitch;


    tm1MS.timeStart(10000);
    EnableAllButton(false);

    if (g_pMainThread->CheckRelMoveAlarm(Axis_Const::SPY, true, dPos[pBtn->Tag]))
        g_Motion.RelMove(Axis_Const::SPY, dPos[pBtn->Tag]);
    else
    {
        Application->MessageBoxA("噴嘴超出移動範圍!","Confirm",MB_OK);
        EnableAllButton(true);
        return;
    }

    while(1)
    {
        if(g_Motion.IsMotionDone(Axis_Const::SPY)) break;
        if(tm1MS.timeUp()) break;
        Application->ProcessMessages();
    }

    EnableAllButton(true);
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnStartFluxClick(TObject *Sender)
{
    TSpeedButton *pBtn=(TSpeedButton *)Sender;

    g_Motion.SetDO(DO::SprayerFluxOn, !g_MNet.GetDO(DO::SprayerFluxOn));
    g_Motion.SetDO(DO::SprayerAirOn, !g_MNet.GetDO(DO::SprayerAirOn));
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnStartWaterClick(TObject *Sender)
{
    TSpeedButton *pBtn=(TSpeedButton *)Sender;

    g_Motion.SetDO(DO::SprayerAirOn, !g_MNet.GetDO(DO::SprayerAirOn));
    g_Motion.SetDO(DO::SprayerWaterOn, !g_MNet.GetDO(DO::SprayerWaterOn));
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnStopSprayerClick(TObject *Sender)
{
    TSpeedButton *pBtn=(TSpeedButton *)Sender;

    g_Motion.SetDO(DO::SprayerFluxOn, false);
    g_Motion.SetDO(DO::SprayerAirOn, false);
    g_Motion.SetDO(DO::SprayerAirOn, false);
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnAutoStartSBTSprayFClick(TObject *Sender)
{
    frmMain->SpeedButton1Click(frmMain->SpeedButton1);
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnAutoStartSBTSprayRClick(TObject *Sender)
{
    frmMain->SpeedButton1Click(frmMain->SpeedButton3);
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnMGZDown1StepClick(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

    TSpeedButton *pBtn = (TSpeedButton *)Sender;

    double dPos[20]={0};

    dPos[0]=g_IniFile.m_dMgzPitch;

    if (g_DIO.ReadDIBit(DI::RightLaneChangerOut))
    {
        Application->MessageBoxA("料片未完整送出 (X034 on)","Confirm",MB_OK);
        return;
    }
    if (!g_Motion.GetDI(DI::RightPusherBwd))
    {
        Application->MessageBoxA("推桿未縮回!","Confirm",MB_OK);
        return;
    }


    tm1MS.timeStart(10000);
    EnableAllButton(false);

    if (!g_IniFile.m_bIsMgzUpFirst)
        g_Motion.RelMove(Axis_Const::MGZ, g_IniFile.m_dMgzPitch);
    else
        g_Motion.RelMove(Axis_Const::MGZ, -g_IniFile.m_dMgzPitch);

    while(1)
    {
        if(g_Motion.IsMotionDone(Axis_Const::MGZ)) break;
        if(tm1MS.timeUp()) break;
        Application->ProcessMessages();
    }

    EnableAllButton(true);
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnAutoStartFluxScaleSprayClick(TObject *Sender)
{
    frmMain->SpeedButton6Click(frmMain->SpeedButton6);
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnAutoStartWaterScaleSprayClick(TObject *Sender)
{
    frmMain->SpeedButton7Click(frmMain->SpeedButton7);
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnAutoStartCleanSprayClick(TObject *Sender)
{
    frmMain->SpeedButton8Click(frmMain->SpeedButton8);
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnAutoStartFillFluxClick(TObject *Sender)
{
    frmMain->SpeedButton9Click(frmMain->SpeedButton9);
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnAutoStopFillFluxClick(TObject *Sender)
{
    frmMain->SpeedButton10Click(frmMain->SpeedButton10);
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnSPZToHomeClick(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

    TSpeedButton *pBtn = (TSpeedButton *)Sender;

    double dPos[20]={0};

    
    tm1MS.timeStart(10000);
    EnableAllButton(false);

    g_Motion.AbsMove(Axis_Const::SPZ, 0.0);

    while(1)
    {
        if(g_Motion.IsMotionDone(Axis_Const::SPZ)) break;
        if(tm1MS.timeUp()) break;
        Application->ProcessMessages();
    }

    EnableAllButton(true);
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnLDZToHomeClick(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

    TSpeedButton *pBtn = (TSpeedButton *)Sender;

    double dPos[20]={0};

    if ((fabs(g_Motion.GetFeedbackPos(Axis_Const::LDY) - g_IniFile.m_dLoaderClampMgzPos[1]) <= 1 )
        && (g_Motion.GetFeedbackPos(Axis_Const::LDZ) >= g_IniFile.m_dLoaderClampMgzPos[0]))
    {
        Application->MessageBoxA("此位置不可以歸零LDZ!","Confirm",MB_OK);
        return;
    }
    if (!g_Motion.GetDI(DI::LoaderPusherBwd))
    {
        Application->MessageBoxA("推桿未縮回!","Confirm",MB_OK);
        return;
    }
    if (g_DIO.ReadDIBit(DI::LeftLaneChangerIn))
    {
        Application->MessageBoxA("確認入料流道有東西!","Confirm",MB_OK);
        return;
    }
    
    tm1MS.timeStart(10000);
    EnableAllButton(false);

    g_Motion.AbsMove(Axis_Const::LDZ, 0.0);

    while(1)
    {
        if(g_Motion.IsMotionDone(Axis_Const::LDZ)) break;
        if(tm1MS.timeUp()) break;
        Application->ProcessMessages();
    }

    EnableAllButton(true);
}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnLoaderBusherClick(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);
    g_Motion.SetDO(DO::LoaderPusher, !g_MNet.GetDO(DO::LoaderPusher));
    tm1MS.timeStart(10000);
    while (1)
    {
        if (!g_Motion.GetDI(DI::LoaderPusherAlarm))
            g_Motion.SetDO(DO::LoaderPusher, false);
        if(tm1MS.timeUp() || g_Motion.GetDI(DI::LoaderPusherFwd)) break;
        Application->ProcessMessages();
    }

}
//---------------------------------------------------------------------------

void __fastcall TfmManual::btnRLCBusherClick(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);
    g_Motion.SetDO(DO::RightLaneChangerPusher, !g_MNet.GetDO(DO::RightLaneChangerPusher));
    tm1MS.timeStart(10000);
    while (1)
    {
        if (g_Motion.GetDI(DI::RightPusherAlarm))
            g_Motion.SetDO(DO::RightLaneChangerPusher, false);
        if(tm1MS.timeUp() || g_Motion.GetDI(DI::RightPusherFwd)) break;
        Application->ProcessMessages();
    }
}
//---------------------------------------------------------------------------

