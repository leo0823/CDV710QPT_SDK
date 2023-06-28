#include "layout_define.h"
#include "layout_setting_frame_display_time.h"
#include "layout_setting_standby_screen.h"
#include "layout_setting_general.h"
#include "layout_setting_screen.h"
enum
{
        setting_frame_item_obj_id_title,
        setting_frame_item_obj_id_cancel,
        setting_frame_item_obj_id_list,
        setting_frame_item_obj_id_hour_cont,
        setting_frame_item_obj_id_calendar_cont,
        setting_frame_item_obj_id_recently_save_video_cont,
        setting_frame_item_obj_id_front_door_video_cont,
        setting_frame_item_obj_id_cctv_fontage_cont,
};

static void setting_frame_item_cancel_click(lv_event_t *e)
{
        sat_layout_goto(setting_standby_screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, SAT_VOID);
}

static void setting_frame_item_checkbox_click(lv_event_t *e)
{
        lv_obj_t *obj = lv_event_get_current_target(e);
        if (obj == NULL)
        {
                return;
        }
        lv_obj_t *checkbox = lv_obj_get_child_form_id(obj, 1);
        if (checkbox == NULL)
        {
                return;
        }
        if (strncmp(checkbox->bg_img_src, resource_ui_src_get("btn_checkbox_s.png"), strlen(resource_ui_src_get("btn_checkbox_s.png"))))
        {
                lv_obj_set_style_bg_img_src(checkbox, resource_ui_src_get("btn_checkbox_s.png"), LV_PART_MAIN);
        }
        else
        {
                unsigned int selected = 0x00;
                for(int i = 0; i<5; i++)
                {
                        lv_obj_t* parent_cont =  lv_obj_get_child_form_id(lv_obj_get_parent(obj),setting_frame_item_obj_id_hour_cont + i);
                        if(parent_cont == NULL)
                        {
                                continue;
                        }
                        lv_obj_t * checkbox =  lv_obj_get_child_form_id(parent_cont,1);
                        if (strncmp(checkbox->bg_img_src, resource_ui_src_get("btn_checkbox_n.png"), strlen(resource_ui_src_get("btn_checkbox_n.png"))) != 0)
                        {
                                
                                selected ++;
                        }
                }
                if( selected != 1)
                {
                        lv_obj_set_style_bg_img_src(checkbox, resource_ui_src_get("btn_checkbox_n.png"), LV_PART_MAIN);
                }
        }
}

static void setting_frame_item_checkbox_display(void)
{
        lv_obj_t * list = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_frame_item_obj_id_list);
        lv_obj_t * obj = lv_obj_get_child_form_id(lv_obj_get_child_form_id(list,setting_frame_item_obj_id_hour_cont),1);
        int data = user_data_get()->display.frame_list;
        printf("frame_list is 0x%x\n",user_data_get()->display.frame_list);
        if(data & 0x01)
        {
                lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_checkbox_s.png"), LV_PART_MAIN);
        }

        obj = lv_obj_get_child_form_id(lv_obj_get_child_form_id(list,setting_frame_item_obj_id_calendar_cont),1);
        if(data & 0x02)
        {
               lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_checkbox_s.png"), LV_PART_MAIN);
        }
         obj = lv_obj_get_child_form_id(lv_obj_get_child_form_id(list,setting_frame_item_obj_id_recently_save_video_cont),1);
        if (data & 0x04)
        {
               lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_checkbox_s.png"), LV_PART_MAIN);
        }
        obj = lv_obj_get_child_form_id(lv_obj_get_child_form_id(list,setting_frame_item_obj_id_front_door_video_cont),1);
        if (data & 0x08)
        {
               lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_checkbox_s.png"), LV_PART_MAIN);
        }
        obj = lv_obj_get_child_form_id(lv_obj_get_child_form_id(list,setting_frame_item_obj_id_cctv_fontage_cont),1);
        if (data & 0x10)
        {
               lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_checkbox_s.png"), LV_PART_MAIN);
        }
}

static void sat_layout_enter(setting_frame_item)
{
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-3 14:13:25
        ** 说明: 标题创建
        ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), setting_frame_item_obj_id_title, 0, 20, 1024, 40,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      layout_setting_standby_screen_language_get(SETTING_STANDBY_SCREEN_LANG_ID_ITEM_DISPLAY), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-3 14:13:25
        ** 说明: 返回按钮
        ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), setting_frame_item_obj_id_cancel, 35, 15, 48, 48,
                                         setting_frame_item_cancel_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_title_back.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-3 14:13:25
        ** 说明: 列表创建
        ***********************************************/
        {
                setting_list_info_t main_list_group[] = {

                    {0, 0, 928, 88,
                     setting_frame_item_obj_id_hour_cont, 0, -1,
                     SETTING_STANDBY_SCREEN_LANG_ID_HOUR, layout_setting_standby_screen_language_get,
                     -1, NULL,
                     setting_frame_item_checkbox_click, 1},
                    {0, 88, 928, 88,
                     setting_frame_item_obj_id_calendar_cont, 0, -1,
                     SETTING_STANDBY_SCREEN_LANG_ID_CALENDAR, layout_setting_standby_screen_language_get,
                     -1, NULL,
                     setting_frame_item_checkbox_click, 1},
                    {0, 88 * 2, 928, 88,
                     setting_frame_item_obj_id_recently_save_video_cont, 0, -1,
                     SETTING_STANDBY_SCREEN_LANG_ID_RECENTLY_SAVED_VIDEO, layout_setting_standby_screen_language_get,
                     -1, NULL,
                     setting_frame_item_checkbox_click, 1},
                    {0, 88 * 3, 928, 88,
                     setting_frame_item_obj_id_front_door_video_cont, 0, -1,
                     SETTING_STANDBY_SCREEN_LANG_ID_FRONT_DOOR_VIDEO, layout_setting_standby_screen_language_get,
                     -1, NULL,
                     setting_frame_item_checkbox_click, 1},
                    {0, 88 * 2, 928, 88,
                     setting_frame_item_obj_id_cctv_fontage_cont, 0, -1,
                     SETTING_STANDBY_SCREEN_LANG_ID_CCTV_FOOTAGE, layout_setting_standby_screen_language_get,
                     -1, NULL,
                     setting_frame_item_checkbox_click, 1}};

                lv_obj_t *list = setting_list_create(sat_cur_layout_screen_get(), setting_frame_item_obj_id_list);
                lv_common_style_set_common(list, setting_frame_item_obj_id_list, 48, 88, 928, 512, LV_ALIGN_TOP_LEFT, LV_PART_MAIN);

                for (int i = 0; i < sizeof(main_list_group) / sizeof(setting_list_info_t); i++)
                {
                        lv_common_setting_btn_title_sub_info_img_create(list, main_list_group[i].cont_id, main_list_group[i].x, main_list_group[i].y, main_list_group[i].w, main_list_group[i].h,
                                                                        main_list_group[i].click_cb, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                                        0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                                        0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                                        42, 30, 576, 43, main_list_group[i].title_id,
                                                                        main_list_group[i].title_language_id == -1 ? NULL : main_list_group[i].title_language_cb(main_list_group[i].title_language_id), 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                        42, 52, 576, 29, main_list_group[i].sub_id,
                                                                        main_list_group[i].sub_language_id == -1 ? NULL : main_list_group[i].sub_language_cb(main_list_group[i].sub_language_id), 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                        0, 0, 0, 0, -1,
                                                                        NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                        0, 28, 32, 32, main_list_group[i].img_id,
                                                                        resource_ui_src_get((user_data_get()->display.frame_list & (0x01 >> i)) ? "btn_checkbox_s.png" : "btn_checkbox_n.png"), LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);
                }
                setting_frame_item_checkbox_display();
        }
}
static void sat_layout_quit(setting_frame_item)
{

        int data = 0;
        printf("frame_list is 0x%x\n",user_data_get()->display.frame_list);
        lv_obj_t * list = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), setting_frame_item_obj_id_list);
        lv_obj_t * obj = lv_obj_get_child_form_id(lv_obj_get_child_form_id(list,setting_frame_item_obj_id_hour_cont),1);
        if (strncmp(obj->bg_img_src, resource_ui_src_get("btn_checkbox_n.png"), strlen(resource_ui_src_get("btn_checkbox_n.png"))))
        {
               data |= 0x01;
        }

        obj = lv_obj_get_child_form_id(lv_obj_get_child_form_id(list,setting_frame_item_obj_id_calendar_cont),1);
        if (strncmp(obj->bg_img_src, resource_ui_src_get("btn_checkbox_n.png"), strlen(resource_ui_src_get("btn_checkbox_n.png"))))
        {
               data |= 0x02;
        }
        obj = lv_obj_get_child_form_id(lv_obj_get_child_form_id(list,setting_frame_item_obj_id_recently_save_video_cont),1);
        if (strncmp(obj->bg_img_src, resource_ui_src_get("btn_checkbox_n.png"), strlen(resource_ui_src_get("btn_checkbox_n.png"))))
        {
               data |= 0x04;
        }
        obj = lv_obj_get_child_form_id(lv_obj_get_child_form_id(list,setting_frame_item_obj_id_front_door_video_cont),1);
        if (strncmp(obj->bg_img_src, resource_ui_src_get("btn_checkbox_n.png"), strlen(resource_ui_src_get("btn_checkbox_n.png"))))
        {
               data |= 0x08;
        }
        obj = lv_obj_get_child_form_id(lv_obj_get_child_form_id(list,setting_frame_item_obj_id_cctv_fontage_cont),1);
        if (strncmp(obj->bg_img_src, resource_ui_src_get("btn_checkbox_n.png"), strlen(resource_ui_src_get("btn_checkbox_n.png"))))
        {
               data |= 0x10;
        }

        user_data_get()->display.frame_list = data;
        
        user_data_save();
        printf("frame_list is 0x%x\n",user_data_get()->display.frame_list);

}

sat_layout_create(setting_frame_item);