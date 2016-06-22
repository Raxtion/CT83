//---------------------------------------------------------------------------


#pragma hdrstop

#include "CtkLedControll.h"
#include "stdio.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

__fastcall CTK_Led::CTK_Led()
{

}
//---------------------------------------------------------------------------
__fastcall CTK_Led::~CTK_Led()
{

}
//---------------------------------------------------------------------------
bool __fastcall CTK_Led::OpenPort(int nPort)
{
        return Open(nPort,B115200,BIT_8|STOP_1|P_NONE);
}
//---------------------------------------------------------------------------
bool __fastcall CTK_Led::SetMaxCurrent(int nA,int nB,int nC,int nD)
{
        char strSend[100]={0};
        int nCks=(0x89+0x55+0xaa+0x28+nA+nB+nC+nD) & 0xff;
        sprintf(strSend,"%c%c%c%c%c%c%c%c%c",0x89,0x55,0xaa,0x28,nA,nB,nC,nD,nCks);
        WriteData(strSend,0x89-0x80);
        char strReceive[100]={0};

        if(ReadData(strReceive,0x00))
        {

                return true;
        }
        else return false;
}
//---------------------------------------------------------------------------
bool __fastcall CTK_Led::SetCurrent(int nCh,int nM,int nC,int nP)
{
        char strSend[100]={0};
        int nCks=(0x89+0x55+0xaa+0x23+nCh+nM+nC+nP) & 0xff;
        sprintf(strSend,"%c%c%c%c%c%c%c%c%c",0x89,0x55,0xaa,0x23,nCh,nM,nC,nP,nCks);
        WriteData(strSend,0x89-0x80);
        char strReceive[100]={0};

        if(ReadData(strReceive,0x00))
        {

                return true;
        }
        else return false;
}
//---------------------------------------------------------------------------
void __fastcall CTK_Led::Try()
{
        char strSend[100]={0};
        int nCks=(0x85+0x55+0xaa+0x25) & 0xff;
        sprintf(strSend,"%c%%c%c%c",0x85,0x55,0xaa,0x25,nCks);
        WriteData(strSend,0x85-0x80);
        char strReceive[100]={0};

        if(ReadData(strReceive,0x00))
        {

                return;
        }
        else return;
}
