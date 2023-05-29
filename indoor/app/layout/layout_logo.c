

#include "layout_define.h"
#include "onvif.h"
#include "tuya_api.h"
#include "tuya_uuid_and_key.h"
#include "layout_monitor.h"
// #include "dds/topic_table.h"
// #include "dds/msgStruct/message_data.h"
// #include "dds/public_topic.h"

#include "common/user_record.h"
#include "common/user_network.h"
#include "common/user_linphone.h"

static int input_index = 0;


enum
{
        logo_obj_id_logo_img,
        logo_obj_id_model_label,
        logo_obj_id_version_label,
        logo_obj_id_tuya_register_tips,
        logo_obj_id_tuya_register_textarea,
        logo_obj_id_tuya_register_number_keyboard_btn,
};


/************************************************************
** 函数说明: 待机检测任务
** 作者: xiaoxiao
** 日期: 2023-05-19 15:14:02
** 参数说明: 
** 注意事项: 
************************************************************/
static void standby_dection_timer(lv_timer_t *t)
{
        extern bool standby_timeout_check_and_process(void);
        standby_timeout_check_and_process();
}

static void logo_enter_system_timer(lv_timer_t *t)
{
        /*****  tuya api初始化 *****/
        //tuya_api_init(TUYA_PID);
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-1-5 10:5:6
        ** 说明: 时间初始化
        ***********************************************/
        user_time_init();

        /*
         * @日期: 2022-08-11
         * @作者: leo.liu
         * @注释: 开启文件系统
         */
        media_file_list_init();

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-1-5 17:17:15
        ** 说明: 网络初始化
        ***********************************************/
        user_network_init();

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-1-5 10:6:36
        ** 说明: linphone 初始化
        ***********************************************/
        user_linphone_init();

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-1-5 10:6:36
         ** 说明: GPIO 初始化
         ***********************************************/
        user_gpio_init();

        /************************************************************
        ** 函数说明: 待机初始化
        ** 作者: xiaoxiao
        ** 日期: 2023-05-19 15:21:05
        ** 参数说明: 
        ** 注意事项: 
        ************************************************************/
        standby_timer_init(sat_playout_get(frame_show),60000);
        standby_timer_restart(false);

        lv_timer_t * standby_timer = lv_sat_timer_create(standby_dection_timer, 1000, NULL);
        standby_timer->lock = true;
        lv_timer_ready(standby_timer);

        /**********************************************
         ** 作者: leo.liu
         ** 日期: 2023-1-5 10:6:36
         ** 说明:暂时放在连接wifi
        ***********************************************/
#if 0
        wifi_device_conneting();
        if(user_data_get()->wifi_enable)
        {
                wifi_device_open();
        }
        else
        {
                wifi_device_close();
        }
 #endif       
        tuya_event_cmd_register(tuya_event_defalut_handle);
        /************************************************************
        ** 函数说明:警报记录初始化
        ** 作者: xiaoxiao
        ** 日期: 2023-05-05 20:50:03
        ** 参数说明: 
        ** 注意事项: 
        ************************************************************/
        alarm_list_init();

        /************************************************************
        ** 函数说明: 通话记录列表初始化
        ** 作者: xiaoxiao
        ** 日期: 2023-05-17 10:17:15
        ** 参数说明: 
        ** 注意事项: 
        ************************************************************/
        call_list_init();

        alarm_sensor_cmd_register(layout_alarm_trigger_default);//警报回调注册


        if (user_data_get()->is_device_init == false)
        {
                sat_layout_goto(power_setting, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
        }
        else
        {
                audio_output_cmd_register(audio_output_event_default_process);
                user_linphone_call_incoming_received_register(monitor_doorcamera_call_extern_func);
                if(alarm_trigger_check() == false)
                {
                        sat_layout_goto(home, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
                }
                //sat_layout_goto(home, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);

        }
}

/************************************************************
** 函数说明: 序列号提示输入
** 作者: xiaoxiao
** 日期: 2023-05-12 09:39:40
** 参数说明: 
** 注意事项: 
************************************************************/
static void logo_serial_numbe_txt_create(void)
{
        lv_common_text_create(sat_cur_layout_screen_get(), logo_obj_id_tuya_register_tips, 0, 160,1024, 100,
                                NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                "Please enter the serial number", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
}

/************************************************************
** 函数说明: 涂鸦id序列号文本区域
** 作者: xiaoxiao
** 日期: 2023-05-12 09:49:16
** 参数说明: 
** 注意事项: 
************************************************************/
static void layout_logo_input_txt_create(void)
{
        lv_obj_t * ta = lv_common_textarea_create(sat_cur_layout_screen_get(), logo_obj_id_tuya_register_textarea, 60, 60, 904, 54,
                                                NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0X101010,
                                                LV_OPA_COVER, 0Xffffff, LV_OPA_COVER, 0Xffffff,
                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                "", 0Xffffff, 0Xffffff, LV_TEXT_ALIGN_CENTER, lv_font_normal, 8,
                                                0, 500, 0Xffffff);
        lv_obj_add_state(ta,LV_STATE_FOCUSED);
        lv_obj_set_style_anim_time(ta, 500,  LV_STATE_FOCUSED | LV_PART_CURSOR);
}

static void layout_logo_ok_btn_up(lv_obj_t *obj)
{
	static char input_buffer[6] = {0};
	obj = lv_obj_get_child_form_id(lv_scr_act(), logo_obj_id_tuya_register_textarea);
	int pos = lv_textarea_get_cursor_pos(obj);
	if (pos == 0)
	{
		return;
	}
	if ((input_index) == 0)
	{
		memset(input_buffer, 0, sizeof(input_buffer));
		strcpy(input_buffer, lv_textarea_get_text(obj));
		lv_textarea_set_text(obj, "");
		lv_textarea_set_cursor_pos(obj, 0);
		(input_index)++;
	}
	else if ((input_index) == 1)
	{
		if (strcmp(input_buffer, lv_textarea_get_text(obj)) == 0)
		{
			int index;
			sscanf(input_buffer, "%d", &index);
			if (tuya_key_and_key_xls_register(index) == true)
			{
				//system("umount /mnt");
				lv_obj_clean(sat_cur_layout_screen_get());
                                lv_common_img_btn_create(sat_cur_layout_screen_get(), logo_obj_id_logo_img, 0, 0, 1024, 600, // 273, 235, 486, 130,
                                NULL, false, LV_OPA_COVER, 0, LV_OPA_TRANSP, 0,
                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                resource_ui_src_get("ic_logo.png"), LV_OPA_TRANSP, 0, LV_ALIGN_CENTER);
		                lv_sat_timer_create(logo_enter_system_timer, 1000, NULL);

			}
		}
		else
		{
			lv_textarea_set_text(obj, "");
			lv_textarea_set_cursor_pos(obj, 0);
			(input_index) = 0;
		}
	}
}

/************************************************************
** 函数说明: 
** 作者: xiaoxiao
** 日期: 2023-05-12 10:15:00
** 参数说明: 
** 注意事项: 
************************************************************/
static void logo_num_keyboard_event(lv_event_t *e)
{

	lv_obj_t *obj = lv_event_get_target(e);
	uint32_t id = lv_btnmatrix_get_selected_btn(obj);

        lv_obj_t *ta = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),logo_obj_id_tuya_register_textarea);

        if (id == 11)
        {
               lv_textarea_del_char(ta);
        }else if (id == 9)
        {
               layout_logo_ok_btn_up(obj);
        }
        else
        {
                const char *text = lv_btnmatrix_get_btn_text(obj, id);

                if (text != NULL)
                {

                        lv_textarea_add_text(ta,text);
                }
        }
}

/************************************************************
** 函数说明: 序号键盘输入创建
** 作者: xiaoxiao
** 日期: 2023-05-12 10:04:53
** 参数说明: 
** 注意事项: 
************************************************************/
static void layout_logo_input_keyboard_create(void)
{
        lv_obj_t * kb = lv_common_number_input_keyboard_create(sat_cur_layout_screen_get(), logo_obj_id_tuya_register_number_keyboard_btn, 389, 229, 230, 371,
                                                logo_num_keyboard_event, LV_OPA_COVER, 0X101010, LV_OPA_COVER, 0x00a8ff,
                                                360, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                360, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                0XFFFFFF, 0XFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large,
                                                13, 22);
        static const char *btnm_map[] = {
        "1", "2", "3", "\n",
        "4", "5", "6", "\n",
        "7", "8", "9", "\n",
        "OK", "0", " ", "\n", ""};


        lv_btnmatrix_set_map(kb, btnm_map);
}

static void sat_layout_enter(logo)
{
        lv_common_video_mode_enable(false);



        lv_common_text_create(sat_cur_layout_screen_get(), logo_obj_id_model_label, 559, 550, 200, 33,
                              NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                              "Model:CIP-710QPT", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_RIGHT, NULL);

        lv_common_text_create(sat_cur_layout_screen_get(), logo_obj_id_version_label, 863, 550, 135, 33,
                              NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                              SYSTEM_VERSION, 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_RIGHT, NULL);

        lv_obj_pressed_func = lv_layout_touch_callback;


	if (tuya_key_and_uuid_init() == false)
	{
		logo_serial_numbe_txt_create();
		layout_logo_input_txt_create();
                layout_logo_input_keyboard_create();
	}
	else
	{
                lv_common_img_btn_create(sat_cur_layout_screen_get(), logo_obj_id_logo_img, 0, 0, 1024, 600, // 273, 235, 486, 130,
                                NULL, false, LV_OPA_COVER, 0, LV_OPA_TRANSP, 0,
                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                resource_ui_src_get("ic_logo.png"), LV_OPA_TRANSP, 0, LV_ALIGN_CENTER);
		lv_sat_timer_create(logo_enter_system_timer, 1000, NULL);
	}


}

static void sat_layout_quit(logo)
{
}

sat_layout_create(logo);
