using System;
using System.Text;
using System.Runtime.InteropServices;

namespace TPM
{
    public partial class MNet
    {
        public class M_P120
        {
            //
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_p120_initial(ushort RingNo, ushort SlaveIP);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_p120_get_hardware_info(ushort RingNo, ushort SlaveIP, ref byte DeviceID, ref byte MCU_Version);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_p120_start_channel_counter(ushort RingNo, ushort SlaveIP, ushort ChannelNo);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_p120_stop_channel_counter(ushort RingNo, ushort SlaveIP, ushort ChannelNo);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_p120_reset_channel_counter(ushort RingNo, ushort SlaveIP, ushort ChannelNo);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_p120_get_channel_value(ushort RingNo, ushort SlaveIP, ushort ChannelNo, ref uint Value);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_p120_get_value_all(ushort RingNo, ushort SlaveIP, uint[] Value);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_p120_get_mode(ushort RingNo, ushort SlaveIP, ushort Groups, ref byte Mode);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_p120_get_count(ushort RingNo, ushort SlaveIP, ushort ChannelNo, ref uint Value);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_p120_get_count_all(ushort RingNo, ushort SlaveIP, uint[] Value);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_p120_get_frequency(ushort RingNo, ushort SlaveIP, ushort ChannelNo, ref double Value);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_p120_get_frequency_all(ushort RingNo, ushort SlaveIP, double[] Value);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_p120_get_period(ushort RingNo, ushort SlaveIP, ushort ChannelNo, ref double Value);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_p120_get_period_all(ushort RingNo, ushort SlaveIP, double[] Value);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_p120_get_gate_time(ushort RingNo, ushort SlaveIP, ushort ChannelNo, ref double Value);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_p120_get_gate_time_all(ushort RingNo, ushort SlaveIP, double[] Value);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_p120_get_gate_count(ushort RingNo, ushort SlaveIP, ushort GroupNo, ref uint Value);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_p120_get_gate_count_all(ushort RingNo, ushort SlaveIP, uint[] Value);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_p120_start_counter(ushort RingNo, ushort SlaveIP, ushort ChannelNo);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_p120_stop_counter(ushort RingNo, ushort SlaveIP, ushort ChannelNo);


        }
    }
}

