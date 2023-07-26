#include "layout_define.h"
#include "layout_setting_ipaddress.h"
enum
{
        setting_ipaddress_obj_id_titile_label,
        setting_ipaddress_obj_id_cancel_btn,
        setting_ipaddress_obj_id_next_btn,

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-1 8:50:19
        ** 说明: 数字键盘
        ***********************************************/
        setting_ipaddress_obj_id_number_keyboard_btn,

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-1 13:43:33
        ** 说明: ip文本框
        ***********************************************/
        setting_ipaddress_obj_id_product_ip_textbox,
        setting_ipaddress_obj_id_default_gateway_textbox,
        setting_ipaddress_obj_id_subnet_mask_textbox,
        setting_ipaddress_obj_id_dns_textbox,
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-1 13:43:33
        ** 说明: ip文本显示
        ***********************************************/
        setting_ipaddress_obj_id_product_ip_label,
        setting_ipaddress_obj_id_default_gateway_label,
        setting_ipaddress_obj_id_subnet_mask_label,
        setting_ipaddress_obj_id_dns_label
};

static bool enter_ip_setting_ipc_display = false;
bool enter_layout_setting_ipaddress_is_ipc_display()
{
        return enter_ip_setting_ipc_display;
}

void enter_layout_setting_ipaddress_ipc_display_set(bool is)
{
        enter_ip_setting_ipc_display = is;
}
static void setting_ipaddress_obj_cancel_click(lv_event_t *e)
{
        if (enter_layout_setting_ipaddress_is_ipc_display())
        {
                sat_layout_goto(ipc_camera_display, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
        }
        else
        {
                sat_layout_goto(setting_installation, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
        }
}

static void setting_ipaddress_next_obj_display(void)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_ipaddress_obj_id_next_btn);
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
static lv_obj_t *setting_ipaddress_textarea_focused_get(void)
{

        int obj_id[] = {
            setting_ipaddress_obj_id_product_ip_textbox,
            setting_ipaddress_obj_id_default_gateway_textbox,
            setting_ipaddress_obj_id_subnet_mask_textbox,
            setting_ipaddress_obj_id_dns_textbox};

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
static void setting_ipaddress_obj_confirm_click(lv_event_t *e)
{
        lv_obj_t *textarea = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_ipaddress_obj_id_product_ip_textbox);
        if (textarea == NULL)
        {
                return;
        }
        strncpy(network_data_get()->ip, lv_textarea_get_text(textarea), sizeof(network_data_get()->ip));

        textarea = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_ipaddress_obj_id_subnet_mask_textbox);
        if (textarea == NULL)
        {
                return;
        }
        strncpy(network_data_get()->mask, lv_textarea_get_text(textarea), sizeof(network_data_get()->mask));

        network_data_save();

        if (enter_layout_setting_ipaddress_is_ipc_display())
        {
                sat_layout_goto(ipc_camera_display, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
        }
        else
        {
                sat_layout_goto(setting_installation, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
        }
}
static bool setting_ipaddress_textbox_del(void)
{
        lv_obj_t *textarea = setting_ipaddress_textarea_focused_get();

        if (textarea == NULL)
        {
                return false;
        }

        lv_textarea_del_char(textarea);

        return true;
}
static bool setting_ipaddress_textbox_add(const char *string)
{
        lv_obj_t *textarea = setting_ipaddress_textarea_focused_get();

        if (textarea == NULL)
        {

                return false;
        }

        lv_textarea_add_text(textarea, string);
        return true;
}

static void setting_ipaddress_obj_keyboad_click(lv_event_t *e)
{
        lv_obj_t *obj = lv_event_get_target(e);
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);

        if (id == 11)
        {

                setting_ipaddress_textbox_del();
        }
        else
        {
                const char *text = lv_btnmatrix_get_btn_text(obj, id);

                if (text != NULL)
                {

                        setting_ipaddress_textbox_add(text);
                }
        }
        setting_ipaddress_next_obj_display();
}
static void sat_layout_enter(setting_ipaddress)
{
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明: 标题显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_ipaddress_obj_id_titile_label, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(INSTALLATION_XLS_LANG_ID_IP_ADDRES), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:25
        ** 说明: 上一步下一步
        ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_ipaddress_obj_id_cancel_btn, 35, 15, 48, 48,
                                         setting_ipaddress_obj_cancel_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);

                lv_obj_t *obj = lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_ipaddress_obj_id_next_btn, 912, 15, 80, 48,
                                                         setting_ipaddress_obj_confirm_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
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
                lv_common_number_input_keyboard_create(sat_cur_layout_screen_get(), setting_ipaddress_obj_id_number_keyboard_btn, 608, 127, 312, 500,
                                                       setting_ipaddress_obj_keyboad_click, LV_OPA_COVER, 0X101010, LV_OPA_COVER, 0x00a8ff,
                                                       360, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                       360, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                       0XFFFFFF, 0XFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large,
                                                       18, 24);
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:43:29
        ** 说明: 文本输入框显示
        ***********************************************/
        char ip[32] = {0};
        char mask[32] = {0};
        sat_ip_mac_addres_get("eth0", ip, NULL, mask);
        {
                lv_common_textarea_create(sat_cur_layout_screen_get(), setting_ipaddress_obj_id_product_ip_textbox, 298, 166, 250, 50,
                                          NULL, LV_OPA_TRANSP, 0, LV_OPA_COVER, 0X101010,
                                          LV_OPA_TRANSP, 0Xffffff, LV_OPA_COVER, 0Xffffff,
                                          9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0X101010,
                                          9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0x00a8ff,
                                          ip, 0Xffffff, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal, 15,
                                          5, 500, 0Xffffff);
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:43:48
        ** 说明: 文本显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_ipaddress_obj_id_product_ip_label, 32, 173, 200, 50,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(SIGNLE_OPERATION_NETWORK_XLS_LANG_ID_IP), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_LEFT, lv_font_normal);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:43:29
         ** 说明: 文本输入框显示
         ***********************************************/
        {
                lv_common_textarea_create(sat_cur_layout_screen_get(), setting_ipaddress_obj_id_default_gateway_textbox, 298, 250, 250, 50,
                                          NULL, LV_OPA_TRANSP, 0, LV_OPA_COVER, 0X101010,
                                          LV_OPA_TRANSP, 0Xffffff, LV_OPA_COVER, 0Xffffff,
                                          9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0X101010,
                                          9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0x00a8ff,
                                          "192.168.0.1", 0Xffffff, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal, 15,
                                          5, 500, 0Xffffff);
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:43:48
        ** 说明: 文本显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_ipaddress_obj_id_default_gateway_label, 32, 257, 200, 50,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(SIGNLE_OPERATION_NETWORK_XLS_LANG_ID_GATEWAY), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_LEFT, lv_font_normal);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:43:29
         ** 说明: 文本输入框显示
         ***********************************************/
        {
                lv_common_textarea_create(sat_cur_layout_screen_get(), setting_ipaddress_obj_id_subnet_mask_textbox, 298, 334, 250, 50,
                                          NULL, LV_OPA_TRANSP, 0, LV_OPA_COVER, 0X101010,
                                          LV_OPA_TRANSP, 0Xffffff, LV_OPA_COVER, 0Xffffff,
                                          9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0X101010,
                                          9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0x00a8ff,
                                          mask, 0Xffffff, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal, 15,
                                          5, 500, 0Xffffff);
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:43:48
        ** 说明: 文本显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_ipaddress_obj_id_subnet_mask_label, 32, 341, 200, 50,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(SIGNLE_OPERATION_NETWORK_XLS_LANG_ID_MASK), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_LEFT, lv_font_normal);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:43:29
         ** 说明: 文本输入框显示
         ***********************************************/
        {
                lv_common_textarea_create(sat_cur_layout_screen_get(), setting_ipaddress_obj_id_dns_textbox, 298, 418, 250, 50,
                                          NULL, LV_OPA_TRANSP, 0, LV_OPA_COVER, 0X101010,
                                          LV_OPA_TRANSP, 0Xffffff, LV_OPA_COVER, 0Xffffff,
                                          9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0X101010,
                                          9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0x00a8ff,
                                          "192.168.0.1", 0Xffffff, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal, 15,
                                          5, 500, 0Xffffff);
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:43:48
        ** 说明: 文本显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_ipaddress_obj_id_dns_label, 32, 425, 200, 50,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(SIGNLE_OPERATION_NETWORK_XLS_LANG_ID_DNS), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_LEFT, lv_font_normal);
        }
}
static void sat_layout_quit(setting_ipaddress)
{
        enter_layout_setting_ipaddress_ipc_display_set(false);
}

sat_layout_create(setting_ipaddress);