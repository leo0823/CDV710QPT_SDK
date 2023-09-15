#include "layout_define.h"
#include "layout_monitor.h"
enum
{
         layout_alarm_obj_id_bg,
         layout_alarm_obj_id_bell,
         layout_alarm_obj_id_title,
         layout_alarm_obj_id_time,
         layout_alarm_obj_id_mode,
         layout_alarm_obj_id_log,
         layout_alarm_obj_id_confirm_btn,
         layout_alarm_obj_id_confirm_label,

        layout_alarm_obj_id_passwd_cont,

};

typedef enum
{
        layout_alarm_obj_id_number_keyboard_btn,
        layout_alarm_password_input_obj_id_tips,
        layout_alarm_password_input_obj_id_cancel,
        layout_alarm_obj_id_passwd_input_tx1,
        layout_alarm_obj_id_passwd_input_tx2,
        layout_alarm_obj_id_passwd_input_tx3,
        layout_alarm_obj_id_passwd_input_tx4,

}passwd_cont_obj_id;

static short int alarm_passwd_input_error_count = 0;//输入错误次数
static short int alarm_idel_time = 0;//警报铃声空闲时间计时
static lv_timer_t * alarm_ring_idel_timer = 0;//警报铃声空闲时间计时
static void alarm_alarm_cont_display(lv_timer_t *ptimer)
{

        lv_disp_t*obj = lv_disp_get_default();
        if (strncmp((char *)obj->bg_img,(char *)resource_wallpaper_src_get("bg_emergency_occur01.jpg", 1024, 600), strlen((char *)obj->bg_img)) == 0)
        {
                lv_disp_set_bg_image(lv_disp_get_default(), resource_wallpaper_src_get("bg_emergency_occur02.jpg", 1024, 600));
        }
        else if (strncmp((char *)obj->bg_img,(char *)resource_wallpaper_src_get("bg_emergency_occur02.jpg", 1024, 600), strlen((char *)obj->bg_img)) == 0)
        {
                lv_disp_set_bg_image(lv_disp_get_default(), resource_wallpaper_src_get("bg_emergency_occur03.jpg", 1024, 600));
        }else
        {
                lv_disp_set_bg_image(lv_disp_get_default(), resource_wallpaper_src_get("bg_emergency_occur01.jpg", 1024, 600));
        }
}


/************************************************************
** 函数说明: 开启警报监控
** 作者: xiaoxiao
** 日期: 2023-05-08 09:53:58
** 参数说明: 
** 注意事项: 
************************************************************/
static void layout_alarm_monitor_open(void)
{
        if(user_data_get()->alarm.emergency_mode == 1)
        { 
                int ch = layout_alarm_alarm_channel_get();
                
                if(ch >= DEVICE_MAX)
                {
                        return ;       
                }else if(monitor_valid_channel_check(MON_CH_CCTV1 + ch))
                {
                        monitor_channel_set(MON_CH_CCTV1 + ch);
                        monitor_open(false,true);
                }    
               
        }else 
        {       

        }
                 
}

static void alarm_ring_idel_check(lv_timer_t *ptimer)
{
        if(alarm_idel_time++ == 20)
        {
                user_data_get()->alarm.alarm_ring_play = true;
                user_data_save();
                ring_alarm_play();
                lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),  layout_alarm_obj_id_passwd_cont);
                if(parent)
                {
                        lv_obj_add_flag(parent,LV_OBJ_FLAG_HIDDEN);
                }
                alarm_idel_time = 0;
                lv_timer_del(alarm_ring_idel_timer);
                alarm_ring_idel_timer = NULL;
                if(user_data_get()->system_mode && 0x0f != 0x01)
                {
                        sat_ipcamera_data_sync(0x00, 0x04, (char *)user_data_get(), sizeof(user_data_info), 10, 100, NULL);
                }
        }
}

static void alarm_stop_obj_click(lv_event_t *ev)
{
        if(alarm_ring_idel_timer != NULL)
        {
                lv_timer_del(alarm_ring_idel_timer);
                alarm_ring_idel_timer = NULL;
        }
        alarm_idel_time = 0;
        alarm_ring_idel_timer = lv_sat_timer_create(alarm_ring_idel_check, 1000, NULL);
        user_data_get()->alarm.alarm_ring_play = false;
        user_data_save();
        if(user_data_get()->system_mode && 0x0f != 0x01)
        {
                sat_ipcamera_data_sync(0x00, 0x04, (char *)user_data_get(), sizeof(user_data_info), 10, 100, NULL);
        }
        sat_linphone_audio_play_stop();
        lv_obj_t * passwd_cont = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),layout_alarm_obj_id_passwd_cont);
        if(1/*user_data_get()->alarm.is_alarm_return == false*/)//警报停止模式
        {

                struct tm tm;
                user_time_read(&tm);
                if (user_data_get()->alarm.emergency_mode == 1) // 判断是否为警报器触发的警报
                {
                        alarm_list_add(security_emergency_stop, 8, &tm);
                }else
                {
                        alarm_list_add(emergency_stop, 8, &tm);
                }
                lv_obj_clear_flag(passwd_cont, LV_OBJ_FLAG_HIDDEN);                    
  
        }else
        {
                if (user_data_get()->alarm.emergency_mode == 1) // 判断是否为警报器触发的警报
                {
                        int ch = layout_alarm_alarm_channel_get();
                        if (((user_data_get()->alarm.alarm_enable[ch] == 2) && (user_sensor_value_get(ch)> ALM_HIGHT)) || ((user_data_get()->alarm.alarm_enable[ch] == 1) && (user_sensor_value_get(ch) < ALM_LOW)))
                        {
                                user_data_get()->alarm.alarm_trigger[ch] = false;
                                user_data_save();
                                struct tm tm;
                                user_time_read(&tm);
                                alarm_list_add(emergency_return, ch, &tm);
                        }
                        else
                        {
                                user_data_get()->alarm.alarm_ring_play = true;
                                user_data_save();
                                sat_ipcamera_data_sync(0x00, 0x04, (char *)user_data_get(), sizeof(user_data_info), 10, 100, NULL);
                                ring_alarm_play();
                        }
                }
                else
                {
                        user_data_get()->alarm.alarm_trigger[7] = false;
                        user_data_save();
                        struct tm tm;
                        user_time_read(&tm);
                        alarm_list_add(emergency_return, 8, &tm);
                }
                if(user_data_get()->system_mode && 0x0f != 0x01)
                {
                        sat_ipcamera_data_sync(0x00, 0x04, (char *)user_data_get(), sizeof(user_data_info), 10, 100, NULL);
                }
                alarm_trigger_check();
        }
}



/************************************************************
** 函数说明: 警报界面警报触发处理
** 作者: xiaoxiao
** 日期: 2023-05-06 21:33:07
** 参数说明:
** 注意事项:
************************************************************/
static void layout_alarm_trigger_func(int arg1, int arg2)
{
        if((arg1 == 7) && (arg2 < ALM_LOW * 100))
        {
                buzzer_call_trigger_check();
        }else
        {
                if((!(user_data_get()->alarm.away_alarm_enable_list & (0x01 << arg1)))&&(!(user_data_get()->alarm.security_alarm_enable_list & (0x01 << arg1))))
                {
                        return;
                }
                if (((user_data_get()->alarm.alarm_enable[arg1] == 1 && arg2 > ALM_HIGHT * 100) || (user_data_get()->alarm.alarm_enable[arg1] == 2 && arg2 < ALM_LOW * 100)) && (user_data_get()->alarm.alarm_trigger[arg1] == false))
                {

                        user_data_get()->alarm.alarm_trigger[arg1] = true;
                        user_data_get()->alarm.emergency_mode = 1;
                        user_data_save();
                        struct tm tm;
                        user_time_read(&tm);
        
                        alarm_list_add(security_emergency, arg1, &tm);
                }
        }
}

/************************************************************
** 函数说明: 警报时触发模式显示
** 作者: xiaoxiao
** 日期: 2023-05-04 16:47:47
** 参数说明:
** 注意事项:
************************************************************/
static void layout_alarm_alarm_mode_label_display(void)
{
        struct tm tm;
        user_time_read(&tm);
        lv_obj_t *obj1 = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),  layout_alarm_obj_id_title);
        lv_obj_t *obj2 = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),  layout_alarm_obj_id_mode);
        if (user_data_get()->alarm.emergency_mode == 0)
        {
                lv_label_set_text_fmt(obj1, lang_str_get(LAYOUT_ALARM_XLS_LANG_ID_EMERHENCY));
                lv_label_set_text_fmt(obj2, lang_str_get(LAYOUT_ALARM_XLS_LANG_ID_HOUSEHOLD_OPERATION));
        }
        else
        {
                lv_label_set_text_fmt(obj1, lang_str_get(LAYOUT_ALARM_XLS_LANG_ID_SECURITY_EMERGENCY));
                lv_label_set_text_fmt(obj2, lang_str_get(LAYOUT_ALARM_XLS_LANG_ID_SENSOR1 + layout_alarm_alarm_channel_get()));
        }
}


/***********************************************
** 作者: leo.liu
** 日期: 2023-2-1 8:51:49
** 说明: 输入数字键盘
***********************************************/
static lv_obj_t * layout_alarm_password_input_textarea_focused_get(void)
{
        lv_obj_t *textarea = NULL;

        lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),  layout_alarm_obj_id_passwd_cont);
        for (int i = 0; i < 2; i++)
        {
               
                for (int j = 0; j < 4; j++)
                {
                        textarea = lv_obj_get_child_form_id(parent,  layout_alarm_obj_id_passwd_input_tx1 + j);
                        if (lv_obj_get_state(textarea) == LV_STATE_FOCUSED)
                        {
                            return textarea;
                        }
                }
        }
        return textarea;
}


static void passwd_incorrect_timer(lv_timer_t *ptimer)
{
        lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),  layout_alarm_obj_id_passwd_cont);
        lv_obj_set_style_bg_color(parent, lv_color_hex(0x0), LV_PART_MAIN);
        lv_timer_del(ptimer);

}

bool layout_alarm_stop_btn_label_display(void)
{
        lv_obj_t * obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),layout_alarm_obj_id_confirm_btn);
        if(obj != NULL)
        {
                lv_obj_t *label = lv_obj_get_child_form_id(obj,layout_alarm_obj_id_confirm_label);
                if(user_data_get()->alarm.is_alarm_return)
                {
                        lv_label_set_text(label,lang_str_get(LAYOUT_ALARM_XLS_LANG_ID_RETURN));
                }else
                {
                        lv_label_set_text(label,lang_str_get(LAYOUT_ALARM_XLS_LANG_ID_STOP));
                }
                return true;
        }
        return false;
}

/************************************************************
** 函数说明: 文本区域复位
** 作者: xiaoxiao
** 日期：2023-09-13 21:06:00 
** 参数说明: 
** 注意事项：
************************************************************/
static void layout_alarm_passwd_input_txt_reset(void)
{
        lv_obj_t * parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),layout_alarm_obj_id_passwd_cont);
        lv_obj_t *textarea = NULL;
        if(parent)
        {
                //文本区域复位
                for(int k = 0;k < 4;k++)
                {
                        textarea = lv_obj_get_child_form_id(parent,  layout_alarm_obj_id_passwd_input_tx1 + k);
                        lv_textarea_del_char(textarea);
                        lv_obj_clear_state(textarea, LV_STATE_FOCUSED);
                }
                textarea = lv_obj_get_child_form_id(parent,  layout_alarm_obj_id_passwd_input_tx1);
                lv_obj_add_state(textarea, LV_STATE_FOCUSED);
        }

}

/************************************************************
** 函数说明: 文本区域选择下一位
** 作者: xiaoxiao
** 日期：2023-09-13 21:06:00 
** 参数说明: 
** 注意事项：
************************************************************/
static void  layout_alarm_passwd_input_text_next_foucued(void)
{
        lv_obj_t *textarea = NULL;

        lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),  layout_alarm_obj_id_passwd_cont);
   
        for (int j = 0; j < 4; j++)
        {
                textarea = lv_obj_get_child_form_id(parent,  layout_alarm_obj_id_passwd_input_tx1 + j);
                if (lv_obj_get_state(textarea) == LV_STATE_FOCUSED)
                {
                        if(j == 3)
                        {
                                char buffer[4];
                                memset(buffer,0,sizeof(buffer));
                                
                                for(int k =0;k<4;k++)
                                {
                                        strcat(buffer,lv_textarea_get_text(lv_obj_get_child_form_id(parent,  layout_alarm_obj_id_passwd_input_tx1 + k)));
                                }
                                if(strncmp(user_data_get()->etc.password,buffer,4) == 0)
                                {
                                        #ifdef ALARM_RETURN
                                        if (user_data_get()->alarm.emergency_mode)
                                        {
                                                lv_obj_add_flag(parent, LV_OBJ_FLAG_HIDDEN);
                                                lv_obj_t * label = lv_obj_get_child_form_id(lv_obj_get_child_form_id(sat_cur_layout_screen_get(),layout_alarm_obj_id_confirm_btn),layout_alarm_obj_id_confirm_label);
                                                user_data_get()->alarm.is_alarm_return = true;
                                                user_data_save();
                                                sat_ipcamera_data_sync(0x00, 0x04, (char *)user_data_get(), sizeof(user_data_info), 10, 100, NULL);
                                                lv_label_set_text(label,lang_str_get(LAYOUT_ALARM_XLS_LANG_ID_RETURN));
                                                return;
                                        }
                                        #else
                                        if (user_data_get()->alarm.emergency_mode == 1) // 判断是否为警报器触发的警报
                                        {
                                                int ch = layout_alarm_alarm_channel_get();
                                                if (((user_data_get()->alarm.alarm_enable[ch] == 2) && (user_sensor_value_get(ch)> ALM_HIGHT)) || ((user_data_get()->alarm.alarm_enable[ch] == 1) && (user_sensor_value_get(ch) < ALM_LOW)))
                                                {
                                                        user_data_get()->alarm.alarm_trigger[ch] = false;
                                                        user_data_save();
                                                        struct tm tm;
                                                        user_time_read(&tm);
                                                        alarm_list_add(emergency_stop, ch, &tm);
                                                }
                                                else
                                                {
                                                        user_data_get()->alarm.alarm_ring_play = true;
                                                        user_data_save();

                                                        lv_obj_add_flag(parent, LV_OBJ_FLAG_HIDDEN);//错误三次键盘隐藏
                                                        layout_alarm_passwd_input_txt_reset();
        
                                                        ring_alarm_play();
         
                                                }
                                        }
                                        else
                                        {
                                                user_data_get()->alarm.alarm_trigger[7] = false;
                                                user_data_save();
                                                // struct tm tm;
                                                // user_time_read(&tm);
                                                // alarm_list_add(emergency_stop, 8, &tm);
                                                
                                        }
                                        if(user_data_get()->system_mode && 0x0f != 0x01)
                                        {
                                                sat_ipcamera_data_sync(0x00, 0x04, (char *)user_data_get(), sizeof(user_data_info), 10, 100, NULL);
                                        }
                                        alarm_trigger_check();
                                        return;
                                        #endif
                                }

                                //密码错误，屏幕闪烁
                                lv_obj_set_style_bg_color(parent, lv_color_hex(0x5E0000), LV_PART_MAIN);
                                lv_sat_timer_create(passwd_incorrect_timer, 500, NULL);
                                //输入错误三次键盘隐藏

                                if((alarm_passwd_input_error_count ++) == 2)
                                {
                                        alarm_passwd_input_error_count = 0;
                                        user_data_get()->alarm.alarm_ring_play = true;
                                        user_data_save();
                                        ring_alarm_play();
                                        if(user_data_get()->system_mode && 0x0f != 0x01)
                                        {
                                                sat_ipcamera_data_sync(0x00, 0x04, (char *)user_data_get(), sizeof(user_data_info), 10, 100, NULL);
                                        }
                                        lv_obj_add_flag(parent, LV_OBJ_FLAG_HIDDEN);
                                }
                                layout_alarm_passwd_input_txt_reset();
                                return ;                              
                        }
                        lv_obj_clear_state(textarea, LV_STATE_FOCUSED);
                        textarea = lv_obj_get_child_form_id(parent,  layout_alarm_obj_id_passwd_input_tx1 + j + 1);
                        lv_obj_add_state(textarea, LV_STATE_FOCUSED);
                        return;
                }
                
        }
        
}

/************************************************************
** 函数说明: 文本区域选择上一位
** 作者: xiaoxiao
** 日期：2023-09-13 21:06:00 
** 参数说明: 
** 注意事项：
************************************************************/
static void  layout_alarm_passwd_input_text_prev_foucued(void)
{
        lv_obj_t *textarea = NULL;

        lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),  layout_alarm_obj_id_passwd_cont);

        for (int j = 0; j < 4; j++)
        {
                textarea = lv_obj_get_child_form_id(parent,  layout_alarm_obj_id_passwd_input_tx1 + j);
                if ((lv_obj_get_state(textarea) == LV_STATE_FOCUSED) && (j != 0))
                {
                    lv_obj_clear_state(textarea, LV_STATE_FOCUSED);
                    textarea = lv_obj_get_child_form_id(parent,  layout_alarm_obj_id_passwd_input_tx1 + j - 1);
                    lv_obj_add_state(textarea, LV_STATE_FOCUSED);
                    return;
                }
        }
        
}

static bool  layout_alarm_password_input_textbox_del(void)
{
         layout_alarm_passwd_input_text_prev_foucued();
        lv_obj_t *textarea =  layout_alarm_password_input_textarea_focused_get();

        if (textarea == NULL)
        {
                return false;
        }
        lv_textarea_del_char(textarea);

        return true;
}

static bool  layout_alarm_passwd_inpu_textbox_add(const char *string)
{
        lv_obj_t *textarea =  layout_alarm_password_input_textarea_focused_get();

        if (textarea == NULL)
        {
                return false;
        }

        lv_textarea_add_text(textarea, string);
        layout_alarm_passwd_input_text_next_foucued();
        return true;
}

static void  layout_alarm_password_input_keyboard_click(lv_event_t *ev)
{
        lv_obj_t *obj = lv_event_get_target(ev);
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);

        if (id == 11)
        {
                 layout_alarm_password_input_textbox_del();
        }
        else
        {
                const char *text = lv_btnmatrix_get_btn_text(obj, id);

                if (text != NULL)
                {

                        layout_alarm_passwd_inpu_textbox_add(text);
                }
        }
}

/************************************************************
** 函数说明: 键盘隐藏
** 作者: xiaoxiao
** 日期: 2023-05-16 21:29:07
** 参数说明: 
** 注意事项: 
************************************************************/
static void layout_alarm_close_keyboard_obj_click(lv_event_t *ev)
{
        user_data_get()->alarm.alarm_ring_play = true;
        user_data_save();
        ring_alarm_play();
        if(user_data_get()->system_mode && 0x0f != 0x01)
        {
                sat_ipcamera_data_sync(0x00, 0x04, (char *)user_data_get(), sizeof(user_data_info), 10, 100, NULL);
        }
        lv_obj_t * passwd_cont = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),layout_alarm_obj_id_passwd_cont);
        lv_obj_add_flag(passwd_cont,LV_OBJ_FLAG_HIDDEN);
        layout_alarm_passwd_input_txt_reset();
        if(alarm_ring_idel_timer != NULL)
        {
                lv_timer_del(alarm_ring_idel_timer);
                alarm_ring_idel_timer = NULL;
        }
        alarm_idel_time = 0;
}


/************************************************************
** 函数说明: 警报时间显示
** 作者: xiaoxiao
** 日期: 2023-05-04 16:53:39
** 参数说明:
** 注意事项:
************************************************************/
static void layout_alarm_alarm_time_label_display(void)
{
        struct tm tm;
        int ch = layout_alarm_alarm_channel_get();
        alarm_occur_time_get(ch, &tm);
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),  layout_alarm_obj_id_time);
        lv_label_set_text_fmt(obj, "%04d.%02d.%02d  %02d:%02d:%02d", tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

static bool layout_alarm_streams_running_register_callback(char *arg)
{
        int rec_mode = 0;
        if(user_data_get()->alarm.security_alarm_enable)
        {
                if((user_data_get()->alarm.security_auto_record) && ((media_sdcard_insert_check() == SD_STATE_INSERT) || (media_sdcard_insert_check() == SD_STATE_FULL))) 
                {
                     record_video_start(true, REC_MODE_ALARM);                      
                }
        }else if(user_data_get()->alarm.away_alarm_enable)
        {
                if(user_data_get()->alarm.away_auto_record)
                {
                        rec_mode |= REC_MODE_ALARM;
                }
        }
        sat_linphone_calls_cmd_send();
        record_jpeg_start(REC_MODE_TUYA_ALARM);

        return true;
}

/************************************************************
** 函数说明: 铃声播放回调
** 作者: xiaoxiao
** 日期: 2023-06-21 10:00:22
** 参数说明: 0:start 1:finish
** 注意事项: 
************************************************************/
static bool layout_alarm_ringplay_register_callback(int arg)
{
     //   SAT_DEBUG("arg is  %d\n",arg);
        if(arg == 1)
        {
                ring_alarm_play();
        }
        return true;
}


/************************************************************
** 函数说明: 
** 作者: xiaoxiao
** 日期: 2023-06-07 18:26:29
** 参数说明: 
** 注意事项: 
************************************************************/
static void sat_layout_enter(alarm)
{
        alarm_power_out_ctrl(true);
        sat_linphone_audio_play_stop();
        user_data_get()->alarm.is_alarm_return = false;
        user_data_get()->alarm.alarm_ring_play = true;
        user_data_save();
        alarm_sensor_cmd_register(layout_alarm_trigger_func); // 警报触发函数注册
        standby_timer_close();
        user_linphone_call_streams_running_receive_register(layout_alarm_streams_running_register_callback);
        ring_play_event_cmd_register(layout_alarm_ringplay_register_callback);
        user_linphone_call_incoming_received_register(NULL);
        layout_alarm_monitor_open();
        /************************************************************
        ** 函数说明: 背景创建
        ** 作者: xiaoxiao
        ** 日期: 2023-04-25 23:12:18
        ** 参数说明:
        ** 注意事项:
        ************************************************************/
        {
                lv_disp_set_bg_image(lv_disp_get_default(), resource_wallpaper_src_get("bg_emergency_occur01.jpg", 1024, 600));
                lv_timer_t *timer_task = lv_sat_timer_create(alarm_alarm_cont_display, 1000, NULL);
                lv_timer_ready(timer_task);

                /************************************************************
                ** 函数说明:
                ** 作者: xiaoxiao
                ** 日期: 2023-04-25 22:10:54
                ** 参数说明:
                ** 注意事项: 警报图标显示
                ************************************************************/
                {
                        lv_common_img_btn_create(sat_cur_layout_screen_get(),  layout_alarm_obj_id_bell, 392, 70, 240, 240,
                                                 NULL, false, LV_OPA_COVER, 0xff5951, LV_OPA_COVER, 0,
                                                 180, 40, LV_BORDER_SIDE_FULL, LV_OPA_40, 0xff90bd,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 resource_ui_src_get("ic_emergency_bell.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                }

                /************************************************************
                ** 函数说明: emergency title
                ** 作者: xiaoxiao
                ** 日期: 2023-04-25 23:35:58
                ** 参数说明:
                ** 注意事项:
                ************************************************************/
                {
                        lv_common_text_create(sat_cur_layout_screen_get(),  layout_alarm_obj_id_title, 0, 333, 1024, 78,
                                              NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              lang_str_get(LAYOUT_ALARM_XLS_LANG_ID_EMERHENCY), 0XE40A00, 0XE40A00, LV_TEXT_ALIGN_CENTER, lv_font_large);
                }

                /************************************************************
                ** 函数说明: 警报触发模式显示
                ** 作者: xiaoxiao
                ** 日期: 2023-05-04 16:51:43
                ** 参数说明:
                ** 注意事项:
                ************************************************************/
                {
                        lv_common_text_create(sat_cur_layout_screen_get(),  layout_alarm_obj_id_mode, 0, 415, 1024, 78,
                                              NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              "", 0XE40A00, 0XE40A00, LV_TEXT_ALIGN_CENTER, lv_font_large);
                        layout_alarm_alarm_mode_label_display();
                }

                /************************************************************
                ** 函数说明: emergency log
                ** 作者: xiaoxiao
                ** 日期: 2023-04-25 23:35:58
                ** 参数说明:
                ** 注意事项:
                ************************************************************/
                {
                        lv_common_text_create(sat_cur_layout_screen_get(),  layout_alarm_obj_id_time, 0, 467, 1024, 33,
                                              NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              "", 0XE40A00, 0XE40A00, LV_TEXT_ALIGN_CENTER, lv_font_normal);
                        layout_alarm_alarm_time_label_display();
                }

                /************************************************************
                ** 函数说明: 确认按键创建
                ** 作者: xiaoxiao
                ** 日期: 2023-04-25 22:43:38
                ** 参数说明:
                ** 注意事项:
                ************************************************************/
                {
                        lv_common_img_text_btn_create(sat_cur_layout_screen_get(),  layout_alarm_obj_id_confirm_btn, 0, 528, 1024, 72,
                                                      alarm_stop_obj_click, LV_OPA_COVER, 0xFF6B64, LV_OPA_COVER, 0xFF6B64,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      400, 17, 224, 27,  layout_alarm_obj_id_confirm_label,
                                                      lang_str_get(LAYOUT_ALARM_XLS_LANG_ID_STOP), 0xffffff, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_large,
                                                      3, 0, 77, 77, -1,
                                                      NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                }
        }
        {
                /************************************************************
                ** 函数说明: 警报铃声任务
                ** 作者: xiaoxiao
                ** 日期: 2023-05-15 20:52:12
                ** 参数说明: 
                ** 注意事项: 
                ************************************************************/
                ring_alarm_play();
         
        }

        {
            lv_obj_t * parent = lv_common_img_btn_create(sat_cur_layout_screen_get(), layout_alarm_obj_id_passwd_cont, 0, 0, 1024, 600,
                                        NULL, false, LV_OPA_90, 0, LV_OPA_90, 0,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                        NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
            
            lv_obj_add_flag(parent, LV_OBJ_FLAG_HIDDEN);

            /************************************************************
            ** 函数说明: 数字键盘创建
            ** 作者: xiaoxiao
            ** 日期: 2023-04-27 16:40:03
            ** 参数说明: 
            ** 注意事项: 
            ************************************************************/
            {
                lv_obj_t *obj = lv_common_number_input_keyboard_create(parent, layout_alarm_obj_id_number_keyboard_btn, 128, 90, 312, 500,
                                                     layout_alarm_password_input_keyboard_click, LV_OPA_COVER, 0X101010, LV_OPA_COVER, 0x00a8ff,
                                                    360, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                    360, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                    0XFFFFFF, 0XFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large,
                                                    18, 24);
                lv_btnmatrix_set_btn_ctrl(obj, 9, LV_BTNMATRIX_CTRL_HIDDEN);
            }

            /************************************************************
            ** 函数说明: 密码提示
            ** 作者: xiaoxiao
            ** 日期: 2023-04-27 17:50:33
            ** 参数说明: 
            ** 注意事项: 
            ************************************************************/
            {
                    lv_common_text_create(parent, layout_alarm_password_input_obj_id_tips, 644, 198, 217, 43,
                                        NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                       lang_str_get(LAYOUT_SECURITY_XLS_LANG_ID_ENTER_PASSSWORD), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_normal);
            }

            /************************************************************
            ** 函数说明: 密码文本输入框创建
            ** 作者: xiaoxiao
            ** 日期: 2023-04-27 17:30:01
            ** 参数说明: 
            ** 注意事项: 
            ************************************************************/
            for (int j = 0; j < 4; j++)
            {

                lv_obj_t *obj = lv_common_textarea_create(parent, layout_alarm_obj_id_passwd_input_tx1+j, 596 + 84 * j, 262, 60, 76,
                                                            NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0X101010,
                                                            LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0X101010,
                                                            0, 4, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0Xffffff,
                                                            0, 4, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                            NULL, 0Xffffff, 0Xffffff, LV_TEXT_ALIGN_CENTER, lv_font_large, 1,
                                                            20, 500, 0Xffffff);

                lv_textarea_set_password_mode(obj, true);
                lv_textarea_set_password_show_time(obj, 500);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                if (j == 0)
                {
                        lv_obj_add_state(obj, LV_STATE_FOCUSED);
                }
            }

            /***********************************************
            ** 作者: leo.liu
            ** 日期: 2023-2-3 14:13:25
            ** 说明: 返回按钮
            ***********************************************/
            {
                lv_common_img_btn_create(parent, layout_alarm_password_input_obj_id_cancel, 35, 15, 48, 48,
                                                layout_alarm_close_keyboard_obj_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                            0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                            0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                            resource_ui_src_get("btn_close.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
            }
       
        }
        lv_obj_pressed_func = NULL;
}
static void sat_layout_quit(alarm)
{
        if(alarm_ring_idel_timer != NULL)
        {
                lv_timer_del(alarm_ring_idel_timer);
                alarm_ring_idel_timer = NULL;
        }
        user_linphone_call_incoming_received_register(monitor_doorcamera_call_extern_func);
        alarm_power_out_ctrl(false);
        lv_obj_pressed_func = lv_layout_touch_callback;
        ring_play_event_cmd_register(NULL);
        user_linphone_call_streams_running_receive_register(NULL);
        alarm_sensor_cmd_register(layout_alarm_trigger_default); // 警报触发函数注册
        record_video_stop();
        monitor_close(0x02);
        standby_timer_restart(true);
        lv_disp_set_bg_image(lv_disp_get_default(), NULL);

}


sat_layout_create(alarm);