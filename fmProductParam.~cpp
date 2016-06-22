//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fmProductParam.h"
#include "CtkLedControll.h"
#include "fmMotorCheck.h"
#include "fmMotorCheck.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//TfrmProductParam *frmProductParam;
extern CTK_Led g_LED;
//---------------------------------------------------------------------------
__fastcall TfrmProductParam::TfrmProductParam(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TfrmProductParam::m_nLEDDimmer0Change(TObject *Sender)
{
        g_LED.SetCurrent(0,0,m_nLEDDimmer0->Position,0);

        labelLED0->Caption=m_nLEDDimmer0->Position;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProductParam::FormShow(TObject *Sender)
{
        labelLED0->Caption=m_nLEDDimmer0->Position;
        labelLED1->Caption=m_nLEDDimmer1->Position;         
}
//---------------------------------------------------------------------------

void __fastcall TfrmProductParam::m_nLEDDimmer1Change(TObject *Sender)
{
        g_LED.SetCurrent(1,0,m_nLEDDimmer1->Position,0);

        labelLED1->Caption=m_nLEDDimmer1->Position;
}
//---------------------------------------------------------------------------
void __fastcall TfrmProductParam::StaticText5Click(TObject *Sender)
{

        ////AXIS0=0,AXIS1,AXIS2,AXIS3,LDZ,LDY,SPZ,SPX,CDX,MGZ,RLC,SPY,LLC

        TStaticText *pText=(TStaticText *)Sender;
        TfrmMotorCheck *pMotorCheckDlg;

        pMotorCheckDlg=new TfrmMotorCheck(this);
        pMotorCheckDlg->m_nActiveAxis=pText->Tag;
        pMotorCheckDlg->Caption=pText->Caption;

        if(pMotorCheckDlg->ShowModal()==mrOk)
        {
                TEdit *pEdit=(TEdit *)FindComponent(pText->Hint);
                if(pEdit) pEdit->Text=pMotorCheckDlg->m_dCurrPos;
                else ShowMessage("¼g¤J¥¢±Ñ");
        }


        delete pMotorCheckDlg;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProductParam::m_bIsMagazineUpFirstClick(
      TObject *Sender)
{
    TCheckBox *pChx = (TCheckBox *)Sender;
    if (!pChx->Checked)
    {
        this->m_dMagazinePushPosZ->Enabled = true;
        this->m_dMagazinePushPosUpFirstZ->Enabled = false;
    }
    else
    {
        this->m_dMagazinePushPosZ->Enabled = false;
        this->m_dMagazinePushPosUpFirstZ->Enabled = true;
    }
}
//---------------------------------------------------------------------------


