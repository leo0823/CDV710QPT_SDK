#include "layout_define.h"

bool frame_display_timeout_check(void);
static void layout_close_click(lv_event_t *ev)
{
    sat_layout_goto(home,LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
}
static void close_cancel_btn_create(void)
{
    lv_obj_add_event_cb(sat_cur_layout_screen_get(), layout_close_click, LV_EVENT_CLICKED, NULL);
}

static void sat_layout_enter(close)
{
    standby_timer_close();
	backlight_enable(false);
    close_cancel_btn_create();
    if(user_data_get()->motion.enable)
    {
        if (user_data_get()->motion.timer_en == false)
            {


            }
            else
            {
            }

    }
    else if ((user_data_get()->display.standby_mode == 1) && (user_data_get()->display.frame_list & 0x1F) && (frame_display_timeout_check() == false))
	{
        sat_layout_goto(frame_show,LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
	}
}

static void sat_layout_quit(close)
{
    extern bool tuya_api_app_sync_utc_time(void);
    tuya_api_app_sync_utc_time();
    lv_obj_remove_event_cb(sat_cur_layout_screen_get(), layout_close_click);
}

sat_layout_create(close);