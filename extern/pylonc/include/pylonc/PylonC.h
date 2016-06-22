/*-----------------------------------------------------------------------------
(c) 2009 by Basler Vision Technologies
Section: Basler Components
Project: PYLON
Author:  AH, TK
-----------------------------------------------------------------------------*/

#ifndef PYLONC_PYLONC_H_
#define PYLONC_PYLONC_H_

/**
  \file
  \brief pylon C bindings
*/


#include <stdio.h>   /* for FILENAME_MAX */
#include <genapic/GenApiCDefines.h>
#ifdef GENAPIC_WIN_BUILD
#   include <windows.h> /* thread api needs windows headers */
#endif
#include <genapic/GenApiC.h>

#include <pylonc/PylonCDefines.h>
#pragma pack(push, PYLONC_PACKING)

#include <pylonc/PylonCModule.h>
#include <pylonc/PylonCError.h>
#include <pylonc/PylonCEnums.h>

#if defined PYLONC_EXPORTS
[idl_quote( "typedef [public] long int32_t;" )];
[idl_quote( "typedef [public] long uint32_t;")];
#endif


#ifdef __cplusplus
// avoid namespace ambiguities between std::_Bool (from yvals.h) and ::_Bool (from GenApiCTypes.h)
#  ifdef _MSC_VER
#    define _Bool ::_Bool
#    define PYLONC_BOOL_DEFINED
#  endif

extern "C" {
#endif /* __cplusplus */

/** \addtogroup pylon pylon Interface
 * @{
 */

/* pylon invalid handle type */
#define PYLONC_INVALID_HANDLE GENAPIC_INVALID_HANDLE

/* pylon device access modes */
#define PYLONC_ACCESS_MODE_MONITOR      0
#define PYLONC_ACCESS_MODE_CONTROL      (1 << 0)
#define PYLONC_ACCESS_MODE_STREAM       (1 << 1)
#define PYLONC_ACCESS_MODE_EVENT        (1 << 2)
#define PYLONC_ACCESS_MODE_EXCLUSIVE    (1 << 3)

/* pylon handle types */
GENAPIC_DECLARE_HANDLE( PYLON_DEVICE_HANDLE );              /**< \brief A handle for a device object */
GENAPIC_DECLARE_HANDLE( PYLON_DEVICE_INFO_HANDLE );         /**< \brief A handle for a device info object */
GENAPIC_DECLARE_HANDLE( PYLON_STREAMGRABBER_HANDLE );       /**< \brief A handle for a stream grabber object */
GENAPIC_DECLARE_HANDLE( PYLON_EVENTGRABBER_HANDLE );        /**< \brief A handle for an event grabber object */
GENAPIC_DECLARE_HANDLE( PYLON_CHUNKPARSER_HANDLE );         /**< \brief A handle for a chunk parser object */
GENAPIC_DECLARE_HANDLE( PYLON_EVENTADAPTER_HANDLE );        /**< \brief A handle for an event adapter object */
GENAPIC_DECLARE_HANDLE( PYLON_WAITOBJECT_HANDLE );          /**< \brief A handle for a wait object */
GENAPIC_DECLARE_HANDLE( PYLON_WAITOBJECTS_HANDLE );         /**< \brief A handle for a node object set */
GENAPIC_DECLARE_HANDLE( PYLON_STREAMBUFFER_HANDLE );        /**< \brief A handle for a stream buffer object */
GENAPIC_DECLARE_HANDLE( PYLON_DEVICECALLBACK_HANDLE );      /**< \brief A handle for a device callback object */
GENAPIC_DECLARE_HANDLE( PYLON_FORMAT_CONVERTER_HANDLE );    /**< \brief A handle for a pixel format converter object */

/** \brief pylon device removal callback handler type. */
typedef  void PYLONC_CC PylonDeviceRemCb_t(PYLON_DEVICE_HANDLE h);


#ifndef PYLON_TLB_ONLY
/** \brief Result data struct for PylonStreamGrabberRetrieveResult().
 *  This data describes grab results (typically image data) retrieved from the device.
 *  Some items are optional (marked as "optional") and are only filled in if they are supported by the device.
**/
typedef struct tag_PylonGrabResult_t
{
    const void *Context;                /**< Application specific context specified when calling PylonStreamGrabberRegisterBuffer() */
    PYLON_STREAMBUFFER_HANDLE hBuffer;  /**< Data buffer handle returned when calling PylonStreamGrabberRegisterBuffer() */
    const void *pBuffer;                /**< Pointer to the raw data */
    EPylonGrabStatus Status;            /**< Result status. check this to check whether the result contains valid data. */
    unsigned int FrameNr;               /**< Sequential frame number (optional) */
    EPylonPayloadType PayloadType;      /**< Type of data contained in buffer */
    EPylonPixelType PixelType;          /**< Pixel type (if the result contains pixel data) */
    uint64_t TimeStamp;                 /**< Time stamp generated by the device when filling the result (optional)*/
    int SizeX;                          /**< Number of columns, in pixels (only if payload is image data) */
    int SizeY;                          /**< Number of rows, in pixels (only if payload is image data) */
    int OffsetX;                        /**< Starting column, in pixels (only if payload is image data) */
    int OffsetY;                        /**< Starting row, in pixels (only if payload is image data) */
    int PaddingX;                       /**< Number of extra data bytes at end of row (only if payload is image data) */
    int PaddingY;                       /**< Number of extra data bytes at end of image (only if payload is image data) */
    uint64_t PayloadSize;               /**< Total payload size, in bytes, pointed to by pBuffer */
    unsigned int ErrorCode;             /**< Additional error code in case Status is gst_Failed (optional) */
    /* String_t m_ErrorDescription; */
} PylonGrabResult_t;
#endif

#ifndef PYLON_TLB_ONLY
/** \brief Result data struct for PylonEventGrabberRetrieveEvent(). */
typedef struct tag_PylonEventResult_t
{
    unsigned char Buffer[576];          /**< Raw chunk data which can be passed to PylonChunkParserAttachBuffer() */
    unsigned int ErrorCode;             /**< Error code if there was an error retrieving the event data */
} PylonEventResult_t;
#endif

/** 
 * @}
 */

/*
* ----------------------------------------------------------------------------
* Initialization/Deinitialization
* ----------------------------------------------------------------------------
*/

IDL_ENTRY(PYLONC_MODULE, "_PylonInitialize@0", "Initialize the pylon runtime system.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE_DOC
PylonInitialize(void);

IDL_ENTRY(PYLONC_MODULE, "_PylonTerminate@0", "Shut down the pylon runtime system.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE_DOC
PylonTerminate(void);

/*
* ----------------------------------------------------------------------------
* Device factory: device enumeration, device creation
* ----------------------------------------------------------------------------
*/

/** \addtogroup pylon pylon Interface
 * @{
 */

/** \brief Fixed string size for PylonDeviceInfo_t members. */
#define PYLON_MAX_DEVICEINFO_ENTRY_LENGTH 64

/** \brief Device info struct.
 *
 *  This struct provides general information about the device gathered during enumeration.
**/
typedef struct tag_PylonDeviceInfo_t
{
    char FullName[FILENAME_MAX];                                /**< Full unique device name for identification */
    char FriendlyName[PYLON_MAX_DEVICEINFO_ENTRY_LENGTH];       /**< User friendly device name for display purpose */
    char VendorName[PYLON_MAX_DEVICEINFO_ENTRY_LENGTH];         /**< Manufacturer of the device*/
    char ModelName[PYLON_MAX_DEVICEINFO_ENTRY_LENGTH];          /**< Model name of the device*/ 
    char SerialNumber[PYLON_MAX_DEVICEINFO_ENTRY_LENGTH];       /**< Serial number of the device */
    char DeviceClass[PYLON_MAX_DEVICEINFO_ENTRY_LENGTH];        /**< The device class (transport layer) used by the device  */
    char DeviceVersion[PYLON_MAX_DEVICEINFO_ENTRY_LENGTH];      /**< The device version as reported by the device */
    char UserDefinedName[PYLON_MAX_DEVICEINFO_ENTRY_LENGTH];    /**< User defined name, if present, as reported by the device */
} PylonDeviceInfo_t;

/** 
 * @}
 */

/* Device enumeration / creation */
IDL_ENTRY(PYLONC_MODULE, "_PylonEnumerateDevices@4", "Enumerate all devices.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonEnumerateDevices(RETVAL_PAR size_t *numDevices);

/* GigE Device enumeration / creation */
IDL_ENTRY(PYLONC_MODULE, "_PylonGigEEnumerateAllDevices@4", "Enumerate all GigE devices in all subnets.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonGigEEnumerateAllDevices(RETVAL_PAR size_t *numDevices);

IDL_ENTRY(PYLONC_MODULE, "_PylonGigEForceIp@16", "'Force' a static IP address configuration in a device identified by its MAC Address.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonGigEForceIp( STRING_PAR const char* pMacAddress, STRING_PAR const char* pIpAddress, STRING_PAR const char* pSubnetMask, STRING_PAR const char* pDefaultGateway);

IDL_ENTRY(PYLONC_MODULE, "_PylonGigERestartIpConfiguration@4", "Let a device restart the IP configuration cycle.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonGigERestartIpConfiguration( STRING_PAR const char* pMacAddress);

#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonGigEChangeIpConfiguration( PYLON_DEVICE_HANDLE hDev, _Bool EnablePersistentIp, _Bool EnableDhcp );
#endif

IDL_ENTRY(PYLONC_MODULE, "_PylonGigESetPersistentIpAddress@16", "Writes a persistent IP address to the device.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonGigESetPersistentIpAddress( PYLON_DEVICE_HANDLE hDev, STRING_PAR const char* pIpAddress, STRING_PAR const char* pSubnetMask, STRING_PAR const char* pDefaultGateway);

#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC
PylonGigEGetPersistentIpAddress( PYLON_DEVICE_HANDLE hDev, char* pIpAddress, size_t* pIpAddressLen, char* pSubnetMask, size_t* pSubnetMaskLen, char* pDefaultGateway, size_t* pDefaultGatewayLen);
#endif


#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonGigEBroadcastIpConfiguration( 
                                  const char * pMacAddress, 
                                  _Bool EnablePersistentIp, 
                                  _Bool EnableDHCP, 
                                  const char * pIpAddress, 
                                  const char * pSubnetMask ,
                                  const char * pDefaultGateway, 
                                  const char * pUserdefinedName, 
                                  _Bool * pRetval 
                                  );
#endif

PYLONC_API GENAPIC_RESULT PYLONC_CC
PylonGetDeviceInfo(size_t index, /*RETVAL_PAR*/ PylonDeviceInfo_t* pDi);

IDL_ENTRY(PYLONC_MODULE, "_PylonGetDeviceInfoHandle@8", "Return a handle for a device info object.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonGetDeviceInfoHandle( size_t index, RETVAL_PAR PYLON_DEVICE_INFO_HANDLE* phDi );

IDL_ENTRY(PYLONC_MODULE, "_PylonDeviceInfoGetNumProperties@8", "Return the number of properties stored in a device info object.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceInfoGetNumProperties( PYLON_DEVICE_INFO_HANDLE hDi, RETVAL_PAR size_t* numProperties );

#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC PylonDeviceInfoGetPropertyValueByName( PYLON_DEVICE_INFO_HANDLE hDi, const char* pName, char* pValue, size_t* pBufLen );
PYLONC_API GENAPIC_RESULT PYLONC_CC PylonDeviceInfoGetPropertyValueByIndex( PYLON_DEVICE_INFO_HANDLE hDi, size_t index, char* pBuf, size_t* pBufLen );
PYLONC_API GENAPIC_RESULT PYLONC_CC PylonDeviceInfoGetPropertyName( PYLON_DEVICE_INFO_HANDLE hDi, size_t index, char* pName, size_t* pBufLen);
#endif

IDL_ENTRY(PYLONC_MODULE, "_PylonCreateDeviceByIndex@8", "Create a device object.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonCreateDeviceByIndex( size_t index, RETVAL_PAR PYLON_DEVICE_HANDLE *phDev);

IDL_ENTRY(PYLONC_MODULE, "_PylonCreateDeviceFromDirectShowID@8", "Create a device object.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonCreateDeviceFromDirectShowID( int id, RETVAL_PAR PYLON_DEVICE_HANDLE *phDev);

IDL_ENTRY(PYLONC_MODULE, "_PylonDestroyDevice@4", "Delete a device object.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDestroyDevice(PYLON_DEVICE_HANDLE hDev);


/* Device operations */
IDL_ENTRY(PYLONC_MODULE, "_PylonDeviceOpen@8", "Open a device.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceOpen(PYLON_DEVICE_HANDLE hDev, int accessMode);

IDL_ENTRY(PYLONC_MODULE, "_PylonDeviceClose@4", "Close a device.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceClose(PYLON_DEVICE_HANDLE hDev);

#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceIsOpen(PYLON_DEVICE_HANDLE hDev, PINVOKE_RETVAL_PAR _Bool * pOpen);
#endif

IDL_ENTRY(PYLONC_MODULE, "_PylonDeviceAccessMode@8", "Return access mode flags for a device.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceAccessMode(PYLON_DEVICE_HANDLE hDev, RETVAL_PAR int* pAccessMode);

/* Returns the device info object from which the device was created */
PYLONC_API GENAPIC_RESULT PYLONC_CC
PylonDeviceGetDeviceInfo(PYLON_DEVICE_HANDLE hDev, /* OUT_PAR */ PylonDeviceInfo_t *pDeviceInfo);

IDL_ENTRY(PYLONC_MODULE, "_PylonDeviceGetDeviceInfoHandle@8", "Return the handle to the device info object from which a device was created.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceGetDeviceInfoHandle(PYLON_DEVICE_HANDLE hDev, RETVAL_PAR PYLON_DEVICE_INFO_HANDLE *phDi );

IDL_ENTRY(PYLONC_MODULE, "_PylonDeviceGetNumStreamGrabberChannels@8", "Return the access mode flags for a device.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceGetNumStreamGrabberChannels(PYLON_DEVICE_HANDLE hDev, RETVAL_PAR size_t *pNumChannels);

IDL_ENTRY(PYLONC_MODULE, "_PylonDeviceGetStreamGrabber@12", "Obtain a stream grabber handle from a device.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceGetStreamGrabber(PYLON_DEVICE_HANDLE hDev, size_t index, RETVAL_PAR PYLON_STREAMGRABBER_HANDLE *phStg);

IDL_ENTRY(PYLONC_MODULE, "_PylonDeviceGetEventGrabber@8", "Obtain an event grabber handle from a device.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceGetEventGrabber(PYLON_DEVICE_HANDLE hDev, RETVAL_PAR PYLON_EVENTGRABBER_HANDLE *phEvg);

IDL_ENTRY(PYLONC_MODULE, "_PylonDeviceGetNodeMap@8", "Return the parameter node map for a device.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceGetNodeMap(PYLON_DEVICE_HANDLE hDev, RETVAL_PAR NODEMAP_HANDLE *phMap);


/* returns GENAPIC_INVALID_HANDLE when there is no transport layer nodemap */
IDL_ENTRY(PYLONC_MODULE, "_PylonDeviceGetTLNodeMap@8", "Obtain a transport layer parameter node map from a device.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceGetTLNodeMap(PYLON_DEVICE_HANDLE hDev, RETVAL_PAR NODEMAP_HANDLE *phMap);

IDL_ENTRY(PYLONC_MODULE, "_PylonDeviceCreateChunkParser@8", "Create a chunk parser for a device.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceCreateChunkParser(PYLON_DEVICE_HANDLE hDev, RETVAL_PAR PYLON_CHUNKPARSER_HANDLE *phChp);

IDL_ENTRY(PYLONC_MODULE, "_PylonDeviceDestroyChunkParser@8", "Destroy a chunk parser.")
PYLONC_API GENAPIC_RESULT PYLONC_CC  PINVOKE
PylonDeviceDestroyChunkParser(PYLON_DEVICE_HANDLE hDev, PYLON_CHUNKPARSER_HANDLE hChp);

IDL_ENTRY(PYLONC_MODULE, "_PylonDeviceCreateEventAdapter@8", "Create an event adapter for a device.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceCreateEventAdapter(PYLON_DEVICE_HANDLE hDev, RETVAL_PAR PYLON_EVENTADAPTER_HANDLE *phEva);

IDL_ENTRY(PYLONC_MODULE, "_PylonDeviceDestroyEventAdapter@8", "Destroy an event adapter.")
PYLONC_API GENAPIC_RESULT PYLONC_CC  PINVOKE
PylonDeviceDestroyEventAdapter(PYLON_DEVICE_HANDLE hDev, PYLON_EVENTADAPTER_HANDLE hEva);

#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE_DOC
PylonDeviceRegisterRemovalCallback(PYLON_DEVICE_HANDLE hDev, PylonDeviceRemCb_t *pCbFunction, PINVOKE_RETVAL_PAR PYLON_DEVICECALLBACK_HANDLE *phCb);

PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceDeregisterRemovalCallback(PYLON_DEVICE_HANDLE hDev, PYLON_DEVICECALLBACK_HANDLE hCb);

PYLONC_API GENAPIC_RESULT PYLONC_CC 
PylonDeviceRegisterRemovalCallbackHwnd(PYLON_DEVICE_HANDLE hDev, void* hwnd, PylonDeviceRemCb_t *pCbFunction, PYLON_DEVICECALLBACK_HANDLE *phCb);

PYLONC_API GENAPIC_RESULT PYLONC_CC
PylonDeviceDeregisterRemovalCallbackHwnd(PYLON_DEVICE_HANDLE hDev, PYLON_DEVICECALLBACK_HANDLE hCb);
#endif

/* Device convenience methods */

#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceSetIntegerFeature(PYLON_DEVICE_HANDLE hDev, const char *pName, int64_t value);
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceGetIntegerFeature(PYLON_DEVICE_HANDLE hDev, const char *pName, PINVOKE_RETVAL_PAR int64_t *pValue);
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceGetIntegerFeatureMin(PYLON_DEVICE_HANDLE hDev, const char *pName, PINVOKE_RETVAL_PAR int64_t *pValue);
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceGetIntegerFeatureMax(PYLON_DEVICE_HANDLE hDev, const char *pName, PINVOKE_RETVAL_PAR int64_t *pValue);
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceGetIntegerFeatureInc(PYLON_DEVICE_HANDLE hDev, const char *pName, PINVOKE_RETVAL_PAR int64_t *pValue);
PYLONC_API GENAPIC_RESULT PYLONC_CC
PylonDeviceGrabSingleFrame(PYLON_DEVICE_HANDLE hDev, size_t channel, void * pBuffer, size_t bufferSize, PylonGrabResult_t *pGrabResult, _Bool *pReady, uint32_t timeout);
#endif

IDL_ENTRY(PYLONC_MODULE, "_PylonDeviceSetFloatFeature@16", "Set a float feature's value.") 
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceSetFloatFeature(PYLON_DEVICE_HANDLE hDev, STRING_PAR const char *pName, double value);

IDL_ENTRY(PYLONC_MODULE, "_PylonDeviceGetFloatFeature@12", "Return a float feature's value.") 
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceGetFloatFeature(PYLON_DEVICE_HANDLE hDev, STRING_PAR const char *pName, RETVAL_PAR double *pValue);

IDL_ENTRY(PYLONC_MODULE, "_PylonDeviceGetFloatFeatureMin@12", "Return a float feature's minimum value.") 
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceGetFloatFeatureMin(PYLON_DEVICE_HANDLE hDev, STRING_PAR const char *pName, RETVAL_PAR double *pValue);

IDL_ENTRY(PYLONC_MODULE, "_PylonDeviceGetFloatFeatureMax@12", "Return a float feature's maximum value.") 
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceGetFloatFeatureMax(PYLON_DEVICE_HANDLE hDev, STRING_PAR const char *pName, RETVAL_PAR double *pValue);

#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceSetBooleanFeature(PYLON_DEVICE_HANDLE hDev, const char *pName, _Bool value);

PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceGetBooleanFeature(PYLON_DEVICE_HANDLE hDev, const char *pName, PINVOKE_RETVAL_PAR _Bool * pValue);
#endif

IDL_ENTRY(PYLONC_MODULE, "_PylonDeviceExecuteCommandFeature@8", "Execute a command.") 
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceExecuteCommandFeature(PYLON_DEVICE_HANDLE hDev, STRING_PAR const char *pName);

#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceIsCommandDone(PYLON_DEVICE_HANDLE hDev, const char *pName, PINVOKE_RETVAL_PAR _Bool * pResult);
#endif

IDL_ENTRY(PYLONC_MODULE, "_PylonDeviceFeatureFromString@12", "Set a feature's value from a string.") 
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonDeviceFeatureFromString(PYLON_DEVICE_HANDLE hDev, STRING_PAR const char* pName, STRING_PAR const char* pValue);

#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC
PylonDeviceFeatureToString(PYLON_DEVICE_HANDLE hDev, const char *pName, char* pBuf, size_t* pBufLen);

PYLONC_API _Bool PYLONC_CC
PylonDeviceFeatureIsImplemented(PYLON_DEVICE_HANDLE hDev, const char* pName);

PYLONC_API _Bool PYLONC_CC
PylonDeviceFeatureIsAvailable(PYLON_DEVICE_HANDLE hDev, const char* pName);

PYLONC_API _Bool PYLONC_CC
PylonDeviceFeatureIsReadable(PYLON_DEVICE_HANDLE hDev, const char* pName);

PYLONC_API _Bool PYLONC_CC
PylonDeviceFeatureIsWritable(PYLON_DEVICE_HANDLE hDev, const char* pName);
#endif

IDL_ENTRY(GENAPIC_MODULE, "_PylonDeviceFeatureGetAccessMode@12", "Return a feature's access permissions.") 
PYLONC_API GENAPIC_RESULT GENAPIC_CC PINVOKE
PylonDeviceFeatureGetAccessMode( PYLON_DEVICE_HANDLE hDev, STRING_PAR const char* pName, RETVAL_PAR EGenApiAccessMode *pResult);

/* Stream grabber operations */
IDL_ENTRY(PYLONC_MODULE, "_PylonStreamGrabberOpen@4", "Open a stream grabber.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonStreamGrabberOpen(PYLON_STREAMGRABBER_HANDLE hStg);

IDL_ENTRY(PYLONC_MODULE, "_PylonStreamGrabberClose@4", "Close a stream grabber.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonStreamGrabberClose(PYLON_STREAMGRABBER_HANDLE hStg);

#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonStreamGrabberIsOpen(PYLON_STREAMGRABBER_HANDLE hStg, PINVOKE_RETVAL_PAR _Bool * pOpen);
#endif

IDL_ENTRY(PYLONC_MODULE, "_PylonStreamGrabberGetWaitObject@8", "Return a stream grabber's wait object.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonStreamGrabberGetWaitObject(PYLON_STREAMGRABBER_HANDLE hStg, RETVAL_PAR PYLON_WAITOBJECT_HANDLE *phWobj);

IDL_ENTRY(PYLONC_MODULE, "_PylonStreamGrabberSetMaxNumBuffer@8", "Set the maximum number of data buffers for a stream grabber to use.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonStreamGrabberSetMaxNumBuffer(PYLON_STREAMGRABBER_HANDLE hStg, size_t numBuffers );

IDL_ENTRY(PYLONC_MODULE, "_PylonStreamGrabberGetMaxNumBuffer@8", "Return the maximum number of data buffers a stream grabber is set to use.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonStreamGrabberGetMaxNumBuffer(PYLON_STREAMGRABBER_HANDLE hStg, RETVAL_PAR size_t *pNumBuffers );

IDL_ENTRY(PYLONC_MODULE, "_PylonStreamGrabberSetMaxBufferSize@8", "Set the maximum data buffer size for a stream grabber.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonStreamGrabberSetMaxBufferSize(PYLON_STREAMGRABBER_HANDLE hStg, size_t maxSize );

IDL_ENTRY(PYLONC_MODULE, "_PylonStreamGrabberGetMaxBufferSize@8", "Return the maximum data buffer size for a stream grabber.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonStreamGrabberGetMaxBufferSize(PYLON_STREAMGRABBER_HANDLE hStg, RETVAL_PAR size_t *pMaxSize );


#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC PylonStreamGrabberRegisterBuffer(PYLON_STREAMGRABBER_HANDLE hStg, void* pBuffer, size_t BufLen, PYLON_STREAMBUFFER_HANDLE *phBuf);
#endif

IDL_ENTRY(PYLONC_MODULE, "_PylonStreamGrabberDeregisterBuffer@8", "Detach an image data buffer from a stream grabber.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonStreamGrabberDeregisterBuffer(PYLON_STREAMGRABBER_HANDLE hStg, PYLON_STREAMBUFFER_HANDLE hBuf);

IDL_ENTRY(PYLONC_MODULE, "_PylonStreamGrabberPrepareGrab@4", "Prepare a stream grabber for grabbing.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonStreamGrabberPrepareGrab(PYLON_STREAMGRABBER_HANDLE hStg);

IDL_ENTRY(PYLONC_MODULE, "_PylonStreamGrabberFinishGrab@4", "Shut down a stream grabber.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonStreamGrabberFinishGrab(PYLON_STREAMGRABBER_HANDLE hStg);

IDL_ENTRY(PYLONC_MODULE, "_PylonStreamGrabberCancelGrab@4", "Cancel grab operation.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonStreamGrabberCancelGrab(PYLON_STREAMGRABBER_HANDLE hStg);

#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE_DOC
PylonStreamGrabberRetrieveResult(PYLON_STREAMGRABBER_HANDLE hStg, PylonGrabResult_t * pGrabResult, PINVOKE_RETVAL_PAR _Bool * pReady);
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE_DOC
PylonStreamGrabberQueueBuffer(PYLON_STREAMGRABBER_HANDLE hStg, PYLON_STREAMBUFFER_HANDLE hBuf, const void * pContext);
#endif

IDL_ENTRY(PYLONC_MODULE, "_PylonStreamGrabberGetNodeMap@8", "Return a node map for a stream grabber.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonStreamGrabberGetNodeMap(PYLON_STREAMGRABBER_HANDLE hStg, RETVAL_PAR NODEMAP_HANDLE *phMap);



/* Wait objects */
#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonWaitObjectIsValid(PYLON_WAITOBJECT_HANDLE hWobj, PINVOKE_RETVAL_PAR _Bool * pValid);

PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonWaitObjectWait(PYLON_WAITOBJECT_HANDLE hWobj, uint32_t timeout, PINVOKE_RETVAL_PAR _Bool * pResult);

PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonWaitObjectWaitEx(PYLON_WAITOBJECT_HANDLE hWobj, uint32_t timeout, _Bool alertable, PINVOKE_RETVAL_PAR EPylonWaitExResult *pWaitResult);
#endif

IDL_ENTRY(PYLONC_MODULE, "_PylonWaitObjectCreate@4", "Create a user-controllable wait object.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonWaitObjectCreate(RETVAL_PAR PYLON_WAITOBJECT_HANDLE *phWobj);

IDL_ENTRY(PYLONC_MODULE, "_PylonWaitObjectDestroy@4", "Get rid of a user-controllable wait object.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonWaitObjectDestroy(PYLON_WAITOBJECT_HANDLE hWobj);

IDL_ENTRY(PYLONC_MODULE, "_PylonWaitObjectSignal@4", "Set a wait object to the 'signaled' state.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonWaitObjectSignal(PYLON_WAITOBJECT_HANDLE hWobj);

IDL_ENTRY(PYLONC_MODULE, "_PylonWaitObjectReset@4", "Reset a wait object to the 'not signaled' state.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonWaitObjectReset(PYLON_WAITOBJECT_HANDLE hWobj);

IDL_ENTRY(PYLONC_MODULE, "_PylonWaitObjectsCreate@4", "Create a wait object set.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonWaitObjectsCreate(RETVAL_PAR PYLON_WAITOBJECTS_HANDLE *phWos);

IDL_ENTRY(PYLONC_MODULE, "_PylonWaitObjectsDestroy@4", "Destroy a wait object set.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonWaitObjectsDestroy(PYLON_WAITOBJECTS_HANDLE hWos);



#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE PylonWaitObjectsAdd(PYLON_WAITOBJECTS_HANDLE hWos, PYLON_WAITOBJECT_HANDLE hWobj, PINVOKE_RETVAL_PAR size_t *pIndex);

PYLONC_API GENAPIC_RESULT PYLONC_CC PylonWaitObjectsAddMany(PYLON_WAITOBJECTS_HANDLE hWos, size_t numWaitObjects, ...);
#endif

IDL_ENTRY(PYLONC_MODULE, "_PylonWaitObjectsRemoveAll@4", "Remove all wait objects from a wait object set.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonWaitObjectsRemoveAll(PYLON_WAITOBJECTS_HANDLE hWos);

#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE PylonWaitObjectsWaitForAll(PYLON_WAITOBJECTS_HANDLE hWos, uint32_t timeout, PINVOKE_RETVAL_PAR _Bool * pResult);

PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE PylonWaitObjectsWaitForAny(PYLON_WAITOBJECTS_HANDLE hWos, uint32_t timeout, size_t *pIndex, PINVOKE_RETVAL_PAR _Bool * pResult);
PYLONC_API GENAPIC_RESULT PYLONC_CC PylonWaitObjectsWaitForAny(PYLON_WAITOBJECTS_HANDLE hWos, uint32_t timeout, size_t *pIndex, _Bool * pResult);
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE PylonWaitObjectsWaitForAllEx(PYLON_WAITOBJECTS_HANDLE hWos, uint32_t timeout, _Bool alertable, PINVOKE_RETVAL_PAR EPylonWaitExResult *pWaitResult);

PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE PylonWaitObjectsWaitForAnyEx(PYLON_WAITOBJECTS_HANDLE hWos, uint32_t timeout, size_t *pIndex, _Bool alertable, PINVOKE_RETVAL_PAR EPylonWaitExResult *pWaitResult);
#endif



/* Event grabber operations */
extern PYLONC_API const size_t PylonEventGrabberBufferSize;

IDL_ENTRY(PYLONC_MODULE, "_PylonEventGrabberOpen@4", "Open an event grabber.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonEventGrabberOpen(PYLON_EVENTGRABBER_HANDLE hEvg);

IDL_ENTRY(PYLONC_MODULE, "_PylonEventGrabberClose@4", "Close an event grabber.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonEventGrabberClose(PYLON_EVENTGRABBER_HANDLE hEvg);

#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonEventGrabberIsOpen(PYLON_EVENTGRABBER_HANDLE hEvg, PINVOKE_RETVAL_PAR _Bool * pOpen);

PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE_DOC
PylonEventGrabberRetrieveEvent(PYLON_EVENTGRABBER_HANDLE hEvg, PylonEventResult_t * pEventResult, PINVOKE_RETVAL_PAR _Bool * pReady);
#endif

IDL_ENTRY(PYLONC_MODULE, "_PylonEventGrabberGetWaitObject@8", "Return an event grabber's wait object.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonEventGrabberGetWaitObject(PYLON_EVENTGRABBER_HANDLE hEvg, RETVAL_PAR PYLON_WAITOBJECT_HANDLE *phWobj);

IDL_ENTRY(PYLONC_MODULE, "_PylonEventGrabberGetNodeMap@8", "Return an event grabber's parameter node map.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonEventGrabberGetNodeMap(PYLON_EVENTGRABBER_HANDLE hEvg, RETVAL_PAR NODEMAP_HANDLE *phMap);

/* Event grabber convenience methods */
IDL_ENTRY(PYLONC_MODULE, "_PylonEventGrabberGetNumBuffers@8", "Return the number of event buffers used by an event grabber.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonEventGrabberGetNumBuffers(PYLON_EVENTGRABBER_HANDLE hEvg, RETVAL_PAR size_t *pNumBuffers);

IDL_ENTRY(PYLONC_MODULE, "_PylonEventGrabberSetNumBuffers@8", "Set the number of event buffers used by an event grabber.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonEventGrabberSetNumBuffers(PYLON_EVENTGRABBER_HANDLE hEvg, size_t numBuffers);

/* event adapter operations */
#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE_DOC
PylonEventAdapterDeliverMessage(PYLON_EVENTADAPTER_HANDLE hEva, const PylonEventResult_t * pEventResult);
#endif



/* Chunk parser operations */
#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC PylonChunkParserAttachBuffer(PYLON_CHUNKPARSER_HANDLE hChp, const void *pBuffer, size_t BufLen);
#endif

IDL_ENTRY(PYLONC_MODULE, "_PylonChunkParserDetachBuffer@4", "Detach a data buffer from a chunk parser.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonChunkParserDetachBuffer(PYLON_CHUNKPARSER_HANDLE hChp);

#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC
PylonChunkParserUpdateBuffer(PYLON_CHUNKPARSER_HANDLE hChp, const void *pBuffer);

PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonChunkParserHasCRC(PYLON_CHUNKPARSER_HANDLE hChp, PINVOKE_RETVAL_PAR _Bool * pResult);

PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonChunkParserCheckCRC(PYLON_CHUNKPARSER_HANDLE hChp, PINVOKE_RETVAL_PAR _Bool * pResult);
#endif

/* Color conversion operations */
IDL_ENTRY(PYLONC_MODULE, "_PylonPixelFormatConverterCreate@12", "Create a pixel format converter.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE_DOC
PylonPixelFormatConverterCreate(PYLON_DEVICE_HANDLE hDev,
                                int outAlign,
                                RETVAL_PAR PYLON_FORMAT_CONVERTER_HANDLE* phConv);

#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC
PylonPixelFormatConverterConvert( PYLON_FORMAT_CONVERTER_HANDLE hConv, void * targetBuffer, size_t targetBufferSize, const void * sourceBuffer, size_t sourceBufferSize );

PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonPixelFormatConverterGetOutputBufferSize(PYLON_FORMAT_CONVERTER_HANDLE hConv, PINVOKE_RETVAL_PAR size_t *pBufSiz);
#endif

IDL_ENTRY(PYLONC_MODULE, "_PylonPixelFormatConverterDestroy@4", "Delete a pixel format converter.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonPixelFormatConverterDestroy( PYLON_FORMAT_CONVERTER_HANDLE hConv );

IDL_ENTRY(PYLONC_MODULE, "_PylonBitsPerPixel@8", "Return the number of bits per pixel for a pixel type.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonBitsPerPixel(EPylonPixelType pixelType, RETVAL_PAR int* pResult);

#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonIsMono(EPylonPixelType pixelType, PINVOKE_RETVAL_PAR _Bool * pResult);
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonIsBayer(EPylonPixelType pixelType, PINVOKE_RETVAL_PAR _Bool * pResult);
#endif

IDL_ENTRY(PYLONC_MODULE, "_PylonPixelTypeFromString@8", "Translate a pixel type name to an enumeration value.")
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonPixelTypeFromString(STRING_PAR const char* pString, RETVAL_PAR EPylonPixelType *pPixelType);



#ifdef GENAPIC_WIN_BUILD   /* Stuff that requires the Win32 API */

PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonWaitObjectFromW32(HANDLE hW32, _Bool duplicate, PINVOKE_RETVAL_PAR PYLON_WAITOBJECT_HANDLE *phWobj);

PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE_DOC
PylonWaitObjectGetW32Handle(PYLON_WAITOBJECT_HANDLE hWobj, PINVOKE_RETVAL_PAR PHANDLE phW32);

PYLONC_API GENAPIC_RESULT PYLONC_CC
PylonRTThreadGetPriorityCapabilities(int32_t* pPriorityMin, int32_t* pPriorityMax);

PYLONC_API GENAPIC_RESULT PYLONC_CC
PylonRTThreadSetPriority(HANDLE hThread, int32_t priority);

PYLONC_API GENAPIC_RESULT PYLONC_CC
PylonRTThreadGetPriority(HANDLE hThread, int32_t* pPriority);

#endif /* GENAPIC_WIN_BUILD */


#ifndef PYLON_TLB_ONLY
GENAPIC_API GENAPIC_RESULT GENAPIC_CC PINVOKE_DOC
PylonDevicePortRead(PYLON_DEVICE_HANDLE hDev, void* pBuffer, int64_t Address, size_t Length);

GENAPIC_API GENAPIC_RESULT GENAPIC_CC PINVOKE_DOC
PylonDevicePortWrite(PYLON_DEVICE_HANDLE hDev, const void* pBuffer, int64_t Address, size_t Length);
#endif

IDL_ENTRY(PYLONC_MODULE, "_PylonFeaturePersistenceSave@8", "Saves the node tree to a file.") 
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonFeaturePersistenceSave(NODEMAP_HANDLE hMap, STRING_PAR const char* pFileName);

#ifndef PYLON_TLB_ONLY
PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonFeaturePersistenceLoad(NODEMAP_HANDLE hMap,  const char* pFileName, _Bool verify);

PYLONC_API GENAPIC_RESULT PYLONC_CC
PylonFeaturePersistenceSaveToString(NODEMAP_HANDLE hMap, char* pFeatures, size_t* pFeaturesLen);

PYLONC_API GENAPIC_RESULT PYLONC_CC PINVOKE
PylonFeaturePersistenceLoadFromString(NODEMAP_HANDLE hMap, const char* pFeatures, _Bool verify);
#endif

#ifdef __cplusplus
} /* extern "C" */
#  ifdef PYLONC_BOOL_DEFINED
#    undef _Bool
#    undef PYLONC_BOOL_DEFINED
#  endif

#endif /* __cplusplus */

#include <pylonc/PylonC32BitMethods.h>

#pragma pack(pop)

#endif /* PYLONC_PYLONC_H_ */
