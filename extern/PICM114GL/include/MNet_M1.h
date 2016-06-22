#ifndef __MNET_M1_H__
#define __MNET_M1_H__

#include "Type_def.h"


#ifdef __cplusplus
extern "C" {
#endif
//
// Initial
I16 PASCAL _mnet_m1_initial( U16 RingNo, U16 SlaveIP );
//
// Pulse I/O Configuration
I16 PASCAL _mnet_m1_set_pls_outmode( U16 RingNo, U16 SlaveIP, U16 pls_outmode );
I16 PASCAL _mnet_m1_set_pls_iptmode( U16 RingNo, U16 SlaveIP, U16 pls_iptmode, U16 pls_iptdir );
I16 PASCAL _mnet_m1_set_feedback_src( U16 RingNo, U16 SlaveIP, U16 FbkSrc );
I16 PASCAL _mnet_m1_set_abs_reference(U16 RingNo, U16 SlaveIP, U16 Ref);
I16 PASCAL _mnet_m1_set_move_ratio( U16 RingNo, U16 SlaveIP, F64 move_ratio );
//
// Interface I/O Configuration
I16 PASCAL _mnet_m1_set_alm( U16 RingNo, U16 SlaveIP, U16 alm_logic, U16 alm_mode );
I16 PASCAL _mnet_m1_set_inp( U16 RingNo, U16 SlaveIP, U16 inp_enable, U16 inp_logic );
I16 PASCAL _mnet_m1_set_erc( U16 RingNo, U16 SlaveIP, U16 erc_logic, U16 erc_on_time, U16 erc_off_time );
I16 PASCAL _mnet_m1_set_erc_on( U16 RingNo, U16 SlaveIP, I16 on_off );
I16 PASCAL _mnet_m1_set_svon( U16 RingNo, U16 SlaveIP, U16 on_off );
I16 PASCAL _mnet_m1_set_ralm( U16 RingNo, U16 SlaveIP, U16 on_off );
I16 PASCAL _mnet_m1_set_el_mode(U16 RingNo, U16 SlaveIP, U16 el_mode);
I16 PASCAL _mnet_m1_set_sd( U16 RingNo, U16 SlaveIP, I16 sd_enable, I16 sd_logic, I16 sd_latch, I16 sd_mode );
I16 PASCAL _mnet_m1_set_ltc_logic( U16 RingNo, U16 SlaveIP, U16 ltc_logic );
I16 PASCAL _mnet_m1_set_pcs( U16 RingNo, U16 SlaveIP, U16 pcs_logic );
I16 PASCAL _mnet_m1_set_clr( U16 RingNo, U16 SlaveIP, U16 clr_logic );
I16 PASCAL _mnet_m1_dio_output( U16 RingNo, U16 SlaveIP, U16 DoNo, U16 on_off );
I16 PASCAL _mnet_m1_dio_input( U16 RingNo, U16 SlaveIP, U16 DiNo );
I16 PASCAL _mnet_m1_get_dio( U16 RingNo, U16 SlaveIP, U8 *Val );
I16 PASCAL _mnet_m1_set_mechanical_input_filter( U16 RingNo, U16 SlaveIP, U16 on_off );
// I/O Status
I16 PASCAL _mnet_m1_get_io_status( U16 RingNo, U16 SlaveIP, U32 *IO_status );
//
// Velocity Control
I16 PASCAL _mnet_m1_v_move( U16 RingNo, U16 SlaveIP, U8 Dir );
I16 PASCAL _mnet_m1_v_change( U16 RingNo, U16 SlaveIP, F64 NewVel, F64 Time );
I16 PASCAL _mnet_m1_fix_speed_range( U16 RingNo, U16 SlaveIP, F64 MaxVel );
I16 PASCAL _mnet_m1_unfix_speed_range( U16 RingNo, U16 SlaveIP );
//
// Position Control
I16 PASCAL _mnet_m1_set_tmove_speed( U16 RingNo, U16 SlaveIP, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m1_set_smove_speed( U16 RingNo, U16 SlaveIP, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
I16 PASCAL _mnet_m1_start_r_move( U16 RingNo, U16 SlaveIP, I32 Distance );
I16 PASCAL _mnet_m1_start_a_move( U16 RingNo, U16 SlaveIP, I32 Pos );
//
// Stop
I16 PASCAL _mnet_m1_sd_stop( U16 RingNo, U16 SlaveIP );
I16 PASCAL _mnet_m1_emg_stop( U16 RingNo, U16 SlaveIP );
//
// Motion Status
I16 PASCAL _mnet_m1_motion_done( U16 RingNo, U16 SlaveIP, U16 *MoSt );
//
// Home
I16 PASCAL _mnet_m1_start_home_move( U16 RingNo, U16 SlaveIP, U8 Dir );
I16 PASCAL _mnet_m1_set_home_config( U16 RingNo, U16 SlaveIP, U16 home_mode, U16 org_logic, U16 ez_logic, U16 ez_count, U16 erc_out );
I16 PASCAL _mnet_m1_start_home_search( U16 RingNo, U16 SlaveIP, U8 Dir, F64 ORGOffset );
I16 PASCAL _mnet_m1_start_home_escape( U16 RingNo, U16 SlaveIP, U8 Dir );
I16 PASCAL _mnet_m1_start_search_ez( U16 RingNo, U16 SlaveIP, U8 Dir, U16 EzCount );
//
// Counter Operating
I16 PASCAL _mnet_m1_set_command( U16 RingNo, U16 SlaveIP, I32 Cmd );
I16 PASCAL _mnet_m1_get_command( U16 RingNo, U16 SlaveIP, I32 *Cmd );
I16 PASCAL _mnet_m1_reset_command( U16 RingNo, U16 SlaveIP );
I16 PASCAL _mnet_m1_get_position( U16 RingNo, U16 SlaveIP, I32 *Pos );
I16 PASCAL _mnet_m1_set_position( U16 RingNo, U16 SlaveIP, I32 Pos );
I16 PASCAL _mnet_m1_reset_position( U16 RingNo, U16 SlaveIP );
I16 PASCAL _mnet_m1_set_error_counter( U16 RingNo, U16 SlaveIP, I32 ErrCnt );
I16 PASCAL _mnet_m1_get_error_counter( U16 RingNo, U16 SlaveIP, I32 *ErrCnt );
I16 PASCAL _mnet_m1_reset_error_counter( U16 RingNo, U16 SlaveIP );
I16 PASCAL _mnet_m1_get_current_speed( U16 RingNo, U16 SlaveIP, F64 *speed );
//
// Position Compare and Latch
I16 PASCAL _mnet_m1_set_comparator_mode( U16 RingNo, U16 SlaveIP, I16 CompNo, I16 CmpSrc, I16 CmpMethod, I16 CmpAction );
I16 PASCAL _mnet_m1_set_comparator_data( U16 RingNo, U16 SlaveIP, I16 CompNo, F64 Pos );
I16 PASCAL _mnet_m1_set_trigger_comparator( U16 RingNo, U16 SlaveIP, U16 CmpSrc , U16 CmpMethod );
I16 PASCAL _mnet_m1_set_trigger_comparator_data( U16 RingNo, U16 SlaveIP,  F64 Data );
I16 PASCAL _mnet_m1_get_comparator_data( U16 RingNo, U16 SlaveIP, I16 CompNo, F64 *Pos );
I16 PASCAL _mnet_m1_set_soft_limit( U16 RingNo, U16 SlaveIP, I32 PLimit, I32 MLimit );
I16 PASCAL _mnet_m1_enable_soft_limit( U16 RingNo, U16 SlaveIP, U8 Action );
I16 PASCAL _mnet_m1_disable_soft_limit( U16 RingNo, U16 SlaveIP );
I16 PASCAL _mnet_m1_get_latch_data( U16 RingNo, U16 SlaveIP, I16 LatchNo, F64 *Pos );
I16 PASCAL _mnet_m1_set_auto_trigger( U16 RingNo, U16 SlaveIP, U16 CmpSrc, U16 CmpMethod, U16 Interval, U16 on_off );
//
// Destination Change
I16 PASCAL _mnet_m1_start_p_change( U16 RingNo, U16 SlaveIP, I32 NewPos );
I16 PASCAL _mnet_m1_start_d_change( U16 RingNo, U16 SlaveIP, I32 NewDist );
//
// Backlash Correction
I16 PASCAL _mnet_m1_set_backlash( U16 RingNo, U16 SlaveIP, U16 Value, U16 Enable, U16 CntSrc );
//
// Synchronize
I16 PASCAL _mnet_m1_set_sta_trigger( U16 RingNo, U16 SlaveIP,  U16 TriType );
I16 PASCAL _mnet_m1_sync_v_move( U16 RingNo, U16 SlaveIP, U8 Dir );
I16 PASCAL _mnet_m1_start_sync_r_move( U16 RingNo, U16 SlaveIP, I32 Distance );
I16 PASCAL _mnet_m1_start_sync_a_move( U16 RingNo, U16 SlaveIP, I32 Pos );
I16 PASCAL _mnet_m1_start_sync_tr_line( U16 RingNo, U16* SlaveIP, I32 DistX, I32 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m1_start_sync_ta_line( U16 RingNo, U16* SlaveIP, I32 PosX, I32 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec );
I16 PASCAL _mnet_m1_start_sync_sr_line( U16 RingNo, U16* SlaveIP, I32 DistX, I32 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
I16 PASCAL _mnet_m1_start_sync_sa_line( U16 RingNo, U16* SlaveIP, I32 PosX, I32 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec );
I16 PASCAL _mnet_m1_sync_sd_stop( U16 RingNo, U16 SlaveIP );
I16 PASCAL _mnet_m1_sync_imd_stop( U16 RingNo, U16 SlaveIP );
//
// Misc
I16 PASCAL _mnet_m1_get_speed_range( U16 RingNo, U16 SlaveIP, F64 *MinVel, F64 *MaxVel );
//
#ifdef __cplusplus
}
#endif


#endif //__MNET_M1_H__
