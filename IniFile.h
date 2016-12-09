//---------------------------------------------------------------------------

#ifndef IniFileH
#define IniFileH

#include "vcl.h"
#include <vector>
#include "GlobalFunction.h"


#define System_Section "System"
#define Machine_Section "Machine"
#define Product_Section "Product"


#define IniFile_Dir "C:\\Product_Data\\"

#define MAX_AXIS 13     //4+9

//---------------------------------------------------------------------------
class CIniFile
{
//Variable
public:
   int m_nErrorCode;
  //System
  int m_nLanguageMode;    //0=Chinese 1=English
  int m_nPriviledge;
  AnsiString m_strARTPassword;
  AnsiString m_strENGPassword;
  AnsiString m_strLastFileName;
  double m_dCycleTimeOut;

  std::vector<AnsiString> m_vecMsg;

  __fastcall CIniFile();

  //-----------------Machine-----------------
   double m_dACCSpeed[MAX_AXIS];
  double m_dDECSpeed[MAX_AXIS];
  double m_dJogSpeed[MAX_AXIS];
  double m_dWorkSpeed[MAX_AXIS];

  double m_dMgzStartPos;
  double m_dMgzStartPosUpFirst;
  double m_dMgzPitch;
  int m_nMgzSize;

  double m_dConveyerPos[5];
  double m_dNGMagPos;

  double m_dCleanSprayPosX[4];
  double m_dCleanSprayPosY[4];
  double m_dCleanSprayPosZ;
  int m_nCleanSprayTimes;
  double m_dCleanSprayDistance;
  double m_dSprayerCleanWaterPressure;
  double m_dSprayerCleanAirPressure;
  int m_nFullCleanSprayTimes;

  double m_dScaleSprayPosX[2];
  double m_dScaleSprayPosY[2];
  double m_dScaleSprayPosZ[2];
  double m_dScaleSprayTime[2];
  int m_nScaleSprayTimes[2];
  double m_dScaleSprayDelayTime;
  int m_nAutoFillTime;
  int m_nAutoFillFulxPerCount;
  double m_dSpraryDelayTimeB;
  double m_dSpraryDelayTimeA;
  double m_dSuccBackDelayTime;
  //double m_dScale

  double m_dLDYUnLoadClamperAlarm;
  double m_dSprayLaneAlarmX[2];
  double m_dSprayLaneAlarmY[2];
  double m_dSprayLaneAlarmZ;
  double m_dWeightScaleAlarmUp;
  double m_dWeightScaleAlarmDown;

  AnsiString m_strAutoCleanSprayLaneDateTime[3];

  bool m_bForceEject;
  bool m_bUsePreAutoWeightScale;
  bool m_bUseUnClampAutoWeightScale;
  bool m_bUseAutoCleanSprayLane;
  bool m_bIsMgzUpFirst;
  bool m_bStopLoader;
  bool m_bIsUseCIM;
  bool m_bIsUseRightLCPusher;
  bool m_bIsUse1DReader;

  int m_nRailOption;                     //0:All 1:Front 2:Rear

  //-----------------Product-----------------

  //pos
  double m_dLoaderClampMgzPos[3];        //0:Z 1:Y 2:Z 
  double m_dMagazinePushPosY;
  double m_dMagazinePushPosZ;
  double m_dMagazinePushPosUpFirstZ;
  double m_dLoaderMgzPitch;
  double m_dLoaderUnClampMgzPos[3];        //0:Z 1:Y 2:Z

  double m_dLeftLaneChangerMgzPos;
  double m_dLeftLaneChangerSprayPos[2];         //1: front lane 0:Rear Lane

  //Spray
  double m_dStartSprayPosX[2];
  double m_dStartSprayPosY[2];
  double m_dSprayDistance;
  double m_dSprayPitch;
  double m_dSprayPosZ;
  int m_nSprayTimes;
  double m_dSprayReadyPos;

  double m_dFluxTankAirPressure;        //AO_0
  double m_dSprayerAirPressure;         //AO_1

  double m_dMarkScore0;

  double m_dRightLaneChangerSprayPos[2];
  double m_dCCDCheckPosX[4];
  double m_dCCDCheckPosY[4];
  bool m_bIsUseCCDCheckPos[4];
  double m_dRightLaneChangerDelayTime;

  int m_nLEDDimmer[2];

  //CCD
  int m_nMinThreshold;

  //Option
  bool m_bUseSprayer;
  bool m_bUseCCD;
  bool m_bIsMagazineUpFirst;
 
//Function
public:
  void __fastcall MachineFile(bool bRead);
  void __fastcall ProductFile(char *strFileName,bool bRead);
  AnsiString __fastcall GetErrorString(char *SectionName,int nCode,int nLanMode=0);  //LanMode 0: CHT 1:ENG
  void __fastcall StoreHistory(int nYear,int nMonth,int nDate,AnsiString strMessage);
  void __fastcall StoreHistoryNew();
  bool __fastcall SearchFile(AnsiString strBarCode,AnsiString &strFileName);

  void __fastcall AddNewID(int nLevel,char *strID,char *strPassword);
  AnsiString __fastcall ReadPassword(int nLevel,char *strID);
  void __fastcall AddLog(char *pRx,int nSize);

  AnsiString __fastcall GetFileNameWithNewExt(char *strFileName,char *strExtension);
  AnsiString __fastcall GetFileNameWithoutExt(char *strFileName);
};
#endif
