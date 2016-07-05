//---------------------------------------------------------------------------


#pragma hdrstop

#include "IniFile.h"
#include <IniFiles.hpp>
#include "time.h"
#include <dir.h>
#include "stdlib.h"
#include <stdio.h>

#define ErrorMessage_Dir "Error Message\\"
#define ErrorMessageFileName "C83ErrorMessage.ini"
#define ErrorMessageEngFileName "C83ErrorMessageEng.ini"
#define UserName "User.sis"
#define MachineFileName "C83Machine.sis"

CIniFile g_IniFile;

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------

void __fastcall CIniFile::MachineFile(bool bRead)
{
  AnsiString strFile;
  TIniFile *pIniFile;
                    
  strFile.sprintf("%s%s",IniFile_Dir,MachineFileName);
  pIniFile = new TIniFile(strFile);

 //System
  DDXFile_Int(bRead,pIniFile,System_Section,"Language",m_nLanguageMode);
  DDXFile_Int(bRead,pIniFile,System_Section,"Priviledge",m_nPriviledge);
  DDXFile_String(bRead,pIniFile,System_Section,"ARTPassword",m_strARTPassword,"CLARE");
  DDXFile_String(bRead,pIniFile,System_Section,"ENGPassword",m_strENGPassword,"123");
  DDXFile_String(bRead,pIniFile,System_Section,"LastFileName",m_strLastFileName,"C:\\Product Data\\Default.ini");

  //Machine
  for(int nIndex=0;nIndex<MAX_AXIS;nIndex++)
  {
        DDXFile_Float(bRead,pIniFile,Machine_Section,"JogSpeed"+FormatFloat("0",nIndex+1),m_dJogSpeed[nIndex],30.0);
        DDXFile_Float(bRead,pIniFile,Machine_Section,"ACCSpeed"+FormatFloat("0",nIndex+1),m_dACCSpeed[nIndex],0.1);
        DDXFile_Float(bRead,pIniFile,Machine_Section,"DECSpeed"+FormatFloat("0",nIndex+1),m_dDECSpeed[nIndex],0.1);
        DDXFile_Float(bRead,pIniFile,Machine_Section,"WorkSpeed"+FormatFloat("0",nIndex+1),m_dWorkSpeed[nIndex],50.0); 
  }

  DDXFile_Float(bRead,pIniFile,Machine_Section,"m_dMgzStartPos",m_dMgzStartPos,0.0);
  DDXFile_Float(bRead,pIniFile,Machine_Section,"m_dMgzStartPosUpFirst",m_dMgzStartPosUpFirst,0.0);
  DDXFile_Float(bRead,pIniFile,Machine_Section,"m_dMgzPitch",m_dMgzPitch,0.0);
  DDXFile_Int(bRead,pIniFile,Machine_Section,"m_nMgzSize",m_nMgzSize);



  DDXFile_Float(bRead,pIniFile,Machine_Section,"m_dScaleSprayPosX0",m_dScaleSprayPosX[0],0.0);
  DDXFile_Float(bRead,pIniFile,Machine_Section,"m_dScaleSprayPosY0",m_dScaleSprayPosY[0],0.0);
  DDXFile_Float(bRead,pIniFile,Machine_Section,"m_dScaleSprayPosZ0",m_dScaleSprayPosZ[0],0.0);
  DDXFile_Float(bRead,pIniFile,Machine_Section,"m_dScaleSprayPosX1",m_dScaleSprayPosX[1],0.0);
  DDXFile_Float(bRead,pIniFile,Machine_Section,"m_dScaleSprayPosY1",m_dScaleSprayPosY[1],0.0);
  DDXFile_Float(bRead,pIniFile,Machine_Section,"m_dScaleSprayPosZ1",m_dScaleSprayPosZ[1],0.0);
  //DDXFile_Int(bRead,pIniFile,Machine_Section,"m_nScaleSprayTime0",m_nScaleSprayTime[0]);        //move to product
  DDXFile_Int(bRead,pIniFile,Machine_Section,"m_nScaleSprayTime1",m_nScaleSprayTime[1]);
  //DDXFile_Int(bRead,pIniFile,Machine_Section,"m_nScaleSprayTimes0",m_nScaleSprayTimes[0]);      //move to product
  DDXFile_Int(bRead,pIniFile,Machine_Section,"m_nScaleSprayTimes1",m_nScaleSprayTimes[1]);
  DDXFile_Float(bRead,pIniFile,Machine_Section,"m_dScaleSprayDelayTime",m_dScaleSprayDelayTime,0.0);

  DDXFile_Float(bRead,pIniFile,Machine_Section,"m_dLDYUnLoadClamperAlarm",m_dLDYUnLoadClamperAlarm,0.0);
  DDXFile_Float(bRead,pIniFile,Machine_Section,"m_dSprayLaneAlarmX0",m_dSprayLaneAlarmX[0],0.0);
  DDXFile_Float(bRead,pIniFile,Machine_Section,"m_dSprayLaneAlarmY0",m_dSprayLaneAlarmY[0],0.0);
  DDXFile_Float(bRead,pIniFile,Machine_Section,"m_dSprayLaneAlarmX1",m_dSprayLaneAlarmX[1],0.0);
  DDXFile_Float(bRead,pIniFile,Machine_Section,"m_dSprayLaneAlarmY1",m_dSprayLaneAlarmY[1],0.0);
  DDXFile_Float(bRead,pIniFile,Machine_Section,"m_dSprayLaneAlarmZ",m_dSprayLaneAlarmZ,0.0);

  DDXFile_String(bRead,pIniFile,Machine_Section,"m_strAutoCleanSprayLaneDateTime0",m_strAutoCleanSprayLaneDateTime[0],"00:00");
  DDXFile_String(bRead,pIniFile,Machine_Section,"m_strAutoCleanSprayLaneDateTime1",m_strAutoCleanSprayLaneDateTime[1],"00:00");
  DDXFile_String(bRead,pIniFile,Machine_Section,"m_strAutoCleanSprayLaneDateTime2",m_strAutoCleanSprayLaneDateTime[2],"00:00");

  DDXFile_Bool(bRead,pIniFile,Machine_Section,"m_bForceEject",m_bForceEject,false);
  DDXFile_Bool(bRead,pIniFile,Machine_Section,"m_bUsePreAutoWeightScale",m_bUsePreAutoWeightScale,true);
  DDXFile_Bool(bRead,pIniFile,Machine_Section,"m_bUseAutoCleanSprayLane",m_bUseAutoCleanSprayLane,false);
  DDXFile_Bool(bRead,pIniFile,Machine_Section,"m_bIsMgzUpFirst",m_bIsMgzUpFirst,false);
  DDXFile_Bool(bRead,pIniFile,Machine_Section,"m_bStopLoader",m_bStopLoader,false);

  DDXFile_Int(bRead,pIniFile,Machine_Section,"m_nRailOption",m_nRailOption);
  delete pIniFile;
}
//---------------------------------------------------------------------------
void __fastcall CIniFile::ProductFile(char *strFileName,bool bRead)                                                            
{                                                                                                                              
  AnsiString strName;                                                                                                          
  TIniFile *pIniFile;                                                                                                          
  pIniFile = new TIniFile(strFileName);

  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dLoaderClampMgzPos0",m_dLoaderClampMgzPos[0],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dLoaderClampMgzPos1",m_dLoaderClampMgzPos[1],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dLoaderClampMgzPos2",m_dLoaderClampMgzPos[2],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dMagazinePushPosY",m_dMagazinePushPosY,0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dMagazinePushPosZ",m_dMagazinePushPosZ,0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dMagazinePushPosUpFirstZ",m_dMagazinePushPosUpFirstZ,0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dLoaderMgzPitch",m_dLoaderMgzPitch,0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dLoaderUnClampMgzPos0",m_dLoaderUnClampMgzPos[0],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dLoaderUnClampMgzPos1",m_dLoaderUnClampMgzPos[1],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dLoaderUnClampMgzPos2",m_dLoaderUnClampMgzPos[2],0.0);

  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dLeftLaneChangerMgzPos",m_dLeftLaneChangerMgzPos,0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dLeftLaneChangerSprayPos0",m_dLeftLaneChangerSprayPos[0],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dLeftLaneChangerSprayPos1",m_dLeftLaneChangerSprayPos[1],0.0);

  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dRightLaneChangerSprayPos0",m_dRightLaneChangerSprayPos[0],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dRightLaneChangerSprayPos1",m_dRightLaneChangerSprayPos[1],0.0);

  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dStartSprayPosX0",m_dStartSprayPosX[0],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dStartSprayPosX1",m_dStartSprayPosX[1],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dStartSprayPosY0",m_dStartSprayPosY[0],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dStartSprayPosY1",m_dStartSprayPosY[1],0.0);

  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dSprayDistance",m_dSprayDistance,0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dSprayPitch",m_dSprayPitch,0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dSprayPosZ",m_dSprayPosZ,0.0);
  DDXFile_Int(bRead,pIniFile,Product_Section,"m_nSprayTimes",m_nSprayTimes,1);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dSprayReadyPos",m_dSprayReadyPos,0.0);

  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dRightLaneChangerSprayPos0",m_dRightLaneChangerSprayPos[0],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dRightLaneChangerSprayPos1",m_dRightLaneChangerSprayPos[1],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dCCDCheckPosX0",m_dCCDCheckPosX[0],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dCCDCheckPosY0",m_dCCDCheckPosY[0],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dCCDCheckPosX1",m_dCCDCheckPosX[1],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dCCDCheckPosY1",m_dCCDCheckPosY[1],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dCCDCheckPosX2",m_dCCDCheckPosX[2],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dCCDCheckPosY2",m_dCCDCheckPosY[2],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dCCDCheckPosX3",m_dCCDCheckPosX[3],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dCCDCheckPosY3",m_dCCDCheckPosY[3],0.0);
  DDXFile_Bool(bRead,pIniFile,Product_Section,"m_bIsUseCCDCheckPos0",m_bIsUseCCDCheckPos[0],false);
  DDXFile_Bool(bRead,pIniFile,Product_Section,"m_bIsUseCCDCheckPos1",m_bIsUseCCDCheckPos[1],false);
  DDXFile_Bool(bRead,pIniFile,Product_Section,"m_bIsUseCCDCheckPos2",m_bIsUseCCDCheckPos[2],false);
  DDXFile_Bool(bRead,pIniFile,Product_Section,"m_bIsUseCCDCheckPos3",m_bIsUseCCDCheckPos[3],false);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dRightLaneChangerDelayTime",m_dRightLaneChangerDelayTime,0.0);

  DDXFile_Float(bRead,pIniFile,Product_Section,"m_nLEDDimmer0",m_nLEDDimmer[0],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_nLEDDimmer1",m_nLEDDimmer[1],0.0);

  DDXFile_Bool(bRead,pIniFile,Product_Section,"m_bUseSprayer",m_bUseSprayer,false);
  DDXFile_Bool(bRead,pIniFile,Product_Section,"m_bUseCCD",m_bUseCCD,false);
  DDXFile_Bool(bRead,pIniFile,Product_Section,"m_bIsMagazineUpFirst",m_bIsMagazineUpFirst,false);

  DDXFile_Int(bRead,pIniFile,Product_Section,"m_nMinThreshold",m_nMinThreshold,125);

  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dFluxTankAirPressure",m_dFluxTankAirPressure,0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dSprayerAirPressure",m_dSprayerAirPressure,0.0);

  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dMarkScore0",m_dMarkScore0,0.0);

  DDXFile_Int(bRead,pIniFile,Product_Section,"m_nScaleSprayTime0",m_nScaleSprayTime[0]);
  DDXFile_Int(bRead,pIniFile,Product_Section,"m_nScaleSprayTimes0",m_nScaleSprayTimes[0]);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dWeightScaleAlarmUp",m_dWeightScaleAlarmUp,0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dWeightScaleAlarmDown",m_dWeightScaleAlarmDown,0.0);

  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dCleanSprayPosX0",m_dCleanSprayPosX[0],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dCleanSprayPosY0",m_dCleanSprayPosY[0],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dCleanSprayPosX1",m_dCleanSprayPosX[1],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dCleanSprayPosY1",m_dCleanSprayPosY[1],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dCleanSprayPosX2",m_dCleanSprayPosX[2],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dCleanSprayPosY2",m_dCleanSprayPosY[2],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dCleanSprayPosX3",m_dCleanSprayPosX[3],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dCleanSprayPosY3",m_dCleanSprayPosY[3],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dCleanSprayPosZ",m_dCleanSprayPosZ,0.0);
  DDXFile_Int(bRead,pIniFile,Product_Section,"m_nCleanSprayTimes",m_nCleanSprayTimes);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dCleanSprayDistance",m_dCleanSprayDistance,0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dSprayerCleanWaterPressure",m_dSprayerCleanWaterPressure,0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dSprayerCleanAirPressure",m_dSprayerCleanAirPressure,0.0);
  DDXFile_Int(bRead,pIniFile,Product_Section,"m_nFullCleanSprayTimes",m_nFullCleanSprayTimes);

  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dConveyerPos0",m_dConveyerPos[0],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dConveyerPos1",m_dConveyerPos[1],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dConveyerPos2",m_dConveyerPos[2],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dConveyerPos3",m_dConveyerPos[3],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dConveyerPos4",m_dConveyerPos[4],0.0);
  DDXFile_Float(bRead,pIniFile,Product_Section,"m_dNGMagPos",m_dNGMagPos,0.0);

  DDXFile_Int(bRead,pIniFile,Product_Section,"m_nAutoFillTime",m_nAutoFillTime);

  delete pIniFile;
}
//---------------------------------------------------------------------------
AnsiString __fastcall CIniFile::GetErrorString(char *SectionName,int nCode,int nLanMode)
{
  AnsiString strFileName,strErrMsg,strErrMsg1,strCode,strErrName;
  TIniFile *pIniFile;

  if(nLanMode==0) strErrName=ErrorMessageFileName;
  else strErrName=ErrorMessageEngFileName;

  strFileName.sprintf("%s%s%s",IniFile_Dir,ErrorMessage_Dir,strErrName);
  pIniFile = new TIniFile(strFileName);

  strCode.sprintf("E%04d",nCode);
  if(nLanMode==0) strErrMsg=pIniFile->ReadString(SectionName,strCode,"未定義錯誤碼!!");
  else strErrMsg=pIniFile->ReadString(SectionName,strCode,"Not Defined Error Code!!!");
  strErrMsg1.sprintf("[%s] %s=%s",SectionName,strCode,strErrMsg);
  delete pIniFile;

  return strErrMsg1+"\n";
}
//---------------------------------------------------------------------------
void __fastcall CIniFile::StoreHistory(int nYear,int nMonth,int nDate,AnsiString strMessage)
{
  AnsiString strFileName;
  TIniFile *pIniFile;
  int nFileMonth,nIndex; 

  strFileName.sprintf("%s\\Message History\\%4d_%02d_%02d.ini",IniFile_Dir,nYear,nMonth,nDate);
  pIniFile = new TIniFile(strFileName);

  nFileMonth=pIniFile->ReadInteger("Control","Month",1);
  nIndex=pIniFile->ReadInteger("Control","Index",1);

  if(nFileMonth!=nMonth)
  {
    nIndex=1;
    pIniFile->WriteInteger("Control","Month",nMonth);
  }

  AnsiString strID;
  strID.sprintf("No%08d",nIndex);
  pIniFile->WriteString("History",strID,strMessage);

  nIndex++;

  strID.sprintf("No%08d",nIndex);
  pIniFile->WriteString("History",strID,"//-------------以下做作廢--------------------//");

  pIniFile->WriteInteger("Control","Index",nIndex);

  delete pIniFile;
}
//---------------------------------------------------------------------------
void __fastcall CIniFile::StoreHistoryNew()
{
  AnsiString strFileName;
  TIniFile *pIniFile;
  int nFileMonth,nIndex;
  time_t timer;
  struct tm *tblock;

  int nSize=m_vecMsg.size();
  if(nSize==0) return;

  AnsiString strMsg;
  strMsg.sprintf("訊息共有 %d 筆\n每筆花費時間約 10 ms\n是否要儲存訊息??",nSize);
  if(Application->MessageBoxA(strMsg.c_str(),"Confirm",MB_ICONQUESTION|MB_OKCANCEL)!=IDOK) return;

   /* gets time of day */
   timer = time(NULL);
   /* converts date/time to a structure */
   tblock = localtime(&timer);
   int nMonth=tblock->tm_mon;
   int nDate=tblock->tm_mday;

  strFileName.sprintf("%s\\Message History\\%d.ini",IniFile_Dir,nDate);
  pIniFile = new TIniFile(strFileName);

  nFileMonth=pIniFile->ReadInteger("Control","Month",1);
  nIndex=pIniFile->ReadInteger("Control","Index",1);

  if(nFileMonth!=nMonth)
  {
    DeleteFile(strFileName);
    nIndex=1;
    pIniFile->WriteInteger("Control","Month",nMonth);
  }

  AnsiString strID;

  for(int nSz=0;nSz<nSize;nSz++)
  {
    strID.sprintf("No%08d",nIndex);
    pIniFile->WriteString("History",strID,m_vecMsg[nSz]);

    nIndex++;
  }
 
  m_vecMsg.clear();
  
  strID.sprintf("No%08d",nIndex);
  pIniFile->WriteString("History",strID,"//-------------以下做作廢--------------------//");

  pIniFile->WriteInteger("Control","Index",nIndex);

  delete pIniFile;
}
//---------------------------------------------------------------------------
bool __fastcall CIniFile::SearchFile(AnsiString strBarCode,AnsiString &strFileName)
{
  WIN32_FIND_DATA FindFileData;
  AnsiString strName;
  char *pFileName;
  TIniFile *pIniFile;
  bool bResult=false;
  
  strName.sprintf("%s*.ini",IniFile_Dir);
  HANDLE hFile=FindFirstFile(strName.c_str(),&FindFileData);
  if(hFile!=INVALID_HANDLE_VALUE)
  {
    while(FindNextFile(hFile,&FindFileData)!=0)
    {
      pFileName=FindFileData.cFileName;
      strName.sprintf("%s%s",IniFile_Dir,pFileName);
      pIniFile = new TIniFile(strName);
      AnsiString strCode=pIniFile->ReadString(Product_Section,"BarCode","0000");
      delete pIniFile;
      if(strCode==strBarCode)
      {
        strFileName=strName;
        bResult=true;
        break;
      }
    }
    FindClose(hFile);
  }

  return bResult;
}
//---------------------------------------------------------------------------
void __fastcall CIniFile::AddNewID(int nLevel,char *strID,char *strPassword)
{
  AnsiString strFile;
  TIniFile *pIniFile;
  char *Level[]={"Operator","Engineer","Supervisor"};

  if(nLevel<0 || nLevel>2) nLevel=0;
                    
  strFile.sprintf("%s%s",IniFile_Dir,UserName);
  pIniFile = new TIniFile(strFile);

  pIniFile->WriteString(Level[nLevel],strID,strPassword);

  delete pIniFile;
}
//---------------------------------------------------------------------------
AnsiString __fastcall CIniFile::ReadPassword(int nLevel,char *strID)
{
         AnsiString strFile;
  TIniFile *pIniFile;
  char *Level[]={"Operator","Engineer","Supervisor"};

  if(nLevel<0 || nLevel>2) nLevel=0;
                    
  strFile.sprintf("%s%s",IniFile_Dir,UserName);
  pIniFile = new TIniFile(strFile);

  AnsiString Pwd=pIniFile->ReadString(Level[nLevel],strID,"NOTFOUND");

  delete pIniFile;

  return Pwd;
}
//---------------------------------------------------------------------------
void __fastcall CIniFile::AddLog(char *pRx,int nSize)
 {
    
        AnsiString strTime;
        time_t timer;
        struct tm *tblock;

        timer = time(NULL);
        tblock = localtime(&timer);  

        try{
                FILE *pFile;

                strTime.sprintf("C:\\C83 Log\\%04d_%02d_%02d.txt",tblock->tm_year+1900,tblock->tm_mon+1,tblock->tm_mday);

                pFile=fopen(strTime.c_str(),"a+");

                if(pFile!=NULL)
                {
                        fprintf(pFile,"\n[%2d:%02d:%02d] ",tblock->tm_hour,tblock->tm_min, tblock->tm_sec);

                        int nIndex=0;
                        while(nIndex<nSize)
                        {
                                //if(pRx[nIndex]=='>') fprintf(pFile,"%c\n  ",pRx[nIndex]);
                                //else
                                fprintf(pFile,"%c",pRx[nIndex]);
                                nIndex++;
                        }
                        fclose(pFile);
                }

        } catch(const EAccessViolation &e)
        {

                //Application->MessageBox(e.Message.c_str(), "AddLog Exception",MB_OK);
        }
 }
 //---------------------------------------------------------------------------
 __fastcall CIniFile::CIniFile()
 {
        mkdir("C:\\C83 Log");
        
 }
 //---------------------------------------------------------------------------
 AnsiString __fastcall CIniFile::GetFileNameWithoutExt(char *strFileName)
 {
        char drive[MAXDRIVE];
        char dir[MAXDIR];
        char file[MAXFILE];
        char ext[MAXEXT];
        int flags;

        flags=fnsplit(strFileName,drive,dir,file,ext);

        return file;
 }
 //---------------------------------------------------------------------------
 AnsiString __fastcall CIniFile::GetFileNameWithNewExt(char *strFileName,char *strExtension)
 {
        char drive[MAXDRIVE];
        char dir[MAXDIR];
        char file[MAXFILE];
        char ext[MAXEXT];
        int flags;

        flags=fnsplit(strFileName,drive,dir,file,ext);
        AnsiString strName;
        strName.sprintf("%s%s%s.%s",drive,dir,file,strExtension);

        return strName;
 }

