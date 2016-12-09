//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "dir.h"
#include "systdate.h"

#include "fmMain.h"
#include "fmIOCheck.h"
#include "fmChoiceMotor.h"
#include "fmMotorCheck.h"
#include "frmManual.h"
#include "frmPrivilege.h"
#include "fmPassword.h"
#include "fmMachinParam.h"
#include "MainThread.h"
#include "fmProductParam.h"

#include "IniFile.h"
#include "PylonCCD.h"
#include "CEVision.h"
#include "CtkLedControll.h"
#include "C_GetTime.h"
#include "PCIM114GL.H"
#include "NHB300.h"
#include "ZEBEXSerial.h"
#include "RS700HASerial.h"
#include "EQPXML.h"

extern CPylonCCD *g_pCCD;
extern CEVision theVision;
extern CIniFile g_IniFile;
extern CTK_Led g_LED;
extern CMainThread *g_pMainThread;
extern bool g_bStopMainThread;
extern PCIM114GL g_MNet;
extern CNHB300 g_Scale;
extern TfmManual *fmManual;
extern CZEBEXSerial g_1DScanner;
extern RS700HASerial g_2DReader;
extern CEQPXML g_eqpXML;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;

//CGetRealTimeValueThread.h start
//---------------------------------------------------------------------------
class CGetRealTimeValueThread : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall CGetRealTimeValueThread(bool CreateSuspended);
};

CGetRealTimeValueThread *g_pGetRealTimeValueThread;
bool g_bStopGetRealTimeValueThread = false;

//CGetRealTimeValueThread.cpp start
//---------------------------------------------------------------------------
__fastcall CGetRealTimeValueThread::CGetRealTimeValueThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall CGetRealTimeValueThread::Execute()
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);
	static C_GetTime tm2MS(EX_SCALE::TIME_1MS, false);

    g_bStopGetRealTimeValueThread = false;
    AnsiString strtemp1;
    AnsiString strtemp2;
	AnsiString strCommand;
	bool btmRUN = false;

    while (true)
	{
		if (g_bStopGetRealTimeValueThread) break;
        //--- Query RS232 Value

        if (g_pMainThread->m_listReaderTX.size()>0)
	    {
		    strCommand = g_pMainThread->m_listReaderTX.front();
		    g_pMainThread->m_listReaderTX.pop_front();

		    if (strCommand == "READ_1D_CODE")
		    {
                g_1DScanner.Disable();
			    ::Sleep(100);
			    g_1DScanner.Sleep();
                ::Sleep(100);
			    g_1DScanner.Wakeup();
			    ::Sleep(2500);
			    g_1DScanner.Enable();
			    tm1MS.timeStart(5000);
			    btmRUN = true;
		    }
		    if (strCommand == "SHUTDOWN_1D_CODE")
		    {
			    g_1DScanner.Disable();
			    ::Sleep(100);
			    g_1DScanner.Sleep();
                ::Sleep(100);
			    g_pMainThread->m_list1DReaderRX.push_back("SHUTDOWN_1D_CODE_OK");
		    }
        }
        if (btmRUN == true) // timeout process
        {
            if (tm1MS.timeUp() && g_pMainThread->m_list1DReaderRX.size() == 0)
            {
                g_pMainThread->m_list1DReaderRX.push_back("READ_1D_CODE_NG");
                btmRUN = false;
            }
        }

        //---Query Mag 1D Reader
        strtemp1 = "Error!";
        if (g_1DScanner.m_bInitOK) strtemp1 = g_1DScanner.GetData();
        if (strtemp1 != "Error!")
        {
            frmMain->AddList("1D Reader Read: " + strtemp1);
            g_eqpXML.m_strMagzin1DCode = strtemp1;
			g_eqpXML.SendEventReport("125");
			g_pMainThread->m_list1DReaderRX.push_back("READ_1D_CODE_OK");
			btmRUN = false;
        }
        ::Sleep(100);

        //---Query Substrate 2D Reader
        strtemp2 = "Error!";
        if (g_2DReader.m_bInitOK) strtemp2 = g_2DReader.GetData();
        if (strtemp2 != "Error!")
        {
            frmMain->AddList("2D Reader Read: " + strtemp2);
            g_eqpXML.m_strSubstrate2DCode = strtemp2;
        }
        ::Sleep(100);
    }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
	: TForm(Owner)
{
	m_nUserLevel = 0;
    m_bISLoaderConveyerDownRun = false;
    
    
}
//---------------------------------------------------------------------------

#pragma region MainCommonFunction
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
	g_pMainThread = new CMainThread(false);

    g_pGetRealTimeValueThread = new CGetRealTimeValueThread(false);

    if (!FileExists("C:\\Product_Data\\")) _mkdir("C:\\Product_Data\\");

	g_IniFile.MachineFile(true);
	g_IniFile.ProductFile(g_IniFile.m_strLastFileName.c_str(), true);

	Caption = g_IniFile.m_strLastFileName;
	//GetVersion();

	g_LED.OpenPort(1);
	g_Scale.OpenPort(2);

	SetLEDDimmer();

	if (Application->MessageBox("啟用 CCD Camera?", "Look", MB_OKCANCEL) == IDOK)
	{
		g_pCCD = new CPylonCCD(false);
		if (g_pCCD != NULL)
		{
			g_pCCD->OnGrabComplete[0] = OnGrabComplete;
			//g_pCCD->StartGrab(0);
			//g_pCCD->OnGrabComplete[1]=OnGrabComplete;
			//g_pCCD->StartGrab(0);
		}
	}

	theVision.LoadTool(g_IniFile.GetFileNameWithNewExt(Caption.c_str(), "cev").c_str(), "Dummy");

    //g_eqpXML initial
    g_eqpXML.m_bOnLine = true;
    g_eqpXML.StartProcess = frmMain->StartProcess;
    g_eqpXML.OpenFile = frmMain->OpenFilebyCIM;
    g_eqpXML.m_EqpStatus = 'I';

    // IniFile boot CIM 
    if (g_IniFile.m_bIsUseCIM == true)
    {
        ServerCIM->Active = true;
        AddList("CIM Start!");
    }
    else
    {
        ServerCIM->Active = false;
        AddList("CIM Stop!");
        g_eqpXML.m_CIMStatus = "0";
    }

    //Product Parameter setting
    TrackBar2->Position = g_IniFile.m_dFluxTankAirPressure;
    TrackBar3->Position = g_IniFile.m_dSprayerAirPressure;

    m_bStopLoader->Checked = g_IniFile.m_bStopLoader;
    
    timerAutoCleanSprayLane->Enabled = g_IniFile.m_bUseAutoCleanSprayLane;

    m_dMarkScore0->Text = FormatFloat("0.000",g_IniFile.m_dMarkScore0);

    //Reset Scale
    g_Scale.SetZero();

    //Reset1D Reader
    g_1DScanner.Disable();
    ::Sleep(100);
    g_1DScanner.Sleep();
    ::Sleep(100);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	g_bStopMainThread = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    CanClose = false;
    if (Application->MessageBox("是否要離開?", "注意", MB_OKCANCEL) == IDOK)
    {
        if (Application->MessageBox("離開前是否要存檔?", "注意", MB_OKCANCEL) == IDOK)
        Save1Click(Sender);
        CanClose = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SetLEDDimmer()
{

	TrackBar1->Position = g_IniFile.m_nLEDDimmer[0];
	//TrackBar2->Position=g_IniFile.m_nLEDDimmer[1];
}
//---------------------------------------------------------------------------
void  TfrmMain::OnGrabComplete(int nIndex, bool bResult)
{
	theVision.m_ImageBW8.SetImagePtr(g_pCCD->m_pCamera[nIndex].m_nImageSizeX,
		g_pCCD->m_pCamera[nIndex].m_nImageSizeY, g_pCCD->m_pCamera[nIndex].m_pImgBuf,
		g_pCCD->m_pCamera[nIndex].m_nImageSizeX * 8);

	theVision.m_ImageTmpBW8.SetSize(g_pCCD->m_pCamera[nIndex].m_nImageSizeX, g_pCCD->m_pCamera[nIndex].m_nImageSizeY);

	theVision.RotateImage(0.0);

	frmMain->RefreshImage();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::RefreshImage()
{

	double nScaleTempX = 1.0;
	double nScaleTempY = 1.0;


	frmMain->ImagePaintBox->Width = theVision.m_ImageTmpBW8.GetWidth()*theVision.m_dScaleSizeX;
	frmMain->ImagePaintBox->Height = theVision.m_ImageTmpBW8.GetHeight()*theVision.m_dScaleSizeY;

	RECT RectImageSize = { frmMain->ImagePaintBox->Left, frmMain->ImagePaintBox->Top,
		frmMain->ImagePaintBox->Left + frmMain->ImagePaintBox->Width ,
		frmMain->ImagePaintBox->Top + frmMain->ImagePaintBox->Height };

	::InvalidateRect(frmMain->ScrollBox1->Handle, &RectImageSize, false);

}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SetPrivilege(int nLevel)
{
	switch (nLevel)
	{
	case 0:
		Parameter1->Enabled = false;
		Operate1->Enabled = false;
		Exit1->Enabled = false;


		break;
	case 1:
		Parameter1->Enabled = true;
		Operate1->Enabled = true;
		Exit1->Enabled = true;

		break;
	case 2:
		Parameter1->Enabled = true;
		Operate1->Enabled = true;
		Exit1->Enabled = true;

		break;
	}


}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::ReadCaptionFile(TForm *pForm, int nLanguage)
{
	AnsiString strFile;
	TIniFile *pIniFile;

	if (nLanguage>0) strFile.sprintf("%s%s", "C:\\", "Caption_C83_ENG.ini");
	else strFile.sprintf("%s%s", "C:\\", "Caption_C83.ini");

	const char *pSection = pForm->Name.c_str();

	pIniFile = new TIniFile(strFile);

	TStringList *TempList = new TStringList;

	pIniFile->ReadSection(pSection, TempList);

	AnsiString strClass;
	AnsiString strName;
	AnsiString strValue;

	for (int nIndex = 0; nIndex<TempList->Count; nIndex++)
	{
		strName = TempList->Strings[nIndex];
		strValue = pIniFile->ReadString(pSection, strName, "NA");

		if (!pForm->FindComponent(strName)) continue;
		strClass = pForm->FindComponent(strName)->ClassName();

		if (strClass == "TLabel") ((TLabel *)pForm->FindComponent(strName))->Caption = strValue;
		else if (strClass == "TToolButton") ((TToolButton *)pForm->FindComponent(strName))->Caption = strValue;
		else if (strClass == "TSpeedButton") ((TSpeedButton *)pForm->FindComponent(strName))->Caption = strValue;
		else if (strClass == "TBitBtn") ((TBitBtn *)pForm->FindComponent(strName))->Caption = strValue;
		else if (strClass == "TGroupBox") ((TGroupBox *)pForm->FindComponent(strName))->Caption = strValue;
		else if (strClass == "TCheckBox") ((TCheckBox *)pForm->FindComponent(strName))->Caption = strValue;
		else if (strClass == "TStaticText") ((TStaticText *)pForm->FindComponent(strName))->Caption = strValue;
		else if (strClass == "TButton") ((TButton *)pForm->FindComponent(strName))->Caption = strValue;
		else if (strClass == "TTabSheet") ((TTabSheet *)pForm->FindComponent(strName))->Caption = strValue;
		else if (strClass == "TPanel") ((TPanel *)pForm->FindComponent(strName))->Caption = strValue;

	}


	delete TempList;


	delete pIniFile;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::AddList(AnsiString strMessage)
{
	listHistory->AddItem(TimeToStr(Time()) + "-->" + strMessage, NULL);
	listHistory->ItemIndex = listHistory->Count - 1;


	g_IniFile.AddLog(strMessage.c_str(), strMessage.Length());

}
//---------------------------------------------------------------------------
bool TfrmMain::StartProcess(bool bStart)
{
	if(bStart)
	{
		g_pMainThread->m_bIsStartProcessbyCIM = true;
        g_pMainThread->m_listLog.push_back("收到CIM回應 START，機台開始啟動...");
	}
	else
	{
		g_pMainThread->m_bIsStopProcessbyCIM = true;
        g_pMainThread->m_listLog.push_back("收到CIM回應 STOP，機台禁止啟動...");
	}
	return true;
}
//---------------------------------------------------------------------------
bool TfrmMain::OpenFilebyCIM(AnsiString strFileName)
{
    if (FileExists(strFileName))
    {
        g_IniFile.MachineFile(true);
		g_IniFile.ProductFile(strFileName.c_str(), true);

        g_IniFile.m_strLastFileName = strFileName;
        frmMain->Caption = g_IniFile.m_strLastFileName;

		//Set Pressure
		g_Motion.SetAO(0, g_IniFile.m_dFluxTankAirPressure);
		g_Motion.SetAO(1, g_IniFile.m_dSprayerAirPressure);

		theVision.LoadTool(g_IniFile.GetFileNameWithNewExt(frmMain->Caption.c_str(), "cev").c_str(), "Dummy");
	    return true;
    }
    else return false;
}
//---------------------------------------------------------------------------
#pragma endregion

#pragma region Socket
void __fastcall TfrmMain::ServerCIMClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
    g_eqpXML.StartComm(Socket);
    AddList("CIM Connected!!");
    Shape3->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ServerCIMClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
    g_eqpXML.EndComm();
    AddList("CIM Disconnected!!");
    Shape3->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ServerCIMClientError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
    AddList("CIM SocketEror");
    Socket->Close();
    Shape3->Brush->Color = clRed;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ServerCIMClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
    //AddList("CIM Read");
    //g_pMainThread->m_ActionLog.push_back(g_pMainThread->AddTimeString("[ServerCIM]CIM Read"));
    Shape3->Brush->Color = clYellow;
    g_eqpXML.ProcessCIMstr();
}
//---------------------------------------------------------------------------
#pragma endregion

#pragma region MainTimer
void __fastcall TfrmMain::timerCommTimer(TObject *Sender)
{
	if (g_pMainThread->m_listTX.size()>0)
	{
		bool bRet;
		AnsiString strCommand = g_pMainThread->m_listTX.front();
		g_pMainThread->m_listTX.pop_front();
		AddList(strCommand);

		if (strCommand == "PROCESS_CCD")
		{
            float dAvg = 0;
            ImgPixelAverage(&theVision.m_roiMark[0], dAvg);

            if (dAvg > g_IniFile.m_dMarkScore0) bRet = true;
            else bRet = false;

			if (bRet) g_pMainThread->m_listCCDRX.push_back("PROCESS_CCD_OK");
			else g_pMainThread->m_listCCDRX.push_back("PROCESS_CCD_NG");
		}
	}

    if (g_Motion.GetDI(DI::LoaderOutMgzRollOut))
    {
        g_Motion.SetDO(DO::LoaderConveyerDown, true);
        m_bISLoaderConveyerDownRun = true;
    }
    else if (m_bISLoaderConveyerDownRun == true)
    {
        g_Motion.SetDO(DO::LoaderConveyerDown, false);
        m_bISLoaderConveyerDownRun = false;
    }

    if (g_Motion.GetDI(DI::LoaderClamperRelease)) g_Motion.SetDO(DO::LoaderClamper, true);

    //ShowNow
    TShape* shapeShowBox;
    AnsiString strComponentName;
    for (int nX=0;nX<4;nX++)
    {
        strComponentName.sprintf("Shape%02d", nX);
        shapeShowBox=(TShape *)FindComponent(strComponentName);
        if (g_pMainThread->m_arraybShape[nX] == true) shapeShowBox->Brush->Color = clYellow;
        else if (g_pMainThread->m_arraybShape[nX] == false) shapeShowBox->Brush->Color = clGreen;
    }

    //Lock Function Test
    if (g_pMainThread->m_bIsAutoMode)
    {
        SpeedButton1->Enabled = false;
        SpeedButton3->Enabled = false;
        SpeedButton5->Enabled = false;
        SpeedButton4->Enabled = false;
        SpeedButton6->Enabled = false;
        SpeedButton7->Enabled = false;
        SpeedButton8->Enabled = false;
        SpeedButton9->Enabled = false;
        SpeedButton10->Enabled = false;
    }
    else
    {
        SpeedButton1->Enabled = true;
        SpeedButton3->Enabled = true;
        SpeedButton5->Enabled = true;
        SpeedButton4->Enabled = true;
        SpeedButton6->Enabled = true;
        SpeedButton7->Enabled = true;
        SpeedButton8->Enabled = true;
        SpeedButton9->Enabled = true;
        SpeedButton10->Enabled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::timerMessageTimer(TObject *Sender)
{
	static int nErrorCode = 0;

	timerMessage->Enabled = false;

	//Caption = DateTimeToStr(Now());

	if (tm1MSLogOut.timeDevEnd()>3600000)
	{
		SetPrivilege(0);
		tm1MSLogOut.timeDevStart();
	}
    //--Flux Lifetime---
    if (g_pMainThread->tm1MSFluxLifeTime.timeDevEnd() < 604800000)
    {
        double dTimerDEnd = (double)g_pMainThread->tm1MSFluxLifeTime.timeDevEnd();
        int nDD = (int)(dTimerDEnd / (24*60*60*1000));
        dTimerDEnd = dTimerDEnd - (nDD*(24*60*60*1000));
        int nHH = (int)(dTimerDEnd / (60*60*1000));
        dTimerDEnd = dTimerDEnd - (nHH*(60*60*1000));
        int nmm = (int)(dTimerDEnd / (60*1000));
        dTimerDEnd = dTimerDEnd - (nmm*(60*1000));
        int nss = (int)(dTimerDEnd / (1000));
        dTimerDEnd = dTimerDEnd - (nss*(1000));
        int nms = dTimerDEnd;

        AnsiString strFluxLifetime;
        strFluxLifetime.sprintf("Flux Life Time(168H): %02d:%02d:%02d:%02d", nDD, nHH, nmm, nss);
        labFluxLifetime->Caption = strFluxLifetime;
    }
    else
    {
        labFluxLifetime->Caption = "Flux Life Time(168H): 07:00:00:00";
        g_pMainThread->m_bIsFluxLifetimeTimeUp = true;
        labFluxLifetime->Color = clRed;
    }
    //--Strip Count and Show---
    labRunningCounts->Caption = "Running Counts: " + IntToStr(g_pMainThread->m_nStripCount);
    if (g_pMainThread->m_bIsStripCountNeedCopy == true)
    {
        g_pMainThread->m_bIsStripCountNeedCopy = false;
        labLastPassCounts->Caption = "Last Pass Counts: " + IntToStr(g_pMainThread->m_nStripCount);
        AddList("Last Pass Counts: " + IntToStr(g_pMainThread->m_nStripCount));
        g_pMainThread->m_nStripCount = 0;
        g_pMainThread->m_nStripCountForAutoFillFlux = 0;
    }
    //--UPUtime to show---
    if (g_pMainThread->m_listUPUTime.size()>0)
    {
        AnsiString strUPU = FormatFloat("CycleTime 0.00", g_pMainThread->m_listUPUTime.front()/ 1000.0) + " Sec";
        labUPU->Caption = strUPU;
        g_pMainThread->m_listUPUTime.pop_front();
    }
	//--Thread Log---
	if (g_pMainThread->m_listLog.size()>0)
	{
		AnsiString strLog = g_pMainThread->m_listLog.front();
		AddList(strLog);

		g_pMainThread->m_listLog.pop_front();
	}
	//--- Log
	if (theVision.m_listLog.size()>0)
	{
		AnsiString strLog = theVision.m_listLog.front();
		AddList(strLog);

		theVision.m_listLog.pop_front();

	}

	//---Error Code
	if (g_IniFile.m_nErrorCode>0 && (nErrorCode != g_IniFile.m_nErrorCode))
	{
		//if(m_pMessageDlg)
		{
            //process in Machine
			AnsiString strMsg = g_IniFile.GetErrorString("SYSTEM", g_IniFile.m_nErrorCode);
			AddList(strMsg);
			//process in CIM
			AnsiString strMsgCIM = g_IniFile.GetErrorString("SYSTEM", g_IniFile.m_nErrorCode,1);
			AnsiString strCode;
			strCode.sprintf("%04d", g_IniFile.m_nErrorCode);
			g_eqpXML.SendAlarmMessage(strCode.c_str(), strMsgCIM.c_str());
		}
	}

	if (g_Motion.GetDO(DO::Buzzer)) listHistory->Color = clRed;
	else listHistory->Color = clBlack;

	//----Motion
	if (!g_pMainThread->m_bIsAutoMode)
	{

	}

	nErrorCode = g_IniFile.m_nErrorCode;

    //--Idle Run Down---
    if (ServerCIM->Active == true && g_pMainThread->m_bIsHomeDone == true)
    {
        if (g_IniFile.m_nErrorCode > 0 && g_IniFile.m_nErrorCode < 1000 && g_eqpXML.m_EqpStatus !='D')
        {
            g_eqpXML.m_EqpStatus='D';
            g_eqpXML.SendEventReport("1");
        }
        else if (g_DIO.ReadDOBit(DO::StartBtnLamp) && g_eqpXML.m_EqpStatus !='R')
        {
            g_eqpXML.m_EqpStatus='R';
            g_eqpXML.SendEventReport("1");
        }
        else if (g_IniFile.m_nErrorCode == 0 && g_eqpXML.m_EqpStatus !='I' && !g_DIO.ReadDOBit(DO::StartBtnLamp))
        {
            g_eqpXML.m_EqpStatus='I';
            g_eqpXML.SendEventReport("1");
        }
    }

    //---Renew CIM signal
    Shape3->Brush->Color = clLime;

    //---Renew lab
    lab1DShow->Caption = "Read: " + g_eqpXML.m_strMagzin1DCode;

	timerMessage->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::timerScaleTimer(TObject *Sender)
{
	double dd = g_Scale.GetWeight();
	if (dd != -999.0) labelScale->Caption = FormatFloat("0.0g", dd);
	else labelScale->Caption = "NOT_VALID";
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::timerAutoCleanSprayLaneTimer(TObject *Sender)
{
    timerAutoCleanSprayLane->Enabled = false;

    TDateTime DT = TDateTime::CurrentDateTime();
    AnsiString strNow = DT.FormatString("hh:nn").c_str();

    if (strNow != "00:00" && (strNow == g_IniFile.m_strAutoCleanSprayLaneDateTime[0]
        || strNow == g_IniFile.m_strAutoCleanSprayLaneDateTime[1]
        || strNow == g_IniFile.m_strAutoCleanSprayLaneDateTime[2]))
    {
        if (g_pMainThread->m_bIsHomeDone && !g_pMainThread->m_bIsAutoMode)
        {
            g_pMainThread->m_bIsSprayerLock = true;
            g_pMainThread->m_bStartCleanSpray = true;
            g_pMainThread->nThreadIndex[16] = 0;
        }
        else g_IniFile.m_nErrorCode = 716;
        g_IniFile.m_bUsePreAutoWeightScale = true;
    }

    timerAutoCleanSprayLane->Enabled = true;
}
//---------------------------------------------------------------------------
#pragma endregion

#pragma region MainMenu
void __fastcall TfrmMain::Open1Click(TObject *Sender)
{
	AnsiString strMsg;
	if (Application->MessageBoxA("開檔前是否要儲存目前檔案?", "Confirm", MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
	{

		g_IniFile.MachineFile(false);
		g_IniFile.ProductFile(Caption.c_str(), false);

		theVision.SaveTool(g_IniFile.GetFileNameWithNewExt(Caption.c_str(), "cev").c_str(), "Dummy");
		ShowMessage("檔案儲存完成!");
	}

	OpenDialog1->DefaultExt = "INI";
	OpenDialog1->FileName = "*.ini";

	if (OpenDialog1->Execute())
	{
		g_IniFile.MachineFile(true);
		g_IniFile.ProductFile(OpenDialog1->FileName.c_str(), true);

        g_IniFile.m_strLastFileName = OpenDialog1->FileName;
		Caption = g_IniFile.m_strLastFileName;

		//Set Pressure
		g_Motion.SetAO(0, g_IniFile.m_dFluxTankAirPressure);
		g_Motion.SetAO(1, g_IniFile.m_dSprayerAirPressure);

		theVision.LoadTool(g_IniFile.GetFileNameWithNewExt(Caption.c_str(), "cev").c_str(), "Dummy");
	}

	SetLEDDimmer();


}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Save1Click(TObject *Sender)
{
	if (Application->MessageBoxA("確定要存檔?", "Confirm", MB_ICONQUESTION | MB_OKCANCEL) == IDCANCEL) return;

	g_IniFile.MachineFile(false);
	g_IniFile.ProductFile(Caption.c_str(), false);

	theVision.SaveTool(g_IniFile.GetFileNameWithNewExt(Caption.c_str(), "cev").c_str(), "Dummy");

	ShowMessage("檔案儲存完成!");
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Saveas1Click(TObject *Sender)
{
	SaveDialog1->DefaultExt = "ini";
	if (SaveDialog1->Execute())
	{

		if (!FileExists("C:\\Product_Data\\")) _mkdir("C:\\Product_Data\\");
		g_IniFile.m_strLastFileName = SaveDialog1->FileName;
		Caption = SaveDialog1->FileName;
		g_IniFile.MachineFile(false);
		g_IniFile.ProductFile(SaveDialog1->FileName.c_str(), false);

		theVision.SaveTool(g_IniFile.GetFileNameWithNewExt(Caption.c_str(), "cev").c_str(), "Dummy");

		//if (g_IniFile.m_nLanguageMode>0) ShowMessage("Save Done");
		//else ShowMessage("存檔完畢");
		ShowMessage("存檔完畢");
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Load1Click(TObject *Sender)
{
	int nTag = ((TMenuItem *)Sender)->Tag;
	OpenPictureDialog1->DefaultExt = "bmp";
	if (OpenPictureDialog1->Execute())
	{
		theVision.m_ImageTmpBW8.Load(OpenPictureDialog1->FileName.c_str());
		theVision.m_ImageSizeX = theVision.m_ImageTmpBW8.GetWidth();
		theVision.m_ImageSizeY = theVision.m_ImageTmpBW8.GetHeight();
	}

	RefreshImage();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Save2Click(TObject *Sender)
{
	if (SavePictureDialog1->Execute())
	{
		theVision.m_ImageTmpBW8.Save(SavePictureDialog1->FileName.c_str());
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Machine1Click(TObject *Sender)
{
	TfrmMachineParam *pMachineDlg = new TfrmMachineParam(this);

	bool bRead = true;

	AnsiString strCtl;

	for (int nIndex = 0; nIndex<9; nIndex++)
	{
		DDX_Float(bRead, g_IniFile.m_dACCSpeed[nIndex + 4], (TEdit *)pMachineDlg->FindComponent(strCtl.sprintf("editAcc%d", nIndex + 1)));
		DDX_Float(bRead, g_IniFile.m_dDECSpeed[nIndex + 4], (TEdit *)pMachineDlg->FindComponent(strCtl.sprintf("editDec%d", nIndex + 1)));
		DDX_Float(bRead, g_IniFile.m_dJogSpeed[nIndex + 4], (TEdit *)pMachineDlg->FindComponent(strCtl.sprintf("editJogSpeed%d", nIndex + 1)));
		DDX_Float(bRead, g_IniFile.m_dWorkSpeed[nIndex + 4], (TEdit *)pMachineDlg->FindComponent(strCtl.sprintf("editWorkSpeed%d", nIndex + 1)));
	}

	DDX_Float(bRead, g_IniFile.m_dMgzStartPos, pMachineDlg->m_dMgzStartPos);
    DDX_Float(bRead, g_IniFile.m_dMgzStartPosUpFirst, pMachineDlg->m_dMgzStartPosUpFirst);
	DDX_Float(bRead, g_IniFile.m_dMgzPitch, pMachineDlg->m_dMgzPitch);
	DDX_Int(bRead, g_IniFile.m_nMgzSize, pMachineDlg->m_nMgzSize);

	DDX_Float(bRead, g_IniFile.m_dScaleSprayPosX[0], pMachineDlg->m_dScaleSprayPosX0);
	DDX_Float(bRead, g_IniFile.m_dScaleSprayPosY[0], pMachineDlg->m_dScaleSprayPosY0);
	DDX_Float(bRead, g_IniFile.m_dScaleSprayPosZ[0], pMachineDlg->m_dScaleSprayPosZ0);
    DDX_Float(bRead, g_IniFile.m_dScaleSprayPosX[1], pMachineDlg->m_dScaleSprayPosX1);
	DDX_Float(bRead, g_IniFile.m_dScaleSprayPosY[1], pMachineDlg->m_dScaleSprayPosY1);
	DDX_Float(bRead, g_IniFile.m_dScaleSprayPosZ[1], pMachineDlg->m_dScaleSprayPosZ1);
    DDX_Float(bRead, g_IniFile.m_dScaleSprayTime[1], pMachineDlg->m_dScaleSprayTime1);
    DDX_Int(bRead, g_IniFile.m_nScaleSprayTimes[1], pMachineDlg->m_nScaleSprayTimes1);
    DDX_Float(bRead, g_IniFile.m_dScaleSprayDelayTime, pMachineDlg->m_dScaleSprayDelayTime);

    DDX_Float(bRead, g_IniFile.m_dLDYUnLoadClamperAlarm, pMachineDlg->m_dLDYUnLoadClamperAlarm);
    DDX_Float(bRead, g_IniFile.m_dSprayLaneAlarmX[0], pMachineDlg->m_dSprayLaneAlarmX0);
    DDX_Float(bRead, g_IniFile.m_dSprayLaneAlarmY[0], pMachineDlg->m_dSprayLaneAlarmY0);
    DDX_Float(bRead, g_IniFile.m_dSprayLaneAlarmX[1], pMachineDlg->m_dSprayLaneAlarmX1);
    DDX_Float(bRead, g_IniFile.m_dSprayLaneAlarmY[1], pMachineDlg->m_dSprayLaneAlarmY1);
    DDX_Float(bRead, g_IniFile.m_dSprayLaneAlarmZ, pMachineDlg->m_dSprayLaneAlarmZ);

    DDX_String(bRead, g_IniFile.m_strAutoCleanSprayLaneDateTime[0], pMachineDlg->m_strAutoCleanSprayLaneDateTime0);
    DDX_String(bRead, g_IniFile.m_strAutoCleanSprayLaneDateTime[1], pMachineDlg->m_strAutoCleanSprayLaneDateTime1);
    DDX_String(bRead, g_IniFile.m_strAutoCleanSprayLaneDateTime[2], pMachineDlg->m_strAutoCleanSprayLaneDateTime2);

	DDX_Check(bRead, g_IniFile.m_bForceEject, pMachineDlg->m_bForceEject);
    DDX_Check(bRead, g_IniFile.m_bUsePreAutoWeightScale, pMachineDlg->m_bUsePreAutoWeightScale);
    DDX_Check(bRead, g_IniFile.m_bUseUnClampAutoWeightScale, pMachineDlg->m_bUseUnClampAutoWeightScale);
    DDX_Check(bRead, g_IniFile.m_bUseAutoCleanSprayLane, pMachineDlg->m_bUseAutoCleanSprayLane);
    DDX_Check(bRead, g_IniFile.m_bIsMgzUpFirst, pMachineDlg->m_bIsMgzUpFirst);
    DDX_Check(bRead, g_IniFile.m_bIsUseCIM, pMachineDlg->m_bIsUseCIM);
    DDX_Check(bRead, g_IniFile.m_bIsUseRightLCPusher, pMachineDlg->m_bIsUseRightLCPusher);
    DDX_Check(bRead, g_IniFile.m_bIsUse1DReader, pMachineDlg->m_bIsUse1DReader);

    DDX_Radio(bRead, g_IniFile.m_nRailOption, pMachineDlg->m_nRailOption);

    if (g_IniFile.m_bIsMgzUpFirst)
    {
        pMachineDlg->m_dMgzStartPos->Enabled = false;
        pMachineDlg->m_dMgzStartPosUpFirst->Enabled = true;
    }
    else
    {
        pMachineDlg->m_dMgzStartPos->Enabled = true;
        pMachineDlg->m_dMgzStartPosUpFirst->Enabled = false;
    }

    if (m_nUserLevel < 2)
    {
        pMachineDlg->m_dLDYUnLoadClamperAlarm->Enabled = false;
        pMachineDlg->m_dSprayLaneAlarmX0->Enabled = false;
        pMachineDlg->m_dSprayLaneAlarmY0->Enabled = false;
        pMachineDlg->m_dSprayLaneAlarmX1->Enabled = false;
        pMachineDlg->m_dSprayLaneAlarmY1->Enabled = false;
        pMachineDlg->m_dSprayLaneAlarmZ->Enabled = false;
    }

    while (1)
    {
        if (pMachineDlg->ShowModal() == mrOk)
        {
            bRead = true;
            bool bIsDateTimePass[3] = {false, false, false};

            TStringList *StrList0 = SplitString(pMachineDlg->m_strAutoCleanSprayLaneDateTime0->Text, ":");
            if (StrList0->Count == 2)
            {
                if ((StrList0->operator [](0).ToInt() < 24 && StrList0->operator [](0).ToInt() >=0)
                    && (StrList0->operator [](1).ToInt() < 60 && StrList0->operator [](1).ToInt() >=0))
                {
                    bIsDateTimePass[0] = true;
                }
            }
            delete StrList0;
            TStringList *StrList1 = SplitString(pMachineDlg->m_strAutoCleanSprayLaneDateTime1->Text, ":");
            if (StrList1->Count == 2)
            {
                if ((StrList1->operator [](0).ToInt() < 24 && StrList1->operator [](0).ToInt() >=0)
                    && (StrList1->operator [](1).ToInt() < 60 && StrList1->operator [](1).ToInt() >=0))
                {
                    bIsDateTimePass[1] = true;
                }
            }
            delete StrList1;
            TStringList *StrList2 = SplitString(pMachineDlg->m_strAutoCleanSprayLaneDateTime1->Text, ":");
            if (StrList2->Count == 2)
            {
                if ((StrList2->operator [](0).ToInt() < 24 && StrList2->operator [](0).ToInt() >=0)
                    && (StrList2->operator [](1).ToInt() < 60 && StrList2->operator [](1).ToInt() >=0))
                {
                    bIsDateTimePass[2] = true;
                }
            }
            delete StrList2;

            if (!bIsDateTimePass[0] || !bIsDateTimePass[1] || !bIsDateTimePass[2])
            {
                Application->MessageBoxA("自動清洗流道時間設定錯誤!!","Confirm",MB_OK);
            }
            else
            {
                bRead = false;
            }

            if (bRead == false)
	        {
		        for (int nIndex = 0; nIndex<9; nIndex++)
		        {
			        DDX_Float(bRead, g_IniFile.m_dACCSpeed[nIndex + 4], (TEdit *)pMachineDlg->FindComponent(strCtl.sprintf("editAcc%d", nIndex + 1)));
			        DDX_Float(bRead, g_IniFile.m_dDECSpeed[nIndex + 4], (TEdit *)pMachineDlg->FindComponent(strCtl.sprintf("editDec%d", nIndex + 1)));
			        DDX_Float(bRead, g_IniFile.m_dJogSpeed[nIndex + 4], (TEdit *)pMachineDlg->FindComponent(strCtl.sprintf("editJogSpeed%d", nIndex + 1)));
			        DDX_Float(bRead, g_IniFile.m_dWorkSpeed[nIndex + 4], (TEdit *)pMachineDlg->FindComponent(strCtl.sprintf("editWorkSpeed%d", nIndex + 1)));
		        }

		        DDX_Float(bRead, g_IniFile.m_dMgzStartPos, pMachineDlg->m_dMgzStartPos);
                DDX_Float(bRead, g_IniFile.m_dMgzStartPosUpFirst, pMachineDlg->m_dMgzStartPosUpFirst);
		        DDX_Float(bRead, g_IniFile.m_dMgzPitch, pMachineDlg->m_dMgzPitch);
		        DDX_Int(bRead, g_IniFile.m_nMgzSize, pMachineDlg->m_nMgzSize);

		        DDX_Float(bRead, g_IniFile.m_dScaleSprayPosX[0], pMachineDlg->m_dScaleSprayPosX0);
	            DDX_Float(bRead, g_IniFile.m_dScaleSprayPosY[0], pMachineDlg->m_dScaleSprayPosY0);
	            DDX_Float(bRead, g_IniFile.m_dScaleSprayPosZ[0], pMachineDlg->m_dScaleSprayPosZ0);
                DDX_Float(bRead, g_IniFile.m_dScaleSprayPosX[1], pMachineDlg->m_dScaleSprayPosX1);
	            DDX_Float(bRead, g_IniFile.m_dScaleSprayPosY[1], pMachineDlg->m_dScaleSprayPosY1);
	            DDX_Float(bRead, g_IniFile.m_dScaleSprayPosZ[1], pMachineDlg->m_dScaleSprayPosZ1);
                DDX_Float(bRead, g_IniFile.m_dScaleSprayTime[1], pMachineDlg->m_dScaleSprayTime1);
                DDX_Int(bRead, g_IniFile.m_nScaleSprayTimes[1], pMachineDlg->m_nScaleSprayTimes1);
                DDX_Float(bRead, g_IniFile.m_dScaleSprayDelayTime, pMachineDlg->m_dScaleSprayDelayTime);

                DDX_Float(bRead, g_IniFile.m_dLDYUnLoadClamperAlarm, pMachineDlg->m_dLDYUnLoadClamperAlarm);
                DDX_Float(bRead, g_IniFile.m_dSprayLaneAlarmX[0], pMachineDlg->m_dSprayLaneAlarmX0);
                DDX_Float(bRead, g_IniFile.m_dSprayLaneAlarmY[0], pMachineDlg->m_dSprayLaneAlarmY0);
                DDX_Float(bRead, g_IniFile.m_dSprayLaneAlarmX[1], pMachineDlg->m_dSprayLaneAlarmX1);
                DDX_Float(bRead, g_IniFile.m_dSprayLaneAlarmY[1], pMachineDlg->m_dSprayLaneAlarmY1);
                DDX_Float(bRead, g_IniFile.m_dSprayLaneAlarmZ, pMachineDlg->m_dSprayLaneAlarmZ);

                DDX_String(bRead, g_IniFile.m_strAutoCleanSprayLaneDateTime[0], pMachineDlg->m_strAutoCleanSprayLaneDateTime0);
                DDX_String(bRead, g_IniFile.m_strAutoCleanSprayLaneDateTime[1], pMachineDlg->m_strAutoCleanSprayLaneDateTime1);
                DDX_String(bRead, g_IniFile.m_strAutoCleanSprayLaneDateTime[2], pMachineDlg->m_strAutoCleanSprayLaneDateTime2);

		        DDX_Check(bRead, g_IniFile.m_bForceEject, pMachineDlg->m_bForceEject);
                DDX_Check(bRead, g_IniFile.m_bUsePreAutoWeightScale, pMachineDlg->m_bUsePreAutoWeightScale);
                DDX_Check(bRead, g_IniFile.m_bUseUnClampAutoWeightScale, pMachineDlg->m_bUseUnClampAutoWeightScale);
                DDX_Check(bRead, g_IniFile.m_bUseAutoCleanSprayLane, pMachineDlg->m_bUseAutoCleanSprayLane);
                DDX_Check(bRead, g_IniFile.m_bIsMgzUpFirst, pMachineDlg->m_bIsMgzUpFirst);
                DDX_Check(bRead, g_IniFile.m_bIsUseCIM, pMachineDlg->m_bIsUseCIM);
                DDX_Check(bRead, g_IniFile.m_bIsUseRightLCPusher, pMachineDlg->m_bIsUseRightLCPusher);
                DDX_Check(bRead, g_IniFile.m_bIsUse1DReader, pMachineDlg->m_bIsUse1DReader);

                DDX_Radio(bRead, g_IniFile.m_nRailOption, pMachineDlg->m_nRailOption);

                //Set timer
                timerAutoCleanSprayLane->Enabled = g_IniFile.m_bUseAutoCleanSprayLane;

                //Reset FluxLifetime
                if (pMachineDlg->m_bIsResetFluxLifetime->Checked)
                {
                    g_pMainThread->m_bIsFluxLifetimeTimeUp = false;
                    labFluxLifetime->Color = clBtnFace;
                    g_pMainThread->tm1MSFluxLifeTime.timeDevStart();
                }
            }
        }
        else
        {
            break;
        }
    }

}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Product1Click(TObject *Sender)
{
	TfrmProductParam *pWnd = new TfrmProductParam(this);

	bool bRead = true;

	DDX_Float(bRead, g_IniFile.m_dLoaderClampMgzPos[0], pWnd->m_dLoaderClampMgzPos0);
	DDX_Float(bRead, g_IniFile.m_dLoaderClampMgzPos[1], pWnd->m_dLoaderClampMgzPos1);
	DDX_Float(bRead, g_IniFile.m_dLoaderClampMgzPos[2], pWnd->m_dLoaderClampMgzPos2);

	DDX_Float(bRead, g_IniFile.m_dMagazinePushPosY, pWnd->m_dMagazinePushPosY);
	DDX_Float(bRead, g_IniFile.m_dMagazinePushPosZ, pWnd->m_dMagazinePushPosZ);
    DDX_Float(bRead, g_IniFile.m_dMagazinePushPosUpFirstZ, pWnd->m_dMagazinePushPosUpFirstZ);
    DDX_Float(bRead, g_IniFile.m_dLoaderMgzPitch, pWnd->m_dLoaderMgzPitch);

	DDX_Float(bRead, g_IniFile.m_dLoaderUnClampMgzPos[0], pWnd->m_dLoaderUnClampMgzPos0);
	DDX_Float(bRead, g_IniFile.m_dLoaderUnClampMgzPos[1], pWnd->m_dLoaderUnClampMgzPos1);
	DDX_Float(bRead, g_IniFile.m_dLoaderUnClampMgzPos[2], pWnd->m_dLoaderUnClampMgzPos2);

	DDX_Float(bRead, g_IniFile.m_dLeftLaneChangerMgzPos, pWnd->m_dLeftLaneChangerMgzPos);
	DDX_Float(bRead, g_IniFile.m_dLeftLaneChangerSprayPos[0], pWnd->m_dLeftLaneChangerSprayPos0);
	DDX_Float(bRead, g_IniFile.m_dLeftLaneChangerSprayPos[1], pWnd->m_dLeftLaneChangerSprayPos1);

	DDX_Float(bRead, g_IniFile.m_dStartSprayPosX[0], pWnd->m_dStartSprayPosX0);
	DDX_Float(bRead, g_IniFile.m_dStartSprayPosY[0], pWnd->m_dStartSprayPosY0);
	DDX_Float(bRead, g_IniFile.m_dStartSprayPosX[1], pWnd->m_dStartSprayPosX1);
	DDX_Float(bRead, g_IniFile.m_dStartSprayPosY[1], pWnd->m_dStartSprayPosY1);

	DDX_Float(bRead, g_IniFile.m_dSprayPosZ, pWnd->m_dSprayPosZ);
	DDX_Float(bRead, g_IniFile.m_dSprayDistance, pWnd->m_dSprayDistance);
	DDX_Float(bRead, g_IniFile.m_dSprayPitch, pWnd->m_dSprayPitch);
	DDX_Int(bRead, g_IniFile.m_nSprayTimes, pWnd->m_nSprayTimes);
    DDX_Float(bRead, g_IniFile.m_dSprayReadyPos, pWnd->m_dSprayReadyPos);

	DDX_Float(bRead, g_IniFile.m_dRightLaneChangerSprayPos[0], pWnd->m_dRightLaneChangerSprayPos0);
	DDX_Float(bRead, g_IniFile.m_dRightLaneChangerSprayPos[1], pWnd->m_dRightLaneChangerSprayPos1);
	DDX_Float(bRead, g_IniFile.m_dCCDCheckPosX[0], pWnd->m_dCCDCheckPosX0);
	DDX_Float(bRead, g_IniFile.m_dCCDCheckPosY[0], pWnd->m_dCCDCheckPosY0);
    DDX_Float(bRead, g_IniFile.m_dCCDCheckPosX[1], pWnd->m_dCCDCheckPosX1);
	DDX_Float(bRead, g_IniFile.m_dCCDCheckPosY[1], pWnd->m_dCCDCheckPosY1);
    DDX_Float(bRead, g_IniFile.m_dCCDCheckPosX[2], pWnd->m_dCCDCheckPosX2);
	DDX_Float(bRead, g_IniFile.m_dCCDCheckPosY[2], pWnd->m_dCCDCheckPosY2);
    DDX_Float(bRead, g_IniFile.m_dCCDCheckPosX[3], pWnd->m_dCCDCheckPosX3);
	DDX_Float(bRead, g_IniFile.m_dCCDCheckPosY[3], pWnd->m_dCCDCheckPosY3);
    DDX_Check(bRead, g_IniFile.m_bIsUseCCDCheckPos[0], pWnd->m_bIsUseCCDCheckPos0);
    DDX_Check(bRead, g_IniFile.m_bIsUseCCDCheckPos[1], pWnd->m_bIsUseCCDCheckPos1);
    DDX_Check(bRead, g_IniFile.m_bIsUseCCDCheckPos[2], pWnd->m_bIsUseCCDCheckPos2);
    DDX_Check(bRead, g_IniFile.m_bIsUseCCDCheckPos[3], pWnd->m_bIsUseCCDCheckPos3);
    DDX_Float(bRead, g_IniFile.m_dRightLaneChangerDelayTime, pWnd->m_dRightLaneChangerDelayTime);

	DDX_TrackBar(bRead, g_IniFile.m_nLEDDimmer[0], pWnd->m_nLEDDimmer0);
	DDX_TrackBar(bRead, g_IniFile.m_nLEDDimmer[1], pWnd->m_nLEDDimmer1);

	DDX_Check(bRead, g_IniFile.m_bUseSprayer, pWnd->m_bUseSprayer);
	DDX_Check(bRead, g_IniFile.m_bUseCCD, pWnd->m_bUseCCD);
    DDX_Check(bRead, g_IniFile.m_bIsMagazineUpFirst, pWnd->m_bIsMagazineUpFirst);

	DDX_Float(bRead, g_IniFile.m_dFluxTankAirPressure, pWnd->m_dFluxTankAirPressure);
	DDX_Float(bRead, g_IniFile.m_dSprayerAirPressure, pWnd->m_dSprayerAirPressure);

    DDX_Float(bRead, g_IniFile.m_dMarkScore0, pWnd->m_dMarkScore0);

    DDX_Float(bRead, g_IniFile.m_dScaleSprayTime[0], pWnd->m_dScaleSprayTime0);
    DDX_Int(bRead, g_IniFile.m_nScaleSprayTimes[0], pWnd->m_nScaleSprayTimes0);
    DDX_Float(bRead, g_IniFile.m_dWeightScaleAlarmUp, pWnd->m_dWeightScaleAlarmUp);
    DDX_Float(bRead, g_IniFile.m_dWeightScaleAlarmDown, pWnd->m_dWeightScaleAlarmDown);

    DDX_Float(bRead, g_IniFile.m_dCleanSprayPosX[0], pWnd->m_dCleanSprayPosX0);
	DDX_Float(bRead, g_IniFile.m_dCleanSprayPosY[0], pWnd->m_dCleanSprayPosY0);
    DDX_Float(bRead, g_IniFile.m_dCleanSprayPosX[1], pWnd->m_dCleanSprayPosX1);
	DDX_Float(bRead, g_IniFile.m_dCleanSprayPosY[1], pWnd->m_dCleanSprayPosY1);
    DDX_Float(bRead, g_IniFile.m_dCleanSprayPosX[2], pWnd->m_dCleanSprayPosX2);
	DDX_Float(bRead, g_IniFile.m_dCleanSprayPosY[2], pWnd->m_dCleanSprayPosY2);
    DDX_Float(bRead, g_IniFile.m_dCleanSprayPosX[3], pWnd->m_dCleanSprayPosX3);
	DDX_Float(bRead, g_IniFile.m_dCleanSprayPosY[3], pWnd->m_dCleanSprayPosY3);
    DDX_Float(bRead, g_IniFile.m_dCleanSprayPosZ, pWnd->m_dCleanSprayPosZ);
	DDX_Int(bRead, g_IniFile.m_nCleanSprayTimes, pWnd->m_nCleanSprayTimes);
    DDX_Float(bRead, g_IniFile.m_dCleanSprayDistance, pWnd->m_dCleanSprayDistance);
    DDX_Float(bRead, g_IniFile.m_dSprayerCleanWaterPressure, pWnd->m_dSprayerCleanWaterPressure);
    DDX_Float(bRead, g_IniFile.m_dSprayerCleanAirPressure, pWnd->m_dSprayerCleanAirPressure);
    DDX_Int(bRead, g_IniFile.m_nFullCleanSprayTimes, pWnd->m_nFullCleanSprayTimes);

    DDX_Float(bRead, g_IniFile.m_dConveyerPos[0], pWnd->m_dConveyerPos0);
	DDX_Float(bRead, g_IniFile.m_dConveyerPos[1], pWnd->m_dConveyerPos1);
	DDX_Float(bRead, g_IniFile.m_dConveyerPos[2], pWnd->m_dConveyerPos2);
	DDX_Float(bRead, g_IniFile.m_dConveyerPos[3], pWnd->m_dConveyerPos3);
	DDX_Float(bRead, g_IniFile.m_dConveyerPos[4], pWnd->m_dConveyerPos4);
	DDX_Float(bRead, g_IniFile.m_dNGMagPos, pWnd->m_dNGMagPos);

    DDX_Int(bRead, g_IniFile.m_nAutoFillTime, pWnd->m_nAutoFillTime);
    DDX_Int(bRead, g_IniFile.m_nAutoFillFulxPerCount, pWnd->m_nAutoFillFulxPerCount);
    DDX_Float(bRead, g_IniFile.m_dSpraryDelayTimeB, pWnd->m_dSpraryDelayTimeB);
    DDX_Float(bRead, g_IniFile.m_dSpraryDelayTimeA, pWnd->m_dSpraryDelayTimeA);
    DDX_Float(bRead, g_IniFile.m_dSuccBackDelayTime, pWnd->m_dSuccBackDelayTime);

    if (!g_IniFile.m_bIsMagazineUpFirst)
    {
        pWnd->m_dMagazinePushPosZ->Enabled = true;
        pWnd->m_dMagazinePushPosUpFirstZ->Enabled = false;
    }
    else
    {
        pWnd->m_dMagazinePushPosZ->Enabled = false;
        pWnd->m_dMagazinePushPosUpFirstZ->Enabled = true;
    }

    while(1)
    {
        if (pWnd->ShowModal() == mrOk)
        {
            bRead = true;
            if (pWnd->m_dSprayReadyPos->Text.ToDouble() >= g_IniFile.m_dSprayLaneAlarmZ
                || pWnd->m_dSprayPosZ->Text.ToDouble() >= g_IniFile.m_dSprayLaneAlarmZ)
            {
				Application->MessageBoxA("噴嘴Z輸入數據超出限制!!","Confirm",MB_OK);
            }
            else
            {
                bRead = false;
            }

            if (bRead == false)
	        {
		        DDX_Float(bRead, g_IniFile.m_dLoaderClampMgzPos[0], pWnd->m_dLoaderClampMgzPos0);
		        DDX_Float(bRead, g_IniFile.m_dLoaderClampMgzPos[1], pWnd->m_dLoaderClampMgzPos1);
		        DDX_Float(bRead, g_IniFile.m_dLoaderClampMgzPos[2], pWnd->m_dLoaderClampMgzPos2);

		        DDX_Float(bRead, g_IniFile.m_dMagazinePushPosY, pWnd->m_dMagazinePushPosY);
		        DDX_Float(bRead, g_IniFile.m_dMagazinePushPosZ, pWnd->m_dMagazinePushPosZ);
                DDX_Float(bRead, g_IniFile.m_dMagazinePushPosUpFirstZ, pWnd->m_dMagazinePushPosUpFirstZ);
                DDX_Float(bRead, g_IniFile.m_dLoaderMgzPitch, pWnd->m_dLoaderMgzPitch);

		        DDX_Float(bRead, g_IniFile.m_dLoaderUnClampMgzPos[0], pWnd->m_dLoaderUnClampMgzPos0);
		        DDX_Float(bRead, g_IniFile.m_dLoaderUnClampMgzPos[1], pWnd->m_dLoaderUnClampMgzPos1);
		        DDX_Float(bRead, g_IniFile.m_dLoaderUnClampMgzPos[2], pWnd->m_dLoaderUnClampMgzPos2);

		        DDX_Float(bRead, g_IniFile.m_dLeftLaneChangerMgzPos, pWnd->m_dLeftLaneChangerMgzPos);
		        DDX_Float(bRead, g_IniFile.m_dLeftLaneChangerSprayPos[0], pWnd->m_dLeftLaneChangerSprayPos0);
		        DDX_Float(bRead, g_IniFile.m_dLeftLaneChangerSprayPos[1], pWnd->m_dLeftLaneChangerSprayPos1);

		        DDX_Float(bRead, g_IniFile.m_dStartSprayPosX[0], pWnd->m_dStartSprayPosX0);
		        DDX_Float(bRead, g_IniFile.m_dStartSprayPosY[0], pWnd->m_dStartSprayPosY0);
		        DDX_Float(bRead, g_IniFile.m_dStartSprayPosX[1], pWnd->m_dStartSprayPosX1);
		        DDX_Float(bRead, g_IniFile.m_dStartSprayPosY[1], pWnd->m_dStartSprayPosY1);

		        DDX_Float(bRead, g_IniFile.m_dSprayPosZ, pWnd->m_dSprayPosZ);
		        DDX_Float(bRead, g_IniFile.m_dSprayDistance, pWnd->m_dSprayDistance);
		        DDX_Float(bRead, g_IniFile.m_dSprayPitch, pWnd->m_dSprayPitch);
		        DDX_Int(bRead, g_IniFile.m_nSprayTimes, pWnd->m_nSprayTimes);
                DDX_Float(bRead, g_IniFile.m_dSprayReadyPos, pWnd->m_dSprayReadyPos);

		        DDX_Float(bRead, g_IniFile.m_dRightLaneChangerSprayPos[0], pWnd->m_dRightLaneChangerSprayPos0);
		        DDX_Float(bRead, g_IniFile.m_dRightLaneChangerSprayPos[1], pWnd->m_dRightLaneChangerSprayPos1);
		        DDX_Float(bRead, g_IniFile.m_dCCDCheckPosX[0], pWnd->m_dCCDCheckPosX0);
		        DDX_Float(bRead, g_IniFile.m_dCCDCheckPosY[0], pWnd->m_dCCDCheckPosY0);
                DDX_Float(bRead, g_IniFile.m_dCCDCheckPosX[1], pWnd->m_dCCDCheckPosX1);
                DDX_Float(bRead, g_IniFile.m_dCCDCheckPosY[1], pWnd->m_dCCDCheckPosY1);
                DDX_Float(bRead, g_IniFile.m_dCCDCheckPosX[2], pWnd->m_dCCDCheckPosX2);
                DDX_Float(bRead, g_IniFile.m_dCCDCheckPosY[2], pWnd->m_dCCDCheckPosY2);
                DDX_Float(bRead, g_IniFile.m_dCCDCheckPosX[3], pWnd->m_dCCDCheckPosX3);
                DDX_Float(bRead, g_IniFile.m_dCCDCheckPosY[3], pWnd->m_dCCDCheckPosY3);
                DDX_Check(bRead, g_IniFile.m_bIsUseCCDCheckPos[0], pWnd->m_bIsUseCCDCheckPos0);
                DDX_Check(bRead, g_IniFile.m_bIsUseCCDCheckPos[1], pWnd->m_bIsUseCCDCheckPos1);
                DDX_Check(bRead, g_IniFile.m_bIsUseCCDCheckPos[2], pWnd->m_bIsUseCCDCheckPos2);
                DDX_Check(bRead, g_IniFile.m_bIsUseCCDCheckPos[3], pWnd->m_bIsUseCCDCheckPos3);
                DDX_Float(bRead, g_IniFile.m_dRightLaneChangerDelayTime, pWnd->m_dRightLaneChangerDelayTime);

		        DDX_TrackBar(bRead, g_IniFile.m_nLEDDimmer[0], pWnd->m_nLEDDimmer0);
		        DDX_TrackBar(bRead, g_IniFile.m_nLEDDimmer[1], pWnd->m_nLEDDimmer1);

		        DDX_Check(bRead, g_IniFile.m_bUseSprayer, pWnd->m_bUseSprayer);
		        DDX_Check(bRead, g_IniFile.m_bUseCCD, pWnd->m_bUseCCD);
                DDX_Check(bRead, g_IniFile.m_bIsMagazineUpFirst, pWnd->m_bIsMagazineUpFirst);

		        DDX_Float(bRead, g_IniFile.m_dFluxTankAirPressure, pWnd->m_dFluxTankAirPressure);
		        DDX_Float(bRead, g_IniFile.m_dSprayerAirPressure, pWnd->m_dSprayerAirPressure);

                DDX_Float(bRead, g_IniFile.m_dMarkScore0, pWnd->m_dMarkScore0);

                DDX_Float(bRead, g_IniFile.m_dScaleSprayTime[0], pWnd->m_dScaleSprayTime0);
                DDX_Int(bRead, g_IniFile.m_nScaleSprayTimes[0], pWnd->m_nScaleSprayTimes0);
                DDX_Float(bRead, g_IniFile.m_dWeightScaleAlarmUp, pWnd->m_dWeightScaleAlarmUp);
                DDX_Float(bRead, g_IniFile.m_dWeightScaleAlarmDown, pWnd->m_dWeightScaleAlarmDown);

                DDX_Float(bRead, g_IniFile.m_dCleanSprayPosX[0], pWnd->m_dCleanSprayPosX0);
                DDX_Float(bRead, g_IniFile.m_dCleanSprayPosY[0], pWnd->m_dCleanSprayPosY0);
                DDX_Float(bRead, g_IniFile.m_dCleanSprayPosX[1], pWnd->m_dCleanSprayPosX1);
	            DDX_Float(bRead, g_IniFile.m_dCleanSprayPosY[1], pWnd->m_dCleanSprayPosY1);
                DDX_Float(bRead, g_IniFile.m_dCleanSprayPosX[2], pWnd->m_dCleanSprayPosX2);
	            DDX_Float(bRead, g_IniFile.m_dCleanSprayPosY[2], pWnd->m_dCleanSprayPosY2);
                DDX_Float(bRead, g_IniFile.m_dCleanSprayPosX[3], pWnd->m_dCleanSprayPosX3);
	            DDX_Float(bRead, g_IniFile.m_dCleanSprayPosY[3], pWnd->m_dCleanSprayPosY3);
                DDX_Float(bRead, g_IniFile.m_dCleanSprayPosZ, pWnd->m_dCleanSprayPosZ);
	            DDX_Int(bRead, g_IniFile.m_nCleanSprayTimes, pWnd->m_nCleanSprayTimes);
                DDX_Float(bRead, g_IniFile.m_dCleanSprayDistance, pWnd->m_dCleanSprayDistance);
                DDX_Float(bRead, g_IniFile.m_dSprayerCleanWaterPressure, pWnd->m_dSprayerCleanWaterPressure);
                DDX_Float(bRead, g_IniFile.m_dSprayerCleanAirPressure, pWnd->m_dSprayerCleanAirPressure);
                DDX_Int(bRead, g_IniFile.m_nFullCleanSprayTimes, pWnd->m_nFullCleanSprayTimes);

		        DDX_Float(bRead, g_IniFile.m_dConveyerPos[0], pWnd->m_dConveyerPos0);
		        DDX_Float(bRead, g_IniFile.m_dConveyerPos[1], pWnd->m_dConveyerPos1);
		        DDX_Float(bRead, g_IniFile.m_dConveyerPos[2], pWnd->m_dConveyerPos2);
		        DDX_Float(bRead, g_IniFile.m_dConveyerPos[3], pWnd->m_dConveyerPos3);
		        DDX_Float(bRead, g_IniFile.m_dConveyerPos[4], pWnd->m_dConveyerPos4);
		        DDX_Float(bRead, g_IniFile.m_dNGMagPos, pWnd->m_dNGMagPos);

                DDX_Int(bRead, g_IniFile.m_nAutoFillTime, pWnd->m_nAutoFillTime);
                DDX_Int(bRead, g_IniFile.m_nAutoFillFulxPerCount, pWnd->m_nAutoFillFulxPerCount);
                DDX_Float(bRead, g_IniFile.m_dSpraryDelayTimeB, pWnd->m_dSpraryDelayTimeB);
                DDX_Float(bRead, g_IniFile.m_dSpraryDelayTimeA, pWnd->m_dSpraryDelayTimeA);
                DDX_Float(bRead, g_IniFile.m_dSuccBackDelayTime, pWnd->m_dSuccBackDelayTime);
                
		        //Set Pressure
		        g_Motion.SetAO(0, g_IniFile.m_dFluxTankAirPressure);
		        g_Motion.SetAO(1, g_IniFile.m_dSprayerAirPressure);

                TrackBar2->Position = g_IniFile.m_dFluxTankAirPressure;
                TrackBar3->Position = g_IniFile.m_dSprayerAirPressure;
            }
        }
        else
        {
            break;
        }
    }

}
//--------------------------------------------------------------------------- 
void __fastcall TfrmMain::DIDO1Click(TObject *Sender)
{
	TIOCheckDlg *pIOCheckDlg = new TIOCheckDlg(this);

	//CreateCaptionFile(pIOCheckDlg);
	ReadCaptionFile(pIOCheckDlg);
	pIOCheckDlg->ShowModal();
	delete pIOCheckDlg;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Motor1Click(TObject *Sender)
{
	TfrmChoiceMotor *pChoiceMotorDlg = new TfrmChoiceMotor(this);
	TfrmMotorCheck *pMotorCheckDlg;

	while (pChoiceMotorDlg->ShowModal() != mrCancel)
	{
		pMotorCheckDlg = new TfrmMotorCheck(this);
		pMotorCheckDlg->m_nActiveAxis = pChoiceMotorDlg->m_nSelectAxis;
		pMotorCheckDlg->Caption = pChoiceMotorDlg->m_strCaption;

        if (pChoiceMotorDlg->m_nSelectAxis == 4)
        {
            if (g_DIO.ReadDIBit(DI::LeftLaneChangerIn))
            {
                Application->MessageBoxA("確認入料流道有東西!","Confirm",MB_OK);
                delete pMotorCheckDlg;
                delete pChoiceMotorDlg;
                return;
            }
            if (!g_Motion.GetDI(DI::LoaderPusherBwd))
            {
                Application->MessageBoxA("推桿未縮回!","Confirm",MB_OK);
                delete pMotorCheckDlg;
                delete pChoiceMotorDlg;
                return;
            }
        }
        if (pChoiceMotorDlg->m_nSelectAxis == 5)
        {
            if (!g_Motion.GetDI(DI::LoaderPusherBwd))
            {
                Application->MessageBoxA("推桿未縮回!","Confirm",MB_OK);
                delete pMotorCheckDlg;
                delete pChoiceMotorDlg;
                return;
            }
        }
        if (pChoiceMotorDlg->m_nSelectAxis == 9)
        {
            if (g_DIO.ReadDIBit(DI::RightLaneChangerOut))
            {
                Application->MessageBoxA("確認出料流道有東西!","Confirm",MB_OK);
                delete pMotorCheckDlg;
                delete pChoiceMotorDlg;
                return;
            }
        }
        if (pChoiceMotorDlg->m_nSelectAxis == 10)
        {
            if (g_DIO.ReadDIBit(DI::LeftLaneChangerIn) || g_DIO.ReadDIBit(DI::LeftLaneChangerOut)
                || g_DIO.ReadDIBit(DI::FrontLaneSprayIn) || g_DIO.ReadDIBit(DI::RearLaneSprayIn))
            {
                Application->MessageBoxA("確認入料流道有東西!","Confirm",MB_OK);
                delete pMotorCheckDlg;
                delete pChoiceMotorDlg;
                return;
            }
        }
        if (pChoiceMotorDlg->m_nSelectAxis == 12)
        {
            if (g_DIO.ReadDIBit(DI::FrontLaneSprayOut) || g_DIO.ReadDIBit(DI::RearLaneSprayOut)
                || g_DIO.ReadDIBit(DI::RightLaneChangerIn) || g_DIO.ReadDIBit(DI::RightLaneChangerOut))
            {
                Application->MessageBoxA("確認出料流道有東西!","Confirm",MB_OK);
                delete pMotorCheckDlg;
                delete pChoiceMotorDlg;
                return;
            }
        }



		pMotorCheckDlg->ShowModal();
		delete pMotorCheckDlg;
	}

	delete pChoiceMotorDlg;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::ManualOperation1Click(TObject *Sender)
{
    if(!g_pMainThread->m_bIsHomeDone)
    {
        ShowMessage("請先執行機台原點復歸");
        return;
    }

    TfmManual *pWnd=new TfmManual(this);
    pWnd->ShowModal();
    delete pWnd;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Login1Click(TObject *Sender)
{
	TfmPrivilege *pDlg = new TfmPrivilege(this);
	TfrmPassword *pPwdDlg = new TfrmPassword(this);
	int nD = pDlg->ShowModal() - 1;
	delete pDlg;

	switch (nD)
	{
	case 1:
	case 2:
		pPwdDlg->labelOldPassword->Caption = "請輸入密碼";
		pPwdDlg->labelNewPassword->Visible = false;
		pPwdDlg->editNewPassword->Visible = false;
		if (pPwdDlg->ShowModal() == mrOk)
		{
			if (pPwdDlg->editOldPassword->Text == g_IniFile.m_strENGPassword) m_nUserLevel = 1;
			else if (pPwdDlg->editOldPassword->Text == g_IniFile.m_strARTPassword) m_nUserLevel = 2;
			else { Application->MessageBox("密碼錯誤!!", "錯誤", MB_OK); m_nUserLevel = 0; }
		}
		SetPrivilege(m_nUserLevel);
		break;
	case 0:
		m_nUserLevel = 0;
		SetPrivilege(0);
		break;
	case 3:
		if (pPwdDlg->ShowModal() == mrOk)
		{
			if (pPwdDlg->editOldPassword->Text == g_IniFile.m_strENGPassword)
				g_IniFile.m_strENGPassword = pPwdDlg->editNewPassword->Text;
		}
		break;
	}

	delete pPwdDlg;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Exit1Click(TObject *Sender)
{
	if (Application->MessageBoxA("確定離開程式?", "Confirm", MB_ICONQUESTION | MB_OKCANCEL) == IDCANCEL) return;


	if (Application->MessageBoxA("離開前要存檔嗎?", "Confirm", MB_ICONQUESTION | MB_OKCANCEL) == IDOK)
	{

		g_IniFile.MachineFile(false);
		g_IniFile.ProductFile(Caption.c_str(), false);

		theVision.SaveTool(g_IniFile.GetFileNameWithNewExt(Caption.c_str(), "cev").c_str(), "Dummy");

		ShowMessage("檔案儲存完成!");

	}


	exit(0);
}
//---------------------------------------------------------------------------
#pragma endregion


#pragma region MainImage
void __fastcall TfrmMain::ImagePaintBoxPaint(TObject *Sender)
{
	theVision.DrawAll(ImagePaintBox->Canvas->Handle, 640);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::m_bStopLoaderClick(TObject *Sender)
{
    g_IniFile.m_bStopLoader = m_bStopLoader->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::ImagePaintBoxMouseMove(TObject *Sender,
	TShiftState Shift, int X, int Y)
{
	if (m_nUserLevel<1) return;

	if (Shift.Contains(ssLeft))
	{
		// Mouse button down, drag the ROI border
		if (checkShowSearchROI0->Checked) theVision.m_roiMark[0].Drag(theVision.m_eHandle, X, Y, theVision.m_dScaleSizeX, theVision.m_dScaleSizeY);
		RefreshImage();
	}
	else
	{
		if (checkShowSearchROI0->Checked) theVision.m_eHandle = theVision.m_roiMark[0].HitTest(X, Y, theVision.m_dScaleSizeX, theVision.m_dScaleSizeY);

	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnGrabClick(TObject *Sender)
{
	g_pCCD->Grab(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnLiveClick(TObject *Sender)
{
    TSpeedButton *pBtn=(TSpeedButton *)Sender;
    if(pBtn->Down) g_pCCD->StartGrab(0);
    else g_pCCD->StopGrab(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::TrackBar1Change(TObject *Sender)
{
	labelLED0->Caption = TrackBar1->Position;
	g_IniFile.m_nLEDDimmer[0] = TrackBar1->Position;
	g_LED.SetCurrent(0, 0, TrackBar1->Position, 0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::checkShowSearchROI0Click(TObject *Sender)
{
	theVision.m_bShowMarkROI[0] = checkShowSearchROI0->Checked;
	RefreshImage();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnVisionProcessClick(TObject *Sender)
{
	float dAvg = 0;
	ImgPixelAverage(&theVision.m_roiMark[0], dAvg);

	Label1->Caption = "Avg:" + FormatFloat("0.00", dAvg);
}
//---------------------------------------------------------------------------
#pragma endregion


#pragma region MainManual
void __fastcall TfrmMain::checkStartScaleMonitorClick(TObject *Sender)
{
	timerScale->Enabled = checkStartScaleMonitor->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::BitBtn12Click(TObject *Sender)
{
    g_pMainThread->SoftStart();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::BitBtn13Click(TObject *Sender)
{
    g_pMainThread->SoftStop();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::BitBtn14Click(TObject *Sender)
{
    g_pMainThread->SoftReset();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::BitBtn15Click(TObject *Sender)
{
    if(Application->MessageBox("是否整機初始化", "Info", MB_OKCANCEL)==IDCANCEL) return;
    g_pMainThread->SoftInit();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SpeedButton2Click(TObject *Sender)
{
	g_Scale.SetZero();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnOpenLogClick(TObject *Sender)
{
    AnsiString strCMD = "C:\\C83 Log\\" + FormatDateTime("yyyy_mm_dd",Now()) + ".txt";
    ShellExecute(this->Handle, "open", "notepad", strCMD.c_str(), NULL, SW_SHOW);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::TrackBar2Change(TObject *Sender)
{
	g_Motion.SetAO(0, TrackBar2->Position);
	Label2->Caption = TrackBar2->Position;
    editFlux->Text = IntToStr(TrackBar2->Position);
    g_IniFile.m_dFluxTankAirPressure = TrackBar2->Position;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::TrackBar3Change(TObject *Sender)
{
	g_Motion.SetAO(1, TrackBar3->Position);
	Label4->Caption = TrackBar3->Position;
    editAir->Text = IntToStr(TrackBar3->Position);
    g_IniFile.m_dSprayerAirPressure = TrackBar3->Position;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnSet1Click(TObject *Sender)
{
    TSpeedButton *pBtn = (TSpeedButton *)Sender;

    if (pBtn->Tag == 1)
    {
        g_IniFile.m_dFluxTankAirPressure = editFlux->Text.ToDouble();
        TrackBar2->Position = g_IniFile.m_dFluxTankAirPressure;
    }
    else if (pBtn->Tag == 2)
    {
        g_IniFile.m_dSprayerAirPressure = editAir->Text.ToDouble();
        TrackBar3->Position = g_IniFile.m_dSprayerAirPressure;
    }
    else if (pBtn->Tag == 3)
    {
        g_IniFile.m_dMarkScore0 = m_dMarkScore0->Text.ToDouble(); 
    }
    else if (pBtn->Tag == 4)
    {
        m_dMarkScore0->Text = FormatFloat("0.000",g_IniFile.m_dMarkScore0);   
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SpeedButton1Click(TObject *Sender)
{
	static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

	TSpeedButton *pBtn = (TSpeedButton *)Sender;

	if (!g_pMainThread->m_bIsHomeDone)
	{
		ShowMessage("請先原點復歸");
		return;
	}
    if (g_pMainThread->m_bIsSprayerLock)
    {
        ShowMessage("噴嘴忙碌中");
		return;
    }

	pBtn->Enabled = false;
	g_pMainThread->m_listLog.push_back("開始噴塗測試");

	g_Motion.AbsMove(Axis_Const::SPZ, 0.0);

    tm1MS.timeStart(30000);
	while (1)
	{
		if (g_Motion.IsPosDone(Axis_Const::SPZ, 0.0)) break;
		Application->ProcessMessages();
        if (tm1MS.timeUp()) break;
	}

	g_Motion.AbsMove(Axis_Const::SPX, g_IniFile.m_dStartSprayPosX[pBtn->Tag]);
	g_Motion.AbsMove(Axis_Const::SPY, g_IniFile.m_dStartSprayPosY[pBtn->Tag]);

    tm1MS.timeStart(30000);
	while (1)
	{
		if (g_Motion.IsPosDone(Axis_Const::SPX, g_IniFile.m_dStartSprayPosX[pBtn->Tag]) &&
			g_Motion.IsPosDone(Axis_Const::SPY, g_IniFile.m_dStartSprayPosY[pBtn->Tag])) break;
		Application->ProcessMessages();
        if (tm1MS.timeUp()) break;
	}

	g_pMainThread->m_bIsSprayerLock = true;
    if (pBtn->Tag) g_pMainThread->m_bStartSBTSprayF = true;
    else g_pMainThread->m_bStartSBTSprayR = true;
	g_pMainThread->nThreadIndex[17] = 0;
    g_pMainThread->nThreadIndex[12] = 0;

    tm1MS.timeStart(120000);
	while (1)
	{
		if (((pBtn->Tag == true) && !g_pMainThread->m_bStartSBTSprayF) || ((pBtn->Tag == false) && !g_pMainThread->m_bStartSBTSprayR)) break;
		Application->ProcessMessages();
        if (tm1MS.timeUp()) break;
	}

    g_Motion.AbsMove(Axis_Const::SPZ, 0.0);

    tm1MS.timeStart(30000);
	while (1)
	{
		if (g_Motion.IsPosDone(Axis_Const::SPZ, 0.0)) break;
		Application->ProcessMessages();
        if (tm1MS.timeUp()) break;
	}

    g_pMainThread->m_bIsSprayerLock = false;
	g_pMainThread->m_listLog.push_back("噴塗測試結束");
	pBtn->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SpeedButton5Click(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

	TSpeedButton *pBtn = (TSpeedButton *)Sender;

	if (!g_pMainThread->m_bIsHomeDone)
	{
		ShowMessage("請先原點復歸");
		return;
	}
    if (!g_Motion.GetDI(DI::LoaderPusherBwd))
    {
        Application->MessageBoxA("推桿未縮回!","Confirm",MB_OK);
        return;
    }

	pBtn->Enabled = false;
	g_pMainThread->m_listLog.push_back("開始補料盒測試");

	g_pMainThread->m_bStartReLoadClamper = true;
	g_pMainThread->nThreadIndex[8] = 0;
    g_pMainThread->nThreadIndex[1] = 0;

	tm1MS.timeStart(120000);
	while (1)
	{
		if (!g_pMainThread->m_bStartReLoadClamper) break;
        g_pMainThread->doLoadConveyerUp(g_pMainThread->nThreadIndex[1]);
		Application->ProcessMessages();
		if (tm1MS.timeUp() || g_IniFile.m_nErrorCode != 0) break;
	}

    g_Motion.SetDO(DO::LoaderConveyerUp, false);
	g_pMainThread->m_listLog.push_back("補料盒動作測試結束");
	pBtn->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SpeedButton4Click(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

	TSpeedButton *pBtn = (TSpeedButton *)Sender;

	if (!g_pMainThread->m_bIsHomeDone)
	{
		ShowMessage("請先原點復歸");
		return;
	}
    if (!g_Motion.GetDI(DI::LoaderPusherBwd))
    {
        Application->MessageBoxA("推桿未縮回!","Confirm",MB_OK);
        return;
    }

	pBtn->Enabled = false;
	g_pMainThread->m_listLog.push_back("開始退料盒測試");

    g_pMainThread->m_bStartUnLoadClamper = true;
	g_pMainThread->nThreadIndex[9] = 0;
    g_pMainThread->nThreadIndex[2] = 0;

	tm1MS.timeStart(120000);
	while (1)
	{
		if (!g_pMainThread->m_bStartUnLoadClamper) break;
        g_pMainThread->doLoadConveyerDown(g_pMainThread->nThreadIndex[2]);
		Application->ProcessMessages();
		if (tm1MS.timeUp() || g_IniFile.m_nErrorCode != 0) break;
	}

    g_pMainThread->m_bLoaderClamperReady = false;
    g_pMainThread->nThreadIndex[2] = 0;
    g_pMainThread->nThreadIndex[3] = 0;

    g_Motion.SetDO(DO::LoaderConveyerDown, false);
	g_pMainThread->m_listLog.push_back("退料盒動作測試結束");
	pBtn->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SpeedButton6Click(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

	TSpeedButton *pBtn = (TSpeedButton *)Sender;

	if (!g_pMainThread->m_bIsHomeDone)
	{
		ShowMessage("請先原點復歸");
		return;
	}
    if (g_pMainThread->m_bIsSprayerLock)
    {
        ShowMessage("噴嘴忙碌中");
		return;
    }

	pBtn->Enabled = false;
	g_pMainThread->m_listLog.push_back("開始(F) Weight Scale動作測試");

	g_pMainThread->m_bIsSprayerLock = true;
	g_pMainThread->m_bStartFluxScaleSpray = true;
	g_pMainThread->nThreadIndex[13] = 0;

	tm1MS.timeStart(120000);
	while (1)
	{
		if (!g_pMainThread->m_bStartFluxScaleSpray) break;
		Application->ProcessMessages();
		if (tm1MS.timeUp()) break;
	}

    g_pMainThread->m_bIsSprayerLock = false;
	g_pMainThread->m_listLog.push_back("(F) Weight Scale動作測試結束");
	pBtn->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SpeedButton7Click(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

	TSpeedButton *pBtn = (TSpeedButton *)Sender;

	if (!g_pMainThread->m_bIsHomeDone)
	{
		ShowMessage("請先原點復歸");
		return;
	}
    if (g_pMainThread->m_bIsSprayerLock)
    {
        ShowMessage("噴嘴忙碌中");
		return;
    }

	pBtn->Enabled = false;
	g_pMainThread->m_listLog.push_back("開始(F) 疏通位置動作測試");

	g_pMainThread->m_bIsSprayerLock = true;
	g_pMainThread->m_bStartDredgeScaleSpray = true;
	g_pMainThread->nThreadIndex[14] = 0;

	tm1MS.timeStart(120000);
	while (1)
	{
		if (!g_pMainThread->m_bStartDredgeScaleSpray) break;
		Application->ProcessMessages();
		if (tm1MS.timeUp()) break;
	}

    g_pMainThread->m_bIsSprayerLock = false;
	g_pMainThread->m_listLog.push_back("(F) 疏通位置動作測試結束");
	pBtn->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SpeedButton8Click(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

	TSpeedButton *pBtn = (TSpeedButton *)Sender;

	if (!g_pMainThread->m_bIsHomeDone)
	{
		ShowMessage("請先原點復歸");
		return;
	}
    if (g_pMainThread->m_bIsSprayerLock)
    {
        ShowMessage("噴嘴忙碌中");
		return;
    }

	pBtn->Enabled = false;
	g_pMainThread->m_listLog.push_back("開始清洗測試");

    g_pMainThread->m_bIsSprayerLock = true;
	g_pMainThread->m_bStartCleanSpray = true;
	g_pMainThread->nThreadIndex[16] = 0;

	tm1MS.timeStart(1800000);
	while (1)
	{
		if (!g_pMainThread->m_bStartCleanSpray) break;
		Application->ProcessMessages();
		if (tm1MS.timeUp()) break;
	}

    g_pMainThread->m_bIsSprayerLock = true;
	g_pMainThread->m_bStartCleanSprayAir = true;
	g_pMainThread->nThreadIndex[15] = 0;

	tm1MS.timeStart(120000);
	while (1)
	{
		if (!g_pMainThread->m_bStartCleanSprayAir) break;
		Application->ProcessMessages();
		if (tm1MS.timeUp()) break;
	}

    g_pMainThread->m_bIsSprayerLock = false;
	g_pMainThread->m_listLog.push_back("清洗測試結束");
	pBtn->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SpeedButton9Click(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

	TSpeedButton *pBtn = (TSpeedButton *)Sender;

	if (!g_pMainThread->m_bIsHomeDone)
	{
		ShowMessage("請先原點復歸");
		return;
	}

	pBtn->Enabled = false;
	g_pMainThread->m_listLog.push_back("開始補Flux測試");

    g_pMainThread->m_bStartFillFlux = true;
    g_pMainThread->nThreadIndex[18] = 0;

    g_pMainThread->m_bIsSprayerLock = true;

	while (1)
	{
		if (!g_pMainThread->m_bStartFillFlux) break;
		Application->ProcessMessages();
	}

    g_pMainThread->m_bIsSprayerLock = false;

	g_pMainThread->m_listLog.push_back("補Flux測試結束");
	pBtn->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SpeedButton10Click(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

    g_pMainThread->m_bIsSprayerLock = false;
    g_pMainThread->m_bStartFillFlux = false;
    g_pMainThread->nThreadIndex[18] = 0;
    g_pMainThread->m_listLog.push_back("終止 補Flux測試");

    g_Motion.SetDO(DO::FluxTankFluxIn, false);
    g_Motion.SetDO(DO::FluxTankVacuumIn, false);
    g_Motion.SetDO(DO::FluxTankVacOn, false);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SpeedButton16Click(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

    g_pMainThread->m_bIsSprayerLock = false;
    g_pMainThread->m_bStartCleanSpray = false;
    g_pMainThread->m_bStartCleanSprayAir = false;
    g_pMainThread->nThreadIndex[15] = 0;
    g_pMainThread->nThreadIndex[16] = 0;
    g_pMainThread->m_listLog.push_back("終止 清洗測試");

    g_Motion.SetDO(DO::FrontLaneSprayMotor, false);
    g_Motion.SetDO(DO::RearLaneSprayMotor, false);
    g_Motion.SetDO(DO::CleanerWaterOn, false);
    g_Motion.SetDO(DO::CleanerWaterAirSwitch, false);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnLoaderResetClick(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

	TSpeedButton *pBtn = (TSpeedButton *)Sender;

    Application->MessageBoxA("請先移除料盒,與放開夾爪!!","Confirm",MB_OK);
	if (!g_pMainThread->m_bIsHomeDone)
	{
		ShowMessage("請先原點復歸");
		return;
	}
    if (!g_Motion.GetDI(DI::LoaderClamperUp) || g_Motion.GetDI(DI::LoaderClamperMgzExist))
    {
        ShowMessage("請先移除料盒");
        return;
    }
    if (!g_Motion.GetDI(DI::LoaderPusherBwd))
    {
        Application->MessageBoxA("推桿未縮回!","Confirm",MB_OK);
        return;
    }

	pBtn->Enabled = false;

    g_pMainThread->m_bStartInitLoader = true;
    g_pMainThread->nThreadIndex[10] = 0;

    tm1MS.timeStart(120000);
	while (1)
	{
		if (!g_pMainThread->m_bStartInitLoader) break;
		Application->ProcessMessages();
        if (tm1MS.timeUp()) break;
	}
    g_pMainThread->nThreadIndex[2] = 0;
    g_pMainThread->nThreadIndex[3] = 0;
	pBtn->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnInLaneResetClick(TObject *Sender)
{
    if (Application->MessageBoxA("確定移除 入料流道料片,與移除流道步驟?", "Confirm", MB_ICONQUESTION | MB_OKCANCEL) == IDCANCEL) return;

    g_pMainThread->nThreadIndex[4] = 0;
    g_pMainThread->m_bLeftLaneChangerReady = false;
    //ShowNow
    g_pMainThread->m_arraybShape[0] = false;
    ShowMessage("完成");
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnRearLaneResetClick(TObject *Sender)
{
    if (Application->MessageBoxA("確定移除 後流道料片,與移除流道步驟?", "Confirm", MB_ICONQUESTION | MB_OKCANCEL) == IDCANCEL) return;

    g_pMainThread->nThreadIndex[6] = 0;
    g_pMainThread->n_bLaneSprayReady[0] = false;
    g_pMainThread->m_bIsLeftLaneChangerLock = false;
    //ShowNow
    g_pMainThread->m_arraybShape[2] = false;
    ShowMessage("完成");
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnFrnotLaneResetClick(TObject *Sender)
{
    if (Application->MessageBoxA("確定移除 前流道料片,與移除流道步驟?", "Confirm", MB_ICONQUESTION | MB_OKCANCEL) == IDCANCEL) return;

    g_pMainThread->nThreadIndex[5] = 0;
    g_pMainThread->n_bLaneSprayReady[1] = false;
    g_pMainThread->m_bIsLeftLaneChangerLock = false;
    //ShowNow
    g_pMainThread->m_arraybShape[1] = false;
    ShowMessage("完成");
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnOutLaneResetClick(TObject *Sender)
{
    if (Application->MessageBoxA("確定移除 出料流道料片,與移除流道步驟?", "Confirm", MB_ICONQUESTION | MB_OKCANCEL) == IDCANCEL) return;

    g_pMainThread->nThreadIndex[7] = 0;
    //ShowNow
    g_pMainThread->m_arraybShape[3] = false;
    ShowMessage("完成");
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SpeedButton11Click(TObject *Sender)
{
    g_1DScanner.Disable();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SpeedButton12Click(TObject *Sender)
{
    g_1DScanner.Enable();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SpeedButton13Click(TObject *Sender)
{
    g_1DScanner.Sleep();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SpeedButton14Click(TObject *Sender)
{
    g_1DScanner.Wakeup();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SpeedButton15Click(TObject *Sender)
{
    g_1DScanner.Initial();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btn1DReadClick(TObject *Sender)
{
    btn1DRead->Enabled = false;
    g_1DScanner.Wakeup();
    ::Sleep(2500);
    g_1DScanner.Enable();
    ::Sleep(2500);
    g_1DScanner.Disable();
    ::Sleep(100);
    g_1DScanner.Sleep();
    ::Sleep(100);
    btn1DRead->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btn2DReadClick(TObject *Sender)
{
    g_2DReader.Read();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btn1DSleepClick(TObject *Sender)
{
    static C_GetTime tm1MS(EX_SCALE::TIME_1MS, false);

    AnsiString strCommand = "";
    bool bIsReturnOK = false;
    g_pMainThread->m_listReaderTX.clear();
    g_pMainThread->m_listReaderTX.push_back("SHUTDOWN_1D_CODE");

    tm1MS.timeStart(10000);
	while (1)
	{
		if (g_pMainThread->m_listReaderTX.size()>0)
        {
            strCommand = g_pMainThread->m_listReaderTX.front();
		    g_pMainThread->m_listReaderTX.pop_front();
            if (strCommand == "SHUTDOWN_1D_CODE_OK")
            {
                bIsReturnOK = true;
                break;
            }
            else break;
        }
		Application->ProcessMessages();
        if (tm1MS.timeUp()) break;
	}

    if (bIsReturnOK == true) g_pMainThread->m_listLog.push_back("1D Reader 已關閉");
    else g_pMainThread->m_listLog.push_back("1D Reader 關閉失敗");
}
//---------------------------------------------------------------------------

#pragma endregion


















