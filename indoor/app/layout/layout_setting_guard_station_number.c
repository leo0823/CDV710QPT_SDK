#include "layout_define.h"
enum
{
        setting_guard_station_number_obj_id_titile_label,
        setting_guard_station_number_obj_id_cancel_btn,
        setting_guard_station_number_obj_id_next_btn,

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-1 8:50:19
        ** 说明: 数字键盘
        ***********************************************/
        setting_guard_station_number_obj_id_number_keyboard_btn,
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-1 8:50:19
        ** 说明: 数字键盘无用案件覆盖
        ***********************************************/
        setting_guard_station_number_obj_id_number_keyboard_cover,

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-1 13:43:33
        ** 说明: ip文本框
        ***********************************************/
        setting_guard_station_number_obj_id_building_number_textbox,
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-1 13:43:33
        ** 说明: ip文本显示
        ***********************************************/
        setting_guard_station_number_obj_id_building_number_label,

        setting_guard_station_number_obj_id_msg_bg, // 消息框背景
};

static void setting_guard_station_number_obj_cancel_click(lv_event_t *e)
{
        sat_layout_goto(setting_installation, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
}

static void setting_guard_station_number_falid_confirm(lv_event_t *e)
{

        setting_msgdialog_msg_del(setting_guard_station_number_obj_id_msg_bg);
}

/************************************************************
** 函数说明: 数据校验失败提示
** 作者: xiaoxiao
** 日期：2023-09-26 14:23:59
** 参数说明:
** 注意事项：
************************************************************/
static void setting_guard_station_number_falid_tips(void)
{
        lv_obj_t *masgbox = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_guard_station_number_obj_id_msg_bg);
        if (masgbox != NULL)
        {
                setting_msgdialog_msg_del(setting_guard_station_number_obj_id_msg_bg);
        }
        masgbox = setting_msgdialog_msg_bg_create(setting_guard_station_number_obj_id_msg_bg, 0, 282, 143, 460, 283);
        setting_msgdialog_msg_create(masgbox, 1, lang_str_get(SERVER_OPERATION_NETWORK_XLS_LANG_ID_ENTER_FORMAT), 0, 60, 460, 120, false);
        setting_msgdialog_msg_confirm_btn_create(masgbox, 2, setting_guard_station_number_falid_confirm);
}

static void setting_guard_station_number_obj_confirm_click(lv_event_t *e)
{
        lv_obj_t *textarea = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_guard_station_number_obj_id_building_number_textbox);
        int len = strlen(lv_textarea_get_text(textarea));
        if ((len < 1) || (len > 11))
        {
                setting_guard_station_number_falid_tips();
                return;
        }
        strncpy(network_data_get()->guard_number, lv_textarea_get_text(textarea), sizeof(network_data_get()->guard_number));
        network_data_save();
        sat_layout_goto(setting_installation, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
}

static void setting_guard_station_number_next_obj_display(void)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_guard_station_number_obj_id_next_btn);
        if (obj == NULL)
        {

                return;
        }
        if (lv_obj_has_flag(obj, LV_OBJ_FLAG_HIDDEN) == true)
        {

                lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
}
/***********************************************
** 作者: leo.liu
** 日期: 2023-2-1 8:51:49
** 说明: 输入数字键盘
***********************************************/
static lv_obj_t *setting_guard_station_number_textarea_focused_get(void)
{

        int obj_id[] = {
            setting_guard_station_number_obj_id_building_number_textbox,
        };

        lv_obj_t *textarea = NULL;

        for (int i = 0; i < sizeof(obj_id) / sizeof(int); i++)
        {

                textarea = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), obj_id[i]);

                if ((textarea != NULL) && (lv_obj_get_state(textarea) & LV_STATE_FOCUSED))
                {

                        return textarea;
                }
        }

        return textarea;
}

static bool setting_guard_station_number_textbox_del(void)
{
        lv_obj_t *textarea = setting_guard_station_number_textarea_focused_get();

        if (textarea == NULL)
        {
                return false;
        }

        lv_textarea_del_char(textarea);

        return true;
}
static bool setting_guard_station_number_textbox_add(const char *string)
{
        lv_obj_t *textarea = setting_guard_station_number_textarea_focused_get();

        if (textarea == NULL)
        {

                return false;
        }

        lv_textarea_add_text(textarea, string);
        return true;
}

static void setting_guard_station_number_obj_keyboad_click(lv_event_t *e)
{
        lv_obj_t *obj = lv_event_get_target(e);
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);
        if (lv_btnmatrix_has_btn_ctrl(obj, id, LV_BTNMATRIX_CTRL_HIDDEN) == true)
        {
                return;
        }
        if (id == 11)
        {

                setting_guard_station_number_textbox_del();
        }
        else
        {
                const char *text = lv_btnmatrix_get_btn_text(obj, id);

                if (text != NULL)
                {

                        setting_guard_station_number_textbox_add(text);
                }
        }
        setting_guard_station_number_next_obj_display();
}
static void sat_layout_enter(setting_guard_station_number)
{
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明: 标题显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_guard_station_number_obj_id_titile_label, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(INSTALLATION_XLS_LANG_ID_GUARD_STATION_NUMBER), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:25
        ** 说明: 上一步下一步
        ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_guard_station_number_obj_id_cancel_btn, 35, 15, 48, 48,
                                         setting_guard_station_number_obj_cancel_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);

                lv_obj_t *obj = lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_guard_station_number_obj_id_next_btn, 912, 15, 80, 48,
                                                         setting_guard_station_number_obj_confirm_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                         resource_ui_src_get("btn_title_check.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:43:18
        ** 说明: 数字键盘创建
        ***********************************************/
        {
                lv_obj_t *obj = lv_common_number_input_keyboard_create(sat_cur_layout_screen_get(), setting_guard_station_number_obj_id_number_keyboard_btn, 608, 127, 312, 402,
                                                                       setting_guard_station_number_obj_keyboad_click, LV_OPA_COVER, 0x808080, LV_OPA_COVER, 0x00a8ff,
                                                                       360, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                                       360, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                                       0XFFFFFF, 0XFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large,
                                                                       18, 24);
                lv_btnmatrix_set_btn_ctrl(obj, 9, LV_BTNMATRIX_CTRL_HIDDEN | LV_BTNMATRIX_CTRL_DISABLED);
                lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_guard_station_number_obj_id_number_keyboard_cover, 608, 425, 100, 102,
                                         NULL, true, LV_OPA_TRANSP, 0x808080, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:43:29
        ** 说明: 文本输入框显示
        ***********************************************/
        {
                lv_common_textarea_create(sat_cur_layout_screen_get(), setting_guard_station_number_obj_id_building_number_textbox, 298, 292, 250, 50,
                                          NULL, LV_OPA_TRANSP, 0, LV_OPA_COVER, 0X101010,
                                          LV_OPA_TRANSP, 0Xffffff, LV_OPA_COVER, 0Xffffff,
                                          9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0X101010,
                                          9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0x00a8ff,
                                          network_data_get()->guard_number, 0Xffffff, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal, 11,
                                          5, 500, 0Xffffff);
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:43:48
        ** 说明: 文本显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_guard_station_number_obj_id_building_number_label, 32, 299, 200, 50,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(INSTALLATION_XLS_LANG_ID_GUARD_STATION_NUMBER), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_LEFT, lv_font_normal);
        }
}
static void sat_layout_quit(setting_guard_station_number)
{
}

sat_layout_create(setting_guard_station_number);