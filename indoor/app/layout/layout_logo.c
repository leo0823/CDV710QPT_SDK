#include "layout_define.h"
#include "onvif.h"
#include "tuya_api.h"
#include "tuya_uuid_and_key.h"
#include "layout_monitor.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
// #include "dds/topic_table.h"
// #include "dds/msgStruct/message_data.h"
// #include "dds/public_topic.h"

#include "common/user_record.h"
#include "common/user_network.h"
#include "common/user_linphone.h"

static int input_index = 0;

enum
{
        logo_obj_id_logo_img,
        logo_obj_id_model_label,
        logo_obj_id_version_label,

        logo_obj_id_tuya_register_tips,
        logo_obj_id_tuya_register_textarea,
        logo_obj_id_tuya_register_number_keyboard_btn,

        // 都是给全局用的id值，在layout页不能用到些值
        buzzer_alarm_screen_id = 0xfffe,
        sd_state_change_obj_id_format_msgbox_cont = 0xffff,
};

enum
{
        obj_id_sd_flsh_swap_preload,
        obj_id_sd_img,
        obj_id_sd_flsh_swap_img,
        obj_id_flash_img,
        sd_state_change_obj_id_format_msgbox,
        sd_state_change_obj_id_format_text,
        sd_state_change_obj_id_msgbox_confirm,
};

typedef enum
{
        buzzer_alarm_background_id,
        buzzer_call_text_id,
        buzzer_call_icon_id,
        buzzer_call_confirm_id,

} buzzer_alarm_background_obj_id;

/************************************************************
** 函数说明: 待机检测任务
** 作者: xiaoxiao
** 日期: 2023-05-19 15:14:02
** 参数说明:
** 注意事项:
************************************************************/
void standby_dection_timer(lv_timer_t *t)
{
        extern bool standby_timeout_check_and_process(void);
        standby_timeout_check_and_process();
}

static void logo_sip_server_register(void)
{

        char sip_user_id[16] = {0};
        char sip_sever[32] = {0};
        sprintf(sip_user_id, "50%d", user_data_get()->system_mode & 0x0F);
        sprintf(sip_sever, "%s:5066", user_data_get()->mastar_wallpad_ip);
        // printf("%s register to :%s\n",sip_user_id,sip_sever);
        sat_linphone_register(NULL, sip_user_id, NULL, sip_sever);
}

static void sip_register_timer(lv_timer_t *t)
{
        logo_sip_server_register();
}

static void sd_state_change_msgbox_cancel_click(lv_event_t *ev)
{
        setting_msgdialog_msg_del(sd_state_change_obj_id_format_msgbox_cont);
}

static void sd_state_checking_timer(lv_timer_t *timer)
{
        lv_obj_t *masgbox = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), sd_state_change_obj_id_format_msgbox_cont);
        if (masgbox != NULL)
        {
                setting_msgdialog_msg_del(sd_state_change_obj_id_format_msgbox_cont);
        }
        if ((media_sdcard_insert_check() == SD_STATE_INSERT) || (media_sdcard_insert_check() == SD_STATE_FULL))
        {
        }
        else if ((media_sdcard_insert_check() == SD_STATE_ERROR) || (media_sdcard_insert_check() == SD_STATE_UNPLUG))
        {
                masgbox = setting_msgdialog_msg_bg_create(sd_state_change_obj_id_format_msgbox_cont, sd_state_change_obj_id_format_msgbox, 282, 143, 460, 283);
                setting_msgdialog_msg_create(masgbox, sd_state_change_obj_id_format_text, lang_str_get(SD_XLS_LANG_ID_SD_IS_VALID), 0, 60, 460, 120);
        }
        setting_msgdialog_msg_confirm_btn_create(masgbox, sd_state_change_obj_id_msgbox_confirm, sd_state_change_msgbox_cancel_click);
        lv_timer_del(timer);
}

/************************************************************
** 函数说明: SD状态改变默认回调
** 作者: xiaoxiao
** 日期: 2023-07-15 11:50:12
** 参数说明:
** 注意事项:
************************************************************/
void sd_state_change_default_callback(void)
{
        SAT_DEBUG("================================");
        if (user_data_get()->is_device_init == false)
        {
                return;
        }
        lv_obj_t *masgbox = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), sd_state_change_obj_id_format_msgbox_cont);
        if (masgbox != NULL)
        {
                setting_msgdialog_msg_del(sd_state_change_obj_id_format_msgbox_cont);
        }
        masgbox = setting_msgdialog_msg_bg_create(sd_state_change_obj_id_format_msgbox_cont, sd_state_change_obj_id_format_msgbox, 282, 143, 460, 283);
        setting_msgdialog_msg_create(masgbox, sd_state_change_obj_id_format_text, lang_str_get(SD_XLS_LANG_ID_CHECKING_SD), 0, 120, 460, 120);

        lv_sat_timer_create(sd_state_checking_timer, 500, NULL);
}

static int buzzer_call_count = 0;            // 蜂鸣器触发时间倒计时
static lv_timer_t *buzzer_call_timer = NULL; // 蜂鸣器呼叫定时器任务

static void buzzer_alarm_confirm_btn_click(lv_event_t *t)
{
        lv_obj_t *bg = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), buzzer_alarm_screen_id);
        if (bg != NULL)
        {
                user_data_get()->alarm.buzzer_alarm = false;
                user_data_save();
                lv_timer_del(buzzer_call_timer);
                buzzer_call_timer = NULL;
                buzzer_call_count = 0;
                lv_obj_del(bg);
        }
}

static void buzzer_call_trigger_ui_create(void)
{
        if ((sat_cur_layout_get() == sat_playout_get(alarm)) || (sat_cur_layout_get() == sat_playout_get(monitor)))
        {
                lv_obj_t *obj = lv_common_text_create(sat_cur_layout_screen_get(), buzzer_alarm_screen_id, 109, 284, 247, 68,
                                                      NULL, LV_OPA_80, 0x474747, LV_OPA_80, 0,
                                                      16, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      16, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                      lang_str_get(CALL_XLS_LANG_ID_BUZZER_CALL), 0XFFFFFF, 0XFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_normal);
                lv_obj_set_style_pad_top(obj, 23, LV_PART_MAIN);
        }
        else
        {
                lv_obj_t *parent = lv_common_img_btn_create(sat_cur_layout_screen_get(), buzzer_alarm_screen_id, 0, 0, 1024, 600,
                                                            NULL, false, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                            0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                            0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                            NULL, LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

                parent = lv_common_img_btn_create(parent, buzzer_alarm_background_id, 0, 0, 1024, 600,
                                                  NULL, false, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                                  0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                  0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                  resource_ui_src_get("bg_popup_buzzer call.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                lv_common_text_create(parent, buzzer_call_text_id, 303, 58, 418, 38,
                                      NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                      lang_str_get(CALL_XLS_LANG_ID_BUZZER_CALL), 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);

                lv_common_img_btn_create(parent, buzzer_call_icon_id, 303, 142, 418, 314,
                                         NULL, false, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("img_calling_bell.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);

                lv_common_img_btn_create(parent, buzzer_call_confirm_id, 388, 472, 248, 72,
                                         buzzer_alarm_confirm_btn_click, true, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0x808080,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("btn_buzzer_confrim.png"), LV_OPA_TRANSP, 0x00a8ff, LV_ALIGN_CENTER);
                ring_buzzer_play(user_data_get()->audio.buzzer_tone);
        }
}

/************************************************************
** 函数说明: 蜂鸣器定时任务，蜂鸣器的触发时长为6秒，针对不同的场景，在触发时间内做相应的行为
** 作者: xiaoxiao
** 日期：2023-09-12 08:11:03
** 参数说明:
** 注意事项：
************************************************************/
static void default_buzzer_call_timer(lv_timer_t *timer)
{
        lv_obj_t *bg = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), buzzer_alarm_screen_id);
        buzzer_call_count++;
        if (buzzer_call_count == 12)
        {
                buzzer_alarm_confirm_btn_click(NULL);
        }
        else if (bg == NULL)
        {
                buzzer_call_trigger_ui_create();
        }
}

static void (*buzzer_call_fun)(void) = NULL;

void buzzer_call_callback_register(void (*callback)(void))
{
        buzzer_call_fun = callback;
}

bool buzzer_call_trigger_check(void)
{
        if (user_data_get()->alarm.buzzer_alarm)
        {
                if (buzzer_call_fun != NULL)
                {
                        buzzer_call_fun();
                }
        }
        else if (buzzer_call_timer != NULL)
        {
                buzzer_alarm_confirm_btn_click(NULL);
        }
        return true;
}

/************************************************************
** 函数说明: 蜂鸣器警报触发函数
** 作者: xiaoxiao
** 日期：2023-09-12 08:00:33
** 参数说明:
** 注意事项：
************************************************************/
static void buzzer_alarm_trigger_default(void)
{
        if (user_data_get()->is_device_init == false)
        {
                return;
        }
        if (buzzer_call_timer)
        {
                return;
        }
        buzzer_call_trigger_ui_create();
        buzzer_call_timer = lv_timer_create(default_buzzer_call_timer, 500, NULL);
}

/************************************************************
** 函数说明: 警报页面铃声播放/暂停同步
** 作者: xiaoxiao
** 日期：2023-09-12 08:00:33
** 参数说明:
** 注意事项：
************************************************************/
static void alarm_ringtone_play_check(void)
{
        if (sat_cur_layout_get() == sat_playout_get(alarm))
        {
                if (user_data_get()->alarm.alarm_ring_play == false)
                {
                        sat_linphone_audio_play_stop();
                }
                else
                {
                        ring_alarm_play();
                }
        }
}

/************************************************************
** 函数说明: 警报页面stop/return状态转换同步
** 作者: xiaoxiao
** 日期：2023-09-12 08:00:07
** 参数说明:
** 注意事项：
************************************************************/
static void alarm_stop_return_status_display_check(void)
{
        if (sat_cur_layout_get() == sat_playout_get(alarm))
        {
                extern bool layout_alarm_stop_btn_label_display();
                layout_alarm_stop_btn_label_display();
        }
}

/************************************************************
** 函数说明:
** 作者: xiaoxiao
** 日期：2023-09-25 21:23:39
** 参数说明:
** 注意事项：
************************************************************/
static void away_countdown_enable_sync_check(void)
{
        if (user_data_get()->alarm.away_setting_countdown)
        {
                sat_linphone_handup(0xFFFF);
                sat_layout_goto(away_count, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
        }
        else if (sat_cur_layout_get() == sat_playout_get(away_count))
        {
                sat_layout_goto(away, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
        }
}
/************************************************************
** 函数说明: 文件同步事件回调
** 作者: xiaoxiao
** 日期：2023-09-12 07:59:42
** 参数说明:
** 注意事项：
************************************************************/
static void asterisk_server_sync_data_callback(char flag, char *data, int size, int pos, int max)
{
        if (user_data_get()->is_device_init == false)
        {
                return;
        }
        /*master本身不接受回调处理*/
        if (((user_data_get()->system_mode & 0x0F) == 0x01) && (flag != 0x00))
        {
                return;
        }

        static char *recv_data = NULL;
        static int recv_size = 0;
        if ((recv_data == NULL) && (pos == 0))
        {
                recv_data = (char *)malloc(max);
                recv_size = max;
        }

        if (recv_data == NULL)
        {
                printf("[%s:%d] sync data failed\n", __func__, __LINE__);
                return;
        }

        if (recv_size != max)
        {
                printf("[%s:%d] reve data malloc failed( %d %d)\n", __func__, __LINE__, recv_size, max);
                free(recv_data);
                recv_data = NULL;
                return;
        }
        memcpy(&recv_data[pos], data, size);

        if ((size + pos) == max)
        {
                if ((flag == 0x00) && (max == sizeof(user_data_info)))
                {
                        user_data_info *info = (user_data_info *)recv_data;

                        if ((user_data_get()->system_mode & 0x0F) != 0x01)
                        {
                                user_data_get()->etc.call_time = info->etc.call_time;
                                user_data_get()->etc.open_the_door = info->etc.open_the_door;
                                user_data_get()->etc.door1_open_door_mode = info->etc.door1_open_door_mode;
                                user_data_get()->etc.door2_lock_num = info->etc.door2_lock_num;
                                memcpy(&user_data_get()->alarm.cctv_sensor, &info->alarm.cctv_sensor, sizeof(user_data_get()->alarm.cctv_sensor));
                                memcpy(&user_data_get()->alarm.away_sensor_enable, &info->alarm.away_sensor_enable, sizeof(user_data_get()->alarm.away_sensor_enable));
                                memcpy(&user_data_get()->alarm.security_sensor_enable, &info->alarm.security_sensor_enable, sizeof(user_data_get()->alarm.security_sensor_enable));
                                memcpy(&user_data_get()->alarm.alarm_enable, &info->alarm.alarm_enable, sizeof(user_data_get()->alarm.alarm_enable));
                                memcpy(&user_data_get()->alarm.alarm_gpio_value_group, &info->alarm.alarm_gpio_value_group, sizeof(user_data_get()->alarm.alarm_gpio_value_group));
                                standby_timer_close();
                                user_data_get()->etc.cur_time = info->etc.cur_time;
                                user_time_set(&user_data_get()->etc.cur_time);
                                standby_timer_restart(true);
                        }
                        user_data_get()->alarm.away_alarm_enable = info->alarm.away_alarm_enable;
                        user_data_get()->alarm.security_alarm_enable = info->alarm.security_alarm_enable;
                        user_data_get()->alarm.security_auto_record = info->alarm.security_auto_record;
                        user_data_get()->alarm.away_auto_record = info->alarm.away_auto_record;
                        user_data_get()->alarm.away_setting_time = info->alarm.away_setting_time;
                        user_data_get()->alarm.away_release_time = info->alarm.away_release_time;
                        user_data_get()->alarm.away_save_photo = info->alarm.away_save_photo;
                        user_data_get()->alarm.bypass_call = info->alarm.bypass_call;
                        memcpy(&user_data_get()->alarm.away_alarm_enable_list, &info->alarm.away_alarm_enable_list, sizeof(user_data_get()->alarm.away_alarm_enable_list));
                        memcpy(&user_data_get()->alarm.security_alarm_enable_list, &info->alarm.security_alarm_enable_list, sizeof(user_data_get()->alarm.security_alarm_enable_list));
                        for (int i = 0; i < 8; i++) // 警报触发取消同步
                        {
                                if ((user_data_get()->alarm.alarm_trigger[i]) != (info->alarm.alarm_trigger[i]))
                                {
                                        memcpy(&user_data_get()->alarm.alarm_trigger, &info->alarm.alarm_trigger, sizeof(user_data_get()->alarm.alarm_trigger));
                                        user_data_get()->alarm.alarm_trigger[i] = info->alarm.alarm_trigger[i];
                                        alarm_trigger_check();
                                }
                        }
                        if (user_data_get()->alarm.buzzer_alarm != info->alarm.buzzer_alarm) // 蜂鸣器触发，取消同步
                        {
                                user_data_get()->alarm.buzzer_alarm = info->alarm.buzzer_alarm;
                                buzzer_call_trigger_check();
                        }
                        if (user_data_get()->alarm.alarm_ring_play != info->alarm.alarm_ring_play) // 警报页面内，铃声播放取消同步
                        {
                                user_data_get()->alarm.alarm_ring_play = info->alarm.alarm_ring_play;
                                alarm_ringtone_play_check();
                        }
                        if (0 /*user_data_get()->alarm.is_alarm_return != info->alarm.is_alarm_return*/) // 警报页面内，stop/return状态同步(客户取消return状态)
                        {
                                user_data_get()->alarm.is_alarm_return = info->alarm.is_alarm_return;
                                alarm_stop_return_status_display_check();
                        }
                        if (user_data_get()->alarm.away_setting_countdown != info->alarm.away_setting_countdown) // 警报页面内，铃声播放取消同步
                        {
                                user_data_get()->alarm.away_setting_countdown = info->alarm.away_setting_countdown;
                                away_countdown_enable_sync_check();
                        }
                        user_data_save();
                }
                else if ((flag == 0x01) && (max == sizeof(user_network_info)))
                {
                        user_network_info *info = (user_network_info *)recv_data;
                        memcpy(network_data_get()->door_device, info->door_device, sizeof(struct ipcamera_info) * DEVICE_MAX);
                        memcpy(network_data_get()->cctv_device, info->cctv_device, sizeof(struct ipcamera_info) * DEVICE_MAX);
                        strncpy(network_data_get()->sip_server, info->sip_server, sizeof(network_data_get()->sip_server));
                        strncpy(network_data_get()->cctv_server, info->cctv_server, sizeof(network_data_get()->cctv_server));
                        strncpy(network_data_get()->local_server, info->local_server, sizeof(network_data_get()->local_server));
                        strncpy(network_data_get()->network.gateway, info->network.gateway, sizeof(network_data_get()->network.gateway));
                        strncpy(network_data_get()->network.dns, info->network.dns, sizeof(network_data_get()->network.dns));
                        strncpy(network_data_get()->guard_number, info->guard_number, sizeof(network_data_get()->guard_number));
                }
                else if ((flag == 0x02) && (max == sizeof(asterisk_register_info) * 20))
                {
                        asterisk_register_info *register_info = asterisk_register_info_get();
                        if (register_info == NULL)
                        {
                                perror("asterisk info is null\n");
                        }
                        else
                        {
                                memcpy(register_info, recv_data, max);
                        }
                }
                free(recv_data);
                recv_data = NULL;
        }
}

static void flash_backup_to_sd_timer(lv_timer_t *t)
{
        bool backuped = *(bool *)t->user_data;
        if (backuped)
        {
                lv_obj_t *masgbox = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), sd_state_change_obj_id_format_msgbox_cont);
                if (masgbox != NULL)
                {
                        setting_msgdialog_msg_del(sd_state_change_obj_id_format_msgbox_cont);
                }
        }
        lv_timer_del(t);
}

/************************************************************
** 函数说明: 媒体照片备份
** 作者: xiaoxiao
** 日期：2023-09-12 07:58:08
** 参数说明:
** 注意事项：开机备份过程不需ui显示（无效函数）
************************************************************/
void flash_backup_to_sd_dispaly_create(bool *backup_ed)
{
        lv_obj_t *masgbox = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), sd_state_change_obj_id_format_msgbox_cont);
        if (masgbox != NULL)
        {
                setting_msgdialog_msg_del(sd_state_change_obj_id_format_msgbox_cont);
        }
        masgbox = setting_msgdialog_msg_bg_create(sd_state_change_obj_id_format_msgbox_cont, sd_state_change_obj_id_format_msgbox, 282, 143, 460, 283);

        lv_common_img_btn_create(masgbox, obj_id_sd_img, 55, 150, 67, 80,
                                 NULL, false, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                 resource_ui_src_get("Combined_Shape.png"), LV_OPA_TRANSP, 0, LV_ALIGN_CENTER);

        lv_common_img_btn_create(masgbox, obj_id_sd_flsh_swap_img, 175, 180, 105, 44,
                                 NULL, false, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                 resource_ui_src_get("Shape.png"), LV_OPA_TRANSP, 0, LV_ALIGN_CENTER);

        lv_common_img_btn_create(masgbox, obj_id_flash_img, 335, 150, 93, 71,
                                 NULL, false, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                 0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                 resource_ui_src_get("Combined_Shape.png"), LV_OPA_TRANSP, 0, LV_ALIGN_CENTER);
        // 旋转器创建
        {
                static lv_style_t style; // 创建样式
                static lv_style_t bc_style;

                lv_style_init(&style);                                           // 初始化样式
                lv_style_set_arc_color(&style, lv_color_make(0x00, 0x96, 0xFF)); // 设置圆弧颜色
                lv_style_set_arc_width(&style, 12);                              // 设置圆弧宽度；

                lv_style_init(&bc_style);                                           // 初始化样式
                lv_style_set_arc_color(&bc_style, lv_color_make(0xFF, 0xFF, 0xFF)); // 设置背景圆环颜色
                lv_style_set_arc_width(&bc_style, 12);                              // 设置背景圆环宽度

                lv_obj_t *preload = lv_spinner_create(masgbox, 1000, 45);

                lv_obj_set_id(preload, obj_id_sd_flsh_swap_preload);

                lv_obj_add_style(preload, &style, LV_PART_INDICATOR); // 应用到圆弧部分；
                lv_obj_add_style(preload, &bc_style, LV_PART_MAIN);   // 应用到背景圆环部分；

                lv_obj_set_size(preload, 100, 100);
                lv_obj_align(preload, LV_ALIGN_TOP_MID, 0, 40);
        }

        lv_sat_timer_create(flash_backup_to_sd_timer, 1000, backup_ed);
}

/************************************************************
** 函数说明: 文件备份到SD卡
** 作者: xiaoxiao
** 日期: 2023-08-09 11:41:51
** 参数说明:
** 注意事项:
************************************************************/
static bool flash_backup_to_sd()
{

        if (access("/dev/mmcblk0", F_OK) == 0)
        {
                if (access(SD_BASE_PATH, F_OK) != 0)
                {
                        system("mkdir " SD_BASE_PATH);
                }
                system("mount /dev/mmcblk0 " SD_BASE_PATH);
        }
        else
        {
                return false;
        }

        if (access(FLASH_MEDIA_BCAKUP_PATH, F_OK) != 0)
        {
                /***** 文件夹不存在 *****/
                system("mkdir " FLASH_MEDIA_BCAKUP_PATH);
                printf("mkdir " FLASH_MEDIA_BCAKUP_PATH "\n");
        }

        static bool backup_ed = false;
        backup_ed = false;

        if (0)
        {
                flash_backup_to_sd_dispaly_create(&backup_ed);
        }

        system("cp -r " FLASH_PHOTO_PATH "* " FLASH_MEDIA_BCAKUP_PATH);

        media_file_delete_all(FILE_TYPE_FLASH_PHOTO, true);

        backup_ed = true;
        return true;
}

static void logo_enter_system_timer(lv_timer_t *t)
{
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-1-5 10:5:6
        ** 说明: 时间初始化
        ***********************************************/
        user_time_init();

        /*
         * @日期: 2022-08-11
         * @作者: leo.liu
         * @注释: 开启文件系统
         */
        media_file_list_init();

        int id = user_data_get()->system_mode & 0x0F;

        if (id == 0x01)
        {
                /*****  tuya api初始化 *****/
                tuya_api_init(TUYA_PID);
        }

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2023-1-5 10:6:36
         ** 说明: GPIO 初始化
         ***********************************************/
        user_gpio_init();

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-1-5 17:17:15
        ** 说明: 网络初始化
        ***********************************************/
        user_network_init();

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-1-5 10:6:36
        ** 说明: linphone 初始化
        ***********************************************/
        user_linphone_init();
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-1-5 10:6:36
        ** 说明: 文件备份
        ***********************************************/
        flash_backup_to_sd();

        //  usleep(3000 * 1000);
        /*判断是否为master*/

        if (id == 0x01)
        {
                /*主机的话，将server ip更新*/
                memset(user_data_get()->mastar_wallpad_ip, 0, sizeof(user_data_get()->mastar_wallpad_ip));

                int timeout = 0;
                do
                {
                        memset(user_data_get()->mastar_wallpad_ip, 0, sizeof(user_data_get()->mastar_wallpad_ip));
                        sat_ip_mac_addres_get("eth0", user_data_get()->mastar_wallpad_ip, NULL, NULL);
                        if (timeout++ > 30)
                        {
                                printf("get local sip server ip fail\n");
                                break;
                        }
                        usleep(100 * 1000);
                } while (user_data_get()->mastar_wallpad_ip[0] == 0);
                system("mkdir /var/lib/asterisk");
                system("/app/asterisk/sbin/safe_asterisk ");
                // system("/app/asterisk/sbin/asterisk -cvvvvvv ");
        }

        /*注册到sip server*/
        lv_timer_ready(lv_timer_create(sip_register_timer, 5000, NULL));

        /**********************************************
         ** 作者: leo.liu
         ** 日期: 2023-1-5 10:6:36
         ** 说明:暂时放在连接wifi
        ***********************************************/
        tuya_event_cmd_register(tuya_event_defalut_handle);
        /************************************************************
        ** 函数说明:警报记录初始化
        ** 作者: xiaoxiao
        ** 日期: 2023-05-05 20:50:03
        ** 参数说明:
        ** 注意事项:
        ************************************************************/
        alarm_list_init();

        /************************************************************
        ** 函数说明: 通话记录列表初始化
        ** 作者: xiaoxiao
        ** 日期: 2023-05-17 10:17:15
        ** 参数说明:
        ** 注意事项:
        ************************************************************/
        call_list_init();

#if 1
        if ((user_data_get()->system_mode & 0x0F) == 0x01)
        {
                wifi_device_conneting();
                if (user_data_get()->wifi_enable)
                {
                        wifi_device_open();
                }
                else
                {
                        wifi_device_close();
                }
        }
        else
        {
                wifi_device_close();
        }
        if ((user_data_get()->system_mode & 0x0F) == 0x01)
        {
                if (user_data_get()->etc.time_automatically)
                {
                        extern bool tuya_api_time_sync(void);
                        tuya_api_time_sync();
                }
        }

#endif
        /***** 设置背光使能亮度 *****/
        backlight_brightness_set(user_data_get()->display.lcd_brigtness <= 0 ? 4 : user_data_get()->display.lcd_brigtness);

        /***** 音频输出初始化 *****/
        audio_output_cmd_register(audio_output_event_default_process);

        standby_timer_init(sat_playout_get(close), user_data_get()->display.screen_off_time * 1000);
        lv_timer_t *standby_timer = lv_timer_create(standby_dection_timer, 1000, NULL);
        lv_timer_ready(standby_timer);

        standby_timer_close();

        buzzer_call_callback_register(buzzer_alarm_trigger_default);

        alarm_sensor_cmd_register(layout_alarm_trigger_default); // 警报回调注册
        user_linphone_call_incoming_received_register(monitor_doorcamera_call_extern_func);
        sd_state_channge_callback_register(sd_state_change_default_callback);

        sync_data_cmd_callback_register(asterisk_server_sync_data_callback);

        if (user_data_get()->is_device_init == false)
        {
                language_id_set(LANGUAGE_ID_ENGLISH);
                sat_layout_goto(power_setting, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
        }
        else
        {

                language_id_set(user_data_get()->etc.language);
                user_data_save();
                /************************************************************
                 ** 函数说明: 待机初始化
                 ** 作者: xiaoxiao
                 ** 日期: 2023-05-19 15:21:05
                 ** 参数说明:
                 ** 注意事项:
                 ************************************************************/
                standby_timer_restart(true);
                if (alarm_trigger_check() == false)
                {
                        sat_layout_goto(home, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
                }
        }
        lv_timer_del(t);
}

/************************************************************
** 函数说明: 序列号提示输入
** 作者: xiaoxiao
** 日期: 2023-05-12 09:39:40
** 参数说明:
** 注意事项:
************************************************************/
static void logo_serial_numbe_txt_create(void)
{
        lv_common_text_create(sat_cur_layout_screen_get(), logo_obj_id_tuya_register_tips, 0, 160, 1024, 100,
                              NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                              "Please enter the serial number", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large);
}

/************************************************************
** 函数说明: 涂鸦id序列号文本区域
** 作者: xiaoxiao
** 日期: 2023-05-12 09:49:16
** 参数说明:
** 注意事项:
************************************************************/
static void layout_logo_input_txt_create(void)
{
        lv_obj_t *ta = lv_common_textarea_create(sat_cur_layout_screen_get(), logo_obj_id_tuya_register_textarea, 60, 60, 904, 54,
                                                 NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0X101010,
                                                 LV_OPA_COVER, 0Xffffff, LV_OPA_COVER, 0Xffffff,
                                                 0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                 0, 1, LV_BORDER_SIDE_BOTTOM, LV_OPA_COVER, 0x323237,
                                                 "", 0Xffffff, 0Xffffff, LV_TEXT_ALIGN_CENTER, lv_font_normal, 8,
                                                 0, 500, 0Xffffff);
        lv_obj_add_state(ta, LV_STATE_FOCUSED);
        lv_obj_set_style_anim_time(ta, 500, LV_STATE_FOCUSED | LV_PART_CURSOR);
}

static void layout_logo_ok_btn_up(lv_obj_t *obj)
{
        static char input_buffer[6] = {0};
        obj = lv_obj_get_child_form_id(lv_scr_act(), logo_obj_id_tuya_register_textarea);
        int pos = lv_textarea_get_cursor_pos(obj);
        if (pos == 0)
        {
                return;
        }
        if ((input_index) == 0)
        {
                memset(input_buffer, 0, sizeof(input_buffer));
                strcpy(input_buffer, lv_textarea_get_text(obj));
                lv_textarea_set_text(obj, "");
                lv_textarea_set_cursor_pos(obj, 0);
                (input_index)++;
        }
        else if ((input_index) == 1)
        {
                if (strcmp(input_buffer, lv_textarea_get_text(obj)) == 0)
                {
                        int index;
                        sscanf(input_buffer, "%d", &index);
                        if (tuya_key_and_key_xls_register(index) == true)
                        {
                                // system("umount /mnt");
                                lv_obj_clean(sat_cur_layout_screen_get());
                                lv_common_img_btn_create(sat_cur_layout_screen_get(), logo_obj_id_logo_img, 0, 0, 1024, 600, // 273, 235, 486, 130,
                                                         NULL, false, LV_OPA_COVER, 0, LV_OPA_TRANSP, 0,
                                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                         resource_ui_src_get("ic_logo.png"), LV_OPA_TRANSP, 0, LV_ALIGN_CENTER);
                                system("rm -rf /app/tuya/tuya_key_backup");
                                lv_sat_timer_create(logo_enter_system_timer, 1000, NULL);
                        }
                }
                else
                {
                        lv_textarea_set_text(obj, "");
                        lv_textarea_set_cursor_pos(obj, 0);
                        (input_index) = 0;
                }
        }
}

/************************************************************
** 函数说明:
** 作者: xiaoxiao
** 日期: 2023-05-12 10:15:00
** 参数说明:
** 注意事项:
************************************************************/
static void logo_num_keyboard_event(lv_event_t *e)
{

        lv_obj_t *obj = lv_event_get_target(e);
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);

        lv_obj_t *ta = lv_obj_get_child_form_id(sat_cur_layout_screen_get(), logo_obj_id_tuya_register_textarea);

        if (id == 11)
        {
                lv_textarea_del_char(ta);
        }
        else if (id == 9)
        {
                layout_logo_ok_btn_up(obj);
        }
        else
        {
                const char *text = lv_btnmatrix_get_btn_text(obj, id);

                if (text != NULL)
                {

                        lv_textarea_add_text(ta, text);
                }
        }
}

/************************************************************
** 函数说明: 序号键盘输入创建
** 作者: xiaoxiao
** 日期: 2023-05-12 10:04:53
** 参数说明:
** 注意事项:
************************************************************/
static void layout_logo_input_keyboard_create(void)
{
        lv_obj_t *kb = lv_common_number_input_keyboard_create(sat_cur_layout_screen_get(), logo_obj_id_tuya_register_number_keyboard_btn, 389, 229, 230, 371,
                                                              logo_num_keyboard_event, LV_OPA_COVER, 0x808080, LV_OPA_COVER, 0x00a8ff,
                                                              360, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                              360, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                                              0XFFFFFF, 0XFFFFFF, LV_TEXT_ALIGN_CENTER, lv_font_large,
                                                              13, 22);
        static const char *btnm_map[] = {
            "1", "2", "3", "\n",
            "4", "5", "6", "\n",
            "7", "8", "9", "\n",
            "OK", "0", " ", "\n", ""};

        lv_btnmatrix_set_map(kb, btnm_map);
}

static void sat_layout_enter(logo)
{
        lv_common_video_mode_enable(false);

        lv_obj_pressed_func = lv_layout_touch_callback;

        if (access("/tmp/tf", F_OK))
        {
                system("mkdir /tmp/tf");
                system("mount -t vfat /dev/mmcblk0 /tmp/tf");
        }
        if (access("/tmp/tf/tuya_key", F_OK) == 0)
        {
                system("mv /app/tuya/tuya_key /app/tuya/tuya_key_backup");
        }
        else if (access("/app/tuya/tuya_key_backup", F_OK) == 0)
        {
                system("mv /app/tuya/tuya_key_backup /app/tuya/tuya_key");
        }
        if (tuya_key_and_uuid_init() == false)
        {
                logo_serial_numbe_txt_create();
                layout_logo_input_txt_create();
                layout_logo_input_keyboard_create();
        }
        else
        {
                lv_common_img_btn_create(sat_cur_layout_screen_get(), logo_obj_id_logo_img, 0, 0, 1024, 600, // 273, 235, 486, 130,
                                         NULL, false, LV_OPA_COVER, 0, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                                         resource_ui_src_get("ic_logo.png"), LV_OPA_TRANSP, 0, LV_ALIGN_CENTER);
                lv_sat_timer_create(logo_enter_system_timer, 1000, NULL);
        }

        lv_common_text_create(sat_cur_layout_screen_get(), logo_obj_id_model_label, 650, 550, 200, 33,
                              NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                              "Model:CIP-70QPT", 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_RIGHT, NULL);

        lv_common_text_create(sat_cur_layout_screen_get(), logo_obj_id_version_label, 863, 550, 135, 33,
                              NULL, LV_OPA_TRANSP, 0, LV_OPA_TRANSP, 0,
                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                              0, 0, LV_BORDER_SIDE_NONE, LV_OPA_TRANSP, 0,
                              SYSTEM_VERSION, 0XFFFFFFFF, 0xFFFFFF, LV_TEXT_ALIGN_RIGHT, NULL);
}

static void sat_layout_quit(logo)
{
}

sat_layout_create(logo);
