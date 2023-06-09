

#ifndef _USER_LINPHONE_H_
#define _USER_LINPHONE_H_
#include <stdlib.h>
#include <stdbool.h>
typedef bool (*user_linphone_func)(char *args);

#define LinphoneCallIncomingReceivedStr "LinphoneCallIncomingReceived"
#define LinphoneCallStreamsRunningStr "LinphoneCallStreamsRunning"
#define LinphoneCallConnectedStr "LinphoneCallConnected"
#define LinphoneCallPasswordErrorStr "LinphoneCallPasswordError"
#define LinphoneCallOnlineQueryStr "LinphoneCallOnlineQuery"
#define LinphoneCallOutgoingInitStr "LinphoneCallOutgoingInit"
#define LinphoneCallEndStr "LinphoneCallEnd"
#define LinphoneCallAnswerStr "LinphoneCallAnswer"

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 9:59:5
** 说明: 初始化user linphone相关
***********************************************/
void user_linphone_init(void);

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 15:21:6
** 说明: 获取组播IP地址
***********************************************/
char *user_linphone_local_multicast_get(void);

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 10:46:3
** 说明: sip incomoning call register
***********************************************/
void user_linphone_call_incoming_received_register(user_linphone_func callback);
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 10:46:3
** 说明: 流建立后的处理函数
***********************************************/
void user_linphone_call_streams_running_receive_register(user_linphone_func callback);
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 10:46:3
** 说明: 同意通话后建立后的处理函数
***********************************************/
void user_linphone_call_streams_connected_receive_register(user_linphone_func callback);
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 10:46:3
** 说明: 密码错误提示
***********************************************/
void user_linphone_call_password_error_register(user_linphone_func callback);
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 10:46:3
** 说明: 呼叫应答成功后
***********************************************/
void user_linphone_call_outgoing_call_register(user_linphone_func callback);
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 10:46:3
** 说明: 通话结束
***********************************************/
void user_linphone_call_end_register(user_linphone_func callback);
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 10:46:3
** 说明: 通话结束
***********************************************/
void user_linphone_call_answer_register(user_linphone_func callback);
#endif
