//---------------------------------------------------------------------------


#pragma hdrstop

#include "ZEBEXSerial.h"
#include "stdio.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

CZEBEXSerial g_1DScanner(1);
//---------------------------------------------------------------------------
__fastcall CZEBEXSerial::CZEBEXSerial(int nPort)
{
    m_bInitOK=OpenPort(nPort);
}
//---------------------------------------------------------------------------
__fastcall CZEBEXSerial::~CZEBEXSerial()
{

}
//---------------------------------------------------------------------------
bool __fastcall CZEBEXSerial::OpenPort(int nPort)
{
    return Open(nPort,B9600,BIT_8|STOP_1|P_NONE);
}
//---------------------------------------------------------------------------
AnsiString __fastcall CZEBEXSerial::GetData()
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
int __fastcall CZEBEXSerial::Disable()
{
    char strSend[]="\x0f";
    WriteData(strSend);
    return 1;
}

//---------------------------------------------------------------------------
int __fastcall CZEBEXSerial::Enable()
{
    char strSend[]="\x0e";
    WriteData(strSend);
    return 1;
}

//---------------------------------------------------------------------------
int __fastcall CZEBEXSerial::Sleep()
{
    char strSend[]="\x12";
    WriteData(strSend);
    return 1;
}

//---------------------------------------------------------------------------
int __fastcall CZEBEXSerial::Wakeup()
{
    char strSend[]="\x14";
    WriteData(strSend);
    return 1;
}

//---------------------------------------------------------------------------
int __fastcall CZEBEXSerial::Initial()
{
    char strSend[]="\x05";
    WriteData(strSend);
    return 1;
}
