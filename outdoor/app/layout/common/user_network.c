#include "common/user_network.h"
#include "common/sat_main_event.h"
#include "common/sat_user_common.h"
#include "common/user_data.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

#include "common/sat_user_time.h"
#include "common/user_data.h"
#include "common/user_key.h"
#include "common/user_linphone.h"
static void automatic_number_setting_ip(void);
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 16:55:3
** 说明: 所有设备的组播IP
***********************************************/
#define USER_NETWORK_MULTICAST_IP "225.0.0.0"
#define USER_NETWORK_MULTICAST_PORT 50023
#define USER_NETWORK_TCP_SYNC_SERVER_PORT 50030
#define USER_NETWORK_TCP_SYNC_SLAVE_PORT 50031
#define USER_NETWORK_TCP_ASYNC_PORT 50032

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 17:35:22
** 说明: 所有网络命令
***********************************************/
#define NETWORK_CMD_DEVICE_INFO "device_info"
#define NETWORK_CMD_DEVICE_BY_NUMBER "device_by_number"
typedef bool (*user_network_func)(char *args, struct sockaddr_in *client_addr);

typedef struct
{

        char *cmd;
        user_network_func func;
        char *help;
} user_network_func_s;

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 16:53:57
** 说明: 组播套接字
***********************************************/
static int user_linphone_multicast_fd = -1;
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 17:48:30
** 说明: 设备信息查询
***********************************************/
static void string_space_cur_and_next_ptr_get(char *sting, char **first_string, char **second_string)
{
        *first_string = NULL;
        *second_string = NULL;

        char *ptr = (char *)sting;
        while (*ptr && isspace(*ptr))
        {
                ++ptr;
        }
        if (*ptr)
        {
                *first_string = ptr;
                while (*ptr && !isspace(*ptr))
                {
                        ++ptr;
                }
                if (*ptr)
                {
                        *ptr = '\0';

                        *second_string = ptr + 1;
                }
        }
}
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 17:48:30
** 说明: 设备信息查询
***********************************************/
static bool network_cmd_device_info_func(char *info, struct sockaddr_in *client_addr)
{
        // ex info:010001001011
        char *str_user = NULL;
        char *str_port = NULL;
        char *str_device_type = NULL;
        char *str_force = NULL;
        SAT_DEBUG(" %s ", info);
        string_space_cur_and_next_ptr_get(info, &str_user, &str_device_type);
        string_space_cur_and_next_ptr_get(str_device_type, &str_device_type, &str_port);
        string_space_cur_and_next_ptr_get(str_port, &str_port, &str_force);

        if ((str_device_type == NULL) || (str_user == NULL) || (str_port == NULL) || (str_force == NULL))
        {
                SAT_DEBUG(" %s %s", NETWORK_CMD_DEVICE_INFO, info);
        }

        int device = atoi(str_device_type);
        if ((device & 0x02) == 0)
        {
                SAT_DEBUG(" %s %s error", NETWORK_CMD_DEVICE_INFO, info);
                return true;
        }

        if (strlen(info) != 12)
        {

                SAT_DEBUG(" %s %s error", NETWORK_CMD_DEVICE_INFO, info);
                return false;
        }

        // SAT_DEBUG("receive:[%s %s]", NETWORK_CMD_DEVICE_INFO, info);

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-1-9 15:23:52
        ** 说明: 判断是否与本机相关
        ***********************************************/
        if (str_force[0] == '0')
        {
                const char *username = getenv("SIP");
                int loacal_number[4] = {
                    0};
                int client_number[4] = {
                    0};
                loacal_number[0] = (username[0] - 48) * 100 + (username[1] - 48) * 10 + (username[2] - 48);
                loacal_number[1] = ((username[3] - 48) * 100 + (username[4] - 48) * 10 + (username[5] - 48)) & 0x1F;
                loacal_number[2] = (username[6] - 48) * 100 + (username[7] - 48) * 10 + (username[8] - 48);
                loacal_number[3] = (username[9] - 48) * 100 + (username[10] - 48) * 10;

                client_number[0] = (info[0] - 48) * 100 + (info[1] - 48) * 10 + (info[2] - 48);
                client_number[1] = ((info[3] - 48) * 100 + (info[4] - 48) * 10 + (info[5] - 48)) & 0x1F;
                client_number[2] = (info[6] - 48) * 100 + (info[7] - 48) * 10 + (info[8] - 48);
                client_number[3] = (info[9] - 48) * 100 + (info[10] - 48) * 10;

                if (memcmp(loacal_number, client_number, sizeof(loacal_number)))
                {
                        return false;
                }
        }
        else if (user_key_state_get() != KEY_STATE_LONG_DOWN)
        {
                /***********************************************
                 ** 作者: leo.liu
                 ** 日期: 2023-1-9 15:37:38
                 ** 说明:如果是强制的话，需要门铃按下为长
                 按状态
                 ***********************************************/
                SAT_DEBUG("The key is not in a long press state ");
                return false;
        }

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-1-9 15:37:38
        ** 说明: 建立连接
        ***********************************************/
        {
                int socket_fd = -1;
                int port = 0;

                sscanf(str_port, "%d", &port);

                if (sat_socket_tcp_open(&socket_fd, port, 0) == false)
                {

                        SAT_DEBUG(" tcp open failed ");
                        return false;
                }

                char server_ip[32] = {
                    0};
                memset(server_ip, 0, sizeof(server_ip));
                strcpy(server_ip, inet_ntoa(client_addr->sin_addr));

                if (sat_socket_tcp_connect(socket_fd, server_ip, port, 1000) == false)
                {

                        sat_socket_close(socket_fd);
                        SAT_DEBUG(" connect timeout ");
                        return false;
                }

                network_device_info device_info;
                memset(device_info.number, 0, sizeof(device_info.number));
                strcpy(device_info.name, user_data_get()->device.name);
                // strcpy(device.password, user_data_get()->device_password);
                if (sat_sip_local_user_get(device_info.number) == false)
                {
                        sat_socket_close(socket_fd);
                        SAT_DEBUG(" sip user get failed ");
                        return false;
                }

                SAT_DEBUG(" send(%s)	", device_info.name);
                if (sat_socket_tcp_send(socket_fd, (unsigned char *)&device_info, sizeof(network_device_info), 500) == false)
                {

                        sat_socket_close(socket_fd);
                        SAT_DEBUG(" send(%s) failed ", device_info.name);
                        return false;
                }

                sat_socket_close(socket_fd);
        }
        return true;
}

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 10:13:8
** 说明: 依据房号查询设备的账号信息ip port number
***********************************************/
static bool network_cmd_device_by_number_func(char *info, struct sockaddr_in *client_addr)
{
        char *str_ip = NULL;
        char *str_port = NULL;
        char *str_number = NULL;
        string_space_cur_and_next_ptr_get(info, &str_ip, &str_port);
        string_space_cur_and_next_ptr_get(str_port, &str_port, &str_number);
        if ((str_number == NULL) || (str_port == NULL) || (str_number == NULL))
        {
                SAT_DEBUG("%s %s error", NETWORK_CMD_DEVICE_INFO, info);
                return false;
        }

        if (user_data_get()->register_device_count < 1)
        {
                SAT_DEBUG("register device is 0");
                return false;
        }

        char username[128] = {0};
        if (sat_sip_local_user_get(username) == false)
        {
                return false;
        }

        if (strncmp(str_number, username, 12))
        {
                return true;
        }

        int socket_fd = -1;
        int port = 0;

        sscanf(str_port, "%d", &port);
        if (sat_socket_tcp_open(&socket_fd, port, 0) == false)
        {
                SAT_DEBUG("tcp open failed ");
                return false;
        }

        if (sat_socket_tcp_connect(socket_fd, str_ip, port, 1000) == false)
        {
                sat_socket_close(socket_fd);
                SAT_DEBUG("connect timeout ");
                return false;
        }

        network_device_info device_info;
        memset(device_info.number, 0, sizeof(device_info.number));
        strcpy(device_info.number, username);
        memset(device_info.name, 0, sizeof(device_info.name));
        strcpy(device_info.name, user_data_get()->device.name);
        if (sat_socket_tcp_send(socket_fd, (unsigned char *)&device_info, sizeof(network_device_info), 500) == false)
        {

                sat_socket_close(socket_fd);
                SAT_DEBUG("send(%s) failed ", device_info.number);
                return false;
        }

        sat_socket_close(socket_fd);
        return true;
}
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 10:13:8
** 说明: 用户呼入处理
***********************************************/
static user_network_func_s user_network_multicast_func_array[] =
    {
        {NETWORK_CMD_DEVICE_INFO,
         network_cmd_device_info_func,
         "device_info user port force"},

        {NETWORK_CMD_DEVICE_BY_NUMBER,
         network_cmd_device_by_number_func,
         "device_by_number server_ip port number"},

};

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 17:37:3
** 说明：网络事件处理
***********************************************/
static void user_network_multicast_event_func(char *info, struct sockaddr_in *client_addr)
{
        char *ptr = NULL;
        char *args = NULL;

        string_space_cur_and_next_ptr_get(info, &ptr, &args);
        if ((ptr == NULL) || (args == NULL))
        {
                return;
        }

        int n_func = sizeof(user_network_multicast_func_array) / sizeof(user_network_func_s);

        for (int i = 0; i < n_func; i++)
        {

                if (strcmp(user_network_multicast_func_array[i].cmd, (char *)ptr) == 0)
                {

                        if (user_network_multicast_func_array[i].func != NULL)
                        {

                                user_network_multicast_func_array[i].func(args, client_addr);
                        }

                        break;
                }
        }
}

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-10 8:16:51
** 说明: 判断是否属于同一帧
***********************************************/
static bool user_network_frame_check(char *buffer, int len, struct sockaddr_in *sock_addr)
{

        static char receive_buffer_addr[256] = {
            0};
        static int receive_buffer_len = 0;

        static struct sockaddr_in server_addr;
        static unsigned long long receive_buffer_timestamp = 0;

        unsigned long long timestamp = user_timestamp_get();

        if (((timestamp - receive_buffer_timestamp) > 100) || (len != receive_buffer_len) || (strcmp(buffer, receive_buffer_addr)) || (memcmp(sock_addr, &server_addr, sizeof(struct sockaddr_in))))
        {

                receive_buffer_len = len;
                memset(receive_buffer_addr, 0, sizeof(receive_buffer_addr));
                strcpy(receive_buffer_addr, buffer);
                server_addr = *sock_addr;
                receive_buffer_timestamp = timestamp;
                return true;
        }

        return false;
}

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 17:26:43
** 说明: 用户网络任务
***********************************************/
static void *user_network_task(void *arg)
{
        int recv_len = 0;
        char buffer[256] = {
            0};
        struct sockaddr_in client_addr;
        sat_socket_udp_open(&user_linphone_multicast_fd, USER_NETWORK_MULTICAST_PORT, false);

        sat_socket_multicast_join(user_linphone_multicast_fd, USER_NETWORK_MULTICAST_IP);

        while (1)
        {

                memset(buffer, 0, sizeof(buffer));
                memset(&client_addr, 0, sizeof(struct sockaddr_in));
                recv_len = sat_socket_udp_receive(user_linphone_multicast_fd, buffer, sizeof(buffer), &client_addr, 1000);

                if (recv_len > 0)
                {

                        if (user_network_frame_check(buffer, recv_len, &client_addr) == true)
                        {

                                user_network_multicast_event_func(buffer, &client_addr);
                        }
                }
        }

        return NULL;
}
/*********************************************** 		tcp   		***********************************************/

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 10:13:8
** 说明: 用户呼入处理
***********************************************/

typedef bool (*user_network_tcp_func)(int client_fd, char *args, struct sockaddr_in *client_addr);
typedef struct
{

        char *cmd;
        user_network_tcp_func func;
        char *help;
} user_network_tcp_func_s;

#define NETWORK_CMD_DEVICE_ONLINE "device_online"
#define NETWORK_CMD_DOOR_CAMERA_DEVICE_REGISTER "door_camera_device_register"
#define NETWORK_CMD_DEVICE_VERSION "device_version"
#define NETWORK_CMD_DEVICE_PASSWORD "device_password"
#define NETWORK_CMD_DEVICE_NAME "device_name"
#define NETWORK_CMD_DEVICE_DELETE "device_delete"

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-10 8:16:51
** 说明:查询ip是否在线
***********************************************/
static bool network_cmd_device_online_func(int client_fd, char *info, struct sockaddr_in *client_addr)
{
        char *str_number = NULL;
        char *str_ip = NULL;
        string_space_cur_and_next_ptr_get(info, &str_number, &str_ip);
        if ((str_number == NULL) /*|| (str_ip == NULL)*/)
        {
                SAT_DEBUG("str_number failed:%s", info);
                return false;
        }

        for (int i = 0; i < user_data_get()->register_device_count; i++)
        {
                if (strncmp(str_number, user_data_get()->register_device[i], 12) == 0)
                {
                        network_device_info device_info;
                        memset(device_info.number, 0, sizeof(device_info.number));
                        strcpy(device_info.name, user_data_get()->device.name);
                        // strcpy(device.password, user_data_get()->device_password);
                        if (sat_sip_local_user_get(device_info.number) == false)
                        {
                                SAT_DEBUG(" sip user get failed ");
                                return false;
                        }

                        if (sat_socket_tcp_send(client_fd, (unsigned char *)&device_info, sizeof(device_info), 500) == false)
                        {
                                SAT_DEBUG(" send(%s) failed ", info);
                                return false;
                        }
                        SAT_DEBUG("online %s", info);
                        return true;
                }
        }
        SAT_DEBUG("offline %s", info);
        return false;
}
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-10 8:16:51
** 说明:修改账号与IP
***********************************************/
static bool network_cmd_door_camera_device_register_func(int client_fd, char *info, struct sockaddr_in *client_addr)
{
        char *str_number = NULL;
        char *str_register_number = NULL;
        char *str_force = NULL;
        SAT_DEBUG(" info = %s", info);
        string_space_cur_and_next_ptr_get(info, &str_register_number, &str_number);
        string_space_cur_and_next_ptr_get(str_number, &str_number, &str_force);
        SAT_DEBUG(" str_number =%s register:%s force:%s", str_number, str_register_number, str_force);

        if ((str_number == NULL) || (str_register_number == NULL) || (str_force == NULL))
        {
                SAT_DEBUG(" number or ip is null");
                sat_socket_tcp_send(client_fd, (unsigned char *)"password error", strlen("password error") + 1, 500);
                return false;
        }

        if ((strlen(str_number) != 12) /*|| (strlen(str_register_number) != 12)*/)
        {
                SAT_DEBUG(" str_number(%d) != 12 ", strlen(str_number));
                sat_socket_tcp_send(client_fd, (unsigned char *)"password error", strlen("password error") + 1, 500);
                return false;
        }
        int value = (str_number[3] - 48) * 100 + (str_number[4] - 48) * 10 + (str_number[5] - 48);
        if ((value & 0xE0) != 0xC0)
        {
                SAT_DEBUG(" value(%02X) & 0xE0) != 0xC0 ", value & 0xE0);
                sat_socket_tcp_send(client_fd, (unsigned char *)"password error", strlen("password error") + 1, 500);
                return false;
        }

        if (sat_socket_tcp_send(client_fd, (unsigned char *)"input password", strlen("input password") + 1, 500) == false)
        {
                SAT_DEBUG(" send(%s) failed ", info);
                return false;
        }

        unsigned char buffer[16] = {0};
        if (sat_socket_tcp_receive(client_fd, buffer, sizeof(buffer) - 1, 500) == false)
        {
                SAT_DEBUG(" recv(%s) failed ", info);
                return false;
        }
        if (strcmp(user_data_get()->device.password, (char *)buffer))
        {
                SAT_DEBUG(" password error %s###########%s ", user_data_get()->device.password, buffer);
                sat_socket_tcp_send(client_fd, (unsigned char *)"password error", strlen("password error") + 1, 500);
                return false;
        }

        if (user_data_get()->register_device_count >= DEVICE_MAX)
        {
                int j = 0;
                for (j = 1; j < (user_data_get()->register_device_count - 1); j++)
                {
                        memcpy(user_data_get()->register_device[j], user_data_get()->register_device[j + 1], sizeof(user_data_get()->register_device[j]));
                }
                memset(&(user_data_get()->register_device[j]), 0, sizeof(user_data_get()->register_device[j]));
                user_data_get()->register_device_count--;
                user_data_save();
                //    sat_socket_tcp_send(client_fd, (unsigned char *)"register device max", strlen("register device max") + 1, 500);
                // return false;
        }

        if (sat_socket_tcp_send(client_fd, (unsigned char *)"register success", strlen("register success") + 1, 500) == false)
        {
                SAT_DEBUG(" send(%s) failed ", info);
                return false;
        }

        // 010129001011
        char loc_ip[64] = {0};
        char send_number[128] = {0};
        sat_ip_mac_addres_get("eth0", loc_ip, NULL);
        if ((str_force[0] == '0') && (strncmp(str_number, user_data_get()->device.number, 11) == 0))
        {
                sprintf(send_number, "%s@%s", user_data_get()->device.number, loc_ip);
                if (sat_socket_tcp_send(client_fd, (unsigned char *)send_number, strlen(send_number) + 1, 500) == false)
                {
                        SAT_DEBUG(" send(%s) failed ", info);
                        return false;
                }
                for (int i = 0; i < user_data_get()->register_device_count; i++)
                {
                        if (strncmp(user_data_get()->register_device[i], str_register_number, 12) == 0)
                        {
                                SAT_DEBUG(" multiple registration(%s:%s)", str_register_number, send_number);
                                return true;
                        }
                }
                strncpy(user_data_get()->register_device[user_data_get()->register_device_count++], str_register_number, sizeof(user_data_get()->register_device[0]));
                user_data_save();
                SAT_DEBUG(" modiy :register:indoor %s outdoor:%s", str_register_number, send_number);
        }
        else
        {
                sprintf(send_number, "%s@%s", str_number, loc_ip);
                if (sat_socket_tcp_send(client_fd, (unsigned char *)send_number, strlen(send_number) + 1, 500) == false)
                {
                        SAT_DEBUG(" send(%s) failed ", info);
                        return false;
                }

                user_data_get()->register_device_count = 0;
                memset(user_data_get()->register_device, 0, sizeof(user_data_get()->register_device));
                strcpy(user_data_get()->device.number, str_number);
                strcpy(user_data_get()->register_device[user_data_get()->register_device_count++], str_register_number);

                /*修改默认IP和mask*/
                automatic_number_setting_ip();

                user_data_save();

                sat_socket_close(client_fd);

                SAT_DEBUG(" channge:register:indoor %s outdoor:%s", str_register_number, send_number);
                usleep(1000 * 1000);
                system("reboot");
        }

        return true;
}
static bool network_cmd_device_version_func(int client_fd, char *info, struct sockaddr_in *client_addr)
{
        char *str_number = NULL;
        char *str_ip = NULL;
        string_space_cur_and_next_ptr_get(info, &str_number, &str_ip);
        if ((str_number == NULL) /* || (str_ip == NULL) */)
        {
                SAT_DEBUG(" number or ip is null");
                return false;
        }
        if (user_data_get()->register_device_count < 1)
        {
                SAT_DEBUG("register device is 0");
                return false;
        }

        if (strlen(str_number) != 12)
        {
                SAT_DEBUG(" str_number(%d) != 12 ", strlen(str_number));
                return false;
        }
        int value = (str_number[3] - 48) * 100 + (str_number[4] - 48) * 10 + (str_number[5] - 48);
        if ((value & 0xE0) != 0xC0)
        {
                SAT_DEBUG(" value(%02X) & 0xE0) != 0xC0 ", value & 0xE0);
                return false;
        }

        struct tm tm;
        if (platform_build_date_get(&tm) == true)
        {
                char buffer[128] = {0};
                sprintf(buffer, "build time:%04d-%02d-%02d %02d:%02d:%02d", tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
                if (sat_socket_tcp_send(client_fd, (unsigned char *)buffer, strlen(buffer) + 1, 500) == false)
                {
                        SAT_DEBUG(" send(%s) failed ", info);
                        return false;
                }
                SAT_DEBUG("%s", buffer);
                return true;
        }
        return false;
}
// 旧密码验证成功，返回新密码，
// 旧密码验证失败，返回旧密码
static bool network_cmd_device_password_func(int client_fd, char *info, struct sockaddr_in *client_addr)
{ //"device_password A(p1)AAAAAAAAoldA(p2)AAAAAAAAnewA(p3)AAAAAAAA"

        if (user_data_get()->register_device_count < 1)
        {
                SAT_DEBUG("register device is 0");
                return false;
        }

        bool check_password = true;
        char *p1 = strstr(info, "AAAAAAAAA");
        char *p2 = strstr(p1 + 9, "AAAAAAAAA");
        char *p3 = strstr(p2 + 9, "AAAAAAAAA");
        if ((((p2 - p1) != 18) || (strncmp(user_data_get()->device.password, p1 + 9, 9) != 0)) || ((p3 - p2) != 18))
        {
                check_password = false;
        }

        if (check_password == true)
        {
                memset(user_data_get()->device.password, 0, sizeof(user_data_get()->device.password));
                memcpy(user_data_get()->device.password, p2 + 9, 9);
                user_data_save();

                if (sat_socket_tcp_send(client_fd, (unsigned char *)(p2 + 9), 9, 500) == false)
                {
                        SAT_DEBUG(" send(%s) failed ", info);
                        return false;
                }
                return true;
        }
        if (strncmp(user_data_get()->device.password, p1 + 9, 9) == 0)
        {
                if (sat_socket_tcp_send(client_fd, (unsigned char *)(p1 + 9), 9, 500) == false)
                {
                        SAT_DEBUG(" send(%s) failed ", info);
                        return false;
                }
        }
        SAT_DEBUG("%s", info);
        return true;
}

static bool network_cmd_device_name_func(int client_fd, char *info, struct sockaddr_in *client_addr)
{ //"device_password A(p1)AAAAAAAApwdA(p2)AAAAAAAAregister(p3)AAAAAAAA"

        SAT_DEBUG("%s", info);
        if (user_data_get()->register_device_count < 1)
        {
                SAT_DEBUG("register device is 0");
                return false;
        }
        char *p1 = strstr(info, "AAAAAAAAA");
        char *p2 = strstr(p1 + 9, "AAAAAAAAA");
        char *p3 = strstr(p2 + 9, "AAAAAAAAA");
        if (((p2 - p1) != 18) || (strncmp(user_data_get()->device.password, p1 + 9, 9) != 0) || ((p3 - p2) != 21))
        {
                SAT_DEBUG("password faield:%s-%d", p1 + 9, p3 - p2);
                return false;
        }

        for (int i = 0; i < user_data_get()->register_device_count; i++)
        {
                SAT_DEBUG("%s->%s", user_data_get()->register_device[i], p2 + 9);
                if (strncmp(user_data_get()->register_device[i], p2 + 9, 12) == 0)
                {
                        memset(user_data_get()->device.name, 0, sizeof(user_data_get()->device.name));
                        strcpy(user_data_get()->device.name, p3 + 9);
                        user_data_save();

                        if (sat_socket_tcp_send(client_fd, (unsigned char *)(user_data_get()->device.name), strlen(user_data_get()->device.name) + 1, 500) == false)
                        {
                                SAT_DEBUG(" send(%s) failed ", info);
                                return false;
                        }
                        SAT_DEBUG("username modiy success");
                        return true;
                }
        }
        SAT_DEBUG("username modiy failed");
        return false;
}

static bool network_cmd_device_delete_func(int client_fd, char *info, struct sockaddr_in *client_addr)
{ //"device_password A(p1)AAAAAAAApassowrdA(p2)AAAAAAAAoutdoor_userAAAAAAAAAindoor user"

        char *p1 = strstr(info, "AAAAAAAAA");
        char *p2 = strstr(p1 + 9, "AAAAAAAAA");
        char *p3 = strstr(p2 + 9, "AAAAAAAAA");
        if ((((p2 - p1) == 18) && (strncmp(user_data_get()->device.password, p1 + 9, 9) != 0)))
        {
                SAT_DEBUG("password error:%s->%s", p1, user_data_get()->device.password);
                return false;
        }

        if (strncmp(user_data_get()->device.number, p2 + 9, 12) != 0)
        {
                SAT_DEBUG("device number error:%s->%s", p2, user_data_get()->device.number);
                return false;
        }

        if (user_data_get()->register_device_count < 1)
        {
                SAT_DEBUG("register device is 0");
                return false;
        }
        for (int i = 0; i < user_data_get()->register_device_count; i++)
        {
                //  SAT_DEBUG("register:%s,del:%s",user_data_get()->register_device[i],p3+9);
                if (strncmp(user_data_get()->register_device[i], p3 + 9, 12) == 0)
                {
                        int j = 0;
                        for (j = i; j < (user_data_get()->register_device_count - 1); j++)
                        {
                                memcpy(user_data_get()->register_device[j], user_data_get()->register_device[j + 1], sizeof(user_data_get()->register_device[j]));
                        }

                        memset(&(user_data_get()->register_device[j]), 0, sizeof(user_data_get()->register_device[j]));

                        user_data_get()->register_device_count--;
                        user_data_save();

                        /*发送对应的号码*/
                        char username[128] = {0};
                        sat_sip_local_user_get(username);
                        if (sat_socket_tcp_send(client_fd, (unsigned char *)username, sizeof(username), 500) == false)
                        {
                                SAT_DEBUG(" send(%s) failed ", info);
                                return false;
                        }
                        break;
                }
        }

        for (int i = 0; i < user_data_get()->register_device_count; i++)
        {
                SAT_DEBUG("%d:%s", i, user_data_get()->register_device[i]);
        }
        return true;
}
static user_network_tcp_func_s user_network_tcp_func_array[] =
    {
        {NETWORK_CMD_DEVICE_ONLINE,
         network_cmd_device_online_func,
         "device_online number ip"},

        {NETWORK_CMD_DOOR_CAMERA_DEVICE_REGISTER,
         network_cmd_door_camera_device_register_func,
         "device_regigter register_number modiy_outdoor_number force"},

        {NETWORK_CMD_DEVICE_VERSION,
         network_cmd_device_version_func,
         "device_version number ip"},

        {NETWORK_CMD_DEVICE_PASSWORD,
         network_cmd_device_password_func,
         "device_password AAAAAAAAAoldAAAAAAAAAnewAAAAAAAAA"},

        {NETWORK_CMD_DEVICE_NAME,
         network_cmd_device_name_func,
         "device_name AAAAAAAAApwdAAAAAAAAAregisternameAAAAAAAAAnewname"},

        {NETWORK_CMD_DEVICE_DELETE,
         network_cmd_device_delete_func,
         "device_delete AAAAAAAAApasswordAAAAAAAAAuser"},
};

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 17:37:3
** 说明：网络事件处理
***********************************************/
static void user_network_tcp_event_func(int socket_fd, char *info, struct sockaddr_in *client_addr)
{
        char *ptr = NULL;
        char *args = NULL;

        string_space_cur_and_next_ptr_get(info, &ptr, &args);
        if ((ptr == NULL) || (args == NULL))
        {
                return;
        }

        int n_func = sizeof(user_network_tcp_func_array) / sizeof(user_network_func_s);

        for (int i = 0; i < n_func; i++)
        {

                if (strcmp(user_network_tcp_func_array[i].cmd, (char *)ptr) == 0)
                {

                        if (user_network_tcp_func_array[i].func != NULL)
                        {

                                user_network_tcp_func_array[i].func(socket_fd, args, client_addr);
                        }

                        break;
                }
        }
}
static void *user_network_tcp_task(void *arg)
{
#define TCP_RECEIVE_PACKET_MAX (1024)
        int server_fd = -1;
        struct sockaddr_in client_addr;
        unsigned char *receive_data = (unsigned char *)malloc(TCP_RECEIVE_PACKET_MAX);

        sat_socket_tcp_open(&server_fd, USER_NETWORK_TCP_SYNC_SERVER_PORT, DEVICE_MAX);
        while (1)
        {
                memset(&client_addr, 0, sizeof(struct sockaddr_in));
                int client_fd = sat_socket_tcp_accept(server_fd, &client_addr, 500);
                if (client_fd >= 0)
                {
                        int recv_len = 0;
                        while ((recv_len = sat_socket_tcp_receive(client_fd, receive_data, TCP_RECEIVE_PACKET_MAX, 100)) > 0)
                        {
                                user_network_tcp_event_func(client_fd, (char *)receive_data, &client_addr);
                        }
                        sat_socket_close(client_fd);
                }
        }
        return NULL;
}

/***********************************************
 ** 作者: leo.liu
** 日期: 2022-12-9 13:53:54
** 说明: 先开启udhcpc获取IP,失败后通过保存的设置IP，
如果没有IP，通过设置的房号默认分配IP
***********************************************/
static void automatic_number_setting_ip(void)
{
        // 010193001012
        int buffer[4] = {0};
        char ip[32] = {0};
        memset(buffer, 0, sizeof(buffer));
        char *username = user_data_get()->device.number;

        buffer[0] = (username[0] - 48) * 100 + (username[1] - 48) * 10 + (username[2] - 48);
        buffer[1] = ((username[3] - 48) * 100 + (username[4] - 48) * 10 + (username[5] - 48));
        buffer[2] = (username[6] - 48) * 100 + (username[7] - 48) * 10 + (username[8] - 48);
        buffer[3] = (username[9] - 48) * 100 + (username[10] - 48) * 10 + (username[11] - 48);

        sprintf(ip, "%d.%d.%d.%d", buffer[0], buffer[1], buffer[2], buffer[3]);

        memset(user_data_get()->network.ip, 0, sizeof(user_data_get()->network.ip));
        strcpy(user_data_get()->network.ip, ip);

        memset(user_data_get()->network.mask, 0, sizeof(user_data_get()->network.mask));
        strcpy(user_data_get()->network.mask, "255.0.0.0");

        SAT_DEBUG("defalut ip:%s,mask:%s", user_data_get()->network.ip, user_data_get()->network.mask);
}

#define UDHCPC_TIMEOUT_MAX (300)
static bool automatic_ip_setting(void)
{
        /* 在开机脚本已经做了udhcpc后台运行，此处检测3sec，如果没有获取到IP，将执行下一步动作*/

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2022-12-9 13:53:54
         ** 说明: 步骤一
         ***********************************************/
        {
                int count = 0;
                char ip[32] = {0};
                char mac[128] = {0};
                while (sat_ip_mac_addres_get("eth0", ip, mac) == false)
                {
                        usleep(10 * 1000);
                        count++;
                        if (count > UDHCPC_TIMEOUT_MAX)
                        {
                                SAT_DEBUG("udhcpc get ip timeout");
                                break;
                        }
                }
                if (count < UDHCPC_TIMEOUT_MAX)
                {
                        if (strcmp(ip, "10.0.0.2"))
                        {
                                SAT_DEBUG("udhcp ip get successs ! ");
                                return true;
                        }
                }
        }

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2022-12-9 13:53:54
         ** 说明: 步骤二
         ***********************************************/
        system("killall udhcpc");

        char cmd[128] = {0};
        sprintf(cmd, "ifconfig eth0 %s netmask %s", user_data_get()->network.ip, user_data_get()->network.mask[0] != 0 ? user_data_get()->network.mask : "255.0.0.0");
        system(cmd);
        SAT_DEBUG("%s ", cmd);
        memset(cmd, 0, sizeof(cmd));
        sprintf(cmd, "route add -net %s netmask %s eth0", "225.0.0.0", "255.0.0.0");
        system(cmd);
        SAT_DEBUG("%s ", cmd);

        /*升级组播路由*/
        memset(cmd, 0, sizeof(cmd));
        sprintf(cmd, "route add -net %s netmask %s eth0", "224.0.0.0", "255.0.0.0");
        system(cmd);
        SAT_DEBUG("%s ", cmd);
        return true;

        /***********************************************
         ** 作者: leo.liu
         ** 日期: 2022-12-9 13:53:54
         ** 说明: 步骤三
         ***********************************************/
        //    automatic_number_setting_ip();
        return true;
}

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 17:13:48
** 说明: 用户网络处理
***********************************************/
void user_network_init(void)
{
        pthread_t thread_id;

        automatic_ip_setting();

        pthread_create(&thread_id, sat_pthread_attr_get(), user_network_task, NULL);

        pthread_create(&thread_id, sat_pthread_attr_get(), user_network_tcp_task, NULL);
}

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 15:21:6
** 说明: 获取组播IP地址
***********************************************/
char *user_linphone_local_multicast_get(void)
{
        // ex:户外机:"010129001011" -->>> 225.1.1.10
        // ex:室内机:"010001001011" -->>> 225.1.1.10
        int value[4] = {

            0};
        static char multicase_ip[32] = {
            0};
        const char *username = getenv("SIP");

        if ((username == NULL) || (strlen(username) < 12))
        {

                SAT_DEBUG("getenv sip failed ");
                return NULL;
        }

        memset(multicase_ip, 0, sizeof(multicase_ip));

        value[0] = 225;
        value[1] = ((username[3] - 48) * 100 + (username[4] - 48) * 10 + (username[5] - 48)) & 0x1F;
        value[2] = (username[6] - 48) * 100 + (username[7] - 48) * 10 + (username[8] - 48);
        value[3] = (username[9] - 48) * 100 + (username[10] - 48) * 10;
        sprintf(multicase_ip, "%d.%d.%d.%d", value[0], value[1], value[2], value[3]);

        SAT_DEBUG("sip:%s,multicase ip:%s", username, multicase_ip);
        return multicase_ip;
}

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 17:52:32
** 说明: 查询设备信息
***********************************************/
static bool user_network_multicast_cmd_send(unsigned char *cmd, size_t len, network_device_info *device_info, int device_max, int *receive_count, bool force)
{
        bool reslut = false;
        int server_fd = -1;
        int client_fd = -1;

        struct sockaddr_in client_addr;

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-1-7 10:14:26
        ** 说明: 建立tcp服务端
        ***********************************************/
        if (sat_socket_tcp_open(&server_fd, USER_NETWORK_TCP_ASYNC_PORT, DEVICE_MAX) == false)
        {
                SAT_DEBUG(" tcp open failed ");
                return false;
        }

        if (force == false)
        {
                sat_socket_udp_send(user_linphone_multicast_fd, (const char *)cmd, strlen((const char *)cmd), USER_NETWORK_MULTICAST_IP, USER_NETWORK_MULTICAST_PORT, 50);
                sat_socket_udp_send(user_linphone_multicast_fd, (const char *)cmd, strlen((const char *)cmd), USER_NETWORK_MULTICAST_IP, USER_NETWORK_MULTICAST_PORT, 50);
                sat_socket_udp_send(user_linphone_multicast_fd, (const char *)cmd, strlen((const char *)cmd), USER_NETWORK_MULTICAST_IP, USER_NETWORK_MULTICAST_PORT, 50);
        }
        if (sat_socket_udp_send(user_linphone_multicast_fd, (const char *)cmd, strlen((const char *)cmd), USER_NETWORK_MULTICAST_IP, USER_NETWORK_MULTICAST_PORT, 50) == true)
        {

                memset(&client_addr, 0, sizeof(struct sockaddr_in));

                for (int i = 0; i < device_max; i++)
                {

                        client_fd = sat_socket_tcp_accept(server_fd, &client_addr, 100);

                        if (client_fd < 0)
                        {

                                goto finish;
                        }

                        if (sat_socket_tcp_receive(client_fd, (unsigned char *)&device_info[i], sizeof(network_device_info), 100) > 0)
                        {

                                reslut = true;
                                (*receive_count)++;
                        }

                        sat_socket_close(client_fd);
                        client_fd = -1;
                }
        }

finish:

        if (client_fd > 0)
        {

                close(client_fd);
        }

        if (server_fd > 0)
        {

                close(server_fd);
        }

        return reslut;
}

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-7 14:46:50
** device_type:1 indoor,2 :outdoor
***********************************************/
bool user_network_device_query(unsigned char *user, int device_type, network_device_info *device_info, int max_device, int *device_count, bool force)
{
        char cmd[128] = {0};
        sprintf(cmd, NETWORK_CMD_DEVICE_INFO " %s %d %d %d", user, device_type, USER_NETWORK_TCP_ASYNC_PORT, force);
        if (user_network_multicast_cmd_send((unsigned char *)cmd, strlen(cmd), device_info, max_device, device_count, force) == false)
        {
                SAT_DEBUG("cmd send failed ");
                return false;
        }
        int total = (*device_count);
        for (int i = 0; i < total; i++)
        {
                for (int j = i + 1; j < total; j++)
                {
                        if (memcmp(&device_info[i], &device_info[j], sizeof(network_device_info)) == 0)
                        {
                                if (j + 1 != total)
                                {
                                        memmove(&device_info[j], &device_info[j + 1], sizeof(network_device_info) * (total - j - 1));
                                }
                                (*device_count)--;
                        }
                }
        }
        return true;
}

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-7 14:46:50
** 说明: tcp发送数据
***********************************************/
static int user_network_tcp_cmd_send(const char *string, unsigned char *client_ip, int timeout)
{
        int socket_fd = -1;
        if (sat_socket_tcp_open(&socket_fd, USER_NETWORK_TCP_SYNC_SLAVE_PORT, 0) == false)
        {
                SAT_DEBUG(" tcp open failed ");
                return -1;
        }
        if (sat_socket_tcp_connect(socket_fd, (char *)client_ip, USER_NETWORK_TCP_SYNC_SERVER_PORT, timeout) == false)
        {

                sat_socket_close(socket_fd);
                SAT_DEBUG(" connect timeout ");
                return -1;
        }
        if (sat_socket_tcp_send(socket_fd, (unsigned char *)string, strlen(string) + 1, timeout) == false)
        {
                sat_socket_close(socket_fd);
                SAT_DEBUG(" send(%s) failed ", client_ip);
                return -1;
        }
        return socket_fd;
}
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-7 14:46:50
** 说明: 接收当前数据
***********************************************/
static int user_network_tcp_cmd_recv(int socket_fd, unsigned char *buffer, int size, int timeout)
{
        int len = 0;
        if ((len = sat_socket_tcp_receive(socket_fd, buffer, size, timeout)) > 0)
        {
                return len;
        }
        return -1;
}
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-7 14:46:50
** 说明: 查询当前IP下的房号是否在线
***********************************************/
int user_network_device_online(const unsigned char *loc_number, network_device_info *device_info, int timeout)
{
        char number[32] = {0};
        char ip[32] = {0};
        network_device_info device_info_temp;
        /*获取用户对应的房号和IP*/
        sip_user_get_number_and_ip(device_info->number, ip, number);

        int socket_fd = -1;
        unsigned char buffer[128] = {0};
        sprintf((char *)buffer, NETWORK_CMD_DEVICE_ONLINE " %s", loc_number);
        if ((socket_fd = user_network_tcp_cmd_send((char *)buffer, (unsigned char *)ip, timeout)) < 0)
        {
                SAT_DEBUG("online send(%s)to (%s:%d) failed ", buffer, ip, USER_NETWORK_TCP_SYNC_SERVER_PORT);
                return -1;
        }
        if (user_network_tcp_cmd_recv(socket_fd, (unsigned char *)&device_info_temp, sizeof(network_device_info), timeout) <= 0)
        {
                SAT_DEBUG("online recv(%s)to (%s:%d) failed ", buffer, ip, USER_NETWORK_TCP_SYNC_SERVER_PORT);
                sat_socket_close(socket_fd);
                return -1;
        }
        sat_socket_close(socket_fd);

        // (p1)AAAAAAAAApwdAAAAAAAAsip_user
        char *p1 = strstr(device_info_temp.number, "AAAAAAAAA");
        char *p2 = strstr(p1 + 9, "AAAAAAAAA");
        if (strncmp(user_data_get()->device.password, p1 + 9, 9) == 0)
        {
                if ((strcmp(p2 + 9, device_info->number) != 0) /*  || (strcmp(device_info_temp.name, device_info->name) != 0) */)
                {
                        SAT_DEBUG("RECV IP USER:%s", p2 + 9);
                        memset(device_info->number, 0, sizeof(device_info->number));
                        strcpy(device_info->number, p2 + 9);
                        /* memset(device_info->name, 0, sizeof(device_info->name));
                        strcpy(device_info->name, device_info_temp.name); */
                        return 1;
                }
                return 0;
        }
        return -1;
}

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-7 14:46:50
** 说明: 更新房号的IP 返回0:无需更新，1,更新成功，-1,更新失败
***********************************************/
int user_network_user_update(const unsigned char *loc_number, network_device_info *device_info, int timeout)
{
        char number[64] = {0};
        char ip[32] = {0};
        network_device_info device_info_temp;
        int device_count = 0;
        /*获取用户对应的房号和IP*/
        sip_user_get_number_and_ip(device_info->number, ip, number);

        memset(&device_info_temp, 0, sizeof(network_device_info));
        memcpy(device_info_temp.number, device_info->number, sizeof(device_info->number));
        if (user_network_device_online(loc_number, &device_info_temp, timeout) >= 0)
        {
                /*该账号是存在的*/
                if ((strcmp(device_info_temp.number, device_info->number) == 0) /* && (strcmp(device_info_temp.name, device_info->name) == 0) */)
                {
                        return 0;
                }
                //       SAT_DEBUG("RECV IP USER:%s", device_info->number);
                memset(device_info->number, 0, sizeof(device_info->number));
                strcpy(device_info->number, device_info_temp.number);
                /*  memset(device_info->name, 0, sizeof(device_info->name));
                 strcpy(device_info->name, device_info_temp.name); */
                return 1;
        }

        /*该IP已经超时，需要重新组播获取IP信息,组播IP获取如果失败，则不更新用户信息*/
        memset(ip, 0, sizeof(ip));
        if (sat_ip_mac_addres_get(NETWORK_ETH_NAME, ip, NULL) == false)
        {
                SAT_DEBUG("sat_ip_mac_addres_get(NETWORK_ETH_NAME, ip, NULL) == false");
                return -1;
        }

        char cmd[128] = {0};
        sprintf(cmd, NETWORK_CMD_DEVICE_BY_NUMBER " %s %d %s %s", ip, USER_NETWORK_TCP_ASYNC_PORT, number, loc_number);
        SAT_DEBUG("update cmd:%s", cmd);
        if (user_network_multicast_cmd_send((unsigned char *)cmd, strlen(cmd), &device_info_temp, 1, &device_count, false) == false)
        {
                SAT_DEBUG("cmd send failed \n");
                return -1;
        }
        // (p1)AAAAAAAAApwdAAAAAAAAsip_user
        char *p1 = strstr(device_info_temp.number, "AAAAAAAAA");
        char *p2 = strstr(p1 + 9, "AAAAAAAAA");
        if (strncmp(user_data_get()->device.password, p1 + 9, 9) == 0)
        {
                if ((device_count == 1) && (strncmp(p2 + 9, device_info->number, 12) == 0))
                {
                        if ((strcmp(p2 + 9, device_info->number) == 0) /* && (strcmp(device_info_temp.name, device_info->name) == 0) */)
                        {
                                return 0;
                        }
                        SAT_DEBUG("RECV IP USER:%s", device_info->number);
                        memset(device_info->number, 0, sizeof(device_info->number));
                        strcpy(device_info->number, p2 + 9);
                        /* memset(device_info->name, 0, sizeof(device_info->name));
                        strcpy(device_info->name, device_info_temp.name); */
                        return 1;
                }
        }
        return -1;
}