#include "user_gpio.h"
#include "common/gpio_ctrl.h"
#include "common/pwm_ctrl.h"
#include "common/sat_user_common.h"
#include "ssd20x_sarad/ssd20x_sarad.h"
#include "cd4051/cd4051.h"
#include "common/sat_main_event.h"
/***********************************************
** 作者: leo.liu
** 日期: 2022-11-9 10:15:48
** 说明: 功放IO初始化
***********************************************/
#define AMP_GPIO_PIN 12
static void amp_gpio_init(void)
{
        gpio_direction_set(AMP_GPIO_PIN, GPIO_DIR_OUT);
        gpio_level_set(AMP_GPIO_PIN, GPIO_LEVEL_LOW);
}

/***********************************************
** 作者: leo.liu
** 日期: 2022-11-9 10:15:48
** 说明: 功放使能
***********************************************/
void amp_enable_set(bool en)
{
        gpio_level_set(AMP_GPIO_PIN, en ? GPIO_LEVEL_HIGH : GPIO_LEVEL_LOW);
}

#define BL_PWM_NO 0
#define BL_PWM_CH 0
/***
** 日期: 2022-05-10 09:41
** 作者: leo.liu
** 函数作用：背光控制
** 返回参数说明：
***/
bool backlight_enable(bool en)
{
        SAT_DEBUG(" backlight_enable is %d \n",en);
        return pwm_enable(BL_PWM_NO, BL_PWM_CH, en);
}

/***
** 日期: 2022-05-10 09:44
** 作者: leo.liu
** 函数作用：设置背光亮度
** 返回参数说明：
***/
bool backlight_brightness_set(int per)
{
        pwm_period_set(BL_PWM_NO, BL_PWM_CH, 65535);

        return pwm_duty_cycle_set(BL_PWM_NO, BL_PWM_CH, per);
}

/************************************************************
** 函数说明: door1特殊锁控制使能
** 作者: xiaoxiao
** 日期: 2023-05-11 14:36:03
** 参数说明: 
** 注意事项: 
************************************************************/
#define DOOR1_LOCK_1_GPIO_PIN 24
static void door1_lock1_gpio_init(void)
{
        gpio_direction_set(DOOR1_LOCK_1_GPIO_PIN, GPIO_DIR_OUT);
        gpio_level_set(DOOR1_LOCK_1_GPIO_PIN, GPIO_LEVEL_LOW);
}

/************************************************************
** 函数说明: door1特殊锁控制
** 作者: xiaoxiao
** 日期: 2023-05-11 14:37:14
** 参数说明: 
** 注意事项: 
************************************************************/
void door1_lock1_pin_ctrl(bool en)
{
        gpio_level_set(DOOR1_LOCK_1_GPIO_PIN, en ? GPIO_LEVEL_HIGH : GPIO_LEVEL_LOW);
}



/***********************************************
** 作者: leo.liu
** 日期: 2022-11-9 10:15:48
** 说明: 警报使能
***********************************************/
#define ALM_EN_GPIO_PIN 14
static void alarm_enable_gpio_init(void)
{
        gpio_direction_set(ALM_EN_GPIO_PIN, GPIO_DIR_OUT);
        gpio_level_set(ALM_EN_GPIO_PIN, GPIO_LEVEL_LOW);
}
/***********************************************
** 作者: leo.liu
** 日期: 2022-11-9 10:15:48
** 说明: 警报通道控制
***********************************************/
#define AD_CTRL_A_GPIO_PIN 21
#define AD_CTRL_B_GPIO_PIN 20
#define AD_CTRL_C_GPIO_PIN 19
static void ad_ctrl_gpio_init(void)
{
        gpio_direction_set(AD_CTRL_A_GPIO_PIN, GPIO_DIR_OUT);
        gpio_level_set(AD_CTRL_A_GPIO_PIN, GPIO_LEVEL_LOW);

        gpio_direction_set(AD_CTRL_B_GPIO_PIN, GPIO_DIR_OUT);
        gpio_level_set(AD_CTRL_B_GPIO_PIN, GPIO_LEVEL_LOW);

        gpio_direction_set(AD_CTRL_C_GPIO_PIN, GPIO_DIR_OUT);
        gpio_level_set(AD_CTRL_C_GPIO_PIN, GPIO_LEVEL_LOW);
}

static void ad_ctrl_a_gpio_val_set(int val)
{
        gpio_level_set(AD_CTRL_A_GPIO_PIN, val ? GPIO_LEVEL_HIGH : GPIO_LEVEL_LOW);
}
static void ad_ctrl_b_gpio_val_set(int val)
{
        gpio_level_set(AD_CTRL_B_GPIO_PIN, val ? GPIO_LEVEL_HIGH : GPIO_LEVEL_LOW);
}
static void ad_ctrl_c_gpio_val_set(int val)
{
        gpio_level_set(AD_CTRL_C_GPIO_PIN, val ? GPIO_LEVEL_HIGH : GPIO_LEVEL_LOW);
}
static void sarad_enable_func(bool en)
{
        gpio_level_set(ALM_EN_GPIO_PIN, en ? GPIO_LEVEL_LOW : GPIO_LEVEL_HIGH);
}
static float sarad_read_func(void)
{
        return sarad_read(1);
}

/***********************************************
** 作者: leo.liu
** 日期: 2022-11-9 10:15:48
** 说明: gpio任务检测
***********************************************/
static float cd4051_value_group[8] = {0};
const int channel_to_sensor[8] = {5, 6, 7, 4, 0, 3, 1, 2};
float user_sensor_value_get(int ch)
{
        if ((ch < 0) || (ch > 7))
        {
                return 0xFFFFF;
        }
        return cd4051_value_group[ch];
}
/***********************************************
** 作者: leo.liu
** 日期: 2022-11-9 10:15:48
** 说明: gpio任务检测
***********************************************/
static void *user_gpio_detect_task(void *arg)
{
        if (sarad_open() == false)
        {
                SAT_DEBUG("if(sarad_open() == false)");
        }
        cd4051_drive_init(sarad_enable_func, sarad_read_func, ad_ctrl_a_gpio_val_set, ad_ctrl_b_gpio_val_set, ad_ctrl_c_gpio_val_set);
        cd4051_drive_enable_set(true);

        for (int i = 0; i < 8; i++)
        {
                cd4051_value_group[channel_to_sensor[i]] = cd4051_drive_read(i);
        }

        while (1)
        {
                for (int i = 0; i < 8; i++)
                {
                        float value = cd4051_drive_read(i);
                        if (abs(value -  cd4051_value_group[channel_to_sensor[i]]) > 1.0)
                        {
                                cd4051_value_group[channel_to_sensor[i]] = value;
                                SAT_DEBUG(" sensor%d value:%.02f", channel_to_sensor[i], value);
                                sat_msg_send_cmd(MSG_EVENT_CMD_ALARM, channel_to_sensor[i], value * 100);
                        }
                }
                usleep(1000 * 100);
        }
        sarad_close();
        cd4051_drive_enable_set(false);
        return NULL;
}

/***********************************************
** 作者: leo.liu
** 日期: 2022-11-9 10:15:48
** 说明: gpio初始化
***********************************************/
bool user_gpio_init(void)
{
        /***** 初始化背光 *****/
        pwm_init(BL_PWM_NO, BL_PWM_CH);

        backlight_enable(true);

        /* 功放gpio处理 */
        amp_gpio_init();

        /*ad gpio控制处理 */
        ad_ctrl_gpio_init();
        /* 警报使能 */
        alarm_enable_gpio_init();

        /*door1特殊锁初始化*/
        door1_lock1_gpio_init();

        /*开启gpio 任务检测*/
        pthread_t task_id;
        pthread_create(&task_id, sat_pthread_attr_get(), user_gpio_detect_task, NULL);


        return true;
}