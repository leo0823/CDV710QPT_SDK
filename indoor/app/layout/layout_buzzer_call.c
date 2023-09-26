#include "layout_define.h"
#include "layout_intercom_call.h"
enum
{
        buzzer_screen_obj_id,
        buzzer_call_obj_top,
        buzzer_call_obj_status_label,
        buzzer_call_obj_status_icon,
        buzzer_call_bottom_cont,
        buzzer_call_obj_volume,
        buzzer_call_obj_handup,
        buzzer_obj_id_vol_cont,
        buzzer_vol_obj_id_slider_cont,
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
                user_data_get()->alarm.buzzer_alarm = false;
                user_data_save();
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
        lv_label_set_text(obj, "buzzer call");
}

static void buzzer_call_handup_obj_click(lv_event_t *e)
{
        user_data_get()->alarm.buzzer_alarm = false;
        user_data_save();
        if (user_data_get()->system_mode && 0x0f != 0x01)
        {
                sat_ipcamera_data_sync(0x00, 0x04, (char *)user_data_get(), sizeof(user_data_info), 10, 100, NULL);
        }
        sat_layout_goto(home, LV_SCR_LOAD_ANIM_NONE, SAT_VOID);
}

static void buzzer_call_volume_obj_click(lv_event_t *e)
{
        lv_obj_t *bottom_cont = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), buzzer_call_bottom_cont);

        lv_obj_t *vol_cont = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), buzzer_obj_id_vol_cont);

        lv_obj_add_flag(bottom_cont, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(vol_cont, LV_OBJ_FLAG_HIDDEN);
}

static bool layout_buzzer_call_ringplay_register_callback(int arg)
{
        if (arg == 1)
        {
                ring_buzzer_play(user_data_get()->audio.buzzer_tone);
        }
        return true;
}

static void setting_buzzer_call_slider_obj_change_cb(lv_event_t *ev)
{

        lv_obj_t *parent = lv_event_get_current_target(ev);

        int value = lv_slider_get_value(parent);

        user_data_get()->audio.buzzer_volume = value;
        user_data_save();
        sat_linphone_audio_play_volume_set(value);
}

static void layout_buzzer_vol_bar_create(lv_obj_t *parent)
{

        void *left_src = resource_ui_src_alloc("btn_control_minus.png", 42, 42);
        void *right_src = resource_ui_src_alloc("btn_control_plus.png", 42, 42);
        lv_common_slider_create(parent, buzzer_vol_obj_id_slider_cont, 97, 23, 831, 48,
                                setting_buzzer_call_slider_obj_change_cb, LV_OPA_TRANSP, 0X00,
                                0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                6, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                38, 8, 35, 23, 0,
                                "30", 0Xffffff, LV_TEXT_ALIGN_RIGHT, lv_font_normal,
                                127, 18, 577, 12, 1, LV_OPA_COVER, 0x666666, LV_OPA_COVER, 0x00a8ff,
                                74, 3, 42, 42, 2,
                                left_src, LV_OPA_TRANSP, 0X00, LV_ALIGN_CENTER,
                                715, 3, 42, 42, 3,
                                right_src, LV_OPA_TRANSP, 0x00, LV_ALIGN_CENTER,
                                360, 9, 0Xffffff, LV_OPA_COVER, NULL,
                                0, 100, user_data_get()->display.lcd_brigtness);

        resouce_file_src_free(left_src);
        resouce_file_src_free(right_src);
}

static void layout_buzzer_call_screen_click(lv_event_t *e)
{
        lv_obj_t *bottom_cont = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), buzzer_call_bottom_cont);
        lv_obj_t *vol_cont = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), buzzer_obj_id_vol_cont);
        if (lv_obj_has_flag(bottom_cont, LV_OBJ_FLAG_HIDDEN) == true)
        {
                lv_obj_clear_flag(bottom_cont, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(vol_cont, LV_OBJ_FLAG_HIDDEN);
        }
}
static void sat_layout_enter(buzzer_call)
{
        lv_obj_pressed_func = NULL;
        sat_linphone_audio_play_stop();
        standby_timer_close();
        buzzer_call_timeout = 30;
        buzzer_call_status_background_display();

        // 满屏查看
        {

                lv_common_img_btn_create(sat_cur_layout_screen_get(), buzzer_screen_obj_id, 0, 0, 1024, 600,
                                         layout_buzzer_call_screen_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_TOP_MID);
        }
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
                if (user_data_get()->audio.ring_mute == false)
                {
                        ring_buzzer_play(user_data_get()->audio.buzzer_tone);
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
                                         resource_ui_src_get("img_calling_bell.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明:挂断按钮图标显示
        ***********************************************/
        {
                lv_obj_t *bottom_cont = lv_common_img_btn_create(sat_cur_layout_screen_get(), buzzer_call_bottom_cont, 0, 464, 1024, 120,
                                                                 NULL, false, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                                 NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                lv_common_img_btn_create(bottom_cont, buzzer_call_obj_handup, 460, 0, 104, 104,
                                         buzzer_call_handup_obj_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_call_buzzer.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

                /***********************************************
                 ** 作者: leo.liu
                 ** 日期: 2023-2-2 13:46:56
                 ** 说明:音量按钮图标显示
                 ***********************************************/
                {
                        lv_common_img_btn_create(bottom_cont, buzzer_call_obj_volume, 32, 24, 81, 81,
                                                 buzzer_call_volume_obj_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 resource_ui_src_get("btn_call_sound.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                }
        }
        {
                lv_obj_t *vol_cont = lv_common_img_btn_create(sat_cur_layout_screen_get(), buzzer_obj_id_vol_cont, 0, 504, 1024, 96,
                                                              NULL, true, LV_OPA_50, 0, LV_OPA_50, 0,
                                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                              NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_TOP_MID);

                lv_obj_add_flag(vol_cont, LV_OBJ_FLAG_HIDDEN);

                layout_buzzer_vol_bar_create(vol_cont);
        }

        ring_play_event_cmd_register(layout_buzzer_call_ringplay_register_callback);
}

static void sat_layout_quit(buzzer_call)
{
        lv_obj_pressed_func = lv_layout_touch_callback;
        sat_linphone_audio_play_stop();
        standby_timer_restart(true);
        lv_disp_set_bg_image(lv_disp_get_default(), NULL);
        ring_play_event_cmd_register(NULL);
}

sat_layout_create(buzzer_call);