#include "layout_define.h"
#include "layout_intercom_call.h"
enum
{
        buzzer_call_obj_top,
        buzzer_call_obj_status_label,
        buzzer_call_obj_status_icon,
        buzzer_call_obj_volume,
        buzzer_call_obj_handup,
        buzzer_call_obj_answer,
};

static int buzzer_call_timeout = 0;



static lv_obj_t *buzzer_call_top_obj_item_get(int id)
{
        lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), buzzer_call_obj_top);
        if (parent == NULL)
        {
                SAT_DEBUG("   lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), buzzer_call_obj_top);");
                return NULL;
        }
        lv_obj_t *obj = lv_obj_get_child_form_id(parent, id);
        if (obj == NULL)
        {
                SAT_DEBUG(" lv_obj_t* obj = lv_obj_get_child_form_id(parent,0);");
                return NULL;
        }
        return obj;
}
static void buzzer_call_info_display(void)
{
        lv_obj_t *obj = buzzer_call_top_obj_item_get(0);
        if (obj == NULL)
        {
                SAT_DEBUG("lv_obj_t* obj = buzzer_call_top_obj_item_get(0);");
                return;
        }
        struct tm tm;
        user_time_read(&tm);
        lv_label_set_text_fmt(obj, "Buzzer Call: %04d-%02d-%02d %02d:%02d", tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min);
}
static void buzzer_call_time_display(void)
{
        lv_obj_t *obj = buzzer_call_top_obj_item_get(1);
        if (obj == NULL)
        {
                SAT_DEBUG("lv_obj_t* obj = buzzer_call_top_obj_item_get(0);");
                return;
        }
        lv_label_set_text_fmt(obj, "%02d:%02d", buzzer_call_timeout / 60, buzzer_call_timeout % 60);
}
static void buzzer_call_time_timer(lv_timer_t *ptime)
{
        if (buzzer_call_timeout == 0)
        {
                sat_layout_goto(home, LV_SCR_LOAD_ANIM_NONE, SAT_VOID);
        }
        buzzer_call_info_display();
        buzzer_call_time_display();
        buzzer_call_timeout--;
}
static void buzzer_call_status_background_display(void)
{
   lv_disp_set_bg_image(lv_disp_get_default(), resource_wallpaper_src_get("img_calling_backgroud.jpg", 1024, 600));

}
static void buzzer_call_status_label_display(void)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), buzzer_call_obj_status_label);
        if (obj == NULL)
        {
                SAT_DEBUG("   lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), buzzer_call_obj_status_label);");
                return;
        }
        lv_label_set_text(obj,"buzzer call");
}
static void buzzer_call_status_icon_display(void)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), buzzer_call_obj_status_icon);
        if (obj == NULL)
        {
                SAT_DEBUG("   lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), buzzer_call_obj_status_icon);");
                return;
        }
        lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("img_calling_bell.png"), LV_PART_MAIN);
}

static void buzzer_call_handup_obj_click(lv_event_t *e)
{

   sat_layout_goto(home, LV_SCR_LOAD_ANIM_NONE, SAT_VOID);
        
}

static void buzzer_call_handup_obj_display(void)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), buzzer_call_obj_handup);
        if (obj == NULL)
        {
                SAT_DEBUG("   lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), buzzer_call_obj_handup);");
                return;
        }
        lv_obj_set_x(obj, 460);
}

static void buzzer_call_volume_obj_click(lv_event_t *e)
{
}
static void buzzer_call_volume_obj_display(void)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), buzzer_call_obj_volume);
        if (obj == NULL)
        {
                SAT_DEBUG("   lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), buzzer_call_obj_volume);");
                return;
        }
        lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_call_sound.png"), LV_PART_MAIN);
}
static bool layout_buzzer_call_ringplay_register_callback(int arg)
{
        SAT_DEBUG("arg is  %d\n",arg);
        if(arg == 1)
        {
                ring_buzzer_play();
        }
        return true;
}


static void sat_layout_enter(buzzer_call)
{
 
        standby_timer_close();
        buzzer_call_timeout = 30;
        buzzer_call_status_background_display();
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 顶部容器
         ***********************************************/
        {
                lv_obj_t *parent = lv_common_img_btn_create(sat_cur_layout_screen_get(), buzzer_call_obj_top, 0, 0, 1024, 80,
                                                            NULL, false, LV_OPA_COVER, 0, LV_OPA_TRANSP, 0x808080,
                                                            0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                            0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                            NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

                /***********************************************
                 ** 作者: leo.liu
                 ** 日期: 2023-2-2 13:46:56
                 ** 说明: 标题显示
                 ***********************************************/
                {
                        lv_common_text_create(parent, 0, 32, 25, 700, 42,
                                              NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              " ", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_LEFT, lv_font_normal);
                        buzzer_call_info_display();
                }
                /***********************************************
                 ** 作者: leo.liu
                 ** 日期: 2023-2-2 13:46:56
                 ** 说明: 时间显示
                 ***********************************************/
                {
                        lv_common_text_create(parent, 1, 927, 25, 73, 42,
                                              NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              " ", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_RIGHT, lv_font_normal);
                        buzzer_call_time_display();
                        lv_sat_timer_create(buzzer_call_time_timer, 1000, NULL);
                }
        }
        {
            if(user_data_get()->audio.ring_mute == false)
            {
                ring_buzzer_play();
            }

        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明:状态文本显示
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), buzzer_call_obj_status_label, 362, 90, 300, 42,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      " ", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
                buzzer_call_status_label_display();
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明:状态文本图标显示
         ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), buzzer_call_obj_status_icon, 303, 142, 418, 314,
                                         NULL, false, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                buzzer_call_status_icon_display();
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明:挂断按钮图标显示
        ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), buzzer_call_obj_handup, 460, 464, 104, 104,
                                         buzzer_call_handup_obj_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_call_buzzer.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                buzzer_call_handup_obj_display();
        }

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明:音量按钮图标显示
         ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), buzzer_call_obj_volume, 32, 488, 81, 81,
                                         buzzer_call_volume_obj_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_call_sound.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                buzzer_call_volume_obj_display();
        }

        ring_play_event_cmd_register(layout_buzzer_call_ringplay_register_callback);
}

static void sat_layout_quit(buzzer_call)
{
        standby_timer_restart(true);
        lv_disp_set_bg_image(lv_disp_get_default(), NULL);
        ring_play_event_cmd_register(NULL);


}

sat_layout_create(buzzer_call);