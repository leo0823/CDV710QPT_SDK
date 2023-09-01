#include "layout_define.h"
#include "layout_ipc_camera.h"
#include "layout_setting_ipaddress.h"

enum
{
        ipc_camera_search_display_obj_id_top_cont,
        ipc_camera_search_display_obj_id_title,

        ipc_camera_search_display_obj_id_cancel,
        ipc_camera_search_display_obj_id_ip_edit,
        ipc_camera_search_display_obj_id_if_you,

        ipc_camera_search_display_obj_id_register_label,

        ipc_camera_search_display_obj_id_regist_msgbox_bg,
        ipc_camera_search_display_obj_id_regist_msgbox_cont,
        ipc_camera_search_display_obj_id_regist_msgbox_title,
        ipc_camera_search_display_obj_id_regist_msgbox_confirm,
};

static void ipc_camera_search_display_cancel_click(lv_event_t *ev)
{
        if (layout_ipc_camera_input_flag_get() & IPC_CAMERA_FLAG_REGISTER)
        {
                sat_layout_goto(ipc_camera_register, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
        }
        else
        {
                sat_layout_goto(ipc_camera_search, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
        }
}

static void ipc_camera_search_display_ip_edit_click(lv_event_t *ev)
{
        extern void layout_setting_setting_server_ipaddress_flag_set(char flag);
        layout_setting_setting_server_ipaddress_flag_set(layout_ipc_cmeara_is_doorcamera_get() ? 0x01 : 0x02);
        sat_layout_goto(setting_server_ipaddress, LV_SCR_LOAD_ANIM_MOVE_LEFT, SAT_VOID);
}

static bool ipc_camera_search_display_register_func(void)
{
#if 0
        int total = 0;
        if (layout_ipc_cmeara_is_doorcamera_get())
        {
                total = DEVICE_MAX; //()->door_device_count;
        }
        else
        {
                total = DEVICE_MAX; // network_data_get()->cctv_device_count;
        }

        /**
         * 判断 预览的SIP是否已经注册过了
         *  如果sip账号完全相同，说明该账号已经被注册过了。
         * 无需判断，如果用户预将通道都设置为同一个ipcamera
         **/

        for (int i = 0; i < total; i++)
        {
                /** 判断 预览的SIP是否已经注册过了**/
                if (layout_ipc_cmeara_is_doorcamera_get() == true)
                {
                        const char *door_sip_uri = sat_ipcamera_sip_addr_get(layout_ipc_camera_edit_index_get());
                        SAT_DEBUG("%s %s", door_sip_uri, network_data_get()->door_device[i].sip_url);
                        if (strcmp(network_data_get()->door_device[i].sip_url, door_sip_uri) == 0)
                        {
                                SAT_DEBUG("strcmp(network_data_get()->door_device[i].user, door_sip_uri) == 0");
                                return false;
                        }
                }
                else
                {
                        const char *door_sip_uri = sat_ipcamera_rtsp_addr_get(layout_ipc_camera_edit_index_get(), 0);
                        if (strcmp(network_data_get()->cctv_device[i].rtsp[0].rtsp_url, door_sip_uri) == 0)
                        {
                                SAT_DEBUG("strcmp(network_data_get()->cctv_device[i].user, door_sip_uri) == 0");
                                return false;
                        }
                }
        }
#endif
        if (layout_ipc_cmeara_is_doorcamera_get() == true)
        {
                for (int i = 0; i < DEVICE_MAX; i++)
                {
                        if (network_data_get()->door_device[i].sip_url[0] == 0)
                        {
                                char number[32] = {0};
                                char ip[16] = {0};
                                sat_ip_mac_addres_get("eth0", ip, NULL, NULL);
                                sprintf(number, "sip:20%d@%s", i + 1, ip);
                                if (sat_ipcamera_device_register(number, layout_ipc_camera_edit_index_get(), 5000) == true)
                                {
                                        memcpy(&network_data_get()->door_device[i], sat_ipcamera_node_data_get(layout_ipc_camera_edit_index_get()), sizeof(struct ipcamera_info));
                                        memset(network_data_get()->door_device[i].sip_url, 0, sizeof(network_data_get()->door_device[i].sip_url));
                                        strncpy(network_data_get()->door_device[i].sip_url, number, sizeof(network_data_get()->door_device[i].sip_url));

                                        // door重命名，不会重置设备的名字，只是方便室内机端查看
                                        char doorname[64] = {0};
                                        sprintf(doorname, "Door%d(%s)", i + 1, network_data_get()->door_device[i].door_name);
                                        memset(network_data_get()->door_device[i].door_name, 0, sizeof(network_data_get()->door_device[i].door_name));
                                        strncpy(network_data_get()->door_device[i].door_name, doorname, strlen(doorname));

                                        network_data_save();
                                       // SAT_DEBUG("%s %s", number, network_data_get()->door_device[i].sip_url);
                                        return true;
                                }
                                return false;
                        }
                }
        }
        else
        {
                for (int i = 0; i < DEVICE_MAX; i++)
                {
                        if (network_data_get()->cctv_device[i].rtsp[0].rtsp_url[0] == 0)
                        {
                                memcpy(&network_data_get()->cctv_device[i], sat_ipcamera_node_data_get(layout_ipc_camera_edit_index_get()), sizeof(struct ipcamera_info));

                                // CCTV重命名，不会重置设备的名字，只是方便室内机端查看
                                char doorname[64] = {0};
                                sprintf(doorname, "CCTV%d(%s)", i + 1, network_data_get()->cctv_device[i].door_name);
                                memset(network_data_get()->cctv_device[i].door_name, 0, sizeof(network_data_get()->cctv_device[i].door_name));
                                strncpy(network_data_get()->cctv_device[i].door_name, doorname, strlen(doorname));

                                network_data_save();

                                return true;
                        }
                }
        }

        return false;
}

static void ipc_camera_search_display_register_failed_confirm_func(lv_event_t *e)
{
        setting_msgdialog_msg_del(ipc_camera_search_display_obj_id_regist_msgbox_bg);
}

static void ipc_camera_search_display_register_click(lv_event_t *ev)
{
        if (ipc_camera_search_display_register_func() == true)
        {
                sat_layout_goto(ipc_camera_register, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
        }
        else
        {
                lv_obj_t *msgbox = setting_msgdialog_msg_bg_create(ipc_camera_search_display_obj_id_regist_msgbox_bg, ipc_camera_search_display_obj_id_regist_msgbox_cont, 282, 93, 460, 352);
                setting_msgdialog_msg_create(msgbox, ipc_camera_search_display_obj_id_regist_msgbox_title, lang_str_get(DOOR_CAMERA_SEARCH_XLS_LANG_ID_REGISTER_FAILDED), 0, 110, 460, 80);
                setting_msgdialog_msg_confirm_btn_create(msgbox, ipc_camera_search_display_obj_id_regist_msgbox_confirm, ipc_camera_search_display_register_failed_confirm_func);
        }
}

static void ipc_camera_display_ipcamera_state_func(unsigned int type, unsigned int num)
{
        char buffer[128] = {0};
        if (type == 2)
        {
                const char *rtsp = sat_ipcamera_rtsp_addr_get(layout_ipc_camera_edit_index_get(), 0);
                if ((rtsp != NULL) && (strstr(rtsp, "rtsp://")))
                {
                        sprintf(buffer, "%s %s %s", rtsp, sat_ipcamera_username_get(layout_ipc_camera_edit_index_get()), sat_ipcamera_password_get(layout_ipc_camera_edit_index_get()));
                       // SAT_DEBUG("%s", buffer);
                        sat_linphone_ipcamera_start(buffer);
                        lv_common_video_mode_enable(true);
                }
        }
}
static void sat_layout_enter(ipc_camera_display)
{
        standby_timer_close();
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 顶部半透明显示
         ***********************************************/
        {
                lv_obj_t *parent = lv_common_img_btn_create(sat_cur_layout_screen_get(), ipc_camera_search_display_obj_id_top_cont, 0, 0, 1024, layout_ipc_cmeara_is_doorcamera_get() == true ? 160 : 130,
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
                                char buffer[32] = {0};
                                sprintf(buffer, "%s", sat_ipcamera_door_name_get(layout_ipc_camera_edit_index_get()));
                                lv_common_text_create(parent, ipc_camera_search_display_obj_id_title, 0, 20, 1024, 40,
                                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      (char *)buffer, 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
                        }

                        /***********************************************
                         ** 作者: leo.liu
                         ** 日期: 2023-2-2 13:42:25
                         ** 说明: 上一步下一步
                         ***********************************************/
                        {
                                lv_common_img_btn_create(parent, ipc_camera_search_display_obj_id_cancel, 35, 15, 48, 48,
                                                         ipc_camera_search_display_cancel_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
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
                                lv_common_img_btn_create(parent, ipc_camera_search_display_obj_id_ip_edit, 952, 15, 48, 48,
                                                         ipc_camera_search_display_ip_edit_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
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
                                lv_common_text_create(parent, ipc_camera_search_display_obj_id_if_you, 16, 93, 823, 54,
                                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      lang_str_get(layout_ipc_cmeara_is_doorcamera_get() ? DOOR_CAMERA_SEARCH_XLS_LANG_ID_IF_YOUT_CANNOT_SEE : DOOR_CAMERA_SEARCH_XLS_LANG_ID_IF_YOUT_CANNOT_REGISTER), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_LEFT, lv_font_small);
                        }
                }
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: 设备注册
         ***********************************************/
        {
                lv_obj_t *obj = lv_common_text_create(sat_cur_layout_screen_get(), ipc_camera_search_display_obj_id_register_label, 0, 528, 1024, 72,
                                                      ipc_camera_search_display_register_click, LV_OPA_COVER, 0X00A8FF, LV_OPA_COVER, 0X00A8FF,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      lang_str_get(DOOR_CAMERA_SEARCH_XLS_LANG_ID_REGISTRATION), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
                lv_obj_set_style_pad_top(obj, 15, LV_PART_MAIN);
        }

        sat_ipcamera_rtsp_url_get(layout_ipc_camera_edit_index_get());

        ipcamera_state_callback_register(ipc_camera_display_ipcamera_state_func);
}
static void sat_layout_quit(ipc_camera_display)
{
        standby_timer_restart(true);
        lv_common_video_mode_enable(false);
        sat_linphone_ipcamera_stop();
        ipcamera_state_callback_register(NULL);
}

sat_layout_create(ipc_camera_display);