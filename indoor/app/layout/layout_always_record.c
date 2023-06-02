#include "layout_define.h"
typedef enum
{
	always_record_scr_act_obj_id_head_cont,
	always_record_scr_act_obj_id_loop_obj,
	always_record_scr_act_obj_id_record_obj,
} always_record_scr_act_obj_id;
typedef enum
{
	always_record_head_cont_obj_id_cancel_obj,
	always_record_head_cont_obj_id_channel_label,
	always_record_head_cont_obj_id_time_label,
	always_record_head_cont_obj_id_motion_img,
	always_record_head_cont_obj_id_auto_img,
	always_record_head_cont_obj_id_sd_img,
	always_record_head_cont_obj_id_timeout_label
} always_record_head_cont_obj_id;

/************************************************************
** 函数说明: 多通道循环录像还是单通道
** 作者: xiaoxiao
** 日期: 2023-05-26 08:53:53
** 参数说明: 
** 注意事项: 
************************************************************/
static bool always_record_loop = true;
static bool is_always_record_video_ing = false;
static bool is_always_snapshot_ing = false;

static int always_record_time = 10;//记录时长
void always_record_time_set(int sec)
{
	always_record_time = sec;
}

static lv_timer_t *always_record_task = NULL;//刷新任务

/***
**   日期:2022-06-20 14:54:24
**   作者: leo.liu
**   函数作用：创建顶部从其
**   参数说明:
***/
static lv_obj_t *always_record_head_cont_create(void)
{

    lv_obj_t *cont = lv_common_img_btn_create(sat_cur_layout_screen_get(), always_record_scr_act_obj_id_head_cont, 0, 0, 1024, 80,
                                                NULL, true, LV_OPA_COVER, 0x00008, LV_OPA_COVER, 0x00008,
                                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
	return cont;
}

/************************************************************
** 函数说明: 获取通道
** 作者: xiaoxiao
** 日期: 2023-05-26 08:00:46
** 参数说明: 
** 注意事项: 
************************************************************/
static int always_record_channel_get(void)
{

	if ((monitor_valid_channel_check(MON_CH_DOOR1) == false) && (monitor_valid_channel_check(MON_CH_DOOR2) == false))
	{
		for(int i = 0; i < 8; i++)
        {
            if(monitor_valid_channel_check(MON_CH_CCTV1 + i))
            {
                if( i == 7)
                {
                    return MON_CH_NONE;
                } 
                break;;
            }

        }
	}
	int ch = monitor_channel_get();
	if (always_record_loop == false)
	{
		return ch;
	}
	if (ch == MON_CH_NONE)
	{
		ch = MON_CH_DOOR1;
		if (monitor_valid_channel_check(ch) == true)
		{
			return ch;
		}
	}
	int find = 0;
find_start:
	if (ch == MON_CH_DOOR1)
	{
		ch = MON_CH_DOOR2;
		if (monitor_valid_channel_check(ch) == true)
		{
			return ch;
		}
	}
	if (ch == MON_CH_DOOR2)
	{
		ch = MON_CH_CCTV1;
		if (monitor_valid_channel_check(ch) == true)
		{
			return ch;
		}
	}
    for(int i = 0; i < 8; i++)
    {
        if ((ch == MON_CH_CCTV1 + i) && (ch != MON_CH_CCTV8))
        {
            ch = MON_CH_CCTV2 + i;
            if (monitor_valid_channel_check(ch) == true)
            {
                return ch;
            }
        }
    }
	if (ch == MON_CH_CCTV8)
	{
		ch = MON_CH_DOOR1;
		if (monitor_valid_channel_check(ch) == true)
		{
			return ch;
		}
	}
	find++;
	if (find == 2)
	{
		return MON_CH_NONE;
	}
	goto find_start;
}


/************************************************************
** 函数说明: 录像点击事件
** 作者: xiaoxiao
** 日期: 2023-05-26 09:39:18
** 参数说明: 
** 注意事项: 
************************************************************/
static void always_record_record_btn_up(lv_event_t *ev)
{
    if (is_always_record_video_ing == true)
    {
        record_video_stop();
    }
    else
    {
        record_video_start(true, REC_MODE_MANUAL);
    }
}

static void layout_always_monitor_open(void)
{
	int ch = always_record_channel_get();
	if (ch != MON_CH_NONE)
	{
		monitor_channel_set(ch);
		monitor_open(true);
	}
}
static void always_record_record_btn_display(void)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),(always_record_scr_act_obj_id_record_obj));
        if (obj == NULL)
        {
            obj =  lv_common_img_btn_create(sat_cur_layout_screen_get(), always_record_scr_act_obj_id_record_obj, 912, 486, 80, 81,
                    always_record_record_btn_up, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                    resource_ui_src_get("btn_call_rec.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_TOP_MID);
        }
        if(obj == NULL)
        {
            return;
        }
        if((media_sdcard_insert_check() == SD_STATE_INSERT) || (media_sdcard_insert_check() == SD_STATE_FULL))
        {
            if (is_always_record_video_ing == true)
            {
                    lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_call_rec_ing.png"), LV_PART_MAIN);
            }
            else
            {
                    lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_call_rec.png"), LV_PART_MAIN);
            }
        }
        else
        {
            if (is_always_snapshot_ing == true)
            {
                    lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_call_save.png"), LV_PART_MAIN);
            }
            else
            {
                    lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_call_camera.png"), LV_PART_MAIN);
            }
        }

        
}

/************************************************************
** 函数说明: 当前时间显示
** 作者: xiaoxiao
** 日期: 2023-05-26 09:29:07
** 参数说明: 
** 注意事项: 
************************************************************/
static void always_record_time_label_display(void)
{
	lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), always_record_scr_act_obj_id_head_cont);
	lv_obj_t *obj = lv_obj_get_child_form_id(parent, always_record_head_cont_obj_id_time_label);
	if (obj == NULL)
	{
        obj = lv_common_text_create(parent, always_record_head_cont_obj_id_time_label, 182, 22, 240, 35,
                    NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                    ":", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
	}
	static struct tm tm;
	user_time_read(&tm);
	lv_label_set_text_fmt(obj, "%04d-%02d-%02d %02d:%02d", tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min);
}
static void layout_always_record_stop(void)
{
	if (is_always_record_video_ing)
	{
		record_video_stop();
	}
	always_record_record_btn_display();
}


static void layout_always_record_start(void)
{

	if (is_always_record_video_ing == true)
	{
		record_video_stop();
	}
	else if((media_sdcard_insert_check() == SD_STATE_UNPLUG) || (media_sdcard_insert_check() == SD_STATE_ERROR))
	{
        record_jpeg_start(REC_MODE_ALWAYS);

	}
	else
	{
        SAT_DEBUG("record_video_start\n");
		record_video_start(true,REC_MODE_ALWAYS);
	}
	always_record_record_btn_display();
}
/***
**   日期:2022-06-20 14:58:42
**   作者: leo.liu
**   函数作用：创建通道显示
**   参数说明:
***/
static void always_record_channel_label_display(void)
{
	lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), always_record_scr_act_obj_id_head_cont);
	lv_obj_t *obj = lv_obj_get_child_form_id(parent, always_record_head_cont_obj_id_channel_label);
	if (obj == NULL)
	{
        obj = lv_common_text_create(parent,  always_record_head_cont_obj_id_channel_label, 95, 23, 80, 42,
                        NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                        "", 0xFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
	}
    lv_label_set_text(obj,language_common_ch_string_get(monitor_channel_get()));
}
/***
**   日期:2022-06-20 16:38:19
**   作者: leo.liu
**   函数作用：创建任务等待录像
**   参数说明:
***/
static void layout_always_record_delay_task(lv_timer_t * pthime)
{

	layout_always_record_start();
	lv_timer_del(pthime);
	always_record_task = NULL;
}
static void layout_always_monitor_open_task(lv_timer_t *task)
{
	/* if (always_record_loop == true) */
	{
		layout_always_monitor_open();
		always_record_channel_label_display();
	}
	lv_timer_del(task);
	always_record_task = lv_sat_timer_create(layout_always_record_delay_task, 1500, NULL);
}

/************************************************************
** 函数说明: 超时时间显示
** 作者: xiaoxiao
** 日期: 2023-05-26 09:34:05
** 参数说明: 
** 注意事项: 
************************************************************/
static void always_record_tiemout_label_display(void)
{
	lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), always_record_scr_act_obj_id_head_cont);
	lv_obj_t *obj = lv_obj_get_child_form_id(parent, always_record_head_cont_obj_id_timeout_label);
	if (obj == NULL)
	{
        obj = lv_common_text_create(parent, always_record_head_cont_obj_id_timeout_label, 927, 23, 73, 42,
                    NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                    ":", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_normal);
		static int timeout = 0;
		timeout = always_record_time;
		obj->user_data = &timeout;
	}
	int *ptimeout = (int *)obj->user_data;
	int timeout = *ptimeout;
	lv_label_set_text_fmt(obj, "%02d:%02d", timeout / 60, timeout % 60);

	if (timeout != 0)
	{
		(*ptimeout)--;
	}
	else
	{
		(*ptimeout) = always_record_time;
		layout_always_record_stop();
		usleep(500 * 1000);
		/* if (always_record_loop == true) */
		{
			monitor_close();
		}

		if (always_record_task == NULL)
		{
			always_record_task = lv_sat_timer_create(layout_always_monitor_open_task, 1000, NULL);
		}
	}
}



/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: 记录状态状态显示
 ***********************************************/
static void always_record_video_state_callback(bool record_ing)
{
    is_always_record_video_ing = record_ing;
    always_record_record_btn_display();
}

/************************************************************
** 函数说明: 抓拍回调
** 作者: xiaoxiao
** 日期: 2023-06-01 16:24:33
** 参数说明: 
** 注意事项: 
************************************************************/
static void always_record_snapshot_state_callback(bool record_ing)
{
    is_always_snapshot_ing = record_ing;
    always_record_record_btn_display();
}

/************************************************************
** 函数说明: 通道时间刷新
** 作者: xiaoxiao
** 日期: 2023-05-26 09:24:12
** 参数说明: 
** 注意事项: 
************************************************************/
static void always_record_timeout_refresh_task(lv_timer_t *task)
{
	always_record_time_label_display();
	always_record_tiemout_label_display();
}

static void always_record_obj_cancel_obj_click(lv_event_t *e)
{
        sat_layout_goto(setting_recording, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
}

/************************************************************
** 函数说明: 返回按钮显示
** 作者: xiaoxiao
** 日期: 2023-06-01 11:55:45
** 参数说明: 
** 注意事项: 
************************************************************/
static void always_record_cancel_btn_display(void)
{
	lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), always_record_scr_act_obj_id_head_cont);
	lv_obj_t *obj = lv_obj_get_child_form_id(parent, always_record_head_cont_obj_id_cancel_obj);
	if (obj == NULL)
	{
        lv_common_img_btn_create(parent, always_record_head_cont_obj_id_cancel_obj, 0, 0, 80, 80,
                                    always_record_obj_cancel_obj_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                    resource_ui_src_get("btn_title_back.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
	}
}

/************************************************************
** 函数说明: 移动侦测图标显示
** 作者: xiaoxiao
** 日期: 2023-06-01 14:23:17
** 参数说明: 
** 注意事项: 
************************************************************/
static void always_record_motion_icon_display(void)
{
	lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), always_record_scr_act_obj_id_head_cont);
	lv_obj_t *obj = lv_obj_get_child_form_id(parent, always_record_head_cont_obj_id_motion_img);
	if (obj == NULL)
	{
            obj = lv_common_img_btn_create(parent, always_record_head_cont_obj_id_motion_img, 751, 16, 48, 48,
                                        NULL, false, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                        resource_ui_src_get("ic_list_visitor_video.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
	}
    if (obj == NULL)
    {
        return;
    }
    if ((media_sdcard_insert_check() == SD_STATE_INSERT) || (media_sdcard_insert_check() == SD_STATE_FULL))
    {
        lv_obj_set_x(obj, 751);

    }else
    {
        lv_obj_set_x(obj, 751 + 56);
    }
    if (user_data_get()->motion.enable)
    {
        lv_obj_set_style_bg_img_src(obj, resource_ui_src_get(user_data_get()->motion.saving_fmt == 1 ? "ic_list_visitor_img.png" : "ic_list_visitor_video.png"), LV_PART_MAIN);
    }
    else
    {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    }

}

/************************************************************
** 函数说明: 自动记录图标显示
** 作者: xiaoxiao
** 日期: 2023-06-01 14:32:31
** 参数说明: 
** 注意事项: 
************************************************************/
static void always_record_auto_icon_display(void)
{
	lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), always_record_scr_act_obj_id_head_cont);
	lv_obj_t *obj = lv_obj_get_child_form_id(parent, always_record_head_cont_obj_id_auto_img);
	if (obj == NULL)
	{
        obj = lv_common_img_btn_create(parent, always_record_head_cont_obj_id_auto_img, 807, 16, 48, 48,
                                    NULL, false, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                    resource_ui_src_get("ic_monitoring_auto.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
	}
    if(obj == NULL)
    {
        return;
    }
    if ((media_sdcard_insert_check() == SD_STATE_INSERT) || (media_sdcard_insert_check() == SD_STATE_FULL))
    {
        lv_obj_set_x(obj, 807);

    }else
    {
        lv_obj_set_x(obj, 807 + 56);
    }
    lv_obj_set_style_bg_img_src(obj, resource_ui_src_get(user_data_get()->auto_record_mode == 0 ? "ic_monitoring_manual.png" : "ic_monitoring_auto.png"), LV_PART_MAIN);

}
/***
**   日期:2022-06-20 15:18:42
**   作者: leo.liu
**   函数作用：sd卡
**   参数说明:
***/
static void always_record_sd_icon_display(void)
{
	lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), always_record_scr_act_obj_id_head_cont);
	lv_obj_t *obj = lv_obj_get_child_form_id(parent, always_record_head_cont_obj_id_sd_img);
	if (obj == NULL)
	{
        obj = lv_common_img_btn_create(parent, always_record_head_cont_obj_id_sd_img, 872, 16, 48, 48,
                                    NULL, false, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                    resource_ui_src_get("ic_monitoring_sdcard.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
	}
    if((media_sdcard_insert_check() == SD_STATE_UNPLUG) || (media_sdcard_insert_check() == SD_STATE_ERROR))
    {
        lv_obj_add_flag(obj,LV_OBJ_FLAG_HIDDEN);
    }else
    {
        lv_obj_clear_flag(obj,LV_OBJ_FLAG_HIDDEN);
    }
    lv_obj_set_style_bg_img_src(obj, resource_ui_src_get(media_sdcard_insert_check() == SD_STATE_INSERT? "ic_monitoring_sdcard.png" : \
    media_sdcard_insert_check() == SD_STATE_FULL?"ic_monitoring_sdcard_full.png":"ic_monitoring_sdcard__empty.png"), LV_PART_MAIN);


}

/************************************************************
** 函数说明: SD卡状态变化及处理
** 作者: xiaoxiao
** 日期: 2023-06-01 14:44:00
** 参数说明: 
** 注意事项: 
************************************************************/
static void always_record_sd_state_change_callback(void)
{
	always_record_motion_icon_display();
	always_record_auto_icon_display();
	always_record_sd_icon_display();
    always_record_record_btn_display();
    layout_always_record_stop();
}

static void always_record_loop_btn_display(void);
static void always_record_loop_btn_up(lv_event_t *ev)
{
	always_record_loop = always_record_loop ? false : true;
	always_record_loop_btn_display();
}
/************************************************************
** 函数说明: 循环还是单通道
** 作者: xiaoxiao
** 日期: 2023-06-01 17:02:18
** 参数说明: 
** 注意事项: 
************************************************************/
static void always_record_loop_btn_display(void)
{
    SAT_DEBUG("always_record_loop_btn_display\n");
	lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), always_record_scr_act_obj_id_loop_obj);
	if (obj == NULL)
	{
		always_record_loop = true;
        obj = lv_common_img_btn_create(sat_cur_layout_screen_get(), always_record_scr_act_obj_id_loop_obj, 808, 486, 80, 81,
        always_record_loop_btn_up, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
        resource_ui_src_get("btn_monitoring_fixed.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
	}

    lv_obj_set_style_bg_img_src(obj,always_record_loop?resource_ui_src_get("btn_monitoring_repeat.png"):resource_ui_src_get("btn_monitoring_fixed.png"),LV_PART_MAIN);
    

}

static void sat_layout_enter(always_record)
{
    
    always_record_loop = true;
    is_always_record_video_ing = false;
    always_record_time_set(user_data_get()->always_monitoring == 1 ? 10 : user_data_get()->always_monitoring == 2? 30 : 60);
    monitor_channel_set(MON_CH_NONE);
    layout_always_monitor_open();
    always_record_head_cont_create();
    always_record_cancel_btn_display();
    always_record_channel_label_display();
	always_record_motion_icon_display();
	always_record_auto_icon_display();
	always_record_sd_icon_display();
	always_record_time_label_display();
	always_record_tiemout_label_display();
    lv_sat_timer_create(always_record_timeout_refresh_task, 1000 , NULL);
    always_record_record_btn_display();
    always_record_loop_btn_display();
    standby_timer_close();
    
    /*sd卡状态处理*/
    sd_state_channge_callback_register(always_record_sd_state_change_callback);

    /*记录注册*/
    record_state_callback_register(always_record_video_state_callback);

    /*抓拍注册*/
    snapshot_state_callback_register(always_record_snapshot_state_callback);

    always_record_task = lv_sat_timer_create(layout_always_record_delay_task, 1500, NULL);
    
}
static void sat_layout_quit(always_record)
{
    record_video_stop();
    monitor_close();
    /*sd卡状态处理 */
    sd_state_channge_callback_register(NULL);
    record_state_callback_register(NULL);
    
	standby_timer_restart(true);
}


sat_layout_create(always_record);