//---------------------------------------------------------------------------

#ifndef frmMainH
#define frmMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <OleCtrls.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <ScktComp.hpp>
#include <Menus.hpp>
#include <ExtDlgs.hpp>
#include <NMFtp.hpp>
#include <Psock.hpp>
#include "MSMQ_OCX.h"
#include <OleServer.hpp>
#include <vector>


#include "C_GetTime.h"
//---------------------------------------------------------------------------
class TfmMain : public TForm
{
__published:	// IDE-managed Components
        TImageList *ImageList1;
        TListBox *listHistory;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *Open1;
        TMenuItem *Save1;
        TMenuItem *Saveas1;
        TMenuItem *Parameter1;
        TMenuItem *Machine1;
        TMenuItem *Product1;
        TMenuItem *Option1;
        TMenuItem *Operate1;
        TMenuItem *DIDO1;
        TMenuItem *Login1;
        TMenuItem *Motor1;
        TMenuItem *ManualOperation1;
        TMenuItem *Exit1;
        TMenuItem *Version1;
        TSplitter *Splitter1;
        TPanel *Panel1;
        TScrollBox *ScrollBox1;
        TPaintBox *ImagePaintBox;
        TPanel *Panel2;
        TSplitter *Splitter2;
        TSplitter *Splitter3;
        TPaintBox *paintMap;
        TMenuItem *Image1;
        TMenuItem *Load1;
        TMenuItem *Save2;
        TOpenPictureDialog *OpenPictureDialog1;
        TSavePictureDialog *SavePictureDialog1;
        TMenuItem *Append1;
        TMenuItem *N11;
        TMenuItem *N21;
        TMenuItem *N31;
        TMenuItem *N41;
        TSpeedButton *SpeedButton1;
        TTimer *timerMessage;
        TServerSocket *serverVenderID;
        TTimer *timerComm;
        TPageControl *PageControl1;
        TTabSheet *tabCCD;
        TBitBtn *BitBtn6;
        TBitBtn *BitBtn8;
        TBitBtn *BitBtn5;
        TBitBtn *BitBtn3;
        TGroupBox *GroupBox1;
        TSpeedButton *btnGrab;
        TSpeedButton *btnLive;
        TCheckBox *checkShowSearchROI0;
        TCheckBox *checkShowPatternROI0;
        TCheckBox *checkShowLayout;
        TCheckBox *checkShowResult0;
        TBitBtn *btnVisionProcess;
        TBitBtn *BitBtn7;
        TTabSheet *tabCodeReader;
        TSpeedButton *SpeedButton2;
        TServerSocket *serverLaserID;
        TServerSocket *serverCoverID;
        TServerSocket *serverBoatID;
        TGroupBox *GroupBox2;
        TSpeedButton *SpeedButton4;
        TSpeedButton *SpeedButton5;
        TCheckBox *checkShowSearchROI2;
        TCheckBox *checkShowPatternROI2;
        TCheckBox *checkShowResult2;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TSpeedButton *SpeedButton6;
        TSpeedButton *SpeedButton7;
        TSpeedButton *SpeedButton8;
        TSpeedButton *SpeedButton9;
        TClientSocket *clientVenderID;
        TClientSocket *clientLaserID;
        TClientSocket *clientCoverID;
        TClientSocket *clientBoatID;
        TSpeedButton *SpeedButton3;
        TSpeedButton *SpeedButton10;
        TSpeedButton *SpeedButton11;
        TSpeedButton *SpeedButton12;
        TSpeedButton *SpeedButton13;
        TSpeedButton *SpeedButton14;
        TSpeedButton *SpeedButton15;
        TSpeedButton *SpeedButton16;
        TSpeedButton *SpeedButton17;
        TSpeedButton *SpeedButton18;
        TTabSheet *tabLaser;
        TSpeedButton *SpeedButton19;
        TSpeedButton *SpeedButton20;
        TSpeedButton *SpeedButton21;
        TTrackBar *TrackBar1;
        TTrackBar *TrackBar2;
        TLabel *labelLED0;
        TLabel *labelLED1;
        TRadioGroup *radioTable;
        TGroupBox *GroupBox3;
        TBitBtn *BitBtn9;
        TBitBtn *BitBtn10;
        TCheckBox *checkShowSearchROI1;
        TCheckBox *checkShowPatternROI1;
        TCheckBox *checkShowResult1;
        TSpeedButton *SpeedButton22;
        TSpeedButton *SpeedButton23;
        TServerSocket *serverSMS;
        TClientSocket *clientSMS;
        TTimer *timerSMS;
        TTabSheet *tabSMS;
        TSpeedButton *SpeedButton24;
        TSpeedButton *SpeedButton25;
        TStaticText *textSMSStatus;
        TSpeedButton *SpeedButton26;
        TLabel *labelSerialID;
        TSpeedButton *SpeedButton27;
        TLabel *labelLotEnd;
        TSpeedButton *SpeedButton28;
        TLabel *Label2;
        TSpeedButton *SpeedButton30;
        TSpeedButton *SpeedButton31;
        TTabSheet *tabInfo;
        TGroupBox *GroupBox4;
        TSpeedButton *SpeedButton32;
        TGroupBox *GroupBox5;
        TLabel *Label1;
        TStaticText *textLaserCount;
        TSpeedButton *SpeedButton29;
        TStaticText *textOKSummary;
        TStaticText *textNGSummary;
        TLabel *Label3;
        TLabel *Label4;
        TStaticText *textSMSStatus2;
        TSpeedButton *SpeedButton33;
        TTabSheet *tabVisionLog;
        TListBox *listVisionLog;
        TBitBtn *btnClearVisionLog;
        TSpeedButton *SpeedButton34;
        TLabel *labelSubstrateRemains;
        TNMFTP *ftpMap;
        TStaticText *textMapFtpStatus;
        TSpeedButton *SpeedButton35;
        TSpeedButton *SpeedButton36;
        TSpeedButton *SpeedButton37;
        TServerSocket *serverCIM;
        TMSMQQueueInfo *MSMQQueueInfo1;
        TMSMQQueue *MSMQQueue1;
        TMSMQQueueInfo *MSMQQueueInfo2;
        TMSMQQueue *MSMQQueue2;
        TMSMQEvent *MSMQEvent1;
        TMSMQMessage *MSMQMessage1;
        TMSMQQueueInfo *MSMQQueueInfo3;
        TMSMQMessage *MSMQMessage2;
        TMSMQQueue *MSMQQueue3;
        TMSMQEvent *MSMQEvent2;
        TListBox *listCIMLog;
        TStaticText *StaticText5;
        TStaticText *StaticText2;
        TStaticText *StaticText3;
        TEdit *m_strScheduleNo;
        TEdit *m_strSBTSize;
        TEdit *m_strSBTType;
        TSpeedButton *SpeedButton38;
        TSpeedButton *SpeedButton39;
        TSpeedButton *SpeedButton40;
        TRadioGroup *radioROIBlock;
        void __fastcall ImagePaintBoxMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall btnFileOpenClick(TObject *Sender);
        void __fastcall btnFileSaveClick(TObject *Sender);
        void __fastcall btnSaveAsClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall btnIOCheckClick(TObject *Sender);
        void __fastcall btnMotorCheckClick(TObject *Sender);
        void __fastcall btnExitClick(TObject *Sender);
        void __fastcall btnMachineParaClick(TObject *Sender);
        void __fastcall btnProductParaClick(TObject *Sender);
        void __fastcall btnPriviledgeClick(TObject *Sender);
        void __fastcall btnMotorManulClick(TObject *Sender);
        void __fastcall btnOptionClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall paintMapPaint(TObject *Sender);
        void __fastcall ImagePaintBoxPaint(TObject *Sender);
        void __fastcall BitBtn6Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn8Click(TObject *Sender);
        void __fastcall BitBtn5Click(TObject *Sender);
        void __fastcall Load1Click(TObject *Sender);
        void __fastcall Save2Click(TObject *Sender);
        void __fastcall checkShowSearchROI0Click(TObject *Sender);
        void __fastcall checkShowPatternROI0Click(TObject *Sender);
        void __fastcall checkShowLayoutClick(TObject *Sender);
        void __fastcall checkShowResult0Click(TObject *Sender);
        void __fastcall btnGrabClick(TObject *Sender);
        void __fastcall btnLiveClick(TObject *Sender);
        void __fastcall BitBtn7Click(TObject *Sender);
        void __fastcall btnVisionProcessClick(TObject *Sender);
        void __fastcall timerMessageTimer(TObject *Sender);
        void __fastcall timerCommTimer(TObject *Sender);
        void __fastcall serverVenderIDClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall serverVenderIDClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall serverVenderIDClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall serverLaserIDClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall serverLaserIDClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall serverLaserIDClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall serverCoverIDClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall serverCoverIDClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall serverCoverIDClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall serverBoatIDClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall serverBoatIDClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall serverBoatIDClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall SpeedButton8Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton9Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton12Click(TObject *Sender);
        void __fastcall SpeedButton19Click(TObject *Sender);
        void __fastcall SpeedButton20Click(TObject *Sender);
        void __fastcall SpeedButton21Click(TObject *Sender);
        void __fastcall TrackBar1Change(TObject *Sender);
        void __fastcall TrackBar2Change(TObject *Sender);
        void __fastcall SpeedButton16Click(TObject *Sender);
        void __fastcall SpeedButton17Click(TObject *Sender);
        void __fastcall SpeedButton18Click(TObject *Sender);
        void __fastcall BitBtn10Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall SpeedButton22Click(TObject *Sender);
        void __fastcall SpeedButton23Click(TObject *Sender);
        void __fastcall SpeedButton6Click(TObject *Sender);
        void __fastcall SpeedButton7Click(TObject *Sender);
        void __fastcall clientSMSConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall serverSMSClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall serverSMSClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall clientSMSDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall serverSMSClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall clientSMSRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall SpeedButton24Click(TObject *Sender);
        void __fastcall timerSMSTimer(TObject *Sender);
        void __fastcall SpeedButton25Click(TObject *Sender);
        void __fastcall clientSMSError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall serverSMSClientError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall clientVenderIDError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall clientLaserIDError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall clientCoverIDError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall clientBoatIDError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall SpeedButton26Click(TObject *Sender);
        void __fastcall SpeedButton27Click(TObject *Sender);
        void __fastcall SpeedButton28Click(TObject *Sender);
        void __fastcall SpeedButton29Click(TObject *Sender);
        void __fastcall SpeedButton30Click(TObject *Sender);
        void __fastcall Version1Click(TObject *Sender);
        void __fastcall SpeedButton31Click(TObject *Sender);
        void __fastcall PageControl1Change(TObject *Sender);
        void __fastcall btnClearVisionLogClick(TObject *Sender);
        void __fastcall SpeedButton34Click(TObject *Sender);
        void __fastcall SpeedButton35Click(TObject *Sender);
        void __fastcall SpeedButton36Click(TObject *Sender);
        void __fastcall ftpMapFailure(bool &Handled, TCmdType Trans_Type);
        void __fastcall ftpMapConnect(TObject *Sender);
        void __fastcall ftpMapConnectionFailed(TObject *Sender);
        void __fastcall ftpMapDisconnect(TObject *Sender);
        void __fastcall SpeedButton37Click(TObject *Sender);
        void __fastcall serverCIMClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall serverCIMClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall serverCIMClientError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall serverCIMClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall MSMQEvent1Arrived(TObject *Sender,
          LPDISPATCH Queue, long Cursor);
        void __fastcall MSMQEvent2Arrived(TObject *Sender,
          LPDISPATCH Queue, long Cursor);
private:	// User declarations         
        void __fastcall CreateCaptionFile(TForm *pForm);
        void __fastcall ReadCaptionFile(TForm *pForm,int nLanguage=0);

        void __fastcall CreateMapArray(TRect &rect,int nPackageX,int nPackageY,int nDeviceGap,int nSectX,int nSectY);
        void __fastcall DoVisionProcess();
         void __fastcall DoVisionProcess(int nBkIndex);

        AnsiString __fastcall GetSchedule(int nIndex);

        void __fastcall SetLEDDimmer();
        bool __fastcall AxisMoveCheck();

        IMSMQQueue2Ptr IMSMQQTX;
        IMSMQQueue2Ptr IMSMQQRX1;
        IMSMQQueue2Ptr IMSMQQRX2;

public:		// User declarations
        __fastcall TfmMain(TComponent* Owner);
        void RefreshImage();
        void __fastcall GetVersion();
        void __fastcall SetPrivilege(int nLevel);
        void __fastcall AddList(AnsiString strMessage);
        void __fastcall AddCIMList(AnsiString strMessage);
        void __fastcall AddVisionLog(AnsiString strLog);

        int m_nUserLevel; //0:OP 1:Engineer 2:adm
        C_GetTime tm1MSLogOut;

        std::vector<TRect> m_vectRect; //for display vision inspect result
        __int16 m_nSubstrateMap[100*100];

        //PTI
        bool __fastcall ExportMapFile();                    //PTI
        bool __fastcall ExportMapFileTmp(bool bFront);      //PTI
        bool __fastcall RenameMapFile(bool bFront);             //PTI
        //SPIL
        bool __fastcall ExportSPILMapFile(AnsiString strSchedule);
        bool __fastcall UploadMapFile(AnsiString strSchedule);

        //MSMQ
        void __fastcall InitMSMQ();

        //CIM
        static bool StartProcess(bool bStart);
        static bool OpenFilebyCIM(AnsiString strFileName);
        static bool CIMEventReportAck(AnsiString strSSID,AnsiString strAckCode);

};
//---------------------------------------------------------------------------
extern PACKAGE TfmMain *fmMain;
//---------------------------------------------------------------------------
#endif
