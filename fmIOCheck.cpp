//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "fmIOCheck.h"
#include "math.h"
#include "iniFile.h"
#include "PCIM114GL.h"

extern PCIM114GL g_MNet;
//---------------------------------------------------------------------
#pragma resource "*.dfm" 

extern CIniFile g_IniFile;

#define MAX_DIO_PORT 8
//--------------------------------------------------------------------- 
__fastcall TIOCheckDlg::TIOCheckDlg(TComponent* AOwner)
	: TForm(AOwner)
{

}
//---------------------------------------------------------------------

void __fastcall TIOCheckDlg::timerInputTimer(TObject *Sender)
{
  TPanel *pInputPanel;
  AnsiString strComponentName;

  timerInput->Enabled=false;

  byte nPortData=0;
  int nTag=0;
  for(int nIndex2=0;nIndex2<MAX_DIO_PORT;nIndex2++)                //Port
  {
        nPortData=g_MNet.GetDIPort(nIndex2);

        for(int nIndex=0;nIndex<8;nIndex++)             //Byte
        {
                if(nIndex2<8) strComponentName.sprintf("InputPanel%d",nTag);
                else strComponentName.sprintf("Panel%d",nTag-64+3);
                pInputPanel=(TPanel *)FindComponent(strComponentName);
                if(pInputPanel==NULL) return;
                if((nPortData & (byte)(0x01<<nIndex))>0)
                        pInputPanel->Color=clLime;
                else
                        pInputPanel->Color=clGreen;
                nTag++;
        }

  }

  timerInput->Enabled=true;

}
//---------------------------------------------------------------------------

void __fastcall TIOCheckDlg::timerOutputTimer(TObject *Sender)
{
  TSpeedButton *pOutputButton;
  AnsiString strComponentName;

  timerOutput->Enabled=false;

 byte nPortData=0;
 int nTag=0;
 for(int nIndex2=0;nIndex2<MAX_DIO_PORT;nIndex2++)
 {
        nPortData=g_MNet.GetDOPort(nIndex2);
        for(int nIndex=0;nIndex<8;nIndex++)
        {
        if(nIndex2<4) strComponentName.sprintf("SpeedButton%d",nTag+1);
        else strComponentName.sprintf("OutputButton%d",nTag-32);
        pOutputButton=(TSpeedButton *)FindComponent(strComponentName);
        if(pOutputButton==NULL) return;
        if((nPortData & (byte)(0x01<<nIndex))>0)
                pOutputButton->Down=true;
        else
                pOutputButton->Down=false;
        nTag++;
        }
 }
  timerOutput->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TIOCheckDlg::OutputButton0Click(TObject *Sender)
{
  bool bSetValue;

  TSpeedButton *pOutputButton=(TSpeedButton *)Sender;
  if(pOutputButton->Down)
    bSetValue=true;
  else
    bSetValue=false;

  g_MNet.SetDO(pOutputButton->GroupIndex-1,bSetValue);  

}
//---------------------------------------------------------------------------
void __fastcall TIOCheckDlg::SetOutputCaption()
{ 

}
//---------------------------------------------------------------------------
void __fastcall TIOCheckDlg::SetInputCaption()
{


}
//---------------------------------------------------------------------------

void __fastcall TIOCheckDlg::FormCreate(TObject *Sender)
{
    AnsiString strMsg,strStatic;

    for(int nIndex=0;nIndex<95;nIndex++)
    {
        strMsg.sprintf("X%03d",nIndex);
        strStatic.sprintf("StaticText%d",nIndex+1);
        ((TStaticText *)FindComponent(strStatic))->Caption=strMsg;

        strMsg.sprintf("Y%03d",nIndex);
        strStatic.sprintf("StaticText%d",nIndex+97);
        ((TStaticText *)FindComponent(strStatic))->Caption=strMsg;
    }

}
//---------------------------------------------------------------------------


