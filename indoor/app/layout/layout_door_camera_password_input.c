#include "layout_define.h"
#include "layout_door_camera_registed.h"
#include "layout_wifi_input.h"
#include "layout_setting_password.h"
enum
{
        door_camera_password_input_obj_id_title,
        door_camera_password_input_obj_id_cancel,

        door_camera_password_input_obj_id_textarea,

        door_camera_password_input_obj_id_password_hidden,

        door_camera_password_input_obj_id_keyboard,

        door_camera_password_input_obj_id_msgbox,
};
static char door_camera_password_input_password_old[10] = {0};
static char door_camera_password_input_password_temp[10] = {0};
/*
 * door_camera_password_input_enter_mode = 0x00: 已经注册，从注册页面进入修改密码
 * door_camera_password_input_enter_mode = 0x01:修改设备名
 * door_camera_password_input_enter_mode = 0x02:输入密码，进入预览。
 * door_camera_password_input_enter_mode = 0x03:修改cctv的名称
 */
static char door_camera_password_input_enter_mode = 0;
void device_password_input_enter_mode_setting(char mode)
{
        door_camera_password_input_enter_mode = mode;
}


/*door_camera_password_input_enter_mode = 0的情况下，
door_camera_password_state = 0,输入旧密码
door_camera_password_state = 1:输入新密码*/
static int door_camera_password_state = 0;

static lv_obj_t *door_camera_password_input_msgbox_create(const char *title, const char *msg, lv_event_cb_t confirm_cb)
{
        lv_obj_t *parent = lv_common_img_btn_create(sat_cur_layout_screen_get(), door_camera_password_input_obj_id_msgbox, 0, 0, 1024, 600,
                                                    NULL, true, LV_OPA_90, 0, LV_OPA_90, 0,
                                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                    NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

        lv_obj_t *msgbox = lv_common_img_btn_create(parent, 0, 282, 131, 460, 343,
                                                    NULL, false, LV_OPA_COVER, 0x242526, LV_OPA_TRANSP, 0,
                                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                    NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

        lv_common_text_create(msgbox, 0, 32, 10, 396, 47,
                              NULL, LV_OPA_TRANSP, 0x323237, LV_OPA_TRANSP, 0,
                              0, 2, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                              0, 2, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                              title, 0XA8A8A8, 0XA8A8A8, LV_TEXT_ALIGN_CENTER, lv_font_small);

        lv_common_text_create(msgbox, 1, 32, 90, 396, 200,
                              NULL, LV_OPA_TRANSP, 0x323237, LV_OPA_TRANSP, 0,
                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x323237,
                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0x323237,
                              msg, 0xFFFFFFFF, 0xFFFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_small);

        lv_common_img_btn_create(msgbox, 2, 0, 281, 460, 62,
                                 confirm_cb, true, LV_OPA_COVER, 0x0096FF, LV_OPA_COVER, 0x0096FF,
                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                 resource_ui_src_get("btn_title_confirm.png"), LV_OPA_TRANSP, 0x0096FF, LV_ALIGN_CENTER);

        return parent;
}

static void door_camera_password_input_cancel_click(lv_event_t *e)
{
        if ((door_camera_password_input_enter_mode == 0x00) || (door_camera_password_input_enter_mode == 0x01))
        {
                sat_layout_goto(door_camera_edit, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
        }
        else if (door_camera_password_input_enter_mode == 0x02)
        {
                sat_layout_goto(door_camera_search, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
        }
        else if (door_camera_password_input_enter_mode == 0x03)
        {
                sat_layout_goto(cctv_registered, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
        }
}

static void door_camera_password_input_textarea_placeholder_setting(void)
{
        lv_obj_t *textarea = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), door_camera_password_input_obj_id_textarea);
        if (textarea == NULL)
        {
                return;
        }
        if (door_camera_password_input_enter_mode == 0x02)
        {
                lv_textarea_set_placeholder_text(textarea, layout_wifi_input_language_get(WIFI_INPUT_LANG_ID_INPUT_PASSWORD));
        }
        else if (door_camera_password_input_enter_mode == 0x00)
        {
                lv_textarea_set_placeholder_text(textarea, door_camera_password_state == 0 ? layout_setting_password_language_get(SETTING_PASSWORD_LANG_ID_OLD_PASSWORD)
                                                                                           : layout_door_camera_search_language_get(door_camera_password_input_password_temp[0] == 0 ? DOOR_CAMERA_SEARCH_ID_ENTER_AT_LEAST_9_DIGITS_OF_NUMBER
                                                                                                                                                                                     : DOOR_CAMERA_SEARCH_ID_CHANGE_TH_CONNETION_PASSWORD));
        }
        else if (door_camera_password_input_enter_mode == 0x01)
        {
                lv_textarea_set_placeholder_text(textarea, network_data_get()->door_device[device_edit_index_get()].name);
        }
        else if (door_camera_password_input_enter_mode == 0x03)
        {
                lv_textarea_set_placeholder_text(textarea, network_data_get()->cctv_device[device_edit_index_get()].name);
        }
}

static void door_camera_password_input_hidden_click(lv_event_t *ev)
{
        lv_obj_t *obj = lv_event_get_current_target(ev);

        lv_obj_t *textarea = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), door_camera_password_input_obj_id_textarea);

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

static bool door_camera_password_mixture_char_check(const char *string)
{
        bool exist_number = false;
        bool exist_letters = false;
        bool exist_special_characters = false;
        int len = strlen(string);
        for (int i = 0; i < len; i++)
        {
                if (((string[i] >= 'a') && (string[i] <= 'z')) || ((string[i] >= 'A') && (string[i] <= 'Z')))
                {
                        exist_letters = true;
                }
                else if ((string[i] <= '9') && (string[i] >= '0'))
                {
                        exist_number = true;
                }
                else
                {
                        exist_special_characters = true;
                }

                if (exist_letters && exist_number && exist_special_characters)
                {
                        return true;
                }
        }

        return false;
}

static void door_camera_password_input_msgbox_confirm_click(lv_event_t *e)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), door_camera_password_input_obj_id_msgbox);
        if (obj == NULL)
        {
                return;
        }

        lv_obj_del(obj);
}
static void door_camera_password_success_msgbox_confirm_click(lv_event_t *e)
{
        if (door_camera_password_input_enter_mode == 0x02)
        {
                sat_layout_goto(camera_search_display, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
        }
        else if ((door_camera_password_input_enter_mode == 0x00) || (door_camera_password_input_enter_mode == 0x01))
        {
                sat_layout_goto(door_camera_registed, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
        }
        else if (door_camera_password_input_enter_mode == 0x03)
        {
                sat_layout_goto(cctv_registered, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
        }
}

static void door_camera_password_input_keyboard_click(lv_event_t *ev)
{
        lv_obj_t *obj = lv_event_get_target(ev);
        uint16_t btn_id = lv_btnmatrix_get_selected_btn(obj);
        lv_keyboard_mode_t mode = lv_keyboard_get_mode(obj);
        if ((((mode == LV_KEYBOARD_MODE_TEXT_LOWER) || (mode == LV_KEYBOARD_MODE_TEXT_UPPER)) && (btn_id != 41)) ||
            ((mode == LV_KEYBOARD_MODE_SPECIAL) && (btn_id != 43)))
        {
                return;
        }

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明:没有9个字符，修改失败
        ***********************************************/
        lv_obj_t *textarea = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), door_camera_password_input_obj_id_textarea);
        const char *txt = lv_textarea_get_text(textarea);
        if ((door_camera_password_input_enter_mode == 0x00 || door_camera_password_input_enter_mode == 0x02) && (strlen(txt) != 9))
        {
                return;
        }

        if (door_camera_password_input_enter_mode == 0x02)
        {
                lv_obj_t *textarea = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), door_camera_password_input_obj_id_textarea);

                const network_device_info *device_info = camera_search_display_pview_sip_user_get();
                network_device_info device_info_temp = *device_info;
                memset(device_info_temp.password, 0, sizeof(device_info_temp.password));
                strcpy(device_info_temp.password, lv_textarea_get_text(textarea));

                camera_search_display_pview_sip_user_setting(&device_info_temp);
                camera_search_display_enter_mode_setting(1);
                sat_layout_goto(camera_search_display, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
        }
        else if (door_camera_password_input_enter_mode == 0x00)
        {
                if (door_camera_password_state == 0x01)
                {
                        if (door_camera_password_mixture_char_check(txt) == false)
                        {
                                door_camera_password_input_msgbox_create(layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_PASSWORD),
                                                                         layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_SET_THE_PASSWORD_TO_A_MIXTURE),
                                                                         door_camera_password_input_msgbox_confirm_click);
                                return;
                        }

                        if (door_camera_password_input_password_temp[0] == 0)
                        {
                                lv_obj_t *textarea = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), door_camera_password_input_obj_id_textarea);
                                strcpy(door_camera_password_input_password_temp, lv_textarea_get_text(textarea));
                                lv_textarea_set_text(textarea, "");
                                door_camera_password_input_textarea_placeholder_setting();
                        }
                        else
                        {
                                lv_obj_t *textarea = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), door_camera_password_input_obj_id_textarea);
                                if (strcmp(door_camera_password_input_password_temp, lv_textarea_get_text(textarea)) == 0)
                                {
                                        const network_device_info *device_info = door_camera_password_input_enter_mode == 0X02 ? camera_search_display_pview_sip_user_get()
                                                                                                                               : &(network_data_get()->door_device[device_edit_index_get()]);
                                        char *ip = strchr(device_info->user, '@') + 1;
                                        if ((ip != NULL) && (user_network_device_password_modiy(ip, door_camera_password_input_password_old, door_camera_password_input_password_temp, 1000) == 1))
                                        {
                                                door_camera_password_input_msgbox_create(layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_PASSWORD),
                                                                                         layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_PASSWORD_MODIY_SUCCESS),
                                                                                         door_camera_password_success_msgbox_confirm_click);

                                                if (door_camera_password_input_enter_mode == 0x02)
                                                {
                                                        network_device_info device_info_temp;
                                                        memcpy(&device_info_temp, device_info, sizeof(network_device_info));
                                                        strcpy(device_info_temp.password, door_camera_password_input_password_temp);
                                                        camera_search_display_pview_sip_user_setting(&device_info_temp);
                                                }
                                                else if (door_camera_password_input_enter_mode == 0x00)
                                                {
                                                        memset(network_data_get()->door_device[device_edit_index_get()].password, 0, sizeof(network_data_get()->door_device[device_edit_index_get()].password));
                                                        memcpy(network_data_get()->door_device[device_edit_index_get()].password, door_camera_password_input_password_temp, 9);
                                                        network_data_save();
                                                }
                                                return;
                                        }
                                }

                                door_camera_password_input_msgbox_create(layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_PASSWORD),
                                                                         layout_setting_password_language_get(SETTING_PASSWORD_LANG_ID_PASSWORD_NOT_MATCH),
                                                                         door_camera_password_input_msgbox_confirm_click);
                        }
                }
                else if (door_camera_password_state == 0x00)
                {
                        lv_obj_t *textarea = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), door_camera_password_input_obj_id_textarea);
                        const char *input_password = lv_textarea_get_text(textarea);

                        char *ip = strchr(network_data_get()->door_device[device_edit_index_get()].user, '@') + 1;
                        if ((ip != NULL) && (user_network_device_password_modiy(ip, input_password, "leo", 1000) == 0))
                        {
                                door_camera_password_state = 0x01;
                                strcpy(door_camera_password_input_password_old, input_password);

                                memset(door_camera_password_input_password_temp, 0, sizeof(door_camera_password_input_password_temp));
                                lv_textarea_set_text(textarea, "");
                                door_camera_password_input_textarea_placeholder_setting();
                        }
                        else
                        {
                                door_camera_password_input_msgbox_create(layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_PASSWORD),
                                                                         layout_setting_password_language_get(SETTING_PASSWORD_LANG_ID_PASSWORD_NOT_MATCH),
                                                                         door_camera_password_input_msgbox_confirm_click);
                        }
                }
        }
        else if (door_camera_password_input_enter_mode == 0x01)
        {
                lv_obj_t *textarea = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), door_camera_password_input_obj_id_textarea);
                const char *input_name = lv_textarea_get_text(textarea);

                char *ip = strchr(network_data_get()->door_device[device_edit_index_get()].user, '@') + 1;
                if ((ip != NULL) && (user_network_device_name_modiy(ip, network_data_get()->door_device[device_edit_index_get()].password, network_data_get()->sip_user, input_name, 1000) == true))
                {
                        memset(network_data_get()->door_device[device_edit_index_get()].name, 0, sizeof(network_data_get()->door_device[device_edit_index_get()].name));
                        strcpy(network_data_get()->door_device[device_edit_index_get()].name, input_name);
                        network_data_save();

                        door_camera_password_input_msgbox_create(layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_PASSWORD),
                                                                 layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_NAME_MODIY_SUCCESS),
                                                                 door_camera_password_success_msgbox_confirm_click);

                        return;
                }
                door_camera_password_input_msgbox_create(network_data_get()->door_device[device_edit_index_get()].name,
                                                         layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_NAME_MODIY_FAIL),
                                                         door_camera_password_input_msgbox_confirm_click);
        }
        else if (door_camera_password_input_enter_mode == 0x03)
        {
                lv_obj_t *textarea = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), door_camera_password_input_obj_id_textarea);
                const char *input_name = lv_textarea_get_text(textarea);

                memset(network_data_get()->cctv_device[device_edit_index_get()].name, 0, sizeof(network_data_get()->cctv_device[device_edit_index_get()].name));
                strcpy(network_data_get()->cctv_device[device_edit_index_get()].name, input_name);
                network_data_save();

                door_camera_password_input_msgbox_create(layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_PASSWORD),
                                                         layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_NAME_MODIY_SUCCESS),
                                                         door_camera_password_success_msgbox_confirm_click);
        }
}
static void sat_layout_enter(door_camera_password_input)
{
        lv_obj_t *textarea;
        memset(door_camera_password_input_password_temp, 0, sizeof(door_camera_password_input_password_temp));
        memset(door_camera_password_input_password_old, 0, sizeof(door_camera_password_input_password_old));
        door_camera_password_state = door_camera_password_input_enter_mode == 0 ? 0 : 1;
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明: 标题显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), door_camera_password_input_obj_id_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      door_camera_password_input_enter_mode == 0x02   ? camera_search_display_pview_sip_user_get()->user
                                      : door_camera_password_input_enter_mode == 0x01 ? layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_CHANGE_NAME)
                                      : door_camera_password_input_enter_mode == 0x03 ? layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_CHANGE_NAME)
                                                                                      : layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_CHANGE_PASSWORD),
                                      0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 上一步
         ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), door_camera_password_input_obj_id_cancel, 35, 15, 48, 48,
                                         door_camera_password_input_cancel_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
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
                textarea = lv_common_textarea_create(sat_cur_layout_screen_get(), door_camera_password_input_obj_id_textarea, 48, 80, 928, 88,
                                                     NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0X101010,
                                                     LV_OPA_COVER, 0Xffffff, LV_OPA_COVER, 0Xffffff,
                                                     0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                     0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                     NULL, 0Xffffff, 0Xffffff, LV_TEXT_ALIGN_LEFT, lv_font_normal, 9,
                                                     30, 500, 0Xffffff);

                lv_obj_set_style_text_color(textarea, lv_color_hex(0x929292), LV_PART_TEXTAREA_PLACEHOLDER);
                lv_obj_set_style_text_opa(textarea, LV_OPA_COVER, LV_PART_TEXTAREA_PLACEHOLDER);
                lv_obj_add_state(textarea, LV_STATE_FOCUSED);
                lv_textarea_set_password_bullet(textarea, "*");
                door_camera_password_input_textarea_placeholder_setting();
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:43:29
        ** 说明: 隐藏按钮
        ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), door_camera_password_input_obj_id_password_hidden, 928, 100, 48, 48,
                                         door_camera_password_input_hidden_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_list_show.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:43:29
         ** 说明: 键盘
         ***********************************************/
        {

                lv_obj_t *keyboard = lv_common_keyboard_create(sat_cur_layout_screen_get(), door_camera_password_input_obj_id_keyboard, 0, 200, 1024, 400,
                                                               door_camera_password_input_keyboard_click, LV_OPA_COVER, 0x292929, LV_OPA_COVER, 0x00a8ff,
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
static void sat_layout_quit(door_camera_password_input)
{
}

sat_layout_create(door_camera_password_input);