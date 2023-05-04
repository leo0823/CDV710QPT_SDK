#include "layout_define.h"
#include "layout_setting_initialize.h"
#include "layout_setting_general.h"
enum
{
        setting_initialize_obj_id_title,
        setting_initialize_obj_id_cancel,
        setting_initialize_obj_id_data_cannot_label,
        setting_initialize_obj_id_initialize_list_label,
        setting_initialize_obj_id_call_log_lable,
        setting_initialize_obj_id_call_log_complete,
        setting_initialize_obj_id_saved_video_label,
        setting_initialize_obj_id_saved_video_complete,
        setting_initialize_obj_id_emergency_record_label,
        setting_initialize_obj_id_emergency_reocrd_complete,
        setting_initialize_obj_id_initiallization_is_complete_label,
        setting_initialize_obj_id_reset
};
static int setting_initialize_count = 0;
static void setting_initialize_cancel_obj_click(lv_event_t *e)
{
        sat_layout_goto(setting_general, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
}
static void setting_initialize_reset_timer(lv_timer_t *ptimer)
{
        lv_obj_t *obj = NULL;
        if (setting_initialize_count == 0)
        {
                obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_initialize_obj_id_call_log_complete);
        }
        else if (setting_initialize_count == 1)
        {
                obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_initialize_obj_id_saved_video_complete);
        }
        else if (setting_initialize_count == 2)
        {
                obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_initialize_obj_id_emergency_reocrd_complete);
        }
        else if (setting_initialize_count == 3)
        {
                obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_initialize_obj_id_initiallization_is_complete_label);
        }
        else
        {
                lv_obj_t *btn = (lv_obj_t *)ptimer->user_data;
                lv_obj_add_flag(btn, LV_OBJ_FLAG_CLICKABLE);
                lv_timer_del(ptimer);
                return;
        }
        if (obj)
        {
                setting_initialize_count++;
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
}
static void setting_initialize_reset_obj_click(lv_event_t *e)
{
        lv_obj_t *obj = lv_event_get_current_target(e);
        lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        lv_timer_reset(lv_sat_timer_create(setting_initialize_reset_timer, 1000, obj));
}
static void sat_layout_enter(setting_initialize)
{
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: 标题显示
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_initialize_obj_id_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      layout_setting_general_language_get(SETTING_GENERAL_LANG_ID_LANG_INITIALIZATION_USER_DATA), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:25
        ** 说明: 上一步
        ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_initialize_obj_id_cancel, 35, 15, 48, 48,
                                         setting_initialize_cancel_obj_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: data
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_initialize_obj_id_data_cannot_label, 306, 90, 412, 29,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      layout_setting_initialize_language_get(SETTING_INITIALIZE_LANG_ID_DATA_CANNOT_BE), 0x808080, 0x808080, LV_TEXT_ALIGN_CENTER, lv_font_small);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: list
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_initialize_obj_id_initialize_list_label, 423, 137, 179, 35,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      layout_setting_initialize_language_get(SETTING_INITIALIZE_LANG_ID_INITIALZATION_LIST), 0xFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_normal);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: calllog
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_initialize_obj_id_call_log_lable, 273, 193, 234, 29,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      layout_setting_initialize_language_get(SETTING_INITIALIZE_LANG_ID_CALL_LOG), 0x808080, 0x808080, LV_TEXT_ALIGN_RIGHT, lv_font_small);

                lv_obj_t *obj = lv_common_text_create(sat_cur_layout_screen_get(), setting_initialize_obj_id_call_log_complete, 517, 193, 234, 29,
                                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      layout_setting_initialize_language_get(SETTING_INITIALIZE_LANG_ID_COMPLETE), 0x46FF90, 0x46FF90, LV_TEXT_ALIGN_LEFT, lv_font_small);

                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: video
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_initialize_obj_id_saved_video_label, 273, 232, 234, 29,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      layout_setting_initialize_language_get(SETTING_INITIALIZE_LANG_ID_SAVED_VIDEO), 0x808080, 0x808080, LV_TEXT_ALIGN_RIGHT, lv_font_small);

                lv_obj_t *obj = lv_common_text_create(sat_cur_layout_screen_get(), setting_initialize_obj_id_saved_video_complete, 517, 232, 234, 29,
                                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      layout_setting_initialize_language_get(SETTING_INITIALIZE_LANG_ID_COMPLETE), 0x46FF90, 0x46FF90, LV_TEXT_ALIGN_LEFT, lv_font_small);

                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明: emergency record
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_initialize_obj_id_emergency_record_label, 273, 271, 234, 29,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      layout_setting_initialize_language_get(SETTING_INITIALIZE_LANG_ID_EMERGENCY_RECORD), 0x808080, 0x808080, LV_TEXT_ALIGN_RIGHT, lv_font_small);

                lv_obj_t *obj = lv_common_text_create(sat_cur_layout_screen_get(), setting_initialize_obj_id_emergency_reocrd_complete, 517, 271, 234, 29,
                                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      layout_setting_initialize_language_get(SETTING_INITIALIZE_LANG_ID_COMPLETE), 0x46FF90, 0x46FF90, LV_TEXT_ALIGN_LEFT, lv_font_small);

                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: complete
         ***********************************************/
        {

                lv_obj_t *obj = lv_common_text_create(sat_cur_layout_screen_get(), setting_initialize_obj_id_initiallization_is_complete_label, 359, 421, 304, 38,
                                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      layout_setting_initialize_language_get(SETTING_INITIALIZE_LANG_ID_INITIALZATION_IS_COMPLETE), 0x00a8ff, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal);

                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: reset
         ***********************************************/
        {

                lv_obj_t *obj = lv_common_text_create(sat_cur_layout_screen_get(), setting_initialize_obj_id_reset, 0, 528, 1024, 72,
                                                      setting_initialize_reset_obj_click, LV_OPA_COVER, 0x00a8ff, LV_OPA_COVER, 0x00a8ff,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      layout_setting_initialize_language_get(SETTING_INITIALIZE_LANG_ID_RESET), 0xFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_normal);
                lv_obj_set_style_pad_top(obj, 15, LV_PART_MAIN);
        }
        setting_initialize_count = 0;
}
static void sat_layout_quit(setting_initialize)
{
}

sat_layout_create(setting_initialize);