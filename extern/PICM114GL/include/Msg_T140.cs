using System;
using System.Text;
using System.Runtime.InteropServices;

namespace TPM
{
    public partial class MNet
    {
        public class M_T140
        {
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_t140_initial(ushort RingNo, ushort SlaveIP);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_t140_get_channel_value(ushort RingNo, ushort SlaveIP, ushort ChannelNo, ushort[] Value);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_t140_get_value_all(ushort RingNo, ushort SlaveIP, ushort[] Value);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_t140_get_channel_temperature(ushort RingNo, ushort SlaveIP, ushort ChannelNo, ushort Type, double[] Degree);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_t140_get_temperature_all(ushort RingNo, ushort SlaveIP, ushort Type, double[] Degree);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_t140_get_channel_current(ushort RingNo, ushort SlaveIP, ushort ChannelNo, double[] MilliAmpere);
            [DllImport(MSGDLLNAME)]
            public static extern short _mnet_t140_get_current_all(ushort RingNo, ushort SlaveIP, double[] MilliAmpere);


        }
    }
}

