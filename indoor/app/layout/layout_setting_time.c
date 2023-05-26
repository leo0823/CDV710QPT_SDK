#include "layout_define.h"
#include "layout_setting_time.h"
#include "layout_ipc_camera.h"
enum
{
        setting_time_obj_id_title,
        setting_time_obj_id_cancel,
        setting_time_obj_id_next,

        setting_time_obj_id_setting_cont,
        setting_time_obj_id_setting_title,
        setting_time_obj_id_setting_sub,
        setting_time_obj_id_setting_img,

        setting_time_obj_id_year_roller,
        setting_time_obj_id_month_roller,
        setting_time_obj_id_day_roller,
        setting_time_obj_id_hour_roller,
        setting_time_obj_id_min_roller,
        setting_time_obj_id_sec_roller,

        setting_time_obj_id_1_obj,
        setting_time_obj_id_2_obj,
        setting_time_obj_id_3_obj,
        setting_time_obj_id_4_obj
};
// 0x00:first 0x01:home 0x03:setting
static char setting_timer_layout_first_enter_flag = 0x00;
void setting_time_first_enter_set_flag(char isfirst)
{
        setting_timer_layout_first_enter_flag = isfirst;
}
static void setting_time_cancel_click(lv_event_t *ev)
{
        if (setting_timer_layout_first_enter_flag == 0x00)
        {
                sat_layout_goto(setting_wifi, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
        }
        else if (setting_timer_layout_first_enter_flag == 0x01)
        {
                sat_layout_goto(home, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, SAT_VOID);
        }
        else
        {
                sat_layout_goto(setting_general, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
        }
}
static void setting_time_next_click(lv_event_t *ev)
{
        layout_ipc_cmeara_is_doorcamera_set(true);
        sat_layout_goto(ipc_camera_register, LV_SCR_LOAD_ANIM_MOVE_LEFT, SAT_VOID);
}
static void setting_time_set_date_automatically_enable_display(lv_obj_t *obj)
{
        if (user_data_get()->time_automatically == true)
        {
                lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_switch_on.png"), LV_PART_MAIN);
        }
        else
        {
                lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_switch_off.png"), LV_PART_MAIN);
        }
}
static void setting_time_set_date_automatically_click(lv_event_t *ev)
{
        lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_time_obj_id_setting_cont);
        lv_obj_t *img = lv_obj_get_child_form_id(parent, setting_time_obj_id_setting_img);

        user_data_get()->time_automatically = user_data_get()->time_automatically ? false : true;
        user_data_save();
        setting_time_set_date_automatically_enable_display(img);
}
static void setting_time_set_roller_click(lv_event_t *ev)
{
}
static void sat_layout_enter(setting_time)
{
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明: 标题显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_time_obj_id_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      layout_setting_time_language_get(SETTING_TIME_ID_DATE_TIME), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 上一步下一步
         ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_time_obj_id_cancel, 35, 15, 48, 48,
                                         setting_time_cancel_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);

                if (setting_timer_layout_first_enter_flag == 0x00)
                {
                        lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_time_obj_id_next, 952, 15, 48, 48,
                                                 setting_time_next_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 resource_ui_src_get("btn_title_next.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
                }
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:50
         ** 说明: 设置按钮创建
         ***********************************************/
        {
                lv_obj_t *parent = lv_common_setting_btn_title_sub_info_img_create(sat_cur_layout_screen_get(), setting_time_obj_id_setting_cont, 48, 80, 928, 88,
                                                                                   setting_time_set_date_automatically_click, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                                                   0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                                                   0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                                                   0, 8, 838, 50, setting_time_obj_id_setting_title,
                                                                                   layout_setting_time_language_get(SETTING_TIME_ID_SET_DATE_AND_TIME), 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                                   0, 45, 838, 50, setting_time_obj_id_setting_sub,
                                                                                   layout_setting_time_language_get(SETTING_TIME_ID_THE_TIME_IS_SET_AUTOMATICALLY), 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                                   0, 0, 0, 0, -1,
                                                                                   NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                                   840, 20, 80, 48, setting_time_obj_id_setting_img,
                                                                                   resource_ui_src_get("btn_switch_on.png"), LV_OPA_50, 0x00a8ff, LV_ALIGN_CENTER);

                lv_obj_t *obj = lv_obj_get_child_form_id(parent, setting_time_obj_id_setting_img);
                setting_time_set_date_automatically_enable_display(obj);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:50
         ** 说明: year roller
         ***********************************************/
        {
                lv_common_roller_create(sat_cur_layout_screen_get(), setting_time_obj_id_year_roller, 110, 275, 104, 201,
                                        setting_time_set_roller_click, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x323237,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x00a8ff,
                                        3, 30, 2023, 2037, 0x303030, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal,
                                        resource_ui_src_get("roller_icon.png"));
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: -
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_time_obj_id_1_obj, 214, 355, 36, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      "-", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:50
         ** 说明: montth roller
         ***********************************************/
        {
                lv_common_roller_create(sat_cur_layout_screen_get(), setting_time_obj_id_month_roller, 250, 275, 104, 201,
                                        setting_time_set_roller_click, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x323237,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x00a8ff,
                                        3, 30, 1, 12, 0x303030, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal,
                                        resource_ui_src_get("roller_icon.png"));
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: -
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_time_obj_id_2_obj, 354, 355, 36, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      "-", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:50
        ** 说明: day roller
        ***********************************************/
        {
                lv_common_roller_create(sat_cur_layout_screen_get(), setting_time_obj_id_day_roller, 390, 275, 104, 201,
                                        setting_time_set_roller_click, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x323237,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x00a8ff,
                                        3, 30, 1, 31, 0x303030, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal,
                                        resource_ui_src_get("roller_icon.png"));
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: -
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_time_obj_id_3_obj, 638, 355, 36, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      ":", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:50
         ** 说明: hour roller
         ***********************************************/
        {
                lv_common_roller_create(sat_cur_layout_screen_get(), setting_time_obj_id_hour_roller, 534, 275, 104, 201,
                                        setting_time_set_roller_click, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x323237,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x00a8ff,
                                        3, 30, 0, 23, 0x303030, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal,
                                        resource_ui_src_get("roller_icon.png"));
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: -
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_time_obj_id_4_obj, 778, 355, 36, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      ":", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:50
         ** 说明: min roller
         ***********************************************/
        {
                lv_common_roller_create(sat_cur_layout_screen_get(), setting_time_obj_id_min_roller, 674, 275, 104, 201,
                                        setting_time_set_roller_click, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x323237,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x00a8ff,
                                        3, 30, 0, 59, 0x303030, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal,
                                        resource_ui_src_get("roller_icon.png"));
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:50
        ** 说明: sec roller
        ***********************************************/
        {
                lv_common_roller_create(sat_cur_layout_screen_get(), setting_time_obj_id_sec_roller, 814, 275, 104, 201,
                                        setting_time_set_roller_click, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x323237,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x00a8ff,
                                        3, 30, 0, 59, 0x303030, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal,
                                        resource_ui_src_get("roller_icon.png"));
        }
}
static void sat_layout_quit(setting_time)
{
}

sat_layout_create(setting_time);