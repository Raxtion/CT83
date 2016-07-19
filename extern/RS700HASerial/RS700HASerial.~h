//---------------------------------------------------------------------------

#ifndef RS700HASerialH
#define RS700HASerialH
#include <vcl>
#include "SerialPort.h"
//---------------------------------------------------------------------------
class RS700HASerial:private CSerialPort
{
private:

public:
        bool m_bInitOK;
        __fastcall RS700HASerial(int nPort);
        __fastcall ~RS700HASerial();
   

public:
        bool __fastcall OpenPort(int nPort);
        AnsiString __fastcall GetData();
        int __fastcall Read();
};

#endif
