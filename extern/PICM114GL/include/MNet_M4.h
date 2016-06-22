#ifndef __MNET_M4_H__
#define __MNET_M4_H__

#include "Type_def.h"


#ifdef __cplusplus
extern "C" {
#endif

//
// Initial
I16 PASCAL _mnet_m4_initial( U16 RingNo, U16 SlaveIP );
//
// Pulse I/O Configuration
I16 PASCAL _mnet_m4_set_pls_outmode( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 pls_outmode );
I16 PASCAL _mnet_m4_set_pls_iptmode( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 pls_iptmode, U16 pls_iptdir );
I16 PASCAL _mnet_m4_set_feedback_src( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 FbkSrc );
//
// Interface I/O Configuration
I16 PASCAL _mnet_m4_set_alm( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 alm_logic, U16 alm_mode );
I16 PASCAL _mnet_m4_set_inp( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 inp_enable, U16 inp_logic );
I16 PASCAL _mnet_m4_set_erc( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 erc_logic, U16 erc_on_time, U16 erc_off_time );
I16 PASCAL _mnet_m4_set_erc_on( U16 RingNo, U16 SlaveIP, U16 AxisNo, I16 on_off );
I16 PASCAL _mnet_m4_set_svon( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 on_off );
I16 PASCAL _mnet_m4_set_ralm( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 on_off );
I16 PASCAL _mnet_m4_set_sd( U16 RingNo, U16 SlaveIP, U16 AxisNo, I16 sd_enable, I16 sd_logic, I16 sd_latch, I16 sd_mode );
I16 PASCAL _mnet_m4_set_ell( U16 RingNo, U16 SlaveIP, U16 AxisNo, I16 ell_logic );
I16 PASCAL _mnet_m4_set_mechanical_input_filter( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 on_off, U16 FilterLength );
// I/O Status
I16 PASCAL _mnet_m4_get_io_status( U16 RingNo, U16 SlaveIP, U16 AxisNo, U32 *IO_status );
//
// Velocity Control
I16 PASCAL _mnet_m4_v_move( U16 RingNo, U16 SlaveIP, U16 AxisNo, U8 Dir );
I16 PASCAL _mnet_m4_fix_speed_range( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 MaxVel );
I16 PASCAL _mnet_m4_unfix_speed_range( U16 RingNo, U16 SlaveIP, U16 AxisNo );
//I16 PASCAL _mnet_m4_v_change( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 NewVel, F64 Time );
//
// Position Control
I16 PASCAL _mnet_m4_set_tmove_speed( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m4_set_smove_speed( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
I16 PASCAL _mnet_m4_start_r_move( U16 RingNo, U16 SlaveIP, U16 AxisNo, I32 Distance );
I16 PASCAL _mnet_m4_start_a_move( U16 RingNo, U16 SlaveIP, U16 AxisNo, I32 Pos );
//
I16 PASCAL _mnet_m4_tr_move_xy( U16 RingNo, U16 SlaveIP, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m4_ta_move_xy( U16 RingNo, U16 SlaveIP, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m4_sr_move_xy( U16 RingNo, U16 SlaveIP, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
I16 PASCAL _mnet_m4_sa_move_xy( U16 RingNo, U16 SlaveIP, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
I16 PASCAL _mnet_m4_tr_move_zu( U16 RingNo, U16 SlaveIP, F64 DistZ, F64 DistU, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m4_ta_move_zu( U16 RingNo, U16 SlaveIP, F64 PosZ, F64 PosU, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m4_sr_move_zu( U16 RingNo, U16 SlaveIP, F64 DistZ, F64 DistU, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
I16 PASCAL _mnet_m4_sa_move_zu( U16 RingNo, U16 SlaveIP, F64 PosZ, F64 PosU, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
//
I16 PASCAL _mnet_m4_start_tr_line2( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m4_start_ta_line2( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m4_start_sr_line2( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
I16 PASCAL _mnet_m4_start_sa_line2( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
//
I16 PASCAL _mnet_m4_start_tr_line3( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 DistX, F64 DistY, F64 DistZ, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m4_start_ta_line3( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 PosX, F64 PosY, F64 PosZ, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m4_start_sr_line3( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 DistX, F64 DistY, F64 DistZ, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
I16 PASCAL _mnet_m4_start_sa_line3( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 PosX, F64 PosY, F64 PosZ, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec , F64 SVacc, F64 SVdec );
//
I16 PASCAL _mnet_m4_start_tr_line4( U16 RingNo, U16 SlaveIP, F64 DistX, F64 DistY, F64 DistZ, F64 DistU, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m4_start_ta_line4( U16 RingNo, U16 SlaveIP, F64 PosX, F64 PosY, F64 PosZ, F64 PosU, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m4_start_sr_line4( U16 RingNo, U16 SlaveIP, F64 DistX, F64 DistY, F64 DistZ, F64 DistU, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
I16 PASCAL _mnet_m4_start_sa_line4( U16 RingNo, U16 SlaveIP, F64 PosX, F64 PosY, F64 PosZ, F64 PosU, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
//
// Stop
I16 PASCAL _mnet_m4_sd_stop( U16 RingNo, U16 SlaveIP, U16 AxisNo );
I16 PASCAL _mnet_m4_emg_stop( U16 RingNo, U16 SlaveIP, U16 AxisNo );
//
// Motion Status
I16 PASCAL _mnet_m4_motion_done( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 *MoSt );
//
// Home
I16 PASCAL _mnet_m4_set_home_config( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 home_mode, U16 org_logic, U16 ez_logic, U16 ez_count, U16 erc_out );
I16 PASCAL _mnet_m4_start_home_move( U16 RingNo, U16 SlaveIP, U16 AxisNo, U8 Dir );
//
// Counter Operating
I16 PASCAL _mnet_m4_get_command( U16 RingNo, U16 SlaveIP, U16 AxisNo, I32 *Cmd );
I16 PASCAL _mnet_m4_set_command( U16 RingNo, U16 SlaveIP, U16 AxisNo, I32 Cmd );
I16 PASCAL _mnet_m4_reset_command( U16 RingNo, U16 SlaveIP, U16 AxisNo );
I16 PASCAL _mnet_m4_get_position( U16 RingNo, U16 SlaveIP, U16 AxisNo, I32 *Pos );
I16 PASCAL _mnet_m4_set_position( U16 RingNo, U16 SlaveIP, U16 AxisNo, I32 Pos );
I16 PASCAL _mnet_m4_reset_position( U16 RingNo, U16 SlaveIP, U16 AxisNo );
I16 PASCAL _mnet_m4_get_current_speed( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 *speed );
//
// Position Compare and Latch
I16 PASCAL _mnet_m4_set_ltc_logic( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 ltc_logic );
I16 PASCAL _mnet_m4_get_latch_data( U16 RingNo, U16 SlaveIP, U16 AxisNo, I16 LatchNo, F64 *Pos );
I16 PASCAL _mnet_m4_set_comparator_data( U16 RingNo, U16 SlaveIP, U16 AxisNo, I16 CompNo, F64 Pos );
I16 PASCAL _mnet_m4_set_comparator_mode( U16 RingNo, U16 SlaveIP, U16 AxisNo, I16 CompNo, I16 CmpMethod );
I16 PASCAL _mnet_m4_set_trigger_comparator_mode( U16 RingNo, U16 SlaveIP, U16 AxisNo, I16 CmpMethod );
I16 PASCAL _mnet_m4_set_trigger_comparator_data( U16 RingNo, U16 SlaveIP, U16 AxisNo,  F64 Data );
I16 PASCAL _mnet_m4_set_trigger_output_time( U16 RingNo, U16 SlaveIP, U16 Time );
I16 PASCAL _mnet_m4_set_auto_trigger( U16 RingNo, U16 SlaveIP, U16 AxisNo, U16 CmpMethod, U16 Interval, U16 Logic, U16 on_off );
//
// MOF
I16 PASCAL _mnet_m4_set_pulser_iptmode( U16 RingNo, U16 SlaveIP, U16 AxisNo, I16 InputMode, I16 Inverse );
I16 PASCAL _mnet_m4_set_mof_config( U16 RingNo, U16 SlaveIP, I16 MOF_mode );
I16 PASCAL _mnet_m4_disable_mof( U16 RingNo, U16 SlaveIP );
I16 PASCAL _mnet_m4_get_mof_status( U16 RingNo, U16 SlaveIP, U16 *MOF_sts );
I16 PASCAL _mnet_m4_manual_mpg( U16 RingNo, U16 SlaveIP, I16 MPG_axis_sel );
I16 PASCAL _mnet_m4_set_mof_jog_velocity( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, I16 feedrate );
I16 PASCAL _mnet_m4_set_mof_step_distance( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 step_dist );
I16 PASCAL _mnet_m4_set_mof_step_velocity( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, I16 feedrate );
I16 PASCAL _mnet_m4_set_mof_mpg_velocity( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
//
// Synchronous Move - STA
I16 PASCAL _mnet_m4_sync_r_move( U16 RingNo, U16 SlaveIP, U16 AxisNo, I32 Distance );
I16 PASCAL _mnet_m4_sync_a_move( U16 RingNo, U16 SlaveIP, U16 AxisNo, I32 Pos ); 
//
// Synchronous Move - internal
I16 PASCAL _mnet_m4_set_triggered_r_move( U16 RingNo, U16 SlaveIP, U16 AxisNo, I32 Distance, U16 SrcAxisNo, U8 timing );
I16 PASCAL _mnet_m4_set_triggered_a_move( U16 RingNo, U16 SlaveIP, U16 AxisNo, I32 Pos, U16 SrcAxisNo, U8 timing );
I16 PASCAL _mnet_m4_set_triggered_tr_line2( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, U16 SrcAxisNo, U8 timing );
I16 PASCAL _mnet_m4_set_triggered_ta_line2( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, U16 SrcAxisNo, U8 timing );
I16 PASCAL _mnet_m4_set_triggered_sr_line2( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec, U16 SrcAxisNo, U8 timing );
I16 PASCAL _mnet_m4_set_triggered_sa_line2( U16 RingNo, U16 SlaveIP, I16 *AxisArray, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec, U16 SrcAxisNo, U8 timing );
//
// Others
I16 PASCAL _mnet_m4_set_continuous_move( U16 RingNo, U16 SlaveIP, U16 AxisNo, I16 Enable );
I16 PASCAL _mnet_m4_set_velocity_limit( U16 RingNo, U16 SlaveIP, U16 AxisNo, F64 MaxVel );

#ifdef __cplusplus
}
#endif



#endif //__MNET_M4_H__
