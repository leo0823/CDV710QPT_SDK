#include "layout_define.h"
enum
{
        setting_server_ipaddress_obj_id_titile_label,
        setting_server_ipaddress_obj_id_cancel_btn,
        setting_server_ipaddress_obj_id_next_btn,

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-1 8:50:19
        ** 说明: 数字键盘
        ***********************************************/
        setting_server_ipaddress_obj_id_number_keyboard_btn,

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-1 13:43:33
        ** 说明: ip文本框
        ***********************************************/
        setting_server_ipaddress_obj_id_loclal_sever_textbox,
        setting_server_ipaddress_obj_id_sip_server_textbox,
        setting_server_ipaddress_obj_id_update_sever_textbox,
        setting_server_ipaddress_obj_id_cctv_server_textbox,
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-1 13:43:33
        ** 说明: ip文本显示
        ***********************************************/
        setting_server_ipaddress_obj_id_loclal_sever_label,
        setting_server_ipaddress_obj_id_sip_server_label,
        setting_server_ipaddress_obj_id_update_sever_label,
        setting_server_ipaddress_obj_id_cctv_server_label
};

static char etting_server_ipaddress_flag = false;
char layout_setting_setting_server_ipaddress_flag_get()
{
        return etting_server_ipaddress_flag;
}

void layout_setting_setting_server_ipaddress_flag_set(char flag)
{
        etting_server_ipaddress_flag = flag;
}
static void setting_server_ipaddress_obj_cancel_click(lv_event_t *e)
{
        if (layout_setting_setting_server_ipaddress_flag_get() != 0)
        {
                sat_layout_goto(ipc_camera_display, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
        }
        sat_layout_goto(setting_installation, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
}
static void setting_server_ipaddress_obj_confirm_click(lv_event_t *e)
{
        lv_obj_t *local_txt = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_server_ipaddress_obj_id_loclal_sever_textbox);
        if (local_txt != NULL)
        {
                if (is_valid_ipv4(lv_textarea_get_text(local_txt)) == false)
                {
                        return;
                }
        }
        lv_obj_t *sip_txt = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_server_ipaddress_obj_id_sip_server_textbox);
        if (sip_txt != NULL)
        {
                if (is_valid_ipv4(lv_textarea_get_text(sip_txt)) == false)
                {
                        return;
                }
        }
        lv_obj_t *update_txt = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_server_ipaddress_obj_id_update_sever_textbox);
        if (update_txt != NULL)
        {
                if (is_valid_ipv4(lv_textarea_get_text(update_txt)) == false)
                {
                        return;
                }
        }
        lv_obj_t *cctv_txt = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_server_ipaddress_obj_id_cctv_server_textbox);
        if (cctv_txt != NULL)
        {
                if (is_valid_ipv4(lv_textarea_get_text(cctv_txt)) == false)
                {
                        return;
                }
        }
        memset(network_data_get()->local_server, 0, sizeof(network_data_get()->local_server));
        memset(network_data_get()->sip_server, 0, sizeof(network_data_get()->sip_server));
        memset(network_data_get()->cctv_server, 0, sizeof(network_data_get()->cctv_server));
        strncpy(network_data_get()->local_server, lv_textarea_get_text(local_txt), sizeof(network_data_get()->local_server));
        strncpy(network_data_get()->sip_server, lv_textarea_get_text(sip_txt), sizeof(network_data_get()->sip_server));
        strncpy(network_data_get()->cctv_server, lv_textarea_get_text(cctv_txt), sizeof(network_data_get()->cctv_server));
        if (layout_setting_setting_server_ipaddress_flag_get() != 0)
        {
                sat_layout_goto(ipc_camera_display, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
        }
        sat_layout_goto(setting_installation, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
}

static void setting_server_ipaddress_next_obj_display(void)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_server_ipaddress_obj_id_next_btn);
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
static lv_obj_t *setting_server_ipaddress_textarea_focused_get(void)
{

        int obj_id[] = {
            setting_server_ipaddress_obj_id_loclal_sever_textbox,
            setting_server_ipaddress_obj_id_sip_server_textbox,
            setting_server_ipaddress_obj_id_update_sever_textbox,
            setting_server_ipaddress_obj_id_cctv_server_textbox};

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

static bool setting_server_ipaddress_textbox_del(void)
{
        lv_obj_t *textarea = setting_server_ipaddress_textarea_focused_get();

        if (textarea == NULL)
        {
                return false;
        }

        lv_textarea_del_char(textarea);

        return true;
}
static bool setting_server_ipaddress_textbox_add(const char *string)
{
        lv_obj_t *textarea = setting_server_ipaddress_textarea_focused_get();

        if (textarea == NULL)
        {

                return false;
        }

        lv_textarea_add_text(textarea, string);
        return true;
}

static void setting_server_ipaddress_obj_keyboad_click(lv_event_t *e)
{
        lv_obj_t *obj = lv_event_get_target(e);
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);

        if (id == 11)
        {

                setting_server_ipaddress_textbox_del();
        }
        else
        {
                const char *text = lv_btnmatrix_get_btn_text(obj, id);

                if (text != NULL)
                {

                        setting_server_ipaddress_textbox_add(text);
                }
        }
        setting_server_ipaddress_next_obj_display();
}

static void setting_server_ipaddress_local_server()
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_server_ipaddress_obj_id_loclal_sever_textbox);
        if (obj != NULL)
        {
                lv_textarea_set_text(obj, network_data_get()->local_server);
        }
}

static void setting_server_ipaddress_sip_server()
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_server_ipaddress_obj_id_sip_server_textbox);
        if (obj != NULL)
        {
                lv_textarea_set_text(obj, network_data_get()->sip_server);
        }
}

#if 0
static void setting_server_ipaddress_update_server()
{
        lv_obj_t * obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(),setting_server_ipaddress_obj_id_update_sever_textbox);
        if(obj != NULL)
        {
                lv_textarea_set_text(obj,user_data_get()->update_server);
        }
}
#endif

static void setting_server_ipaddress_cctv_server()
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_server_ipaddress_obj_id_cctv_server_textbox);
        if (obj != NULL)
        {
                lv_textarea_set_text(obj, network_data_get()->cctv_server);
        }
}

static void sat_layout_enter(setting_server_ipaddress)
{
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明: 标题显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_server_ipaddress_obj_id_titile_label, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(INSTALLATION_XLS_LANG_ID_OPERATIONG_SERVER_IP_ADDRES), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:25
        ** 说明: 上一步下一步
        ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_server_ipaddress_obj_id_cancel_btn, 35, 15, 48, 48,
                                         setting_server_ipaddress_obj_cancel_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);

                lv_obj_t *obj = lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_server_ipaddress_obj_id_next_btn, 912, 15, 80, 48,
                                                         setting_server_ipaddress_obj_confirm_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
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
                lv_common_number_input_keyboard_create(sat_cur_layout_screen_get(), setting_server_ipaddress_obj_id_number_keyboard_btn, 608, 127, 312, 402,
                                                       setting_server_ipaddress_obj_keyboad_click, LV_OPA_COVER, 0x808080, LV_OPA_COVER, 0x00a8ff,
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
        {
                lv_common_textarea_create(sat_cur_layout_screen_get(), setting_server_ipaddress_obj_id_loclal_sever_textbox, 298, 208, 250, 50,
                                          NULL, LV_OPA_TRANSP, 0, LV_OPA_COVER, 0X101010,
                                          LV_OPA_TRANSP, 0Xffffff, LV_OPA_COVER, 0Xffffff,
                                          9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0X101010,
                                          9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0x00a8ff,
                                          "192.168.0.254", 0Xffffff, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal, 15,
                                          5, 500, 0Xffffff);
                setting_server_ipaddress_local_server();
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:43:48
        ** 说明: 文本显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_server_ipaddress_obj_id_loclal_sever_label, 32, 215, 200, 50,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(SERVER_OPERATION_NETWORK_XLS_LANG_ID_LOCAL_SERVER), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_LEFT, lv_font_normal);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:43:29
         ** 说明: 文本输入框显示
         ***********************************************/
        {
                lv_common_textarea_create(sat_cur_layout_screen_get(), setting_server_ipaddress_obj_id_sip_server_textbox, 298, 292, 250, 50,
                                          NULL, LV_OPA_TRANSP, 0, LV_OPA_COVER, 0X101010,
                                          LV_OPA_TRANSP, 0Xffffff, LV_OPA_COVER, 0Xffffff,
                                          9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0X101010,
                                          9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0x00a8ff,
                                          "192.168.0.1", 0Xffffff, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal, 15,
                                          5, 500, 0Xffffff);
                setting_server_ipaddress_sip_server();
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:43:48
        ** 说明: 文本显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_server_ipaddress_obj_id_sip_server_label, 32, 299, 200, 50,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(SERVER_OPERATION_NETWORK_XLS_LANG_ID_SIP_SERVER), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_LEFT, lv_font_normal);
        }
#if 0
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:43:29
         ** 说明: 文本输入框显示
         ***********************************************/
        {
                lv_common_textarea_create(sat_cur_layout_screen_get(), setting_server_ipaddress_obj_id_update_sever_textbox, 298, 334, 250, 50,
                                          NULL, LV_OPA_TRANSP, 0, LV_OPA_COVER, 0X101010,
                                          LV_OPA_TRANSP, 0Xffffff, LV_OPA_COVER, 0Xffffff,
                                          9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0X101010,
                                          9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0x00a8ff,
                                          "192.168.0.1", 0Xffffff, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal, 15,
                                          5, 500, 0Xffffff);
                setting_server_ipaddress_update_server();
                
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:43:48
        ** 说明: 文本显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_server_ipaddress_obj_id_update_sever_label, 32, 341, 200, 50,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(SERVER_OPERATION_NETWORK_XLS_LANG_ID_UPDATE_SERVER), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_LEFT, lv_font_normal);
        }
#endif
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:43:29
         ** 说明: 文本输入框显示
         ***********************************************/
        {
                lv_common_textarea_create(sat_cur_layout_screen_get(), setting_server_ipaddress_obj_id_cctv_server_textbox, 298, 376, 250, 50,
                                          NULL, LV_OPA_TRANSP, 0, LV_OPA_COVER, 0X101010,
                                          LV_OPA_TRANSP, 0Xffffff, LV_OPA_COVER, 0Xffffff,
                                          9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0X101010,
                                          9, 2, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0x00a8ff,
                                          "192.168.0.1", 0Xffffff, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal, 15,
                                          5, 500, 0Xffffff);
                setting_server_ipaddress_cctv_server();
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:43:48
        ** 说明: 文本显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_server_ipaddress_obj_id_cctv_server_label, 32, 385, 200, 50,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(SERVER_OPERATION_NETWORK_XLS_LANG_ID_CCTV_SERVER), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_LEFT, lv_font_normal);
        }
}
static void sat_layout_quit(setting_server_ipaddress)
{
        layout_setting_setting_server_ipaddress_flag_set(0);
}

sat_layout_create(setting_server_ipaddress);