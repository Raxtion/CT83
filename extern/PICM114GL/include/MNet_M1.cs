using System;
using System.Text;
using System.Runtime.InteropServices;

namespace Motionnet
{
    public class MNetM1
    {
#if __WIN64__
        private const string DLLNAME = "CMNet_x64.dll";
#elif WindowsCE
        private const string DLLNAME = "MNetCE.dll";
#else
        private const string DLLNAME = "CMNet.dll";
#endif
        //
        // Initial
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_initial")]
        public static extern short _mnet_m1_initial(ushort RingNo, ushort SlaveIP);
        //
        // Pulse I/O Configuration
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_pls_outmode")]
        public static extern short _mnet_m1_set_pls_outmode(ushort RingNo, ushort SlaveIP, ushort pls_outmode);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_pls_iptmode")]
        public static extern short _mnet_m1_set_pls_iptmode(ushort RingNo, ushort SlaveIP, ushort pls_iptmode, ushort pls_iptdir);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_feedback_src")]
        public static extern short _mnet_m1_set_feedback_src(ushort RingNo, ushort SlaveIP, ushort FbkSrc);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_move_ratio")]
        public static extern short _mnet_m1_set_move_ratio(ushort RingNo, ushort SlaveIP, double move_ratio);
        //
        // Interface I/O Configuration
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_alm")]
        public static extern short _mnet_m1_set_alm(ushort RingNo, ushort SlaveIP, ushort alm_logic, ushort alm_mode);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_inp")]
        public static extern short _mnet_m1_set_inp(ushort RingNo, ushort SlaveIP, ushort inp_enable, ushort inp_logic);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_erc")]
        public static extern short _mnet_m1_set_erc(ushort RingNo, ushort SlaveIP, ushort erc_logic, ushort erc_on_time, ushort erc_off_time);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_erc_on")]
        public static extern short _mnet_m1_set_erc_on(ushort RingNo, ushort SlaveIP, short on_off);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_svon")]
        public static extern short _mnet_m1_set_svon(ushort RingNo, ushort SlaveIP, ushort on_off);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_ralm")]
        public static extern short _mnet_m1_set_ralm(ushort RingNo, ushort SlaveIP, ushort on_off);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_sd")]
        public static extern short _mnet_m1_set_sd(ushort RingNo, ushort SlaveIP, short sd_enable, short sd_logic, short sd_latch, short sd_mode);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_ltc_logic")]
        public static extern short _mnet_m1_set_ltc_logic(ushort RingNo, ushort SlaveIP, ushort ltc_logic);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_pcs")]
        public static extern short _mnet_m1_set_pcs(ushort RingNo, ushort SlaveIP, ushort pcs_logic);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_clr")]
        public static extern short _mnet_m1_set_clr(ushort RingNo, ushort SlaveIP, ushort clr_logic);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_dio_output")]
        public static extern short _mnet_m1_dio_output(ushort RingNo, ushort SlaveIP, ushort DoNo, ushort on_off);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_dio_input")]
        public static extern short _mnet_m1_dio_input(ushort RingNo, ushort SlaveIP, ushort DiNo);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_mechanical_input_filter")]
        public static extern short _mnet_m1_set_mechanical_input_filter(ushort RingNo, ushort SlaveIP, ushort on_off);
        // I/O Status
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_get_io_status")]
        public static extern short _mnet_m1_get_io_status(ushort RingNo, ushort SlaveIP, ref uint IO_status);
        //
        // Speed Pattern
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_speed_pattern")]
        public static extern short _mnet_m1_set_speed_pattern(ushort RingNo, ushort SlaveIP, byte Pattern);
        //
        // Velocity Control
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_v_move")]
        public static extern short _mnet_m1_v_move(ushort RingNo, ushort SlaveIP, byte Dir);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_v_change")]
        public static extern short _mnet_m1_v_change(ushort RingNo, ushort SlaveIP, double NewVel, double Time);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_fix_speed_range")]
        public static extern short _mnet_m1_fix_speed_range(ushort RingNo, ushort SlaveIP, double MaxVel);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_unfix_speed_range")]
        public static extern short _mnet_m1_unfix_speed_range(ushort RingNo, ushort SlaveIP);
        //
        // Position Control
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_tmove_speed")]
        public static extern short _mnet_m1_set_tmove_speed(ushort RingNo, ushort SlaveIP, double StrVel, double MaxVel, double Tacc, double Tdec);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_smove_speed")]
        public static extern short _mnet_m1_set_smove_speed(ushort RingNo, ushort SlaveIP, double StrVel, double MaxVel, double Tacc, double Tdec, double SVacc, double SVdec);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_start_r_move")]
        public static extern short _mnet_m1_start_r_move(ushort RingNo, ushort SlaveIP, int Distance);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_start_a_move")]
        public static extern short _mnet_m1_start_a_move(ushort RingNo, ushort SlaveIP, int Pos);
        //
        // Stop
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_sd_stop")]
        public static extern short _mnet_m1_sd_stop(ushort RingNo, ushort SlaveIP);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_emg_stop")]
        public static extern short _mnet_m1_emg_stop(ushort RingNo, ushort SlaveIP);
        //
        // Motion Status
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_motion_done")]
        public static extern short _mnet_m1_motion_done(ushort RingNo, ushort SlaveIP, ref ushort MoSt);
        //
        // Home
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_start_home_move")]
        public static extern short _mnet_m1_start_home_move(ushort RingNo, ushort SlaveIP, byte Dir);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_home_config")]
        public static extern short _mnet_m1_set_home_config(ushort RingNo, ushort SlaveIP, ushort home_mode, ushort org_logic, ushort ez_logic, ushort ez_count, ushort erc_out);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_start_home_search")]
        public static extern short _mnet_m1_start_home_search(ushort RingNo, ushort SlaveIP, byte Dir, double ORGOffset);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_start_home_escape")]
        public static extern short _mnet_m1_start_home_escape(ushort RingNo, ushort SlaveIP, byte Dir);
        //
        // Counter Operating
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_command")]
        public static extern short _mnet_m1_set_command(ushort RingNo, ushort SlaveIP, int Cmd);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_get_command")]
        public static extern short _mnet_m1_get_command(ushort RingNo, ushort SlaveIP, ref int Cmd);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_reset_command")]
        public static extern short _mnet_m1_reset_command(ushort RingNo, ushort SlaveIP);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_get_position")]
        public static extern short _mnet_m1_get_position(ushort RingNo, ushort SlaveIP, ref int Pos);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_position")]
        public static extern short _mnet_m1_set_position(ushort RingNo, ushort SlaveIP, int Pos);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_reset_position")]
        public static extern short _mnet_m1_reset_position(ushort RingNo, ushort SlaveIP);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_error_counter")]
        public static extern short _mnet_m1_set_error_counter(ushort RingNo, ushort SlaveIP, int ErrCnt);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_get_error_counter")]
        public static extern short _mnet_m1_get_error_counter(ushort RingNo, ushort SlaveIP, ref int ErrCnt);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_reset_error_counter")]
        public static extern short _mnet_m1_reset_error_counter(ushort RingNo, ushort SlaveIP);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_get_current_speed")]
        public static extern short _mnet_m1_get_current_speed(ushort RingNo, ushort SlaveIP, ref double speed);
        //
        // Position Compare and Latch
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_comparator_mode")]
        public static extern short _mnet_m1_set_comparator_mode(ushort RingNo, ushort SlaveIP, short CompNo, short CmpSrc, short CmpMethod, short CmpAction);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_comparator_data")]
        public static extern short _mnet_m1_set_comparator_data(ushort RingNo, ushort SlaveIP, short CompNo, double Pos);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_trigger_comparator")]
        public static extern short _mnet_m1_set_trigger_comparator(ushort RingNo, ushort SlaveIP, ushort CmpSrc, ushort CmpMethod);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_trigger_comparator_data")]
        public static extern short _mnet_m1_set_trigger_comparator_data(ushort RingNo, ushort SlaveIP, double Data);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_get_comparator_data")]
        public static extern short _mnet_m1_get_comparator_data(ushort RingNo, ushort SlaveIP, short CompNo, ref double Pos);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_soft_limit")]
        public static extern short _mnet_m1_set_soft_limit(ushort RingNo, ushort SlaveIP, int PLimit, int MLimit);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_enable_soft_limit")]
        public static extern short _mnet_m1_enable_soft_limit(ushort RingNo, ushort SlaveIP, byte Action);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_disable_soft_limit")]
        public static extern short _mnet_m1_disable_soft_limit(ushort RingNo, ushort SlaveIP);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_get_latch_data")]
        public static extern short _mnet_m1_get_latch_data(ushort RingNo, ushort SlaveIP, short LatchNo, ref double Pos);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_auto_trigger")]
        public static extern short _mnet_m1_set_auto_trigger(ushort RingNo, ushort SlaveIP, ushort CmpSrc, ushort CmpMethod, ushort Interval, ushort on_off);
        //
        // Destination Change
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_start_p_change")]
        public static extern short _mnet_m1_start_p_change(ushort RingNo, ushort SlaveIP, int NewPos);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_start_d_change")]
        public static extern short _mnet_m1_start_d_change(ushort RingNo, ushort SlaveIP, int NewDist);
        //
        // Backlash Correction
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_backlash")]
        public static extern short _mnet_m1_set_backlash(ushort RingNo, ushort SlaveIP, ushort Value, ushort Enable, ushort CntSrc);
        //
        // Synchronize
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_set_sta_trigger")]
        public static extern short _mnet_m1_set_sta_trigger(ushort RingNo, ushort SlaveIP, ushort TriType);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_sync_v_move")]
        public static extern short _mnet_m1_sync_v_move(ushort RingNo, ushort SlaveIP, byte Dir);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_start_sync_r_move")]
        public static extern short _mnet_m1_start_sync_r_move(ushort RingNo, ushort SlaveIP, int Distance);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_start_sync_a_move")]
        public static extern short _mnet_m1_start_sync_a_move(ushort RingNo, ushort SlaveIP, int Pos);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_start_sync_tr_line")]
        public static extern short _mnet_m1_start_sync_tr_line(ushort RingNo, ref ushort SlaveIP, int DistX, int DistY, double StrVel, double MaxVel, double Tacc, double Tdec);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_start_sync_ta_line")]
        public static extern short _mnet_m1_start_sync_ta_line(ushort RingNo, ref ushort SlaveIP, int PosX, int PosY, double StrVel, double MaxVel, double Tacc, double Tdec);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_start_sync_sr_line")]
        public static extern short _mnet_m1_start_sync_sr_line(ushort RingNo, ref ushort SlaveIP, int DistX, int DistY, double StrVel, double MaxVel, double Tacc, double Tdec, double SVacc, double SVdec);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_start_sync_sa_line")]
        public static extern short _mnet_m1_start_sync_sa_line(ushort RingNo, ref ushort SlaveIP, int PosX, int PosY, double StrVel, double MaxVel, double Tacc, double Tdec, double SVacc, double SVdec);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_sync_sd_stop")]
        public static extern short _mnet_m1_sync_sd_stop(ushort RingNo, ushort SlaveIP);
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_sync_imd_stop")]
        public static extern short _mnet_m1_sync_imd_stop(ushort RingNo, ushort SlaveIP);
        //
        // Misc
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_get_speed_range")]
        public static extern short _mnet_m1_get_speed_range(ushort RingNo, ushort SlaveIP, ref double MinVel, ref double MaxVel);
        //
        //others
        [DllImport(DLLNAME, EntryPoint = "_mnet_m1_check_error")]
        public static extern short _mnet_m1_check_error(ushort RingNo, ushort SlaveIP, ref int ErrorStatus);
        //

    }
}
