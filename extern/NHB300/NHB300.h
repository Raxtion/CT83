//---------------------------------------------------------------------------

#ifndef NHB300H
#define NHB300H
#include <vcl>
#include "SerialPort.h"
//---------------------------------------------------------------------------
class CNHB300:private CSerialPort
{
public:
        __fastcall CNHB300();
        __fastcall ~CNHB300();       

public:
        bool __fastcall OpenPort(int nPort);

        double __fastcall GetWeight();
        void __fastcall SetZero();



};

#endif
