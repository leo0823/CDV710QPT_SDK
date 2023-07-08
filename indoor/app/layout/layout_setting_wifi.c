#include "layout_define.h"
#include "layout_wifi_info.h"
#include "layout_wifi_input.h"
#include "layout_setting_time.h"
// 临时用默认代替

static int wifi_scanf_cont = 20;
static wifi_info wifi_scanf_temp[20] = {

    {
        .name = "SAT_RD_11_1",
        .db = 10,
        .psk_flags = "FREE",
        .free = false,
    },
    {
        .name = "SAT_RD_11_2",
        .db = 30,
        .psk_flags = "FREE",
        .free = false,
    },

    {
        .name = "SAT_RD_11_3",
        .db = 55,
        .psk_flags = "FREE",
        .free = false,
    },
    {
        .name = "SAT_RD_11_4",
        .db = 60,
        .psk_flags = "FREE",
        .free = false,
    },
    {
        .name = "SAT_RD_11_5",
        .db = 70,
        .psk_flags = "FREE",
        .free = false,
    },
    {
        .name = "SAT_RD_11_6",
        .db = 66,
        .psk_flags = "FREE",
        .free = false,
    },
    {
        .name = "SAT_RD_11_7",
        .db = 88,
        .psk_flags = "FREE",
        .free = true,
    },
    {
        .name = "SAT_RD_11_8",
        .db = 90,
        .psk_flags = "FREE",
        .free = false,
    },
    {
        .name = "SAT_RD_11_9",
        .db = 100,
        .psk_flags = "FREE",
        .free = false,
    },
    {
        .name = "SAT_RD_11_10",
        .db = true,
        .psk_flags = "FREE",
        .free = false,
    },
    {
        .name = "SAT_RD_11_11",
        .db = 120,
        .psk_flags = "FREE",
        .free = false,
    },
    {
        .name = "SAT_RD_11_12",
        .db = 128,
        .psk_flags = "FREE",
        .free = false,
    },
    {
        .name = "SAT_RD_11_13",
        .db = 130,
        .psk_flags = "FREE",
        .free = false,
    },
    {
        .name = "SAT_RD_11_14",
        .db = 14,
        .psk_flags = "FREE",
        .free = true,
    },
    {
        .name = "SAT_RD_11_15",
        .db = 45,
        .psk_flags = "FREE",
        .free = false,
    },
    {
        .name = "SAT_RD_11_16",
        .db = 65,
        .psk_flags = "FREE",
        .free = false,
    },
    {
        .name = "SAT_RD_11_17",
        .db = 87,
        .psk_flags = "FREE",
        .free = true,
    },
    {
        .name = "SAT_RD_11_18",
        .db = 60,
        .psk_flags = "FREE",
        .free = false,
    },
    {
        .name = "SAT_RD_11_19",
        .db = 40,
        .psk_flags = "FREE",
        .free = false,
    },
    {
        .name = "SAT_RD_11_20",
        .db = 30,
        .psk_flags = "FREE",
        .free = true,
    },

};
static wifi_info *p_wifi_connected = &wifi_scanf_temp[5];
enum
{
        setting_wifi_obj_id_wifi_wireless_title,
        setting_wifi_obj_id_cancel,
        setting_wifi_obj_id_next,
        setting_wifi_obj_id_wifi_cont,
        setting_wifi_obj_id_wifi_title,
        setting_wifi_obj_id_wifi_sub,
        setting_wifi_obj_id_wifi_img,

        setting_wifi_obj_id_wifi_add_cont,
        setting_wifi_obj_id_wifi_add_title,
        setting_wifi_obj_id_wifi_add_img,

        setting_wifi_obj_id_wifi_connected_user_cont,
        setting_wifi_obj_id_wifi_connected_user_title,
        setting_wifi_obj_id_wifi_connected_user_img,

        setting_wifi_obj_id_wifi_discovered_user_cont,
        setting_wifi_obj_id_wifi_discovered_user_title,
        setting_wifi_obj_id_wifi_discovered_user_img,

        setting_wifi_obj_id_list,

        setting_wifi_obj_id_wifi_discovered_1_cont,
        setting_wifi_obj_id_wifi_discovered_1_title,
        setting_wifi_obj_id_wifi_discovered_1_img,

        setting_wifi_obj_id_wifi_discovered_2_cont,
        setting_wifi_obj_id_wifi_discovered_2_title,
        setting_wifi_obj_id_wifi_discovered_2_img,

        setting_wifi_obj_id_wifi_discovered_3_cont,
        setting_wifi_obj_id_wifi_discovered_3_title,
        setting_wifi_obj_id_wifi_discovered_3_img,

        setting_wifi_obj_id_wifi_discovered_4_cont,
        setting_wifi_obj_id_wifi_discovered_4_title,
        setting_wifi_obj_id_wifi_discovered_4_img,

        setting_wifi_obj_id_wifi_discovered_5_cont,
        setting_wifi_obj_id_wifi_discovered_5_title,
        setting_wifi_obj_id_wifi_discovered_5_img,

        setting_wifi_obj_id_wifi_discovered_6_cont,
        setting_wifi_obj_id_wifi_discovered_6_title,
        setting_wifi_obj_id_wifi_discovered_6_img,

        setting_wifi_obj_id_wifi_discovered_7_cont,
        setting_wifi_obj_id_wifi_discovered_7_title,
        setting_wifi_obj_id_wifi_discovered_7_img,

        setting_wifi_obj_id_wifi_discovered_8_cont,
        setting_wifi_obj_id_wifi_discovered_8_title,
        setting_wifi_obj_id_wifi_discovered_8_img,

        setting_wifi_obj_id_wifi_discovered_9_cont,
        setting_wifi_obj_id_wifi_discovered_9_title,
        setting_wifi_obj_id_wifi_discovered_9_img,

        setting_wifi_obj_id_wifi_discovered_10_cont,
        setting_wifi_obj_id_wifi_discovered_10_title,
        setting_wifi_obj_id_wifi_discovered_10_img,

        setting_wifi_obj_id_wifi_discovered_11_cont,
        setting_wifi_obj_id_wifi_discovered_11_title,
        setting_wifi_obj_id_wifi_discovered_11_img,

        setting_wifi_obj_id_wifi_discovered_12_cont,
        setting_wifi_obj_id_wifi_discovered_12_title,
        setting_wifi_obj_id_wifi_discovered_12_img,

        setting_wifi_obj_id_wifi_discovered_13_cont,
        setting_wifi_obj_id_wifi_discovered_13_title,
        setting_wifi_obj_id_wifi_discovered_13_img,

        setting_wifi_obj_id_wifi_discovered_14_cont,
        setting_wifi_obj_id_wifi_discovered_14_title,
        setting_wifi_obj_id_wifi_discovered_14_img,

        setting_wifi_obj_id_wifi_discovered_15_cont,
        setting_wifi_obj_id_wifi_discovered_15_title,
        setting_wifi_obj_id_wifi_discovered_15_img,

        setting_wifi_obj_id_wifi_discovered_16_cont,
        setting_wifi_obj_id_wifi_discovered_16_title,
        setting_wifi_obj_id_wifi_discovered_16_img,

        setting_wifi_obj_id_wifi_discovered_17_cont,
        setting_wifi_obj_id_wifi_discovered_17_title,
        setting_wifi_obj_id_wifi_discovered_17_img,

        setting_wifi_obj_id_wifi_discovered_18_cont,
        setting_wifi_obj_id_wifi_discovered_18_title,
        setting_wifi_obj_id_wifi_discovered_18_img,

        setting_wifi_obj_id_wifi_discovered_19_cont,
        setting_wifi_obj_id_wifi_discovered_19_title,
        setting_wifi_obj_id_wifi_discovered_19_img,

        setting_wifi_obj_id_wifi_discovered_20_cont,
        setting_wifi_obj_id_wifi_discovered_20_title,
        setting_wifi_obj_id_wifi_discovered_20_img,
};

static void setting_wifi_cancel_click(lv_event_t *e)
{
        if (user_data_get()->system_mode == 0)
        {
                sat_layout_goto(single_operation_network, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
        }
        else
        {
                sat_layout_goto(server_operation_network, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
        }
}
static void setting_wifi_next_click(lv_event_t *e)
{
        setting_time_first_enter_set_flag(0x00);
          sat_layout_goto(setting_time, LV_SCR_LOAD_ANIM_MOVE_LEFT, SAT_VOID);
}

static void wifi_setting_wifi_enable_display(lv_obj_t *obj)
{
        if (user_data_get()->wifi_enable == true)
        {
                lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_switch_on.png"), LV_PART_MAIN);
        }
        else
        {
                lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_switch_off.png"), LV_PART_MAIN);
        }
}
static void setting_wifi_disable_obj_hidden(void)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_wifi_obj_id_wifi_add_cont);
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_wifi_obj_id_wifi_connected_user_cont);
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_wifi_obj_id_wifi_discovered_user_cont);
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_wifi_obj_id_list);
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
}
static void setting_wifi_setting_click(lv_event_t *e)
{
        lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_wifi_obj_id_wifi_cont);
        lv_obj_t *img = lv_obj_get_child_form_id(parent, setting_wifi_obj_id_wifi_img);

        user_data_get()->wifi_enable = user_data_get()->wifi_enable ? false : true;
        user_data_save();
        wifi_setting_wifi_enable_display(img);

        if (user_data_get()->wifi_enable == false)
        {
                setting_wifi_disable_obj_hidden();
        }
        else
        {
                sat_layout_goto(setting_wifi, LV_SCR_LOAD_ANIM_NONE, SAT_VOID);
        }
}
static int setting_wifi_discover_obj_id_get(int i, int j)
{
        int obj_id[20][3] = {
            {setting_wifi_obj_id_wifi_discovered_1_cont, setting_wifi_obj_id_wifi_discovered_1_title, setting_wifi_obj_id_wifi_discovered_1_img},

            {setting_wifi_obj_id_wifi_discovered_2_cont, setting_wifi_obj_id_wifi_discovered_2_title, setting_wifi_obj_id_wifi_discovered_2_img},

            {setting_wifi_obj_id_wifi_discovered_3_cont, setting_wifi_obj_id_wifi_discovered_3_title, setting_wifi_obj_id_wifi_discovered_3_img},

            {setting_wifi_obj_id_wifi_discovered_4_cont, setting_wifi_obj_id_wifi_discovered_4_title, setting_wifi_obj_id_wifi_discovered_4_img},

            {setting_wifi_obj_id_wifi_discovered_5_cont, setting_wifi_obj_id_wifi_discovered_5_title, setting_wifi_obj_id_wifi_discovered_5_img},

            {setting_wifi_obj_id_wifi_discovered_6_cont, setting_wifi_obj_id_wifi_discovered_6_title, setting_wifi_obj_id_wifi_discovered_6_img},

            {setting_wifi_obj_id_wifi_discovered_7_cont, setting_wifi_obj_id_wifi_discovered_7_title, setting_wifi_obj_id_wifi_discovered_7_img},

            {setting_wifi_obj_id_wifi_discovered_8_cont, setting_wifi_obj_id_wifi_discovered_8_title, setting_wifi_obj_id_wifi_discovered_8_img},

            {setting_wifi_obj_id_wifi_discovered_9_cont, setting_wifi_obj_id_wifi_discovered_9_title, setting_wifi_obj_id_wifi_discovered_9_img},

            {setting_wifi_obj_id_wifi_discovered_10_cont, setting_wifi_obj_id_wifi_discovered_10_title, setting_wifi_obj_id_wifi_discovered_10_img},

            {setting_wifi_obj_id_wifi_discovered_11_cont, setting_wifi_obj_id_wifi_discovered_11_title, setting_wifi_obj_id_wifi_discovered_11_img},

            {setting_wifi_obj_id_wifi_discovered_12_cont, setting_wifi_obj_id_wifi_discovered_12_title, setting_wifi_obj_id_wifi_discovered_12_img},

            {setting_wifi_obj_id_wifi_discovered_13_cont, setting_wifi_obj_id_wifi_discovered_13_title, setting_wifi_obj_id_wifi_discovered_13_img},

            {setting_wifi_obj_id_wifi_discovered_14_cont, setting_wifi_obj_id_wifi_discovered_14_title, setting_wifi_obj_id_wifi_discovered_14_img},

            {setting_wifi_obj_id_wifi_discovered_15_cont, setting_wifi_obj_id_wifi_discovered_15_title, setting_wifi_obj_id_wifi_discovered_15_img},

            {setting_wifi_obj_id_wifi_discovered_16_cont, setting_wifi_obj_id_wifi_discovered_16_title, setting_wifi_obj_id_wifi_discovered_16_img},

            {setting_wifi_obj_id_wifi_discovered_17_cont, setting_wifi_obj_id_wifi_discovered_17_title, setting_wifi_obj_id_wifi_discovered_17_img},

            {setting_wifi_obj_id_wifi_discovered_18_cont, setting_wifi_obj_id_wifi_discovered_18_title, setting_wifi_obj_id_wifi_discovered_18_img},

            {setting_wifi_obj_id_wifi_discovered_19_cont, setting_wifi_obj_id_wifi_discovered_19_title, setting_wifi_obj_id_wifi_discovered_19_img},

            {setting_wifi_obj_id_wifi_discovered_20_cont, setting_wifi_obj_id_wifi_discovered_20_title, setting_wifi_obj_id_wifi_discovered_20_img},
        };
        return obj_id[i][j];
}
static void setting_wifi_discover_click(lv_event_t *e)
{
        lv_obj_t *obj = lv_event_get_current_target(e);
        for (int i = 0; i < wifi_scanf_cont; i++)
        {
                if (obj->id == setting_wifi_discover_obj_id_get(i, 0))
                {
                        lv_obj_t *label = lv_obj_get_child_form_id(obj, setting_wifi_discover_obj_id_get(i, 1));
                        wifi_input_user_setting(lv_label_get_text(label));
                        sat_layout_goto(wifi_input, LV_SCR_LOAD_ANIM_MOVE_TOP, SAT_VOID);
                }
        }
}
static const char *wifi_setting_wifi_free_icon_get(const wifi_info *info)
{
        if (info->db < 55)
        {
                return resource_ui_src_get("15_list_wifi_05.png");
        }
        else if (info->db < 66)
        {
                return resource_ui_src_get("14_list_wifi_04.png");
        }
        else if (info->db < 88)
        {
                return resource_ui_src_get("13_list_wifi_03.png");
        }
        else if (info->db < 100)
        {
                return resource_ui_src_get("12_list_wifi_02.png");
        }
        return resource_ui_src_get("11_list_wifi_01.png");
}
static const char *wifi_setting_wifi_psk_icon_get(const wifi_info *info)
{
        if (info->db < 55)
        {
                return resource_ui_src_get("25_list_wifi_s_05.png");
        }
        else if (info->db < 66)
        {
                return resource_ui_src_get("24_list_wifi_s_04.png");
        }
        else if (info->db < 88)
        {
                return resource_ui_src_get("23_list_wifi_s_03.png");
        }
        else if (info->db < 100)
        {
                return resource_ui_src_get("22_list_wifi_s_02.png");
        }
        return resource_ui_src_get("21_list_wifi_s_01.png");
}
static const char *wifi_setting_wifi_icon_get(const wifi_info *info)
{
        if (info->free == true)
        {
                return wifi_setting_wifi_free_icon_get(info);
        }

        return wifi_setting_wifi_psk_icon_get(info);
}
static void settign_wifi_connected_click(lv_event_t *e)
{
        connected_wifi_info_setting((void *)p_wifi_connected);
        sat_layout_goto(wifi_info, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
}
static lv_obj_t *setting_wifi_discovered_network_list_create(void)
{
        lv_obj_t *list = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_wifi_obj_id_list);
        if (list != NULL)
        {
                return list;
        }
        list = lv_list_create(sat_cur_layout_screen_get());
        return list;
}
static void setting_wifi_discovered_network_display(void)
{
        int list_item_y = 216;
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明: 加载连接的设备
        ***********************************************/
        if (p_wifi_connected != NULL)
        {
                lv_common_img_text_btn_create(sat_cur_layout_screen_get(), setting_wifi_obj_id_wifi_connected_user_cont, 48, 216, 928, 64,
                                              settign_wifi_connected_click, LV_OPA_TRANSP, 0x00, LV_OPA_TRANSP, 0x101010,
                                              0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                              0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                              58, 20, 838, 64, setting_wifi_obj_id_wifi_connected_user_title,
                                              p_wifi_connected->name, 0xffffff, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                              0, 8, 48, 48, setting_wifi_obj_id_wifi_connected_user_img,
                                              wifi_setting_wifi_icon_get(p_wifi_connected), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);

                list_item_y += 64;
        }

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明:显示搜索的文本
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_wifi_obj_id_wifi_discovered_user_cont, 16, list_item_y + 10, 928, 38,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(WIFI_SETTING_XLS_LANG_ID_DISCOVERED_NETWORKS), 0x00a8ff, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_small);
                list_item_y += 48;
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明:显示搜索的wifi
         ***********************************************/
        {
                lv_obj_t *list = setting_wifi_discovered_network_list_create();
                lv_common_style_set_common(list, setting_wifi_obj_id_list, 48, list_item_y, 928, (600 - list_item_y), LV_ALIGN_TOP_LEFT, LV_PART_MAIN);
                for (int i = 0; i < wifi_scanf_cont; i++)
                {
                        lv_common_img_text_btn_create(list, setting_wifi_discover_obj_id_get(i, 0), 0, list_item_y, 928, 64,
                                                      setting_wifi_discover_click, LV_OPA_TRANSP, 0x00, LV_OPA_TRANSP, 0x101010,
                                                      0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                      0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                      58, 20, 838, 64, setting_wifi_discover_obj_id_get(i, 1),
                                                      wifi_scanf_temp[i].name, 0xffffff, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                      0, 8, 48, 48, setting_wifi_discover_obj_id_get(i, 2),
                                                      (const char *)wifi_setting_wifi_icon_get(&wifi_scanf_temp[i]), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);

                        list_item_y += 64;
                }
        }
}
static void settign_wifi_add_click(lv_event_t *ev)
{
        wifi_input_user_setting(NULL);
        sat_layout_goto(wifi_input, LV_SCR_LOAD_ANIM_MOVE_TOP, SAT_VOID);
}
static void sat_layout_enter(setting_wifi)
{
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明: 标题显示
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_wifi_obj_id_wifi_wireless_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(WIFI_SETTING_XLS_LANG_ID_WIFI_WIRELESS_NETWORK), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:25
        ** 说明: 上一步下一步
        ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_wifi_obj_id_cancel, 35, 15, 48, 48,
                                         setting_wifi_cancel_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);

                lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_wifi_obj_id_next, 952, 15, 48, 48,
                                         setting_wifi_next_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_next.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:50
        ** 说明: 设置按钮创建
        ***********************************************/
        {
                lv_obj_t *parent = lv_common_setting_btn_title_sub_info_img_create(sat_cur_layout_screen_get(), setting_wifi_obj_id_wifi_cont, 48, 80, 928, 88,
                                                                                   setting_wifi_setting_click, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                                                   0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                                                   0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                                                   0, 8, 838, 50, setting_wifi_obj_id_wifi_title,
                                                                                   lang_str_get(WIFI_SETTING_XLS_LANG_ID_WIFI), 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                                   0, 45, 838, 50, setting_wifi_obj_id_wifi_sub,
                                                                                   "Wi-FI MAC: AA:00:00:BB:FF:88", 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                                   0, 0, 0, 0, -1,
                                                                                   NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                                   840, 20, 80, 48, setting_wifi_obj_id_wifi_img,
                                                                                   resource_ui_src_get("btn_switch_on.png"), LV_OPA_50, 0x00a8ff, LV_ALIGN_CENTER);

                lv_obj_t *obj = lv_obj_get_child_form_id(parent, setting_wifi_obj_id_wifi_img);
                wifi_setting_wifi_enable_display(obj);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:50
         ** 说明: 添加wifi
         ***********************************************/
        {
                lv_common_img_text_btn_create(sat_cur_layout_screen_get(), setting_wifi_obj_id_wifi_add_cont, 0, 168, 1024, 48,
                                              settign_wifi_add_click, LV_OPA_TRANSP, 0x00, LV_OPA_TRANSP, 0x101010,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              16, 13, 300, 27, setting_wifi_obj_id_wifi_add_title,
                                              lang_str_get(WIFI_SETTING_XLS_LANG_ID_ADD_NETWORKS), 0x00a8ff, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                              896, 16, 80, 32, setting_wifi_obj_id_wifi_add_img,
                                              (const char *)resource_ui_src_get("wifi_add.png"), LV_OPA_50, 0x00a8ff, LV_ALIGN_CENTER);
        }
        setting_wifi_discovered_network_display();

        if (user_data_get()->wifi_enable == false)
        {
                setting_wifi_disable_obj_hidden();
        }
}
static void sat_layout_quit(setting_wifi)
{
}

sat_layout_create(setting_wifi);