#include "layout_define.h"
#include "layout_setting_general.h"
enum
{
  setting_app_integration_obj_id_title,
  setting_app_integration_obj_id_cancel,
  setting_app_integration_obj_id_select_network,
  setting_app_integration_obj_id_msgbox_bg,
  setting_app_integration_obj_id_connect_status_title,
  setting_app_integration_obj_id_connect_status_tips,
  setting_app_integration_obj_id_connect_status,

};

static void setting_app_integation_cancel_obj_click(lv_event_t *e)
{
  sat_layout_goto(setting_general, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
}

static void setting_app_integation_cancel_click(lv_event_t *ev)
{
  setting_msgdialog_msg_del(setting_app_integration_obj_id_msgbox_bg);
}

static void setting_app_integation_confirm_click(lv_event_t *ev)
{
  setting_msgdialog_msg_del(setting_app_integration_obj_id_msgbox_bg);
}

static void setting_app_connect_msgbox_item_click(lv_event_t *ev)
{

  lv_obj_t *parent = lv_obj_get_child_form_id(lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_app_integration_obj_id_msgbox_bg), 0);

  lv_obj_t *check1 = lv_obj_get_child_form_id(lv_obj_get_child_form_id(parent, 3), 1);

  lv_obj_t *check2 = lv_obj_get_child_form_id(lv_obj_get_child_form_id(parent, 4), 1);

  if (strncmp(check1->bg_img_src, "btn_radio_s.png", strlen("btn_radio_s.png")))
  {
    lv_obj_set_style_bg_img_src(check1, resource_ui_src_get("btn_radio_n.png"), LV_PART_MAIN);
  }
  if (strncmp(check2->bg_img_src, "btn_radio_s.png", strlen("btn_radio_s.png")))
  {
    lv_obj_set_style_bg_img_src(check2, resource_ui_src_get("btn_radio_n.png"), LV_PART_MAIN);
  }

  lv_obj_t *obj = lv_event_get_current_target(ev);
  lv_obj_t *check = lv_obj_get_child_form_id(obj, 1);
  lv_obj_set_style_bg_img_src(check, resource_ui_src_get("btn_radio_s.png"), LV_PART_MAIN);
}

static void layout_app_integration_select_network_click(lv_event_t *ev)
{
  lv_obj_t *masgbox = setting_msgdialog_msg_bg_create(setting_app_integration_obj_id_msgbox_bg, 0, 282, 143, 460, 343);

  setting_msgdialog_msg_create(masgbox, 0, lang_str_get(SETTING_APP_INTEGRATION_XLS_LANG_IS_CONNECTION_NETWORK), 30, 20, 400, 50, true);
  setting_msgdialog_msg_confirm_and_cancel_btn_create(masgbox, 1, 2, setting_app_integation_cancel_click, setting_app_integation_confirm_click);

  lv_common_img_text_btn_create(masgbox, 3, 20, 100, 366, 55,
                                setting_app_connect_msgbox_item_click, LV_OPA_TRANSP, 0x00, LV_OPA_TRANSP, 0x101010,
                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                46, 8, 366 - 16, 32, 0,
                                "WI-FI", 0xffffff, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                0, 8, 32, 32, 1,
                                (const char *)resource_ui_src_get("btn_radio_n.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

  lv_common_img_text_btn_create(masgbox, 4, 20, 160, 366, 55,
                                setting_app_connect_msgbox_item_click, LV_OPA_TRANSP, 0x00, LV_OPA_TRANSP, 0x101010,
                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                46, 8, 366 - 16, 32, 0,
                                lang_str_get(SETTING_APP_INTEGRATION_XLS_LANG_IS_ETHERNET), 0xffffff, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                0, 8, 32, 32, 1,
                                (const char *)resource_ui_src_get("btn_radio_s.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
}

static void layout_setting_app_integration_connect_status_display(void)
{
  lv_common_text_create(sat_cur_layout_screen_get(), setting_app_integration_obj_id_connect_status_title, 0, 173, 1024, 64,
                        NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                        lang_str_get(SETTING_APP_INTEGRATION_XLS_LANG_IS_CONNECT_STATUS_TITLE), 0xffffff, 0xffffff, LV_TEXT_ALIGN_CENTER, lv_font_normal);

  lv_common_img_text_btn_create(sat_cur_layout_screen_get(), setting_app_integration_obj_id_connect_status, 0, 260, 1024, 180,
                                NULL, LV_OPA_TRANSP, 0x00, LV_OPA_TRANSP, 0x101010,
                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                0, 120, 1024, 32, 0,
                                lang_str_get(SETTING_APP_INTEGRATION_XLS_LANG_IS_ETHERNET), 0xffffff, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_normal,
                                449, 8, 126, 126, 1,
                                (const char *)resource_ui_src_get("ic_system_clood_connect.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

  lv_common_text_create(sat_cur_layout_screen_get(), setting_app_integration_obj_id_connect_status_tips, 0, 433, 1024, 78,
                        NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                        0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                        lang_str_get(SETTING_APP_INTEGRATION_XLS_LANG_IS_CONNECT_STATUS_WARN), 0xb8b8b8, 0xb8b8b8, LV_TEXT_ALIGN_CENTER, lv_font_normal);
}
static void sat_layout_enter(setting_app_integration)
{
  /***********************************************
   ** 作者: leo.liu
   ** 日期: 2023-2-2 13:46:56
   ** 说明: 标题显示
   ***********************************************/
  {
    lv_common_text_create(sat_cur_layout_screen_get(), setting_app_integration_obj_id_title, 0, 20, 1024, 40,
                          NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                          0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                          0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                          lang_str_get(SETTING_GENERAL_XLS_LANG_ID_APP_INTEGRATION), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
  }

  /***********************************************
  ** 作者: leo.liu
  ** 日期: 2023-2-2 13:42:25
  ** 说明: 上一步
  ***********************************************/
  {
    lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_app_integration_obj_id_cancel, 35, 15, 48, 48,
                             setting_app_integation_cancel_obj_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                             0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                             0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                             resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
  }

  lv_common_setting_btn_title_sub_info_img_create(sat_cur_layout_screen_get(), setting_app_integration_obj_id_select_network, 48, 80, 928, 88,
                                                  layout_app_integration_select_network_click, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                  0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                  0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                  0, 17, 300, 43, 0,
                                                  lang_str_get(SETTING_APP_INTEGRATION_XLS_LANG_IS_SELECT_NETWORK), 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                  370, 17, 120, 40, -1,
                                                  "", 0x00a8ff, 0x6d6d79, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                  0, 50, 576, 29, 1,
                                                  "WIFI(Not set)", 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                  0, 0, 80, 48, -1,
                                                  NULL, LV_OPA_COVER, 0x00a8ff, LV_ALIGN_RIGHT_MID);

  layout_setting_app_integration_connect_status_display();
}
static void sat_layout_quit(setting_app_integration)
{
}

sat_layout_create(setting_app_integration);