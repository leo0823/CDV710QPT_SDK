#include "layout_define.h"
#include "layout_security.h"
#include "layout_setting_general.h"
typedef enum
{
    layout_security_obj_id_title,
    layout_security_obj_id_tips,
    layout_security_obj_id_audto_record,
    layout_security_obj_id_cancel,
    layout_security_obj_id_log,
    layout_security_obj_id_state_tips,
    layout_security_obj_id_obj_id_confirm_btn,
    layout_security_obj_id_cont1,
    layout_security_obj_id_cont2,
    layout_security_obj_id_cont3,
    layout_security_obj_id_cont4,
    layout_security_obj_id_cont5,
    layout_security_obj_id_cont6,
    layout_security_obj_id_cont7,
    layout_security_obj_id_cont8,

    layout_security_obj_id_passwd_cont,
    layout_security_obj_id_number_keyboard_btn,
    layout_security_obj_id_passwd_input_tx1,
    layout_security_obj_id_passwd_input_tx2,
    layout_security_obj_id_passwd_input_tx3,
    layout_security_obj_id_passwd_input_tx4,
    layout_security_password_input_obj_id_cancel,
    layout_security_password_input_obj_id_tips,
} layout_security_scr_act_obj_id;


typedef enum
{
        layout_security_obj_id_confirm_label,
} layout_security_confirm_btn_obj_id;
typedef enum
{
    layout_security_sensor_select_cont_checkbox_id,
    layout_security_sensor_select_cont_bg_id,
    layout_security_sensor_select_cont_label_id,
    layout_security_sensor_select_cont_img_id,
} layout_security_sensor_select_cont_obj_id;

typedef enum
{
    auto_record_switch_id,
    auto_record_label_id,
} layout_security_obj_id_auto_record_obj_id;
static void layout_security_back_obj_click(lv_event_t *ev)
{
        sat_layout_goto(home,LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
}

/************************************************************
** 函数说明: 获取传感器使能选项
** 作者: xiaoxiao
** 日期: 2023-05-06 10:37:00
** 参数说明: 
** 注意事项: 
************************************************************/
static unsigned char layout_security_sensor_enable_flag(void)
{
        unsigned char selected = 0x00;
        for(int i = 0; i<8; i++)
        {
               lv_obj_t* parent_cont =  lv_obj_get_child_form_id(sat_cur_layout_screen_get(),layout_security_obj_id_cont1 + i);
               if(parent_cont == NULL)
               {
                continue;
               }
               lv_obj_t* checkbox =  lv_obj_get_child_form_id(parent_cont,layout_security_sensor_select_cont_checkbox_id);
                if (strncmp(checkbox->bg_img_src, resource_ui_src_get("btn_checkbox_n.png"), strlen(resource_ui_src_get("btn_checkbox_n.png"))) != 0)
                {
                        selected |= (0x01 << i );
                }

        }
        return selected;
}

/************************************************************
** 函数说明: 底部确认按键显示
** 作者: xiaoxiao
** 日期: 2023-05-09 21:22:03
** 参数说明: 
** 注意事项: 
************************************************************/
static void layout_security_ececution_stop_btn_display(void)
{
        lv_obj_t * obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), layout_security_obj_id_obj_id_confirm_btn);
        if(user_data_get()->alarm.security_alarm_enable)
        {
                printf("set false");
                lv_obj_set_style_bg_color(obj,lv_color_hex(0x47494a),LV_PART_MAIN);
                lv_obj_t * label = lv_obj_get_child_form_id(obj,layout_security_obj_id_confirm_label);
                lv_label_set_text(label,"End");
        }
        else
        {
                if(layout_security_sensor_enable_flag())
                {
                lv_obj_set_style_bg_color(obj,lv_color_hex(0x00A8FF),LV_PART_MAIN);
                lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE); 
                }else
                {
                lv_obj_set_style_bg_color(obj,lv_color_hex(0x47494A),LV_PART_MAIN);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);    
                }
                lv_obj_t * label = lv_obj_get_child_form_id(obj,layout_security_obj_id_confirm_label);
                lv_label_set_text(label,"Confirm");
        }
        }

/************************************************************
** 函数说明: 传感器选择点击事件
** 作者: xiaoxiao
** 日期: 2023-04-27 11:04:59
** 参数说明: 
** 注意事项: 
************************************************************/
static void layout_security_sensor_select_obj_click(lv_event_t *ev)
{

    lv_obj_t *obj = lv_event_get_current_target(ev);
    for(int i = 0; i < 8 ;i++)
    {
        lv_obj_t *cont = lv_obj_get_child_form_id(lv_obj_get_parent(obj), layout_security_obj_id_cont1 + i);
        if(cont == obj)
        {
                float value = user_sensor_value_get(i);
                lv_obj_t *checkbox = lv_obj_get_child_form_id(obj, layout_security_sensor_select_cont_checkbox_id);
                if((strncmp(checkbox->bg_img_src, resource_ui_src_get("btn_checkbox_n.png"), strlen(resource_ui_src_get("btn_checkbox_n.png"))) == 0) && ((user_data_get()->alarm.alarm_enable[i] == 1 && value < 1.0) || (user_data_get()->alarm.alarm_enable[i] == 2  && value > 2.5)))
                {


                    lv_obj_set_style_bg_img_src(checkbox, resource_ui_src_get("btn_checkbox_s.png"), LV_PART_MAIN);

                }
                else
                {
           
                    lv_obj_set_style_bg_img_src(checkbox, resource_ui_src_get("btn_checkbox_n.png"), LV_PART_MAIN);

                }
        }
    }
    layout_security_ececution_stop_btn_display();
}

/************************************************************
** 函数说明: 查看日志
** 作者: xiaoxiao
** 日期: 2023-04-27 11:05:55
** 参数说明: 
** 注意事项: 
************************************************************/
static void layout_security_log_obj_click(lv_event_t *ev)
{
    sat_layout_goto(alarm_list,LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
}



/************************************************************
** 函数说明: 确认警报设备
** 作者: xiaoxiao
** 日期: 2023-04-27 11:05:55
** 参数说明: 
** 注意事项: 
************************************************************/
static void layout_security_confirm_btn_obj_click(lv_event_t *ev)
{
    if(user_data_get()->alarm.security_alarm_enable == true)
    {
        lv_obj_t * passwd_cont = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),layout_security_obj_id_passwd_cont);
        lv_obj_clear_flag(passwd_cont, LV_OBJ_FLAG_HIDDEN);   
    }
    else
    {
        user_data_get()->alarm.security_alarm_enable  = user_data_get()->alarm.security_alarm_enable  ? false : true;
        user_data_save();
        unsigned char list = layout_security_sensor_enable_flag();
        user_data_get()->alarm.security_alarm_enable_list |= list;
        user_data_save();
        layout_security_ececution_stop_btn_display();

    }

   
}


static void layout_security_sensor_select_create()
{
      security_list_info_t main_list_group[] = {

            {92, 144, 204, 160,
            layout_security_obj_id_cont1,
            layout_security_sensor_select_obj_click,
            layout_security_sensor_select_cont_checkbox_id,
            true,
            LAYOUT_SECURITY_LANG_ID_LANG_SEMSOR1, layout_security_language_get,
            },
            {304, 144, 204, 160,
            layout_security_obj_id_cont2,
            layout_security_sensor_select_obj_click,
            layout_security_sensor_select_cont_checkbox_id,
            true,
            LAYOUT_SECURITY_LANG_ID_LANG_SEMSOR2, layout_security_language_get,
            },
            {516, 144, 204, 160,
            layout_security_obj_id_cont3,
            layout_security_sensor_select_obj_click,
            layout_security_sensor_select_cont_checkbox_id,
            true,
            LAYOUT_SECURITY_LANG_ID_LANG_SEMSOR3, layout_security_language_get,
            },
            {728, 144, 204, 160,
            layout_security_obj_id_cont4,
            layout_security_sensor_select_obj_click,
            layout_security_sensor_select_cont_checkbox_id,
            true,
            LAYOUT_SECURITY_LANG_ID_LANG_SEMSOR4, layout_security_language_get,
            },
            {92, 312, 204, 160,
            layout_security_obj_id_cont5,
            layout_security_sensor_select_obj_click,
            layout_security_sensor_select_cont_checkbox_id,
            true,
            LAYOUT_SECURITY_LANG_ID_LANG_SEMSOR5, layout_security_language_get,
            },
            {304, 312, 204, 160,
            layout_security_obj_id_cont6,
            layout_security_sensor_select_obj_click,
            layout_security_sensor_select_cont_checkbox_id,
            true,
            LAYOUT_SECURITY_LANG_ID_LANG_SEMSOR6, layout_security_language_get,
            },
            {516, 312, 204, 160,
            layout_security_obj_id_cont7,
            layout_security_sensor_select_obj_click,
            layout_security_sensor_select_cont_checkbox_id,
            true,
            LAYOUT_SECURITY_LANG_ID_LANG_SEMSOR7, layout_security_language_get,
            },
            {728, 312, 204, 160,
            layout_security_obj_id_cont8,
            layout_security_sensor_select_obj_click,
            layout_security_sensor_select_cont_checkbox_id,
            true,
            LAYOUT_SECURITY_LANG_ID_LANG_SEMSOR8, layout_security_language_get,
            },
        };

        int j = 0;//标志在第几个容器位置上显示数据

        for (int i = 0; i < sizeof(main_list_group) / sizeof(security_list_info_t); i++)
        {
            //if(user_data_get()->alarm.away_alarm_enable_list & (0x01 << i))
            if(((user_data_get()->alarm.alarm_enable[i] == 1) || (user_data_get()->alarm.alarm_enable[i] == 2)) && (user_data_get()->alarm.alarm_enable_always[0][i] == false && user_data_get()->alarm.alarm_enable_always[1][i] == false))
            {
                lv_obj_t *parent =   lv_common_img_text_btn_create(sat_cur_layout_screen_get(),  main_list_group[i].cont_id, main_list_group[j].x, main_list_group[j].y, main_list_group[j].w,  main_list_group[j].h,
                                    main_list_group[j].click_cb,  LV_OPA_COVER, 0x242526, LV_OPA_COVER, 0x242526,
                                        8, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                        0, 96,  204, 54, layout_security_sensor_select_cont_label_id,
                                        main_list_group[i].main_language_cb(main_list_group[i].main_language_id), 0xffffff, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_small,
                                        0, 12, 204, 80, layout_security_sensor_select_cont_img_id,
                                        (const char *)resource_ui_src_get("ic_security_normal_s.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);


                lv_common_img_btn_create(parent, main_list_group[i].check_id, 164, 8, 32, 32,
                                            NULL,false, LV_OPA_TRANSP, 0x00, LV_OPA_TRANSP, 0x101010,
                                            0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                            0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                            (user_data_get()->alarm.security_alarm_enable_list & (0x01 << i))?resource_ui_src_get("btn_checkbox_s.png"):(const char *)resource_ui_src_get("btn_checkbox_n.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                j++;
            }    
        }


}

static void emergenct_occupy_cctv_record_enable_display(void)
{
        lv_obj_t * parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),layout_security_obj_id_audto_record);
        lv_obj_t * obj = lv_obj_get_child_form_id(parent,auto_record_switch_id);
        if (user_data_get()->alarm.security_auto_record == true)
        {
                lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_switch_on.png"), LV_PART_MAIN);
        }
        else
        {
                lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_switch_off.png"), LV_PART_MAIN);
        }
}
/***********************************************
** 作者: leo.liu
** 日期: 2023-2-1 8:51:49
** 说明: 输入数字键盘
***********************************************/
static lv_obj_t *layout_security_password_input_textarea_focused_get(void)
{
        lv_obj_t *textarea = NULL;

        lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), layout_security_obj_id_passwd_cont);
        for (int i = 0; i < 2; i++)
        {
               
                for (int j = 0; j < 4; j++)
                {
                        textarea = lv_obj_get_child_form_id(parent, layout_security_obj_id_passwd_input_tx1 + j);
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
        lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), layout_security_obj_id_passwd_cont);
        lv_obj_set_style_bg_color(parent, lv_color_hex(0x0), LV_PART_MAIN);
        lv_timer_del(ptimer);

}

static void layout_security_passwd_input_text_next_foucued(void)
{
        lv_obj_t *textarea = NULL;

        lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), layout_security_obj_id_passwd_cont);
   
        for (int j = 0; j < 4; j++)
        {
                textarea = lv_obj_get_child_form_id(parent, layout_security_obj_id_passwd_input_tx1 + j);
                if (lv_obj_get_state(textarea) == LV_STATE_FOCUSED)
                {
                        if(j == 3)
                        {
                        char buffer[4];
                        memset(buffer,0,sizeof(buffer));
                        
                        for(int k =0;k<4;k++)
                        {
                                strcat(buffer,lv_textarea_get_text(lv_obj_get_child_form_id(parent, layout_security_obj_id_passwd_input_tx1 + k)));
                        }
                        if(strncmp(user_data_get()->etc.password,buffer,4) == 0)
                        {
                                // lv_obj_add_flag(lv_obj_get_child_form_id(sat_cur_layout_screen_get(),layout_security_obj_id_passwd_cont), LV_OBJ_FLAG_HIDDEN);
                                user_data_get()->alarm.security_alarm_enable = false;
                                unsigned char list = layout_security_sensor_enable_flag();
                                user_data_get()->alarm.security_alarm_enable_list &= (~list);
                                user_data_save();
                                sat_layout_goto(security,LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
                        }
                        
                        lv_obj_set_style_bg_color(parent, lv_color_hex(0x5E0000), LV_PART_MAIN);
                        lv_sat_timer_create(passwd_incorrect_timer, 500, NULL);
                        for(int k = 0;k < 4;k++)
                        {
                                textarea = lv_obj_get_child_form_id(parent, layout_security_obj_id_passwd_input_tx1 + k);
                                lv_textarea_del_char(textarea);
                                lv_obj_clear_state(textarea, LV_STATE_FOCUSED);
                        }
                        textarea = lv_obj_get_child_form_id(parent, layout_security_obj_id_passwd_input_tx1);
                        lv_obj_add_state(textarea, LV_STATE_FOCUSED);
                        return ;                              
                        }
                        lv_obj_clear_state(textarea, LV_STATE_FOCUSED);
                        textarea = lv_obj_get_child_form_id(parent, layout_security_obj_id_passwd_input_tx1 + j + 1);
                        lv_obj_add_state(textarea, LV_STATE_FOCUSED);
                        return;
                }
                
        }
        
}
static void layout_security_passwd_input_text_prev_foucued(void)
{
        lv_obj_t *textarea = NULL;

        lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), layout_security_obj_id_passwd_cont);

        for (int j = 0; j < 4; j++)
        {
                textarea = lv_obj_get_child_form_id(parent, layout_security_obj_id_passwd_input_tx1 + j);
                if ((lv_obj_get_state(textarea) == LV_STATE_FOCUSED) && (j != 0))
                {
                    lv_obj_clear_state(textarea, LV_STATE_FOCUSED);
                    textarea = lv_obj_get_child_form_id(parent, layout_security_obj_id_passwd_input_tx1 + j - 1);
                    lv_obj_add_state(textarea, LV_STATE_FOCUSED);
                    return;
                }
        }
        
}

static bool layout_security_password_input_textbox_del(void)
{
        layout_security_passwd_input_text_prev_foucued();
        lv_obj_t *textarea = layout_security_password_input_textarea_focused_get();

        if (textarea == NULL)
        {
                return false;
        }
        lv_textarea_del_char(textarea);

        return true;
}

static bool layout_security_passwd_inpu_textbox_add(const char *string)
{
        lv_obj_t *textarea = layout_security_password_input_textarea_focused_get();

        if (textarea == NULL)
        {
                return false;
        }

        lv_textarea_add_text(textarea, string);
        layout_security_passwd_input_text_next_foucued();
        return true;
}

static void layout_security_password_input_keyboard_click(lv_event_t *ev)
{
        lv_obj_t *obj = lv_event_get_target(ev);
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);

        if (id == 11)
        {
                layout_security_password_input_textbox_del();
        }
        else
        {
                const char *text = lv_btnmatrix_get_btn_text(obj, id);

                if (text != NULL)
                {

                        layout_security_passwd_inpu_textbox_add(text);
                }
        }
}

static void emergency_occupy_audo_record_click(lv_event_t *ev)
{
  
    if(user_data_get()->alarm.security_alarm_enable)
    {
        return;
    }
    user_data_get()->alarm.security_auto_record = user_data_get()->alarm.security_auto_record ? false : true;
    user_data_save();
    emergenct_occupy_cctv_record_enable_display();

   
}

/************************************************************
** 函数说明: 隐藏键盘
** 作者: xiaoxiao
** 日期: 2023-05-16 21:31:30
** 参数说明: 
** 注意事项: 
************************************************************/
static void layout_security_close_keyboard_click(lv_event_t *ev)
{
        lv_obj_t * passwd_cont = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),layout_security_obj_id_passwd_cont);
        lv_obj_add_flag(passwd_cont,LV_OBJ_FLAG_HIDDEN);
}

static void sat_layout_enter(security)
{
        /************************************************************
        ** 函数说明: 
        ** 作者: xiaoxiao
        ** 日期: 2023-04-26 11:43:19
        ** 参数说明: 标题显示
        ** 注意事项: 
        ************************************************************/
        {
            lv_common_text_create(sat_cur_layout_screen_get(), layout_security_obj_id_title, 0, 20, 1024, 40,
                                    NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                    "Security", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }


        /************************************************************
        ** 函数说明: 消息提示
        ** 作者: xiaoxiao
        ** 日期: 2023-04-27 11:27:18
        ** 参数说明: 
        ** 注意事项: 
        ************************************************************/
        {
            lv_common_text_create(sat_cur_layout_screen_get(), layout_security_obj_id_tips, 36, 97, 512, 88,
                                    NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                    "Detect outside intrusion when you are inside home", 0XB8B8B8, 0XB8B8B8, LV_TEXT_ALIGN_LEFT, lv_font_small);
        }

        
        /************************************************************
        ** 函数说明: CCTV自动录像
        ** 作者: xiaoxiao
        ** 日期: 2023-04-27 11:36:09
        ** 参数说明: 
        ** 注意事项: 
        ************************************************************/
       {

                 lv_common_img_text_btn_create(sat_cur_layout_screen_get(), layout_security_obj_id_audto_record, 548, 93, 476, 88,
                                              emergency_occupy_audo_record_click, LV_OPA_TRANSP, 0x00, LV_OPA_TRANSP, 0x101010,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              0, 10, 476-110, 32, auto_record_label_id,
                                              "CCTV automatic recording", 0xffffff, 0x00a8ff, LV_TEXT_ALIGN_RIGHT, lv_font_small,
                                              476-100, 0, 80, 48, auto_record_switch_id,
                                              (const char *)resource_ui_src_get("btn_switch_on.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                emergenct_occupy_cctv_record_enable_display();
        
       }

        /************************************************************
        ** 函数说明: 退回上一步
        ** 作者: xiaoxiao
        ** 日期: 2023-04-26 11:46:55
        ** 参数说明: 
        ** 注意事项: 
        ************************************************************/
        {
            lv_common_img_btn_create(sat_cur_layout_screen_get(), layout_security_obj_id_cancel,  35, 15, 48, 48,
                                    layout_security_back_obj_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                    resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }

        /************************************************************
        ** 函数说明: 传感器选择
        ** 作者: xiaoxiao
        ** 日期: 2023-04-27 10:48:40
        ** 参数说明: 
        ** 注意事项: 
        ************************************************************/
       {
            layout_security_sensor_select_create();
       }


        /************************************************************
        ** 函数说明: emergency log
        ** 作者: xiaoxiao
        ** 日期: 2023-04-25 23:35:58
        ** 参数说明: 
        ** 注意事项: 
        ************************************************************/
        {
            lv_common_img_btn_create(sat_cur_layout_screen_get(), layout_security_obj_id_log, 960, 16, 48, 48,
                                        layout_security_log_obj_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP,0x808080,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                        resource_ui_src_get("btn_title_emergencylist.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                
        }

        /************************************************************
        ** 函数说明: 在家模式设防状态显示
        ** 作者: xiaoxiao
        ** 日期: 2023-04-28 16:26:21
        ** 参数说明: 
        ** 注意事项: 
        ************************************************************/
       {
            lv_obj_t * obj = lv_common_text_create(sat_cur_layout_screen_get(), layout_security_obj_id_state_tips, 0, 481, 1024, 38,
                                    NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                    "Security mode is running", 0xFF6666, 0xFF6666, LV_TEXT_ALIGN_CENTER, lv_font_normal);
            if(!user_data_get()->alarm.security_alarm_enable) lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
       }

        /************************************************************
        ** 函数说明: 传感器警报选择确认
        ** 作者: xiaoxiao
        ** 日期: 2023-04-27 11:11:46
        ** 参数说明: 
        ** 注意事项: 
        ************************************************************/
        {
                lv_common_img_text_btn_create(sat_cur_layout_screen_get(), layout_security_obj_id_obj_id_confirm_btn, 0, 528, 1024, 72,
                                    layout_security_confirm_btn_obj_click, LV_OPA_COVER, 0x00A8FF,  LV_OPA_COVER, 0X101010,
                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                    400, 17, 224, 27, layout_security_obj_id_confirm_label,
                                    "Execution", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large,
                                    3, 0, 77, 77, -1,
                                    NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
            layout_security_ececution_stop_btn_display();
        }

        
        {
            lv_obj_t * parent = lv_common_img_btn_create(sat_cur_layout_screen_get(), layout_security_obj_id_passwd_cont, 0, 0, 1024, 600,
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
                lv_obj_t *obj = lv_common_number_input_keyboard_create(parent, layout_security_obj_id_number_keyboard_btn, 128, 90, 312, 500,
                                                    layout_security_password_input_keyboard_click, LV_OPA_COVER, 0X101010, LV_OPA_COVER, 0x00a8ff,
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
                    lv_common_text_create(parent, layout_security_password_input_obj_id_tips, 644, 198, 217, 43,
                                        NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                       "Enter Password", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_normal);
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

                lv_obj_t *obj = lv_common_textarea_create(parent, layout_security_obj_id_passwd_input_tx1+j, 596 + 84 * j, 262, 60, 76,
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
                    lv_common_img_btn_create(parent, layout_security_password_input_obj_id_cancel, 35, 15, 48, 48,
                                            layout_security_close_keyboard_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                            0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                            0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                            resource_ui_src_get("btn_close.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
            }
            

                

                    
        }

}

static void sat_layout_quit(security)
{
}

sat_layout_create(security);