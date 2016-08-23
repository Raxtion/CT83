//---------------------------------------------------------------------------

#ifndef fmMachinParamH
#define fmMachinParamH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmMachineParam : public TForm
{
__published:	// IDE-managed Components
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TGroupBox *GroupBox1;
        TEdit *editAcc1;
        TEdit *editDec1;
        TEdit *editJogSpeed1;
        TEdit *editWorkSpeed1;
        TEdit *editAcc2;
        TEdit *editDec2;
        TEdit *editJogSpeed2;
        TEdit *editWorkSpeed2;
        TEdit *editAcc3;
        TEdit *editDec3;
        TEdit *editJogSpeed3;
        TEdit *editWorkSpeed3;
        TEdit *editAcc4;
        TEdit *editDec4;
        TEdit *editJogSpeed4;
        TEdit *editWorkSpeed4;
        TStaticText *StaticText1;
        TStaticText *StaticText2;
        TStaticText *StaticText3;
        TStaticText *StaticText4;
        TStaticText *StaticText6;
        TStaticText *StaticText7;
        TStaticText *StaticText8;
        TStaticText *StaticText9;
        TStaticText *StaticText10;
        TStaticText *StaticText11;
        TStaticText *StaticText12;
        TStaticText *StaticText13;
        TStaticText *StaticText14;
        TEdit *editAcc5;
        TEdit *editDec5;
        TEdit *editJogSpeed5;
        TEdit *editWorkSpeed5;
        TStaticText *StaticText15;
        TEdit *editAcc6;
        TEdit *editDec6;
        TEdit *editJogSpeed6;
        TEdit *editWorkSpeed6;
        TStaticText *StaticText16;
        TStaticText *StaticText23;
        TEdit *editAcc7;
        TEdit *editDec7;
        TEdit *editJogSpeed7;
        TEdit *editWorkSpeed7;
        TStaticText *StaticText36;
        TEdit *editAcc8;
        TEdit *editDec8;
        TEdit *editJogSpeed8;
        TEdit *editWorkSpeed8;
        TStaticText *StaticText37;
        TEdit *editAcc9;
        TEdit *editDec9;
        TEdit *editJogSpeed9;
        TEdit *editWorkSpeed9;
        TStaticText *StaticText38;
        TCheckBox *m_bForceEject;
        TGroupBox *GroupBox2;
        TStaticText *StaticText5;
        TEdit *m_dMgzStartPos;
        TStaticText *StaticText17;
        TStaticText *StaticText18;
        TEdit *m_dMgzPitch;
        TStaticText *StaticText19;
        TStaticText *StaticText20;
        TEdit *m_nMgzSize;
        TStaticText *StaticText21;
        TGroupBox *GroupBox5;
        TStaticText *StaticText44;
    TEdit *m_dScaleSprayPosX0;
        TStaticText *StaticText45;
        TStaticText *StaticText46;
    TEdit *m_dScaleSprayPosY0;
        TStaticText *StaticText47;
        TStaticText *StaticText50;
    TEdit *m_dScaleSprayPosZ0;
        TStaticText *StaticText51;
    TGroupBox *GroupBox6;
    TStaticText *StaticText56;
    TEdit *m_dLDYUnLoadClamperAlarm;
    TStaticText *StaticText57;
    TStaticText *StaticText52;
    TEdit *m_dSprayLaneAlarmX0;
    TStaticText *StaticText53;
    TStaticText *StaticText54;
    TEdit *m_dSprayLaneAlarmY0;
    TStaticText *StaticText55;
    TStaticText *StaticText58;
    TEdit *m_dSprayLaneAlarmX1;
    TStaticText *StaticText59;
    TStaticText *StaticText60;
    TEdit *m_dSprayLaneAlarmY1;
    TStaticText *StaticText61;
    TStaticText *StaticText88;
    TEdit *m_dScaleSprayDelayTime;
    TStaticText *StaticText89;
    TGroupBox *GroupBox7;
    TStaticText *StaticText76;
    TEdit *m_dScaleSprayPosX1;
    TStaticText *StaticText77;
    TStaticText *StaticText78;
    TEdit *m_dScaleSprayPosY1;
    TStaticText *StaticText79;
    TStaticText *StaticText80;
    TEdit *m_dScaleSprayPosZ1;
    TStaticText *StaticText81;
    TStaticText *StaticText82;
    TEdit *m_nScaleSprayTime1;
    TStaticText *StaticText83;
    TStaticText *StaticText86;
    TEdit *m_nScaleSprayTimes1;
    TStaticText *StaticText87;
    TStaticText *StaticText94;
    TEdit *m_dSprayLaneAlarmZ;
    TStaticText *StaticText95;
    TStaticText *StaticText100;
    TEdit *m_dMgzStartPosUpFirst;
    TStaticText *StaticText101;
    TCheckBox *m_bIsMgzUpFirst;
    TRadioGroup *m_nRailOption;
    TCheckBox *m_bUsePreAutoWeightScale;
    TGroupBox *GroupBox8;
    TEdit *m_strAutoCleanSprayLaneDateTime0;
    TStaticText *StaticText104;
    TStaticText *StaticText106;
    TStaticText *StaticText102;
    TEdit *m_strAutoCleanSprayLaneDateTime1;
    TEdit *m_strAutoCleanSprayLaneDateTime2;
    TCheckBox *m_bUseAutoCleanSprayLane;
    TCheckBox *m_bIsUseCIM;
    TCheckBox *m_bIsUseRightLCPusher;
    TCheckBox *m_bIsResetFluxLifetime;
    TCheckBox *m_bUseUnClampAutoWeightScale;
        void __fastcall StaticText5Click(TObject *Sender);
    void __fastcall m_bIsMgzUpFirsClick(TObject *Sender);
    void __fastcall m_bIsUseCIMClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmMachineParam(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMachineParam *frmMachineParam;
//---------------------------------------------------------------------------
#endif
