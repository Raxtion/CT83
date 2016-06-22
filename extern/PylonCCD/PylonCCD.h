//---------------------------------------------------------------------------

#ifndef PylonCCDH
#define PylonCCDH

#include <vcl>
#include <vector>
#include <pylonc/PylonC.h>

//---------------------------------------------------------------------------
class CPylonCCD:public TThread
{
private:
        GENAPIC_RESULT          res;
        size_t                  numDevices;

        //Palette 
        HPALETTE m_hGrayPalette;

        bool m_bInitOk;
        int m_nCam[10];
        
        struct CCDDevice
        {
                PYLON_DEVICE_HANDLE m_hDev;
                int32_t m_PayloadSize;
                unsigned char* m_pImgBuf;
                int m_nImageSizeX;
                int m_nImageSizeY;
                BITMAPINFO *m_pGrayBitmapInfo;
                //HPALETTE m_hGrayPalette;

                PYLON_STREAMGRABBER_HANDLE  hGrabber;                 /* Handle for the pylon stream grabber. */
                PYLON_WAITOBJECT_HANDLE     hWait;                    /* Handle used for waiting for a grab to be finished. */
                //unsigned char              *buffers[NUM_BUFFERS];     /* Buffers used for grabbing. */
                PYLON_STREAMBUFFER_HANDLE   bufHandles;//[NUM_BUFFERS];  /* Handles for the buffers. */
        };

        bool m_bStopThread;
        bool  m_bTerminateThread;
        bool m_bGrabFinish[256];
        bool m_bIsSingleGrab[256];
        void __fastcall Execute();

 public:
        CCDDevice *m_pCamera;
        void (*OnGrabComplete[256])(int nIndex,bool bResult);
        bool __fastcall GrabComplete(int nIndex){return m_bGrabFinish[m_nCam[nIndex]];};
public:
        __fastcall CPylonCCD(bool CreateSuspended);
        __fastcall ~CPylonCCD();
        void __fastcall CreateGrayBitmapInfo(int nIndex);
        bool __fastcall Grab(int nIndex);
        bool  __fastcall StartGrab(int nIndex);
        bool __fastcall StopGrab(int nIndex);
        void __fastcall TerminateThread();
        bool __fastcall IsGrabFinished(int nIndex){return m_bGrabFinish[m_nCam[nIndex]];}

        

};
//---------------------------------------------------------------------------
#endif
 