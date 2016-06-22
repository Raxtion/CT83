// Depend Master Hardware
#define _NEW_CARD_
using System;
using System.Text;
using System.Runtime.InteropServices;

namespace TPM
{
    public partial class MNet
    {

#if __WIN64__
        private const string DLLName = "MNet_x64.dll";
        private const string M1aName = "MNet_x64.dll";
#elif _NEW_CARD_
        private const string DLLName = "MNet.dll";
        private const string M1aName = "MNet.dll";
#else
        private const string DLLName = "CMNet.dll";
        private const string M1aName = "CMNet.dll";
#endif



        ////////////////////////////////////////////////////////////////////////////////
        //                                Error Code                                  //
        ////////////////////////////////////////////////////////////////////////////////
        public enum ErrCode : short
        {
            ERR_NoError = 0,
            ERR_MNET_Ring_Used = -1,
            ERR_Invalid_Ring = -2,
            ERR_Invalid_Slave = -3,
            ERR_Invalid_Hardware = -4,
            ERR_Invalid_Sync_Object = -5,
            ERR_RingCommunicationError = -8,
            ERR_RingCommunicationTimeOut = -9,
            ERR_DataFifoFull = -10,
            ERR_DataCommunicationFailed = -11,
            ERR_InvalidMaxVel = -16,
            ERR_ObsoleteFunction = -34,
            ERR_G94_RECEIVE_TimeOut = -36,
            ERR_G94_CPURead = -37,
            ERR_G94_MsgCommunication = -38,
            ERR_G94_MsgSize = -39,
            ERR_M4_CPLDRead = -46,
            ERR_M4_RegisterRead = -47,
            ERR_M4_CPLDWrite = -48,
            ERR_M4_RegisterWrite = -49,
            ERR_InvalidAxisNo = -50,
            ERR_FailGetDeviceTable = -74,
            ERR_NoDeviceFound = -75,
            ERR_SlowDownPointError = -101,
            ERR_M1A_InvalidCheckCode = -103,
            ERR_M1A_NotInitializedYet = -105,
            ERR_InvalidParameter_1 = -111,
            ERR_InvalidParameter_2 = -112,
            ERR_InvalidParameter_3 = -113,
            ERR_InvalidParameter_4 = -114,
            ERR_InvalidParameter_5 = -115,
            ERR_InvalidParameter_6 = -116,
            ERR_InvalidParameter_7 = -117,
            ERR_InvalidParameter_8 = -118,
            ERR_InvalidParameter_9 = -119,
            ERR_InvalidParameter_10 = -120,
            ERR_InvalidParameter_11 = -121,
            ERR_InvalidParameter_12 = -122,
            ERR_InvalidDeviceType = -152,
            ERR_GetDLLPath = -170,
            ERR_GetDLLVersion = -171

        }


        ////////////////////////////////////////////////////////////////////////////////
        //                           Slave Type Definition                            //
        ////////////////////////////////////////////////////////////////////////////////
        public enum SlaveType
        {
            // Axis
            G9103_M1X1 = 0xA2,
            G9003_M1X1 = 0xA3,
            G9004_M104 = 0xA4,
            G9004_NPM_FUA4 = 0xA5,
            G9004_NPM_M204 = 0xA6,
            G9004_M204 = 0xA7,
            G9004_M304T = 0xA8,
            // DIO (32 In/Out)
            G9002_Q32 = 0xB0,
            G9002_I16Q16 = 0xB2,
            G9002_I32 = 0xB4,
            // DIO (16 In/Out)
            G9102_I16 = 0xC0,
            G9102_I8Q8 = 0xC4,
            G9102_Q16 = 0xC7,
            G9205_I16 = 0xC8,
            G9205_I8Q8 = 0xCC,
            G9205_Q16 = 0xCF,
            // AIO
            G9004_A104 = 0xD0,
            G9004_A180 = 0xD1,
            // Message Mode Device
            G9004_MSG = 0xE0,
            // Others
            G9004_UNKNOWN = 0xFF,
        } ;

        ////////////////////////////////////////////////////////////////////////////////
        //                            Function Declaration                            //
        ////////////////////////////////////////////////////////////////////////////////

        //
        [DllImport(DLLName)]
        public static extern short _mnet_open();
        [DllImport(DLLName)]
        public static extern short _mnet_close();
        //
        // Ring Operation
        [DllImport(DLLName)]
        public static extern short _mnet_reset_ring(ushort RingNo);
        [DllImport(DLLName)]
        public static extern short _mnet_start_ring(ushort RingNo);
        [DllImport(DLLName)]
        public static extern short _mnet_stop_ring(ushort RingNo);
        [DllImport(DLLName)]
        public static extern short _mnet_get_ring_status(ushort RingNo, ref ushort Status);
        [DllImport(DLLName)]
        public static extern short _mnet_get_ring_error_counter(ushort RingNo, ref ushort ErrCount);
        [DllImport(DLLName)]
        public static extern short _mnet_reset_ring_error_counter(ushort RingNo);
        [DllImport(DLLName)]
        public static extern short _mnet_set_ring_config(ushort RingNo, ushort BaudRate);
        //
        // Slaves
        [DllImport(DLLName)]
        public static extern short _mnet_get_ring_active_table(ushort RingNo, ref uint DevTable);
        [DllImport(DLLName)]
        public static extern short _mnet_get_slave_type(ushort RingNo, ushort SlaveIP, ref byte SlaveType);
        [DllImport(DLLName)]
        public static extern short _mnet_get_msg_slave_type(ushort RingNo, ushort SlaveIP, ref ushort Type);
        //
        // Digital I/O Slave
        [DllImport(DLLName)]
        public static extern short _mnet_io_input(ushort RingNo, ushort SlaveIP, byte PortNo);
        [DllImport(DLLName)]
        public static extern short _mnet_io_output(ushort RingNo, ushort SlaveIP, byte PortNo, byte Val);
        [DllImport(DLLName)]
        public static extern short _mnet_io_input_all(ushort RingNo, ushort SlaveIP, byte[] Value);
        [DllImport(DLLName)]
        public static extern short _mnet_io_output_all(ushort RingNo, ushort SlaveIP, byte[] Value);
        [DllImport(DLLName)]
        public static extern short _mnet_bit_io_input(ushort RingNo, ushort SlaveIP, byte PortNo, byte BitNo, ref byte OnOff);
        [DllImport(DLLName)]
        public static extern short _mnet_bit_io_output(ushort RingNo, ushort SlaveIP, byte PortNo, byte BitNo, byte OnOff);
        [DllImport(DLLName)]
        public static extern short _mnet_bit_io_toggle(ushort RingNo, ushort SlaveIP, byte PortNo, byte BitNo);
        //
        // Misc.
        [DllImport(DLLName)]
        public static extern short _mnet_get_DLL_path(ref char lpFilePath, uint nSize, ref uint nLength);
        [DllImport(DLLName)]
        public static extern short _mnet_get_DLL_version(ref char lpBuf, uint nSize, ref uint nLength);
        //

    }


}
