using System;
using System.Text;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace TPM
{
    public partial class Master
    {
        public class PCI_M114
        {


            private const string DLLNAME = "PCI_M114.dll";
            // Error Table
            public enum ErrCode : short
            {
                ERR_NoError = 0,
                ERR_OpenCardFailed = -14801,
                ERR_MapMemoryFailed = -14802,
                ERR_CardNumberRepeated = -14803,
                ERR_CardNotExist = -14804,
                ERR_CardNotInitYet = -14805,
                ERR_LoadLibraryFailed = -14806,
                ERR_OpenMNetFailed = -14807,
                ERR_InvalidCardNumber = -14808,
                ERR_InvalidAxisNumber = -14809,
                ERR_InvalidParameter1 = -14810,
                ERR_InvalidParameter2 = -14811,
                ERR_InvalidParameter3 = -14812,
                ERR_InvalidParameter4 = -14813,
                ERR_InvalidParameter5 = -14814,
                ERR_InvalidParameter6 = -14815,
                ERR_InvalidParameter7 = -14816,
                ERR_InvalidParameter8 = -14817,
                ERR_InvalidParameter9 = -14818,
                ERR_InvalidParameter10 = -14819,
                ERR_InvalidParameter11 = -14820,
                ERR_InvalidParameter12 = -14821,
                ERR_SlowDownPointError = -14822,
                ERR_Err3PointsInput = -14823,
                ERR_GetCenterFailed = -14824,
                ERR_CompareBufferFull = -14825,
                ERR_AxisNotStoppedYet = -14826,
                ERR_ObsoleteFunction = -14827,
                ERR_GetSecureIdFailed = -14828,
                ERR_GenAesKeyFailed = -14829,
                ERR_NotSupported = -14830,
                ERR_SetAutoCmpFifoFailed = -14831,
                ERR_InvalidBoardID = -14832,
                ERR_LoadFileFailed = -14833,
                ERR_SetInterruptFailed = -14834,
                ERR_WaitInterruptFailed = -14835,
                ERR_WaitInterruptTimeout = -14836,
            }

            // Card Type
            public enum CardType
            {
                CARD_UNKNOWN    = 0,
                CARD_PCI_M114   = 1,
                CARD_PCI_M114GH = 2,
                CARD_PCI_M114GM = 3,
                CARD_PCI_M114GL = 4,
                CARD_PCE_M114   = 5,
                CARD_PCE_M114GH = 6,
                CARD_PCE_M114GM = 7,
                CARD_PCE_M114GL = 8,
                CARD_PCI_M118GL = 10,
                CARD_PCE_M118GL = 12,
            };
            // Initialization
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_open(ref ushort existcards);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_close();
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_initial(ushort SwitchCardNo);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_switch_card_num(ushort CardIndex, ref ushort SwitchCardNo);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_check_switch_card_num(ushort SwitchCardNo, ref byte IsExist);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_cpld_version(ushort SwitchCardNo, ref ushort Ver);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_card_type(ushort SwitchCardNo, ref byte CardType);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_config_from_file(ushort SwitchCardNo, char[] FilePath);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_axis_parameter(ushort SwitchCardNo, ushort AxisNo, ushort ParamNo, double Val);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_axis_parameter(ushort SwitchCardNo, ushort AxisNo, ushort ParamNo, double[] Val);

            // Motionnet
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_ring_config(ushort SwitchCardNo, ushort RingOfCard, byte BaudRate);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_open_mnet(ushort SwitchCardNo);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_start_ring_num(ushort SwitchCardNo, ref ushort RingNo);

            // GPIO
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_axis_input(ushort SwitchCardNo, ushort AxisNo, ref ushort OnOff);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_axis_output(ushort SwitchCardNo, ushort AxisNo, ref ushort OnOff);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_axis_output(ushort SwitchCardNo, ushort AxisNo, ushort OnOff);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_toggle_axis_output(ushort SwitchCardNo, ushort AxisNo);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_axis_output(ushort SwitchCardNo, ushort AxisNo, ushort OnTime, ushort OffTime, ushort Count);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_stop_axis_output(ushort SwitchCardNo, ushort AxisNo);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_axis_output_count(ushort SwitchCardNo, ushort AxisNo, ref ushort Count);

            // Security
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_secure_id(ushort SwitchCardNo, byte[] SecureID);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_gen_aes_key(ushort SwitchCardNo, byte[] SI_Key, byte[] SecureID, byte[] AES_Key);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_check_aes_key(ushort SwitchCardNo, byte[] SI_Key, byte[] AES_Key, ref byte Validity);

            // Interface I/O Configuration
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_alm(ushort SwitchCardNo, ushort AxisNo, short alm_logic, short alm_mode);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_inp(ushort SwitchCardNo, ushort AxisNo, short inp_enable, short inp_logic);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_erc(ushort SwitchCardNo, ushort AxisNo, short erc_logic, short erc_on_time);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_auto_erc(ushort SwitchCardNo, ushort AxisNo, short enable);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_erc_on(ushort SwitchCardNo, ushort AxisNo, short on_off);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_servo(ushort SwitchCardNo, ushort AxisNo, short on_off);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_ralm(ushort SwitchCardNo, ushort AxisNo, short on_off);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_ell(ushort SwitchCardNo, ushort AxisNo, short ell_logic, short ell_mode);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_sd(ushort SwitchCardNo, ushort AxisNo, short enable, short sd_logic, short sd_latch, short sd_mode);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_mechanical_input_filter(ushort SwitchCardNo, ushort AxisNo, ushort ON_OFF);

            // Pulse I/O Configuration
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_pls_outmode(ushort SwitchCardNo, ushort AxisNo, short pls_outmode);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_pls_iptmode(ushort SwitchCardNo, ushort AxisNo, short pls_iptmode, short pls_logic);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_feedback_src(ushort SwitchCardNo, ushort AxisNo, short Src);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_abs_reference(ushort SwitchCardNo, ushort AxisNo, short Ref);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_backlash_comp(ushort SwitchCardNo, ushort AxisNo, short CompPulse);
            // Status
            [DllImport(DLLNAME)]
            public static extern short _m114_motion_done(ushort SwitchCardNo, ushort AxisNo);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_io_status(ushort SwitchCardNo, ushort AxisNo, ref ushort io_sts);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_check_error(ushort SwitchCardNo, ushort AxisNo, ref uint error);

            // Stop
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_sd_stop(ushort SwitchCardNo, ushort AxisNo, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_imd_stop(ushort SwitchCardNo, ushort AxisNo);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_emg_stop(ushort SwitchCardNo, ushort AxisNo);

            // Homing 
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_home_config(ushort SwitchCardNo, ushort AxisNo, short home_mode, short org_logic, short ez_logic, short ez_count, short erc_out);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_home_move(ushort SwitchCardNo, ushort AxisNo, byte Dir, uint StrVel, uint MaxVel, float Tacc);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_home_search(ushort SwitchCardNo, ushort AxisNo, byte Dir, uint StrVel, uint MaxVel, float Tacc, int ORGOffset);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_escape_home(ushort SwitchCardNo, ushort AxisNo, byte Dir, uint StrVel, uint MaxVel, float Tacc);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_search_ez(ushort SwitchCardNo, ushort AxisNo, byte Dir, byte EzCount, uint StrVel, uint MaxVel, float Tacc);

            // Jog
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_jog_switch_continue(ushort SwitchCardNo, ushort AxisNo, byte switch_logic, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_jog_switch_step(ushort SwitchCardNo, ushort AxisNo, byte switch_logic, int Step, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_jog_pulser_step(ushort SwitchCardNo, ushort AxisNo, byte pulser_Dir, byte Step, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_jog_stop(ushort SwitchCardNo, ushort AxisNo);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_jogio_status(ushort SwitchCardNo, ushort AxisNo, ref ushort jogio_sts);

            // Velocity Move
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_tv_move(ushort SwitchCardNo, ushort AxisNo, byte Dir, uint StrVel, uint MaxVel, float Tacc);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_sv_move(ushort SwitchCardNo, ushort AxisNo, byte Dir, uint StrVel, uint MaxVel, float Tacc);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_fix_speed_range(ushort SwitchCardNo, ushort AxisNo, uint MaxVel);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_unfix_speed_range(ushort SwitchCardNo, ushort AxisNo);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_v_change(ushort SwitchCardNo, ushort AxisNo, uint NewVel, float Time);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_current_speed(ushort SwitchCardNo, ushort AxisNo, ref uint speed);

            // Single-Axis Move
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_tr_move(ushort SwitchCardNo, ushort AxisNo, int Dist, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_ta_move(ushort SwitchCardNo, ushort AxisNo, int Pos, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sr_move(ushort SwitchCardNo, ushort AxisNo, int Dist, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sa_move(ushort SwitchCardNo, ushort AxisNo, int Pos, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_tr_move_after_axis(ushort SwitchCardNo, ushort AxisNo, ushort LeadingAxes, int Dist, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_ta_move_after_axis(ushort SwitchCardNo, ushort AxisNo, ushort LeadingAxes, int Pos, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_sr_move_after_axis(ushort SwitchCardNo, ushort AxisNo, ushort LeadingAxes, int Dist, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_sa_move_after_axis(ushort SwitchCardNo, ushort AxisNo, ushort LeadingAxes, int Pos, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_p_change(ushort SwitchCardNo, ushort AxisNo, int NewPos);

            // 2-Axis Linear Move
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_tr_move_xy(ushort SwitchCardNo, int DistX, int DistY, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_ta_move_xy(ushort SwitchCardNo, int PosX, int PosY, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sr_move_xy(ushort SwitchCardNo, int DistX, int DistY, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sa_move_xy(ushort SwitchCardNo, int PosX, int PosY, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_tr_move_zu(ushort SwitchCardNo, int DistZ, int DistU, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_ta_move_zu(ushort SwitchCardNo, int PosZ, int PosU, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sr_move_zu(ushort SwitchCardNo, int DistZ, int DistU, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sa_move_zu(ushort SwitchCardNo, int PosZ, int PosU, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_tr_line2(ushort SwitchCardNo, ushort[] AxisArray, int DistX, int DistY, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_ta_line2(ushort SwitchCardNo, ushort[] AxisArray, int PosX, int PosY, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sr_line2(ushort SwitchCardNo, ushort[] AxisArray, int DistX, int DistY, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sa_line2(ushort SwitchCardNo, ushort[] AxisArray, int PosX, int PosY, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_tr_move_ab(ushort SwitchCardNo, int DistA, int DistB, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_ta_move_ab(ushort SwitchCardNo, int PosA, int PosB, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sr_move_ab(ushort SwitchCardNo, int DistA, int DistB, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sa_move_ab(ushort SwitchCardNo, int PosA, int PosB, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_tr_move_cd(ushort SwitchCardNo, int DistC, int DistD, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_ta_move_cd(ushort SwitchCardNo, int PosC, int PosD, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sr_move_cd(ushort SwitchCardNo, int DistC, int DistD, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sa_move_cd(ushort SwitchCardNo, int PosC, int PosD, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            // 3-Axis Linear Move
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_tr_line3(ushort SwitchCardNo, ushort[] AxisArray, int DistX, int DistY, int DistZ, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_ta_line3(ushort SwitchCardNo, ushort[] AxisArray, int PosX, int PosY, int PosZ, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sr_line3(ushort SwitchCardNo, ushort[] AxisArray, int DistX, int DistY, int DistZ, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sa_line3(ushort SwitchCardNo, ushort[] AxisArray, int PosX, int PosY, int PosZ, uint StrVel, uint MaxVel, float Tacc, float Tdec);

            // 4-Axis Linear Move
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_tr_line4(ushort SwitchCardNo, int DistX, int DistY, int DistZ, int DistU, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_ta_line4(ushort SwitchCardNo, int PosX, int PosY, int PosZ, int PosU, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sr_line4(ushort SwitchCardNo, int DistX, int DistY, int DistZ, int DistU, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sa_line4(ushort SwitchCardNo, int PosX, int PosY, int PosZ, int PosU, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_tr_line4_abcd(ushort SwitchCardNo, int DistA, int DistB, int DistC, int DistD, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_ta_line4_abcd(ushort SwitchCardNo, int PosA, int PosB, int PosC, int PosD, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sr_line4_abcd(ushort SwitchCardNo, int DistA, int DistB, int DistC, int DistD, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sa_line4_abcd(ushort SwitchCardNo, int PosA, int PosB, int PosC, int PosD, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            // Circular Move
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_center(ushort SwitchCardNo, int Sx, int Sy, int Ex, int Ey, int Radius, byte Dir, ref int Cx, ref int Cy);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_tr_arc2(ushort SwitchCardNo, ushort[] AxisArray, int OffsetCx, int OffsetCy, int OffsetEx, int OffsetEy, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_ta_arc2(ushort SwitchCardNo, ushort[] AxisArray, int Cx, int Cy, int Ex, int Ey, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sr_arc2(ushort SwitchCardNo, ushort[] AxisArray, int OffsetCx, int OffsetCy, int OffsetEx, int OffsetEy, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sa_arc2(ushort SwitchCardNo, ushort[] AxisArray, int Cx, int Cy, int Ex, int Ey, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_tr_arc_xy(ushort SwitchCardNo, int OffsetCx, int OffsetCy, int OffsetEx, int OffsetEy, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_ta_arc_xy(ushort SwitchCardNo, int Cx, int Cy, int Ex, int Ey, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_tr_arc_zu(ushort SwitchCardNo, int OffsetCz, int OffsetCu, int OffsetEz, int OffsetEu, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_ta_arc_zu(ushort SwitchCardNo, int Cz, int Cu, int Ez, int Eu, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sr_arc_xy(ushort SwitchCardNo, int OffsetCx, int OffsetCy, int OffsetEx, int OffsetEy, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sa_arc_xy(ushort SwitchCardNo, int Cx, int Cy, int Ex, int Ey, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sr_arc_zu(ushort SwitchCardNo, int OffsetCz, int OffsetCu, int OffsetEz, int OffsetEu, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sa_arc_zu(ushort SwitchCardNo, int Cz, int Cu, int Ez, int Eu, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_tr_arc_ab(ushort SwitchCardNo, int OffsetCa, int OffsetCb, int OffsetEa, int OffsetEb, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_ta_arc_ab(ushort SwitchCardNo, int Ca, int Cb, int Ea, int Eb, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sr_arc_ab(ushort SwitchCardNo, int OffsetCa, int OffsetCb, int OffsetEa, int OffsetEb, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sa_arc_ab(ushort SwitchCardNo, int Ca, int Cb, int Ea, int Eb, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_tr_arc_cd(ushort SwitchCardNo, int OffsetCc, int OffsetCd, int OffsetEc, int OffsetEd, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_ta_arc_cd(ushort SwitchCardNo, int Cc, int Cd, int Ec, int Ed, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sr_arc_cd(ushort SwitchCardNo, int OffsetCc, int OffsetCd, int OffsetEc, int OffsetEd, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_sa_arc_cd(ushort SwitchCardNo, int Cc, int Cd, int Ec, int Ed, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);

            // Cylinder Surface Move
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_tr_arc_xyz(ushort SwitchCardNo, int OffsetCx, int OffsetCy, int OffsetEx, int OffsetEy, int DistZ, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_ta_arc_xyz(ushort SwitchCardNo, int Cx, int Cy, int Ex, int Ey, int PosZ, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_tr_arc_abc(ushort SwitchCardNo, int OffsetCa, int OffsetCb, int OffsetEa, int OffsetEb, int DistC, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_ta_arc_abc(ushort SwitchCardNo, int Ca, int Cb, int Ea, int Eb, int PosC, byte Dir, uint StrVel, uint MaxVel, float Tacc, float Tdec);

            // Counter Control
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_position(ushort SwitchCardNo, ushort AxisNo, ref int pos);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_position(ushort SwitchCardNo, ushort AxisNo, int pos);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_command(ushort SwitchCardNo, ushort AxisNo, ref int cmd);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_command(ushort SwitchCardNo, ushort AxisNo, int cmd);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_error_counter(ushort SwitchCardNo, ushort AxisNo, ref short error);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_reset_error_counter(ushort SwitchCardNo, ushort AxisNo);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_general_counter(ushort SwitchCardNo, ushort AxisNo, ref int CntValue);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_general_counter(ushort SwitchCardNo, ushort AxisNo, short CntSrc, int CntValue);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_target_pos(ushort SwitchCardNo, ushort AxisNo, ref int pos);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_target_pos(ushort SwitchCardNo, ushort AxisNo, int pos);

            // Ring Counter
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_enable_command_ring_counter(ushort SwitchCardNo, ushort AxisNo, uint RingCounter);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_disable_command_ring_counter(ushort SwitchCardNo, ushort AxisNo);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_enable_position_ring_counter(ushort SwitchCardNo, ushort AxisNo, uint RingCounter);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_disable_position_ring_counter(ushort SwitchCardNo, ushort AxisNo);

            // Soft Limit
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_soft_limit(ushort SwitchCardNo, ushort AxisNo, int PLimit, int NLimit);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_enable_soft_limit(ushort SwitchCardNo, ushort AxisNo, short Action);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_disable_soft_limit(ushort SwitchCardNo, ushort AxisNo);

            // Counter Latch
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_ltc_logic(ushort SwitchCardNo, ushort AxisNo, short ltc_logic);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_latch_data(ushort SwitchCardNo, ushort AxisNo, short LatchNo, ref int Pos);

            // Counter Comparator
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_general_comparator(ushort SwitchCardNo, ushort AxisNo, short CmpSrc, short CmpMethod, short CmpAction, int Data);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_check_compare_data(ushort SwitchCardNo, ushort AxisNo, short CompType, ref int Pos);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_check_compare_status(ushort SwitchCardNo, ushort AxisNo, ref ushort cmp_sts);

            // Counter Comparator Trigger Out(Axis 2 & 3)            
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_enable_trigger_comparator(ushort SwitchCardNo, ushort AxisNo, byte CmpSrc, byte CmpMethod, int CmpData);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_disable_trigger_comparator(ushort SwitchCardNo, ushort AxisNo);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_trigger_available_buffer(ushort SwitchCardNo, ushort AxisNo, ref byte buffer);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_add_trigger_comparator(ushort SwitchCardNo, ushort AxisNo, int CmpData);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_cancel_trigger_buffer(ushort SwitchCardNo, ushort AxisNo);

            // Continuous Move
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_check_continuous_buffer(ushort SwitchCardNo, ushort AxisNo);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_continuous_buffer_status(ushort SwitchCardNo, ushort AxisNo);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_cancel_continuous_buffer(ushort SwitchCardNo, ushort AxisNo);

            // Auto Compare(Axis 0 & 1)
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_auto_compare_encoder(ushort SwitchCardNo, ushort AxisNo, ref int EncPos);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_auto_compare_encoder(ushort SwitchCardNo, ushort AxisNo, int EncPos);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_auto_compare_count(ushort SwitchCardNo, ushort AxisNo, ref ushort Count);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_auto_compare_status(ushort SwitchCardNo, ushort AxisNo, ref ushort OnOff);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_auto_compare_trigger(ushort SwitchCardNo, ushort AxisNo, ushort Level, ushort Width);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_auto_compare_function(ushort SwitchCardNo, ushort AxisNo, byte Dir, int StrPos, int Interval, ushort TrgCnt);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_auto_compare_table(ushort SwitchCardNo, ushort AxisNo, byte Dir, ushort Size, int[] Table);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_start_auto_compare(ushort SwitchCardNo, ushort AxisNo, ushort OnOff);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_force_trigger_output(ushort SwitchCardNo, ushort AxisNo);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_auto_compare_source(ushort SwitchCardNo, ushort AxisNo, ushort SrcAxisNo);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_auto_compare_table_capacity(ushort SwitchCardNo, ushort AxisNo, ref ushort Size);

            //Interrupt
            //for Interrupt Support (PCE-M114GM only)
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_int_control(ushort SwitchCardNo, ushort IntType);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_int_wait(ushort SwitchCardNo, uint TimeoutInMs);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_int_check(ushort SwitchCardNo, ushort IntType, ushort IntAxes);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_set_int_factor(ushort SwitchCardNo, ushort AxisNo, uint IntFactor);
            [DllImport(DLLNAME)]
            public static extern ErrCode _m114_get_int_status(ushort SwitchCardNo, ushort AxisNo, uint ErrorInt, uint EventInt);

            
            
        }
    }
}
