#include "layout_define.h"
// typedef enum
// {
// 	always_record_scr_act_obj_id_head_cont,
// 	always_record_scr_act_obj_id_loop_obj,
// 	always_record_scr_act_obj_id_record_obj,
// } always_record_scr_act_obj_id;
// typedef enum
// {
// 	always_record_head_cont_obj_id_cancel_obj,
// 	always_record_head_cont_obj_id_channel_label,
// 	always_record_head_cont_obj_id_time_label,
// 	always_record_head_cont_obj_id_motion_img,
// 	always_record_head_cont_obj_id_auto_img,
// 	always_record_head_cont_obj_id_sd_img,
// 	always_record_head_cont_obj_id_timeout_label
// } always_record_head_cont_obj_id;

// /************************************************************
// ** 函数说明: 多通道循环录像还是单通道
// ** 作者: xiaoxiao
// ** 日期: 2023-05-26 08:53:53
// ** 参数说明: 
// ** 注意事项: 
// ************************************************************/
// static bool always_record_loop = true;
// static bool is_always_record_video_ing = false;

// static int always_record_time = 10;//记录时长

// static lv_timer_t *always_record_task = NULL;//刷新任务
// /************************************************************
// ** 函数说明: 获取通道
// ** 作者: xiaoxiao
// ** 日期: 2023-05-26 08:00:46
// ** 参数说明: 
// ** 注意事项: 
// ************************************************************/
// static int always_record_channel_get(void)
// {

// 	if ((monitor_valid_channel_check(MON_CH_DOOR1) == false) && (monitor_valid_channel_check(MON_CH_DOOR2) == false))
// 	{
// 		for(int i = 0; i < 8; i++)
//         {
//             if(monitor_valid_channel_check(MON_CH_CCTV1 + i))
//             {
//                 break;;
//             }
//             if( i == 7)
//             {
//                 return MON_CH_NONE;
//             } 
//         }
// 	}
// 	int ch = monitor_channel_get();
// 	if (always_record_loop == false)
// 	{
// 		return ch;
// 	}
// 	if (ch == MON_CH_NONE)
// 	{
// 		ch = MON_CH_DOOR1;
// 		if (monitor_valid_channel_check(ch) == true)
// 		{
// 			return ch;
// 		}
// 	}
// 	int find = 0;
// find_start:
// 	if (ch == MON_CH_DOOR1)
// 	{
// 		ch = MON_CH_DOOR2;
// 		if (monitor_valid_channel_check(ch) == true)
// 		{
// 			return ch;
// 		}
// 	}
// 	if (ch == MON_CH_DOOR2)
// 	{
// 		ch = MON_CH_CCTV1;
// 		if (monitor_valid_channel_check(ch) == true)
// 		{
// 			return ch;
// 		}
// 	}
//     for(int i = 0; i < 8; i++)
//     {
//         if ((ch == MON_CH_CCTV1 + i) && (ch != MON_CH_CCTV8))
//         {
//             ch = MON_CH_CCTV2 + i;
//             if (monitor_valid_channel_check(ch) == true)
//             {
//                 return ch;
//             }
//         }
//     }
// 	if (ch == MON_CH_CCTV8)
// 	{
// 		ch = MON_CH_DOOR1;
// 		if (monitor_valid_channel_check(ch) == true)
// 		{
// 			return ch;
// 		}
// 	}
// 	find++;
// 	if (find == 2)
// 	{
// 		return MON_CH_NONE;
// 	}
// 	goto find_start;
// }

// static void monitor_obj_record_video_display(void)
// {

//         if (is_always_record_video_ing == true)
//         {
//                 lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_call_rec_ing.png"), LV_PART_MAIN);
//         }
//         else
//         {
//                 lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_call_rec.png"), LV_PART_MAIN);
//         }
// }

// /************************************************************
// ** 函数说明: 录像点击事件
// ** 作者: xiaoxiao
// ** 日期: 2023-05-26 09:39:18
// ** 参数说明: 
// ** 注意事项: 
// ************************************************************/
// static void always_record_record_btn_up(lv_obj_t *obj)
// {
//     if (is_always_record_video_ing == true)
//     {
//         record_video_stop();
//     }
//     else
//     {
//         record_video_start(true, REC_MODE_MANUAL);
//     }
// }

// static void layout_always_monitor_open(void)
// {
// 	int ch = always_record_channel_get();
// 	if (ch != MON_CH_NONE)
// 	{
// 		monitor_channel_set(ch);
// 		monitor_open(true);
// 	}
// }
// /************************************************************
// ** 函数说明: 当前时间显示
// ** 作者: xiaoxiao
// ** 日期: 2023-05-26 09:29:07
// ** 参数说明: 
// ** 注意事项: 
// ************************************************************/
// static void always_record_time_label_display(void)
// {
// 	lv_obj_t *parent = lv_obj_get_child_form_id(lv_scr_act(), always_record_scr_act_obj_id_head_cont);
// 	lv_obj_t *obj = lv_obj_get_child_form_id(parent, always_record_head_cont_obj_id_time_label);
// 	if (obj == NULL)
// 	{
//         lv_common_text_create(parent, always_record_head_cont_obj_id_time_label, 182, 22, 240, 35,
//                     NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
//                     0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
//                     0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
//                     ":", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
// 	}
// 	static struct tm tm;
// 	user_time_read(&tm);
// 	lv_label_set_text_fmt(obj, "%04d-%02d-%02d %02d:%02d", tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min);
// }

// /************************************************************
// ** 函数说明: 超时时间显示
// ** 作者: xiaoxiao
// ** 日期: 2023-05-26 09:34:05
// ** 参数说明: 
// ** 注意事项: 
// ************************************************************/
// static void always_record_tiemout_label_display(void)
// {
// 	lv_obj_t *parent = lv_obj_get_child_form_id(lv_scr_act(), always_record_scr_act_obj_id_head_cont);
// 	lv_obj_t *obj = lv_obj_get_child_form_id(parent, always_record_head_cont_obj_id_timeout_label);
// 	if (obj == NULL)
// 	{
//         lv_common_text_create(parent, always_record_head_cont_obj_id_time_label, 8800, 21, 80, 35,
//                     NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
//                     0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
//                     0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
//                     ":", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
// 		static int timeout = 0;
// 		timeout = always_record_time;
// 		obj->user_data = &timeout;
// 	}
// 	int *ptimeout = (int *)obj->user_data;
// 	int timeout = *ptimeout;
// 	lv_label_set_text_fmt(obj, "%02d:%02d", timeout / 60, timeout % 60);

// 	if (timeout != 0)
// 	{
// 		(*ptimeout)--;
// 	}
// 	else
// 	{
// 		(*ptimeout) = always_record_time;
// 		layout_always_record_stop();
// 		usleep(500 * 1000);
// 		/* if (always_record_loop == true) */
// 		{
// 			monitor_close();
// 		}

// 		if (always_record_task == NULL)
// 		{
// 			always_record_task = lv_layout_task_create(layout_always_monitor_open_task, 3000, LV_TASK_PRIO_MID, NULL);
// 		}
// 	}
// }
// /***********************************************
//  ** 作者: leo.liu
//  ** 日期: 2023-2-2 13:42:25
//  ** 说明: 记录状态状态显示
//  ***********************************************/
// static void monitor_record_video_state_callback(bool record_ing)
// {
//     is_always_record_video_ing = record_ing;
//     always_record_record_btn_display();
// }
// /************************************************************
// ** 函数说明: 通道时间刷新
// ** 作者: xiaoxiao
// ** 日期: 2023-05-26 09:24:12
// ** 参数说明: 
// ** 注意事项: 
// ************************************************************/
// static void always_record_timeout_refresh_task(lv_timer_t *task)
// {
// 	always_record_time_label_display();
// 	always_record_tiemout_label_display();
// }
// static void layout_always_record_start(void)
// {

// 	if (video_record_status_get() == true)
// 	{
// 		record_video_stop();
// 	}
// 	else if (media_sdcard_insert_check() == false)
// 	{
//         if (is_always_snapshot_ing == false)
//         {
//             sat_linphone_calls_cmd_send();
//             if (record_jpeg_start(REC_MODE_ALWAYS) == true)
//             {
//                 lv_layout_task_create(layout_always_snap_task_wait_finish_task, 100, LV_TASK_PRIO_MID, NULL);
//             }
    
//         }

// 	}
// 	else
// 	{
// 		record_video_start(REC_MODE_ALWAYS);
// 	}
// 	always_record_record_btn_display();
// }
// /***
// **   日期:2022-06-20 16:38:19
// **   作者: leo.liu
// **   函数作用：创建任务等待录像
// **   参数说明:
// ***/
// static void layout_always_record_delay_task(lv_timer_t * pthime)
// {

// 	layout_always_record_start();
// 	lv_timer_del(pthime);
// 	always_record_task = NULL;
// }
static void sat_layout_enter(always_record)
{
    // always_record_loop = true;
    // monitor_channel_set(MON_CH_NONE);
    // layout_always_monitor_open();
    // lv_sat_timer_create(always_record_timeout_refresh_task, 1000 , NULL);
    // /*记录注册*/
    // record_state_callback_register(monitor_record_video_state_callback);
    // {
    //         lv_common_img_btn_create(sat_cur_layout_screen_get(), always_record_scr_act_obj_id_record_obj, 808, 24, 80, 81,
    //                             NULL, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
    //                             0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
    //                             0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
    //                             resource_ui_src_get("btn_call_rec.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_TOP_MID);

    //         always_record_record_btn_display();
    // }

    // always_record_task = lv_sat_timer_create(layout_always_record_delay_task, 100, NULL);

}
static void sat_layout_quit(always_record)
{

}


sat_layout_create(always_record);