using System;
using System.Text;
using System.Runtime.InteropServices;

namespace TPM
{
    public partial class MNet
    {
        public class M_A122
        {
            //
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_a122_initial(ushort RingNo, ushort SlaveIP);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_a122_get_hardware_info(ushort RingNo, ushort SlaveIP, ref byte DeviceID, ref byte MCU_Version);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_a122_get_input_channel_value(ushort RingNo, ushort SlaveIP, ushort ChannelNo, ref short Value);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_a122_get_input_value_all(ushort RingNo, ushort SlaveIP, short[] Value);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_a122_get_input_channel_voltage(ushort RingNo, ushort SlaveIP, ushort ChannelNo, ref double Volt);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_a122_get_input_voltage_all(ushort RingNo, ushort SlaveIP, double[] Volt);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_a122_set_output_channel_value(ushort RingNo, ushort SlaveIP, ushort ChannelNo, short Value);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_a122_set_output_value_all(ushort RingNo, ushort SlaveIP, short Value0, short Value1, short Value2, short Value3);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_a122_set_output_channel_voltage(ushort RingNo, ushort SlaveIP, ushort ChannelNo, double Volt);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_a122_set_output_voltage_all(ushort RingNo, ushort SlaveIP, double Volt0, double Volt1, double Volt2, double Volt3);


            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_a122_set_output_value(ushort RingNo, ushort SlaveIP, ushort Channels, short Value);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_a122_set_output_voltage(ushort RingNo, ushort SlaveIP, ushort Channels, double Volt);


        }
    }
}

