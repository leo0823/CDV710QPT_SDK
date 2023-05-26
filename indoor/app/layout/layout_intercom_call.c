#include "layout_define.h"
#include "layout_intercom_call.h"
#include "layout_home.h"
enum
{
        intercom_call_obj_id_title,
        intercom_call_obj_id_cancel,
        intercom_call_obj_id_tabview,
        intercom_call_obj_id_externsion,
        intercom_call_obj_id_guard,
        intercom_call_obj_id_id_base,

        intercom_call_obj_id_list = intercom_call_obj_id_id_base + 8,
};

static void intercom_call_cancel_obj_click(lv_event_t *e)
{
        sat_layout_goto(home, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
}

static lv_obj_t *intercom_call_table_view_obj_create(void)
{
        lv_obj_t *tabview = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), intercom_call_obj_id_tabview);
        if (tabview != NULL)
        {
                return tabview;
        }
        tabview = lv_tabview_create(sat_cur_layout_screen_get(), LV_DIR_TOP, 56);
        lv_common_style_set_common(tabview, intercom_call_obj_id_tabview, 0, 80, 1024, 464 + 56, LV_ALIGN_TOP_LEFT, LV_PART_MAIN);

        lv_obj_t *cont = lv_tabview_get_content(tabview);
        lv_common_style_set_common(cont, 0, 0, 56, 1024, 464, LV_ALIGN_CENTER, LV_PART_MAIN);
        lv_obj_t *page_1 = lv_tabview_add_tab(tabview, layout_intercom_language_get(INTERCOM_LANG_ID_CAll_CHANNEL));
        lv_common_style_set_common(page_1, 0, 0, 0, 1024, 464, LV_ALIGN_TOP_LEFT, LV_PART_MAIN);
        lv_obj_t *page_2 = lv_tabview_add_tab(tabview, layout_intercom_language_get(INTERCOM_LANG_ID_CAll_LOG));
        lv_common_style_set_common(page_2, 1, 0, 0, 1024, 464, LV_ALIGN_TOP_LEFT, LV_PART_MAIN);

        lv_obj_t *btnmatrix = lv_tabview_get_tab_btns(tabview);
        lv_common_style_set_common(btnmatrix, 1, 0, 8, 1024, 40, LV_ALIGN_CENTER, LV_PART_MAIN);
        lv_common_style_set_text(btnmatrix, NULL, 0XFFFFFF, 0XFFFFFF, LV_ALIGN_CENTER, lv_font_normal, LV_STATE_PRESSED | LV_STATE_CHECKED, LV_PART_MAIN);
        lv_common_style_set_event(btnmatrix, NULL, true, LV_OPA_TRANSP, 0XFFFFFF, LV_PART_ITEMS, LV_OPA_COVER, 0x101010, LV_PART_ITEMS | LV_STATE_CHECKED);

        lv_common_style_set_boader(btnmatrix, 20, LV_OPA_TRANSP, 0, LV_BORDER_SIDE_NONE, 0XFFFFFF, LV_PART_ITEMS);
        lv_common_style_set_boader(btnmatrix, 20, LV_OPA_TRANSP, 0, LV_BORDER_SIDE_NONE, 0XFFFFFF, LV_PART_ITEMS | LV_STATE_CHECKED);

        lv_obj_set_style_pad_left(btnmatrix, 352, LV_PART_MAIN);
        lv_obj_set_style_pad_right(btnmatrix, 352, LV_PART_MAIN);

        return tabview;
}

static void intercom_extension_obj_click(lv_event_t *e)
{
}

static void intercom_id_obj_click(lv_event_t *e)
{
        lv_obj_t *obj = lv_event_get_target(e);
        uint32_t index = lv_btnmatrix_get_selected_btn(obj) + 1;

        //  network_device_info device_info;
        //  memset(&device_info, 0, sizeof(network_device_info));
        // if (sat_sip_local_indoor_number_get(id, device_info.user) == true)
        {
                if (sat_ipcamera_device_name_get(index, 300) == true)
                // if (user_network_user_update((unsigned char *)network_data_get()->sip_user, &device_info, 300) >= 0)
                {
                        intercom_call_status_setting(1);
                        // intercom_call_username_setting(device_info.user);
                        intercom_call_username_setting(sat_ipcamera_node_data_get(index)->sip_url);
                        sat_layout_goto(intercom_talk, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
                }
        }
}
static void sat_layout_enter(intercom_call)
{
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明: 标题显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), intercom_call_obj_id_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      layout_home_language_get(HOME_LANG_ID_CALL), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 上一步下一步
         ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), intercom_call_obj_id_cancel, 35, 15, 48, 48,
                                         intercom_call_cancel_obj_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明:table view 创建
         ***********************************************/
        lv_obj_t *tabview = intercom_call_table_view_obj_create();
        {
                lv_obj_t *cont = lv_tabview_get_content(tabview);
                lv_obj_t *page_1 = lv_obj_get_child_form_id(cont, 0);
                {
                        lv_obj_t *txt_obj = lv_common_text_create(page_1, intercom_call_obj_id_externsion, 0, 8, 231, 231,
                                                                  intercom_extension_obj_click, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x0096ff,
                                                                  0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                                  0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                                  layout_intercom_language_get(INTERCOM_LANG_ID_EXTENSION), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_normal);

                        lv_obj_set_style_pad_top(txt_obj, 94, LV_PART_MAIN);
                        lv_obj_set_style_bg_color(txt_obj, lv_color_hex(0x0096ff), LV_STATE_USER_1);
                        lv_obj_set_style_bg_opa(txt_obj, LV_OPA_COVER, LV_STATE_USER_1);
                        lv_obj_add_state(txt_obj, LV_STATE_USER_1);

                        txt_obj = lv_common_text_create(page_1, intercom_call_obj_id_guard, 0, 231 + 8, 231, 231,
                                                        intercom_extension_obj_click, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x0096ff,
                                                        0, 1, LV_BORDER_SIDE_RIGHT, LV_OPA_COVER, 0x101010,
                                                        0, 1, LV_BORDER_SIDE_RIGHT, LV_OPA_COVER, 0x101010,
                                                        layout_intercom_language_get(INTERCOM_LANG_ID_GUARD), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_normal);

                        lv_obj_set_style_pad_top(txt_obj, 94, LV_PART_MAIN);
                        lv_obj_set_style_bg_color(txt_obj, lv_color_hex(0x0096ff), LV_STATE_USER_1);
                        lv_obj_set_style_bg_opa(txt_obj, LV_OPA_COVER, LV_STATE_USER_1);

                        lv_obj_t *btnmatrix = lv_common_number_input_keyboard_create(page_1, intercom_call_obj_id_id_base, 231, 8, 793, 384,
                                                                                     intercom_id_obj_click, LV_OPA_TRANSP, 0x00, LV_OPA_TRANSP, 0x00a8ff,
                                                                                     0, 1, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0x101010,
                                                                                     0, 3, LV_BORDER_SIDE_FULL, LV_OPA_COVER, 0x101010,
                                                                                     0XFFFFFF, 0XFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large,
                                                                                     0, 0);

                        lv_obj_set_style_bg_color(btnmatrix, lv_color_hex(0x194861), LV_STATE_DISABLED | LV_PART_ITEMS);
                        lv_obj_set_style_bg_opa(btnmatrix, LV_OPA_COVER, LV_STATE_DISABLED | LV_PART_ITEMS);

                        static const char *btnm_map[] = {
                            "ID\n1", "ID\n2", "ID\n3", "\n",
                            "ID\n4", "ID\n5", "ID\n6", "\n",
                            "ID\n7", "ID\n8", "ID\n9", ""};
                        static const char *btnm_img_map[] = {
                            NULL,
                            NULL,
                            NULL,
                            NULL,
                            NULL,
                            NULL,
                            NULL,
                            NULL,
                        };
                        lv_btnmatrix_set_map(btnmatrix, btnm_map);
                        lv_btnmatrix_set_btn_bg_map(btnmatrix, btnm_img_map);
                        lv_btnmatrix_set_btn_ctrl(btnmatrix, 8, LV_BTNMATRIX_CTRL_HIDDEN);
                        lv_btnmatrix_set_btn_ctrl(btnmatrix, network_data_get()->sip_user[11] - 49, LV_BTNMATRIX_CTRL_DISABLED);
                }
        }
}

static void sat_layout_quit(intercom_call)
{
}
sat_layout_create(intercom_call);
