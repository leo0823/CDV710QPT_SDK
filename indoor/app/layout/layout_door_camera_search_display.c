#include "layout_define.h"
#include "layout_door_camera_registed.h"
#include "layout_setting_password.h"
enum
{
        camera_search_display_obj_id_top_cont,
        camera_search_display_obj_id_title,

        camera_search_display_obj_id_cancel,
        camera_search_display_obj_id_ip_edit,
        camera_search_display_obj_id_if_you,

        camera_search_display_obj_id_register_label,

        camera_search_display_obj_id_msgbox,
};

static network_device_info camera_search_display_pview_device_info = {0};
void camera_search_display_pview_sip_user_setting(const network_device_info *device_info)
{
        memset(&camera_search_display_pview_device_info, 0, sizeof(network_device_info));
        memcpy(&camera_search_display_pview_device_info, device_info, sizeof(network_device_info));
}
const network_device_info *camera_search_display_pview_sip_user_get(void)
{
        return &camera_search_display_pview_device_info;
}

/*
 * 进入模式选择。0：从注册的页面进入，1：从搜索页面进入
 */
static int camera_search_display_enter_mode = 0;
void camera_search_display_enter_mode_setting(int mode)
{
        camera_search_display_enter_mode = mode;
}

static lv_obj_t *camera_search_display_msgbox_create(const char *title, const char *msg, lv_event_cb_t confirm_cb)
{
        lv_obj_t *parent = lv_common_img_btn_create(sat_cur_layout_screen_get(), camera_search_display_obj_id_msgbox, 0, 0, 1024, 600,
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

static void camera_search_display_cancel_click(lv_event_t *ev)
{
        if (camera_search_display_enter_mode == 0)
        {
                sat_layout_goto(door_camera_registed, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
        }
        else if (camera_search_display_enter_mode == 1)
        {
                sat_layout_goto(door_camera_search, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
        }
}
static void camera_search_display_ip_edit_click(lv_event_t *ev)
{
}

static bool camera_search_display_linphone_stream_func(char *str)
{
        lv_common_video_mode_enable(true);
        return true;
}
static void camera_search_display_linphone_msg_confirm_click(lv_event_t *e)
{
        device_password_input_enter_mode_setting(0x02);
        sat_layout_goto(door_camera_password_input, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
}

static bool camera_search_display_linphone_password_func(char *str)
{
        char *p = str, *user = NULL;
        while ((p = strstr(p, "sip:")) != NULL)
        {
                user = p;
                p += 4;
        }

        char *e = strchr(user, '>');
        if (e == NULL)
        {
                SAT_DEBUG("camera_search_display_linphone_password_func");
                return false;
        }
        *e = 0;
        if (strcmp(camera_search_display_pview_device_info.user, user))
        {
                SAT_DEBUG("%s:%s dot math", camera_search_display_pview_device_info.user, user);
                return false;
        }

        sat_linphone_handup(0xFF);
        camera_search_display_msgbox_create(layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_PASSWORD),
                                            layout_setting_password_language_get(SETTING_PASSWORD_LANG_ID_PASSWORD_NOT_MATCH),
                                            camera_search_display_linphone_msg_confirm_click);
        return true;
}

static void camera_search_display_register_click(lv_event_t *ev)
{
        bool number_same = false;
        if (network_data_get()->door_device_count > 7)
        {
                return;
        }

        int count = network_data_get()->door_device_count;
        char *ip = strchr(camera_search_display_pview_device_info.user, '@') + 1;
        char *pview_user_info = strchr(camera_search_display_pview_device_info.user, ':') + 1;
        /**
         * 判断 预览的SIP是否已经注册过了
         *  如果sip账号完全相同，说明该账号已经被注册过了。
         **/
        for (int i = 0; i < network_data_get()->door_device_count; i++)
        {
                /** 判断 预览的SIP是否已经注册过了**/
                if (strncmp(network_data_get()->door_device[i].user, pview_user_info, 12) == 0)
                {
                        if (strcmp(network_data_get()->door_device[i].user + 12, pview_user_info + 12) == 0)
                        {
                                return;
                        }
                        number_same = true;
                        SAT_DEBUG("number same:%s->%s", network_data_get()->door_device[i].user, pview_user_info);
                        break;
                }
        }
        /*
         * 重新获取注册的房号
         */
        char door_number[64] = {0};
        int index = 0, device_index = 0;
        for (; index < DEVICE_MAX; index++)
        {
                if (sat_sip_local_doorcamera_number_get(index, door_number) == false)
                {
                        return;
                }

                for (device_index = 0; device_index < network_data_get()->door_device_count; device_index++)
                {
                        if (strncmp(network_data_get()->door_device[device_index].user, door_number, 12) == 0)
                        {
                                break;
                        }
                }
                if (device_index == network_data_get()->door_device_count)
                {
                        SAT_DEBUG("doornumber:%s", door_number);
                        break;
                }
        }

        if (index >= DEVICE_MAX)
        {
                SAT_DEBUG("device max fail");
                return;
        }

         char user_name[128] = {0};
        sat_sip_local_user_get(user_name);
        if (user_network_doorcamera_device_register(user_name, door_number, camera_search_display_pview_device_info.password, ip, number_same, 100) == true)
        {
                memset(network_data_get()->door_device[count].user, 0, sizeof(network_data_get()->door_device[count].user));
                strcpy(network_data_get()->door_device[count].user, door_number);

                memset(network_data_get()->door_device[count].name, 0, sizeof(network_data_get()->door_device[count].name));
                strcpy(network_data_get()->door_device[count].name, camera_search_display_pview_device_info.name);

                memset(network_data_get()->door_device[count].password, 0, sizeof(network_data_get()->door_device[count].password));
                strcpy(network_data_get()->door_device[count].password, camera_search_display_pview_device_info.password);

                network_data_get()->door_device_count++;
                network_device_sort();
                network_data_save();
                sat_layout_goto(door_camera_registed, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
        }
}
static void camera_search_display_timer(lv_timer_t *ptimer)
{
        return;
        sat_layout_goto(door_camera_search, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
}
static void sat_layout_enter(camera_search_display)
{
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 顶部半透明显示
         ***********************************************/
        {
                lv_obj_t *parent = lv_common_img_btn_create(sat_cur_layout_screen_get(), camera_search_display_obj_id_top_cont, 0, 0, 1024, 160,
                                                            NULL, false, LV_OPA_50, 0, LV_OPA_TRANSP, 0,
                                                            0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                            0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                            NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                {
                        /***********************************************
                         ** 作者: leo.liu
                         ** 日期: 2023-2-2 13:46:56
                         ** 说明: 标题显示
                         ***********************************************/
                        {
                                lv_common_text_create(parent, camera_search_display_obj_id_title, 0, 20, 1024, 40,
                                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      (char *)camera_search_display_pview_device_info.user, 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
                        }

                        /***********************************************
                         ** 作者: leo.liu
                         ** 日期: 2023-2-2 13:42:25
                         ** 说明: 上一步下一步
                         ***********************************************/
                        {
                                lv_common_img_btn_create(parent, camera_search_display_obj_id_cancel, 35, 15, 48, 48,
                                                         camera_search_display_cancel_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                         resource_ui_src_get("btn_title_cancel.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                        }

                        /***********************************************
                         ** 作者: leo.liu
                         ** 日期: 2023-2-2 13:42:25
                         ** 说明: ip
                         ***********************************************/
                        {
                                lv_common_img_btn_create(parent, camera_search_display_obj_id_ip_edit, 952, 15, 48, 48,
                                                         camera_search_display_ip_edit_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                         resource_ui_src_get("btn_title_IPset.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                        }

                        /***********************************************
                         ** 作者: leo.liu
                         ** 日期: 2023-2-2 13:46:56
                         ** 说明: 标题显示
                         ***********************************************/
                        {
                                lv_common_text_create(parent, camera_search_display_obj_id_if_you, 16, 93, 823, 54,
                                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_IF_YOUT_CANNOT_SEE), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_LEFT, lv_font_small);
                        }
                }
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: 标题显示
         ***********************************************/
        {
                lv_obj_t *obj = lv_common_text_create(sat_cur_layout_screen_get(), camera_search_display_obj_id_register_label, 0, 528, 1024, 72,
                                                      camera_search_display_register_click, LV_OPA_COVER, 0X00A8FF, LV_OPA_COVER, 0X00A8FF,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_REGISTRATION), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
                lv_obj_set_style_pad_top(obj, 15, LV_PART_MAIN);
        }

        char call_user[256] = {0};
        sprintf(call_user, "%s/%s", camera_search_display_pview_device_info.user, camera_search_display_pview_device_info.password);
        sat_linphone_call(call_user, true, true, NULL);
        user_linphone_call_password_error_register(camera_search_display_linphone_password_func);
        user_linphone_call_streams_running_receive_register(camera_search_display_linphone_stream_func);

        lv_timer_reset(lv_sat_timer_create(camera_search_display_timer, 5000, NULL));
}
static void sat_layout_quit(camera_search_display)
{
        user_linphone_call_streams_running_receive_register(NULL);
        user_linphone_call_password_error_register(NULL);

        lv_common_video_mode_enable(false);

        sat_linphone_handup(0xFF);
}

sat_layout_create(camera_search_display);
