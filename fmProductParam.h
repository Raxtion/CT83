//---------------------------------------------------------------------------

#ifndef fmProductParamH
#define fmProductParamH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmProductParam : public TForm
{
__published:	// IDE-managed Components
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TGroupBox *GroupBox4;
        TLabel *Label2;
        TEdit *m_dMarkScore0;
        TGroupBox *GroupBox10;
        TLabel *labelLED0;
        TLabel *labelLED1;
        TTrackBar *m_nLEDDimmer0;
        TTrackBar *m_nLEDDimmer1;
        TGroupBox *GroupBox1;
        TStaticText *StaticText5;
        TEdit *m_dLoaderClampMgzPos0;
        TStaticText *StaticText17;
        TStaticText *StaticText1;
        TEdit *m_dLoaderClampMgzPos1;
        TStaticText *StaticText2;
        TStaticText *StaticText3;
        TEdit *m_dLoaderClampMgzPos2;
        TStaticText *StaticText4;
        TStaticText *StaticText6;
        TEdit *m_dMagazinePushPosY;
        TStaticText *StaticText7;
        TStaticText *StaticText8;
        TEdit *m_dMagazinePushPosZ;
        TStaticText *StaticText9;
        TStaticText *StaticText10;
        TStaticText *StaticText11;
        TStaticText *StaticText12;
        TEdit *m_dLoaderUnClampMgzPos2;
        TEdit *m_dLoaderUnClampMgzPos1;
        TEdit *m_dLoaderUnClampMgzPos0;
        TStaticText *StaticText13;
        TStaticText *StaticText14;
        TStaticText *StaticText15;
        TGroupBox *GroupBox2;
        TStaticText *StaticText16;
        TEdit *m_dLeftLaneChangerMgzPos;
        TStaticText *StaticText18;
        TStaticText *StaticText19;
        TEdit *m_dLeftLaneChangerSprayPos0;
        TStaticText *StaticText20;
        TStaticText *StaticText21;
        TEdit *m_dLeftLaneChangerSprayPos1;
        TStaticText *StaticText22;
        TGroupBox *GroupBox3;
        TStaticText *StaticText23;
        TEdit *m_dStartSprayPosX0;
        TStaticText *StaticText24;
        TStaticText *StaticText25;
        TEdit *m_dStartSprayPosY0;
        TStaticText *StaticText26;
        TStaticText *StaticText27;
        TStaticText *StaticText28;
        TEdit *m_dStartSprayPosX1;
        TEdit *m_dStartSprayPosY1;
        TStaticText *StaticText29;
        TStaticText *StaticText30;
        TStaticText *StaticText31;
        TEdit *m_dSprayPosZ;
        TStaticText *StaticText32;
        TStaticText *StaticText33;
        TEdit *m_dSprayDistance;
        TStaticText *StaticText34;
        TGroupBox *GroupBox5;
        TStaticText *StaticText35;
        TStaticText *StaticText36;
        TEdit *m_dRightLaneChangerSprayPos0;
        TEdit *m_dRightLaneChangerSprayPos1;
        TStaticText *StaticText37;
        TStaticText *StaticText38;
        TStaticText *StaticText39;
        TStaticText *StaticText40;
    TEdit *m_dCCDCheckPosX0;
    TEdit *m_dCCDCheckPosY0;
        TStaticText *StaticText41;
        TStaticText *StaticText42;
        TCheckBox *m_bUseSprayer;
        TCheckBox *m_bUseCCD;
        TStaticText *StaticText43;
        TEdit *m_nSprayTimes;
        TStaticText *StaticText44;
        TStaticText *StaticText45;
        TEdit *m_dSprayPitch;
        TStaticText *StaticText46;
        TGroupBox *GroupBox6;
        TStaticText *StaticText47;
        TStaticText *StaticText48;
        TEdit *m_dFluxTankAirPressure;
        TEdit *m_dSprayerAirPressure;
    TStaticText *StaticText49;
    TEdit *m_dLoaderMgzPitch;
    TStaticText *StaticText50;
    TStaticText *StaticText51;
    TEdit *m_dSprayReadyPos;
    TStaticText *StaticText52;
    TStaticText *StaticText53;
    TEdit *m_dRightLaneChangerDelayTime;
    TStaticText *StaticText54;
    TStaticText *StaticText55;
    TEdit *m_dMagazinePushPosUpFirstZ;
    TStaticText *StaticText56;
    TCheckBox *m_bIsMagazineUpFirst;
    TStaticText *StaticText57;
    TStaticText *StaticText58;
    TEdit *m_dCCDCheckPosX1;
    TEdit *m_dCCDCheckPosY1;
    TStaticText *StaticText59;
    TStaticText *StaticText60;
    TStaticText *StaticText61;
    TStaticText *StaticText62;
    TEdit *m_dCCDCheckPosX2;
    TEdit *m_dCCDCheckPosY2;
    TStaticText *StaticText63;
    TStaticText *StaticText64;
    TStaticText *StaticText65;
    TStaticText *StaticText66;
    TEdit *m_dCCDCheckPosX3;
    TEdit *m_dCCDCheckPosY3;
    TStaticText *StaticText67;
    TStaticText *StaticText68;
    TCheckBox *m_bIsUseCCDCheckPos0;
    TCheckBox *m_bIsUseCCDCheckPos1;
    TCheckBox *m_bIsUseCCDCheckPos2;
    TCheckBox *m_bIsUseCCDCheckPos3;
    TLabel *Label1;
    TGroupBox *GroupBox7;
    TStaticText *StaticText73;
    TEdit *m_nScaleSprayTime0;
    TStaticText *StaticText74;
    TStaticText *StaticText84;
    TEdit *m_nScaleSprayTimes0;
    TStaticText *StaticText85;
    TStaticText *StaticText96;
    TEdit *m_dWeightScaleAlarmUp;
    TStaticText *StaticText97;
    TStaticText *StaticText98;
    TEdit *m_dWeightScaleAlarmDown;
    TStaticText *StaticText99;
        void __fastcall m_nLEDDimmer0Change(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall m_nLEDDimmer1Change(TObject *Sender);
        void __fastcall StaticText5Click(TObject *Sender);
    void __fastcall m_bIsMagazineUpFirstClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmProductParam(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmProductParam *frmProductParam;
//---------------------------------------------------------------------------
#endif
