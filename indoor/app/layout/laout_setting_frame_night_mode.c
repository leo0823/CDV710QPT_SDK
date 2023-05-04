#include "layout_define.h"
#include "layout_setting_frame_display_time.h"
#include "layout_setting_standby_screen.h"
#include "layout_setting_general.h"
#include "layout_setting_screen.h"
enum
{
        setting_frame_night_mode_obj_id_title,
        setting_frame_night_mode_obj_id_cancel,

        setting_frame_night_mode_obj_id_list,
        setting_frame_night_mode_obj_id_use_night_mode_cont,
        setting_frame_night_mode_obj_id_use_night_mode_title,
        setting_frame_night_mode_obj_id_use_night_mode_sub,
        setting_frame_night_mode_obj_id_use_night_mode_img,

        setting_frame_night_mode_obj_id_setting_time_cont,

        setting_frame_night_mode_obj_id_roller_start_hour,
        setting_frame_night_mode_obj_id_rolle_start_minr,
        setting_frame_night_mode_obj_id_roller_end_hour,
        setting_frame_night_mode_obj_id_roller_end_min,

        setting_frame_night_mode_obj_id_roller_1_obj,
        setting_frame_night_mode_obj_id_roller_2_obj,
        setting_frame_night_mode_obj_id_roller_3_obj,

};

static void setting_frame_night_mode_obj_cancel_click(lv_event_t *e)
{
        sat_layout_goto(setting_standby_screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
}

static void setting_frame_night_mode_checkbox_obj_display(void)
{
        lv_obj_t *list = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_frame_night_mode_obj_id_list);
        if (list == NULL)
        {
                return;
        }
        lv_obj_t *item = lv_obj_get_child_form_id(list, setting_frame_night_mode_obj_id_use_night_mode_cont);
        if (item == NULL)
        {
                return;
        }
        lv_obj_t *scr_of_img = lv_obj_get_child_form_id(item, setting_frame_night_mode_obj_id_use_night_mode_img);
        if (scr_of_img == NULL)
        {
                return;
        }

        lv_obj_t *sub_list = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_frame_night_mode_obj_id_setting_time_cont);
        if (sub_list == NULL)
        {
                return;
        }

        if (user_data_get()->display.night_mode == 0)
        {
                lv_obj_set_style_bg_img_src(scr_of_img, resource_ui_src_get("btn_switch_off.png"), LV_PART_MAIN);
                lv_obj_add_flag(sub_list, LV_OBJ_FLAG_HIDDEN);
        }
        else
        {
                lv_obj_set_style_bg_img_src(scr_of_img, resource_ui_src_get("btn_switch_on.png"), LV_PART_MAIN);
                lv_obj_clear_flag(sub_list, LV_OBJ_FLAG_HIDDEN);
        }
}
static void setting_frame_night_mode_obj_list_click(lv_event_t *e)
{
        lv_obj_t *item = lv_event_get_current_target(e);
        if (item == NULL)
        {
                return;
        }

        user_data_get()->display.night_mode = user_data_get()->display.night_mode == 0 ? 1 : 0;
        user_data_save();
        setting_frame_night_mode_checkbox_obj_display();
}
static void setting_frame_night_mode_obj_slider(lv_event_t *e)
{
}
static void sat_layout_enter(setting_frame_night_mode)
{
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-3 14:13:25
         ** 说明: 标题创建
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_frame_night_mode_obj_id_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      layout_setting_standby_screen_language_get(SETTING_STANDBY_SCREEN_LANG_ID_NIGHT_MODE), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-3 14:13:25
        ** 说明: 返回按钮
        ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_frame_night_mode_obj_id_cancel, 35, 15, 48, 48,
                                         setting_frame_night_mode_obj_cancel_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-3 14:13:25
         ** 说明: 主列表
         ***********************************************/
        {
                setting_list_info_t main_list_group[] = {

                    {0, 0, 928, 88,
                     setting_frame_night_mode_obj_id_use_night_mode_cont, setting_frame_night_mode_obj_id_use_night_mode_title, setting_frame_night_mode_obj_id_use_night_mode_sub,
                     SETTING_STANDBY_SCREEN_LANG_ID_USER_NIGHT_MODE, layout_setting_standby_screen_language_get,
                     SETTING_STANDBY_SCREEN_LANG_ID_ADJUSTS_THE_BRIGHTNESS, layout_setting_standby_screen_language_get,
                     setting_frame_night_mode_obj_list_click, setting_frame_night_mode_obj_id_use_night_mode_img},
                };

                lv_obj_t *list = setting_list_create(sat_cur_layout_screen_get(), setting_frame_night_mode_obj_id_list);
                lv_common_style_set_common(list, setting_frame_night_mode_obj_id_list, 48, 88, 928, 512, LV_ALIGN_TOP_LEFT, LV_PART_MAIN);

                for (int i = 0; i < sizeof(main_list_group) / sizeof(setting_list_info_t); i++)
                {
                        lv_common_setting_btn_title_sub_info_img_create(list, main_list_group[i].cont_id, main_list_group[i].x, main_list_group[i].y, main_list_group[i].w, main_list_group[i].h,
                                                                        main_list_group[i].click_cb, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                                        0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                                        0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                                        0, 25, 576, 43, main_list_group[i].title_id,
                                                                        main_list_group[i].title_language_id == -1 ? NULL : main_list_group[i].title_language_cb(main_list_group[i].title_language_id), 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                        0, 52, 576, 29, main_list_group[i].sub_id,
                                                                        main_list_group[i].sub_language_id == -1 ? NULL : main_list_group[i].sub_language_cb(main_list_group[i].sub_language_id), 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                        0, 0, 0, 0, -1,
                                                                        NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                        840, 20, 80, 48, main_list_group[i].img_id,
                                                                        resource_ui_src_get("btn_switch_on.png"), LV_OPA_50, 0x00a8ff, LV_ALIGN_CENTER);
                }
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-3 14:13:25
         ** 说明: slider
         ***********************************************/
        {
                lv_obj_t *parent = lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_frame_night_mode_obj_id_setting_time_cont, 215, 275, 596, 201,
                                                            NULL, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                                            0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                            0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                            NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

                lv_common_roller_create(parent, setting_frame_night_mode_obj_id_roller_start_hour, 0, 0, 104, 201,
                                        setting_frame_night_mode_obj_slider, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x323237,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x00a8ff,
                                        3, 30, 0, 23, 0x303030, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal,
                                        resource_ui_src_get("roller_icon.png"));

                lv_common_text_create(parent, setting_frame_night_mode_obj_id_roller_1_obj, 104, 78, 36, 72,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      ":", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);

                lv_common_roller_create(parent, setting_frame_night_mode_obj_id_rolle_start_minr, 140, 0, 104, 201,
                                        setting_frame_night_mode_obj_slider, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x323237,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x00a8ff,
                                        3, 30, 0, 59, 0x303030, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal,
                                        resource_ui_src_get("roller_icon.png"));

                lv_common_text_create(parent, setting_frame_night_mode_obj_id_roller_2_obj, 280, 78, 36, 72,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      "-", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);

                lv_common_roller_create(parent, setting_frame_night_mode_obj_id_roller_end_hour, 352, 0, 104, 201,
                                        setting_frame_night_mode_obj_slider, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x323237,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x00a8ff,
                                        3, 30, 0, 23, 0x303030, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal,
                                        resource_ui_src_get("roller_icon.png"));

                lv_common_text_create(parent, setting_frame_night_mode_obj_id_roller_3_obj, 456, 78, 36, 72,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      ":", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);

                lv_common_roller_create(parent, setting_frame_night_mode_obj_id_roller_end_min, 492, 0, 104, 201,
                                        setting_frame_night_mode_obj_slider, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x323237,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x00a8ff,
                                        3, 30, 0, 59, 0x303030, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal,
                                        resource_ui_src_get("roller_icon.png"));
        }

        setting_frame_night_mode_checkbox_obj_display();
}

static void sat_layout_quit(setting_frame_night_mode)
{
}

sat_layout_create(setting_frame_night_mode);