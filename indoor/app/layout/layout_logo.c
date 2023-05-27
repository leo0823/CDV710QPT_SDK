

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

enum
{
        logo_obj_id_logo_img,
        logo_obj_id_model_label,
        logo_obj_id_version_label
};

static void logo_enter_system_timer(lv_timer_t *t)
{
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-1-5 17:17:15
         ** 说明: 网络初始化
         ***********************************************/
        user_network_init();

        /*****  tuya api初始化 *****/
        tuya_api_init(TUYA_PID);
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
        ** 日期: 2023-1-5 10:6:36
        ** 说明: linphone 初始化
        ***********************************************/
        user_linphone_init();

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-1-5 10:6:36
         ** 说明: linphone 初始化
         ***********************************************/
        user_gpio_init();
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-1-5 10:6:36
         ** 说明:暂时放在连接wifi
         ***********************************************/
        wifi_device_conneting();
        if (user_data_get()->wifi_enable)
        {
                wifi_device_open();
        }
        else
        {
                wifi_device_close();
        }

        tuya_event_cmd_register(tuya_event_defalut_handle);
        if (0) //(user_data_get()->is_device_init == false)
        {
                sat_layout_goto(power_setting, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
        }
        else
        {
                audio_output_cmd_register(audio_output_event_default_process);
                user_linphone_call_incoming_received_register(monitor_doorcamera_call_extern_func);
                sat_layout_goto(home, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
        }
}

static void sat_layout_enter(logo)
{
        lv_common_video_mode_enable(false);
        if (tuya_key_and_uuid_init() == false)
        {
                // goto enter input
                tuya_key_and_key_xls_register(1);
        }
        else
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), logo_obj_id_logo_img, 0, 0, 1024, 600, // 273, 235, 486, 130,
                                         NULL, false, LV_OPA_COVER, 0, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("ic_logo.png"), LV_OPA_TRANSP, 0, LV_ALIGN_CENTER);

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

                lv_sat_timer_create(logo_enter_system_timer, 1000, NULL);
        }
}

static void sat_layout_quit(logo)
{
}

sat_layout_create(logo);
