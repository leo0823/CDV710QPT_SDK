#include "layout_define.h"
#include "layout_setting_version_information.h"
#include "layout_setting_general.h"
#include "common/user_upgrade.h"
enum
{
        setting_version_information_obj_id_title,
        setting_version_information_obj_id_cancel,
        setting_version_information_obj_id_list,

        setting_version_information_obj_id_current_version_cont,
        setting_version_information_obj_id_current_version_title,
        setting_version_information_obj_id_current_version_sub,

        setting_version_information_obj_id_update_version_cont,

        ssetting_version_information_obj_id_msgbox_cont,
        ssetting_version_information_obj_id_msgbox_parent,
        ssetting_version_information_obj_id_msgbox_text,
};
static void setting_version_information_cancel_obj_click(lv_event_t *e)
{
        sat_layout_goto(setting_general, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
}
static lv_obj_t *setting_version_infomration_msgbox_create(const char *text)
{
        lv_obj_t *parent = lv_common_img_btn_create(sat_cur_layout_screen_get(), ssetting_version_information_obj_id_msgbox_cont, 0, 0, 1024, 600,
                                                    NULL, true, LV_OPA_80, 0, LV_OPA_80, 0,
                                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                    0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                    NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

        lv_obj_t *msgbox = lv_common_img_btn_create(parent, ssetting_version_information_obj_id_msgbox_parent, 387, 263, 250, 75,
                                                    NULL, false, LV_OPA_COVER, 0x242526, LV_OPA_TRANSP, 0,
                                                    10, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                    10, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                    NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

        lv_common_text_create(msgbox, ssetting_version_information_obj_id_msgbox_text, 0, 22, 250, 30,
                              NULL, LV_OPA_TRANSP, 0x323237, LV_OPA_TRANSP, 0,
                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_COVER, 0x323237,
                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_COVER, 0x323237,
                              text, 0Xffffff, 0Xffffff, LV_TEXT_ALIGN_CENTER, lv_font_small);

        return parent;
}

static void setting_version_information_timer(lv_timer_t *ptimer)
{
        if (outdoor_network_enable_status_get() == false)
        {
                sat_layout_goto(setting_version_information, LV_SCR_LOAD_ANIM_NONE, SAT_VOID);
        }
}

static void setting_version_information_update_click(lv_event_t *e)
{
        lv_obj_t *obj = lv_event_get_current_target(e);
        if (obj == NULL)
        {
                return;
        }

        lv_obj_t *parent = lv_obj_get_parent(obj);
        if (parent == NULL)
        {
                return;
        }

        lv_obj_t *label = lv_obj_get_child_form_id(parent, 0);
        if (label == NULL)
        {
                return;
        }

        char user[128] = {0};
        char ip[32] = {0};

        if (sip_user_get_number_and_ip(network_data_get()->door_device[parent->id].user, ip, user) == true)
        {

                char msg[128] = {0};
                sprintf(msg, "%s %s", lv_label_get_text(label), layout_setting_version_information_language_get(SETTING_VERSION_INFORMATION_LANG_ID_UPDATE_ING));
                setting_version_infomration_msgbox_create(msg);

                outdoor_network_upgrade(ip);
                lv_sat_timer_create(setting_version_information_timer, 1000, NULL);
        }
}

static void setting_version_information_sd_status_callback(void)
{
        sat_layout_goto(setting_version_information, LV_SCR_LOAD_ANIM_NONE, SAT_VOID);
}

static void setting_version_information_version_get_timer(lv_timer_t *ptimer)
{
        char user[128] = {0};
        char ip[32] = {0};
        char version_buf[128] = {0};

        if (network_data_get()->door_device_count > 0)
        {
                for (int i = 0; i < network_data_get()->door_device_count; i++)
                {
                        memset(user, 0, sizeof(user));
                        memset(ip, 0, sizeof(ip));
                        memset(version_buf, 0, sizeof(version_buf));
                        if (sip_user_get_number_and_ip(network_data_get()->door_device[i].user, ip, user) == true)
                        {
                                user_network_device_version_get(user, ip, version_buf, sizeof(version_buf), 200);
                        }

                        if (version_buf[0] == 0)
                        {
                                strcpy(version_buf, "version unknow");
                        }

                        lv_obj_t *list = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_version_information_obj_id_list);
                        lv_obj_t *item = lv_obj_get_child_form_id(list, i);
                        lv_obj_t *obj = lv_obj_get_child_form_id(item, 1);
                        lv_label_set_text(obj, version_buf);
                }
        }
}

static void sat_layout_enter(setting_version_information)
{
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: 标题显示
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_version_information_obj_id_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      layout_setting_general_language_get(SETTING_GENERAL_LANG_ID_LANG_VERSION_INFORMATION), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:25
        ** 说明: 上一步
        ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_version_information_obj_id_cancel, 35, 15, 48, 48,
                                         setting_version_information_cancel_obj_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 当前版本号显示
         ***********************************************/
        {
                char version_info[128] = {0};
                struct tm tm;
                if (platform_build_date_get(&tm) == true)
                {
                        sprintf(version_info, SYSTEM_VERSION "   build time:%04d-%02d-%02d %02d:%02d:%02d", tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
                }
                else
                {
                        strcpy(version_info, SYSTEM_VERSION);
                }

                lv_common_setting_btn_title_sub_info_img_create(sat_cur_layout_screen_get(), setting_version_information_obj_id_current_version_cont, 48, 88, 928, 72,
                                                                NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                                0, 17, 576, 43, setting_version_information_obj_id_current_version_title,
                                                                layout_setting_version_information_language_get(SETTING_VERSION_INFORMATION_LANG_ID_CURRENT_VERSION), 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                0, 42, 576, 29, setting_version_information_obj_id_current_version_sub,
                                                                version_info, 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                0, 0, 0, 0, -1,
                                                                NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                0, 0, 0, 0, -1,
                                                                NULL, LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 列表
         ***********************************************/
        char user[128] = {0};
        char ip[32] = {0};
        char version_buf[128] = {0};
        bool upgrade = (access(SD_BASE_PATH "/SAT_ANYKA3918OS", F_OK) == 0) ? true : false;
        if (network_data_get()->door_device_count > 0)
        {
                lv_obj_t *list = setting_list_create(sat_cur_layout_screen_get(), setting_version_information_obj_id_list);
                lv_common_style_set_common(list, setting_version_information_obj_id_list, 48, 160, 928, 440, LV_ALIGN_TOP_LEFT, LV_PART_MAIN);

                for (int i = 0; i < network_data_get()->door_device_count; i++)
                {
                        memset(user, 0, sizeof(user));
                        memset(ip, 0, sizeof(ip));
                        memset(version_buf, 0, sizeof(version_buf));
                        if (sip_user_get_number_and_ip(network_data_get()->door_device[i].user, ip, user) == true)
                        {
                                user_network_device_version_get(user, ip, version_buf, sizeof(version_buf), 200);
                        }

                        if (version_buf[0] == 0)
                        {
                                strcpy(version_buf, "version unknow");
                        }
                        lv_obj_t *parent = lv_common_setting_btn_title_sub_info_img_create(list, i, 0, 72 * i, 928, 72,
                                                                                           NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                                                           0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                                                           0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                                                           0, 17, 576, 43, 0,
                                                                                           network_data_get()->door_device[i].name, 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                                           0, 42, 576, 29, 1,
                                                                                           version_buf, 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                                           0, 0, 0, 0, -1,
                                                                                           NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                                           0, 0, 0, 0, -1,
                                                                                           NULL, LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);

                        if (upgrade == true)
                        {
                                lv_obj_t *obj = lv_common_text_create(parent, 3, 800, 12, 124, 48,
                                                                      setting_version_information_update_click, LV_OPA_COVER, 0x00a8FF, LV_OPA_COVER, 0x00a8FF,
                                                                      25, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                                      25, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                                      layout_setting_version_information_language_get(SETTING_VERSION_INFORMATION_LANG_ID_UPDATE), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_normal);

                                lv_obj_set_style_pad_top(obj, 8, LV_PART_MAIN);
                        }
                }
        }
        sd_state_channge_callback_register(setting_version_information_sd_status_callback);

        lv_sat_timer_create(setting_version_information_version_get_timer, 3000, NULL);
}
static void sat_layout_quit(setting_version_information)
{
        sd_state_channge_callback_register(NULL);
}

sat_layout_create(setting_version_information);