#include "layout_define.h"
#include "layout_door_camera_registed.h"
enum
{
        door_camera_search_1_obj_id_title,
        door_camera_search_1_obj_id_cancel,

        door_camera_search_1_obj_id_if_yout_press_cont,
        door_camera_search_obj_1_id_if_yout_press_text,
        door_camera_search_obj_1_id_if_yout_press_img,

        door_camera_search_1_obj_id_door_camera_list,
        door_camera_search_1_obj_id_searched_door_camera_title,

        door_camera_search_1_obj_id_searched_door_camera_item1_cont,
        door_camera_search_1_obj_id_searched_door_camera_item1_title,
        door_camera_search_1_obj_id_searched_door_camera_item1_sub,
        door_camera_search_1_obj_id_searched_door_camera_item1_img,

        door_camera_search_1_obj_id_searched_door_camera_item2_cont,
        door_camera_search_1_obj_id_searched_door_camera_item2_title,
        door_camera_search_1_obj_id_searched_door_camera_item2_sub,
        door_camera_search_1_obj_id_searched_door_camera_item2_img,

        door_camera_search_1_obj_id_searched_door_camera_item3_cont,
        door_camera_search_1_obj_id_searched_door_camera_item3_title,
        door_camera_search_1_obj_id_searched_door_camera_item3_sub,
        door_camera_search_1_obj_id_searched_door_camera_item3_img,

        door_camera_search_1_obj_id_searched_door_camera_item4_cont,
        door_camera_search_1_obj_id_searched_door_camera_item4_title,
        door_camera_search_1_obj_id_searched_door_camera_item4_sub,
        door_camera_search_1_obj_id_searched_door_camera_item4_img,

        door_camera_search_1_obj_id_searched_door_camera_item5_cont,
        door_camera_search_1_obj_id_searched_door_camera_item5_title,
        door_camera_search_1_obj_id_searched_door_camera_item5_sub,
        door_camera_search_1_obj_id_searched_door_camera_item5_img,

        door_camera_search_1_obj_id_searched_door_camera_item6_cont,
        door_camera_search_1_obj_id_searched_door_camera_item6_title,
        door_camera_search_1_obj_id_searched_door_camera_item6_sub,
        door_camera_search_1_obj_id_searched_door_camera_item6_img,

        door_camera_search_1_obj_id_searched_door_camera_item7_cont,
        door_camera_search_1_obj_id_searched_door_camera_item7_title,
        door_camera_search_1_obj_id_searched_door_camera_item7_sub,
        door_camera_search_1_obj_id_searched_door_camera_item7_img,

        door_camera_search_1_obj_id_searched_door_camera_item8_cont,
        door_camera_search_1_obj_id_searched_door_camera_item8_title,
        door_camera_search_1_obj_id_searched_door_camera_item8_sub,
        door_camera_search_1_obj_id_searched_door_camera_item8_img,
};

static int door_camera_search_1_serched_item_obj_id_get(int item, int id)
{
        int obj_id[8][5] = {

            {door_camera_search_1_obj_id_searched_door_camera_item1_cont,
             door_camera_search_1_obj_id_searched_door_camera_item1_title,
             door_camera_search_1_obj_id_searched_door_camera_item1_sub,
             door_camera_search_1_obj_id_searched_door_camera_item1_img},

            {door_camera_search_1_obj_id_searched_door_camera_item2_cont,
             door_camera_search_1_obj_id_searched_door_camera_item2_title,
             door_camera_search_1_obj_id_searched_door_camera_item2_sub,
             door_camera_search_1_obj_id_searched_door_camera_item2_img},

            {door_camera_search_1_obj_id_searched_door_camera_item3_cont,
             door_camera_search_1_obj_id_searched_door_camera_item3_title,
             door_camera_search_1_obj_id_searched_door_camera_item3_sub,
             door_camera_search_1_obj_id_searched_door_camera_item3_img},

            {door_camera_search_1_obj_id_searched_door_camera_item4_cont,
             door_camera_search_1_obj_id_searched_door_camera_item4_title,
             door_camera_search_1_obj_id_searched_door_camera_item4_sub,
             door_camera_search_1_obj_id_searched_door_camera_item4_img},

            {door_camera_search_1_obj_id_searched_door_camera_item5_cont,
             door_camera_search_1_obj_id_searched_door_camera_item5_title,
             door_camera_search_1_obj_id_searched_door_camera_item5_sub,
             door_camera_search_1_obj_id_searched_door_camera_item5_img},

            {door_camera_search_1_obj_id_searched_door_camera_item6_cont,
             door_camera_search_1_obj_id_searched_door_camera_item6_title,
             door_camera_search_1_obj_id_searched_door_camera_item6_sub,
             door_camera_search_1_obj_id_searched_door_camera_item6_img},

            {door_camera_search_1_obj_id_searched_door_camera_item7_cont,
             door_camera_search_1_obj_id_searched_door_camera_item7_title,
             door_camera_search_1_obj_id_searched_door_camera_item7_sub,
             door_camera_search_1_obj_id_searched_door_camera_item7_img},

            {door_camera_search_1_obj_id_searched_door_camera_item8_cont,
             door_camera_search_1_obj_id_searched_door_camera_item8_title,
             door_camera_search_1_obj_id_searched_door_camera_item8_sub,
             door_camera_search_1_obj_id_searched_door_camera_item8_img}};

        return obj_id[item][id];
}
static void door_camera_search_1_cancel_click(lv_event_t *ev)
{
        sat_layout_goto(door_camera_registed, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
}
static void setting_door_camera_searched_1_list_click(lv_event_t *ev)
{
        lv_obj_t *parent = lv_event_get_current_target(ev);
        if (parent == NULL)
        {
                return;
        }

        int parent_id = parent->id;
        for (int i = 0; i < 8; i++)
        {
                if (parent_id == door_camera_search_1_serched_item_obj_id_get(i, 0))
                {
                        lv_obj_t *title = lv_obj_get_child_form_id(parent, door_camera_search_1_serched_item_obj_id_get(i, 1));
                        lv_obj_t *sub = lv_obj_get_child_form_id(parent, door_camera_search_1_serched_item_obj_id_get(i, 2));
                        if ((title == NULL) || (sub == NULL))
                        {
                                return;
                        }
                        network_device_info device_info;
                        sprintf(device_info.user, "sip:%s", lv_label_get_text(sub));
                        strcpy(device_info.name, lv_label_get_text(title));
                        camera_search_display_pview_sip_user_setting(&device_info);
                        // 此处已经有return
                        device_password_input_enter_mode_setting(0x02);
                        
                        sat_layout_goto(door_camera_password_input, LV_SCR_LOAD_ANIM_NONE, SAT_VOID);
                }
        }
}
static lv_obj_t *setting_door_camera_search_1_list_create(void)
{
        lv_obj_t *list = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), door_camera_search_1_obj_id_door_camera_list);
        if (list != NULL)
        {
                return list;
        }
        list = lv_list_create(sat_cur_layout_screen_get());
        lv_common_style_set_common(list, door_camera_search_1_obj_id_door_camera_list, 48, 200, 928, (600 - 200), LV_ALIGN_TOP_LEFT, LV_PART_MAIN);
        return list;
}

static network_device_info *p_door_device_info[DEVICE_MAX] = {NULL};
static int door_device_total = 0;
static void door_camera_search_user_info_release(void)
{
        for (int i = 0; i < DEVICE_MAX; i++)
        {
                if (p_door_device_info[i] != NULL)
                {
                        lv_mem_free(p_door_device_info[i]);
                        p_door_device_info[i] = NULL;
                }
        }
        door_device_total = 0;
}

static void door_camera_search_1_list_display(void)
{
        lv_obj_t *list = setting_door_camera_search_1_list_create();
        lv_obj_clean(list);

        int item_y = 0;

        for (int i = 0; (i < door_device_total) && (p_door_device_info[i] != NULL); i++)
        {
#if 0
                char sip_info[256] = {0};
                sprintf(sip_info, "%s@%s", user_name, user_ip);
               	//此处已经有return
               //	usleep(5*1000*1000);
                camera_search_display_pview_sip_user_setting(sip_info);
				//extern unsigned long long mem_size;
				//printf("-------->>%llu \n",mem_size);
                sat_layout_goto(camera_search_display, LV_SCR_LOAD_ANIM_NONE, SAT_VOID);
#endif

                lv_common_setting_btn_title_sub_info_img_create(list, door_camera_search_1_serched_item_obj_id_get(i, 0), 48, item_y, 928, 88,
                                                                setting_door_camera_searched_1_list_click, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                                58, 8, 618, 43, door_camera_search_1_serched_item_obj_id_get(i, 1),
                                                                (char *)p_door_device_info[i]->name, 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                58, 51, 618, 29, door_camera_search_1_serched_item_obj_id_get(i, 2),
                                                                (char *)p_door_device_info[i]->user, 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                0, 0, 0, 0, -1,
                                                                NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                0, 20, 48, 48, door_camera_search_1_serched_item_obj_id_get(i, 3),
                                                                resource_ui_src_get("ic_list_new.png"), LV_OPA_TRANSP, 0, LV_ALIGN_CENTER);
                item_y += 88;
        }
}

static void door_camera_search_1_emty_timer(lv_timer_t *ptimer)
{
        network_device_info user_info_temp[DEVICE_MAX] = {0};
        int user_temp_count = 0;
        if ((user_network_device_query((unsigned char *)network_data_get()->sip_user, 2, user_info_temp, sizeof(user_info_temp[0]), &user_temp_count, true)) == true)
        {
                if ((user_temp_count > 0) && (user_temp_count != door_device_total))
                {
                        door_camera_search_user_info_release();
                        for (int i = 0; i < user_temp_count; i++)
                        {
                                p_door_device_info[i] = (network_device_info *)lv_mem_alloc(sizeof(network_device_info));
                                memset(p_door_device_info[i], 0, sizeof(network_device_info));
                                *(p_door_device_info[i]) = user_info_temp[i];
                        }
                        door_device_total = user_temp_count;
                        door_camera_search_1_list_display();
                }
        }
}
static void sat_layout_enter(door_camera_search)
{
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明: 标题显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), door_camera_search_1_obj_id_title, 0, 20, 1024, 40,
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
                lv_common_img_btn_create(sat_cur_layout_screen_get(), door_camera_search_1_obj_id_cancel, 35, 15, 48, 48,
                                         door_camera_search_1_cancel_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:50
        ** 说明: 搜索户外机
        ***********************************************/
        {
                lv_common_img_text_btn_create(sat_cur_layout_screen_get(), door_camera_search_1_obj_id_if_yout_press_cont, 0, 80, 1024, 72,
                                              NULL, LV_OPA_TRANSP, 0x00, LV_OPA_TRANSP, 0x101010,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              253, 6, 542, 60, door_camera_search_obj_1_id_if_yout_press_text,
                                              layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_IF_YOUT_PRESS), 0XB8B8B8, 0x00a8ff, LV_TEXT_ALIGN_CENTER, lv_font_small,
                                              235, 15, 48, 48, door_camera_search_obj_1_id_if_yout_press_img,
                                              (const char *)resource_ui_src_get("ic_camerabell.png"), LV_OPA_50, 0x00a8ff, LV_ALIGN_CENTER);
        }

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:50
         ** 说明: 显示搜索的设备
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), door_camera_search_1_obj_id_searched_door_camera_title, 16, 152, 584, 48,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_SEARCHED_DOOR_CAMERA), 0X00A8ff, 0X00A8ff, LV_TEXT_ALIGN_LEFT, lv_font_small);
        }
        door_camera_search_1_list_display();

        lv_sat_timer_create(door_camera_search_1_emty_timer, 3000, NULL);
}
static void sat_layout_quit(door_camera_search)
{
        door_camera_search_user_info_release();
}
sat_layout_create(door_camera_search);