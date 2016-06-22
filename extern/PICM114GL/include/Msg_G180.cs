using System;
using System.Text;
using System.Runtime.InteropServices;

namespace TPM
{
    public partial class MNet
    {
        public class M_G180
        {
            /////////////////////////////////////////////////////////////////////////////////
            [StructLayout(LayoutKind.Sequential)]
            public struct DCON_CONFIG
            {
                // Baudrate
                public enum EBaudrate : byte
                {
                    EBaud1200 = 0,	// 1200 bits/sec
                    EBaud2400 = 1,	// 2400 bits/sec
                    EBaud4800 = 2,	// 4800 bits/sec
                    EBaud9600 = 3,	// 9600 bits/sec
                    EBaud19200 = 4,	// 19200 bits/sec
                    EBaud38400 = 5,	// 38400 bits/sec
                    EBaud57600 = 6,	// 57600 bits/sec
                    EBaud115200 = 7,	// 115200 bits/sec
                }

                // Parity scheme
                public enum EParity : byte
                {
                    EParN81 = 0,
                    EParE81 = 1,
                    EParO81 = 2,
                    EParN91 = 3,
                    EParN82 = 4,
                    EParE82 = 5,
                    EParO82 = 6,
                    EParN92 = 7,
                }

                public byte Switch;     // 0~255
                [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
                public byte[] M_Name;
                [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
                public byte[] S_Name;
                public byte Typecode;   // 0~255
                public byte Baudrate;   // 0~7, correspond to EBaudrate
                public byte Parity;     // 0~7, correspond to EParity
                public byte Filter;     // 0:60HZ rejection, 1:50HZ rejection
                public byte Checksum;   // 0:Disable, 1:Enable
                public byte Fast;       // 0:Normal, 1:Fast
                public byte Format;     // 0:Engineer Unit, 1:Percent, 2:2's Complement HEX
            }
            /////////////////////////////////////////////////////////////////////////////////
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_g180_initial(ushort RingNo, ushort SlaveIP);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_g180_get_hardware_info(ushort RingNo, ushort SlaveIP, ref byte DeviceID, ref byte MCU_Version);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_g180_run_mode(ushort RingNo, ushort SlaveIP);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_g180_stop_mode(ushort RingNo, ushort SlaveIP);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_g180_init_mode(ushort RingNo, ushort SlaveIP);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_g180_get_error_code(ushort RingNo, ushort SlaveIP, byte TargetFuncCode, ref byte ErrCode);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_g180_get_value(ushort RingNo, ushort SlaveIP, ushort AA, ushort Channels, uint[] Value, ref byte AI_Diagnostic);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_g180_set_value(ushort RingNo, ushort SlaveIP, ushort AA, ushort Channels, uint Value);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_g180_auto_search(ushort RingNo, ushort SlaveIP, byte Parity, byte Checksum);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_g180_get_configuration(ushort RingNo, ushort SlaveIP, ushort AA, byte[] Value);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_g180_write_eeprom(ushort RingNo, ushort SlaveIP);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_g180_set_switch(ushort RingNo, ushort SlaveIP, ushort AA, byte Switch);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_g180_set_configuration(ushort RingNo, ushort SlaveIP, ushort AA, byte NN, byte TT, byte CC, byte FF);
            /////////////////////////////////////////////////////////////////////////////////
        }
    }
}
