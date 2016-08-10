//---------------------------------------------------------------------------


#pragma hdrstop

#include "EQPXML.h"
#include "IniFile.h"
#include "MainThread.h"
#include "dir.h"
CEQPXML g_eqpXML;
extern CIniFile g_IniFile;
extern CMainThread *g_pMainThread;


#define MAX_SEND_BUFF 30000
//---------------------------------------------------------------------------

#pragma package(smart_init)

void __fastcall CEQPXML::doHostStatus(char *pRx)
{
	TiXmlDocument doc;
	doc.Parse(pRx);
	TiXmlElement* pRoot = doc.FirstChildElement("Root");
	TiXmlElement* pData = pRoot->FirstChildElement("DATA");

	AnsiString strMsgID(pRoot->Attribute("MSGID"));
	AnsiString strData = pData->GetText();

	if (strData == "1") m_CIMStatus = "1";
	else if (strData == "0") m_CIMStatus = "0";
	else if (strData == "2") m_CIMStatus = "2";
	else m_CIMStatus = "0";

	//SendXML("HOST_STATUS","ACK","ACK","");

	pRoot->SetAttribute("TYPE", "ACK");
	pData->SetValue("ACK");
	TiXmlNode *pNode3 = pData->FirstChild();
	pNode3->SetValue("");

	SendXML(doc);

}
//---------------------------------------------------------------------------
void __fastcall CEQPXML::doDTSet(char *pRx)
{
    /*
	TiXmlDocument doc;
	doc.Parse(pRx);
	TiXmlElement *pRoot = doc.FirstChildElement("Root");
	TiXmlElement *pData = pRoot->FirstChildElement("DATA");

	AnsiString strMsgID(pRoot->Attribute("MSGID"));
	AnsiString strData = pData->GetText();
	//Set System Date Time Here

	SendXML("DTSET", "ACK", "ACK", "0");           //0:OK 1:NG
    */
}
//---------------------------------------------------------------------------
void __fastcall CEQPXML::doCIMMsg(char *pRx)
{
	TiXmlDocument doc;
	doc.Parse(pRx);
	TiXmlElement *pRoot = doc.FirstChildElement("Root");
	TiXmlElement *pData = pRoot->FirstChildElement("DATA");

	AnsiString strMsgID(pRoot->Attribute("MSGID"));
	AnsiString strData = pData->GetText();
	//do something whith that message
	m_strCIMMsgLog.push_back(strData);

	SendXML("CIMMSG", "ACK", "ACK", "0");           //0:OK 1:NG
}
//---------------------------------------------------------------------------
void __fastcall CEQPXML::doQueryVID(char *pRx)
{
	TiXmlDocument doc;
	doc.Parse(pRx);
	TiXmlElement *pRoot = doc.FirstChildElement("Root");
	TiXmlElement *pData = pRoot->FirstChildElement("DATA");

	AnsiString strMsgID(pRoot->Attribute("MSGID"));
	AnsiString strData = pData->GetText();

	//const char *pTID = pRoot->Attribute("TID");
	//const char *pCEID = pData->Attribute("CEID");
	//const char *pSxFy = pData->Attribute("SxFy");
	//do something whith that message
	pRoot->SetAttribute("TYPE", "ACK");
	TiXmlElement *pSVID;
	TiXmlElement *pID;
	TiXmlElement *pValue;

    //---------------------------------------------------------------------------
    //Set param for SVID
    TStringList *strList = SplitString(g_IniFile.m_strLastFileName, "\\");
    AnsiString strLastFilePath = "";
    for (int i=0;i<strList->Count-1;i++)
    {
        strLastFilePath += strList->Strings[i] + "\\";
    }
    delete strList;

    //AnsiString strHeadType; (g_IniFile.m_nHeadType == 0) ? strHeadType = "SOLID" : strHeadType = "HOLLOW";
    //AnsiString strVacummOn; (g_IniFile.m_nVacummOn == 0) ? strVacummOn = "FAIL" : strVacummOn = "TRUE";
    //AnsiString strPressCheck; (g_IniFile.m_nPressCheck == 0) ? strPressCheck = "FAIL" : strPressCheck = "TRUE";
    //AnsiString strDummyCheck; (g_IniFile.m_nDummyCheck == 0) ? strDummyCheck = "FAIL" : strDummyCheck = "TRUE";

    //---------------------------------------------------------------------------
    //Add SVID
    TDateTime DT = TDateTime::CurrentDateTime();
    char SVIDIndex[25][4] = { 0 };
    strcpy(SVIDIndex[0], "1");
    strcpy(SVIDIndex[1], "2");
    strcpy(SVIDIndex[2], "3");
    strcpy(SVIDIndex[3], "4");
    strcpy(SVIDIndex[4], "5");
    strcpy(SVIDIndex[5], "6");
    strcpy(SVIDIndex[6], "7");
    strcpy(SVIDIndex[7], "8");
    strcpy(SVIDIndex[8], "51");
    strcpy(SVIDIndex[9], "55");

    char SVID[25][100] = { 0 };

    strcpy(SVID[0], DT.FormatString("yyyymmddhhnnss").c_str());
    strcpy(SVID[1], "CT-83");
    strcpy(SVID[2], "01");
    strcpy(SVID[3], "0.0.0.1");
    strcpy(SVID[4], "OP_ID");
    strcpy(SVID[5], g_IniFile.m_strLastFileName.c_str());
    strcpy(SVID[6], m_EqpStatus.c_str());                           //Equipment process state (I=Idle, R=Run, D=Down)
    strcpy(SVID[7], m_CIMStatus.c_str());                           //CIM control state (0=Offline, 1=Online/Local, 2=Online/Remote)
    strcpy(SVID[8], m_strMagzin1DCode.c_str());       //LoaderMagID
    strcpy(SVID[9], "This is 2D");       //SubstrateID

	for (int nIndex = 0; nIndex<25; nIndex++)
	{
		pSVID = new TiXmlElement("SVID");
		pID = new TiXmlElement("ID");
		pID->LinkEndChild(new TiXmlText(SVIDIndex[nIndex]));
		pValue = new TiXmlElement("VALUE");
		pValue->LinkEndChild(new TiXmlText(SVID[nIndex]));
		pSVID->LinkEndChild(pID);
		pSVID->LinkEndChild(pValue);
		pData->LinkEndChild(pSVID);
	}

    /*  //not yet to report ECID and DVID
    //---------------------------------------------------------------------------
    //Add ECID
    char ECIDIndex[1][4] = { 0 };
	strcpy(ECIDIndex[0], "621");

	char ECID[1][100] = { 0 };
	strcpy(ECID[0], g_IniFile.m_strApplicationPath.c_str());

	for (int nIndex = 0; nIndex<1; nIndex++)
	{
		pSVID = new TiXmlElement("ECID");
		pID = new TiXmlElement("ID");
		pID->LinkEndChild(new TiXmlText(ECIDIndex[nIndex]));
		pValue = new TiXmlElement("VALUE");
		pValue->LinkEndChild(new TiXmlText(ECID[nIndex]));
		pSVID->LinkEndChild(pID);
		pSVID->LinkEndChild(pValue);
		pData->LinkEndChild(pSVID);
	}

    //---------------------------------------------------------------------------
    //Add DVID
    LaserDiff m_strLaserDiff;
    m_strLaserDiff.strRDLD = "";
    m_strLaserDiff.strFDLD = "";
    m_strLaserDiff.strRULD = "";
    m_strLaserDiff.strFULD = "";
    generateLaserDiff(m_strLaserDiff);
    AnsiString strRDLD = m_strLaserDiff.strRDLD;
    AnsiString strFDLD = m_strLaserDiff.strFDLD;
    AnsiString strRULD = m_strLaserDiff.strRULD;
    AnsiString strFULD = m_strLaserDiff.strFULD;

	char DVID[5][100] = { 0 };
	strcpy(DVID[0], g_IniFile.m_strSetupEENum.c_str());
    strcpy(DVID[1], strRDLD.c_str());
    strcpy(DVID[2], strFDLD.c_str());
    strcpy(DVID[3], strRULD.c_str());
    strcpy(DVID[4], strFULD.c_str());

	for (int nIndex = 0; nIndex<5; nIndex++)
	{
		pSVID = new TiXmlElement("DVID");
		pID = new TiXmlElement("ID");
		pID->LinkEndChild(new TiXmlText(FormatFloat("0", nIndex + 1300).c_str()));
		pValue = new TiXmlElement("VALUE");
		pValue->LinkEndChild(new TiXmlText(DVID[nIndex]));
		pSVID->LinkEndChild(pID);
		pSVID->LinkEndChild(pValue);
		pData->LinkEndChild(pSVID);
	}
    */
	SendXML(doc);
}
//---------------------------------------------------------------------------
void __fastcall CEQPXML::doEventReportAck(char *pRx)
{
    /*
	TiXmlDocument doc;
	doc.Parse(pRx);
	TiXmlElement* pRoot = doc.FirstChildElement("Root");
	TiXmlElement* pData = pRoot->FirstChildElement("ACK");
	const char *pTID = pRoot->Attribute("TID");
	const char *pAckText = pData->GetText();

	if (pTID && pAckText) EventReportAck(pTID, pAckText);

	//do something for that
    */
}
//---------------------------------------------------------------------------
void __fastcall CEQPXML::doAlarmAck(char *pRx)
{
	/*
	TiXmlDocument doc;
	doc.Parse(pRx);
	TiXmlElement* pRoot = doc.FirstChildElement("Root");
	TiXmlElement* pData=pRoot->FirstChildElement("ACK");
	*/
	//do something for that
}
//---------------------------------------------------------------------------
void __fastcall CEQPXML::doRCMD(char *pRx)
{

	bool bRet = false;
	TiXmlDocument doc;
	doc.Parse(pRx);
	TiXmlElement *pRoot = doc.FirstChildElement("Root");
	TiXmlElement *pData = pRoot->FirstChildElement("DATA");

	AnsiString strData = pData->GetText();            //RUN/STOP/PAUSE/RESUME/PPSELECT,PPID/LOCAL/REMOTE
	AnsiString strSub = strData.SubString(0, 8);

	if (strSub == "RUN") bRet = StartProcess(true);
	else if (strSub == "RESUME") bRet = StartProcess(true);
	else if (strSub == "STOP") bRet = StartProcess(false);
	else if (strSub == "PAUSE") bRet = StartProcess(false);
	else if (strSub == "PPSELECT")
	{
        TStringList *StrList = SplitString(strData, ",");
        //AnsiString strName = strData.SubString(10, strData.Length() - 9);
		//AnsiString strFile;
		//strFile.sprintf("C:\\Product_Data\\%s\\%s.ini", strName, strName);
		//bRet = OpenFile(strFile);
        bRet = OpenFile(StrList->Strings[1]);

        delete StrList;
	}
	else if (strSub == "LOCAL")
	{
		m_CIMStatus = "1";
		bRet = true;
	}
	else if (strSub == "REMOTE")
	{
		m_CIMStatus = "2";
		bRet = true;
	}
    else if (strSub == "MES_MOVE_IN")
	{
        m_strMagzin1DCodeRX = "";
        TStringList *StrList = SplitString(strData, ",");
        for (int nX=0;nX<StrList->Count;nX++)
        {
            AnsiString strData1 = StrList->operator [](nX);
            AnsiString strSub1 = StrList->operator [](nX).SubString(0,14);
            if (strSub1 == "MOVE_IN_STATUS")
            {
                TStringList *StrList1 = SplitString(strData, "=");
                AnsiString strData2 = StrList1->operator [](1);
                if (strData2 == "PASS") m_strMagzin1DCodeRX = "Y";
                else m_strMagzin1DCodeRX = "N";
                delete StrList1;
            }
        }

        delete StrList;
        if (m_strMagzin1DCodeRX == "Y") bRet = true;
        else bRet = false;
	}
	else
	{
		SendXML("RCMD", "ACK", "ACK", "1");
		return;
	}

	if (bRet) SendXML("RCMD", "ACK", "ACK", "0");
	else SendXML("RCMD", "ACK", "ACK", "2");

}
//---------------------------------------------------------------------------
void __fastcall CEQPXML::doQueryPPID(char *pRx)
{
    /*
	TiXmlDocument doc;
	TiXmlElement *pRoot;
	TiXmlElement *pIDE;
	AnsiString strName;
	WIN32_FIND_DATA FindFileData;

	pRoot = new TiXmlElement("Root");
	pRoot->SetAttribute("MSGID", "QUERY_PPID");
	pRoot->SetAttribute("TYPE", "ACK");

	//strName.sprintf("%s*.ini",IniFile_Dir);
	HANDLE hFile = FindFirstFile(strName.c_str(), &FindFileData);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			//strName.sprintf("%s%s",IniFile_Dir,FindFileData.cFileName);
			pIDE = new TiXmlElement("PPID");
			pIDE->LinkEndChild(new TiXmlText(strName.c_str()));
			pRoot->LinkEndChild(pIDE);
		} while (FindNextFile(hFile, &FindFileData) != 0);
	}
	else
	{
		pIDE = new TiXmlElement("PPID");
		pIDE->LinkEndChild(new TiXmlText(""));
		pRoot->LinkEndChild(pIDE);
	}

	doc.LinkEndChild(pRoot);
	SendXML(doc);
    */
}
//---------------------------------------------------------------------------
void __fastcall CEQPXML::doQueryPPIDNew(char *pRx)
{
    /*
	TiXmlDocument doc;
	TiXmlElement *pRoot;
	TiXmlElement *pIDE;
	AnsiString strName;
	WIN32_FIND_DATA FindFileData;

	pRoot = new TiXmlElement("Root");
	pRoot->SetAttribute("MSGID", "QUERY_PPID");
	pRoot->SetAttribute("TYPE", "ACK");

	TSearchRec sr;
	int nRes = FindFirst("C:\\Product_Data\\*", faDirectory, sr);
	if (nRes == 0)
	{
		do
		{
			if (sr.Attr == faDirectory)
			{
				if (sr.Name != "." && sr.Name != ".." && sr.Name != "Message History" && sr.Name != "Error Message")
				{
					pIDE = new TiXmlElement("PPID");
					pIDE->LinkEndChild(new TiXmlText(sr.Name.c_str()));
					pRoot->LinkEndChild(pIDE);
				}
			}
		} while (FindNext(sr) == 0);
	}
	else
	{
		pIDE = new TiXmlElement("PPID");
		pIDE->LinkEndChild(new TiXmlText(""));
		pRoot->LinkEndChild(pIDE);
	}
	FindClose(sr);

	doc.LinkEndChild(pRoot);
	SendXML(doc);
    */
}
//---------------------------------------------------------------------------
void __fastcall CEQPXML::doQueryPPIDFullPath(char *pRx)
{
    TiXmlDocument doc;
	TiXmlElement *pRoot;
	TiXmlElement *pIDE;
	AnsiString strName;
	WIN32_FIND_DATA FindFileData;

	pRoot = new TiXmlElement("Root");
	pRoot->SetAttribute("MSGID", "QUERY_PPID");
	pRoot->SetAttribute("TYPE", "ACK");

    m_liststrFileName.clear();
    m_liststrForderName.clear();
    DirExplore("C:\\Product_Data", m_liststrForderName, m_liststrFileName);

    while (true)
    {
        if (m_liststrFileName.size()==0)
        {
            pIDE = new TiXmlElement("PPID");
		    pIDE->LinkEndChild(new TiXmlText(""));
		    pRoot->LinkEndChild(pIDE);
            break;
        }

        TStringList* strSplitPath = SplitString(m_liststrFileName.front(), "\\");
        if (strSplitPath->operator [](2) != "Error Message" && strSplitPath->Count != 3)
        {
            pIDE = new TiXmlElement("PPID");
            pIDE->LinkEndChild(new TiXmlText(m_liststrFileName.front().c_str()));
            pRoot->LinkEndChild(pIDE);
        }
        delete strSplitPath;
        m_liststrFileName.pop_front();

        if (m_liststrFileName.size()==0) break;
    }

    doc.LinkEndChild(pRoot);
	SendXML(doc);
}
//---------------------------------------------------------------------------
void __fastcall CEQPXML::doQueryPPBody(char *pRx)
{
    TiXmlDocument doc1;
    doc1.Parse(pRx);
	TiXmlElement* pRoot1 = doc1.FirstChildElement("Root");
	TiXmlElement* pData1=pRoot1->FirstChildElement("DATA");

	AnsiString strData=pData1->GetText();           //Recipe Name
	AnsiString strSxFx=pData1->Attribute("SxFy");

	//TIniFile *pIniFile = new TIniFile("C:\\Product_Data\\"+strData+"\\"+strData+".ini");
    TIniFile *pIniFile = new TIniFile(strData);

	TiXmlDocument doc;
	TiXmlElement* pRoot;
	TiXmlElement *pData;
	TiXmlElement *pParam;
	TiXmlElement *pProperty;
	AnsiString strName;
	WIN32_FIND_DATA FindFileData;

	pRoot=new TiXmlElement("Root");
	pRoot->SetAttribute("MSGID","QUERY_PPBODY");
	pRoot->SetAttribute("TYPE","ACK");

	AnsiString strTmp;
	pData=new TiXmlElement("DATA");
	pData->SetAttribute("PPID",strData.c_str());
	pData->SetAttribute("SxFy",strSxFx.c_str());

	char *ParamItem[]={
		//Loader
		"m_dLoaderClampMgzPos0","mm","A","0","1000",				//Loader Pos1
		"m_dLoaderClampMgzPos1","mm","A","0","1000",				//Loader Pos2
		"m_dLoaderClampMgzPos2","mm","A","0","1000",				//Loader Pos3
		"m_dMagazinePushPosY","mm","A","0","1000",					//Loader Push PosY
		"m_dMagazinePushPosZ","mm","A","0","1000",					//Loader Push PosZ
		"m_dMagazinePushPosUpFirstZ","mm","A","0","1000",			//Loader Push PosZ
		"m_dLoaderMgzPitch","mm","A","0","100",						//Loader Magzine Pitch
		"m_dLoaderUnClampMgzPos0","mm","A","0","1000",				//Loader Pos4
		"m_dLoaderUnClampMgzPos1","mm","A","0","1000",				//Loader Pos5
		"m_dLoaderUnClampMgzPos2","mm","A","0","1000",				//Loader Pos6

		"m_dLeftLaneChangerMgzPos","mm","A","0","1000",				//Left LC Substrate in Pos
		"m_dLeftLaneChangerSprayPos0","mm","A","0","1000",			//Left LC Substrate out Rear Pos
		"m_dLeftLaneChangerSprayPos1","mm","A","0","1000",			//Left LC Substrate out Front Pos

		//Work
		"m_dSprayReadyPos","mm","A","0","150",						//Spray Ready Pos
		"m_dStartSprayPosX0","mm","A","0","1000",					//Spray Ready Rear PosX
		"m_dStartSprayPosX1","mm","A","0","1000",					//Spray Ready Front PosX
		"m_dStartSprayPosY0","mm","A","0","1000",					//Spray Ready Rear PosY
		"m_dStartSprayPosY1","mm","A","0","1000",					//Spray Ready Front PosY
		"m_dSprayDistance","mm","A","0","500",						//Spray Distance
		"m_dSprayPitch","mm","A","0","500",							//Spray Y Pitch
		"m_dSprayPosZ","mm","A","0","150",							//Spray Ready PosZ
		"m_nSprayTimes","NULL","A","0","100",						//Spray times

		"m_dFluxTankAirPressure","NULL","A","0","1600",				//Spray Tank Air in
		"m_dSprayerAirPressure","NULL","A","0","1600",				//Spray Air out

		"m_nScaleSprayTime0","s","A","0","1000",					//Weight Scale time
		"m_nScaleSprayTimes0","NULL","A","0","1000",				//Weight Scale times
		"m_dWeightScaleAlarmUp","g","A","0","1000",					//Weight Up Limitation
		"m_dWeightScaleAlarmDown","g","A","0","1000",				//Weight Down Limitation

		"m_nAutoFillTime","s","A","0","120",						//Auto Fill Flux Duration

		"m_dSprayDelayTimeB","s","A","0","600",						//Delay Time of Before Spray 
		"m_dSprayDelayTimeA","s","A","0","600",						//Delay Time of After Spray 
		"m_dSuccBackDelayTime","s","A","0","600",					//Delay Time of Vacuum Off

		//UnLoader
		"m_dRightLaneChangerSprayPos0","mm","A","0","1000",			//Right LC Substrate in Rear Pos
		"m_dRightLaneChangerSprayPos1","mm","A","0","1000",			//Right LC Substrate in Front Pos
		"m_dCCDCheckPosX0","mm","A","0","1000",						//CCD Check PosX0
		"m_dCCDCheckPosY0","mm","A","0","1000",						//CCD Check PosY0
		"m_dCCDCheckPosX1","mm","A","0","1000",						//CCD Check PosX1
		"m_dCCDCheckPosY1","mm","A","0","1000",						//CCD Check PosY1
		"m_dCCDCheckPosX2","mm","A","0","1000",						//CCD Check PosX2
		"m_dCCDCheckPosY2","mm","A","0","1000",						//CCD Check PosY2
		"m_dCCDCheckPosX3","mm","A","0","1000",						//CCD Check PosX3
		"m_dCCDCheckPosY3","mm","A","0","1000",						//CCD Check PosY3
		"m_dRightLaneChangerDelayTime","s","A","0","600",			//Delay Time After CCD Check

		"m_dConveyerPos0","mm","A","0","1000",						//Substrate Out Pos 1
		"m_dConveyerPos1","mm","A","0","1000",						//Substrate Out Pos 2
		"m_dConveyerPos2","mm","A","0","1000",						//Substrate Out Pos 3
		"m_dConveyerPos3","mm","A","0","1000",						//Substrate Out Pos 4
		"m_dConveyerPos4","mm","A","0","1000",						//Substrate Out Pos 5
		"m_dNGMagPos","mm","A","0","1000",							//Substrate Out NG Mag Pos

		"m_bIsUseCCDCheckPos0","NULL","A","0","1",					//Check Box for using CCD Check Pos0
		"m_bIsUseCCDCheckPos1","NULL","A","0","1",					//Check Box for using CCD Check Pos1
		"m_bIsUseCCDCheckPos2","NULL","A","0","1",					//Check Box for using CCD Check Pos2
		"m_bIsUseCCDCheckPos3","NULL","A","0","1",					//Check Box for using CCD Check Pos3

		//Vision
		"m_dMarkScore0","NULL","A","0","255",						//Minimum Score for Black White algorithm
		"m_nLEDDimmer0","NULL","A","0","255",						//LED Light Scale

		//CleanSprayerLane
		"m_dCleanSprayPosX0","mm","A","0","1000",					//Spray Clean PosX 0
		"m_dCleanSprayPosY0","mm","A","0","1000",					//Spray Clean PosY 0
		"m_dCleanSprayPosX1","mm","A","0","1000",					//Spray Clean PosX 1
		"m_dCleanSprayPosY1","mm","A","0","1000",					//Spray Clean PosY 1
		"m_dCleanSprayPosX2","mm","A","0","1000",					//Spray Clean PosX 2
		"m_dCleanSprayPosY2","mm","A","0","1000",					//Spray Clean PosY 2
		"m_dCleanSprayPosX3","mm","A","0","1000",					//Spray Clean PosX 3
		"m_dCleanSprayPosY3","mm","A","0","1000",					//Spray Clean PosY 3
		"m_dCleanSprayPosZ","mm","A","0","150",						//Spray Clean PosZ 
		"m_nCleanSprayTimes","NULL","A","0","100",					//Clean X Direction times
		"m_nFullCleanSprayTimes","NULL","A","0","100",				//Clean Total times
		"m_dCleanSprayDistance","mm","A","0","500",					//Clean Distance
		"m_dSprayerCleanWaterPressure","NULL","A","0","1600",		//Clean Water out
		"m_dSprayerCleanAirPressure","NULL","A","0","1600",			//Clean Air out

		//Option
		"m_bUseSprayer","NULL","A","0","1",							//Is Use Sprayer					
		"m_bUseCCD","NULL","A","0","1",								//Is Use CCD
		"m_bIsMagazineUpFirst", "NULL", "A", "0", "1",				//Is Use MagazineUpFirst
		//以上為產品參數
		"END" };                                      //E:End


	if (FileExists(strData))
	{
		int nX = 0;
		while (1)
		{
			if (strcmp(ParamItem[nX * 5], "END") == 0) break;

			pParam = new TiXmlElement("PARAMETER");
			pParam->SetAttribute("NAME", ParamItem[nX * 5]);

			pProperty = new TiXmlElement("PROPERTY");
			pProperty->LinkEndChild(new TiXmlText("TRUE"));
			pParam->LinkEndChild(pProperty);

			for (int t = 0; t<3; t++)
			{
				pProperty = new TiXmlElement("PROPERTY");
				pProperty->LinkEndChild(new TiXmlText(ParamItem[nX * 5 + t]));
				pParam->LinkEndChild(pProperty);
			}

			if (false)
			//if (strcmp(ParamItem[nX * 5], "m_dLoaderClampMgzPos0") == 0)
			{
				/* Here Build Special Product Parameter
				AnsiString strScaleOffset = "";
				for (int nx = 0; nx<50; nx++)
				{
					strScaleOffset += pIniFile->ReadString("Offset_Table", "m_dScaleOffsetRear" + FormatFloat("0", nx), "0") + "/";
				}
				pProperty = new TiXmlElement("PROPERTY");
				AnsiString strResult = strScaleOffset;
				if (strResult.IsEmpty()) strResult = "NULL";
				pProperty->LinkEndChild(new TiXmlText(strResult.c_str()));
				pParam->LinkEndChild(pProperty);
				*/
			}
			else
			{
				pProperty = new TiXmlElement("PROPERTY");
				AnsiString strResult = pIniFile->ReadString(Product_Section, ParamItem[nX * 5], "0");
				if (strResult.IsEmpty()) strResult = "NULL";
				pProperty->LinkEndChild(new TiXmlText(strResult.c_str()));
				pParam->LinkEndChild(pProperty);
			}

			for (int t = 3; t<5; t++)
			{
				pProperty = new TiXmlElement("PROPERTY");
				pProperty->LinkEndChild(new TiXmlText(ParamItem[nX * 5 + t]));
				pParam->LinkEndChild(pProperty);
			}

			pData->LinkEndChild(pParam);
			nX++;
		}

		pRoot->LinkEndChild(pData);
		doc.LinkEndChild(pRoot);
		SendXML(doc);
	}
	else
	{
		pRoot->LinkEndChild(pData);
		doc.LinkEndChild(pRoot);
		SendXML(doc);
	}
}
//---------------------------------------------------------------------------
void __fastcall CEQPXML::doSetPPBody(char *pRx)
{
	TiXmlDocument doc1;
	doc1.Parse(pRx);
	TiXmlElement *pRoot1 = doc1.FirstChildElement("Root");
	TiXmlElement *pData1 = pRoot1->FirstChildElement("DATA");

	AnsiString strData = pData1->Attribute("PPID");

    char *ParamItem[]={
		//Loader
		"m_dLoaderClampMgzPos0", "mm", "A", "0", "1000",				//Loader Pos1
		"m_dLoaderClampMgzPos1", "mm", "A", "0", "1000",				//Loader Pos2
		"m_dLoaderClampMgzPos2", "mm", "A", "0", "1000",				//Loader Pos3
		"m_dMagazinePushPosY", "mm", "A", "0", "1000",					//Loader Push PosY
		"m_dMagazinePushPosZ", "mm", "A", "0", "1000",					//Loader Push PosZ
		"m_dMagazinePushPosUpFirstZ", "mm", "A", "0", "1000",			//Loader Push PosZ
		"m_dLoaderMgzPitch", "mm", "A", "0", "100",						//Loader Magzine Pitch
		"m_dLoaderUnClampMgzPos0", "mm", "A", "0", "1000",				//Loader Pos4
		"m_dLoaderUnClampMgzPos1", "mm", "A", "0", "1000",				//Loader Pos5
		"m_dLoaderUnClampMgzPos2", "mm", "A", "0", "1000",				//Loader Pos6

		"m_dLeftLaneChangerMgzPos", "mm", "A", "0", "1000",				//Left LC Substrate in Pos
		"m_dLeftLaneChangerSprayPos0", "mm", "A", "0", "1000",			//Left LC Substrate out Rear Pos
		"m_dLeftLaneChangerSprayPos1", "mm", "A", "0", "1000",			//Left LC Substrate out Front Pos

		//Work
		"m_dSprayReadyPos", "mm", "A", "0", "150",						//Spray Ready Pos
		"m_dStartSprayPosX0", "mm", "A", "0", "1000",					//Spray Ready Rear PosX
		"m_dStartSprayPosX1", "mm", "A", "0", "1000",					//Spray Ready Front PosX
		"m_dStartSprayPosY0", "mm", "A", "0", "1000",					//Spray Ready Rear PosY
		"m_dStartSprayPosY1", "mm", "A", "0", "1000",					//Spray Ready Front PosY
		"m_dSprayDistance", "mm", "A", "0", "500",						//Spray Distance
		"m_dSprayPitch", "mm", "A", "0", "500",							//Spray Y Pitch
		"m_dSprayPosZ", "mm", "A", "0", "150",							//Spray Ready PosZ
		"m_nSprayTimes", "NULL", "A", "0", "100",						//Spray times

		"m_dFluxTankAirPressure", "NULL", "A", "0", "1600",				//Spray Tank Air in
		"m_dSprayerAirPressure", "NULL", "A", "0", "1600",				//Spray Air out

		"m_nScaleSprayTime0", "s", "A", "0", "1000",					//Weight Scale time
		"m_nScaleSprayTimes0", "NULL", "A", "0", "1000",				//Weight Scale times
		"m_dWeightScaleAlarmUp", "g", "A", "0", "1000",					//Weight Up Limitation
		"m_dWeightScaleAlarmDown", "g", "A", "0", "1000",				//Weight Down Limitation

		"m_nAutoFillTime", "s", "A", "0", "120",						//Auto Fill Flux Duration

		"m_dSprayDelayTimeB", "s", "A", "0", "600",						//Delay Time of Before Spray 
		"m_dSprayDelayTimeA", "s", "A", "0", "600",						//Delay Time of After Spray 
		"m_dSuccBackDelayTime", "s", "A", "0", "600",					//Delay Time of Vacuum Off

		//UnLoader
		"m_dRightLaneChangerSprayPos0", "mm", "A", "0", "1000",			//Right LC Substrate in Rear Pos
		"m_dRightLaneChangerSprayPos1", "mm", "A", "0", "1000",			//Right LC Substrate in Front Pos
		"m_dCCDCheckPosX0", "mm", "A", "0", "1000",						//CCD Check PosX0
		"m_dCCDCheckPosY0", "mm", "A", "0", "1000",						//CCD Check PosY0
		"m_dCCDCheckPosX1", "mm", "A", "0", "1000",						//CCD Check PosX1
		"m_dCCDCheckPosY1", "mm", "A", "0", "1000",						//CCD Check PosY1
		"m_dCCDCheckPosX2", "mm", "A", "0", "1000",						//CCD Check PosX2
		"m_dCCDCheckPosY2", "mm", "A", "0", "1000",						//CCD Check PosY2
		"m_dCCDCheckPosX3", "mm", "A", "0", "1000",						//CCD Check PosX3
		"m_dCCDCheckPosY3", "mm", "A", "0", "1000",						//CCD Check PosY3
		"m_dRightLaneChangerDelayTime", "s", "A", "0", "600",			//Delay Time After CCD Check

		"m_dConveyerPos0", "mm", "A", "0", "1000",						//Substrate Out Pos 1
		"m_dConveyerPos1", "mm", "A", "0", "1000",						//Substrate Out Pos 2
		"m_dConveyerPos2", "mm", "A", "0", "1000",						//Substrate Out Pos 3
		"m_dConveyerPos3", "mm", "A", "0", "1000",						//Substrate Out Pos 4
		"m_dConveyerPos4", "mm", "A", "0", "1000",						//Substrate Out Pos 5
		"m_dNGMagPos", "mm", "A", "0", "1000",							//Substrate Out NG Mag Pos

		"m_bIsUseCCDCheckPos0", "NULL", "A", "0", "1",					//Check Box for using CCD Check Pos0
		"m_bIsUseCCDCheckPos1", "NULL", "A", "0", "1",					//Check Box for using CCD Check Pos1
		"m_bIsUseCCDCheckPos2", "NULL", "A", "0", "1",					//Check Box for using CCD Check Pos2
		"m_bIsUseCCDCheckPos3", "NULL", "A", "0", "1",					//Check Box for using CCD Check Pos3

		//Vision
		"m_dMarkScore0", "NULL", "A", "0", "255",						//Minimum Score for Black White algorithm
		"m_nLEDDimmer0", "NULL", "A", "0", "255",						//LED Light Scale

		//CleanSprayerLane
		"m_dCleanSprayPosX0", "mm", "A", "0", "1000",					//Spray Clean PosX 0
		"m_dCleanSprayPosY0", "mm", "A", "0", "1000",					//Spray Clean PosY 0
		"m_dCleanSprayPosX1", "mm", "A", "0", "1000",					//Spray Clean PosX 1
		"m_dCleanSprayPosY1", "mm", "A", "0", "1000",					//Spray Clean PosY 1
		"m_dCleanSprayPosX2", "mm", "A", "0", "1000",					//Spray Clean PosX 2
		"m_dCleanSprayPosY2", "mm", "A", "0", "1000",					//Spray Clean PosY 2
		"m_dCleanSprayPosX3", "mm", "A", "0", "1000",					//Spray Clean PosX 3
		"m_dCleanSprayPosY3", "mm", "A", "0", "1000",					//Spray Clean PosY 3
		"m_dCleanSprayPosZ", "mm", "A", "0", "150",						//Spray Clean PosZ 
		"m_nCleanSprayTimes", "NULL", "A", "0", "100",					//Clean X Direction times
		"m_nFullCleanSprayTimes", "NULL", "A", "0", "100",				//Clean Total times
		"m_dCleanSprayDistance", "mm", "A", "0", "500",					//Clean Distance
		"m_dSprayerCleanWaterPressure", "NULL", "A", "0", "1600",		//Clean Water out
		"m_dSprayerCleanAirPressure", "NULL", "A", "0", "1600",			//Clean Air out

		//Option
		"m_bUseSprayer", "NULL", "A", "0", "1",							//Is Use Sprayer					
		"m_bUseCCD", "NULL", "A", "0", "1",								//Is Use CCD
		"m_bIsMagazineUpFirst", "NULL", "A", "0", "1",				    //Is Use MagazineUpFirst
		//以上為產品參數
		"END" };                                      //E:End

    TiXmlElement *pParam = pData1->FirstChildElement("PARAMETER");
    bool bResult = false;
    int nSize = 0;
    int nX=0;
    while (true)
    {
        if (pParam == NULL) break;
        AnsiString strParam = pParam->GetText();
        int nPos = strParam.Pos(",");
        AnsiString strA = strParam.SubString(1, nPos - 1);
        if (strcmp(ParamItem[nX*5],"END")==0) {bResult = true; break;}
        else if (strcmp(ParamItem[nX*5],strA.c_str())!=0) {bResult = false; break;}
        else bResult = true;
        nSize++;
        nX++;
        pParam = pParam->NextSiblingElement("PARAMETER");
    }
    if (nSize != 72) bResult = false;

    if (bResult == true)
    {
        //If there is no following path, to add new folder
        TStringList* strSplitPath = SplitString(strData, "\\");
        AnsiString strPath = strSplitPath->operator [](0) + "\\";
        for (int nX=0;nX<strSplitPath->Count-2;nX++)
        {
            strPath += strSplitPath->operator [](nX+1) + "\\";
            if (!FileExists(strPath.c_str())) _mkdir(strPath.c_str());
        }
        delete strSplitPath;

        //new IniFile
        TIniFile *pIniFile = new TIniFile(strData);

        TiXmlElement *pParam = pData1->FirstChildElement("PARAMETER");

        while (1)
        {
            if (pParam == NULL) break;
            AnsiString strParam = pParam->GetText();
            int nPos = strParam.Pos(",");
            AnsiString strA = strParam.SubString(1, nPos - 1);
            AnsiString strB = strParam.SubString(nPos + 1, strParam.Length() - strA.Length() + 1);

			if (false)
            //if (strA == "m_strHeadScal")
            {
                /*  Here Build Special Product Parameter 
				//if not in MachineParam then add.
                TStringList* strList = SplitString(g_IniFile.m_strHeadScals, "/");
                bool bIsInputINstrList = false;
                for (int i=0;i<strList->Count;i++)
                {
                    if (strB == strList->Strings[i])
                    {
                        bIsInputINstrList = true;
                        break;
                    }
                    else bIsInputINstrList = false;
                }
                if (bIsInputINstrList == false && strB != "")
                {
                    g_IniFile.m_strHeadScals += (strB+"/");
                    g_IniFile.MachineFile(false);
                }
                delete strList;
                //add in ProductParam
                pIniFile->WriteString(Product_Section, strA, strB);
				*/
            }
            else
            {
                pIniFile->WriteString(Product_Section, strA, strB);
            }
            pParam = pParam->NextSiblingElement("PARAMETER");
        }

        SendXML("SET_PPBODY", "ACK", "ACK", "0");
        
	    delete pIniFile;
    }
    else SendXML("SET_PPBODY", "ACK", "ACK", "3");
}
//---------------------------------------------------------------------------
void __fastcall CEQPXML::SendXML(char *pMSGID, char *pType, char *pTextName, char *pValue, char *pTID)
{
	char send[MAX_SEND_BUFF] = { 0 };
	char A[MAX_SEND_BUFF] = { 0 };

	try
	{
		sprintf(A, "<?xml version=\"1.0\" encoding=\"utf-8\" ?><Root MSGID=\"%s\" TYPE=\"%s\" TID=\"%s\" ><%s>%s</%s></Root>", pMSGID, pType, pTID, pTextName, pValue, pTextName);

		sprintf(send, "%c%c%c%c%c%s", 0x00, 0x00, 0x00, strlen(A) + 1, 0x00, A);


		if (m_pSocket != NULL && m_bOnLine)
		{
			m_pSocket->SendBuf(send, strlen(A) + 5);
			//m_pSocket->SendBuf(send,MAX_SEND_BUFF);
			//g_IniFile.AddLog(send,MAX_SEND_BUFF);
		}
	}
	catch (const EAccessViolation &e)
	{
		Application->MessageBox(e.Message.c_str(), "Look2", MB_OK);
	}

}
//---------------------------------------------------------------------------
void __fastcall CEQPXML::SendXML(TiXmlDocument &theDoc)
{
	try
	{
		TiXmlPrinter printer;
		theDoc.Accept(&printer);
		const char *NewString = printer.CStr();

		long nLen = strlen(NewString) + 1;
		//char *send=new char[strlen(NewString)+5];
		char *send = new char[MAX_SEND_BUFF];

		char strLen[4] = { 0 };
		strLen[0] = (nLen & 0xff000000) >> 24;
		strLen[1] = (nLen & 0x00ff0000) >> 16;
		strLen[2] = (nLen & 0x0000ff00) >> 8;
		strLen[3] = (nLen & 0x000000ff);

		sprintf(send, "%c%c%c%c%c%s", strLen[0], strLen[1], strLen[2], strLen[3], 0x00, NewString);

		if (m_pSocket != NULL && m_bOnLine)
		{
			m_pSocket->SendBuf(send, strlen(NewString) + 5);
			//m_pSocket->SendBuf(send,MAX_SEND_BUFF);                  //note To write log
			//g_IniFile.AddLog("Send XML",8);                          //note To write log

            AnsiString AAA = printer.CStr();
            g_IniFile.AddLog(AAA.c_str(), AAA.Length());
		}
		delete send;
	}
	catch (const EAccessViolation &e)
	{
		Application->MessageBox(e.Message.c_str(), "Look3", MB_OK);
		//delete send;
	}
}
//---------------------------------------------------------------------------

__fastcall CEQPXML::CEQPXML()
{
    m_pSocket = NULL;
    m_EqpStatus = "I";
    m_CIMStatus = "0";
	receiveRx = (char *)malloc(30000);//new char[30000];
    receive = (char *)malloc(30000);//new char[30000];

    m_strSubstrate2DCode = "Substrate2DCode";
    m_strMagzin1DCode = "Magzin1DCode";
    m_strMagzin1DCodeRX = "";
    m_strBuffer = "";
}
//---------------------------------------------------------------------------
__fastcall CEQPXML::~CEQPXML()
{
    free( receiveRx);
    free( receive);
}
//---------------------------------------------------------------------------

void __fastcall CEQPXML::StartComm(TCustomWinSocket *pSocket)
{
     m_pSocket = pSocket;
}
//---------------------------------------------------------------------------
void __fastcall CEQPXML::EndComm()
{
     m_pSocket = NULL;
}

//---------------------------------------------------------------------------
void __fastcall CEQPXML::ProcessCIM()
{
    /*
    long nSize = 0;

    try
    {
        //receiveRx=(char *)VirtualAlloc(NULL, 30000, MEM_COMMIT, PAGE_READWRITE);//(char *)malloc(30000);//new char[30000];
        //receive=(char *)VirtualAlloc(NULL, 30000, MEM_COMMIT, PAGE_READWRITE);///(char *)malloc(30000);//new char[30000];

        if (receive==NULL || receiveRx==NULL) return;

        memset(receiveRx,0x00,30000);
        memset(receive,0x00,30000);

        m_pSocket->ReceiveBuf(receiveRx,30000);

        TiXmlDocument doc;
        int nIndex = 0;

        while(1)
        {

            doc.Clear();
            memset(receive,0x00,30000);

            if(nIndex>=30000) break;

            nSize=(receiveRx[0+nIndex]<<24)+(receiveRx[1+nIndex]<<16)+(receiveRx[2+nIndex]<<8)+receiveRx[3+nIndex]+4;//+5;
            if(nSize<=5 || nSize>=30000)
                break;

            memcpy(receive,receiveRx+nIndex,nSize);
            nIndex+=nSize;
            if(nIndex>=30000) break;


            doc.Parse(receive+5);
            TiXmlElement* pRoot = doc.FirstChildElement("Root");
            if(pRoot==NULL) break;
            //TiXmlElement* pData=pRoot->FirstChildElement("DATA");

            AnsiString strMsgID(pRoot->Attribute("MSGID"));
            //AnsiString strData=pData->GetText();

            if (strMsgID=="HOST_STATUS") doHostStatus(receive+5);                         //Local realtime renew CIMAP status
            else if (strMsgID=="DTSET") doDTSet(receive+5);                               // no used
            else if (strMsgID=="CIMMSG") doCIMMsg(receive+5);                             //Secs/Gem S10F3   CIM show TEXT to machine
            else if (strMsgID=="QUERY_VID") doQueryVID(receive+5);                        //Secs/Gem S1F3,S2F13  CIM Use SCID,ECID,DVID get machine param
            else if (strMsgID=="EVENT_REPORT") doEventReportAck(receive+5);               //Local Rise ECID 1,3,115
            else if (strMsgID=="ALARM") doAlarmAck(receive+5);                            // no used
            else if (strMsgID=="RCMD") doRCMD(receive+5);                                 //Secs/Gem S2F21,S2F41 CIM send RCMD, change machine /RUN/STOP/PAUSE/RESUME/PPSELECT,PPID/LOCAL/REMOTE
            else if (strMsgID=="QUERY_PPID") doQueryPPIDFullPath(receive+5);              //Secs/Gem S7F19   CIM Find Recipe folder and file name
            else if (strMsgID=="QUERY_PPBODY") doQueryPPBody(receive+5);                  //Secs/Gem S7F25   CIM Use Recipe file name get all recipe param
            else if (strMsgID=="SET_PPBODY") doSetPPBody(receive+5);                      //Secs/Gem S7F23   CIM Use param and value modify recipe, not add a new recipy

        }
	}
	catch(const EAccessViolation &e)
	{
		//Application->MessageBox(e.Message.c_str(), "Look", MB_OK);
		g_IniFile.AddLog("catch ProcessCIM",16);
		//delete receive;
    }
    */
}

//---------------------------------------------------------------------------
void __fastcall CEQPXML::ProcessCIMstr()
{
    try
    {
        TiXmlDocument doc;
        //-------------------------------------------------------------
        AnsiString strGet = m_pSocket->ReceiveText();

        while (true)
        {
            doc.Clear();

            if (m_strBuffer != "")
            {
                m_strBuffer += strGet;
                if (m_nSizeBuffer > m_strBuffer.Length())
                {
                    break;
                }
                else
                {
                    strGet = m_strBuffer;
                    m_strBuffer = "";
                    m_nSizeBuffer = 0;
                }
            }

            AnsiString strSize = strGet.SubString(0,5);
            int nSize0; ((int)strSize.c_str()[0]>=0) ? nSize0 = (int)strSize.c_str()[0]: nSize0 = (256+(int)strSize.c_str()[0]);
            int nSize1; ((int)strSize.c_str()[1]>=0) ? nSize1 = (int)strSize.c_str()[1]: nSize1 = (256+(int)strSize.c_str()[1]);
            int nSize2; ((int)strSize.c_str()[2]>=0) ? nSize2 = (int)strSize.c_str()[2]: nSize2 = (256+(int)strSize.c_str()[2]);
            int nSize3; ((int)strSize.c_str()[3]>=0) ? nSize3 = (int)strSize.c_str()[3]: nSize3 = (256+(int)strSize.c_str()[3]);
            int nSize4; ((int)strSize.c_str()[4]>=0) ? nSize4 = (int)strSize.c_str()[4]: nSize4 = (256+(int)strSize.c_str()[4]);
            int nSize = (nSize0<<24)+(nSize1<<16)+(nSize2<<8)+(nSize3<<0)+nSize4+4;

            if (strGet.Length()<nSize)
            {
                m_nSizeBuffer = nSize;
                m_strBuffer += strGet;
                break;
            }

            AnsiString strSubGet = strGet.SubString(6, nSize-7);

            doc.Parse(strSubGet.c_str());
            TiXmlElement* pRoot = doc.FirstChildElement("Root");
            if(pRoot==NULL) break;
            AnsiString strMsgID(pRoot->Attribute("MSGID"));
            if (strMsgID=="HOST_STATUS") doHostStatus(strSubGet.c_str());                         //Local realtime renew CIMAP status
            else if (strMsgID=="DTSET") doDTSet(strSubGet.c_str());                               // no used
            else if (strMsgID=="CIMMSG") doCIMMsg(strSubGet.c_str());                             //Secs/Gem S10F3   CIM show TEXT to machine
            else if (strMsgID=="QUERY_VID") doQueryVID(strSubGet.c_str());                        //Secs/Gem S1F3,S2F13  CIM Use SCID,ECID,DVID get machine param
            else if (strMsgID=="EVENT_REPORT") doEventReportAck(strSubGet.c_str());               //Local Rise ECID 1,3,115
            else if (strMsgID=="ALARM") doAlarmAck(strSubGet.c_str());                            // no used
            else if (strMsgID=="RCMD") doRCMD(strSubGet.c_str());                                 //Secs/Gem S2F21,S2F41 CIM send RCMD, change machine /RUN/STOP/PAUSE/RESUME/PPSELECT,PPID/LOCAL/REMOTE
            else if (strMsgID=="QUERY_PPID") doQueryPPIDFullPath(strSubGet.c_str());              //Secs/Gem S7F19   CIM Find Recipe folder and file name
            else if (strMsgID=="QUERY_PPBODY") doQueryPPBody(strSubGet.c_str());                  //Secs/Gem S7F25   CIM Use Recipe file name get all recipe param
            else if (strMsgID=="SET_PPBODY") doSetPPBody(strSubGet.c_str());                      //Secs/Gem S7F23   CIM Use param and value modify recipe, not add a new recipy


            strGet = strGet.SubString(nSize+1, strGet.Length()-nSize);
            //g_IniFile.AddLog("--------------------",20);
            //g_IniFile.AddLog(strGet.c_str(),strGet.Length());
            //g_IniFile.AddLog(IntToStr(strGet.Length()).c_str(),IntToStr(strGet.Length()).Length());
            //g_IniFile.AddLog("--------------------",20);
            if (strGet == "")
                break;
        }
	}
	catch(const EAccessViolation &e)
	{
		//Application->MessageBox(e.Message.c_str(), "Look", MB_OK);
		g_IniFile.AddLog("catch ProcessCIM",16);
    }

}
//---------------------------------------------------------------------------
void __fastcall CEQPXML::SendEventReport(char *pEvent,char *pTID)
{

        SendXML("EVENT_REPORT","RPT","CEID",pEvent,pTID);

}
//---------------------------------------------------------------------------
void __fastcall CEQPXML::SendAlarmMessage(char *pID,char *pText)
{
    TiXmlDocument doc;
    TiXmlElement* pRoot;

    pRoot = new TiXmlElement("Root");
    pRoot->SetAttribute("MSGID","ALARM");
    pRoot->SetAttribute("TYPE","RPT");

    TiXmlElement *pIDE = new TiXmlElement("ID");
    pIDE->LinkEndChild(new TiXmlText(pID));

	TiXmlElement *pTxt = new TiXmlElement("TEXT");
    pTxt->LinkEndChild(new TiXmlText(pText));

    pRoot->LinkEndChild(pIDE);
    pRoot->LinkEndChild(pTxt);

    doc.LinkEndChild(pRoot);
    SendXML(doc);
}




/*
<!--EQ上拋EAP，請求上拋上層系統判斷是否OK-->
<!--CMD為命令類別，暫訂"DEVICE_PRECHECK"，若要需求再作修改-->
<!--TID為時間標籤，格式yyyyMMddHHmmsszzzz-->
<!--IP為機台內部IP，例如192.168.101.101-->
<!--RCPID為機台目前使用的Recipe-->
<!--EQPID為機號，例如：K001JL-->
<!--TIME為當前時間，格式yyyy/MM/dd HH:mm:ss-->

<?xml version="1.0" encoding="utf-8"?>
<CMD CMD="DEVICE_PRECHECK" Type="Request" TID="201303080834369056" Sys="mes">
    <HEADER IP="192.168.101.201" PATH="mes" RCPID="12003123" 	EQPID="3013DS" TIME="2013/03/08 08:34:36" />
    <DEVICE_INFO>
		<LOTID VALUE="20D3B425.1" />
		<DEVICE_TYPE VALUE="COVER/CARRIER" />
		<DEVICE_ID VALUE="上蓋或載板ID" />
		<!--其他依user需求再擴充-->
    </DEVICE_INFO>	
</CMD>
*/


