#include "layout_define.h"
#include "layout_setting_screen.h"
#include "layout_setting_general.h"
enum
{
        setting_screen_obj_id_title,
        setting_screen_obj_id_cancel,
        setting_screen_obj_id_mian_list,

        setting_screen_obj_id_sub_list,

        setting_screen_obj_id_lcd_screen_cont,
        setting_screen_obj_id_lcd_screen_title,

        setting_screen_obj_id_lcd_screen_slider_cont,
        setting_screen_obj_id_lcd_screen_slider_text,
        setting_screen_obj_id_lcd_screen_slider_left_btn,
        setting_screen_obj_id_lcd_screen_slider_right_btn,
        setting_screen_obj_id_lcd_screen_slider,

        setting_screen_obj_id_standby_screen_cont,
        setting_screen_obj_id_standby_screen_title,
        setting_screen_obj_id_standby_screen_sub,

        setting_screen_obj_id_screen_clean_cont,
        setting_screen_obj_id_screen_clean_title,
};
static void setting_screen_slider_obj_change_cb(lv_event_t *ev)
{
        // SAT_DEBUG("=========\n");
        lv_obj_t *parent = lv_event_get_current_target(ev);
        // lv_obj_t *obj = lv_obj_get_child_form_id(parent, setting_screen_obj_id_lcd_screen_title);
        int value = lv_slider_get_value(parent);

        user_data_get()->display.lcd_brigtness = value;
        user_data_save();
        backlight_brightness_set(value == 0 ? 1 : value);
        	
}
static void setting_screen_standby_screen_obj_click(lv_event_t *ev)
{
        sat_layout_goto(setting_standby_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT,SAT_VOID);
}
static void setting_screen_screen_clean_obj_click(lv_event_t *ev)
{
     sat_layout_goto(setting_screen_clean, LV_SCR_LOAD_ANIM_MOVE_LEFT,SAT_VOID);   
}
static lv_obj_t *setting_screen_sub_list_create(void)
{
        setting_list_info_t main_list_group[] = {

            {0, 0, 622, 72, setting_screen_obj_id_lcd_screen_cont, setting_screen_obj_id_lcd_screen_title, -1, SCREEN_LANG_ID_LCD_SCREEN_BRIGHNESS, layout_setting_screen_language_get, -1, NULL, NULL},
            {0, 72, 622, 72, setting_screen_obj_id_standby_screen_cont, setting_screen_obj_id_standby_screen_title, setting_screen_obj_id_standby_screen_sub, SCREEN_LANG_ID_LCD_STANDBY_SCREEN, layout_setting_screen_language_get, SCREEN_LANG_ID_LCD_SCREEN_AFTER_15SEC, layout_setting_screen_language_get, setting_screen_standby_screen_obj_click},
            {0, 72 * 2, 622, 72, setting_screen_obj_id_screen_clean_cont, setting_screen_obj_id_screen_clean_title, -1, SCREEN_LANG_ID_LCD_SCREEN_CLEANING_MODE, layout_setting_screen_language_get, -1, NULL, setting_screen_screen_clean_obj_click},
        };

        lv_obj_t *list = setting_list_create(sat_cur_layout_screen_get(), setting_screen_obj_id_sub_list);
        lv_common_style_set_common(list, setting_screen_obj_id_sub_list, 354, 88, 622, 512, LV_ALIGN_TOP_LEFT, LV_PART_MAIN);

        for (int i = 0; i < sizeof(main_list_group) / sizeof(setting_list_info_t); i++)
        {
                lv_obj_t *item = lv_common_setting_btn_title_sub_info_img_create(list, main_list_group[i].cont_id, main_list_group[i].x, main_list_group[i].y, main_list_group[i].w, main_list_group[i].h,
                                                                                 main_list_group[i].click_cb, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                                                 0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                                                 0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x00a8ff,
                                                                                 0, 17, 576, 43, main_list_group[i].title_id,
                                                                                 main_list_group[i].title_language_id == -1 ? NULL : main_list_group[i].title_language_cb(main_list_group[i].title_language_id), 0xFFFFFF, 0x00a8ff, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                                 0, 42, 576, 29, main_list_group[i].sub_id,
                                                                                 main_list_group[i].sub_language_id == -1 ? NULL : main_list_group[i].sub_language_cb(main_list_group[i].sub_language_id), 0x6d6d79, 0x00484f, LV_TEXT_ALIGN_LEFT, lv_font_small,
                                                                                 0, 0, 0, 0, -1,
                                                                                 NULL, 0xFFFFFF, 0x0078Cf, LV_TEXT_ALIGN_LEFT, lv_font_normal,
                                                                                 0, 0, 0, 0, -1,
                                                                                 NULL, LV_OPA_COVER, 0x00a8ff, LV_ALIGN_CENTER);

                if (main_list_group[i].cont_id == setting_screen_obj_id_lcd_screen_cont)
                {
                        void *left_src = resource_ui_src_alloc("btn_control_minus.png", 42, 42);
                        void *right_src = resource_ui_src_alloc("btn_control_plus.png", 42, 42);
                        char light[32] =  {0};
                        sprintf(light,"%02d",user_data_get()->display.lcd_brigtness);
                        
                        lv_common_slider_create(item, setting_screen_obj_id_lcd_screen_slider_cont, 173, 11, 449, 48,
                                                setting_screen_slider_obj_change_cb, LV_OPA_TRANSP, 0X00,
                                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                6, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                38, 8, 35, 23, setting_screen_obj_id_lcd_screen_slider_text,
                                                light, 0Xffffff, LV_TEXT_ALIGN_RIGHT, lv_font_normal,
                                                127, 18, 272, 12, setting_screen_obj_id_lcd_screen_slider, LV_OPA_COVER, 0x666666, LV_OPA_COVER, 0x00a8ff,
                                                74, 3, 42, 42, setting_screen_obj_id_lcd_screen_slider_left_btn,
                                                left_src, LV_OPA_TRANSP, 0X00, LV_ALIGN_CENTER,
                                                404, 3, 42, 42, setting_screen_obj_id_lcd_screen_slider_right_btn,
                                                right_src, LV_OPA_TRANSP, 0x00, LV_ALIGN_CENTER,
                                                360, 9, 0Xffffff, LV_OPA_COVER, NULL,
                                                0, 100, user_data_get()->display.lcd_brigtness);

                        resouce_file_src_free(left_src);
                        resouce_file_src_free(right_src);
                }
        }
        return list;
}
static void sat_layout_enter(setting_screen)
{
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:25
        ** 说明: 左边主列表
        ***********************************************/
        setting_main_list_create(3);
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:25
        ** 说明: 右边副列表
        ***********************************************/
        setting_screen_sub_list_create();
}
static void sat_layout_quit(setting_screen)
{
}

sat_layout_create(setting_screen);