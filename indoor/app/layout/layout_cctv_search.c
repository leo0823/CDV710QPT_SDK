#include "layout_define.h"
#include "layout_home.h"
#include "layout_door_camera_registed.h"

extern void cctv_serch_input_index_setting(int index);
enum
{
        cctv_search_obj_id_title,
        cctv_search_obj_id_cancel,

        cctv_search_obj_id_door_camera_list,
        cctv_search_obj_id_searched_door_camera_title,

        cctv_search_obj_id_searched_door_camera_item1_cont,
        cctv_search_obj_id_searched_door_camera_item1_title,
        cctv_search_obj_id_searched_door_camera_item1_sub,
        cctv_search_obj_id_searched_door_camera_item1_img,

        cctv_search_obj_id_searched_door_camera_item2_cont,
        cctv_search_obj_id_searched_door_camera_item2_title,
        cctv_search_obj_id_searched_door_camera_item2_sub,
        cctv_search_obj_id_searched_door_camera_item2_img,

        cctv_search_obj_id_searched_door_camera_item3_cont,
        cctv_search_obj_id_searched_door_camera_item3_title,
        cctv_search_obj_id_searched_door_camera_item3_sub,
        cctv_search_obj_id_searched_door_camera_item3_img,

        cctv_search_obj_id_searched_door_camera_item4_cont,
        cctv_search_obj_id_searched_door_camera_item4_title,
        cctv_search_obj_id_searched_door_camera_item4_sub,
        cctv_search_obj_id_searched_door_camera_item4_img,

        cctv_search_obj_id_searched_door_camera_item5_cont,
        cctv_search_obj_id_searched_door_camera_item5_title,
        cctv_search_obj_id_searched_door_camera_item5_sub,
        cctv_search_obj_id_searched_door_camera_item5_img,

        cctv_search_obj_id_searched_door_camera_item6_cont,
        cctv_search_obj_id_searched_door_camera_item6_title,
        cctv_search_obj_id_searched_door_camera_item6_sub,
        cctv_search_obj_id_searched_door_camera_item6_img,

        cctv_search_obj_id_searched_door_camera_item7_cont,
        cctv_search_obj_id_searched_door_camera_item7_title,
        cctv_search_obj_id_searched_door_camera_item7_sub,
        cctv_search_obj_id_searched_door_camera_item7_img,

        cctv_search_obj_id_searched_door_camera_item8_cont,
        cctv_search_obj_id_searched_door_camera_item8_title,
        cctv_search_obj_id_searched_door_camera_item8_sub,
        cctv_search_obj_id_searched_door_camera_item8_img,
};

static int cctv_search_serched_item_obj_id_get(int item, int id)
{
        int obj_id[8][5] = {

            {cctv_search_obj_id_searched_door_camera_item1_cont,
             cctv_search_obj_id_searched_door_camera_item1_title,
             cctv_search_obj_id_searched_door_camera_item1_sub,
             cctv_search_obj_id_searched_door_camera_item1_img},

            {cctv_search_obj_id_searched_door_camera_item2_cont,
             cctv_search_obj_id_searched_door_camera_item2_title,
             cctv_search_obj_id_searched_door_camera_item2_sub,
             cctv_search_obj_id_searched_door_camera_item2_img},

            {cctv_search_obj_id_searched_door_camera_item3_cont,
             cctv_search_obj_id_searched_door_camera_item3_title,
             cctv_search_obj_id_searched_door_camera_item3_sub,
             cctv_search_obj_id_searched_door_camera_item3_img},

            {cctv_search_obj_id_searched_door_camera_item4_cont,
             cctv_search_obj_id_searched_door_camera_item4_title,
             cctv_search_obj_id_searched_door_camera_item4_sub,
             cctv_search_obj_id_searched_door_camera_item4_img},

            {cctv_search_obj_id_searched_door_camera_item5_cont,
             cctv_search_obj_id_searched_door_camera_item5_title,
             cctv_search_obj_id_searched_door_camera_item5_sub,
             cctv_search_obj_id_searched_door_camera_item5_img},

            {cctv_search_obj_id_searched_door_camera_item6_cont,
             cctv_search_obj_id_searched_door_camera_item6_title,
             cctv_search_obj_id_searched_door_camera_item6_sub,
             cctv_search_obj_id_searched_door_camera_item6_img},

            {cctv_search_obj_id_searched_door_camera_item7_cont,
             cctv_search_obj_id_searched_door_camera_item7_title,
             cctv_search_obj_id_searched_door_camera_item7_sub,
             cctv_search_obj_id_searched_door_camera_item7_img},

            {cctv_search_obj_id_searched_door_camera_item8_cont,
             cctv_search_obj_id_searched_door_camera_item8_title,
             cctv_search_obj_id_searched_door_camera_item8_sub,
             cctv_search_obj_id_searched_door_camera_item8_img}};

        return obj_id[item][id];
}
static void cctv_search_cancel_click(lv_event_t *ev)
{
        sat_layout_goto(cctv_registered, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
}
static void cctv_serarch_list_click(lv_event_t *ev)
{
        lv_obj_t *parent = lv_event_get_current_target(ev);
        if (parent == NULL)
        {
                return;
        }

        int parent_id = parent->id;
        for (int i = 0; i < 8; i++)
        {
                if (parent_id == cctv_search_serched_item_obj_id_get(i, 0))
                {
                        cctv_serch_input_index_setting(i);
                        sat_layout_goto(cctv_serch_input, LV_SCR_LOAD_ANIM_NONE, SAT_VOID);
                }
        }
}
static lv_obj_t *setting_cctv_search_list_create(void)
{
        lv_obj_t *list = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), cctv_search_obj_id_door_camera_list);
        if (list != NULL)
        {
                return list;
        }
        list = lv_list_create(sat_cur_layout_screen_get());
        lv_common_style_set_common(list, cctv_search_obj_id_door_camera_list, 48, 136, 928, (600 - 200), LV_ALIGN_TOP_LEFT, LV_PART_MAIN);
        return list;
}

static void cctv_search_list_display(void)
{
        lv_obj_t *list = setting_cctv_search_list_create();
        lv_obj_clean(list);

        int item_y = 0;

        int user_count = sat_ipcamera_online_num_get();

        char user_name[128] = {0};
        char user_ip[128] = {0};
        for (int i = 0; (i < user_count); i++)
        {
                memset(user_name, 0, sizeof(user_name));
                memset(user_ip, 0, sizeof(user_ip));

                sprintf(user_name, "CCTV%d", i + 1);
                strcpy(user_ip, sat_ipcamera_ipaddr_get(i));

                printf("user name:%s \n", user_name);
                printf("user ip:%s\n", user_ip);
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

                lv_common_setting_btn_title_sub_info_img_create(list, cctv_search_serched_item_obj_id_get(i, 0), 48, item_y, 928, 88,
                                                                cctv_serarch_list_click, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                                0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                                58, 8, 618, 43, cctv_search_serched_item_obj_id_get(i, 1),
                                                                (char *)user_name, 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                58, 51, 618, 29, cctv_search_serched_item_obj_id_get(i, 2),
                                                                (char *)user_ip, 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                0, 0, 0, 0, -1,
                                                                NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                0, 20, 48, 48, cctv_search_serched_item_obj_id_get(i, 3),
                                                                resource_ui_src_get("ic_list_new.png"), LV_OPA_TRANSP, 0, LV_ALIGN_CENTER);
                item_y += 88;
        }
}

static lv_timer_t *p_cctv_search_timer = NULL;
static void cctv_search_emty_timer(lv_timer_t *ptimer)
{
        sat_ipcamera_device_online_search();
}
static void cctv_search_ipcamera_state_func(unsigned int type, unsigned int num)
{
        if (type == 1)
        {
                cctv_search_list_display();
                if (p_cctv_search_timer != NULL)
                {
                        lv_timer_del(p_cctv_search_timer);
                        p_cctv_search_timer = NULL;
                }
        }
}
static void sat_layout_enter(cctv_search)
{
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明: 标题显示
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), cctv_search_obj_id_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      layout_home_language_get(HOME_LANG_ID_CCTV), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 上一步下一步
         ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), cctv_search_obj_id_cancel, 35, 15, 48, 48,
                                         cctv_search_cancel_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:50
         ** 说明: 显示搜索的设备
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), cctv_search_obj_id_searched_door_camera_title, 16, 88, 584, 48,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      layout_door_camera_search_language_get(DOOR_CAMERA_SEARCH_ID_SEARCHED_DOOR_CAMERA), 0X00A8ff, 0X00A8ff, LV_TEXT_ALIGN_LEFT, lv_font_small);
        }
        p_cctv_search_timer = lv_sat_timer_create(cctv_search_emty_timer, 3000, NULL);
        lv_timer_ready(p_cctv_search_timer);

        ipcamera_state_callback_register(cctv_search_ipcamera_state_func);
}
static void sat_layout_quit(cctv_search)
{
        ipcamera_state_callback_register(NULL);
}
sat_layout_create(cctv_search);