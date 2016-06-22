#ifndef __MNET_M204_H__
#define __MNET_M204_H__

#include "Type_def.h"


#ifdef __cplusplus
extern "C" {
#endif

//
// Initial
I16 PASCAL _mnet_m204_initial( U16 RingNo, U16 SlaveIP );
//
// Pulse I/O Configuration
I16 PASCAL _mnet_m204_set_pls_outmode( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 pls_outmode );
I16 PASCAL _mnet_m204_set_pls_iptmode( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 pls_iptmode, U16 pls_iptdir );
I16 PASCAL _mnet_m204_set_feedback_src( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 FbkSrc );
I16 PASCAL _mnet_m204_set_abs_reference(U16 RingNo, U16 SlaveIP, U16 AxisNo, I16 Ref);
//
// Interface I/O Configuration
I16 PASCAL _mnet_m204_set_alm( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 alm_logic, U16 alm_mode );
I16 PASCAL _mnet_m204_set_inp( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 inp_enable, U16 inp_logic );
I16 PASCAL _mnet_m204_set_erc( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 erc_logic, U16 erc_on_time, U16 erc_off_time );
I16 PASCAL _mnet_m204_set_erc_on( U16 RingNo, U16 SlaveIP, U16 AxisNo, I16 on_off );
I16 PASCAL _mnet_m204_set_sd( U16 RingNo, U16 SlaveIP, U16 AxisNo, I16 sd_enable, I16 sd_logic, I16 sd_latch, I16 sd_mode );
I16 PASCAL _mnet_m204_set_svon( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 on_off );
I16 PASCAL _mnet_m204_set_ralm( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 on_off );
I16 PASCAL _mnet_m204_set_ltc_logic( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 ltc_logic );
I16 PASCAL _mnet_m204_set_el( U16 RingNo, U16 SlaveIP, U16 AxisNo, I16 el_mode, I16 el_logic );
// Status
I16 PASCAL _mnet_m204_get_io_status( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 *io_sts );
I16 PASCAL _mnet_m204_motion_done( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 *McSts );
I16 PASCAL _mnet_m204_check_error( U16 RingNo, U16 SlaveIP, U16 AxisNo, U32* ErrorStatus );
//
// Velocity Control
I16 PASCAL _mnet_m204_tv_move( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc );
I16 PASCAL _mnet_m204_sv_move( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc, F64 SVacc );
I16 PASCAL _mnet_m204_v_change( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 NewVel, F64 Time );
I16 PASCAL _mnet_m204_cmp_v_change( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 Res_Dist, F64 OldVel, F64 NewVel, F64 Time );
I16 PASCAL _mnet_m204_fix_speed_range( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 MaxVel );
I16 PASCAL _mnet_m204_unfix_speed_range( U16 RingNo, U16 SlaveIP, U16 AxisNo );
//
// Position Control
I16 PASCAL _mnet_m204_start_tr_move( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 Dist, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m204_start_ta_move( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 Pos, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m204_start_sr_move( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 Dist, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
I16 PASCAL _mnet_m204_start_sa_move( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 Pos, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
//
I16 PASCAL _mnet_m204_start_tr_line2( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m204_start_ta_line2( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m204_start_sr_line2( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
I16 PASCAL _mnet_m204_start_sa_line2( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
//
I16 PASCAL _mnet_m204_start_tr_line3( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 DistX, F64 DistY, F64 DistZ, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m204_start_ta_line3( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 PosX, F64 PosY, F64 PosZ, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m204_start_sr_line3( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 DistX, F64 DistY, F64 DistZ, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
I16 PASCAL _mnet_m204_start_sa_line3( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 PosX, F64 PosY, F64 PosZ, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
//
I16 PASCAL _mnet_m204_start_tr_line4( U16 RingNo, U16 SlaveIP, F64 DistX, F64 DistY, F64 DistZ, F64 DistU, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m204_start_ta_line4( U16 RingNo, U16 SlaveIP, F64 PosX, F64 PosY, F64 PosZ, F64 PosU, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m204_start_sr_line4( U16 RingNo, U16 SlaveIP, F64 DistX, F64 DistY, F64 DistZ, F64 DistU, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
I16 PASCAL _mnet_m204_start_sa_line4( U16 RingNo, U16 SlaveIP, F64 PosX, F64 PosY, F64 PosZ, F64 PosU, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
//
I16 PASCAL _mnet_m204_start_tr_arc2( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m204_start_ta_arc2( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m204_start_sr_arc2( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
I16 PASCAL _mnet_m204_start_sa_arc2( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
//
I16 PASCAL _mnet_m204_start_tr_arc_xyz( U16 RingNo, U16 SlaveIP, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, F64 DistZ, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m204_start_ta_arc_xyz( U16 RingNo, U16 SlaveIP, F64 Cx, F64 Cy, F64 Ex, F64 Ey, F64 PosZ, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m204_start_sr_arc_xyz( U16 RingNo, U16 SlaveIP, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, F64 DistZ, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
I16 PASCAL _mnet_m204_start_sa_arc_xyz( U16 RingNo, U16 SlaveIP, F64 Cx, F64 Cy, F64 Ex, F64 Ey, F64 PosZ, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
//
I16 PASCAL _mnet_m204_tr_move_after_axis(U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 LeadingAxes, F64 Dist, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _mnet_m204_ta_move_after_axis(U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 LeadingAxes, F64 Pos, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _mnet_m204_sr_move_after_axis(U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 LeadingAxes, F64 Dist, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 PASCAL _mnet_m204_sa_move_after_axis(U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 LeadingAxes, F64 Pos, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
//
// Stop
I16 PASCAL _mnet_m204_sd_stop( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 Tdec );
I16 PASCAL _mnet_m204_emg_stop( U16 RingNo, U16 SlaveIP, U16 AxisNo );
//
// Home
I16 PASCAL _mnet_m204_set_home_config( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 home_mode, U16 org_logic, U16 ez_logic, U16 ez_count, U16 erc_out );
I16 PASCAL _mnet_m204_start_home_move( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc );
I16 PASCAL _mnet_m204_escape_home( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc );
I16 PASCAL _mnet_m204_home_search( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc, F64 ORGOffset );
//
// Counter Operating
I16 PASCAL _mnet_m204_get_command( U16 RingNo, U16 SlaveIP, U16 AxisNo, I32 *cmd );
I16 PASCAL _mnet_m204_get_position( U16 RingNo, U16 SlaveIP, U16 AxisNo, I32 *pos );
I16 PASCAL _mnet_m204_get_error_counter( U16 RingNo, U16 SlaveIP, U16 AxisNo, I16 *error );
I16 PASCAL _mnet_m204_set_command( U16 RingNo, U16 SlaveIP, U16 AxisNo, I32 cmd );
I16 PASCAL _mnet_m204_set_position( U16 RingNo, U16 SlaveIP, U16 AxisNo, I32 pos );
I16 PASCAL _mnet_m204_reset_command( U16 RingNo, U16 SlaveIP, U16 AxisNo );
I16 PASCAL _mnet_m204_reset_position( U16 RingNo, U16 SlaveIP, U16 AxisNo );
I16 PASCAL _mnet_m204_reset_error_counter( U16 RingNo, U16 SlaveIP, U16 AxisNo );
I16 PASCAL _mnet_m204_get_target_pos( U16 RingNo, U16 SlaveIP, U16 AxisNo, I32 *Pos );
I16 PASCAL _mnet_m204_set_target_pos( U16 RingNo, U16 SlaveIP, U16 AxisNo, I32 Pos );
I16 PASCAL _mnet_m204_set_move_ratio(U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 Ratio);
I16 PASCAL _mnet_m204_set_ring_count(U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 Src, F64 Data);
I16 PASCAL _mnet_m204_enable_ring_count(U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 Src, U16 OnOff);
I16 PASCAL _mnet_m204_get_rest_command( U16 RingNo, U16 SlaveIP, U16 AxisNo, I32 *rest_command );
I16 PASCAL _mnet_m204_get_current_speed( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 *speed );
//
// Position Override
I16 PASCAL _mnet_m204_p_change( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 NewPos );
I16 PASCAL _mnet_m204_d_change( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 NewDist );
//
// General Compare
I16 PASCAL _mnet_m204_set_general_comparator(U16 RingNo, U16 SlaveIP, U16 AxisNo, I16 CmpSrc, I16 CmpMethod, I16 CmpAction, F64 Data);
I16 PASCAL _mnet_m204_set_trigger_comparator(U16 RingNo, U16 SlaveIP, U16 AxisNo, I16 CmpSrc, I16 CmpMethod, F64 Data);
I16 PASCAL _mnet_m204_set_trigger_type(U16 RingNo, U16 SlaveIP, U16 AxisNo, I16 TriggerType);
I16 PASCAL _mnet_m204_set_soft_limit(U16 RingNo, U16 SlaveIP, U16 AxisNo, I32 PLimit, I32 NLimit);
I16 PASCAL _mnet_m204_enable_soft_limit(U16 RingNo, U16 SlaveIP, U16 AxisNo, I16 Action);
I16 PASCAL _mnet_m204_disable_soft_limit(U16 RingNo, U16 SlaveIP, U16 AxisNo);
I16 PASCAL _mnet_m204_check_compare_data(U16 RingNo, U16 SlaveIP, U16 AxisNo, I16 CmpType, F64 *Pos);
//
// Auto Compare
I16 PASCAL _mnet_m204_get_auto_compare_encoder(U16 RingNo, U16 SlaveIP, U16 AxisNo, I32 *EncPos);
I16 PASCAL _mnet_m204_set_auto_compare_encoder(U16 RingNo, U16 SlaveIP, U16 AxisNo, I32 EncPos);
I16 PASCAL _mnet_m204_get_auto_compare_count(U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 *Count);
I16 PASCAL _mnet_m204_get_auto_compare_status(U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 *OnOff);
I16 PASCAL _mnet_m204_set_auto_compare_trigger(U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 Level, U16 Width);
I16 PASCAL _mnet_m204_set_auto_compare_function(U16 RingNo, U16 SlaveIP, U16 AxisNo, U8 Dir, I32 StrPos, I32 Interval, U16 TrgCnt);
I16 PASCAL _mnet_m204_set_auto_compare_table(U16 RingNo, U16 SlaveIP, U16 AxisNo, U8 Dir, U16 Size, I32 *Table);
I16 PASCAL _mnet_m204_start_auto_compare(U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 OnOff);
I16 PASCAL _mnet_m204_force_trigger_output(U16 RingNo, U16 SlaveIP, U16 AxisNo);
//
// Jog
enum JogStep { Jog_Step_1 = 1, Jog_Step_10 = 10, Jog_Step_100 = 100 };
I16 PASCAL _mnet_m204_jog_switch_continue(U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 SwitchLogic, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _mnet_m204_jog_switch_step(U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 SwitchLogic, F64 Dist, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _mnet_m204_jog_pulser_step(U16 RingNo, U16 SlaveIP, U16 AxisNo, U8 Dir, U8 Step, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 PASCAL _mnet_m204_get_jogio_status(U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 *Status);
//
// Latch
I16 PASCAL _mnet_m204_get_latch_data(U16 RingNo, U16 SlaveIP, U16 AxisNo, I16 LatchNo, I32 *Pos);
//
// Pre-registers
I16 PASCAL _mnet_m204_check_continuous_buffer(U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 *IsFull);
//
#ifdef __cplusplus
}
#endif


#endif //__MNET_M204_H__
