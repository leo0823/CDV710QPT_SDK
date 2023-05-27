#include "layout_define.h"
#include "layout_setting_version_information.h"
#include "layout_setting_sound.h"
#include "layout_setting_general.h"
enum
{
        setting_volume_obj_id_title,
        setting_volume_obj_id_cancel,

        setting_volume_obj_id_list,

        setting_volume_obj_id_buzzer_cont,
        setting_volume_obj_id_buzzer_label,
        setting_volume_obj_id_buzzer_volume_img,
        setting_volume_obj_id_buzzer_volume_slider_cont,
        setting_volume_obj_id_buzzer_volume_slider_text,
        setting_volume_obj_id_buzzer_volume_slider_left_btn,
        setting_volume_obj_id_buzzer_volume_slider_right_btn,
        setting_volume_obj_id_buzzer_volume_slider,

        setting_volume_obj_id_entrance_cont,
        setting_volume_obj_id_entrance_label,
        setting_volume_obj_id_entrance_volume_img,
        setting_volume_obj_id_entrance_volume_slider_cont,
        setting_volume_obj_id_entrance_volume_slider_text,
        setting_volume_obj_id_entrance_volume_slider_left_btn,
        setting_volume_obj_id_entrance_volume_slider_right_btn,
        setting_volume_obj_id_entrance_volume_slider,
        setting_volume_obj_id_entrance_voice_img,
        setting_volume_obj_id_entrance_voice_slider_cont,
        setting_volume_obj_id_entrance_voice_slider_text,
        setting_volume_obj_id_entrance_voice_slider_left_btn,
        setting_volume_obj_id_entrance_voice_slider_right_btn,
        setting_volume_obj_id_entrance_voice_slider,

        setting_volume_obj_id_common_entrance_cont,
        setting_volume_obj_id_common_entrance_label,
        setting_volume_obj_id_common_entrance_volume_img,
        setting_volume_obj_id_common_entrance_volume_slider_cont,
        setting_volume_obj_id_common_entrance_volume_slider_text,
        setting_volume_obj_id_common_entrance_volume_slider_left_btn,
        setting_volume_obj_id_common_entrance_volume_slider_right_btn,
        setting_volume_obj_id_common_entrance_volume_slider,
        setting_volume_obj_id_common_entrance_voice_img,
        setting_volume_obj_id_common_entrance_voice_slider_cont,
        setting_volume_obj_id_common_entrance_voice_slider_text,
        setting_volume_obj_id_common_entrance_voice_slider_left_btn,
        setting_volume_obj_id_common_entrance_voice_slider_right_btn,
        setting_volume_obj_id_common_entrance_voice_slider,

        setting_volume_obj_id_guard_station_cont,
        setting_volume_obj_id_guard_station_label,
        setting_volume_obj_id_guard_station_volume_img,
        setting_volume_obj_id_guard_station_volume_slider_cont,
        setting_volume_obj_id_guard_station_volume_slider_text,
        setting_volume_obj_id_guard_station_volume_slider_left_btn,
        setting_volume_obj_id_guard_station_volume_slider_right_btn,
        setting_volume_obj_id_guard_station_volume_slider,
        setting_volume_obj_id_guard_station_voice_img,
        setting_volume_obj_id_guard_station_voice_slider_cont,
        setting_volume_obj_id_guard_station_voice_slider_text,
        setting_volume_obj_id_guard_station_voice_slider_left_btn,
        setting_volume_obj_id_guard_station_voice_slider_right_btn,
        setting_volume_obj_id_guard_station_voice_slider,

        setting_volume_obj_id_extension_cont,
        setting_volume_obj_id_extension_label,
        setting_volume_obj_id_extension_volume_img,
        setting_volume_obj_id_extension_volume_slider_cont,
        setting_volume_obj_id_extension_volume_slider_text,
        setting_volume_obj_id_extension_volume_slider_left_btn,
        setting_volume_obj_id_extension_volume_slider_right_btn,
        setting_volume_obj_id_extension_volume_slider,
        setting_volume_obj_id_extension_voice_img,
        setting_volume_obj_id_extension_voice_slider_cont,
        setting_volume_obj_id_extension_voice_slider_text,
        setting_volume_obj_id_extension_voice_slider_left_btn,
        setting_volume_obj_id_extension_voice_slider_right_btn,
        setting_volume_obj_id_extension_voice_slider,

        setting_volume_obj_id_touch_notification_cont,
        setting_volume_obj_id_touch_notification_label,
        setting_volume_obj_id_touch_notification_volume_img,
        setting_volume_obj_id_touch_notification_volume_slider_cont,
        setting_volume_obj_id_touch_notification_volume_slider_text,
        setting_volume_obj_id_touch_notification_volume_slider_left_btn,
        setting_volume_obj_id_touch_notification_volume_slider_right_btn,
        setting_volume_obj_id_touch_notification_volume_slider,
        setting_volume_obj_id_touch_notification_voice_img,
        setting_volume_obj_id_touch_notification_voice_slider_cont,
        setting_volume_obj_id_touch_notification_voice_slider_text,
        setting_volume_obj_id_touch_notification_voice_slider_left_btn,
        setting_volume_obj_id_touch_notification_voice_slider_right_btn,
        setting_volume_obj_id_touch_notification_voice_slider,
};
static void setting_volume_cancel_obj_click(lv_event_t *e)
{
        sat_layout_goto(setting_sound, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
}

static void setting_volume_slider_change_cb(lv_event_t *e)
{
}
static lv_obj_t *setting_volume_slider_obj_create(void)
{
        setting_list_info_t main_list_group[] = {

            {0, 0, 970, 70, setting_volume_obj_id_buzzer_cont, setting_volume_obj_id_buzzer_label, -1, SOUND_LANG_ID_BUZZER, layout_setting_sound_language_get, -1, NULL, NULL, -1},
            {0, 70, 970, 140, setting_volume_obj_id_entrance_cont, setting_volume_obj_id_entrance_label, -1, SOUND_LANG_ID_ENTRANCE, layout_setting_sound_language_get, -1, NULL, NULL, -1},
            {0, 70 + 140, 970, 140, setting_volume_obj_id_common_entrance_cont, setting_volume_obj_id_common_entrance_label, -1, SOUND_LANG_ID_COMMON_ENTRANCE, layout_setting_sound_language_get, -1, NULL, NULL, -1},
            {0, 70 + 140 * 2, 970, 140, setting_volume_obj_id_guard_station_cont, setting_volume_obj_id_guard_station_label, -1, SOUND_LANG_ID_GUARD_STATION, layout_setting_sound_language_get, -1, NULL, NULL, -1},
            {0, 70 + 140 * 3, 970, 140, setting_volume_obj_id_extension_cont, setting_volume_obj_id_extension_label, -1, SOUND_LANG_ID_EXTENSION, layout_setting_sound_language_get, -1, NULL, NULL, -1},
            {0, 70 + 140 * 4, 970, 140, setting_volume_obj_id_touch_notification_cont, setting_volume_obj_id_touch_notification_label, -1, SOUND_LANG_ID_TOUCH_NOTIFICATION, layout_setting_sound_language_get, -1, NULL, NULL, -1},
        };
        int slider_volume_group[][6] = {

            {setting_volume_obj_id_buzzer_volume_img,
             setting_volume_obj_id_buzzer_volume_slider_cont,
             setting_volume_obj_id_buzzer_volume_slider_text,
             setting_volume_obj_id_buzzer_volume_slider_left_btn,
             setting_volume_obj_id_buzzer_volume_slider_right_btn,
             setting_volume_obj_id_buzzer_volume_slider},

            {setting_volume_obj_id_entrance_volume_img,
             setting_volume_obj_id_entrance_volume_slider_cont,
             setting_volume_obj_id_entrance_volume_slider_text,
             setting_volume_obj_id_entrance_volume_slider_left_btn,
             setting_volume_obj_id_entrance_volume_slider_right_btn,
             setting_volume_obj_id_entrance_volume_slider},

            {setting_volume_obj_id_common_entrance_volume_img,
             setting_volume_obj_id_common_entrance_volume_slider_cont,
             setting_volume_obj_id_common_entrance_volume_slider_text,
             setting_volume_obj_id_common_entrance_volume_slider_left_btn,
             setting_volume_obj_id_common_entrance_volume_slider_right_btn,
             setting_volume_obj_id_common_entrance_volume_slider},

            {setting_volume_obj_id_guard_station_volume_img,
             setting_volume_obj_id_guard_station_volume_slider_cont,
             setting_volume_obj_id_guard_station_volume_slider_text,
             setting_volume_obj_id_guard_station_volume_slider_left_btn,
             setting_volume_obj_id_guard_station_volume_slider_right_btn,
             setting_volume_obj_id_guard_station_volume_slider},

            {setting_volume_obj_id_extension_volume_img,
             setting_volume_obj_id_extension_volume_slider_cont,
             setting_volume_obj_id_extension_volume_slider_text,
             setting_volume_obj_id_extension_volume_slider_left_btn,
             setting_volume_obj_id_extension_volume_slider_right_btn,
             setting_volume_obj_id_extension_volume_slider},

            {setting_volume_obj_id_touch_notification_volume_img,
             setting_volume_obj_id_touch_notification_volume_slider_cont,
             setting_volume_obj_id_touch_notification_volume_slider_text,
             setting_volume_obj_id_touch_notification_volume_slider_left_btn,
             setting_volume_obj_id_touch_notification_volume_slider_right_btn,
             setting_volume_obj_id_touch_notification_volume_slider},
        };
        int slider_voice_group[][6] = {

            {-1, -1, -1, -1, -1, -1},
            {setting_volume_obj_id_entrance_voice_img,
             setting_volume_obj_id_entrance_voice_slider_cont,
             setting_volume_obj_id_entrance_voice_slider_text,
             setting_volume_obj_id_entrance_voice_slider_left_btn,
             setting_volume_obj_id_entrance_voice_slider_right_btn,
             setting_volume_obj_id_entrance_voice_slider},

            {setting_volume_obj_id_common_entrance_voice_img,
             setting_volume_obj_id_common_entrance_voice_slider_cont,
             setting_volume_obj_id_common_entrance_voice_slider_text,
             setting_volume_obj_id_common_entrance_voice_slider_left_btn,
             setting_volume_obj_id_common_entrance_voice_slider_right_btn,
             setting_volume_obj_id_common_entrance_voice_slider},

            {setting_volume_obj_id_guard_station_voice_img,
             setting_volume_obj_id_guard_station_voice_slider_cont,
             setting_volume_obj_id_guard_station_voice_slider_text,
             setting_volume_obj_id_guard_station_voice_slider_left_btn,
             setting_volume_obj_id_guard_station_voice_slider_right_btn,
             setting_volume_obj_id_guard_station_voice_slider},

            {setting_volume_obj_id_extension_voice_img,
             setting_volume_obj_id_extension_voice_slider_cont,
             setting_volume_obj_id_extension_voice_slider_text,
             setting_volume_obj_id_extension_voice_slider_left_btn,
             setting_volume_obj_id_extension_voice_slider_right_btn,
             setting_volume_obj_id_extension_voice_slider},

            {setting_volume_obj_id_touch_notification_voice_img,
             setting_volume_obj_id_touch_notification_voice_slider_cont,
             setting_volume_obj_id_touch_notification_voice_slider_text,
             setting_volume_obj_id_touch_notification_voice_slider_left_btn,
             setting_volume_obj_id_touch_notification_voice_slider_right_btn,
             setting_volume_obj_id_touch_notification_voice_slider},
        };

        lv_obj_t *list = setting_list_create(sat_cur_layout_screen_get(), setting_volume_obj_id_list);
        lv_common_style_set_common(list, setting_volume_obj_id_list, 27, 88, 970, 512, LV_ALIGN_TOP_LEFT, LV_PART_MAIN);

        void *left_src = resource_ui_src_alloc("btn_control_minus.png", 42, 42);
        void *right_src = resource_ui_src_alloc("btn_control_plus.png", 42, 42);
        for (int i = 0; i < sizeof(main_list_group) / sizeof(setting_list_info_t); i++)
        {
                lv_obj_t *item = lv_common_setting_btn_title_sub_info_img_create(list, main_list_group[i].cont_id, main_list_group[i].x, main_list_group[i].y, main_list_group[i].w, main_list_group[i].h,
                                                                                 main_list_group[i].click_cb, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                                                 0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                                                 0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                                                 0, i == 0 ? 17 : 52, 576, 43, main_list_group[i].title_id,
                                                                                 main_list_group[i].title_language_id == -1 ? NULL : main_list_group[i].title_language_cb(main_list_group[i].title_language_id), 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                                 0, 42, 576, 29, main_list_group[i].sub_id,
                                                                                 main_list_group[i].sub_language_id == -1 ? NULL : main_list_group[i].sub_language_cb(main_list_group[i].sub_language_id), 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                                 0, 0, 0, 0, -1,
                                                                                 NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                                 0, 0, 0, 0, -1,
                                                                                 NULL, LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);

                lv_common_img_btn_create(item, slider_volume_group[i][0], 297, 14, 42, 42,
                                         NULL, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("volume.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

                lv_common_slider_create(item, slider_volume_group[i][1], 255, 8, 678, 54,
                                        setting_volume_slider_change_cb, LV_OPA_TRANSP, 0X00,
                                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                        6, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                        137, 8, 40, 38, slider_volume_group[i][2],
                                        "50", 0Xffffff, LV_TEXT_ALIGN_CENTER, lv_font_normal,
                                        223, 22, 328, 10, slider_volume_group[i][5], LV_OPA_COVER, 0x666666, LV_OPA_COVER, 0x00a8ff,
                                        165, 6, 42, 42, slider_volume_group[i][3],
                                        left_src, LV_OPA_TRANSP, 0X00, LV_ALIGN_CENTER,
                                        567, 6, 42, 42, slider_volume_group[i][4],
                                        right_src, LV_OPA_TRANSP, 0x00, LV_ALIGN_CENTER,
                                        360, 9, 0Xffffff, LV_OPA_COVER, NULL,
                                        0, 100, 50);

                if (slider_voice_group[i][0] > 0)
                {
                        lv_common_img_btn_create(item, slider_voice_group[i][0], 297, 84, 42, 42,
                                                 NULL, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 resource_ui_src_get("voice.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

                        lv_common_slider_create(item, slider_voice_group[i][1], 255, 78, 678, 54,
                                                setting_volume_slider_change_cb, LV_OPA_TRANSP, 0X00,
                                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                6, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                137, 8, 40, 38, slider_voice_group[i][2],
                                                "50", 0Xffffff, LV_TEXT_ALIGN_CENTER, lv_font_normal,
                                                223, 22, 328, 10, slider_voice_group[i][5], LV_OPA_COVER, 0x666666, LV_OPA_COVER, 0x00a8ff,
                                                165, 6, 42, 42, slider_voice_group[i][3],
                                                left_src, LV_OPA_TRANSP, 0X00, LV_ALIGN_CENTER,
                                                567, 6, 42, 42, slider_voice_group[i][4],
                                                right_src, LV_OPA_TRANSP, 0x00, LV_ALIGN_CENTER,
                                                360, 9, 0Xffffff, LV_OPA_COVER, NULL,
                                                0, 100, 50);
                }
        }

        resouce_file_src_free(left_src);
        resouce_file_src_free(right_src);

        return list;
}

static void sat_layout_enter(setting_volume)
{
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明: 标题显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_volume_obj_id_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      layout_setting_sound_language_get(SOUND_LANG_ID_VOLUME), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:25
        ** 说明: 上一步
        ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_volume_obj_id_cancel, 35, 15, 48, 48,
                                         setting_volume_cancel_obj_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }

        setting_volume_slider_obj_create();
}
static void sat_layout_quit(setting_volume)
{
}

sat_layout_create(setting_volume);