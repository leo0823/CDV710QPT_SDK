#include "layout_define.h"
#include "layout_door_camera_registed.h"
#include "layout_setting_storage_space.h"
enum
{
        door_camera_search_obj_id_title,
        door_camera_search_obj_id_cancel,
        door_camera_search_obj_id_next,

        door_camera_search_obj_id_door_camera_search_cont,
        door_camera_search_obj_id_door_camera_search_text,
        door_camera_search_obj_id_door_camera_search_img,

        door_camera_search_obj_id_registered_door_camera_title,
        door_camera_search_obj_id_door_camera_list,

        door_camera_search_obj_id_msgbox,
};

static lv_obj_t *door_camera_search_msgbox_create(const char *title, const char *msg, lv_event_cb_t cancel_cb, lv_event_cb_t confirm_cb)
{
        lv_obj_t *parent = lv_common_img_btn_create(sat_cur_layout_screen_get(), door_camera_search_obj_id_msgbox, 0, 0, 1024, 600,
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

        lv_common_img_btn_create(msgbox, 2, 0, 281, 230, 62,
                                 cancel_cb, true, LV_OPA_COVER, 0x47494A, LV_OPA_COVER, 0x47494A,
                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                 resource_ui_src_get("btn_title_cancel.png"), LV_OPA_TRANSP, 0x0096FF, LV_ALIGN_CENTER);

        lv_common_img_btn_create(msgbox, 3, 230, 281, 230, 62,
                                 confirm_cb, true, LV_OPA_COVER, 0x0096FF, LV_OPA_COVER, 0x0096FF,
                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                 resource_ui_src_get("btn_title_confirm.png"), LV_OPA_TRANSP, 0x0096FF, LV_ALIGN_CENTER);

        return parent;
}

static void door_camera_search_cancel_click(lv_event_t *ev)
{
        if (user_data_get()->is_device_init == 0)
        {
                sat_layout_goto(setting_time, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
        }
        else
        {
                sat_layout_goto(setting_installation, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
        }
}
static void door_camera_search_next_click(lv_event_t *ev)
{
        sat_layout_goto(setting_complete, LV_SCR_LOAD_ANIM_MOVE_LEFT, SAT_VOID);
}
static void setting_door_camera_register_list_click(lv_event_t *ev)
{
        lv_obj_t *obj = lv_event_get_current_target(ev);
        if ((obj == NULL) || (obj->id > 7))
        {
                return;
        }

        network_device_info device_info;
        sprintf(device_info.user, "sip:%s", network_data_get()->door_device[obj->id].user);
        strcpy(device_info.name, network_data_get()->door_device[obj->id].name);
        strcpy(device_info.password, network_data_get()->door_device[obj->id].password);
        camera_search_display_pview_sip_user_setting(&device_info);

        camera_search_display_enter_mode_setting(0);
        sat_layout_goto(camera_search_display, LV_SCR_LOAD_ANIM_NONE, SAT_VOID);
}
static void setting_door_camera_register_edit_click(lv_event_t *ev)
{
        lv_obj_t *obj = lv_event_get_current_target(ev);
        if (obj == NULL)
        {
                return;
        }
        lv_obj_t *parent = lv_obj_get_parent(obj);
        if ((parent == NULL) || (parent->id > network_data_get()->door_device_count))
        {
                return;
        }

        device_edit_index_setting(parent->id);
        sat_layout_goto(door_camera_edit, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
}

static void setting_door_camera_register_del_msgbox_confirm_click(lv_event_t *e)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), door_camera_search_obj_id_msgbox);
        if (obj == NULL)
        {
                return;
        }

        lv_obj_t *item = (lv_obj_t *)obj->user_data;
        int device_index = item->id;
        if ((item == NULL) || (device_index > 7))
        {
                return;
        }

        if (user_network_device_delete(&(network_data_get()->door_device[device_index]), 1000) == false)
        {
                SAT_DEBUG("del %s failed", network_data_get()->door_device[device_index].user);
        }

        if (device_index == (network_data_get()->door_device_count - 1))
        {
                memset(&(network_data_get()->door_device[device_index]), 0, sizeof(network_data_get()->door_device[device_index]));
        }
        else
        {
                memmove(&network_data_get()->door_device[device_index], &network_data_get()->door_device[device_index + 1], sizeof(network_device_info) * (network_data_get()->door_device_count - device_index - 1));
        }
        network_data_get()->door_device_count--;
        network_data_save();
        sat_layout_goto(door_camera_registed, LV_SCR_LOAD_ANIM_NONE, SAT_VOID);
}

static void setting_door_camera_register_del_cancel_click(lv_event_t *e)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), door_camera_search_obj_id_msgbox);
        if (obj == NULL)
        {
                return;
        }
        lv_obj_del(obj);
}

static void setting_door_camera_register_del_click(lv_event_t *ev)
{
        lv_obj_t *obj = lv_event_get_current_target(ev);
        if (obj == NULL)
        {
                return;
        }
        lv_obj_t *parent = lv_obj_get_parent(obj);
        if ((parent == NULL) || (parent->id > 7))
        {
                return;
        }

        lv_obj_t *msgbox = door_camera_search_msgbox_create(layout_setting_storage_space_language_get(SETTING_STORAGE_LANG_ID_DELETE),
                                                            layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_DO_YOU_WANT_DELETE_DOOR_CAMERA),
                                                            setting_door_camera_register_del_cancel_click, setting_door_camera_register_del_msgbox_confirm_click);

        msgbox->user_data = parent;
}
static void setting_door_camera_add_serch_click(lv_event_t *ev)
{
        sat_layout_goto(door_camera_search, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
}

static lv_obj_t *setting_door_camera_search_list_create(void)
{
        lv_obj_t *list = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), door_camera_search_obj_id_door_camera_list);
        if (list != NULL)
        {
                return list;
        }
        list = lv_list_create(sat_cur_layout_screen_get());
        lv_common_style_set_common(list, door_camera_search_obj_id_door_camera_list, 48, 194, 928, (600 - 194), LV_ALIGN_TOP_LEFT, LV_PART_MAIN);
        return list;
}

static lv_obj_t *door_camera_register_list_create(void)
{
        lv_obj_t *list = setting_door_camera_search_list_create();

        lv_obj_clean(list);

        int item_y = 0;
        char number[128] = {0};
        char ip[32] = {0};
        for (int i = 0; i < network_data_get()->door_device_count; i++)
        {
                memset(number, 0, sizeof(number));
                memset(ip, 0, sizeof(ip));
                sip_user_get_number_and_ip(network_data_get()->door_device[i].user, ip, number);

                int check_online = user_network_device_online((unsigned char *)network_data_get()->sip_user, &(network_data_get()->door_device[i]), 100);
                if (check_online == 1)
                {
                        network_data_save();
                }

                lv_obj_t *parent = lv_common_setting_btn_title_sub_info_img_create(list, i, 0, item_y, 928, 88,
                                                                                   setting_door_camera_register_list_click, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                                                   0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                                                   0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                                                   58, 8, 838, 50, 0,
                                                                                   network_data_get()->door_device[i].name, 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                                   58, 45, 838, 50, 1,
                                                                                   network_data_get()->door_device[i].user, 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                                   0, 0, 0, 0, -1,
                                                                                   NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                                   0, 20, 48, 48, 2,
                                                                                   resource_ui_src_get(check_online >= 0 ? "ic_detect.png" : "ic_error.png"), LV_OPA_TRANSP, 0, LV_ALIGN_CENTER);

                lv_common_img_btn_create(parent, 3, 808, 20, 48, 48,
                                         setting_door_camera_register_edit_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_list_edit.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);

                lv_common_img_btn_create(parent, 4, 880, 20, 48, 48,
                                         setting_door_camera_register_del_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_list_delete.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);

                item_y += 88;
        }

        return list;
}

static void door_camera_register_timer(lv_timer_t *ptimer)
{
        bool update = false;
        for (int i = 0; i < network_data_get()->door_device_count; i++)
        {
                if (user_network_user_update((unsigned char *)network_data_get()->sip_user, &(network_data_get()->door_device[i]), 300) != 0)
                {
                        update = true;
                }
        }

        if (update == true)
        {
                network_data_save();
                door_camera_register_list_create();
        }
}

static void sat_layout_enter(door_camera_registed)
{
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: 标题显示
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), door_camera_search_obj_id_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_DOOR_CAMERA), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 上一步下一步
         ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), door_camera_search_obj_id_cancel, 35, 15, 48, 48,
                                         door_camera_search_cancel_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
                if (user_data_get()->is_device_init == 0)
                {
                        lv_common_img_btn_create(sat_cur_layout_screen_get(), door_camera_search_obj_id_next, 952, 15, 48, 48,
                                                 door_camera_search_next_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 resource_ui_src_get("btn_title_next.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
                }
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:50
         ** 说明: 搜索户外机
         ***********************************************/
        {
                lv_common_img_text_btn_create(sat_cur_layout_screen_get(), door_camera_search_obj_id_door_camera_search_cont, 384, 95, 319, 35,
                                              setting_door_camera_add_serch_click, LV_OPA_TRANSP, 0x00, LV_OPA_TRANSP, 0x101010,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              96, 0, 223, 35, door_camera_search_obj_id_door_camera_search_text,
                                              layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_DOOR_CAMERA_SEARCH), 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                              0, 1, 80, 32, door_camera_search_obj_id_door_camera_search_img,
                                              (const char *)resource_ui_src_get("wifi_add.png"), LV_OPA_50, 0x00a8ff, LV_ALIGN_CENTER);
        }

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:50
         ** 说明: 搜索户外机
         ***********************************************/
        {
                /***********************************************
                 ** 作者: leo.liu
                 ** 日期: 2023-2-2 13:42:50
                 ** 说明: 显示注册的设备
                 ***********************************************/
                if (network_data_get()->door_device_count > 0)
                {
                        lv_obj_t *obj = lv_common_text_create(sat_cur_layout_screen_get(), door_camera_search_obj_id_registered_door_camera_title, 0, 146, 584, 48,
                                                              NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                              layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_REGISTERED_DOOR_CAMERA), 0X00A8ff, 0X00A8ff, LV_TEXT_ALIGN_LEFT, lv_font_small);

                        lv_obj_set_style_pad_left(obj, 16, LV_PART_MAIN);

                        door_camera_register_list_create();
                }
        }

        lv_sat_timer_create(door_camera_register_timer, 3000, NULL);
}
static void sat_layout_quit(door_camera_registed)
{
}

sat_layout_create(door_camera_registed);