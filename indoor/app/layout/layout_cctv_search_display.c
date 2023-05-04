#include "layout_define.h"
#include "layout_door_camera_registed.h"
#include "layout_setting_general.h"

extern int cctv_serch_input_index_get(void);

 enum {
        cctv_search_display_obj_id_top_cont,
        cctv_search_display_obj_id_title,

        cctv_search_display_obj_id_cancel,

        cctv_search_display_obj_id_channel_list,

        cctv_search_display_obj_id_register_label,
};

static void cctv_search_display_cancel_click(lv_event_t *ev)
{
        sat_layout_goto(cctv_search, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
}

static void cctv_search_display_register_click(lv_event_t *ev)
{
        lv_obj_t *top = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), cctv_search_display_obj_id_top_cont);
        if (top == NULL)
        {
                return;
        }
        lv_obj_t *list = lv_obj_get_child_form_id(top, cctv_search_display_obj_id_channel_list);
        if (list == NULL)
        {
                return;
        }
        for (int i = 0; i < sat_ipcamera_profile_token_num_get( cctv_serch_input_index_get()); i++)
        {
                lv_obj_t *item = lv_obj_get_child_form_id(list, i);
                if (item != NULL)
                {
                        lv_obj_t *obj = lv_obj_get_child_form_id(item, 1);
                        lv_obj_t *label = lv_obj_get_child_form_id(item, 0);
                        if ((obj != NULL) && (label != NULL) && (strncmp(obj->bg_img_src, resource_ui_src_get("btn_radio_s.png"), strlen(resource_ui_src_get("btn_radio_s.png"))) == 0))
                        {
                                int index = 0;
                                for (; index < network_data_get()->cctv_device_count; index++)
                                {
                                        if (strcmp(network_data_get()->cctv_device[index].user, lv_label_get_text(label)) == 0)
                                        {
                                                return;
                                        }
                                }
                                memset(network_data_get()->cctv_device[index].name, 0, sizeof(network_data_get()->cctv_device[index].name));
                                sprintf(network_data_get()->cctv_device[index].name, "CCTV%d", index + 1);
                                memset(network_data_get()->cctv_device[index].user, 0, sizeof(network_data_get()->cctv_device[index].user));
                                strcpy(network_data_get()->cctv_device[index].user, lv_label_get_text(label));
                                network_data_get()->cctv_device_count++;
                                network_data_save();
                                sat_layout_goto(cctv_registered, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
                                break;
                        }
                }
        }
}

static void cctv_search_display_obj_id_channel_list_click(lv_event_t *e)
{
        lv_obj_t *parent = lv_event_get_current_target(e);
        if (parent == NULL)
        {
                return;
        }
        lv_obj_t *obj = lv_obj_get_child_form_id(parent, 1);
        lv_obj_t *label = lv_obj_get_child_form_id(parent, 0);
        if ((obj == NULL) || (label == NULL))
        {
                return;
        }

        if (strncmp(obj->bg_img_src, resource_ui_src_get("btn_radio_s.png"), strlen(resource_ui_src_get("btn_radio_s.png"))))
        {
                lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_radio_s.png"), LV_PART_MAIN);

                sat_linphone_ipcamera_stop();
                usleep(10 * 1000);

                sat_linphone_ipcamera_start(lv_label_get_text(label));

                lv_obj_t *list = lv_obj_get_parent(parent);
                int n_child = lv_obj_get_child_cnt(list);
                for (int i = 0; i < n_child; i++)
                {
                        lv_obj_t *item = lv_obj_get_child(list, i);
                        if ((item != NULL) && (item != parent))
                        {
                                obj = lv_obj_get_child_form_id(item, 1);
                                if (obj != NULL)
                                {
                                        lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_radio_n.png"), LV_PART_MAIN);
                                }
                        }
                }
        }
}

static void cctv_display_ipcamera_state_func(unsigned int type, unsigned int num)
{
        if (type == 2)
        {
                lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), cctv_search_display_obj_id_top_cont);

                lv_obj_t *list = setting_list_create(parent, cctv_search_display_obj_id_channel_list);
                lv_obj_clean(list);
                lv_common_style_set_common(list, cctv_search_display_obj_id_channel_list, 0, 80, 928, 100, LV_ALIGN_TOP_LEFT, LV_PART_MAIN);

                int j = 0;
                for (int i = 0; i < sat_ipcamera_profile_token_num_get( cctv_serch_input_index_get()); i++)
                {
                        const char *rtsp = sat_ipcamera_rtsp_addr_get( cctv_serch_input_index_get(), i);
                        if (rtsp[0] != 0)
                        {
                                char buffer[128] = {0};
                                sprintf(buffer, "%s %s %s", rtsp, sat_ipcamera_username_get( cctv_serch_input_index_get()), sat_ipcamera_password_get( cctv_serch_input_index_get()));
                                lv_common_img_text_btn_create(list, i, 0, 0 + 40 * j, 928, 40,
                                                              cctv_search_display_obj_id_channel_list_click, LV_OPA_TRANSP, 0x00, LV_OPA_TRANSP, 0x101010,
                                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                              90, 4, 800, 35, 0,
                                                              buffer, 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                              35, 0, 40, 40, 1,
                                                              (const char *)resource_ui_src_get(j == 0 ? "btn_radio_s.png" : "btn_radio_n.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_RIGHT_MID);
                                if (j == 0)
                                {
                                        sat_linphone_ipcamera_stop();
                                        usleep(10 * 1000);
                                        sat_linphone_ipcamera_start(buffer);
                                        lv_common_video_mode_enable(true);
                                }
                                j++;
                        }
                }
        }
}
static void sat_layout_enter(cctv_search_display)
{
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 顶部半透明显示
         ***********************************************/
        lv_obj_t *parent = lv_common_img_btn_create(sat_cur_layout_screen_get(), cctv_search_display_obj_id_top_cont, 0, 0, 1024, 160,
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
                char buffer[32] = {0};
                sprintf(buffer, "CCTV%d", cctv_serch_input_index_get() + 1);
                lv_common_text_create(parent, cctv_search_display_obj_id_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      buffer, 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);

                /***********************************************
                 ** 作者: leo.liu
                 ** 日期: 2023-2-2 13:42:25
                 ** 说明: 上一步下一步
                 ***********************************************/
                lv_common_img_btn_create(parent, cctv_search_display_obj_id_cancel, 35, 15, 48, 48,
                                         cctv_search_display_cancel_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_cancel.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
        }

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: 注册
         ***********************************************/
        {
                lv_obj_t *obj = lv_common_text_create(sat_cur_layout_screen_get(), cctv_search_display_obj_id_register_label, 0, 528, 1024, 72,
                                                      cctv_search_display_register_click, LV_OPA_COVER, 0X00A8FF, LV_OPA_COVER, 0X00A8FF,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_REGISTRATION), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
                lv_obj_set_style_pad_top(obj, 15, LV_PART_MAIN);
        }

        sat_ipcamera_rtsp_url_get( cctv_serch_input_index_get());

        ipcamera_state_callback_register(cctv_display_ipcamera_state_func);
}
static void sat_layout_quit(cctv_search_display)
{
        lv_common_video_mode_enable(false);
        sat_linphone_ipcamera_stop();
        ipcamera_state_callback_register(NULL);
}

sat_layout_create(cctv_search_display);
