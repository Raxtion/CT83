//---------------------------------------------------------------------------

#ifndef CtkLedControllH
#define CtkLedControllH
#include <vcl>
#include "SerialPort.h"

//---------------------------------------------------------------------------
class CTK_Led :private CSerialPort
{
public:
        __fastcall CTK_Led();
        __fastcall ~CTK_Led();
        bool __fastcall OpenPort(int nPort);
        bool __fastcall SetMaxCurrent(int nA,int nB,int nC,int nD);
        bool __fastcall SetCurrent(int nCh,int nM,int nC,int nP);       //nM: 0:constant 1:extern 2:strobe nC:Current nP:Pulse

        void __fastcall Try();

        
};
#endif
 