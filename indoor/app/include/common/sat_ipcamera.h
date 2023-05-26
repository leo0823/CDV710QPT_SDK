#ifndef _SAT_IPCAMERA_H_
#define _SAT_IPCAMERA_H_
#include <stdbool.h>

#define IPCAMERA_NUM_MAX 8
#define IPCAMERA_PROFILE_MAX 8
typedef struct
{
        char profile_token[64];
        char rtsp_url[128];
} ipcamera_rtsp_info;
struct ipcamera_info
{
        char username[64];
        char password[64];
        char ipaddr[32];
        int port;
        ipcamera_rtsp_info rtsp[IPCAMERA_PROFILE_MAX];
        char sip_url[128];
        int profile_token_num;
        char door_name[64];
};
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:获取onvif所有的rtsp流
*****************************************************************/
bool sat_ipcamera_rtsp_url_get(int index);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:搜索onvif所有的rtsp流
*****************************************************************/
bool sat_ipcamera_device_discover_search(bool doorcamera);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:设置账号和密码
*****************************************************************/
bool sat_ipcamera_user_password_set(int index, const char *username, const char *password);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:获取在线的IP
*****************************************************************/
int sat_ipcamera_online_num_get(void);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:获取有效的ipcamera
*****************************************************************/
int sat_ipcamera_valid_num_get(void);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:获取ip
*****************************************************************/
const char *sat_ipcamera_ipaddr_get(int index);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:获取端口
*****************************************************************/
int sat_ipcamera_port_get(int index);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:获取rtsp url
*****************************************************************/
const char *sat_ipcamera_sip_addr_get(int index);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:获取账号
*****************************************************************/
const char *sat_ipcamera_username_get(int index);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:获取密码
*****************************************************************/
const char *sat_ipcamera_password_get(int index);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:获取别名
*****************************************************************/
const char *sat_ipcamera_door_name_get(int index);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:获取rtsp url
*****************************************************************/
const char *sat_ipcamera_rtsp_addr_get(int index, int ch);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:获取token 数目
*****************************************************************/
int sat_ipcamera_profile_token_num_get(int index);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:向doorcamera 注册一个设备
*****************************************************************/
bool sat_ipcamera_device_register(const char *loc_sip_uri, int index, int timeout);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:向doorcamera 注册一个设备
*****************************************************************/
bool sat_ipcamera_device_delete(const char *loc_sip_uri, int index, int timeout);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:设置ipcamera参数
*****************************************************************/
bool sat_ipcamera_initialization_parameters(struct ipcamera_info *device, int total);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:向doorcamera 查询是否在线
*****************************************************************/
bool sat_ipcamera_device_name_get(int index, int timeout);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:向doorcamera 用户名设置
*****************************************************************/
bool sat_ipcamera_device_name_set(const char *name, int index, int timeout);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:向doorcamera 修改密码
*****************************************************************/
bool sat_ipcamera_device_password_set(const char *new_pwd, int index, int timeout);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:获取节点信息
*****************************************************************/
struct ipcamera_info *sat_ipcamera_node_data_get(int index);
#endif