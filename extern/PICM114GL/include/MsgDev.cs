using System;
using System.Text;
using System.Runtime.InteropServices;

namespace TPM
{
    public partial class MNet
    {
#if __WIN64__
        private const string MSGDLLNAME = "MNetMsg_x64.dll";
#elif WindowsCE
        private const string MSGDLLNAME = "MsgDevCE.dll";
#elif __TPM__
        private const string MSGDLLNAME = "MNetMsg.dll";
#else
        private const string MSGDLLNAME = "MsgDev.dll";
#endif

        // G9004A message mode device type
        public enum MsgSlaveType : ushort
        {
            P120 = 0x1620, // Pulse count
            T140 = 0x2040, // Temperature measure
            G180 = 0x0780, // DCON to Motionnet Gateway
            A122 = 0x0122, // Analog input and output
            UnKnow = 0xFFFF,
        }
        /////////////////////////////////////////////////////////////////////////////////
        // error code
        public enum MsgErrCode : short
        {
            ERR_MSG_NonsenseParameter1 = 1,
            ERR_MSG_NonsenseParameter2 = 2,
            ERR_MSG_NonsenseParameter3 = 3,
            ERR_MSG_NonsenseParameter4 = 4,
            ERR_MSG_NonsenseParameter5 = 5,
            ERR_MSG_NonsenseParameter6 = 6,
            ERR_MSG_NonsenseParameter7 = 7,
            ERR_MSG_NonsenseParameter8 = 8,
            ERR_MSG_NonsenseParameter9 = 9,
            ERR_MSG_NoError = 0,
            ERR_MSG_Base = (-1000),
            ERR_MSG_InvalidDeviceType = (ERR_MSG_Base - 1),
            ERR_MSG_InvalidParameter1 = (ERR_MSG_Base - 2),
            ERR_MSG_InvalidParameter2 = (ERR_MSG_Base - 3),
            ERR_MSG_InvalidParameter3 = (ERR_MSG_Base - 4),
            ERR_MSG_InvalidParameter4 = (ERR_MSG_Base - 5),
            ERR_MSG_InvalidParameter5 = (ERR_MSG_Base - 6),
            ERR_MSG_InvalidParameter6 = (ERR_MSG_Base - 7),
            ERR_MSG_InvalidParameter7 = (ERR_MSG_Base - 8),
            ERR_MSG_InvalidParameter8 = (ERR_MSG_Base - 9),
            ERR_MSG_InvalidParameter9 = (ERR_MSG_Base - 10),
            ERR_MSG_CommunicationError = (ERR_MSG_Base - 11),
            // G180
            ERR_G180_Base = (-1100),
            ERR_G180_InvalidCommand = (ERR_G180_Base - 1),
            ERR_G180_ChecksumError = (ERR_G180_Base - 2),
            ERR_G180_Timeout = (ERR_G180_Base - 3),
        }
        /////////////////////////////////////////////////////////////////////////////////
    }
}

