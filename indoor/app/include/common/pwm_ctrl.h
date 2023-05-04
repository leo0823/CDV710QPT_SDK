#ifndef _PWM_CTRL_H_
#define _PWM_CTRL_H_

#include <stdbool.h>
/***
** 日期: 2022-05-10 09:15 
** 作者: leo.liu
** 函数作用：初始化pwm设备
** 返回参数说明：pwmx:pwm号(比如pwmx = 2 ->pwm2)
**              CH:pwm 通道：一般默认0
***/
bool pwm_init(int pwmx,int ch);


/***
** 日期: 2022-05-10 09:27 
** 作者: leo.liu
** 函数作用：使能/失能pwmd
** 返回参数说明：
***/
bool pwm_enable(int pwmx,int ch,bool en);

/***
** 日期: 2022-05-10 09:30 
** 作者: leo.liu
** 函数作用：pwm 频率设置
** 返回参数说明：
***/
bool pwm_period_set(int pwmx,int ch,int period);
/***
** 日期: 2022-05-10 09:30 
** 作者: leo.liu
** 函数作用：pwm 频率占空比设置
** 返回参数说明：
***/
bool pwm_duty_cycle_set(int pwmx,int ch,int duty_cycle);

#endif