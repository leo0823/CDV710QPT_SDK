#ifndef _LAYOUT_WIFI_INPUT_H_
#define _LAYOUT_WIFI_INPUT_H_

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：设置wifi输入账号
** 返回参数说明：
***/
void wifi_input_user_setting(const char *user);
/************************************************************
** 函数说明: wifi输入模式设置
** 作者: xiaoxiao
** 日期：2023-10-24 21:34:15
** 参数说明: 有一些是免费wifi，不需要输入密码，直接连接
** 注意事项：
************************************************************/
void wifi_input_mode_set(int mode);
#endif
