//---------------------------------------------------------------------------

#ifndef fmMainH
#define fmMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include "C_GetTime.h"
#include <ScktComp.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *Open1;
        TMenuItem *Save1;
        TMenuItem *Saveas1;
        TMenuItem *Image1;
        TMenuItem *Load1;
        TMenuItem *Save2;
        TMenuItem *Parameter1;
        TMenuItem *Machine1;
        TMenuItem *Product1;
        TMenuItem *Operate1;
        TMenuItem *DIDO1;
        TMenuItem *Motor1;
        TMenuItem *ManualOperation1;
        TMenuItem *Login1;
        TMenuItem *Exit1;
        TMenuItem *Version1;
        TSplitter *Splitter1;
        TPanel *Panel1;
        TListBox *listHistory;
        TSplitter *Splitter2;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TGroupBox *GroupBox1;
        TSpeedButton *btnGrab;
        TSpeedButton *btnLive;
        TLabel *labelLED0;
        TCheckBox *checkShowSearchROI0;
        TCheckBox *checkShowPatternROI0;
        TCheckBox *checkShowResult0;
        TBitBtn *btnVisionProcess;
        TBitBtn *BitBtn7;
        TTrackBar *TrackBar1;
        TTimer *timerComm;
        TSaveDialog *SaveDialog1;
        TOpenDialog *OpenDialog1;
        TSavePictureDialog *SavePictureDialog1;
        TOpenPictureDialog *OpenPictureDialog1;
        TTimer *timerMessage;
        TLabel *Label1;
        TGroupBox *GroupBox2;
        TLabel *labelScale;
        TLabel *Label3;
        TSpeedButton *SpeedButton2;
        TCheckBox *checkStartScaleMonitor;
        TTimer *timerScale;
        TTabSheet *TabSheet2;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton3;
        TGroupBox *GroupBox3;
        TTrackBar *TrackBar2;
        TTrackBar *TrackBar3;
        TLabel *Label2;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
    TSpeedButton *SpeedButton4;
    TSpeedButton *SpeedButton5;
    TSpeedButton *SpeedButton6;
    TSpeedButton *SpeedButton7;
    TSpeedButton *SpeedButton8;
    TSpeedButton *SpeedButton9;
    TSpeedButton *SpeedButton10;
    TCheckBox *m_bStopLoader;
    TBitBtn *BitBtn12;
    TBitBtn *BitBtn13;
    TBitBtn *BitBtn14;
    TBitBtn *BitBtn15;
    TEdit *editFlux;
    TEdit *editAir;
    TButton *btnSet1;
    TButton *btnSet2;
    TTimer *timerAutoCleanSprayLane;
    TGroupBox *GroupBox4;
    TLabel *Label7;
    TEdit *m_dMarkScore0;
    TButton *Button1;
    TButton *Button2;
    TButton *btnOpenLog;
    TPanel *Panel2;
    TScrollBox *ScrollBox1;
    TPaintBox *ImagePaintBox;
    TSplitter *Splitter3;
    TPageControl *PageControl2;
    TTabSheet *TabSheet4;
    TSpeedButton *btnRearLaneReset;
    TSpeedButton *btnFrnotLaneReset;
    TSpeedButton *btnInLaneReset;
    TSpeedButton *btnOutLaneReset;
    TSpeedButton *btnLoaderReset;
    TShape *Shape03;
    TShape *Shape00;
    TShape *Shape01;
    TShape *Shape02;
    TServerSocket *ServerCIM;
    TShape *Shape3;
    TSpeedButton *SpeedButton16;
    TTabSheet *TabSheet3;
    TSpeedButton *SpeedButton11;
    TSpeedButton *SpeedButton12;
    TSpeedButton *SpeedButton13;
    TSpeedButton *SpeedButton14;
    TSpeedButton *SpeedButton15;
    TButton *btn1DRead;
    TButton *btn2DRead;
    TLabel *labFluxLifetime;
    TLabel *labRunningCounts;
    TLabel *labLastPassCounts;
    TLabel *labUPU;
        void __fastcall DIDO1Click(TObject *Sender);
        void __fastcall Motor1Click(TObject *Sender);
        void __fastcall Exit1Click(TObject *Sender);
        void __fastcall Login1Click(TObject *Sender);
        void __fastcall ImagePaintBoxPaint(TObject *Sender);
        void __fastcall ImagePaintBoxMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall btnGrabClick(TObject *Sender);
        void __fastcall TrackBar1Change(TObject *Sender);
        void __fastcall timerCommTimer(TObject *Sender);
        void __fastcall checkShowSearchROI0Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Save1Click(TObject *Sender);
        void __fastcall Saveas1Click(TObject *Sender);
        void __fastcall Open1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Load1Click(TObject *Sender);
        void __fastcall Save2Click(TObject *Sender);
        void __fastcall timerMessageTimer(TObject *Sender);
        void __fastcall Machine1Click(TObject *Sender);
        void __fastcall Product1Click(TObject *Sender);
        void __fastcall btnVisionProcessClick(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall timerScaleTimer(TObject *Sender);
        void __fastcall checkStartScaleMonitorClick(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall TrackBar2Change(TObject *Sender);
        void __fastcall TrackBar3Change(TObject *Sender);
    void __fastcall SpeedButton5Click(TObject *Sender);
    void __fastcall SpeedButton4Click(TObject *Sender);
    void __fastcall SpeedButton6Click(TObject *Sender);
    void __fastcall SpeedButton7Click(TObject *Sender);
    void __fastcall SpeedButton8Click(TObject *Sender);
    void __fastcall btnLiveClick(TObject *Sender);
    void __fastcall ManualOperation1Click(TObject *Sender);
    void __fastcall SpeedButton9Click(TObject *Sender);
    void __fastcall SpeedButton10Click(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall btnLoaderResetClick(TObject *Sender);
    void __fastcall btnInLaneResetClick(TObject *Sender);
    void __fastcall btnRearLaneResetClick(TObject *Sender);
    void __fastcall btnFrnotLaneResetClick(TObject *Sender);
    void __fastcall btnOutLaneResetClick(TObject *Sender);
    void __fastcall m_bStopLoaderClick(TObject *Sender);
    void __fastcall BitBtn12Click(TObject *Sender);
    void __fastcall BitBtn13Click(TObject *Sender);
    void __fastcall BitBtn14Click(TObject *Sender);
    void __fastcall BitBtn15Click(TObject *Sender);
    void __fastcall btnSet1Click(TObject *Sender);
    void __fastcall timerAutoCleanSprayLaneTimer(TObject *Sender);
    void __fastcall btnOpenLogClick(TObject *Sender);
    void __fastcall SpeedButton11Click(TObject *Sender);
    void __fastcall SpeedButton12Click(TObject *Sender);
    void __fastcall SpeedButton13Click(TObject *Sender);
    void __fastcall SpeedButton14Click(TObject *Sender);
    void __fastcall SpeedButton15Click(TObject *Sender);
    void __fastcall ServerCIMClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ServerCIMClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ServerCIMClientError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
    void __fastcall ServerCIMClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall SpeedButton16Click(TObject *Sender);
    void __fastcall btn1DReadClick(TObject *Sender);
    void __fastcall btn2DReadClick(TObject *Sender);
private:	// User declarations
        int m_nUserLevel; //0:OP 1:Engineer 2:adm
        C_GetTime tm1MSLogOut;
        bool m_bISLoaderConveyerDownRun;
public:		// User declarations
        __fastcall TfrmMain(TComponent* Owner);

        static void OnGrabComplete(int nIndex,bool bResult);
        static bool StartProcess(bool bStart);
        static bool OpenFilebyCIM(AnsiString strFileName);
        void __fastcall RefreshImage();
        void __fastcall SetPrivilege(int nLevel);
        void __fastcall ReadCaptionFile(TForm *pForm,int nLanguage=0);       //0:Chinese
        void __fastcall AddList(AnsiString strMessage);
        void __fastcall SetLEDDimmer();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
