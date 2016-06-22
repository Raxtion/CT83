//---------------------------------------------------------------------------


#pragma hdrstop

#include "NHB300.h"
#include "stdio.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

CNHB300 g_Scale;
//---------------------------------------------------------------------------
__fastcall CNHB300::CNHB300()
{

}
//---------------------------------------------------------------------------
__fastcall CNHB300::~CNHB300()
{

}
//---------------------------------------------------------------------------
bool __fastcall CNHB300::OpenPort(int nPort)
{
        return Open(nPort,B9600,BIT_8|STOP_1|P_NONE);
}
//---------------------------------------------------------------------------
double __fastcall CNHB300::GetWeight()
{
        char strReceive[300]={0};
        AnsiString strMsg;
        AnsiString strMsgNew;

        if(ReadSizeData(strReceive))
        {
               AnsiString strMsg=strReceive;

               int nPosStart=strMsg.AnsiPos("ST,");
               int nPosEnd=strMsg.SubString(nPosStart,15).AnsiPos("g")+nPosStart-1;


                if(nPosStart>0 && nPosEnd>0 && (nPosEnd-nPosStart)>5)
                {
                                strMsgNew=strMsg.SubString(nPosEnd-8,8);
                                if(strMsgNew.AnsiPos("-")>0)
                                {
                                        strMsgNew=strMsg.SubString(nPosEnd-7,7);
                                        return strMsgNew.ToDouble()*-1.0;
                                }
                                else return strMsgNew.ToDouble();
                }
                else return -999.0;
        }
        else return -999.0;

}
//---------------------------------------------------------------------------
void __fastcall CNHB300::SetZero()
{
        char strReceive[300]={0};
        char strSend[100]={0};
        sprintf(strSend,"T");

        WriteData(strSend);



}



