#include "layout_define.h"
#include "layout_setting_standby_screen.h"
#include "layout_setting_screen.h"
#include "layout_setting_general.h"
enum
{
        setting_standby_screen_obj_id_title,
        setting_standby_screen_obj_id_cancel,

        setting_standby_screen_obj_id_mian_list,
        setting_standby_screen_obj_id_screen_off_cont,
        setting_standby_screen_obj_id_screen_off_title,
        setting_standby_screen_obj_id_screen_off_sub,
        setting_standby_screen_obj_id_screen_off_img,
        setting_standby_screen_obj_id_open_frame_cont,
        setting_standby_screen_obj_id_open_frame_title,
        setting_standby_screen_obj_id_open_frame_img,

        setting_standby_screen_obj_id_sub_list,
        setting_standby_screen_obj_id_display_time_cont,
        setting_standby_screen_obj_id_display_time_title,
        setting_standby_screen_obj_id_display_time_sub,
        setting_standby_screen_obj_id_display_night_mode_cont,
        setting_standby_screen_obj_id_display_night_mode_title,
        setting_standby_screen_obj_id_display_night_mode_sub,
        setting_standby_screen_obj_id_display_item_cont,
        setting_standby_screen_obj_id_display_item_title,
        setting_standby_screen_obj_id_display_item_sub,
        setting_standby_screen_obj_id_background_cont,
        setting_standby_screen_obj_id_background_title,
        setting_standby_screen_obj_id_background_sub,
};

static void setting_standby_screen_cancel_click(lv_event_t *e)
{
        sat_layout_goto(setting_screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
}
static void setting_standby_screen_main_checkbox_obj_display(void)
{
        lv_obj_t *list = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_standby_screen_obj_id_mian_list);
        if (list == NULL)
        {
                return;
        }
        lv_obj_t *item = lv_obj_get_child_form_id(list, setting_standby_screen_obj_id_screen_off_cont);
        if (item == NULL)
        {
                return;
        }
        lv_obj_t *scr_of_img = lv_obj_get_child_form_id(item, setting_standby_screen_obj_id_screen_off_img);
        if (scr_of_img == NULL)
        {
                return;
        }

        item = lv_obj_get_child_form_id(list, setting_standby_screen_obj_id_open_frame_cont);
        lv_obj_t *frame_open_img = lv_obj_get_child_form_id(item, setting_standby_screen_obj_id_open_frame_img);
        if (frame_open_img == NULL)
        {
                return;
        }

        lv_obj_t *sub_list = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_standby_screen_obj_id_sub_list);
        if (sub_list == NULL)
        {
                return;
        }

        if (user_data_get()->display.standby_mode == 0)
        {
                lv_obj_set_style_bg_img_src(scr_of_img, resource_ui_src_get("btn_radio_s.png"), LV_PART_MAIN);
                lv_obj_set_style_bg_img_src(frame_open_img, resource_ui_src_get("btn_radio_n.png"), LV_PART_MAIN);

                lv_obj_add_flag(sub_list, LV_OBJ_FLAG_HIDDEN);
        }
        else
        {
                lv_obj_set_style_bg_img_src(frame_open_img, resource_ui_src_get("btn_radio_s.png"), LV_PART_MAIN);
                lv_obj_set_style_bg_img_src(scr_of_img, resource_ui_src_get("btn_radio_n.png"), LV_PART_MAIN);

                lv_obj_clear_flag(sub_list, LV_OBJ_FLAG_HIDDEN);
        }
}

static void setting_standby_screen_main_list_click(lv_event_t *e)
{
        lv_obj_t *item = lv_event_get_current_target(e);
        if (item == NULL)
        {
                return;
        }
        if (item->id == setting_standby_screen_obj_id_screen_off_cont)
        {
                if (user_data_get()->display.standby_mode != 0)
                {
                        user_data_get()->display.standby_mode = 0;
                        user_data_save();
                        setting_standby_screen_main_checkbox_obj_display();
                }
        }
        else if (user_data_get()->display.standby_mode == 0)
        {
                user_data_get()->display.standby_mode = 1;
                user_data_save();
                setting_standby_screen_main_checkbox_obj_display();
        }
}
static lv_obj_t *setting_standby_screen_main_list_create(void)
{
        setting_list_info_t main_list_group[] = {

            {0, 0, 928, 88,
             setting_standby_screen_obj_id_screen_off_cont, setting_standby_screen_obj_id_screen_off_title, setting_standby_screen_obj_id_screen_off_sub,
             SETTING_STANDBY_SCREEN_LANG_ID_SCREEN_OFF, layout_setting_standby_screen_language_get,
             SCREEN_LANG_ID_LCD_SCREEN_AFTER_15SEC, layout_setting_screen_language_get,
             setting_standby_screen_main_list_click, setting_standby_screen_obj_id_screen_off_img},
            {0, 88, 928, 88,
             setting_standby_screen_obj_id_open_frame_cont, setting_standby_screen_obj_id_open_frame_title, -1,
             SETTING_STANDBY_SCREEN_LANG_ID_OPEN_FRAME, layout_setting_standby_screen_language_get,
             -1, NULL,
             setting_standby_screen_main_list_click,
             setting_standby_screen_obj_id_open_frame_img}};

        lv_obj_t *list = setting_list_create(sat_cur_layout_screen_get(), setting_standby_screen_obj_id_mian_list);
        lv_common_style_set_common(list, setting_standby_screen_obj_id_mian_list, 48, 88, 928, 512, LV_ALIGN_TOP_LEFT, LV_PART_MAIN);

        for (int i = 0; i < sizeof(main_list_group) / sizeof(setting_list_info_t); i++)
        {
                lv_common_setting_btn_title_sub_info_img_create(list, main_list_group[i].cont_id, main_list_group[i].x, main_list_group[i].y, main_list_group[i].w, main_list_group[i].h,
                                                                main_list_group[i].click_cb, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                                42, 25, 576, 43, main_list_group[i].title_id,
                                                                main_list_group[i].title_language_id == -1 ? NULL : main_list_group[i].title_language_cb(main_list_group[i].title_language_id), 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                42, 52, 576, 29, main_list_group[i].sub_id,
                                                                main_list_group[i].sub_language_id == -1 ? NULL : main_list_group[i].sub_language_cb(main_list_group[i].sub_language_id), 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                0, 0, 0, 0, -1,
                                                                NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                0, 28, 32, 32, main_list_group[i].img_id,
                                                                resource_ui_src_get("btn_radio_n.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }
        return list;
}
static void setting_standby_screen_sub_list_click(lv_event_t *e)
{
        lv_obj_t *obj = lv_event_get_current_target(e);
        if (obj == NULL)
        {
                return;
        }
        if (obj->id == setting_standby_screen_obj_id_display_time_cont)
        {
                sat_layout_goto(setting_frame_display_time, LV_SCR_LOAD_ANIM_MOVE_LEFT, SAT_VOID);
        }
        else if (obj->id == setting_standby_screen_obj_id_display_night_mode_cont)
        {
                sat_layout_goto(setting_frame_night_mode, LV_SCR_LOAD_ANIM_MOVE_LEFT, SAT_VOID);
        }
        else if (obj->id == setting_standby_screen_obj_id_display_item_cont)
        {
                sat_layout_goto(setting_frame_item, LV_SCR_LOAD_ANIM_MOVE_LEFT, SAT_VOID);
        }
        else if (obj->id == setting_standby_screen_obj_id_background_cont)
        {
                sat_layout_goto(setting_frame_backgorund, LV_SCR_LOAD_ANIM_MOVE_LEFT, SAT_VOID);
        }
}
static lv_obj_t *setting_standby_screen_sub_list_create(void)
{
        setting_list_info_t main_list_group[] = {

            {0, 0, 836, 72,
             setting_standby_screen_obj_id_display_time_cont, setting_standby_screen_obj_id_display_time_title, setting_standby_screen_obj_id_display_time_sub,
             SETTING_STANDBY_SCREEN_LANG_ID_DISPLAY_TIME, layout_setting_standby_screen_language_get,
             SETTING_STANDBY_SCREEN_LANG_ID_ALWAYS, layout_setting_standby_screen_language_get,
             setting_standby_screen_sub_list_click},
            {0, 72, 836, 72,
             setting_standby_screen_obj_id_display_night_mode_cont, setting_standby_screen_obj_id_display_night_mode_title, setting_standby_screen_obj_id_display_night_mode_sub,
             SETTING_STANDBY_SCREEN_LANG_ID_USER_NIGHT_MODE, layout_setting_standby_screen_language_get,
             SETTING_STANDBY_SCREEN_LANG_ID_ADJUSTS_THE_BRIGHTNESS, layout_setting_standby_screen_language_get,
             setting_standby_screen_sub_list_click},
            {0, 72 * 2, 836, 72,
             setting_standby_screen_obj_id_display_item_cont, setting_standby_screen_obj_id_display_item_title, setting_standby_screen_obj_id_display_item_sub,
             SETTING_STANDBY_SCREEN_LANG_ID_ITEM_DISPLAY, layout_setting_standby_screen_language_get,
             SETTING_STANDBY_SCREEN_LANG_ID_1_ITEM, layout_setting_standby_screen_language_get,
             setting_standby_screen_sub_list_click},
            {0, 72 * 3, 836, 72,
             setting_standby_screen_obj_id_background_cont, setting_standby_screen_obj_id_background_title, setting_standby_screen_obj_id_background_sub,
             SETTING_STANDBY_SCREEN_LANG_ID_BACKROUND, layout_setting_standby_screen_language_get,
             SETTING_STANDBY_SCREEN_LANG_ID_RANDOM_IMAGE, layout_setting_standby_screen_language_get,
             setting_standby_screen_sub_list_click},
        };

        lv_obj_t *list = setting_list_create(sat_cur_layout_screen_get(), setting_standby_screen_obj_id_sub_list);
        lv_common_style_set_common(list, setting_standby_screen_obj_id_sub_list, 94, 264, 836, 314, LV_ALIGN_TOP_LEFT, LV_PART_MAIN);

        for (int i = 0; i < sizeof(main_list_group) / sizeof(setting_list_info_t); i++)
        {
                lv_common_setting_btn_title_sub_info_img_create(list, main_list_group[i].cont_id, main_list_group[i].x, main_list_group[i].y, main_list_group[i].w, main_list_group[i].h,
                                                                main_list_group[i].click_cb, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                                0, 17, 576, 43, main_list_group[i].title_id,
                                                                main_list_group[i].title_language_id == -1 ? NULL : main_list_group[i].title_language_cb(main_list_group[i].title_language_id), 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                0, 42, 576, 29, main_list_group[i].sub_id,
                                                                main_list_group[i].sub_language_id == -1 ? NULL : main_list_group[i].sub_language_cb(main_list_group[i].sub_language_id), 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                0, 0, 0, 0, -1,
                                                                NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                0, 0, 0, 0, -1,
                                                                NULL, LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }
        return list;
}
static void sat_layout_enter(setting_standby_screen)
{
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-3 14:13:25
         ** 说明: 标题创建
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_standby_screen_obj_id_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      layout_setting_screen_language_get(SCREEN_LANG_ID_LCD_STANDBY_SCREEN), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-3 14:13:25
        ** 说明: 返回按钮
        ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_standby_screen_obj_id_cancel, 35, 15, 48, 48,
                                         setting_standby_screen_cancel_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-3 14:13:25
         ** 说明: 主列表创建
         ***********************************************/
        {
                setting_standby_screen_main_list_create();
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-3 14:13:25
         ** 说明: 子列表创建
         ***********************************************/
        {
                setting_standby_screen_sub_list_create();
        }

        setting_standby_screen_main_checkbox_obj_display();
}
static void sat_layout_quit(setting_standby_screen)
{
}

sat_layout_create(setting_standby_screen);