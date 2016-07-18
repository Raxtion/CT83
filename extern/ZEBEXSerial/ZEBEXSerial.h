//---------------------------------------------------------------------------

#ifndef ZEBEXSerialH
#define ZEBEXSerialH
#include <vcl>
#include "SerialPort.h"
//---------------------------------------------------------------------------
class CZEBEXSerial:private CSerialPort
{
private:

public:
        bool m_bInitOK;
        __fastcall CZEBEXSerial(int nPort);
        __fastcall ~CZEBEXSerial();
   

public:
        bool __fastcall OpenPort(int nPort);
        AnsiString __fastcall GetData();
        int __fastcall Disable();
        int __fastcall Enable();
        int __fastcall Sleep();
        int __fastcall Wakeup();
        int __fastcall Initial();
};

#endif
