#include "layout_define.h"
#include "layout_wifi_input.h"
enum
{
        cctv_serch_input_obj_id_title,
        cctv_serch_input_obj_id_cancel,

        cctv_serch_input_obj_id_textarea,

        cctv_serch_input_obj_id_password_hidden,

        cctv_serch_input_obj_id_keyboard
};
static int cctv_serch_input_index = 0;
void cctv_serch_input_index_setting(int index)
{
        cctv_serch_input_index = index;
}
int cctv_serch_input_index_get(void)
{
        return cctv_serch_input_index;
}
/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：设置wifi输入账号
** 返回参数说明：
***/
static char cctv_serch_input_user_temp[128] = {0};

static void cctv_serch_input_cancel_click(lv_event_t *ev)
{
        sat_layout_goto(cctv_search, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
}

static void cctv_serch_input_password_hidden_click(lv_event_t *ev)
{
        lv_obj_t *obj = lv_event_get_current_target(ev);

        lv_obj_t *textarea = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), cctv_serch_input_obj_id_textarea);

        bool password_mode = lv_textarea_get_password_mode(textarea);
        lv_textarea_set_password_mode(textarea, password_mode ? false : true);
        if (password_mode == true)
        {
                lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("5_list_show.png"), LV_PART_MAIN);
        }
        else
        {
                lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_list_hide.png"), LV_PART_MAIN);
        }
}
static void cctv_serch_input_textarea_placeholder_setting(void)
{
        lv_obj_t *textarea = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), cctv_serch_input_obj_id_textarea);
        if (textarea == NULL)
        {

                return;
        }
        lv_textarea_set_placeholder_text(textarea, layout_wifi_input_language_get(cctv_serch_input_user_temp[0] == 0 ? WIFI_INPUT_LANG_ID_INPUT_USER : WIFI_INPUT_LANG_ID_INPUT_PASSWORD));
}
static void cctv_serch_input_password_hidden_icon(void)
{
        lv_obj_t *icon = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), cctv_serch_input_obj_id_password_hidden);
        if (icon == NULL)
        {

                return;
        }
        if (cctv_serch_input_user_temp[0] == 0)
        {
                lv_obj_add_flag(icon, LV_OBJ_FLAG_HIDDEN);
        }
        else
        {
                lv_obj_clear_flag(icon, LV_OBJ_FLAG_HIDDEN);
        }
}
static void cctv_serch_input_keyboard_click(lv_event_t *ev)
{
        lv_obj_t *obj = lv_event_get_target(ev);
        uint16_t btn_id = lv_btnmatrix_get_selected_btn(obj);
        lv_keyboard_mode_t mode = lv_keyboard_get_mode(obj);
        if ((((mode == LV_KEYBOARD_MODE_TEXT_LOWER) || (mode == LV_KEYBOARD_MODE_TEXT_UPPER)) && (btn_id != 41)) ||
            ((mode == LV_KEYBOARD_MODE_SPECIAL) && (btn_id != 43)))
        {
                return;
        }

        lv_obj_t *textarea = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), cctv_serch_input_obj_id_textarea);
        if (cctv_serch_input_user_temp[0] == 0)
        {

                strcpy(cctv_serch_input_user_temp, lv_textarea_get_text(textarea));
                lv_textarea_set_text(textarea, "");
                cctv_serch_input_textarea_placeholder_setting();
                cctv_serch_input_password_hidden_icon();
        }
        else
        {
                SAT_DEBUG("===========%d", cctv_serch_input_index);
                sat_ipcamera_user_password_set(cctv_serch_input_index, cctv_serch_input_user_temp, lv_textarea_get_text(textarea));
                sat_layout_goto(cctv_search_display, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
        }
}
static void sat_layout_enter(cctv_serch_input)
{
        memset(cctv_serch_input_user_temp, 0, sizeof(cctv_serch_input_user_temp));
        lv_obj_t *textarea;
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明: 标题显示
        ***********************************************/
        {
                char buffer[32] = {0};
                sprintf(buffer, "CCTV%d", cctv_serch_input_index + 1);
                lv_common_text_create(sat_cur_layout_screen_get(), cctv_serch_input_obj_id_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      buffer, 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 上一步
         ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), cctv_serch_input_obj_id_cancel, 35, 15, 48, 48,
                                         cctv_serch_input_cancel_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:43:29
        ** 说明: 文本输入框显示
        ***********************************************/
        {
                textarea = lv_common_textarea_create(sat_cur_layout_screen_get(), cctv_serch_input_obj_id_textarea, 48, 80, 928, 88,
                                                     NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0X101010,
                                                     LV_OPA_COVER, 0Xffffff, LV_OPA_COVER, 0Xffffff,
                                                     0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                     0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                     NULL, 0Xffffff, 0Xffffff, LV_TEXT_ALIGN_LEFT, lv_font_normal, 64,
                                                     30, 500, 0Xffffff);

                lv_obj_set_style_text_color(textarea, lv_color_hex(0x929292), LV_PART_TEXTAREA_PLACEHOLDER);
                lv_obj_set_style_text_opa(textarea, LV_OPA_COVER, LV_PART_TEXTAREA_PLACEHOLDER);
                lv_obj_add_state(textarea, LV_STATE_FOCUSED);
                lv_textarea_set_password_bullet(textarea, "*");
                cctv_serch_input_textarea_placeholder_setting();
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:43:29
        ** 说明: 隐藏按钮
        ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), cctv_serch_input_obj_id_password_hidden, 928, 100, 48, 48,
                                         cctv_serch_input_password_hidden_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_list_show.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);

                cctv_serch_input_password_hidden_icon();
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:43:29
         ** 说明: 键盘
         ***********************************************/
        {

                lv_obj_t *keyboard = lv_common_keyboard_create(sat_cur_layout_screen_get(), cctv_serch_input_obj_id_keyboard, 0, 200, 1024, 400,
                                                               cctv_serch_input_keyboard_click, LV_OPA_COVER, 0x292929, LV_OPA_COVER, 0x00a8ff,
                                                               0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                               0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                               8, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                               8, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                               0xFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large,
                                                               24, 18, 18, 8, 12, 12,
                                                               LV_OPA_COVER, 0x353535, LV_OPA_COVER, 0x353535);

                lv_keyboard_set_textarea(keyboard, textarea);
        }
}
static void sat_layout_quit(cctv_serch_input)
{
}
sat_layout_create(cctv_serch_input);