#include "layout_define.h"
#include "layout_intercom_call.h"
enum
{
        intercom_talk_obj_top,
        intercom_talk_obj_status_label,
        intercom_talk_obj_status_icon,
        intercom_talk_obj_volume,
        intercom_talk_obj_handup,
        intercom_talk_obj_answer,
};

static int intercom_talk_timeout = 0;
/*0:空闲，1：call outgoing 2:incomming 3:talk*/
static int intercom_call_state = 0;
static char *intercom_call_user = NULL;
void intercom_call_status_setting(int state)
{
        intercom_call_state = state;
}
bool intercom_call_username_setting(const char *user)
{
        if (user == NULL)
        {
                return false;
        }
        if (intercom_call_user != NULL)
        {
                lv_mem_free(intercom_call_user);
        }
        intercom_call_user = lv_mem_alloc(strlen(user) + 1);
        strcpy(intercom_call_user, user);
        return true;
}
static lv_obj_t *intercom_talk_call_top_obj_item_get(int id)
{
        lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), intercom_talk_obj_top);
        if (parent == NULL)
        {
                SAT_DEBUG("   lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), intercom_talk_obj_top);");
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
static void intercom_talk_call_info_display(void)
{
        lv_obj_t *obj = intercom_talk_call_top_obj_item_get(0);
        if (obj == NULL)
        {
                SAT_DEBUG("lv_obj_t* obj = intercom_talk_call_top_obj_item_get(0);");
                return;
        }
        struct tm tm;
        user_time_read(&tm);
        lv_label_set_text_fmt(obj, "Call: %s    %04d-%02d:%02d %02d:%02d", intercom_call_user, tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min);
}
static void intercom_talk_call_time_display(void)
{
        lv_obj_t *obj = intercom_talk_call_top_obj_item_get(1);
        if (obj == NULL)
        {
                SAT_DEBUG("lv_obj_t* obj = intercom_talk_call_top_obj_item_get(0);");
                return;
        }
        lv_label_set_text_fmt(obj, "%02d:%02d", intercom_talk_timeout / 60, intercom_talk_timeout % 60);
}
static void intercom_talk_call_time_timer(lv_timer_t *ptime)
{
        if (intercom_talk_timeout == 0)
        {
                sat_layout_goto(home, LV_SCR_LOAD_ANIM_NONE, SAT_VOID);
        }
        intercom_talk_call_info_display();
        intercom_talk_call_time_display();
        intercom_talk_timeout--;
}
static void intercom_talk_status_background_display(void)
{
        if (intercom_call_state != 3)
        {
                lv_disp_set_bg_image(lv_disp_get_default(), resource_wallpaper_src_get("img_calling_backgroud.jpg", 1024, 600));
        }
        else
        {
                lv_disp_set_bg_image(lv_disp_get_default(), resource_wallpaper_src_get("img_calling_voice_backgroud.jpg", 1024, 600));
        }
}
static void intercom_talk_call_status_label_display(void)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), intercom_talk_obj_status_label);
        if (obj == NULL)
        {
                SAT_DEBUG("   lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), intercom_talk_obj_status_label);");
                return;
        }

        lv_label_set_text(obj, lang_str_get(intercom_call_state == 1   ? INTERCOM_XLS_LANG_ID_OUTCOMING_CALL
                                                            : intercom_call_state == 2 ? INTERCOM_XLS_LANG_ID_INCOMMING_CALL
                                                                                       : INTERCOM_XLS_LANG_ID_CONNECTED_CALL));
}
static void intercom_talk_call_status_icon_display(void)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), intercom_talk_obj_status_icon);
        if (obj == NULL)
        {
                SAT_DEBUG("   lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), intercom_talk_obj_status_icon);");
                return;
        }
        lv_obj_set_style_bg_img_src(obj, resource_ui_src_get(intercom_call_state == 3 ? "img_calling_voice.png" : "img_calling.png"), LV_PART_MAIN);
}

static void intercom_talk_handup_obj_click(lv_event_t *e)
{
        if (intercom_call_state == 1)
        {
                sat_layout_goto(intercom_call, LV_SCR_LOAD_ANIM_NONE, SAT_VOID);
        }
        else
        {
                sat_layout_goto(home, LV_SCR_LOAD_ANIM_NONE, SAT_VOID);
        }
}

static void intercom_talk_handup_obj_display(void)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), intercom_talk_obj_handup);
        if (obj == NULL)
        {
                SAT_DEBUG("   lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), intercom_talk_obj_handup);");
                return;
        }
        lv_obj_set_x(obj, intercom_call_state == 2 ? 536 : 460);
}

static void intercom_talk_answer_obj_display(void)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), intercom_talk_obj_answer);
        if (obj == NULL)
        {
                SAT_DEBUG("   lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), intercom_talk_obj_handup);");
                return;
        }
        if (intercom_call_state == 2)
        {
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
        else
        {
                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
}

static bool intercom_talk_call_strams_outgoing_callback(char *arg)
{
        if (intercom_call_state == 1)
        {
                ring_intercom_play();
        }

        return true;
}
static bool intercom_talk_call_end_callback(char *arg)
{
        sat_linphone_audio_play_stop();
        if (intercom_call_state == 1)
        {
                sat_layout_goto(intercom_call, LV_SCR_LOAD_ANIM_NONE, true);
        }
        else
        {
                sat_layout_goto(home, LV_SCR_LOAD_ANIM_NONE, true);
        }
}
static void intercom_talk_call_volume_obj_click(lv_event_t *e)
{
}
static void intercom_talk_call_volume_obj_display(void)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), intercom_talk_obj_volume);
        if (obj == NULL)
        {
                SAT_DEBUG("   lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), intercom_talk_obj_volume);");
                return;
        }
        lv_obj_set_style_bg_img_src(obj, resource_ui_src_get(intercom_call_state == 3 ? "btn_call_sound_voice.png" : "btn_call_sound.png"), LV_PART_MAIN);
}
static void intercom_talk_answer_obj_click(lv_event_t *e)
{
        intercom_call_state = 3;

        intercom_talk_timeout = 60;
        intercom_talk_call_volume_obj_display();
        intercom_talk_answer_obj_display();
        intercom_talk_handup_obj_display();
        intercom_talk_call_status_label_display();
        intercom_talk_call_status_icon_display();
        intercom_talk_status_background_display();
        intercom_talk_answer_obj_display();

        sat_linphone_answer(-1);

        char cmd[128] = {0};
        char user[128] = {0};
        sprintf(cmd, "SAT_CMD %s", LinphoneCallAnswerStr);
        sprintf(user, "%s/%s", intercom_call_user, "mynameleo");
        sat_linphone_message_cmd_send(user, cmd);
}

static bool intercom_talk_call_answer_callback(char *args)
{
        intercom_call_state = 3;

        intercom_talk_timeout = user_data_get()->call_time == 1 ? 1 * 60 : user_data_get()->call_time == 2 ? 3 * 60 : 5 * 60;
        intercom_talk_call_volume_obj_display();
        intercom_talk_answer_obj_display();
        intercom_talk_handup_obj_display();
        intercom_talk_call_status_label_display();
        intercom_talk_call_status_icon_display();
        intercom_talk_status_background_display();
        intercom_talk_answer_obj_display();

        sat_linphone_answer(-1);
        SAT_DEBUG("============================");
        return true;
}
static void sat_layout_enter(intercom_talk)
{
        standby_timer_close();
        intercom_talk_timeout = 30;
        intercom_talk_status_background_display();
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 顶部容器
         ***********************************************/
        {
                lv_obj_t *parent = lv_common_img_btn_create(sat_cur_layout_screen_get(), intercom_talk_obj_top, 0, 0, 1024, 80,
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
                        intercom_talk_call_info_display();
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
                        intercom_talk_call_time_display();
                        lv_sat_timer_create(intercom_talk_call_time_timer, 1000, NULL);
                }
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明:状态文本显示
         ***********************************************/
        {
                lv_common_text_create(sat_cur_layout_screen_get(), intercom_talk_obj_status_label, 362, 90, 300, 42,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      " ", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
                intercom_talk_call_status_label_display();
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明:状态文本图标显示
         ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), intercom_talk_obj_status_icon, 303, 142, 418, 314,
                                         NULL, false, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                intercom_talk_call_status_icon_display();
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:46:56
        ** 说明:挂断按钮图标显示
        ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), intercom_talk_obj_handup, 460, 464, 104, 104,
                                         intercom_talk_handup_obj_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_call_endcall.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                intercom_talk_handup_obj_display();
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明:接听按钮图标显示
         ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), intercom_talk_obj_answer, 384, 464, 104, 104,
                                         intercom_talk_answer_obj_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_call_call.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

                intercom_talk_answer_obj_display();
        }
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:46:56
         ** 说明:音量按钮图标显示
         ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), intercom_talk_obj_volume, 32, 488, 81, 81,
                                         intercom_talk_call_volume_obj_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_call_sound.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                intercom_talk_call_volume_obj_display();
        }

        if (intercom_call_state == 1)
        {
                char cmd[128] = {0};
                sprintf(cmd, "sip:%s", intercom_call_user);
                sat_linphone_call(cmd, false, true, NULL);

                user_linphone_call_answer_register(intercom_talk_call_answer_callback);
        }

        user_linphone_call_outgoing_call_register(intercom_talk_call_strams_outgoing_callback);
        user_linphone_call_end_register(intercom_talk_call_end_callback);
}

static void sat_layout_quit(intercom_talk)
{
        standby_timer_restart(true);
        intercom_call_state = 0;
        lv_disp_set_bg_image(lv_disp_get_default(), NULL);

        sat_linphone_handup(0xFF);
        user_linphone_call_outgoing_call_register(NULL);
        user_linphone_call_end_register(NULL);
        user_linphone_call_answer_register(NULL);
}

sat_layout_create(intercom_talk);