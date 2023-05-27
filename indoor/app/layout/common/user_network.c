

#include "common/user_network.h"
#include "common/sat_main_event.h"
#include "common/sat_user_common.h"
#include "common/sat_user_time.h"
#include "common/user_data.h"
#include "layout_define.h"
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
#include "mxml-3.3.1/mxml.h"
#include "onvif.h"
#define DOOR_CAMERA_RECEIVE_BUFFER_MAX (100 * 1024)
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 16:55:3
** 说明: 所有设备的组播IP
***********************************************/
#define USER_NETWORK_MULTICAST_IP "239.255.255.250"
#define USER_NETWORK_MULTICAST_PORT 3702
#define USER_NETWORK_TCP_SYNC_SERVER_PORT 80
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 16:55:3
** 说明: 所有设备的组播IP
***********************************************/
#define S200_OK_REQUEST_PATH ONVIF_XML_PATH "200_ok_requeset.html"
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 16:53:57
** 说明: 组播套接字
***********************************************/
static int user_linphone_multicast_fd = -1;

/*接受数据解析处理*/
static bool discover_receive_data_parsing_processing(struct sockaddr_in *client_addr, const char *buf, int size)
{
        return true;
}
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 17:26:43
** 说明: 用户网络任务
***********************************************/
static void *user_network_common_multicast_task(void *arg)
{
        int recv_len = 0;
        /*存在缺陷，如果两帧都是buffer_size大小的包，并且间隔小于500ms，会被丢失之前的包*/
        char *buffer = malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        struct sockaddr_in client_addr;

        sat_socket_udp_open(&user_linphone_multicast_fd, USER_NETWORK_MULTICAST_PORT, true);
        sat_socket_multicast_join(user_linphone_multicast_fd, USER_NETWORK_MULTICAST_IP);
        while (1)
        {

                memset(buffer, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
                memset(&client_addr, 0, sizeof(struct sockaddr_in));
                recv_len = sat_socket_udp_receive(user_linphone_multicast_fd, buffer, DOOR_CAMERA_RECEIVE_BUFFER_MAX, &client_addr, 1000);
                if (recv_len > 0)
                {
                        discover_receive_data_parsing_processing(&client_addr, buffer, recv_len);
                }
        }

        return NULL;
}

/*********************************************** 		tcp   		***********************************************/
#define POST_ONVIF_DEVICE_HTML_TEXT "POST /onvif/device_service"

static bool trcp_device_serverce_xml_200_ok_requeset(int tcp_socket_fd, const char *string)
{
        int html_size = sat_file_size_get(S200_OK_REQUEST_PATH);
        if (html_size <= 0)
        {
                SAT_DEBUG(" char html_size = sat_file_size_get(S200_OK_REQUEST_PATH); \n");
                return false;
        }

        char *html_fmt = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        if (html_fmt == NULL)
        {
                SAT_DEBUG("char *html_buffer = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);");
                return false;
        }

        memset(html_fmt, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        int read_len = sat_file_read(S200_OK_REQUEST_PATH, html_fmt, html_size);
        if (read_len < 0)
        {
                SAT_DEBUG("int read_len = sat_file_read(S200_OK_REQUEST_PATH, html_buffer, html_size);");
                free(html_fmt);
                return false;
        }

        char *html_buffer = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        if (html_buffer == NULL)
        {
                SAT_DEBUG("char *html_buffer = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);");
                free(html_fmt);
                return false;
        }

        char *xml_fmt = strstr(html_fmt, "<?xml version=\"1.0\"");
        if (xml_fmt == NULL)
        {
                SAT_DEBUG("char *xml_fmt = strstr(html_fmt, \"<?xml version=1.0\n%s\n", html_fmt);
                free(html_buffer);
                free(html_fmt);
                return false;
        }

        char *xml_buffer = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        if (xml_buffer == NULL)
        {
                SAT_DEBUG("char *xml_buffer = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);");
                free(html_buffer);
                free(html_fmt);
                return false;
        }

        sprintf(xml_buffer, xml_fmt, string);
        int xml_size = strlen(xml_buffer);

        memset(xml_fmt, 0, strlen(xml_fmt) + 1);
        strcpy(xml_fmt, xml_buffer);

        memset(html_buffer, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        sprintf(html_buffer, html_fmt, xml_size);
        sat_socket_tcp_send(tcp_socket_fd, (unsigned char *)html_buffer, strlen(html_buffer), 3000);

        free(html_buffer);
        free(html_fmt);
        free(xml_buffer);
        return true;
}
static bool tcp_device_servrce_xml_get_device_name(int tcp_socket_fd, const char *xml)
{
        trcp_device_serverce_xml_200_ok_requeset(tcp_socket_fd, "CIP-70QPT");
        return true;
}

static bool tcp_device_serverce_xml_parsing(const char *xml,
                                            char *username, int username_size,
                                            char *password_digest, int passowrd_digest_size,
                                            char *nonce, int nonce_size,
                                            char *created, int created_size)
{
        bool reslut = false;
        char *pxml = strstr(xml, "<?xml version=\"1.0\"");
        if (pxml == NULL)
        {
                printf("%s\n", xml);
                return false;
        }

        mxml_node_t *root = mxmlLoadString(NULL, pxml, MXML_NO_CALLBACK);
        if (root != NULL)
        {
                mxml_node_t *node = mxmlFindElementSub(root, root, "Username", NULL, NULL, MXML_DESCEND);
                if (node != NULL)
                {
                        const char *text = mxmlGetText(node, NULL);
                        if (text != NULL)
                        {
                                //  SAT_DEBUG("Username:%s\n\n%s\n\n", text,pxml);
                                strncpy(username, text, username_size);
                                reslut = true;
                        }
                }

                node = mxmlFindElementSub(root, root, "Password", NULL, NULL, MXML_DESCEND);
                if (node != NULL)
                {
                        const char *text = mxmlGetText(node, NULL);
                        if (text != NULL)
                        {
                                //  SAT_DEBUG("Password:%s", text);
                                strncpy(password_digest, text, passowrd_digest_size);
                                reslut = true;
                        }
                }

                node = mxmlFindElementSub(root, root, "Nonce", NULL, NULL, MXML_DESCEND);
                if (node != NULL)
                {
                        const char *text = mxmlGetText(node, NULL);
                        if (text != NULL)
                        {
                                //   SAT_DEBUG("Nonce:%s", text);
                                strncpy(nonce, text, nonce_size);
                                reslut = true;
                        }
                }

                node = mxmlFindElementSub(root, root, "Created", NULL, NULL, MXML_DESCEND);
                if (node != NULL)
                {
                        const char *text = mxmlGetText(node, NULL);
                        if (text != NULL)
                        {
                                //  SAT_DEBUG("created:%s", text);
                                strncpy(created, text, created_size);
                                reslut = true;
                        }
                }
        }
        else
        {
                SAT_DEBUG("mxml_node_t *root = mxmlLoadString(NULL, pxml, MXML_NO_CALLBACK);")
        }
        mxmlDelete(root);
        return reslut;
}
static bool tcp_receive_device_service_html_processing(int tcp_socket_fd, const unsigned char *recv_data, int recv_size)
{
        char username[128] = {0};
        char password[128] = {0};
        char nonce[128] = {0};
        char created[128] = {0};
        if (tcp_device_serverce_xml_parsing((const char *)recv_data, username, sizeof(username),
                                            password, sizeof(password),
                                            nonce, sizeof(nonce),
                                            created, sizeof(created)) == false)
        {
                SAT_DEBUG("tcp_device_serverce_xml_parsing() == false");
                return false;
        }
#if 0
        if (onvif_username_token_check(username, password, nonce, created) == false)
        {
                return tcp_device_serverce_xml_bad_request(tcp_socket_fd);
        }
#endif

        char *soap_action_start_ptr = strstr((const char *)recv_data, "SOAPAction");
        if (soap_action_start_ptr == NULL)
        {
                SAT_DEBUG("char* soap_action_start_ptr = strstr(recv_data,\" SOAPAction \")");
                return false;
        }
        char *soap_action_end_str = strstr((const char *)recv_data, "<?xml version=\"1.0\"");
        if (soap_action_end_str == NULL)
        {
                SAT_DEBUG(" char *soap_action_end_str = strstr(recv_data, \"<?xml version=\"1.0\");");
                return false;
        }
        soap_action_end_str[0] = '\0';
        if (strstr(soap_action_start_ptr, "Get name"))
        {
                soap_action_end_str[0] = '<';
                return tcp_device_servrce_xml_get_device_name(tcp_socket_fd, soap_action_end_str);
        }
        return false;
}
static bool tcp_receive_data_parsing_processing(int tcp_socket_fd, const unsigned char *recv_data, int recv_size)
{
        if (strncasecmp((const char *)recv_data, POST_ONVIF_DEVICE_HTML_TEXT, strlen(POST_ONVIF_DEVICE_HTML_TEXT)) == 0)
        {
                return tcp_receive_device_service_html_processing(tcp_socket_fd, recv_data, recv_size);
        }
        return true;
}
static void *user_network_tcp_task(void *arg)
{
        int server_fd = -1;
        int recv_len = 0;
        struct sockaddr_in client_addr;
        unsigned char *receive_data = (unsigned char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);

        sat_socket_tcp_open(&server_fd, USER_NETWORK_TCP_SYNC_SERVER_PORT, DEVICE_MAX);
        while (1)
        {
                memset(&client_addr, 0, sizeof(struct sockaddr_in));
                int client_fd = sat_socket_tcp_accept(server_fd, &client_addr, 500);
                if (client_fd >= 0)
                {
                        memset(receive_data, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
                        while ((recv_len = sat_socket_tcp_receive(client_fd, receive_data, DOOR_CAMERA_RECEIVE_BUFFER_MAX, 100)) > 0)
                        {
                                //  printf("%s\n", receive_data);
                                tcp_receive_data_parsing_processing(client_fd, receive_data, recv_len);
                        }
                        sat_socket_close(client_fd);
                }
        }
        return NULL;
}

#define UDHCPC_TIMEOUT_MAX (30)
static bool ipaddr_udhcp_server_get_wait(void)
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
        return false;
}
static bool obtain_aipddress_based_on_manual(void)
{
        char cmd[128] = {0};
        sprintf(cmd, "ifconfig eth0 %s netmask %s", network_data_get()->ip, network_data_get()->mask[0] != 0 ? network_data_get()->mask : "255.0.0.0");
        system(cmd);
        SAT_DEBUG("%s ", cmd);
        return true;
}

static bool obtain_ipaddress_based_on_username(void)
{
        // 010193001012
        int buffer[4] = {0};
        char ip[32] = {0};
        memset(buffer, 0, sizeof(buffer));
        char *username = network_data_get()->sip_user;

        buffer[0] = (username[0] - 48) * 100 + (username[1] - 48) * 10 + (username[2] - 48);
        buffer[1] = ((username[3] - 48) * 100 + (username[4] - 48) * 10 + (username[5] - 48));
        buffer[2] = (username[6] - 48) * 100 + (username[7] - 48) * 10 + (username[8] - 48);
        buffer[3] = (username[9] - 48) * 100 + (username[10] - 48) * 10 + (username[11] - 48);

        sprintf(ip, "%d.%d.%d.%d", buffer[0], buffer[1], buffer[2], buffer[3]);

        char cmd[128] = {0};
        sprintf(cmd, "ifconfig eth0 %s netmask %s", ip, "255.0.0.0");
        system(cmd);
        SAT_DEBUG("%s ", cmd);

        SAT_DEBUG("defalut ip:%s,mask:%s", network_data_get()->ip, network_data_get()->mask);
        return true;
}

static bool add_multicase_routing_addres(void)
{
        char cmd[128] = {0};
        sprintf(cmd, "route add -net %s netmask %s eth0", "239.0.0.0", "255.0.0.0");
        system(cmd);
        SAT_DEBUG("%s ", cmd);

        sprintf(cmd, "route add -net %s netmask %s eth0", "225.0.0.0", "255.0.0.0");
        system(cmd);
        SAT_DEBUG("%s ", cmd);

        /*升级组播路由*/
        memset(cmd, 0, sizeof(cmd));
        sprintf(cmd, "route add -net %s netmask %s eth0", "224.0.0.0", "255.0.0.0");
        system(cmd);
        SAT_DEBUG("%s ", cmd);
        return true;
}

static bool netsta_port_information_kill(const char *info)
{

        char *end = strstr(info, "/");
        if (end == NULL)
        {
                return false;
        }
        *end = '\0';
        char *start = end - 1;
        while ((start != NULL) && !isspace(*start))
        {
                start--;
        }
        if (start != NULL)
        {
                char cmd[128] = {0};
                sprintf(cmd, "kill -s 9 %s", start);
                SAT_DEBUG("%s", cmd);
                system(cmd);
                return true;
        }
        return false;
}
static bool kill_related_port_process(char *port)
{
        FILE *fp = popen("netstat -anp", "r");
        if (fp == NULL)
        {
                printf("popen netstat -anp\n");
                return false;
        }
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), fp) > 0)
        {
                if (strstr(buffer, port) != NULL)
                {
                        netsta_port_information_kill(buffer);
                }
        }
        pclose(fp);
        return true;
}

static bool automatic_ip_setting(void)
{
        /*杀死相关的端口进程*/
        kill_related_port_process("5060");

        /* 在开机脚本已经做了udhcpc后台运行，此处检测3sec，如果没有获取到IP，将执行下一步动作*/
        if (ipaddr_udhcp_server_get_wait() == false)
        {
                system("killall udhcpc");
                if (network_data_get()->ip[0] != '\0')
                {
                        obtain_aipddress_based_on_manual();
                }
                else
                {
                        obtain_ipaddress_based_on_username();
                }
                add_multicase_routing_addres();
        }
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
        pthread_create(&thread_id, sat_pthread_attr_get(), user_network_common_multicast_task, NULL);
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
        int value[4] = {0};
        static char multicase_ip[32] = {0};
        const char *username = getenv("SIP");

        if ((username == NULL) || (strlen(username) < 12))
        {

                SAT_DEBUG("getenv sip failed");
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
