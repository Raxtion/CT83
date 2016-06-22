//---------------------------------------------------------------------------


#pragma hdrstop

#include "PylonCCD.h"


#define CHECK( errc ) if ( GENAPI_E_OK != errc ) ShowMessage( FormatFloat("Pylon CCD Camera ErrCode=0",errc) )
#define CHECK2( errc ) if ( GENAPI_E_OK != errc ) return false
//---------------------------------------------------------------------------

#pragma package(smart_init)
CPylonCCD *g_pCCD;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
__fastcall CPylonCCD::CPylonCCD(bool CreateSuspended): TThread(CreateSuspended)

{
        m_bInitOk=false;
        m_bStopThread=true;
        m_bTerminateThread=false;

        PylonInitialize();

        numDevices=0;

        m_nCam[0]=0;
        m_nCam[1]=0;

        res = PylonEnumerateDevices( &numDevices );

        CHECK(res);
        if(numDevices==0 ) {ShowMessage("No CCD Found");return;}

        m_pCamera=new CCDDevice[numDevices];

        
        for(int nIndex=0;nIndex<numDevices;nIndex++)
        {
                res = PylonCreateDeviceByIndex(nIndex, &m_pCamera[nIndex].m_hDev );
                CHECK(res);
                res = PylonDeviceOpen( m_pCamera[nIndex].m_hDev, PYLONC_ACCESS_MODE_CONTROL | PYLONC_ACCESS_MODE_STREAM | PYLONC_ACCESS_MODE_EVENT  );
                CHECK(res);
                if(PylonDeviceFeatureIsAvailable(m_pCamera[nIndex].m_hDev, "EnumEntry_PixelFormat_Mono8"))
                {
                        res=PylonDeviceFeatureFromString(m_pCamera[nIndex].m_hDev, "PixelFormat", "Mono8" );
                        CHECK(res);
                }

                if(PylonDeviceFeatureIsAvailable( m_pCamera[nIndex].m_hDev, "EnumEntry_TriggerSelector_AcquisitionStart"))
                {
                        res = PylonDeviceFeatureFromString( m_pCamera[nIndex].m_hDev, "TriggerSelector", "AcquisitionStart");
                        CHECK(res);
                        res = PylonDeviceFeatureFromString(m_pCamera[nIndex].m_hDev, "TriggerMode", "Off");
                        CHECK(res);
                }

                if(PylonDeviceFeatureIsAvailable( m_pCamera[nIndex].m_hDev, "EnumEntry_TriggerSelector_FrameStart"))
                {
                        res = PylonDeviceFeatureFromString( m_pCamera[nIndex].m_hDev, "TriggerSelector", "FrameStart");
                        CHECK(res);
                        res = PylonDeviceFeatureFromString( m_pCamera[nIndex].m_hDev, "TriggerMode", "Off");
                        CHECK(res);
                }

                if(PylonDeviceFeatureIsAvailable( m_pCamera[nIndex].m_hDev, "DeviceUserID"))
                {
                        char xxx[20]={0};
                        unsigned int cc=20;
                        res = PylonDeviceFeatureToString( m_pCamera[nIndex].m_hDev, "DeviceUserID", xxx,&cc);
                        CHECK(res);

                        if(strcmp(xxx,"cam0")==0) m_nCam[0]=nIndex;
                        else m_nCam[1]=nIndex;
                }

                //res = PylonDeviceFeatureFromString( m_pCamera[nIndex].m_hDev, "AcquisitionMode", "Continuous" );            //Continuous Grab
                //CHECK(res);



                if(PylonDeviceFeatureIsWritable(m_pCamera[nIndex].m_hDev, "GevSCPSPacketSize"))
                {
                        res = PylonDeviceSetIntegerFeature( m_pCamera[nIndex].m_hDev, "GevSCPSPacketSize", 1500 );
                        CHECK(res);
                }


                res = PylonDeviceGetIntegerFeatureInt32( m_pCamera[nIndex].m_hDev, "PayloadSize", &m_pCamera[nIndex].m_PayloadSize );
                CHECK(res);

                m_pCamera[nIndex].m_pImgBuf= (unsigned char*) malloc( m_pCamera[nIndex].m_PayloadSize  );

                 if ( m_pCamera[nIndex].m_pImgBuf==NULL) ShowMessage("Image Buffer == 0");

                res = PylonDeviceGetIntegerFeatureInt32( m_pCamera[nIndex].m_hDev, "Width", &m_pCamera[nIndex].m_nImageSizeX );
                CHECK(res);

                res = PylonDeviceGetIntegerFeatureInt32( m_pCamera[nIndex].m_hDev, "Height", &m_pCamera[nIndex].m_nImageSizeY);
                CHECK(res);

                CreateGrayBitmapInfo(nIndex);

                //------------------------------------------
                /* Get the number of streams supported by the device and the transport layer. */

                unsigned int nStreams=0;
                res = PylonDeviceGetNumStreamGrabberChannels( m_pCamera[nIndex].m_hDev, &nStreams );
                CHECK(res);
                if (nStreams < 1 )
                {
                        ShowMessage("The transport layer doesn't support image streams\n");
                }

                /* Create and open a stream grabber for the first channel. */

                res = PylonDeviceGetStreamGrabber( m_pCamera[nIndex].m_hDev, 0, &m_pCamera[nIndex].hGrabber );
                CHECK(res);
                res = PylonStreamGrabberOpen( m_pCamera[nIndex].hGrabber );
                CHECK(res);

                /* Get a handle for the stream grabber's wait object. The wait object
                allows waiting for buffers to be filled with grabbed data. */
                res = PylonStreamGrabberGetWaitObject( m_pCamera[nIndex].hGrabber, &m_pCamera[nIndex].hWait );
                CHECK(res);

                /* .. We will not use more than NUM_BUFFERS for grabbing. */
                res = PylonStreamGrabberSetMaxNumBuffer( m_pCamera[nIndex].hGrabber, 1 );
                CHECK(res);
                /* .. We will not use buffers bigger than payloadSize bytes. */
                res = PylonStreamGrabberSetMaxBufferSize( m_pCamera[nIndex].hGrabber, m_pCamera[nIndex].m_PayloadSize );
                CHECK(res);


                /*  Allocate the resources required for grabbing. After this, critical parameters
                        that impact the payload size must not be changed until FinishGrab() is called. */
                res = PylonStreamGrabberPrepareGrab( m_pCamera[nIndex].hGrabber );
                CHECK(res);

                res = PylonStreamGrabberRegisterBuffer(m_pCamera[nIndex].hGrabber, m_pCamera[nIndex].m_pImgBuf , m_pCamera[nIndex].m_PayloadSize,  &m_pCamera[nIndex].bufHandles );
                CHECK(res);

                int i=0;
                res = PylonStreamGrabberQueueBuffer( m_pCamera[nIndex].hGrabber, m_pCamera[nIndex].bufHandles, (void*) i );
                CHECK(res);





        }

        for(int nIndex=0;nIndex<256;nIndex++)
        {

                m_bIsSingleGrab[nIndex]=false;
        }


}
//---------------------------------------------------------------------------
__fastcall CPylonCCD::~CPylonCCD()
{
      //PylonGrabRessult_t grabResult;
      _Bool isReady;

      int nErr=0;

        for(int nIndex=0;nIndex<numDevices;nIndex++)
        {
                /* Clean up. */

                /*  ... Stop the camera. */
                res = PylonDeviceExecuteCommandFeature( m_pCamera[nIndex].m_hDev, "AcquisitionStop");
                CHECK(res);

                /* ... We must issue a cancel call to ensure that all pending buffers are put into the
                        stream grabber's output queue. */
                res = PylonStreamGrabberCancelGrab( m_pCamera[nIndex].hGrabber );
                CHECK(res);

                /* ... The buffers can now be retrieved from the stream grabber. */
                /*
                do
                {
                        nErr++;
                        if(nErr>10) break;
                        res = PylonStreamGrabberRetrieveResult( m_pCamera[nIndex].hGrabber, &grabResult, &isReady );
                        CHECK(res);
                } while ( isReady );
                 */
                /* ... When all buffers have been retrieved from the stream grabber, they can be deregistered.
                        After that, it is safe to free the memory. */


                res = PylonStreamGrabberDeregisterBuffer( m_pCamera[nIndex].hGrabber, m_pCamera[nIndex].bufHandles );
                CHECK(res);
                //free( buffers[i] );


                /* ... Release grabbing related resources. */
                res = PylonStreamGrabberFinishGrab( m_pCamera[nIndex].hGrabber );
                CHECK(res);

                /* After calling PylonStreamGrabberFinishGrab(), parameters that impact the payload size (e.g.,
                        the AOI width and height parameters) are unlocked and can be modified again. */

                /* ... Close the stream grabber. */
                res = PylonStreamGrabberClose( m_pCamera[nIndex].hGrabber );
                CHECK(res);


                res = PylonDeviceClose(  m_pCamera[nIndex].m_hDev );
                CHECK(res);
                res = PylonDestroyDevice (  m_pCamera[nIndex].m_hDev );
                CHECK(res); 

                free(  m_pCamera[nIndex].m_pImgBuf );
         }
        PylonTerminate();

        if(m_pCamera!=NULL) delete m_pCamera;  
        
}
//-----------------------------------------------------------------------
void __fastcall CPylonCCD::CreateGrayBitmapInfo(int nIndex)
{
  DWORD bitmapInfoSize,i;

        
	// Bitmap info structure for the image
	bitmapInfoSize = sizeof(BITMAPINFO) + 255*sizeof(RGBQUAD);
  m_pCamera[nIndex].m_pGrayBitmapInfo =(BITMAPINFO*)new BYTE[bitmapInfoSize];


	m_pCamera[nIndex].m_pGrayBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pCamera[nIndex].m_pGrayBitmapInfo->bmiHeader.biPlanes = 1;
	m_pCamera[nIndex].m_pGrayBitmapInfo->bmiHeader.biBitCount = 8;
	m_pCamera[nIndex].m_pGrayBitmapInfo->bmiHeader.biCompression = BI_RGB;
	m_pCamera[nIndex].m_pGrayBitmapInfo->bmiHeader.biSizeImage = 0;
	m_pCamera[nIndex].m_pGrayBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
	m_pCamera[nIndex].m_pGrayBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
	m_pCamera[nIndex].m_pGrayBitmapInfo->bmiHeader.biClrUsed = 0;
	m_pCamera[nIndex].m_pGrayBitmapInfo->bmiHeader.biClrImportant = 0;

	m_pCamera[nIndex].m_pGrayBitmapInfo->bmiHeader.biWidth = m_pCamera[nIndex].m_nImageSizeX;       //645
	m_pCamera[nIndex].m_pGrayBitmapInfo->bmiHeader.biHeight = -m_pCamera[nIndex].m_nImageSizeY;


	for (i = 0 ; i < 256 ; i++) {
		m_pCamera[nIndex].m_pGrayBitmapInfo->bmiColors[i].rgbBlue = (BYTE)i;
		m_pCamera[nIndex].m_pGrayBitmapInfo->bmiColors[i].rgbGreen = (BYTE)i;
		m_pCamera[nIndex].m_pGrayBitmapInfo->bmiColors[i].rgbRed = (BYTE)i;
		m_pCamera[nIndex].m_pGrayBitmapInfo->bmiColors[i].rgbReserved = 0;
	}

        //m_hGrayPalette=CreatePalette(pGrayPalette);


}
//-----------------------------------------------------------------------
bool __fastcall CPylonCCD::Grab(int nIndex)
{
         /*
        PylonGrabResult_t grabResult;
         _Bool bufferReady;


         res = PylonDeviceGrabSingleFrame( m_pCamera[nIndex].m_hDev, 0, m_pCamera[nIndex].m_pImgBuf, m_pCamera[nIndex].m_PayloadSize,
            &grabResult, &bufferReady, 500 );

         if ( GENAPI_E_OK == res && !bufferReady ) ShowMessage("Buffer Not Ready....Time out");
         CHECK(res);

         if ( grabResult.Status == Grabbed )
        {
                //ShowMessage(FormatFloat( "X=0",grabResult.SizeX)+FormatFloat( "Y=0",grabResult.SizeY) );
                OnGrabComplete[nIndex](nIndex,true);
                return true;

        }
        else if ( grabResult.Status == Failed )
        {
             CHECK(grabResult.ErrorCode);
             OnGrabComplete[nIndex](nIndex,false);
             return false;
        }
        
        */
        m_bGrabFinish[m_nCam[nIndex]]=false;
        m_bIsSingleGrab[m_nCam[nIndex]]=true;
        StartGrab(m_nCam[nIndex]);
        

}
//-----------------------------------------------------------------------
bool __fastcall CPylonCCD::StartGrab(int nIndex)
{
        try
        {
            res = PylonDeviceExecuteCommandFeature( m_pCamera[nIndex].m_hDev, "AcquisitionStart");
            CHECK(res);
        }
        catch(...) {}
}
//-----------------------------------------------------------------------
bool __fastcall CPylonCCD::StopGrab(int nIndex)
{ 
        try
        {
            res = PylonDeviceExecuteCommandFeature( m_pCamera[nIndex].m_hDev, "AcquisitionStop");
            CHECK(res);
        }
        catch(...) {}
}
//-----------------------------------------------------------------------
void __fastcall CPylonCCD::Execute()
{
        PylonGrabResult_t grabResult;
        _Bool isReady;

        while(1)
        {
                if(m_bTerminateThread)
                {
                        for(int nIndex=0;nIndex<numDevices;nIndex++)
                                res = PylonDeviceExecuteCommandFeature( m_pCamera[nIndex].m_hDev, "AcquisitionStop");
                        break;
                }

                for(int nIndex=0;nIndex<numDevices;nIndex++)
                {
                     //m_bGrabFinish[nIndex]=false;

                     res = PylonStreamGrabberRetrieveResult( m_pCamera[nIndex].hGrabber, &grabResult, &isReady );
                     //CHECK(res);
                     if(isReady )
                     {
                             if ( grabResult.Status == Grabbed )
                             {
                                     m_bGrabFinish[nIndex]=true;
                                     OnGrabComplete[nIndex](nIndex,true);

                                     /* Once finished with the processing, requeue the buffer to be filled again. */
                                     int N=0;
                                     res = PylonStreamGrabberQueueBuffer( m_pCamera[nIndex].hGrabber, grabResult.hBuffer, (void*) N );
                                     //CHECK(res);

                                     if(m_bIsSingleGrab[nIndex])
                                     {
                                             m_bIsSingleGrab[nIndex]=false;
                                             res = PylonDeviceExecuteCommandFeature( m_pCamera[nIndex].m_hDev, "AcquisitionStop"); 
                                     }
                             }
                             else if ( grabResult.Status == Failed )
                             {
                             }
                     }
                }
                ::Sleep(1);
        }

}
//-----------------------------------------------------------------------
void __fastcall CPylonCCD::TerminateThread()
{
        m_bTerminateThread=true;
        WaitFor();

}

