
#include "layout_define.h"
#include "ring_common.h"
#include "user_gpio.h"
#define RESOURCE_FILE_PATH_MAX 128

/*
 * @日期: 2022-08-11
 * @作者: leo.liu
 * @功能: 获取唯一的字符串
 * @return:
 */
static char *resource_src_get(const char *path, const char *file, int w, int h, bool alloc)
{
        int file_length = 0;

        if (path != NULL)
        {
                file_length += strlen(path);
        }

        if (file != NULL)
        {
                file_length += strlen(file);
        }

        if (file_length > RESOURCE_FILE_PATH_MAX)
        {

                LV_LOG_ERROR("recource path length too long");
                return NULL;
        }

        int resouce_string_size = file_length + 1 + sizeof(uint32_t) * 2 + 1;

        char *resource_string = NULL;

        if (alloc == false)
        {
                static char string[RESOURCE_FILE_PATH_MAX] = {
                    0};
                resource_string = string;
        }
        else
        {
                resource_string = lv_mem_alloc(resouce_string_size);
        }

        lv_memset_00(resource_string, resouce_string_size);

        if (path != NULL)
        {
                strcpy(resource_string, path);
        }

        if (file != NULL)
        {
                strcat(resource_string, file);
        }

        uint32_t *p_param = (uint32_t *)&resource_string[strlen(resource_string) + 2];

        *p_param = w;
        p_param++;
        *p_param = h;
        return resource_string;
}

/*
 * @日期: 2022-08-11
 * @作者: leo.liu
 * @功能: 获取ui资源的路径
 * @return:
 */
void *resource_ui_src_get(const char *file)
{
        return (void *)resource_src_get(RESOURCE_UI_PATH, file, 0, 0, false);
}

/*
 * @日期: 2022-08-11
 * @作者: leo.liu
 * @功能: 获取背景图片
 * @return:
 */
void *resource_wallpaper_src_get(char *file, uint32_t w, uint32_t h)
{
        return (void *)resource_src_get(RESOURCE_WALLPAPER_PATH, file, w, h, false);
}

/*
 * @日期: 2022-08-12
 * @作者: leo.liu
 * @功能: 文件路径获取
 * @return:
 */
void *file_path_src_get(char *path, const char *file, uint32_t w, uint32_t h)
{
        return (void *)resource_src_get(path, file, w, h, false);
}

/*
 * @日期: 2022-08-11
 * @作者: leo.liu
 * @功能: 释放文件
 * @return:
 */
bool resouce_file_src_free(void *pstr)
{
        if (pstr == NULL)
        {
                return false;
        }

        lv_mem_free(pstr);
        return true;
}

/*
 * @日期: 2022-08-11
 * @作者: leo.liu
 * @功能: 创建一个ui资源文件
 * @return:
 */
void *resource_ui_src_alloc(char *file, uint32_t w, uint32_t h)
{
        return (void *)resource_src_get(RESOURCE_UI_PATH, file, w, h, true);
}

/*
 * @日期: 2022-08-11
 * @作者: leo.liu
 * @功能: 创建一个壁纸资源文件
 * @return:
 */
void *resource_wallpaper_src_alloc(char *file, uint32_t w, uint32_t h)
{
        return (void *)resource_src_get(RESOURCE_WALLPAPER_PATH, file, w, h, true);
}

/***********************************************
** 作者: leo.liu
** 日期: 2022-12-26 16:48:12
** 说明: 控件被按下
***********************************************/
void lv_layout_touch_callback(lv_event_t *e)
{
        standby_timer_restart(false);
        ring_touch_play();
}
/***********************************************
** 作者: leo.liu
** 日期: 2022-12-26 16:48:12
** 说明: 获取编译日期
***********************************************/
bool platform_build_date_get(struct tm *tm)
{
#define MONTH_PER_YEAR 12   // 一年12月
#define YEAR_MONTH_DAY 20   // 年月日缓存大小
#define HOUR_MINUTES_SEC 20 // 时分秒缓存大小

        const char year_month[MONTH_PER_YEAR][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        char compile_date[YEAR_MONTH_DAY] = {0};
        char compile_time[HOUR_MINUTES_SEC] = {0};
        char str_month[4] = {0};

        sprintf(compile_date, "%s", __DATE__); // "Aug 23 2016"
        sprintf(compile_time, "%s", __TIME__); // "10:59:19"

        sscanf(compile_date, "%s %d %d", str_month, &(tm->tm_mday), &(tm->tm_year));
        sscanf(compile_time, "%d:%d:%d", &(tm->tm_hour), &(tm->tm_min), &(tm->tm_sec));

        for (int i = 0; i < MONTH_PER_YEAR; ++i)
        {
                if (strncmp(str_month, year_month[i], 3) == 0)
                {
                        tm->tm_mon = i + 1;
                        return true;
                }
        }
        return false;
}
/***********************************************
** 作者: leo.liu
** 日期: 2022-12-26 16:48:12
** 说明: sip账号获取其IP和房号
***********************************************/
bool sip_user_get_number_and_ip(const char *user, char *ip, char *number)
{
        char user_temp[128] = {0};
        if (user == NULL)
        {
                return false;
        }
        strcpy(user_temp, user);

        char *ptr = strchr(user_temp, '@');
        if (ptr == NULL)
        {
                return false;
        }
        *ptr = 0;
        if (number != NULL)
        {
                strcpy(number, user_temp);
        }

        ptr += 1;
        if (ptr == NULL)
        {
                return false;
        }

        if (ip != NULL)
        {
                strcpy(ip, ptr);
        }
        return true;
}
/***********************************************
** 作者: leo.liu
** 日期: 2022-12-26 16:48:12
** 说明: 音频回调处理函数
***********************************************/
void audio_output_event_default_process(int arg)
{
        SAT_DEBUG("AMP %s", arg ? "enable" : "disable");
        amp_enable_set(arg ? true : false);
}
static int alarm_ch;
/************************************************************
** 函数说明: 获取警报通道
** 作者: xiaoxiao
** 日期: 2023-05-04 17:06:40
** 参数说明: 
** 注意事项: 
************************************************************/
int layout_alarm_alarm_channel_get(void)
{
        return alarm_ch;
}

/************************************************************
** 函数说明: 设置警报通道
** 作者: xiaoxiao
** 日期: 2023-05-04 17:09:12
** 参数说明: 
** 注意事项: 
************************************************************/
void layout_alarm_alarm_channel_set(int ch)
{
        alarm_ch = ch;
}
/************************************************************
** 函数说明: 警报处理函数
** 作者: xiaoxiao
** 日期: 2023-04-28 17:07:39
** 参数说明: 
** 注意事项: 
************************************************************/
void layout_alarm_trigger_default(int arg1,int arg2)
{  

        if(((user_data_get()->alarm.away_alarm_enable == false) && (!(user_data_get()->alarm.away_alarm_enable_list & (0x01 << arg1))))
        && ((user_data_get()->alarm.security_alarm_enable == false) && (!(user_data_get()->alarm.security_alarm_enable_list & (0x01 << arg1))))) 
        {
               
                return;
        }

        if((user_data_get()->alarm.alarm_enable[arg1] == 1  && arg2 > 250) || (user_data_get()->alarm.alarm_enable[arg1] == 2  && arg2 < 100))
        {
                layout_alarm_alarm_channel_set(arg1);
                user_data_get()->alarm.alarm_trigger[arg1]  = true;
                user_data_get()->alarm.emergency_mode = 1;
                user_data_save();
                struct tm tm;
                user_time_read(&tm);
                alarm_list_add(security_emergency,arg1, &tm);
                sat_layout_goto(alarm, LV_SCR_LOAD_ANIM_FADE_IN, SAT_VOID);
        }
}

/************************************************************
** 函数说明: 检测是否需要触发警报
** 作者: xiaoxiao
** 日期: 2023-05-08 09:07:36
** 参数说明: 
** 注意事项: 
************************************************************/
bool alarm_trigger_check(void)
{

        bool alarm_occur = false;

        for(int i =0; i<8; i++)
        {
                if(user_data_get()->alarm.alarm_enable[i] != 0 )
                {
                        if((user_data_get()->alarm.alarm_trigger[i] == true) && (user_data_get()->alarm.alarm_enable[i] != 0))
                        {
                                alarm_occur = true;
                                if(user_data_get()->alarm.alarm_enable[i] == 1)
                                {
                                        sat_msg_send_cmd(MSG_EVENT_CMD_ALARM, i, 0.25 * 100);//发送警报事件
                                }else
                                {
                                        sat_msg_send_cmd(MSG_EVENT_CMD_ALARM, i, 3.0 * 100);//发送警报事件
                                }
                                return true;
                        }
                }
                else
                {
                        user_data_get()->alarm.alarm_trigger[i] = false;
                        user_data_save();
                }                
        }

        return alarm_occur;


}

/***********************************************************************/

bool last_call_new;
/************************************************************
** 函数说明: 设置last_call_log new flag
** 作者: xiaoxiao
** 日期: 2023-05-17 16:11:26
** 参数说明: 
** 注意事项: 
************************************************************/
void layout_last_call_new_flag_set(bool new)
{
        last_call_new = new;
}
/************************************************************
** 函数说明: 获取是否有未查看的通话记录标志
** 作者: xiaoxiao
** 日期: 2023-05-17 16:09:19
** 参数说明: 
** 注意事项: 
************************************************************/
bool layout_last_call_new_flag_get(void)
{
        return last_call_new;
}

/***********************************************************************/
