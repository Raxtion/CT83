//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fmMain.h"
#include "fmMachinParam.h"
#include "fmMotorCheck.h"
#include "EQPXML.h"

extern CEQPXML g_eqpXML;
extern TfrmMain *frmMain;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TfrmMachineParam *frmMachineParam;

//---------------------------------------------------------------------------
__fastcall TfrmMachineParam::TfrmMachineParam(TComponent* Owner)
        : TForm(Owner)
{


}
//---------------------------------------------------------------------------



void __fastcall TfrmMachineParam::StaticText5Click(TObject *Sender)
{       

        //AXIS0=0,AXIS1,AXIS2,AXIS3,LDZ,LDY,SPZ,SPX,CDX,MGZ,RLC,SPY,LLC

        TStaticText *pText=(TStaticText *)Sender;
        TfrmMotorCheck *pMotorCheckDlg;

        pMotorCheckDlg=new TfrmMotorCheck(this);
        pMotorCheckDlg->m_nActiveAxis=pText->Tag;
        pMotorCheckDlg->Caption=pText->Caption;

        if(pMotorCheckDlg->ShowModal()==mrOk)
        {
                TEdit *pEdit=(TEdit *)FindComponent(pText->Hint);
                if(pEdit) pEdit->Text=pMotorCheckDlg->m_dCurrPos;
                else ShowMessage("�g�J����");
        }


        delete pMotorCheckDlg;
}
//---------------------------------------------------------------------------




void __fastcall TfrmMachineParam::m_bIsMgzUpFirsClick(TObject *Sender)
{
    TCheckBox *pChx = (TCheckBox *)Sender;
    if (pChx->Checked)
    {
        this->m_dMgzStartPos->Enabled = false;
        this->m_dMgzStartPosUpFirst->Enabled = true;
    }
    else
    {
        this->m_dMgzStartPos->Enabled = true;
        this->m_dMgzStartPosUpFirst->Enabled = false;
    }
}
//---------------------------------------------------------------------------



void __fastcall TfrmMachineParam::m_bIsUseCIMClick(TObject *Sender)
{
    if (m_bIsUseCIM->Checked == true)
    {
        frmMain->ServerCIM->Active = true;
        frmMain->AddList("CIM Start!");
    }
    else
    {
        frmMain->ServerCIM->Active = false;
        frmMain->AddList("CIM Stop!");
        frmMain->Shape3->Visible = false;
        g_eqpXML.m_CIMStatus = "0";
    }
}
//---------------------------------------------------------------------------

