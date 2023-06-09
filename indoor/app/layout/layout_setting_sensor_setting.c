#include "layout_define.h"
#include "layout_setting_sensor_usage.h"
#include "layout_setting_general.h"

enum
{
        setting_sensor_settings_obj_id_title,
        setting_sensor_settings_obj_id_cancel,
        setting_sensor_settings_obj_id_list,

        setting_sensor_settings_obj_id_item1_cont,

        setting_sensor_settings_obj_id_item2_cont,

        setting_sensor_settings_obj_id_item3_cont,

        setting_sensor_settings_obj_id_item4_cont,

        setting_sensor_settings_obj_id_item5_cont,

        setting_sensor_settings_obj_id_item6_cont,

        setting_sensor_settings_obj_id_item7_cont,
};
static void setting_sensor_settings_cancel_obj_click(lv_event_t *e)
{
        sat_layout_goto(setting_installation, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
}

static void setting_sensor_settings_list_click(lv_event_t *e)
{
        lv_obj_t *cont = lv_event_get_current_target(e);
        if (cont == NULL)
        {
                return;
        }
        lv_obj_t *obj = lv_obj_get_child_form_id(cont, 2);
        if (obj == NULL)
        {
                return;
        }
        if (strncmp((const char *)obj->bg_img_src, resource_ui_src_get("btn_switch_off.png"), strlen(resource_ui_src_get("btn_switch_off.png"))))
        {
                lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_switch_off.png"), LV_PART_MAIN);
        }
        else
        {
                lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_switch_on.png"), LV_PART_MAIN);
        }
}

static void sat_layout_enter(setting_sensor_settings)
{
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明: 标题显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_sensor_settings_obj_id_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(SETTING_SENSOR_USAGE_XLS_LANG_ID_SENSOR_SETTINGS), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:25
        ** 说明: 上一步
        ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_sensor_settings_obj_id_cancel, 35, 15, 48, 48,
                                         setting_sensor_settings_cancel_obj_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:25
        ** 说明: 列表
        ***********************************************/
        {
                setting_list_info_t main_list_group[] = {

                    {0, 0, 928, 72,
                     setting_sensor_settings_obj_id_item1_cont, 0, 1,
                     SETTING_SENSOR_USAGE_XLS_LANG_ID_SENSOR_CONTACT_1, lang_str_get,
                     SETTING_SENSOR_USAGE_XLS_LANG_ID_NOT_USED, lang_str_get,
                     setting_sensor_settings_list_click, 2},
                    {0, 72, 928, 72,
                     setting_sensor_settings_obj_id_item2_cont, 0, 1,
                     SETTING_SENSOR_USAGE_XLS_LANG_ID_SENSOR_CONTACT_2, lang_str_get,
                     SETTING_SENSOR_USAGE_XLS_LANG_ID_SENSOR_FOR_SECURITY, lang_str_get,
                     setting_sensor_settings_list_click, 2},
                    {0, 72 * 2, 928, 72,
                     setting_sensor_settings_obj_id_item3_cont, 0, 1,
                     SETTING_SENSOR_USAGE_XLS_LANG_ID_SENSOR_CONTACT_3, lang_str_get,
                     SETTING_SENSOR_USAGE_XLS_LANG_ID_SENSOR_FOR_SECURITY, lang_str_get,
                     setting_sensor_settings_list_click, 2},
                    {0, 72 * 3, 928, 72,
                     setting_sensor_settings_obj_id_item4_cont, 0, 1,
                     SETTING_SENSOR_USAGE_XLS_LANG_ID_SENSOR_CONTACT_4, lang_str_get,
                     SETTING_SENSOR_USAGE_XLS_LANG_ID_SENSOR_FOR_SECURITY, lang_str_get,
                     setting_sensor_settings_list_click, 2},
                    {0, 72 * 4, 928, 72,
                     setting_sensor_settings_obj_id_item5_cont, 0, 1,
                     SETTING_SENSOR_USAGE_XLS_LANG_ID_SENSOR_CONTACT_5, lang_str_get,
                     SETTING_SENSOR_USAGE_XLS_LANG_ID_SENSOR_FOR_SECURITY, lang_str_get,
                     setting_sensor_settings_list_click, 2},
                    {0, 72 * 5, 928, 72,
                     setting_sensor_settings_obj_id_item6_cont, 0, 1,
                     SETTING_SENSOR_USAGE_XLS_LANG_ID_SENSOR_CONTACT_6, lang_str_get,
                     SETTING_SENSOR_USAGE_XLS_LANG_ID_SENSOR_FOR_SECURITY, lang_str_get,
                     setting_sensor_settings_list_click, 2},
                    {0, 72 * 6, 928, 72,
                     setting_sensor_settings_obj_id_item7_cont, 0, 1,
                     SETTING_SENSOR_USAGE_XLS_LANG_ID_SENSOR_CONTACT_7, lang_str_get,
                     SETTING_SENSOR_USAGE_XLS_LANG_ID_SENSOR_FOR_SECURITY, lang_str_get,
                     setting_sensor_settings_list_click, 2},
                };

                lv_obj_t *list = setting_list_create(sat_cur_layout_screen_get(), setting_sensor_settings_obj_id_list);
                lv_common_style_set_common(list, setting_sensor_settings_obj_id_list, 48, 88, 928, 512, LV_ALIGN_TOP_LEFT, LV_PART_MAIN);

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
                                                                        840, 10, 80, 48, main_list_group[i].img_id,
                                                                        resource_ui_src_get("btn_switch_off.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
                }
        }
}
static void sat_layout_quit(setting_sensor_settings)
{
}

sat_layout_create(setting_sensor_settings);