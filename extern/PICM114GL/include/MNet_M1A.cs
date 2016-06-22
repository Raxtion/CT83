using System;
using System.Text;
using System.Runtime.InteropServices;

namespace TPM
{
    public partial class MNet
    {
        public class M_M1A
        {
            //
            // Initial
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_initial(ushort RingNo, ushort SlaveIP);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_load_motion_file(ushort RingNo, ushort SlaveIP, byte[] FilePath);
            //
            // Pulse I/O Configuration
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_pls_outmode(ushort RingNo, ushort SlaveIP, ushort pls_outmode);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_pls_iptmode(ushort RingNo, ushort SlaveIP, ushort pls_iptmode, ushort pls_iptdir);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_feedback_src(ushort RingNo, ushort SlaveIP, ushort FbkSrc);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_move_ratio(ushort RingNo, ushort SlaveIP, float move_ratio);
            //
            // Interface I/O Configuration
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_alm(ushort RingNo, ushort SlaveIP, ushort alm_logic, ushort alm_mode);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_inp(ushort RingNo, ushort SlaveIP, ushort inp_enable, ushort inp_logic);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_sd(ushort RingNo, ushort SlaveIP, short sd_enable, short sd_logic, short sd_latch, short sd_mode);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_erc(ushort RingNo, ushort SlaveIP, ushort erc_logic, ushort erc_on_time, ushort erc_off_time);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_erc_on(ushort RingNo, ushort SlaveIP, short on_off);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_auto_erc(ushort RingNo, ushort SlaveIP, short Enable);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_svon(ushort RingNo, ushort SlaveIP, ushort on_off);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_ralm(ushort RingNo, ushort SlaveIP, ushort on_off);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_pcs(ushort RingNo, ushort SlaveIP, ushort pcs_logic);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_ltc_logic(ushort RingNo, ushort SlaveIP, ushort ltc_logic);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_clr(ushort RingNo, ushort SlaveIP, ushort clr_logic);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_clr_mask(ushort RingNo, ushort SlaveIP, byte CLR_Mask);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_mechanical_input_filter(ushort RingNo, ushort SlaveIP, ushort on_off);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_backlash(ushort RingNo, ushort SlaveIP, ushort Value, ushort Enable, ushort CntSrc);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_dio_output(ushort RingNo, ushort SlaveIP, ushort DoNo, ushort on_off);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_dio_input(ushort RingNo, ushort SlaveIP, ushort DiNo);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_get_io_status(ushort RingNo, ushort SlaveIP, ref uint IO_status);
            //
            // Counter Operating
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_get_command(ushort RingNo, ushort SlaveIP, ref int Cmd);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_command(ushort RingNo, ushort SlaveIP, int Cmd);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_reset_command(ushort RingNo, ushort SlaveIP);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_get_position(ushort RingNo, ushort SlaveIP, ref int Pos);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_position(ushort RingNo, ushort SlaveIP, int Pos);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_reset_position(ushort RingNo, ushort SlaveIP);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_get_error_counter(ushort RingNo, ushort SlaveIP, ref int ErrCnt);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_error_counter(ushort RingNo, ushort SlaveIP, int ErrCnt);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_reset_error_counter(ushort RingNo, ushort SlaveIP);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_get_current_speed(ushort RingNo, ushort SlaveIP, ref uint Speed);
            //
            // Motion
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_tmove_speed(ushort RingNo, ushort SlaveIP, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_smove_speed(ushort RingNo, ushort SlaveIP, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_speed_pattern(ushort RingNo, ushort SlaveIP, byte Pattern);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_v_move(ushort RingNo, ushort SlaveIP, byte Dir);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_start_r_move(ushort RingNo, ushort SlaveIP, int Distance);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_start_a_move(ushort RingNo, ushort SlaveIP, int Pos);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_sd_stop(ushort RingNo, ushort SlaveIP);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_emg_stop(ushort RingNo, ushort SlaveIP);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_motion_done(ushort RingNo, ushort SlaveIP, ref ushort MoSt);
            //
            // Home
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_home_config(ushort RingNo, ushort SlaveIP, ushort home_mode, ushort org_logic, ushort ez_logic, ushort ez_count, ushort erc_out);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_start_home_move(ushort RingNo, ushort SlaveIP, byte Dir);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_start_home_search(ushort RingNo, ushort SlaveIP, byte Dir, int ORGOffset);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_start_home_escape(ushort RingNo, ushort SlaveIP, byte Dir);
            //
            // Position Compare and Latch
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_comparator_mode(ushort RingNo, ushort SlaveIP, short CompNo, short CmpSrc, short CmpMethod, short CmpAction);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_comparator_data(ushort RingNo, ushort SlaveIP, short CompNo, int Pos);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_trigger_comparator(ushort RingNo, ushort SlaveIP, ushort CmpSrc, ushort CmpMethod);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_trigger_comparator_data(ushort RingNo, ushort SlaveIP, int Data);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_auto_trigger(ushort RingNo, ushort SlaveIP, ushort CmpSrc, ushort CmpMethod, ushort Interval, ushort on_off);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_get_comparator_data(ushort RingNo, ushort SlaveIP, short CompNo, ref int Pos);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_soft_limit(ushort RingNo, ushort SlaveIP, int PLimit, int MLimit);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_enable_soft_limit(ushort RingNo, ushort SlaveIP, byte Action);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_disable_soft_limit(ushort RingNo, ushort SlaveIP);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_get_latch_data(ushort RingNo, ushort SlaveIP, short LatchNo, ref int Pos);
            //
            // Velocity Change
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_v_change(ushort RingNo, ushort SlaveIP, uint NewVel, float Time);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_fix_speed_range(ushort RingNo, ushort SlaveIP, uint MaxVel);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_unfix_speed_range(ushort RingNo, ushort SlaveIP);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_get_speed_range(ushort RingNo, ushort SlaveIP, ref uint MinVel, ref uint MaxVel);
            //
            // Position Override
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_start_p_change(ushort RingNo, ushort SlaveIP, int NewPos);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_start_d_change(ushort RingNo, ushort SlaveIP, int NewDist);
            //
            // Pre-registers
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_continuous_move(ushort RingNo, ushort SlaveIP, ushort Enable);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_get_preregister_status(ushort RingNo, ushort SlaveIP, ref byte Full);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_get_preregister_depth(ushort RingNo, ushort SlaveIP, ref byte Depth);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_cancel_preregister(ushort RingNo, ushort SlaveIP);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_shift_preregister(ushort RingNo, ushort SlaveIP);
            //
            // Interpolation
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_set_group(ushort RingNo, ushort GroupNo, ushort[] AxisArray, ushort AxisCount);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_group_reset_command(ushort RingNo, ushort GroupNo);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_group_reset_position(ushort RingNo, ushort GroupNo);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_group_continuous_move(ushort RingNo, ushort GroupNo, ushort Enable);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_group_tr_lineN(ushort RingNo, ushort GroupNo, int[] DistArray, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_group_ta_lineN(ushort RingNo, ushort GroupNo, int[] PosArray, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_group_sr_lineN(ushort RingNo, ushort GroupNo, int[] DistArray, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_group_sa_lineN(ushort RingNo, ushort GroupNo, int[] PosArray, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_group_tr_lineN_continuous(ushort RingNo, ushort GroupNo, int[] DistArray, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_group_ta_lineN_continuous(ushort RingNo, ushort GroupNo, int[] PosArray, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_group_sr_lineN_continuous(ushort RingNo, ushort GroupNo, int[] DistArray, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_group_sa_lineN_continuous(ushort RingNo, ushort GroupNo, int[] PosArray, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_group_tr_arc(ushort RingNo, ushort GroupNo, ushort AxIP, ushort AyIP, int OffsetCx, int OffsetCy, int OffsetEx, int OffsetEy, short Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_group_ta_arc(ushort RingNo, ushort GroupNo, ushort AxIP, ushort AyIP, int Cx, int Cy, int Ex, int Ey, short Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_group_sr_arc(ushort RingNo, ushort GroupNo, ushort AxIP, ushort AyIP, int OffsetCx, int OffsetCy, int OffsetEx, int OffsetEy, short Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_group_sa_arc(ushort RingNo, ushort GroupNo, ushort AxIP, ushort AyIP, int Cx, int Cy, int Ex, int Ey, short Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_group_tr_arc_continuous(ushort RingNo, ushort GroupNo, ushort AxIP, ushort AyIP, int OffsetCx, int OffsetCy, int OffsetEx, int OffsetEy, short Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_group_ta_arc_continuous(ushort RingNo, ushort GroupNo, ushort AxIP, ushort AyIP, int Cx, int Cy, int Ex, int Ey, short Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_group_sr_arc_continuous(ushort RingNo, ushort GroupNo, ushort AxIP, ushort AyIP, int OffsetCx, int OffsetCy, int OffsetEx, int OffsetEy, short Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_group_sa_arc_continuous(ushort RingNo, ushort GroupNo, ushort AxIP, ushort AyIP, int Cx, int Cy, int Ex, int Ey, short Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_group_emg_stop(ushort RingNo, ushort GroupNo);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_group_sd_stop(ushort RingNo, ushort GroupNo);
            //
            // EEPROM
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_get_hardware_info(ushort RingNo, ushort SlaveIP, ref uint VendorID, ref ushort DeviceID);
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_recovery_from_EEPROM(ushort RingNo, ushort SlaveIP);
            //[DllImport(M1aName)]
            //public static extern short _mnet_m1a_backup_to_EEPROM(ushort RingNo, ushort SlaveIP);
            //
            //others
            [DllImport(M1aName)]
            public static extern short _mnet_m1a_check_error(ushort RingNo, ushort SlaveIP, ref int ErrorStatus);
            //

#if __ENGINEER__
        [DllImport(DLLNAME)]
        public static extern short _mnet_m1a_write_asic_cmd(ushort RingNo, ushort SlaveIP, ushort Cmd);
        [DllImport(DLLNAME)]
        public static extern short _mnet_m1a_write_asic_reg_ushort(ushort RingNo, ushort SlaveIP, ushort RegIdx, ushort Low, ushort High);
        [DllImport(DLLNAME)]
        public static extern short _mnet_m1a_write_asic_reg_ulong(ushort RingNo, ushort SlaveIP, ushort RegIdx, uint Data);
        [DllImport(DLLNAME)]
        public static extern short _mnet_m1a_read_asic_reg_ushort(ushort RingNo, ushort SlaveIP, ushort RegIdx, ref ushort Low, ref ushort High);
        [DllImport(DLLNAME)]
        public static extern short _mnet_m1a_read_asic_reg_ulong(ushort RingNo, ushort SlaveIP, ushort RegIdx, ref uint Data);
        [DllImport(DLLNAME)]
        public static extern short _mnet_m1a_write_gpio(ushort RingNo, ushort SlaveIP, byte Value);
        [DllImport(DLLNAME)]
        public static extern short _mnet_m1a_read_gpio(ushort RingNo, ushort SlaveIP, ref byte Value);
        [DllImport(DLLNAME)]
        public static extern short _mnet_m1a_dump_registers(ushort RingNo, ushort SlaveIP);
        [DllImport(DLLNAME)]
        public static extern short _mnet_m1a_check_int(ushort RingNo, ushort SlaveIP, ref byte IntStatus);
        [DllImport(DLLNAME)]
        public static extern short _mnet_m1a_get_serr(ushort RingNo, ushort SlaveIP, ref uint ErrorStatus);
        [DllImport(DLLNAME)]
        public static extern short _mnet_m1a_get_sevt(ushort RingNo, ushort SlaveIP, ref uint EventStatus);
        [DllImport(DLLNAME)]
        public static extern short _mnet_m1a_set_int_factor(ushort RingNo, ushort SlaveIP, uint int_factor);
        [DllImport(DLLNAME)]
        public static extern short _mnet_m1a_get_EEPROM_data(ushort RingNo, ushort SlaveIP, ref ST_EEPROM eeprom);
#endif // __ENGINEER__
        }
    }

}
