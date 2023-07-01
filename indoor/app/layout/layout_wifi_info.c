#include "layout_define.h"
#include "layout_wifi_info.h"
enum
{

        wifi_info_obj_id_title,
        wifi_info_obj_id_cancel,

        wifi_info_obj_id_security_cont,
        wifi_info_obj_id_security_title,
        wifi_info_obj_id_security_sub,

        wifi_info_obj_id_ipaddr_cont,
        wifi_info_obj_id_ipaddr_title,
        wifi_info_obj_id_ipaddr_sub,
};
static wifi_info *p_connected_wifi_info = NULL;
/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:46:56
 ** 说明: 设置连接wifi的信息
 ***********************************************/
void connected_wifi_info_setting(const void *info)
{
        p_connected_wifi_info = (void *)info;
}
static void wifi_info_cancel_click(lv_event_t *ev)
{
        if (user_data_get()->is_device_init == false)
        {
                sat_layout_goto(setting_wifi, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
        }
        else{
                  sat_layout_goto(setting_user_wifi, LV_SCR_LOAD_ANIM_NONE, SAT_VOID);
        }
}
static void sat_layout_enter(wifi_info)
{
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: 标题显示
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), wifi_info_obj_id_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      p_connected_wifi_info->name, 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 上一步
         ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), wifi_info_obj_id_cancel, 35, 15, 48, 48,
                                         wifi_info_cancel_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:50
         ** 说明: security
         ***********************************************/
        {
                lv_common_setting_btn_title_sub_info_img_create(sat_cur_layout_screen_get(), wifi_info_obj_id_security_cont, 48, 80, 928, 88,
                                                                NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                                0, 8, 838, 50, wifi_info_obj_id_security_title,
                                                                lang_str_get(WIFI_INFO_XLS_LANG_ID_SECURITY), 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                0, 45, 838, 50, wifi_info_obj_id_security_sub,
                                                                p_connected_wifi_info->psk_flags, 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                0, 0, 0, 0, -1,
                                                                NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                840, 20, 80, 48, -1,
                                                                NULL, LV_OPA_50, 0x00a8ff, LV_ALIGN_CENTER);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:50
         ** 说明: ipaddres
         ***********************************************/
        {
                lv_common_setting_btn_title_sub_info_img_create(sat_cur_layout_screen_get(), wifi_info_obj_id_ipaddr_cont, 48, 168, 928, 88,
                                                                NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                                0, 8, 838, 50, wifi_info_obj_id_ipaddr_title,
                                                                lang_str_get(WIFI_INFO_XLS_LANG_ID_IP_ADDRES), 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                0, 45, 838, 50, wifi_info_obj_id_ipaddr_sub,
                                                                "192.168.0.2", 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                0, 0, 0, 0, -1,
                                                                NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                840, 20, 80, 48, -1,
                                                                NULL, LV_OPA_50, 0x00a8ff, LV_ALIGN_CENTER);
        }
}
static void sat_layout_quit(wifi_info)
{
}

sat_layout_create(wifi_info);