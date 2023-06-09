#include "layout_define.h"
#include "layout_away.h"
#include "layout_setting_general.h"
typedef enum
{
    layout_away_count_obj_id_bg,
    layout_away_count_obj_id_end_btn,
    layout_away_count_obj_id_end_btn_label,
    layout_away_count_obj_id_end_time_label,
    layout_away_count_obj_id_main_bg,
}layout_away_count_scr_act_obj_id;

typedef enum
{
layout_away_count_obj_id_main_bg_tips,
}layout_away_count_main_bg_obj_id;


static int away_count_sec = 0;//离家设防生效缓冲时间（在缓冲时间过后，离家设防开始）

 lv_timer_t * away_alarm_release_det = NULL;
/************************************************************
** 函数说明: 离家模式设防倒计时结束按键事件
** 作者: xiaoxiao
** 日期: 2023-05-04 19:52:19
** 参数说明: 
** 注意事项: 
************************************************************/
static void layout_away_count_end_btn_obj_click(lv_event_t *ev)
{
   sat_layout_goto(away,LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
}

/************************************************************
** 函数说明: 倒计时显示
** 作者: xiaoxiao
** 日期: 2023-05-04 21:45:35
** 参数说明: 
** 注意事项: 
************************************************************/
static void layout_away_count_timer_obj_display(void)
{

    lv_obj_t *label_time = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), layout_away_count_obj_id_end_time_label);
    if (label_time == NULL)
    {
        return;
    }
    lv_label_set_text_fmt(label_time, "%02d:%02d", away_count_sec / 60, away_count_sec % 60);   
        
}

static void away_alarm_release_det_timer(lv_timer_t *ptimer)
{
    lv_timer_del(away_alarm_release_det);
    away_alarm_release_det = NULL;
    if(user_data_get()->alarm.away_alarm_enable == false)
    {
        return;

    }
    bool alarm_occur = false;
    for(int i =0 ;i<8;i++)
    {
        if(!(user_data_get()->alarm.away_alarm_enable_list & (0x01 << i)))
        {
            continue;
        }
        float value = user_sensor_value_get(i);
        if((user_data_get()->alarm.alarm_enable[i] == 1 && value > 2.5) || (user_data_get()->alarm.alarm_enable[i] == 2  && value < 1.0))
        {
            if(alarm_occur == false)
            {
                layout_alarm_alarm_channel_set(i);
                alarm_occur = true;

            }
            user_data_get()->alarm.alarm_trigger[i]  = true;
            struct tm tm;
            user_time_read(&tm);
            alarm_list_add(security_emergency,i, &tm);
            user_data_get()->alarm.emergency_mode = 1;
            user_data_save();
        }
    }
    if(alarm_occur)
    {
        if(sat_cur_layout_get() !=  sat_playout_get(alarm))
        {
            
            sat_layout_goto(alarm, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
        }
    }
}

static void layout_away_count_timer(lv_timer_t *ptimer)
{

    if(away_count_sec != 0)
    {
        away_count_sec -- ;
        layout_away_count_timer_obj_display();
    }
    else
    {

        user_data_get()->alarm.away_alarm_enable = true;
        extern unsigned char layout_away_sensor_enable_flag(void);
        user_data_get()->alarm.away_alarm_enable_list |= layout_away_sensor_enable_flag();
        user_data_save();
        
        
        away_alarm_release_det = lv_sat_timer_create(away_alarm_release_det_timer, 1000 * user_data_get()->alarm.away_release_time  , NULL);
        away_alarm_release_det->lock = true;
        sat_layout_goto(away,LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);    

    }

}

/************************************************************
** 函数说明: 离家设防缓冲页面参数初始化
** 作者: xiaoxiao
** 日期: 2023-05-06 08:25:05
** 参数说明: 
** 注意事项: 
************************************************************/
static void layout_alarm_count_param_init(void)
{
    if(away_alarm_release_det != NULL)
    {
        lv_timer_del(away_alarm_release_det);
        away_alarm_release_det = NULL;
    }
    away_count_sec =user_data_get()->alarm.away_setting_time * 60;

}

static void sat_layout_enter(away_count)
{
    SAT_DEBUG("away_alarm_enable_list is 0x%x\n",user_data_get()->alarm.away_alarm_enable_list);

    /************************************************************
    ** 函数说明:离家设防缓冲页面参数初始化
    ** 作者: xiaoxiao
    ** 日期: 2023-05-06 08:30:13
    ** 参数说明: 
    ** 注意事项: 
    ************************************************************/
   {
        layout_alarm_count_param_init();
   }
    /************************************************************
    ** 函数说明: 离家设防倒计时背景创建
    ** 作者: xiaoxiao
    ** 日期: 2023-05-04 19:55:11
    ** 参数说明: 
    ** 注意事项: 
    ************************************************************/
   {
        lv_common_img_btn_create(sat_cur_layout_screen_get(), layout_away_count_obj_id_bg, 0, 0, 1024, 600,
                                NULL, false, LV_OPA_COVER, 0, LV_OPA_COVER, 0,
                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
   }

    /************************************************************
    ** 函数说明: 背景图标
    ** 作者: xiaoxiao
    ** 日期: 2023-05-04 21:04:31
    ** 参数说明: 
    ** 注意事项: 
    ************************************************************/
   {
        lv_common_img_text_btn_create(sat_cur_layout_screen_get(), layout_away_count_obj_id_main_bg, 0, 0, 1024, 500,
                        NULL, LV_OPA_COVER, 0,  LV_OPA_COVER, 0,
                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                        0, 250, 1024, 46, layout_away_count_obj_id_main_bg_tips,
                        "Away", 0XFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large,
                        0, 0, 1024, 300, -1,
                        resource_ui_src_get("img_away.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
     
   }

    /************************************************************
    ** 函数说明: 离家模式设防倒计时显示
    ** 作者: xiaoxiao
    ** 日期: 2023-05-04 19:59:05
    ** 参数说明: 
    ** 注意事项: 
    ************************************************************/
   {
        // 时间
        lv_common_text_create(sat_cur_layout_screen_get(), layout_away_count_obj_id_end_time_label, 0, 336, 1024, 134,
                                                NULL, LV_OPA_TRANSP, 0X303030, LV_OPA_TRANSP, 0,
                                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                NULL, 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_plus);
        layout_away_count_timer_obj_display();

        lv_sat_timer_create(layout_away_count_timer, 1000, NULL);
   }

     /************************************************************
     ** 函数说明: 离家模式设防结束倒计时按键创建
     ** 作者: xiaoxiao
     ** 日期: 2023-05-04 19:43:18
     ** 参数说明: 
     ** 注意事项: 
     ************************************************************/
    {
        lv_common_img_text_btn_create(sat_cur_layout_screen_get(), layout_away_count_obj_id_end_btn, 0, 528, 1024, 72,
                        layout_away_count_end_btn_obj_click, LV_OPA_COVER, 0X47494A,  LV_OPA_COVER, 0X101010,
                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                        0, 17, 1024, 46, layout_away_count_obj_id_end_btn_label,
                        "End", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large,
                        3, 0, 77, 77, -1,
                        NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
    }
}


static void sat_layout_quit(away_count)
{
    
}

sat_layout_create(away_count);