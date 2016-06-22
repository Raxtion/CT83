using System;
using System.Text;
using System.Runtime.InteropServices;

namespace TPM
{
    public partial class MNet
    {
        private const string DLLName = "CMNet.dll";
        
        public class M204
        {
            ////////////////////////////////////////////////////////////////////////////////
            /////////////////////////                            ///////////////////////////
            ///////////////////////// 4-Axis Motion Slaves(M204) ///////////////////////////
            /////////////////////////                            ///////////////////////////
            ////////////////////////////////////////////////////////////////////////////////
            //
            // Initial
            [DllImport(DLLName)]
            public static extern short _mnet_m204_initial(ushort RingNo, ushort SlaveIP);
            //
            // Pulse I/O Configuration
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_pls_outmode(ushort RingNo, ushort SlaveIP, ushort AxisNo, ushort pls_outmode);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_pls_iptmode(ushort RingNo, ushort SlaveIP, ushort AxisNo, ushort pls_iptmode, ushort pls_iptdir);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_feedback_src(ushort RingNo, ushort SlaveIP, ushort AxisNo, ushort FbkSrc);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_abs_reference(ushort RingNo, ushort SlaveIP, ushort AxisNo, short Ref);
            //
            // Interface I/O Configuration
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_alm(ushort RingNo, ushort SlaveIP, ushort AxisNo, ushort alm_logic, ushort alm_mode);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_inp(ushort RingNo, ushort SlaveIP, ushort AxisNo, ushort inp_enable, ushort inp_logic);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_erc(ushort RingNo, ushort SlaveIP, ushort AxisNo, ushort erc_logic, ushort erc_on_time, ushort erc_off_time);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_erc_on(ushort RingNo, ushort SlaveIP, ushort AxisNo, short on_off);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_sd(ushort RingNo, ushort SlaveIP, ushort AxisNo, short sd_enable, short sd_logic, short sd_latch, short sd_mode);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_svon(ushort RingNo, ushort SlaveIP, ushort AxisNo, ushort on_off);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_ralm(ushort RingNo, ushort SlaveIP, ushort AxisNo, ushort on_off);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_ltc_logic(ushort RingNo, ushort SlaveIP, ushort AxisNo, ushort ltc_logic);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_el(ushort RingNo, ushort SlaveIP, ushort AxisNo, short el_mode, short el_logic);
            // I/O Status
            [DllImport(DLLName)]
            public static extern short _mnet_m204_get_io_status(ushort RingNo, ushort SlaveIP, ushort AxisNo, ref ushort io_sts);
            //
            // Velocity Control
            [DllImport(DLLName)]
            public static extern short _mnet_m204_tv_move(ushort RingNo, ushort SlaveIP, ushort AxisNo, double StrVel, double MaxVel, double Tacc);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_sv_move(ushort RingNo, ushort SlaveIP, ushort AxisNo, double StrVel, double MaxVel, double Tacc, double SVacc);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_v_change(ushort RingNo, ushort SlaveIP, ushort AxisNo, double NewVel, double Time);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_cmp_v_change(ushort RingNo, ushort SlaveIP, ushort AxisNo, double Res_Dist, double OldVel, double NewVel, double Time);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_fix_speed_range(ushort RingNo, ushort SlaveIP, ushort AxisNo, double MaxVel);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_unfix_speed_range(ushort RingNo, ushort SlaveIP, ushort AxisNo);
            //
            // Position Control
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_tr_move(ushort RingNo, ushort SlaveIP, ushort AxisNo, double Dist, double StrVel, double MaxVel, double Tacc, double Tdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_ta_move(ushort RingNo, ushort SlaveIP, ushort AxisNo, double Pos, double StrVel, double MaxVel, double Tacc, double Tdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_sr_move(ushort RingNo, ushort SlaveIP, ushort AxisNo, double Dist, double StrVel, double MaxVel, double Tacc, double Tdec, double SVacc, double SVdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_sa_move(ushort RingNo, ushort SlaveIP, ushort AxisNo, double Pos, double StrVel, double MaxVel, double Tacc, double Tdec, double SVacc, double SVdec);
            //
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_tr_line2(ushort RingNo, ushort SlaveIP, short[] AxisArray, double DistX, double DistY, double StrVel, double MaxVel, double Tacc, double Tdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_ta_line2(ushort RingNo, ushort SlaveIP, short[] AxisArray, double PosX, double PosY, double StrVel, double MaxVel, double Tacc, double Tdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_sr_line2(ushort RingNo, ushort SlaveIP, short[] AxisArray, double DistX, double DistY, double StrVel, double MaxVel, double Tacc, double Tdec, double SVacc, double SVdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_sa_line2(ushort RingNo, ushort SlaveIP, short[] AxisArray, double PosX, double PosY, double StrVel, double MaxVel, double Tacc, double Tdec, double SVacc, double SVdec);
            //
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_tr_line3(ushort RingNo, ushort SlaveIP, short[] AxisArray, double DistX, double DistY, double DistZ, double StrVel, double MaxVel, double Tacc, double Tdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_ta_line3(ushort RingNo, ushort SlaveIP, short[] AxisArray, double PosX, double PosY, double PosZ, double StrVel, double MaxVel, double Tacc, double Tdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_sr_line3(ushort RingNo, ushort SlaveIP, short[] AxisArray, double DistX, double DistY, double DistZ, double StrVel, double MaxVel, double Tacc, double Tdec, double SVacc, double SVdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_sa_line3(ushort RingNo, ushort SlaveIP, short[] AxisArray, double PosX, double PosY, double PosZ, double StrVel, double MaxVel, double Tacc, double Tdec, double SVacc, double SVdec);
            //
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_tr_line4(ushort RingNo, ushort SlaveIP, double DistX, double DistY, double DistZ, double DistU, double StrVel, double MaxVel, double Tacc, double Tdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_ta_line4(ushort RingNo, ushort SlaveIP, double PosX, double PosY, double PosZ, double PosU, double StrVel, double MaxVel, double Tacc, double Tdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_sr_line4(ushort RingNo, ushort SlaveIP, double DistX, double DistY, double DistZ, double DistU, double StrVel, double MaxVel, double Tacc, double Tdec, double SVacc, double SVdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_sa_line4(ushort RingNo, ushort SlaveIP, double PosX, double PosY, double PosZ, double PosU, double StrVel, double MaxVel, double Tacc, double Tdec, double SVacc, double SVdec);
            //
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_tr_arc2(ushort RingNo, ushort SlaveIP, short[] AxisArray, double OffsetCx, double OffsetCy, double OffsetEx, double OffsetEy, short DIR, double StrVel, double MaxVel, double Tacc, double Tdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_ta_arc2(ushort RingNo, ushort SlaveIP, short[] AxisArray, double Cx, double Cy, double Ex, double Ey, short DIR, double StrVel, double MaxVel, double Tacc, double Tdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_sr_arc2(ushort RingNo, ushort SlaveIP, short[] AxisArray, double OffsetCx, double OffsetCy, double OffsetEx, double OffsetEy, short DIR, double StrVel, double MaxVel, double Tacc, double Tdec, double SVacc, double SVdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_sa_arc2(ushort RingNo, ushort SlaveIP, short[] AxisArray, double Cx, double Cy, double Ex, double Ey, short DIR, double StrVel, double MaxVel, double Tacc, double Tdec, double SVacc, double SVdec);
            //
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_tr_arc_xyz(ushort RingNo, ushort SlaveIP, double OffsetCx, double OffsetCy, double OffsetEx, double OffsetEy, double DistZ, short DIR, double StrVel, double MaxVel, double Tacc, double Tdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_ta_arc_xyz(ushort RingNo, ushort SlaveIP, double Cx, double Cy, double Ex, double Ey, double PosZ, short DIR, double StrVel, double MaxVel, double Tacc, double Tdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_sr_arc_xyz(ushort RingNo, ushort SlaveIP, double OffsetCx, double OffsetCy, double OffsetEx, double OffsetEy, double DistZ, short DIR, double StrVel, double MaxVel, double Tacc, double Tdec, double SVacc, double SVdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_sa_arc_xyz(ushort RingNo, ushort SlaveIP, double Cx, double Cy, double Ex, double Ey, double PosZ, short DIR, double StrVel, double MaxVel, double Tacc, double Tdec, double SVacc, double SVdec);
            //
            [DllImport(DLLName)]
            public static extern short _mnet_m204_tr_move_after_axis(ushort RingNo, ushort SlaveIP, ushort AxisNo, ushort LeadingAxes, double Dist, double StrVel, double MaxVel, double Tacc, double Tdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_ta_move_after_axis(ushort RingNo, ushort SlaveIP, ushort AxisNo, ushort LeadingAxes, double Pos, double StrVel, double MaxVel, double Tacc, double Tdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_sr_move_after_axis(ushort RingNo, ushort SlaveIP, ushort AxisNo, ushort LeadingAxes, double Dist, double StrVel, double MaxVel, double Tacc, double Tdec, double SVacc, double SVdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_sa_move_after_axis(ushort RingNo, ushort SlaveIP, ushort AxisNo, ushort LeadingAxes, double Pos, double StrVel, double MaxVel, double Tacc, double Tdec, double SVacc, double SVdec);
            //
            // Stop
            [DllImport(DLLName)]
            public static extern short _mnet_m204_sd_stop(ushort RingNo, ushort SlaveIP, ushort AxisNo, double Tdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_emg_stop(ushort RingNo, ushort SlaveIP, ushort AxisNo);
            //
            // Motion Status
            [DllImport(DLLName)]
            public static extern short _mnet_m204_motion_done(ushort RingNo, ushort SlaveIP, ushort AxisNo, ref ushort McSts);
            //
            // Home
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_home_config(ushort RingNo, ushort SlaveIP, ushort AxisNo, ushort home_mode, ushort org_logic, ushort ez_logic, ushort ez_count, ushort erc_out);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_home_move(ushort RingNo, ushort SlaveIP, ushort AxisNo, double StrVel, double MaxVel, double Tacc);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_escape_home(ushort RingNo, ushort SlaveIP, ushort AxisNo, double StrVel, double MaxVel, double Tacc);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_home_search(ushort RingNo, ushort SlaveIP, ushort AxisNo, double StrVel, double MaxVel, double Tacc, double ORGOffset);
            //
            // Counter Operating
            [DllImport(DLLName)]
            public static extern short _mnet_m204_get_command(ushort RingNo, ushort SlaveIP, ushort AxisNo, ref int cmd);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_get_position(ushort RingNo, ushort SlaveIP, ushort AxisNo, ref int pos);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_get_error_counter(ushort RingNo, ushort SlaveIP, ushort AxisNo, ref short error);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_command(ushort RingNo, ushort SlaveIP, ushort AxisNo, int cmd);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_position(ushort RingNo, ushort SlaveIP, ushort AxisNo, int pos);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_reset_command(ushort RingNo, ushort SlaveIP, ushort AxisNo);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_reset_position(ushort RingNo, ushort SlaveIP, ushort AxisNo);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_reset_error_counter(ushort RingNo, ushort SlaveIP, ushort AxisNo);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_get_target_pos(ushort RingNo, ushort SlaveIP, ushort AxisNo, ref int Pos);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_target_pos(ushort RingNo, ushort SlaveIP, ushort AxisNo, int Pos);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_move_ratio(ushort RingNo, ushort SlaveIP, ushort AxisNo, double Ratio);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_ring_count(ushort RingNo, ushort SlaveIP, ushort AxisNo, ushort Src, double Data);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_enable_ring_count(ushort RingNo, ushort SlaveIP, ushort AxisNo, ushort Src, ushort OnOff);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_get_rest_command(ushort RingNo, ushort SlaveIP, ushort AxisNo, ref int rest_command);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_get_current_speed(ushort RingNo, ushort SlaveIP, ushort AxisNo, ref double speed);
            //
            // Position Override
            [DllImport(DLLName)]
            public static extern short _mnet_m204_p_change(ushort RingNo, ushort SlaveIP, ushort AxisNo, double NewPos);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_d_change(ushort RingNo, ushort SlaveIP, ushort AxisNo, double NewDist);
            //
            // General Compare
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_general_comparator(ushort RingNo, ushort SlaveIP, ushort AxisNo, short CmpSrc, short CmpMethod, short CmpAction, double Data);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_trigger_comparator(ushort RingNo, ushort SlaveIP, ushort AxisNo, short CmpSrc, short CmpMethod, double Data);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_trigger_type(ushort RingNo, ushort SlaveIP, ushort AxisNo, short TriggerType);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_soft_limit(ushort RingNo, ushort SlaveIP, ushort AxisNo, int PLimit, int NLimit);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_enable_soft_limit(ushort RingNo, ushort SlaveIP, ushort AxisNo, short Action);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_disable_soft_limit(ushort RingNo, ushort SlaveIP, ushort AxisNo);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_check_compare_data(ushort RingNo, ushort SlaveIP, ushort AxisNo, short CmpType, ref double Pos);
            //
            // Auto Compare
            [DllImport(DLLName)]
            public static extern short _mnet_m204_get_auto_compare_encoder(ushort RingNo, ushort SlaveIP, ushort AxisNo, ref int EncPos);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_auto_compare_encoder(ushort RingNo, ushort SlaveIP, ushort AxisNo, int EncPos);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_get_auto_compare_count(ushort RingNo, ushort SlaveIP, ushort AxisNo, ref ushort Count);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_get_auto_compare_status(ushort RingNo, ushort SlaveIP, ushort AxisNo, ref ushort OnOff);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_auto_compare_trigger(ushort RingNo, ushort SlaveIP, ushort AxisNo, ushort Level, ushort Width);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_auto_compare_function(ushort RingNo, ushort SlaveIP, ushort AxisNo, byte Dir, int StrPos, int Interval, ushort TrgCnt);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_set_auto_compare_table(ushort RingNo, ushort SlaveIP, ushort AxisNo, byte Dir, ushort Size, ref int Table);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_start_auto_compare(ushort RingNo, ushort SlaveIP, ushort AxisNo, ushort OnOff);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_force_trigger_output(ushort RingNo, ushort SlaveIP, ushort AxisNo);
            //
            // Jog
            enum JogStep { Jog_Step_1 = 1, Jog_Step_10 = 10, Jog_Step_100 = 100 };
            [DllImport(DLLName)]
            public static extern short _mnet_m204_jog_switch_continue(ushort RingNo, ushort SlaveIP, ushort AxisNo, ushort SwitchLogic, double StrVel, double MaxVel, double Tacc, double Tdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_jog_switch_step(ushort RingNo, ushort SlaveIP, ushort AxisNo, ushort SwitchLogic, double Dist, double StrVel, double MaxVel, double Tacc, double Tdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_jog_pulser_step(ushort RingNo, ushort SlaveIP, ushort AxisNo, byte Dir, byte Step, double StrVel, double MaxVel, double Tacc, double Tdec);
            [DllImport(DLLName)]
            public static extern short _mnet_m204_get_jogio_status(ushort RingNo, ushort SlaveIP, ushort AxisNo, ref ushort Status);
            // Latch
            [DllImport(DLLName)]
            public static extern short _mnet_m204_get_latch_data(ushort RingNo, ushort SlaveIP, ushort AxisNo, short LatchNo, ref int Pos);
            //
            // Pre-registers
            [DllImport(DLLName)]
            public static extern short _mnet_m204_check_continuous_buffer(ushort RingNo, ushort SlaveIP, ushort AxisNo, ref ushort IsFull);
            //
            [DllImport("kernel32")]
            private static extern long WritePrivateProfileString(string section, string key, string val, string filePath);
            [DllImport("kernel32")]
            private static extern int GetPrivateProfileString(string section, string key, string def, StringBuilder retVal, int size, string filePath);

            public static short get_file_to_initial(ushort RingNo, ushort IP, string FilePath)
            {
                string[] param = new string[] {
                "HOME_MODE",            "ORG_LOGIC",            "EZ_LOGIC",            "EZ_COUNT",            "ERC_OUT",
                 "EL_LOGIC",            "EL_MODE",              "ALM_LOGIC",           "ALM_MODE",            "INP_LOGIC",
               "INP_ENABLE",            "ERC_LOGIC",            "ERC_ACTTIME",         "SD_ENABLE",           "SD_LOGIC",
                  "SD_MODE",            "SD_LATCH",             "LTC_LOGIC",           "PLS_OUT_MODE",        "PLS_IN_SRC",
              "PLS_IN_MODE",            "PLS_IN_DIR",           "ABS_REF"  ,           "MOVE_MODE",           "STOP_MODE",
                 "VEL_PROF",            "DIST",                 "STR_VEL",             "MAX_VEL",             "Tacc",
                    "Tdec"};
                short[,] s_param = new short[4, param.Length];
                //Param[] AxisParam = new Param[4];
                StringBuilder retVal = new StringBuilder(255);  //回傳所要接收的值 
                string Section = "AxisNo";
                //string Key = "";
                string Defaut = "null";      //如果沒有 Section , Key 兩個參數值，則將此值賦給變量 
                int Size = 255;              //設定回傳 Siez  
                double[,] d_param = new double[4, 2];
                int strref = 0;
                #region Get parameter
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < param.Length; j++)
                    {
                        strref = GetPrivateProfileString(Section + string.Format(" {0}", i), param[j], Defaut, retVal, Size, FilePath);
                        if (retVal.ToString() == "null")
                            return -1;
                        if (j == 29 || j == 30)
                            d_param[i, j - 29] = double.Parse(retVal.ToString());
                        else
                            s_param[i, j] = short.Parse(retVal.ToString());
                        //Debug.WriteLine(string.Format("s_param[{0}, {1}]={2}", i, j, s_param[i, j]));
                    }
                }
                #endregion
                short ret = 0;
                for (ushort AxisNo = 0; AxisNo < 4; AxisNo++)
                {
                    ret += (short)M204._mnet_m204_set_pls_iptmode(RingNo, IP, AxisNo, (ushort)s_param[AxisNo, 20], (ushort)s_param[AxisNo, 21]);
                    ret += (short)M204._mnet_m204_set_pls_outmode(RingNo, IP, AxisNo, (ushort)s_param[AxisNo, 18]);
                    ret += (short)M204._mnet_m204_set_feedback_src(RingNo, IP, AxisNo, (ushort)s_param[AxisNo, 19]);
                    ret += (short)M204._mnet_m204_set_erc(RingNo, IP, AxisNo, (ushort)s_param[AxisNo, 11], (ushort)s_param[AxisNo, 12], (ushort)3);
                    ret += (short)M204._mnet_m204_set_sd(RingNo, IP, AxisNo, s_param[AxisNo, 13], s_param[AxisNo, 14], s_param[AxisNo, 16], s_param[AxisNo, 15]);
                    ret += (short)M204._mnet_m204_set_alm(RingNo, IP, AxisNo, (ushort)s_param[AxisNo, 7], (ushort)s_param[AxisNo, 8]);
                    ret += (short)M204._mnet_m204_set_ltc_logic(RingNo, IP, AxisNo, (ushort)s_param[AxisNo, 17]);
                    ret += (short)M204._mnet_m204_set_home_config(RingNo, IP, AxisNo, (ushort)s_param[AxisNo, 0], (ushort)s_param[AxisNo, 1], (ushort)s_param[AxisNo, 2], (ushort)s_param[AxisNo, 3], (ushort)s_param[AxisNo, 4]);
                    ret += (short)M204._mnet_m204_set_abs_reference(RingNo, IP, AxisNo, (short)s_param[AxisNo, 22]);

                    ret += (short)M204._mnet_m204_set_svon(RingNo, IP, AxisNo, 0);
                    ret += (short)M204._mnet_m204_set_inp(RingNo, IP, AxisNo, (ushort)s_param[AxisNo, 10], (ushort)s_param[AxisNo, 9]);
                    ret += (short)M204._mnet_m204_set_el(RingNo, IP, AxisNo, s_param[AxisNo, 6], s_param[AxisNo, 5]);

                    ret += (short)M204._mnet_m204_set_command(RingNo, IP, AxisNo, 0);
                    ret += (short)M204._mnet_m204_set_position(RingNo, IP, AxisNo, 0);
                    ret += (short)M204._mnet_m204_reset_error_counter(RingNo, IP, AxisNo);
                }
                return ret;
            }
        }
    }
}