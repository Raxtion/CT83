//---------------------------------------------------------------------------


#pragma hdrstop

#include "RS700HASerial.h"
#include "stdio.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

RS700HASerial g_2DReader(2);
//---------------------------------------------------------------------------
__fastcall RS700HASerial::RS700HASerial(int nPort)
{
    m_bInitOK=OpenPort(nPort);
}
//---------------------------------------------------------------------------
__fastcall RS700HASerial::~RS700HASerial()
{

}
//---------------------------------------------------------------------------
bool __fastcall RS700HASerial::OpenPort(int nPort)
{
    return Open(nPort,B9600,BIT_8|STOP_1|P_NONE);
}
//---------------------------------------------------------------------------
AnsiString __fastcall RS700HASerial::GetData()
{
    if(!m_bInitOK) return "Error!";

    char strReceive[100]={0};
    if(ReadData(strReceive,'\n'))
    {
        return (AnsiString)strReceive;
    }

    return "Error!";
}

//---------------------------------------------------------------------------
int __fastcall RS700HASerial::Read()
{
    char strSend[]="LON\r\n";
    WriteData(strSend);
    return 1;
}
