#include "layout_define.h"
#include "layout_setting_complete.h"
#include "layout_monitor.h"
enum
{
        setting_complete_obj_id_title,
        setting_complete_obj_id_cancel,
        setting_complete_obj_id_start_setting,
        setting_complete_obj_id_confirm
};
static void setting_complete_cancel_click(lv_event_t *ev)
{
        sat_layout_goto(ipc_camera_register, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
}
static void setting_complete_confirm_click(lv_event_t *ev)
{
        /************************************************************
         ** 函数说明: 待机初始化
        ** 作者: xiaoxiao
        ** 日期: 2023-05-19 15:21:05
        ** 参数说明:
        ** 注意事项:
        ************************************************************/
        standby_timer_init(sat_playout_get(close), user_data_get()->display.screen_off_time * 1000);
        standby_timer_restart(true);
        extern void standby_dection_timer(lv_timer_t *t);
        lv_timer_t *standby_timer = lv_timer_create(standby_dection_timer, 1000, NULL);
        lv_timer_ready(standby_timer);
        user_data_get()->is_device_init = 1;
        user_data_save();

        audio_output_cmd_register(audio_output_event_default_process);
        user_linphone_call_incoming_received_register(monitor_doorcamera_call_extern_func);
        sat_layout_goto(home, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
}

static void sat_layout_enter(setting_complete)
{
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明: 标题显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_complete_obj_id_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      layout_complete_language_get(SETTING_COMPLETE_LANG_ID_SETTING_COMPLETE), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 上一步下一步
         ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_complete_obj_id_cancel, 35, 15, 48, 48,
                                         setting_complete_cancel_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
        }

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:51:30
        ** 说明: 欢迎开始使用
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_complete_obj_id_start_setting, 68, 164, 888, 70,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      layout_complete_language_get(SETTING_COMPLETE_LANG_ID_START_SETTING_IS_COMPLETE), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_normal);
        }

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: 标题显示
         ***********************************************/
        {
                lv_obj_t *obj = lv_common_text_create(sat_cur_layout_screen_get(), setting_complete_obj_id_confirm, 0, 528, 1024, 72,
                                                      setting_complete_confirm_click, LV_OPA_COVER, 0X00A8FF, LV_OPA_COVER, 0X00A8FF,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      language_common_string_get(LANG_COMMON_ID_CONFIRM), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
                lv_obj_set_style_pad_top(obj, 15, LV_PART_MAIN);
        }
}
static void sat_layout_quit(setting_complete)
{
}

sat_layout_create(setting_complete);