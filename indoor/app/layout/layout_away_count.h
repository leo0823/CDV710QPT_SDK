#ifndef LAYOUT_AWAY_COUNT
#define LAYOUT_AWAY_COUNT
#include "../share/lvgl-8.3.1/lvgl.h"
typedef struct
{
  lv_timer_t *away_setting_time_countdown_timer;
  lv_timer_t *away_release_time_countdown_timer;
  int away_release_time[7];
  int away_count_sec; // 离家设防生效缓冲时间（在缓冲时间过后，离家设防开始）
} layout_away_count_info;

layout_away_count_info *layout_away_count_data_get(void);

/************************************************************
** 函数说明: 离家模式下的传感器回调事件
** 作者: xiaoxiao
** 日期：2023-11-02 09:33:38
** 参数说明:
** 注意事项：
************************************************************/
void away_mode_alarm_trigger_callback(int arg1, int arg2);
/************************************************************
** 函数说明: 离家模式设防检测任务创建
** 作者: xiaoxiao
** 日期：2023-11-02 18:13:36
** 参数说明:
** 注意事项：
************************************************************/
void away_mode_alarm_trigger_timer_create(void);
#endif