#include "layout_define.h"
#include "layout_monitor.h"
#include "layout_intercom_call.h"
enum
{
        monitor_obj_id_top_cont,
        monitor_obj_id_disp_btn_cont,

        monitor_obj_id_disp_adj_cont,

        monitor_obj_id_vol_adj_cont,

        monitor_obj_id_channel_switch_left_btn,
        monitor_obj_id_channel_switch_right_btn,

        monitor_obj_id_buttom_cont,
        monitor_obj_id_volume_cont,
        monitor_obj_id_display_cont,
        monitor_obj_id_talk_cont,
        monitor_obj_id_handup_cont,
        monitor_obj_id_cctv_btn,
        monitor_obj_id_rec_video_cont,
        monitor_obj_id_rec_photo_cont,
        monitor_obj_id_nor_lock_cont,
        monitor_obj_id_lock_1_cont,
        monitor_obj_id_lock_2_cont,

        monitor_obj_id_unlock_icon,
};
static void monitor_obj_handup_display(void);
static void monitor_obj_normal_lock_display(void);
static void monitor_obj_volume_display(void);

static int monitor_timeout_sec = 0;
static bool is_monitor_door_camera_talk = false;
static bool is_monitor_snapshot_ing = false;
static bool is_monitor_record_video_ing = false;

static void monitor_obj_cctv_cancel_obj_click(lv_event_t *e)
{
        sat_layout_goto(home, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
}
/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: 获取顶部容器的子控件
 ***********************************************/
static lv_obj_t *monitor_top_child_obj_get(int id)
{
        lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), monitor_obj_id_top_cont);
        if (parent == NULL)
        {
                return NULL;
        }
        return lv_obj_get_child_form_id(parent, id);
}
/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: 获取顶部容器的子控件
 ***********************************************/
static lv_obj_t *monitor_buttom_child_obj_get(int id)
{
        lv_obj_t *parent = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), monitor_obj_id_buttom_cont);
        if (parent == NULL)
        {
                return NULL;
        }
        return lv_obj_get_child_form_id(parent, id);
}
/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: cctv 返回按钮
 ***********************************************/
static void monitor_obj_cctv_cancel_obj_display(void)
{
        lv_obj_t *obj = monitor_top_child_obj_get(0);
        if (obj == NULL)
        {
                return;
        }
        if (is_channel_ipc_camera(monitor_channel_get()) == true)
        {
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
        else
        {
                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
}
/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: 顶部时间通道显示
 ***********************************************/
static void monitior_obj_channel_info_obj_display(void)
{
        lv_obj_t *obj = monitor_top_child_obj_get(1);
        if (obj == NULL)
        {
                return;
        }
        struct tm tm;
        user_time_read(&tm);
        int channel = monitor_channel_get();
        if (is_channel_ipc_camera(channel) == true)
        {
                lv_obj_set_x(obj, 96);
                channel -= 8;
                lv_label_set_text_fmt(obj, "%s  %04d-%02d-%02d  %02d:%02d", network_data_get()->cctv_device[channel].name, tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min);
        }
        else
        {
                lv_obj_set_x(obj, 37);
                lv_label_set_text_fmt(obj, "%s  %04d-%02d-%02d  %02d:%02d", network_data_get()->door_device[channel].name, tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min);
        }
}
/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: 顶部图标显示
 ***********************************************/
static void montior_obj_top_icon_display(void)
{

        lv_obj_t *obj = NULL;
        int pos_x = 863;
        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: SD卡显示
         ***********************************************/
        {
                obj = monitor_top_child_obj_get(5);
                if (obj == NULL)
                {
                        return;
                }
                if (media_sdcard_insert_check() == true)
                {
                        lv_obj_set_x(obj, pos_x);
                        lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
                        pos_x -= 56;
                }
                else
                {
                        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                }
        }

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 自动记录
         ***********************************************/
        {
                obj = monitor_top_child_obj_get(4);
                if (obj == NULL)
                {
                        return;
                }
                lv_obj_set_x(obj, pos_x);
                pos_x -= 56;
                lv_obj_set_style_bg_img_src(obj, resource_ui_src_get(user_data_get()->auto_record_mode == 0 ? "ic_monitoring_manual.png" : "ic_monitoring_auto.png"), LV_PART_MAIN);
        }

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 移动侦测
         ***********************************************/
        {
                obj = monitor_top_child_obj_get(3);
                if (obj == NULL)
                {
                        return;
                }
                if (user_data_get()->motion.enable)
                {
                        lv_obj_set_x(obj, pos_x);
                        pos_x -= 56;
                        lv_obj_set_style_bg_img_src(obj, resource_ui_src_get(user_data_get()->motion.saving_fmt == 1 ? "ic_list_visitor_img.png" : "ic_list_visitor_video.png"), LV_PART_MAIN);
                }
                else
                {
                        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                }
        }
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-2-2 13:42:25
        ** 说明: 静音
        ***********************************************/
        {
                obj = monitor_top_child_obj_get(2);
                if (obj == NULL)
                {
                        return;
                }
                if (user_data_get()->audio.door_ring_volume == 0)
                {
                        lv_obj_set_x(obj, pos_x);
                        pos_x -= 56;
                        lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("ic_ring_volume_mute.png"), LV_PART_MAIN);
                }
                else
                {
                        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                }
        }
}
/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: 监控时间
 ***********************************************/
static void monitor_timeout_sec_reset(int sec)
{
        if (sec > 0)
        {
                monitor_timeout_sec = sec;
                return;
        }

        if (monitor_enter_flag_get() == MON_ENTER_MANUAL_CCTV_FLAG)
        {
                monitor_timeout_sec = 60;
        }
        else
        {
                monitor_timeout_sec = 30;
        }
}
/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: 监控时间文本显示
 ***********************************************/
static void monitor_obj_timeout_label_display(void)
{
        lv_obj_t *obj = monitor_top_child_obj_get(6);
        if (obj == NULL)
        {
                return;
        }
        lv_label_set_text_fmt(obj, "%02d:%02d", monitor_timeout_sec / 60, monitor_timeout_sec % 60);
}
static void monitor_obj_timeout_timer(lv_timer_t *ptimer)
{
        if (monitor_timeout_sec > 0)
        {
                monitor_obj_timeout_label_display();
                // monitor_timeout_sec--;
        }
        else
        {

                sat_layout_goto(home, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
        }
}
/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: 门口机切换
 ***********************************************/
static void monitor_obj_channel_switch_click(lv_event_t *e)
{
        lv_obj_t *obj = lv_event_get_current_target(e);
        if (obj == NULL)
        {
                return;
        }

        if (obj->id == monitor_obj_id_channel_switch_left_btn)
        {
                int ch = monitor_channel_prev_get();
                if (ch >= 0)
                {
                        monitor_enter_flag_set(is_channel_ipc_camera(ch) == true ? MON_ENTER_MANUAL_DOOR_FLAG : MON_ENTER_MANUAL_CCTV_FLAG);
                        monitor_channel_set(ch);
                        monitor_open();
                        monitor_timeout_sec_reset(0);
                        monitior_obj_channel_info_obj_display();
                }
        }
        else if (obj->id == monitor_obj_id_channel_switch_right_btn)
        {
                int ch = monitor_channel_next_get();
                if (ch >= 0)
                {
                        monitor_enter_flag_set(is_channel_ipc_camera(ch) == true ? MON_ENTER_MANUAL_DOOR_FLAG : MON_ENTER_MANUAL_CCTV_FLAG);
                        monitor_channel_set(ch);
                        monitor_open();
                        monitor_timeout_sec_reset(0);
                        monitior_obj_channel_info_obj_display();
                }
        }
}

/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: 音量调整
 ***********************************************/
static void monitor_obj_volume_click(lv_event_t *e)
{
}
static void monitor_obj_volume_display(void)
{
        lv_obj_t *obj = monitor_buttom_child_obj_get(monitor_obj_id_volume_cont);
        if (obj == NULL)
        {
                return;
        }
        lv_obj_set_style_bg_img_src(obj, resource_ui_src_get(is_monitor_door_camera_talk == true ? "btn_call_sound_voice.png" : "btn_call_sound.png"), LV_PART_MAIN);
}

/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: 颜色调整
 ***********************************************/
static void monitor_obj_display_click(lv_event_t *e)
{
}
/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: 通话按钮
 ***********************************************/
static void monitor_obj_talk_display(void)
{
        lv_obj_t *obj = monitor_buttom_child_obj_get(monitor_obj_id_talk_cont);
        if (obj == NULL)
        {
                return;
        }
        if ((is_channel_ipc_camera(monitor_channel_get()) == false) && (is_monitor_door_camera_talk == false))
        {
                if (user_data_get()->etc.open_the_door == 0)
                {
                        lv_obj_set_x(obj, 402);
                }
                else
                {
                        int ch = monitor_channel_get();
                        int lock_num = user_data_get()->etc.door2_lock_num;
                        lv_obj_set_x(obj, ((ch == MON_CH_DOOR2) && (lock_num == 2)) ? 286 : 344);
                }
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
        else
        {
                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
}
static void monitor_obj_talk_click(lv_event_t *e)
{
        if (is_monitor_door_camera_talk == false)
        {
                is_monitor_door_camera_talk = true;

                sat_linphone_answer(-1);
                monitor_obj_talk_display();
                monitor_obj_handup_display();
                monitor_obj_normal_lock_display();
                monitor_obj_volume_display();
        }
}
/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: 挂断按钮
 ***********************************************/
static void monitor_obj_handup_click(lv_event_t *e)
{
        sat_layout_goto(home, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
}
static void monitor_obj_handup_display(void)
{
        lv_obj_t *obj = monitor_buttom_child_obj_get(monitor_obj_id_handup_cont);
        if (obj == NULL)
        {
                return;
        }
        int ch = monitor_channel_get();
        int lock_num = user_data_get()->etc.door2_lock_num;

        if (is_channel_ipc_camera(ch) == false)
        {
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
                if (is_monitor_door_camera_talk == false)
                {
                        if (user_data_get()->etc.open_the_door == 0)
                        {
                                lv_obj_set_x(obj, 518);
                        }
                        else
                        {
                                lv_obj_set_x(obj, ((ch == MON_CH_DOOR2) && (lock_num == 2)) ? 634 : 576);
                        }
                        lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_call_cancel.png"), LV_PART_MAIN);
                }
                else
                {
                        if (user_data_get()->etc.open_the_door == 0)
                        {
                                lv_obj_set_x(obj, 518);
                        }
                        else
                        {
                                lv_obj_set_x(obj, ((ch == MON_CH_DOOR2) && (lock_num == 2)) ? 576 : 518);
                        }
                        lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_call_endcall.png"), LV_PART_MAIN);
                }
        }
        else
        {
                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
}

/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: 开锁指令
 ***********************************************/
static void monitor_unlock_ctrl(bool en)
{
        const char *user = monitor_channel_get_url(monitor_channel_get(), false);
        char *cmd[3] = {
            "SAT_SHELL echo 33 > /sys/class/gpio/export",
            "SAT_SHELL echo out > /sys/class/gpio/gpio33/direction",
            "SAT_SHELL echo 1 > /sys/class/gpio/gpio33/value"};

        if (en == false)
        {
                cmd[2] = "SAT_SHELL echo 0 > /sys/class/gpio/gpio33/value";
        }

        for (int i = 0; i < sizeof(cmd) / sizeof(char *); i++)
        {
                sat_linphone_message_cmd_send(user, cmd[i]);
        }
}
static void monitor_obj_unlock_open_timer(lv_timer_t *ptimer)
{
        lv_obj_t *obj = (lv_obj_t *)ptimer->user_data;

        if (obj != NULL)
        {
                lv_obj_del(obj);
        }
        monitor_unlock_ctrl(false);
        lv_timer_del(ptimer);
}
static bool monitor_obj_unlock_icon_display(void)
{
        lv_obj_t *obj = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), monitor_obj_id_unlock_icon);
        if (obj != NULL)
        {
                return false;
        }

        obj = lv_common_img_btn_create(sat_cur_layout_screen_get(), monitor_obj_id_unlock_icon, 436, 224, 152, 152,
                                       NULL, false, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                       0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                       0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                       resource_ui_src_get("6_call_notice_door.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_TOP_MID);

        lv_timer_reset(lv_sat_timer_create(monitor_obj_unlock_open_timer, 1500, obj));
        return true;
}

/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: 正常锁按钮
 ***********************************************/
static void monitor_obj_normal_lock_click(lv_event_t *e)
{
        if (monitor_obj_unlock_icon_display() == true)
        {
                ring_unlock_play();
                monitor_unlock_ctrl(true);
        }
}
static void monitor_obj_normal_lock_display(void)
{
        lv_obj_t *obj = monitor_buttom_child_obj_get(monitor_obj_id_nor_lock_cont);
        if (obj == NULL)
        {
                return;
        }
        int ch = monitor_channel_get();
        int lock_num = user_data_get()->etc.door2_lock_num;

        if (is_channel_ipc_camera(ch) == false)
        {
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
                if (is_monitor_door_camera_talk == false)
                {
                        if ((user_data_get()->etc.open_the_door == 0) || (((ch == MON_CH_DOOR2) && (lock_num == 2))))
                        {
                                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                        }
                        else
                        {
                                lv_obj_set_x(obj, 460);
                        }
                }
                else
                {
                        if ((user_data_get()->etc.open_the_door == 0) || ((ch == MON_CH_DOOR1) || (lock_num == 1)))
                        {
                                lv_obj_set_x(obj, 402);
                        }
                        else
                        {
                                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                        }
                }
        }
        else
        {
                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
}

/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: 正常锁按钮
 ***********************************************/
static void monitor_obj_lock_1_click(lv_event_t *e)
{
}
static void monitor_obj_lock_1_display(void)
{
        lv_obj_t *obj = monitor_buttom_child_obj_get(monitor_obj_id_lock_1_cont);
        if (obj == NULL)
        {
                return;
        }
        int ch = monitor_channel_get();
        int lock_num = user_data_get()->etc.door2_lock_num;

        if (is_channel_ipc_camera(ch) == false)
        {
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
                if (is_monitor_door_camera_talk == false)
                {
                        if ((user_data_get()->etc.open_the_door == 0) || (((ch == MON_CH_DOOR1) && (lock_num == 1))))
                        {
                                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                        }
                        else
                        {
                                lv_obj_set_x(obj, 402);
                        }
                }
                else
                {
                        if ((user_data_get()->etc.open_the_door == 0) || ((ch == MON_CH_DOOR1) || (lock_num == 1)))
                        {
                                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                        }
                        else
                        {
                                lv_obj_set_x(obj, 344);
                        }
                }
        }
        else
        {
                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
}
/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: 锁2
 ***********************************************/
static void monitor_obj_lock_2_click(lv_event_t *e)
{
}
static void monitor_obj_lock_2_display(void)
{
        lv_obj_t *obj = monitor_buttom_child_obj_get(monitor_obj_id_lock_2_cont);
        if (obj == NULL)
        {
                return;
        }
        int ch = monitor_channel_get();
        int lock_num = user_data_get()->etc.door2_lock_num;

        if (is_channel_ipc_camera(ch) == false)
        {
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
                if (is_monitor_door_camera_talk == false)
                {
                        if ((user_data_get()->etc.open_the_door == 0) || (((ch == MON_CH_DOOR1) && (lock_num == 1))))
                        {
                                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                        }
                        else
                        {
                                lv_obj_set_x(obj, 518);
                        }
                }
                else
                {
                        if ((user_data_get()->etc.open_the_door == 0) || ((ch == MON_CH_DOOR1) || (lock_num == 1)))
                        {
                                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                        }
                        else
                        {
                                lv_obj_set_x(obj, 460);
                        }
                }
        }
        else
        {
                lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
}

/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: 通话按钮
 ***********************************************/
static void monitor_obj_record_video_click(lv_event_t *e)
{
        if (is_monitor_record_video_ing == true)
        {
                record_video_stop();
        }
        else
        {
                record_video_start(true, REC_MODE_MANUAL);
        }
}
static void monitor_obj_record_video_display(void)
{
        lv_obj_t *obj = monitor_buttom_child_obj_get(monitor_obj_id_rec_video_cont);
        if (obj == NULL)
        {
                return;
        }
        if (is_monitor_record_video_ing == true)
        {
                lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_call_rec_ing.png"), LV_PART_MAIN);
        }
        else
        {
                lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_call_rec.png"), LV_PART_MAIN);
        }
}
/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: 通话按钮
 ***********************************************/
static void monitor_obj_record_photo_click(lv_event_t *e)
{
        if (is_monitor_snapshot_ing == false)
        {
                sat_linphone_calls_cmd_send();
                record_jpeg_start(REC_MODE_MANUAL);
        }
}
static void monitor_obj_record_photo_display(void)
{
        lv_obj_t *obj = monitor_buttom_child_obj_get(monitor_obj_id_rec_photo_cont);
        if (obj == NULL)
        {
                return;
        }
        if (is_monitor_snapshot_ing == true)
        {
                lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_call_save.png"), LV_PART_MAIN);
        }
        else
        {
                lv_obj_set_style_bg_img_src(obj, resource_ui_src_get("btn_call_camera.png"), LV_PART_MAIN);
        }
}
/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: SD卡状态变化处理
 ***********************************************/
static void monitor_sd_state_change_callback(void)
{
        montior_obj_top_icon_display();
}
/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: 抓拍状态显示
 ***********************************************/
static void monitor_snapshot_state_callback(bool snapshot_ing)
{
        is_monitor_snapshot_ing = snapshot_ing;
        monitor_obj_record_photo_display();
}
/***********************************************
 ** 作者: leo.liu
 ** 日期: 2023-2-2 13:42:25
 ** 说明: 记录状态状态显示
 ***********************************************/
static void monitor_record_video_state_callback(bool record_ing)
{
        is_monitor_record_video_ing = record_ing;
        monitor_obj_record_video_display();
}
static void sat_layout_enter(monitor)
{
        is_monitor_door_camera_talk = false;
        is_monitor_snapshot_ing = false;
        is_monitor_record_video_ing = false;
        monitor_timeout_sec_reset(0);

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 顶部容器
         ***********************************************/
        {
                lv_obj_t *parent = lv_common_img_btn_create(sat_cur_layout_screen_get(), monitor_obj_id_top_cont, 0, 0, 1024, 80,
                                                            NULL, false, LV_OPA_30, 0, LV_OPA_30, 0,
                                                            0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                            0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                            NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

                /***********************************************
                 ** 作者: leo.liu
                 ** 日期: 2023-2-2 13:42:25
                 ** 说明: 返回键(CCTV)
                 ***********************************************/
                {
                        lv_common_img_btn_create(parent, 0, 0, 0, 80, 80,
                                                 monitor_obj_cctv_cancel_obj_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 resource_ui_src_get("btn_title_back.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

                        monitor_obj_cctv_cancel_obj_display();
                }
                /***********************************************
                 ** 作者: leo.liu
                 ** 日期: 2023-2-2 13:42:25
                 ** 说明: 通道显示
                 ***********************************************/
                {
                        lv_common_text_create(parent, 1, 0, 23, 324, 42,
                                              NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              NULL, 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_LEFT, lv_font_normal);
                        monitior_obj_channel_info_obj_display();
                }
                /***********************************************
                 ** 作者: leo.liu
                 ** 日期: 2023-2-2 13:42:25
                 ** 说明: 静音图标显示
                 ***********************************************/
                {
                        lv_common_img_btn_create(parent, 2, 695, 16, 48, 48,
                                                 NULL, false, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 resource_ui_src_get("ic_ring_volume_mute.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                }
                /***********************************************
                 ** 作者: leo.liu
                 ** 日期: 2023-2-2 13:42:25
                 ** 说明: 移动侦测图标显示
                 ***********************************************/
                {
                        lv_common_img_btn_create(parent, 3, 751, 16, 48, 48,
                                                 NULL, false, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 resource_ui_src_get("ic_list_visitor_video.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                }
                /***********************************************
                 ** 作者: leo.liu
                 ** 日期: 2023-2-2 13:42:25
                 ** 说明: 自动侦测图标显示
                 ***********************************************/
                {
                        lv_common_img_btn_create(parent, 4, 807, 16, 48, 48,
                                                 NULL, false, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 resource_ui_src_get("ic_monitoring_auto.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                }
                /***********************************************
                ** 作者: leo.liu
                ** 日期: 2023-2-2 13:42:25
                ** 说明: sd图标显示
                ***********************************************/
                {
                        lv_common_img_btn_create(parent, 5, 872, 16, 48, 48,
                                                 NULL, false, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 resource_ui_src_get("ic_monitoring_sdcard.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                }

                montior_obj_top_icon_display();
                /***********************************************
                 ** 作者: leo.liu
                 ** 日期: 2023-2-2 13:42:25
                 ** 说明: 倒计时
                 ***********************************************/
                {
                        lv_common_text_create(parent, 6, 927, 23, 73, 42,
                                              NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                              NULL, 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_LEFT, lv_font_normal);

                        lv_timer_ready(lv_sat_timer_create(monitor_obj_timeout_timer, 1000, NULL));
                }
        }

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 通道切换
         ***********************************************/
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), monitor_obj_id_channel_switch_left_btn, 10, 276, 82, 82,
                                         monitor_obj_channel_switch_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_thumbnail_arrow_left_n.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_TOP_MID);

                lv_common_img_btn_create(sat_cur_layout_screen_get(), monitor_obj_id_channel_switch_right_btn, 932, 276, 82, 82,
                                         monitor_obj_channel_switch_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_thumbnail_arrow_right_n.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_TOP_MID);
        }

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-2-2 13:42:25
         ** 说明: 底部容器
         ***********************************************/
        {
                lv_obj_t *parent = lv_common_img_btn_create(sat_cur_layout_screen_get(), monitor_obj_id_buttom_cont, 0, 464, 1024, 120,
                                                            NULL, false, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                            0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                            0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                            NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

                /***********************************************
                ** 作者: leo.liu
                ** 日期: 2023-2-2 13:42:25
                ** 说明: 显示调整
                ***********************************************/
                {
                        lv_common_img_btn_create(parent, monitor_obj_id_display_cont, 32, 24, 80, 81,
                                                 monitor_obj_display_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 resource_ui_src_get("btn_call_brightness.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_TOP_MID);
                }
                /***********************************************
                 ** 作者: leo.liu
                 ** 日期: 2023-2-2 13:42:25
                 ** 说明: 音量调整
                 ***********************************************/
                {
                        lv_common_img_btn_create(parent, monitor_obj_id_volume_cont, 136, 24, 80, 81,
                                                 monitor_obj_volume_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 resource_ui_src_get("btn_call_sound.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_TOP_MID);

                        monitor_obj_volume_display();
                }

                /***********************************************
                ** 作者: leo.liu
                ** 日期: 2023-2-2 13:42:25
                ** 说明: 通话按钮
                ***********************************************/
                {
                        lv_common_img_btn_create(parent, monitor_obj_id_talk_cont, 235, 0, 104, 104,
                                                 monitor_obj_talk_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 resource_ui_src_get("btn_call_call.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_TOP_MID);

                        monitor_obj_talk_display();
                }
                /***********************************************
                 ** 作者: leo.liu
                 ** 日期: 2023-2-2 13:42:25
                 ** 说明: 挂断按钮
                 ***********************************************/
                {
                        lv_common_img_btn_create(parent, monitor_obj_id_handup_cont, 517, 0, 104, 104,
                                                 monitor_obj_handup_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 resource_ui_src_get("btn_call_cancel.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_TOP_MID);

                        monitor_obj_handup_display();
                }
                /***********************************************
                ** 作者: leo.liu
                ** 日期: 2023-2-2 13:42:25
                ** 说明: 正常锁
                ***********************************************/
                {
                        lv_common_img_btn_create(parent, monitor_obj_id_nor_lock_cont, 460, 0, 104, 104,
                                                 monitor_obj_normal_lock_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 resource_ui_src_get("btn_call_door_open.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_TOP_MID);

                        monitor_obj_normal_lock_display();
                }
                /***********************************************
                ** 作者: leo.liu
                ** 日期: 2023-2-2 13:42:25
                ** 说明: 锁1
                ***********************************************/
                {
                        lv_common_img_btn_create(parent, monitor_obj_id_lock_1_cont, 350, 0, 104, 104,
                                                 monitor_obj_lock_1_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 resource_ui_src_get("btn_call_door1_open.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_TOP_MID);

                        monitor_obj_lock_1_display();
                }
                /***********************************************
                 ** 作者: leo.liu
                 ** 日期: 2023-2-2 13:42:25
                 ** 说明: 锁2
                 ***********************************************/
                {
                        lv_common_img_btn_create(parent, monitor_obj_id_lock_2_cont, 350, 0, 104, 104,
                                                 monitor_obj_lock_2_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 resource_ui_src_get("btn_call_door2_open.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_TOP_MID);

                        monitor_obj_lock_2_display();
                }
                /***********************************************
                 ** 作者: leo.liu
                 ** 日期: 2023-2-2 13:42:25
                 ** 说明: 视频
                 ***********************************************/
                {
                        lv_common_img_btn_create(parent, monitor_obj_id_rec_video_cont, 808, 24, 80, 81,
                                                 monitor_obj_record_video_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 resource_ui_src_get("btn_call_rec.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_TOP_MID);

                        monitor_obj_record_video_display();
                }
                /***********************************************
                 ** 作者: leo.liu
                 ** 日期: 2023-2-2 13:42:25
                 ** 说明: 照片
                 ***********************************************/
                {
                        lv_common_img_btn_create(parent, monitor_obj_id_rec_photo_cont, 912, 24, 80, 81,
                                                 monitor_obj_record_photo_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                 resource_ui_src_get("btn_call_camera.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_TOP_MID);

                        monitor_obj_record_photo_display();
                }
        }

        monitor_open();

        /*門口機内部呼叫*/
        user_linphone_call_incoming_received_register(monitor_doorcamera_call_inside_func);
        /*sd卡状态处理*/
        sd_state_channge_callback_register(monitor_sd_state_change_callback);

        /*抓拍注册*/
        snapshot_state_callback_register(monitor_snapshot_state_callback);
        /*记录注册*/
        record_state_callback_register(monitor_record_video_state_callback);
}
static void sat_layout_quit(monitor)
{

        monitor_close();

        user_linphone_call_incoming_received_register(monitor_doorcamera_call_extern_func);
        /*sd卡状态处理 */
        sd_state_channge_callback_register(NULL);
}

sat_layout_create(monitor);

/*************************************************************************************************************************************************
*******************************											                                               *******************************
*******************************					                               楚河汉界		                                         *******************************
*******************************											                                               *******************************
*************************************************************************************************************************************************/
//<sip:010193001011@172.16.0.110>
static int monitor_incoming_user_get_channel(char *arg)
{
        char *ps = strstr(arg, "<sip:") + 5;
        char *pe = strchr(arg, '>');
        if ((ps == NULL) || (pe == NULL))
        {
                return -1;
        }
        *pe = 0;
        // SAT_DEBUG("ncoming number:%s", ps);
        return monitor_index_get_by_user(ps);
}

bool monitor_doorcamera_call_extern_func(char *arg)
{
        SAT_DEBUG("-------->>%s", arg);
        int from_channel = 0;
        if ((from_channel = monitor_incoming_user_get_channel(arg)) >= 0)
        {
                if (from_channel == 0)
                {
                        ring_door1_call_play();
                }
                else if (from_channel == 1)
                {
                        ring_door2_call_play();
                }
                monitor_enter_flag_set(MON_ENTER_CALL_FLAG);
                monitor_channel_set(from_channel);
                sat_layout_goto(monitor, LV_SCR_LOAD_ANIM_FADE_IN, true);
        }
        else if (sat_cur_layout_get() != sat_playout_get(intercom_talk))
        {
                char *ptr = strstr(arg, "sip:");
                if ((ptr != NULL) && (strlen(ptr) > 4))
                {
                        ring_intercom_play();
                        intercom_call_status_setting(2);
                        intercom_call_username_setting(ptr + 4);
                        SAT_DEBUG("call :%s", ptr);
                        sat_layout_goto(intercom_talk, LV_SCR_LOAD_ANIM_FADE_IN, true);
                }
        }
        return true;
}
bool monitor_doorcamera_call_inside_func(char *arg)
{
        SAT_DEBUG("-------->>%s", arg);
        int from_channel = 0;
        int cur_channel = monitor_channel_get();
        if ((from_channel = monitor_incoming_user_get_channel(arg)) >= 0)
        {
                if (from_channel == 0)
                {
                        ring_door1_call_play();
                }
                else if (from_channel == 1)
                {
                        ring_door2_call_play();
                }

                if (from_channel != cur_channel)
                {
                        monitor_enter_flag_set(MON_ENTER_CALL_FLAG);
                        monitor_channel_set(from_channel);
                        monitior_obj_channel_info_obj_display();
                }
        }
        return true;
}