//---------------------------------------------------------------------------

#ifndef SerialPortH
#define SerialPortH

#include "PComm.h"
//---------------------------------------------------------------------------
class CSerialPort 
{
private:
	
        int m_nPortNo;

	//DWORD m_nReadByte;
public:
        __fastcall CSerialPort();
        __fastcall ~CSerialPort();

        bool __fastcall Open(int nPort,int nBaudRate,int nMode);

        bool __fastcall WriteData(char *pBuffer,int nLen=0);
        bool __fastcall ReadData(char *pBuffer,char EndByte,int nTimeOut=1000);
        bool __fastcall ReadSizeData(char *pBuffer,int nTimeOut=1000);


};


//---------------------------------------------------------------------------
#endif
