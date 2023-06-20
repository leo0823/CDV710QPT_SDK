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
#include "common/sat_user_time.h"
#include "mxml-3.3.1/mxml.h"
#include "onvif/onvif.h"
#include "base64/include/libbase64.h"
#include "sha1/sha1.h"

#define DISCONVER_DEVICE_FILE_PATH ONVIF_XML_PATH "device_discovery_feedback.xml"
#define BAD_REQUEST_PATH ONVIF_XML_PATH "bad_requset.html"
#define S200_OK_REQUEST_PATH ONVIF_XML_PATH "200_ok_requeset.html"
#define GET_ONVIF_MEDIA_PROFILE_PATH ONVIF_XML_PATH "onvif_media_get_profile.html"
#define DEVICE_SERVICE_GET_INFORMATION_PATH ONVIF_XML_PATH "device_service_get_information.html"
#define DEVICE_SERVICE_GET_CAPABILITIES_PATH ONVIF_XML_PATH "device_serverce_get_capabilities.html"
#define DEVICE_SERVICE_GET_DNS_PATH ONVIF_XML_PATH "device_service_get_dns.html"
#define DEVICE_SERVICE_GET_NETWORKINTERFACE_PATH ONVIF_XML_PATH "device_service_get_networkinterfaces.html"
#define DEVICE_SERVICE_GET_INCLUDECAPABILITY_PATH ONVIF_XML_PATH "device_service_get_IncludeCapability.html"
#define DEVICE_SERVICE_GET_SYSTEM_TIME_AND_TIME_PATH ONVIF_XML_PATH "device_service_get_systemtime.html"
#define DEVICE_SERVICE_GET_SCOPES_PATH ONVIF_XML_PATH "device_serverce_get_scopes.html"
#define GET_ONVIF_STREAM_URI_PATH ONVIF_XML_PATH "get_streamuri.html"
#define GET_ONVIF_SNAPSHOT_URI_PATH ONVIF_XML_PATH "get_snapshoturi.html"
#define GET_ONVIF_VIDEO_SOURCE_PATH ONVIF_XML_PATH "onvif_media_get_videosources.html"
#define GET_ONVIF_INITIALTERMINATIONTIME_PATH ONVIF_XML_PATH "event_get_initialterminationtime.html"
#define GET_ONVIF_SNAPSHOT_JPG_PATH ONVIF_XML_PATH "push_snapshot_jpeg.xml"
#define FILE_ONVIF_SNAPSHOT_JPG_PATH ONVIF_XML_PATH "snapshot.jpg"

#define DOOR_CAMERA_RECEIVE_BUFFER_MAX (256 * 1024)

static int user_linphone_multicast_fd = -1;
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 16:55:3
** 说明: 所有设备的组播IP
***********************************************/
#define USER_NETWORK_MULTICAST_IP "239.255.255.250"
#define USER_NETWORK_MULTICAST_PORT 3702
#define USER_NETWORK_TCP_SYNC_SERVER_PORT 80

/*j解析设备*/
static bool discover_devices_data_parsing(const char *buf, const char *type, char *data, int size)
{
        bool reslut = false;
        const char *pxml = strstr(buf, "<"); //"<?xml version=\"1.0\"");
        if (pxml == NULL)
        {
                // printf("%s\n", buf);
                // return false;
                pxml = buf;
        }

        mxml_node_t *root = mxmlLoadString(NULL, pxml, MXML_NO_CALLBACK);
        if (root != NULL)
        {
                mxml_node_t *probe = mxmlFindElementSub(root, root, type, NULL, NULL, MXML_DESCEND);
                if (probe != NULL)
                {
                        const char *text = mxmlGetText(probe, NULL);
                        if (text != NULL)
                        {
                                strncpy(data, text, size);
                        }
                        reslut = true;
                }
        }
        /*  else
         {
                 SAT_DEBUG("mxml_node_t *root = mxmlLoadString(NULL, pxml, MXML_NO_CALLBACK);")
         } */
        mxmlDelete(root);
        return reslut;
}
static bool discover_devices_data_uuid_get(const char *buf, int size, char *uuid, int uuid_size)
{
        bool reslut = false;
        const char *pxml = strstr(buf, "<"); //<?xml version=\"1.0\"");
        if (pxml == NULL)
        {
                //    printf("%s\n", buf);
                //  return false;
                pxml = buf;
        }

        mxml_node_t *root = mxmlLoadString(NULL, pxml, MXML_NO_CALLBACK);
        if (root != NULL)
        {
                mxml_node_t *probe = mxmlFindElementSub(root, root, "MessageID", NULL, NULL, MXML_DESCEND);
                if (probe != NULL)
                {
                        const char *text = mxmlGetText(probe, NULL);
                        if (text != NULL)
                        {
                                strncpy(uuid, text, uuid_size);
                                reslut = true;
                        }
                }
        }
        else
        {
                SAT_DEBUG("%s", buf);
        }
        mxmlDelete(root);
        return reslut;
}
/*向对端发送设备信息*/
static bool doorcamera_device_discover_processing(struct sockaddr_in *client_addr, const char *relatesto_uuid)
{
        bool reslut = true;
        char *xml_buffer = malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        char *xml_buffer_fmt = malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        memset(xml_buffer, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        size_t xml_len = sat_file_read(DISCONVER_DEVICE_FILE_PATH, xml_buffer, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        if (xml_len <= 0)
        {
                SAT_DEBUG("read %s failed ", DISCONVER_DEVICE_FILE_PATH);
                reslut = false;
                goto finish;
        }
        static long msg_count = 10000;
        char ip[32] = {0};
        char local_uuid[128] = {0};
        const char *username = getenv("SIP");
        char regist_id[9] = {0};
        for (int i = 6, j = 0; i < 12; i += 2, j += 3)
        {
                strncat(&regist_id[j], &username[i], 2);
                if ((j + 2) < (sizeof(regist_id) - 3))
                {
                        regist_id[j + 2] = '-';
                }
        }

        sprintf(local_uuid, "urn:uuid:00010010-0001-1020-8000-%s", username);
        sat_ip_mac_addres_get("eth0", ip, NULL);
        sprintf(xml_buffer_fmt, xml_buffer, msg_count++, local_uuid, relatesto_uuid, local_uuid, regist_id, username, user_data_get()->device.name, ip);
        //    SAT_DEBUG("%s", xml_buffer_fmt);
        /****************************************************************
        2022-09-20 author:leo.liu 说明:发送探测消息
        *****************************************************************/
        xml_len = sendto(user_linphone_multicast_fd, xml_buffer_fmt, strlen(xml_buffer_fmt), 0, (const struct sockaddr *)client_addr, sizeof(struct sockaddr_in));
        if (xml_len < 0)
        {
                SAT_DEBUG(" xml_len = sendto(user_linphone_multicast_fd, xml_buffer, xml_len, 0, (const struct sockaddr *)client_addr, sizeof(struct sockaddr_in));");
        }

finish:
        if (xml_buffer != NULL)
        {
                free(xml_buffer);
        }
        if (xml_buffer_fmt != NULL)
        {
                free(xml_buffer_fmt);
        }
        return reslut;
}

/*接受数据解析处理*/
static bool discover_receive_data_parsing_processing(struct sockaddr_in *client_addr, const char *buf, int size)
{
        char data[128] = {0};
        if (discover_devices_data_parsing(buf, "Types", data, sizeof(data)) == true)
        {
                // SAT_DEBUG("discover :%s", type);
                /* 设备搜索*/
                if ((strstr(data, "Device") != NULL) || (strstr(data, "NetworkVideoTransmitter") != NULL) || (strstr(data, "NetworkVideoDisplay")))
                {
                        char relatesto_uuid[128] = {0};
                        if (discover_devices_data_uuid_get(buf, size, relatesto_uuid, sizeof(relatesto_uuid)) == true)
                        {
                                if ((strstr(relatesto_uuid, "18fafa95-0721-0823-0108-a98aa2dda8f7")) && (user_key_state_get() != KEY_STATE_LONG_DOWN))
                                {
                                        SAT_DEBUG("CIP70QPT is searching for a device, please hold down the call button");
                                        return false;
                                }
                                return doorcamera_device_discover_processing(client_addr, relatesto_uuid);
                        }
                }
                SAT_DEBUG("%s", buf);
        }
        return true;
}

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 17:26:43
** 说明: 用户网络任务
***********************************************/
static void *user_network_task(void *arg)
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
#define POST_ONVIF_MEDIA_TEXT "POST /onvif/media"
#define POST_SUBSCRIPTION_TEXT "POST /Subscription"
#define POST_ANALYTICS_TEXT "POST /onvif/analytics"
#define POST_EVENT_TEXT "POST /onvif/event"
#define GET_SNAPSHOT_JPG_TEXT "GET /images/snapshot.jpg"
static bool tcp_device_serverce_xml_parsing(const char *xml,
                                            char *username, int username_size,
                                            char *password_digest, int passowrd_digest_size,
                                            char *nonce, int nonce_size,
                                            char *created, int created_size)
{
        bool reslut = false;
        const char *pxml = strstr(xml, "<"); // "<?xml version=\"1.0\"");
        if (pxml == NULL)
        {
                // printf("%s\n", xml);
                // return false;
                pxml = xml;
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

static bool onvif_username_token_check(const char *admin, const char *from_token, const char *nonce, const char *created)
{
        // base64decode(nonce);
        char nonce_decode[128] = {0};
        size_t nonce_decode_len = 0;
        base64_decode(nonce, strlen(nonce), (char *)nonce_decode, &nonce_decode_len, 0);

        // sha1(base64decode(nonce) + date +password);
        SHA1_CTX ctx;
        SHA1Init(&ctx);
        SHA1Update(&ctx, (unsigned char *)nonce_decode, nonce_decode_len);
        SHA1Update(&ctx, (unsigned char *)created, strlen(created));
        SHA1Update(&ctx, (unsigned char *)user_data_get()->device.password, strlen(user_data_get()->device.password));

        // 输出sha1后的数据
        char hash2[20];
        SHA1Final((unsigned char *)hash2, &ctx);

        // base64编码
        char src_token[128] = {0};
        struct base64_state state;
        base64_stream_encode_init(&state, 0);
        size_t encode_len = 0;
        base64_stream_encode(&state, hash2, 20, src_token, &encode_len);
        size_t final_len = 0;
        base64_stream_encode_final(&state, &src_token[encode_len], &final_len);

        if (strcmp(from_token, src_token))
        {
                SAT_DEBUG("password error");
                return false;
        }
        SAT_DEBUG("password check success");
        return true;
}

static bool tcp_device_serverce_xml_bad_request(int tcp_socket_fd)
{
        int html_size = sat_file_size_get(BAD_REQUEST_PATH);
        if (html_size <= 0)
        {
                SAT_DEBUG(" char html_size = sat_file_size_get(BAD_REQUEST_PATH); \n");
                return false;
        }

        char *html_fmt = (char *)malloc(html_size);
        if (html_fmt == NULL)
        {
                SAT_DEBUG("char *html_buffer = (char *)malloc(html_size);");
                return false;
        }

        memset(html_fmt, 0, html_size);
        int read_len = sat_file_read(BAD_REQUEST_PATH, html_fmt, html_size);
        if (read_len < 0)
        {
                SAT_DEBUG("int read_len = sat_file_read(BAD_REQUEST_PATH, html_buffer, html_size);");
                free(html_fmt);
                return false;
        }
        if (sat_socket_tcp_send(tcp_socket_fd, (unsigned char *)html_fmt, read_len, 3000) == false)
        {
                SAT_DEBUG("sat_socket_tcp_send(tcp_socket_fd, (unsigned char *)html_fmt, read_len, 3000) == false");
        }

        free(html_fmt);
        return true;
}

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

static bool tcp_device_serverce_xml_get_information(int tcp_socket_fd)
{
        int html_size = sat_file_size_get(DEVICE_SERVICE_GET_INFORMATION_PATH);
        if (html_size <= 0)
        {
                SAT_DEBUG(" char html_size = sat_file_size_get(DEVICE_SERVICE_GET_INFORMATION_PATH); \n");
                return false;
        }

        char *html_fmt = (char *)malloc(html_size);
        if (html_fmt == NULL)
        {
                SAT_DEBUG("char *html_buffer = (char *)malloc(html_size);");
                return false;
        }

        memset(html_fmt, 0, html_size);
        int read_len = sat_file_read(DEVICE_SERVICE_GET_INFORMATION_PATH, html_fmt, html_size);
        if (read_len < 0)
        {
                SAT_DEBUG("int read_len = sat_file_read(DEVICE_SERVICE_GET_INFORMATION_PATH, html_buffer, html_size);");
                free(html_fmt);
                return false;
        }
        if (sat_socket_tcp_send(tcp_socket_fd, (unsigned char *)html_fmt, read_len, 3000) == false)
        {
                SAT_DEBUG("sat_socket_tcp_send(tcp_socket_fd, (unsigned char *)html_fmt, read_len, 3000) == false");
        }

        free(html_fmt);
        return true;
}

static bool tcp_device_servrce_xml_get_capabilities(int tcp_socket_fd)
{
        int html_size = sat_file_size_get(DEVICE_SERVICE_GET_CAPABILITIES_PATH);
        if (html_size <= 0)
        {
                SAT_DEBUG(" char html_size = sat_file_size_get(DEVICE_SERVICE_GET_CAPABILITIES_PATH); \n");
                return false;
        }

        char *html_fmt = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        if (html_fmt == NULL)
        {
                SAT_DEBUG("char *html_buffer = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);");
                return false;
        }

        memset(html_fmt, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        int read_len = sat_file_read(DEVICE_SERVICE_GET_CAPABILITIES_PATH, html_fmt, html_size);
        if (read_len < 0)
        {
                SAT_DEBUG("int read_len = sat_file_read(GET_MAP_PORTS_PATH, html_buffer, html_size);");
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
        char ip[32] = {0};
        sat_ip_mac_addres_get("eth0", ip, NULL);
        memset(xml_buffer, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        sprintf(xml_buffer, xml_fmt, ip, ip, ip, ip, ip, ip, ip, ip, ip, ip, ip);
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

static bool tcp_device_servrce_xml_get_scopes(int tcp_socket_fd)
{
        int html_size = sat_file_size_get(DEVICE_SERVICE_GET_SCOPES_PATH);
        if (html_size <= 0)
        {
                SAT_DEBUG(" char html_size = sat_file_size_get(DEVICE_SERVICE_GET_SCOPES_PATH); \n");
                return false;
        }

        char *html_fmt = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        if (html_fmt == NULL)
        {
                SAT_DEBUG("char *html_buffer = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);");
                return false;
        }

        memset(html_fmt, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        int read_len = sat_file_read(DEVICE_SERVICE_GET_SCOPES_PATH, html_fmt, html_size);
        if (read_len < 0)
        {
                SAT_DEBUG("int read_len = sat_file_read(GET_MAP_PORTS_PATH, html_buffer, html_size);");
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
        const char *username = getenv("SIP");
        char regist_id[9] = {0};
        for (int i = 6, j = 0; i < 12; i += 2, j += 3)
        {
                strncat(&regist_id[j], &username[i], 2);
                if ((j + 2) < (sizeof(regist_id) - 3))
                {
                        regist_id[j + 2] = '-';
                }
        }
        memset(xml_buffer, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        sprintf(xml_buffer, xml_fmt, regist_id, username, user_data_get()->device.name);
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

static bool tcp_device_servrce_xml_get_register(int tcp_socket_fd, const char *xml)
{
        char sip_uri[128] = {0};
        if (discover_devices_data_parsing(xml, "Register", sip_uri, sizeof(sip_uri)) == false)
        {
                return false;
        }
        char *p = strstr(sip_uri, "sip:");
        if (p == NULL)
        {
                SAT_DEBUG(" p = %s", sip_uri);
                return false;
        }

        if (detemine_existence_of_the_sip_uri(sip_uri) == false)
        {
                if (register_a_sip_uri(sip_uri) == false)
                {
                        SAT_DEBUG("if(register_a_sip_uri(sip_uri) == false)");
                        return false;
                }
                user_data_save();
        }
        trcp_device_serverce_xml_200_ok_requeset(tcp_socket_fd, "register");
        return true;
}

static bool tcp_device_servrce_xml_get_delete(int tcp_socket_fd, const char *xml)
{
        char sip_uri[128] = {0};
        if (discover_devices_data_parsing(xml, "Delete", sip_uri, sizeof(sip_uri)) == false)
        {
                return false;
        }
        char *p = strstr(sip_uri, "sip:");
        if (p == NULL)
        {
                SAT_DEBUG(" p = %s", sip_uri);
                return false;
        }

        if (detemine_existence_of_the_sip_uri(sip_uri) == false)
        {
                SAT_DEBUG("Account already exists :%s", sip_uri);
                return false;
        }

        if (delete_a_sip_uri(sip_uri) == false)
        {
                SAT_DEBUG("if(register_a_sip_uri(sip_uri) == false)");
                return false;
        }
        user_data_save();

        trcp_device_serverce_xml_200_ok_requeset(tcp_socket_fd, "delete");
        return true;
}

static bool tcp_device_servrce_xml_get_device_name(int tcp_socket_fd, const char *xml)
{
        trcp_device_serverce_xml_200_ok_requeset(tcp_socket_fd, user_data_get()->device.name);
        return true;
}

static bool tcp_device_servrce_xml_set_device_name(int tcp_socket_fd, const char *xml)
{
        char sip_uri[128] = {0};
        if (discover_devices_data_parsing(xml, "SetName", sip_uri, sizeof(sip_uri)) == false)
        {
                return false;
        }
        strncpy(user_data_get()->device.name, sip_uri, sizeof(user_data_get()->device.name));
        user_data_save();
        SAT_DEBUG("change name:%s", sip_uri);
        trcp_device_serverce_xml_200_ok_requeset(tcp_socket_fd, sip_uri);
        return true;
}

static bool tcp_device_servrce_xml_get_version_name(int tcp_socket_fd, const char *xml)
{
        char version[128] = {0};
        struct tm tm;
        if (platform_build_date_get(&tm) == true)
        {
                sprintf(version, "%04d-%02d-%02d %02d:%02d:%02d", tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
                trcp_device_serverce_xml_200_ok_requeset(tcp_socket_fd, version);
        }
        else
        {
                tcp_device_serverce_xml_bad_request(tcp_socket_fd);
        }

        return true;
}
static bool tcp_device_servrce_xml_channge_device_password(int tcp_socket_fd, const char *xml)
{
        char sip_uri[128] = {0};
        if (discover_devices_data_parsing(xml, "ChangePassword", sip_uri, sizeof(sip_uri)) == false)
        {
                return false;
        }
        strncpy(user_data_get()->device.password, sip_uri, sizeof(user_data_get()->device.password));
        user_data_save();
        SAT_DEBUG("change password:%s", sip_uri);
        trcp_device_serverce_xml_200_ok_requeset(tcp_socket_fd, sip_uri);
        return true;
}

static bool tcp_device_serverce_xml_get_dns(int tcp_socket_fd)
{
        int html_size = sat_file_size_get(DEVICE_SERVICE_GET_DNS_PATH);
        if (html_size <= 0)
        {
                SAT_DEBUG(" char html_size = sat_file_size_get(DEVICE_SERVICE_GET_DNS_PATH); \n");
                return false;
        }

        char *html_fmt = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        if (html_fmt == NULL)
        {
                SAT_DEBUG("char *html_buffer = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);");
                return false;
        }

        memset(html_fmt, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        int read_len = sat_file_read(DEVICE_SERVICE_GET_DNS_PATH, html_fmt, html_size);
        if (read_len < 0)
        {
                SAT_DEBUG("int read_len = sat_file_read(GET_MAP_PORTS_PATH, html_buffer, html_size);");
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
        } // mac  ip
        char mac[64] = {0};
        char ip[32] = {0};
        sat_ip_mac_addres_get("eth0", ip, mac);
        memset(xml_buffer, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        sprintf(xml_buffer, xml_fmt, mac, ip);
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

static bool tcp_device_serverce_xml_get_networkinterface(int tcp_socket_fd)
{
        int html_size = sat_file_size_get(DEVICE_SERVICE_GET_NETWORKINTERFACE_PATH);
        if (html_size <= 0)
        {
                SAT_DEBUG(" char html_size = sat_file_size_get(DEVICE_SERVICE_GET_NETWORKINTERFACE_PATH); \n");
                return false;
        }

        char *html_fmt = (char *)malloc(html_size);
        if (html_fmt == NULL)
        {
                SAT_DEBUG("char *html_buffer = (char *)malloc(html_size);");
                return false;
        }

        memset(html_fmt, 0, html_size);
        int read_len = sat_file_read(DEVICE_SERVICE_GET_NETWORKINTERFACE_PATH, html_fmt, html_size);
        if (read_len < 0)
        {
                SAT_DEBUG("int read_len = sat_file_read(DEVICE_SERVICE_GET_NETWORKINTERFACE_PATH, html_buffer, html_size);");
                free(html_fmt);
                return false;
        }
        if (sat_socket_tcp_send(tcp_socket_fd, (unsigned char *)html_fmt, read_len, 3000) == false)
        {
                SAT_DEBUG("sat_socket_tcp_send(tcp_socket_fd, (unsigned char *)html_fmt, read_len, 3000) == false");
        }

        free(html_fmt);
        return true;
}

static bool tcp_device_serverce_xml_get_includecapability(int tcp_socket_fd)
{
        int html_size = sat_file_size_get(DEVICE_SERVICE_GET_INCLUDECAPABILITY_PATH);
        if (html_size <= 0)
        {
                SAT_DEBUG(" char html_size = sat_file_size_get(DEVICE_SERVICE_GET_INCLUDECAPABILITY_PATH); \n");
                return false;
        }

        char *html_fmt = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        if (html_fmt == NULL)
        {
                SAT_DEBUG("char *html_buffer = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);");
                return false;
        }

        memset(html_fmt, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        int read_len = sat_file_read(DEVICE_SERVICE_GET_INCLUDECAPABILITY_PATH, html_fmt, html_size);
        if (read_len < 0)
        {
                SAT_DEBUG("int read_len = sat_file_read(GET_MAP_PORTS_PATH, html_buffer, html_size);");
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
        } // mac  ip
        char mac[64] = {0};
        char ip[32] = {0};
        sat_ip_mac_addres_get("eth0", ip, mac);
        memset(xml_buffer, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        sprintf(xml_buffer, xml_fmt, ip, ip, ip, ip, ip, ip, ip, ip, ip, ip, ip);
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

static bool tcp_device_serverce_xml_get_systemdataandtime(int tcp_socket_fd)
{
        int html_size = sat_file_size_get(DEVICE_SERVICE_GET_SYSTEM_TIME_AND_TIME_PATH);
        if (html_size <= 0)
        {
                SAT_DEBUG(" char html_size = sat_file_size_get(DEVICE_SERVICE_GET_SYSTEM_TIME_AND_TIME_PATH); \n");
                return false;
        }

        char *html_fmt = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        if (html_fmt == NULL)
        {
                SAT_DEBUG("char *html_buffer = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);");
                return false;
        }

        memset(html_fmt, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        int read_len = sat_file_read(DEVICE_SERVICE_GET_SYSTEM_TIME_AND_TIME_PATH, html_fmt, html_size);
        if (read_len < 0)
        {
                SAT_DEBUG("int read_len = sat_file_read(GET_MAP_PORTS_PATH, html_buffer, html_size);");
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
        } // mac  ip
        struct tm tm;
        user_time_read(&tm);
        memset(xml_buffer, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        sprintf(xml_buffer, xml_fmt, tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_year, tm.tm_mon, tm.tm_mday);
        int xml_size = strlen(xml_buffer);
        memset(xml_fmt, 0, strlen(xml_fmt) + 1);
        strcpy(xml_fmt, xml_buffer);

        memset(html_buffer, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        sprintf(html_buffer, html_fmt, xml_size);
        sat_socket_tcp_send(tcp_socket_fd, (unsigned char *)html_buffer, strlen(html_buffer), 3000);
        //   printf("%s,size:%d\n", html_buffer, strlen(html_buffer));
        free(html_buffer);
        free(html_fmt);
        free(xml_buffer);
        return true;
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
                                            created, sizeof(created)) == true)
        {
                if (onvif_username_token_check(username, password, nonce, created) == false)
                {
                        return tcp_device_serverce_xml_bad_request(tcp_socket_fd);
                }
        }

        char *ptr = strstr((const char *)recv_data, "<");
        if (ptr == NULL)
        {
                SAT_DEBUG("%s", recv_data);
                return false;
        }

        char data[128] = {0};
        if (discover_devices_data_parsing(ptr, "GetDeviceInformation", data, sizeof(data)) == true)
        {
                printf("[%s:%d] GetDeviceInformation\n", __func__, __LINE__);
                return tcp_device_serverce_xml_get_information(tcp_socket_fd);
        }
        if (discover_devices_data_parsing(ptr, "GetCapabilities", data, sizeof(data)) == true)
        {
                printf("[%s:%d] GetCapabilities\n", __func__, __LINE__);
                return tcp_device_servrce_xml_get_capabilities(tcp_socket_fd);
        }

        if (discover_devices_data_parsing(ptr, "GetScopes", data, sizeof(data)) == true)
        {
                printf("[%s:%d] GetScopes\n", __func__, __LINE__);
                return tcp_device_servrce_xml_get_scopes(tcp_socket_fd);
        }

        if (discover_devices_data_parsing(ptr, "Register", data, sizeof(data)) == true)
        {
                printf("[%s:%d] Register\n", __func__, __LINE__);
                return tcp_device_servrce_xml_get_register(tcp_socket_fd, ptr);
        }

        if (discover_devices_data_parsing(ptr, "Delete", data, sizeof(data)) == true)
        {
                printf("[%s:%d] Delete\n", __func__, __LINE__);
                return tcp_device_servrce_xml_get_delete(tcp_socket_fd, ptr);
        }

        if (discover_devices_data_parsing(ptr, "GetName", data, sizeof(data)) == true)
        {
                printf("[%s:%d] Get name\n", __func__, __LINE__);
                return tcp_device_servrce_xml_get_device_name(tcp_socket_fd, ptr);
        }

        if (discover_devices_data_parsing(ptr, "SetName", data, sizeof(data)) == true)
        {
                printf("[%s:%d] Set name\n", __func__, __LINE__);
                return tcp_device_servrce_xml_set_device_name(tcp_socket_fd, ptr);
        }

        if (discover_devices_data_parsing(ptr, "GetVersion", data, sizeof(data)) == true)
        {
                printf("[%s:%d] Get version\n", __func__, __LINE__);
                return tcp_device_servrce_xml_get_version_name(tcp_socket_fd, ptr);
        }

        if (discover_devices_data_parsing(ptr, "ChangePassword", data, sizeof(data)) == true)
        {
                printf("[%s:%d] Change password\n", __func__, __LINE__);
                return tcp_device_servrce_xml_channge_device_password(tcp_socket_fd, ptr);
        }

        if ((discover_devices_data_parsing((const char *)ptr, "Category", data, sizeof(data)) == true))
        {
                printf("[%s:%d] Category\n", __func__, __LINE__);
                return tcp_device_servrce_xml_get_capabilities(tcp_socket_fd);
        }
        if (discover_devices_data_parsing((const char *)recv_data, "GetDNS", data, sizeof(data)) == true)
        {
                printf("[%s:%d] GetDNS\n", __func__, __LINE__);
                return tcp_device_serverce_xml_get_dns(tcp_socket_fd);
        }
        if (discover_devices_data_parsing((const char *)recv_data, "GetNetworkInterfaces", data, sizeof(data)) == true)
        {
                printf("[%s:%d] GetNetworkInterfaces\n", __func__, __LINE__);
                return tcp_device_serverce_xml_get_networkinterface(tcp_socket_fd);
        }
        if (discover_devices_data_parsing((const char *)recv_data, "IncludeCapability", data, sizeof(data)) == true)
        {
                printf("[%s:%d] IncludeCapability\n", __func__, __LINE__);
                return tcp_device_serverce_xml_get_includecapability(tcp_socket_fd);
        }
        if (discover_devices_data_parsing((const char *)recv_data, "GetSystemDateAndTime", data, sizeof(data)) == true)
        {
                printf("[%s:%d] GetSystemDateAndTime\n", __func__, __LINE__);
                return tcp_device_serverce_xml_get_systemdataandtime(tcp_socket_fd);
        }
        SAT_DEBUG("%s", recv_data);
        return false;
}

static bool tcp_receive_onvif_media_get_profiles_processing(int tcp_socket_fd)
{
#if 1
        int html_size = sat_file_size_get(GET_ONVIF_MEDIA_PROFILE_PATH);
        if (html_size <= 0)
        {
                SAT_DEBUG(" char html_size = sat_file_size_get(GET_ONVIF_MEDIA_PROFILE_PATH); \n");
                return false;
        }

        char *html_fmt = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        if (html_fmt == NULL)
        {
                SAT_DEBUG("char *html_buffer = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);");
                return false;
        }

        memset(html_fmt, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        int read_len = sat_file_read(GET_ONVIF_MEDIA_PROFILE_PATH, html_fmt, html_size);
        if (read_len < 0)
        {
                SAT_DEBUG("int read_len = sat_file_read(GET_MAP_PORTS_PATH, html_buffer, html_size);");
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
        int xml_size = strlen(xml_fmt);

        memset(html_buffer, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        sprintf(html_buffer, html_fmt, xml_size);
        sat_socket_tcp_send(tcp_socket_fd, (unsigned char *)html_buffer, strlen(html_buffer), 3000);

        free(html_buffer);
        free(html_fmt);
#else
        int html_size = sat_file_size_get(GET_ONVIF_MEDIA_PROFILE_PATH);
        if (html_size <= 0)
        {
                SAT_DEBUG(" char html_size = sat_file_size_get(GET_ONVIF_MEDIA_PROFILE_PATH); \n");
                return false;
        }

        char *html_fmt = (char *)malloc(html_size);
        if (html_fmt == NULL)
        {
                SAT_DEBUG("char *html_buffer = (char *)malloc(html_size);");
                return false;
        }

        memset(html_fmt, 0, html_size);
        int read_len = sat_file_read(GET_ONVIF_MEDIA_PROFILE_PATH, html_fmt, html_size);
        if (read_len < 0)
        {
                SAT_DEBUG("int read_len = sat_file_read(GET_ONVIF_MEDIA_PROFILE_PATH, html_buffer, html_size);");
                free(html_fmt);
                return false;
        }
        if (sat_socket_tcp_send(tcp_socket_fd, (unsigned char *)html_fmt, read_len, 3000) == false)
        {
                SAT_DEBUG("sat_socket_tcp_send(tcp_socket_fd, (unsigned char *)html_fmt, read_len, 3000) == false");
        }

        free(html_fmt);
#endif
        return true;
}

static bool tcp_receive_onvif_media_get_streamuri_processing(int tcp_socket_fd)
{
        int html_size = sat_file_size_get(GET_ONVIF_STREAM_URI_PATH);
        if (html_size <= 0)
        {
                SAT_DEBUG(" char html_size = sat_file_size_get(GET_ONVIF_STREAM_URI_PATH); \n");
                return false;
        }

        char *html_fmt = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        if (html_fmt == NULL)
        {
                SAT_DEBUG("char *html_buffer = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);");
                return false;
        }

        memset(html_fmt, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        int read_len = sat_file_read(GET_ONVIF_STREAM_URI_PATH, html_fmt, html_size);
        if (read_len < 0)
        {
                SAT_DEBUG("int read_len = sat_file_read(DOOR_CAMERA_RECEIVE_BUFFER_MAX, html_buffer, html_size);");
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
        char ip[32] = {0};
        const char *username = getenv("SIP");
        sat_ip_mac_addres_get("eth0", ip, NULL);
        memset(xml_buffer, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        sprintf(xml_buffer, xml_fmt, ip, username, ip);
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

static bool tcp_receive_onvif_media_get_video_sources_processing(int tcp_socket_fd)
{
        int html_size = sat_file_size_get(GET_ONVIF_VIDEO_SOURCE_PATH);
        if (html_size <= 0)
        {
                SAT_DEBUG(" char html_size = sat_file_size_get(GET_ONVIF_VIDEO_SOURCE_PATH); \n");
                return false;
        }

        char *html_fmt = (char *)malloc(html_size);
        if (html_fmt == NULL)
        {
                SAT_DEBUG("char *html_buffer = (char *)malloc(html_size);");
                return false;
        }

        memset(html_fmt, 0, html_size);
        int read_len = sat_file_read(GET_ONVIF_VIDEO_SOURCE_PATH, html_fmt, html_size);
        if (read_len < 0)
        {
                SAT_DEBUG("int read_len = sat_file_read(GET_ONVIF_VIDEO_SOURCE_PATH, html_buffer, html_size);");
                free(html_fmt);
                return false;
        }
        if (sat_socket_tcp_send(tcp_socket_fd, (unsigned char *)html_fmt, read_len, 3000) == false)
        {
                SAT_DEBUG("sat_socket_tcp_send(tcp_socket_fd, (unsigned char *)html_fmt, read_len, 3000) == false");
        }

        free(html_fmt);

        return true;
}

static bool tcp_receive_onvif_media_get_snapshoturi_processing(int tcp_socket_fd)
{
        int html_size = sat_file_size_get(GET_ONVIF_SNAPSHOT_URI_PATH);
        if (html_size <= 0)
        {
                SAT_DEBUG(" char html_size = sat_file_size_get(GET_ONVIF_SNAPSHOT_URI_PATH); \n");
                return false;
        }

        char *html_fmt = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        if (html_fmt == NULL)
        {
                SAT_DEBUG("char *html_buffer = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);");
                return false;
        }

        memset(html_fmt, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        int read_len = sat_file_read(GET_ONVIF_SNAPSHOT_URI_PATH, html_fmt, html_size);
        if (read_len < 0)
        {
                SAT_DEBUG("int read_len = sat_file_read(DOOR_CAMERA_RECEIVE_BUFFER_MAX, html_buffer, html_size);");
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
        char ip[32] = {0};
        sat_ip_mac_addres_get("eth0", ip, NULL);
        memset(xml_buffer, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        sprintf(xml_buffer, xml_fmt, ip);
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
static bool tcp_receive_onvif_media_processing(int tcp_socket_fd, const unsigned char *recv_data, int recv_size)
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
                //     SAT_DEBUG("tcp_device_serverce_xml_parsing() == false");
                //     return false;
                return tcp_device_serverce_xml_bad_request(tcp_socket_fd);
        }
        if (onvif_username_token_check(username, password, nonce, created) == false)
        {
                return tcp_device_serverce_xml_bad_request(tcp_socket_fd);
        }

        char *ptr = strstr((const char *)recv_data, "<");
        if (ptr == NULL)
        {
                SAT_DEBUG("%s", recv_data);
                return false;
        }
        char data[128] = {0};
        if (discover_devices_data_parsing(ptr, "GetProfiles", data, sizeof(data)) == true)
        {
                printf("[%s:%d] GetProfiles\n", __func__, __LINE__);
                return tcp_receive_onvif_media_get_profiles_processing(tcp_socket_fd);
        }
        if (discover_devices_data_parsing(ptr, "GetStreamUri", data, sizeof(data)) == true)
        {
                printf("[%s:%d] GetStreamUri\n", __func__, __LINE__);
                return tcp_receive_onvif_media_get_streamuri_processing(tcp_socket_fd);
        }
        if (discover_devices_data_parsing(ptr, "GetVideoSources", data, sizeof(data)) == true)
        {
                printf("[%s:%d] GetVideoSources\n", __func__, __LINE__);
                return tcp_receive_onvif_media_get_video_sources_processing(tcp_socket_fd);
        }
        if (discover_devices_data_parsing(ptr, "GetSnapshotUri", data, sizeof(data)) == true)
        {
                printf("[%s:%d] GetSnapshotUri\n", __func__, __LINE__);
                return tcp_receive_onvif_media_get_snapshoturi_processing(tcp_socket_fd);
        }
        SAT_DEBUG("%s", recv_data);
        return false;
}

static bool tcp_receive_subscription_processing(int tcp_socket_fd, const unsigned char *recv_data, int recv_size)
{
        char data[512] = {0};
        if (discover_devices_data_parsing((const char *)recv_data, "Unsubscribe", data, sizeof(data)) == true)
        {
                printf("[%s:%d] Unsubscribe\n", __func__, __LINE__);
                printf("============%s:%d\n", __func__, __LINE__);
        }
        return false;
}

static bool tcp_receive_onvif_analytics_get_analyticsengines_processing(int tcp_socket_fd)
{

        printf("[%s:%d]================\n", __func__, __LINE__);
        return true;
}

static bool tcp_receive_analytics_processing(int tcp_socket_fd, const unsigned char *recv_data, int recv_size)
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
                return tcp_device_serverce_xml_bad_request(tcp_socket_fd);
        }
        if (onvif_username_token_check(username, password, nonce, created) == false)
        {
                return tcp_device_serverce_xml_bad_request(tcp_socket_fd);
        }

        char *ptr = strstr((const char *)recv_data, "<");
        if (ptr == NULL)
        {
                SAT_DEBUG("%s", recv_data);
                return false;
        }
        char data[512] = {0};
        if (discover_devices_data_parsing((const char *)recv_data, "GetAnalyticsEngines", data, sizeof(data)) == true)
        {
                printf("[%s:%d] GetAnalyticsEngines\n", __func__, __LINE__);
                return tcp_receive_onvif_analytics_get_analyticsengines_processing(tcp_socket_fd);
        }
        return false;
}

static bool tcp_receive_onvif_event_get_initialterminationtime_processing(int tcp_socket_fd, const char *relatesto_uuid)
{
        int html_size = sat_file_size_get(GET_ONVIF_INITIALTERMINATIONTIME_PATH);
        if (html_size <= 0)
        {
                SAT_DEBUG(" char html_size = sat_file_size_get(GET_ONVIF_INITIALTERMINATIONTIME_PATH); \n");
                return false;
        }

        char *html_fmt = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        if (html_fmt == NULL)
        {
                SAT_DEBUG("char *html_buffer = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);");
                return false;
        }

        memset(html_fmt, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        int read_len = sat_file_read(GET_ONVIF_INITIALTERMINATIONTIME_PATH, html_fmt, html_size);
        if (read_len < 0)
        {
                SAT_DEBUG("int read_len = sat_file_read(DOOR_CAMERA_RECEIVE_BUFFER_MAX, html_buffer, html_size);");
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
        char ip[32] = {0};
        sat_ip_mac_addres_get("eth0", ip, NULL);

        struct tm tm;
        user_time_read(&tm);

        memset(xml_buffer, 0, DOOR_CAMERA_RECEIVE_BUFFER_MAX);
        sprintf(xml_buffer, xml_fmt, relatesto_uuid, ip, ip, tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
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

static bool tcp_receive_event_processing(int tcp_socket_fd, const unsigned char *recv_data, int recv_size)
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
                //     SAT_DEBUG("tcp_device_serverce_xml_parsing() == false");
                //     return false;
                return tcp_device_serverce_xml_bad_request(tcp_socket_fd);
        }
        if (onvif_username_token_check(username, password, nonce, created) == false)
        {
                return tcp_device_serverce_xml_bad_request(tcp_socket_fd);
        }

        const char *ptr = strstr((const char *)recv_data, "<");
        if (ptr == NULL)
        {
                SAT_DEBUG("%s", recv_data);
                return false;
        }

        char data[512] = {0};
        if (discover_devices_data_parsing(ptr, "InitialTerminationTime", data, sizeof(data)) == true)
        {
                printf("[%s:%d] InitialTerminationTime\n", __func__, __LINE__);
                char relatesto_uuid[128] = {0};
                if (discover_devices_data_uuid_get((const char *)recv_data, recv_size, relatesto_uuid, sizeof(relatesto_uuid)) == true)
                {
                        return tcp_receive_onvif_event_get_initialterminationtime_processing(tcp_socket_fd, relatesto_uuid);
                }
        }

        return false;
}

static bool tcp_receive_snapshot_jpg_processing(int tcp_socket_fd, const unsigned char *recv_data, int recv_size)
{ /*
         char username[128] = {0};
         char password[128] = {0};
         char nonce[128] = {0};
         char created[128] = {0};
         if (tcp_device_serverce_xml_parsing((const char *)recv_data, username, sizeof(username),
                                             password, sizeof(password),
                                             nonce, sizeof(nonce),
                                             created, sizeof(created)) == false)
         {
                 //     SAT_DEBUG("tcp_device_serverce_xml_parsing() == false");
                 //     return false;
                 return tcp_device_serverce_xml_bad_request(tcp_socket_fd);
         }
         if (onvif_username_token_check(username, password, nonce, created) == false)
         {
                 return tcp_device_serverce_xml_bad_request(tcp_socket_fd);
         }
  */
        static char *jpeg_buffer = NULL;
        static int jpeg_buffer_size = 0;

        if (jpeg_buffer == NULL)
        {
                int html_size = sat_file_size_get(GET_ONVIF_SNAPSHOT_JPG_PATH);
                if (html_size <= 0)
                {
                        SAT_DEBUG(" char html_size = sat_file_size_get(GET_ONVIF_SNAPSHOT_JPG_PATH); \n");
                        return false;
                }

                char *html_buffer = (char *)malloc(html_size);
                if (html_buffer == NULL)
                {
                        SAT_DEBUG("char *html_buffer = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);");
                        return false;
                }
                memset(html_buffer, 0, html_size);

                int read_len = sat_file_read(GET_ONVIF_SNAPSHOT_JPG_PATH, html_buffer, html_size);
                if (read_len < 0)
                {
                        SAT_DEBUG("int read_len = sat_file_read(DOOR_CAMERA_RECEIVE_BUFFER_MAX, html_buffer, html_size);");
                        free(html_buffer);
                        return false;
                }
                int jpeg_size = sat_file_size_get(FILE_ONVIF_SNAPSHOT_JPG_PATH);

                int xml_szie = jpeg_size + html_size + 128;
                jpeg_buffer = (char *)malloc(xml_szie);
                if (jpeg_buffer == NULL)
                {
                        SAT_DEBUG("char *jpeg_buffer = (char *)malloc(DOOR_CAMERA_RECEIVE_BUFFER_MAX);");
                        free(html_buffer);
                        return false;
                }
                memset(jpeg_buffer, 0, jpeg_size);
                sprintf(jpeg_buffer, html_buffer, jpeg_size);

                html_size = strlen(jpeg_buffer);
                read_len = sat_file_read(FILE_ONVIF_SNAPSHOT_JPG_PATH, &jpeg_buffer[html_size], jpeg_size);
                if (read_len < 0)
                {
                        SAT_DEBUG("int read_len = sat_file_read(DOOR_CAMERA_RECEIVE_BUFFER_MAX, html_buffer, html_size);");
                        free(html_buffer);
                        free(jpeg_buffer);
                        jpeg_buffer = NULL;
                        return false;
                }
                free(html_buffer);
                jpeg_buffer_size = html_size + jpeg_size;
        }
        sat_socket_tcp_send(tcp_socket_fd, (unsigned char *)jpeg_buffer, jpeg_buffer_size, 3000);
        return false;
}

static bool tcp_receive_data_parsing_processing(int tcp_socket_fd, const unsigned char *recv_data, int recv_size)
{
        if (strncasecmp((const char *)recv_data, POST_ONVIF_DEVICE_HTML_TEXT, strlen(POST_ONVIF_DEVICE_HTML_TEXT)) == 0)
        {
                return tcp_receive_device_service_html_processing(tcp_socket_fd, recv_data, recv_size);
        }
        if (strncasecmp((const char *)recv_data, POST_ONVIF_MEDIA_TEXT, strlen(POST_ONVIF_MEDIA_TEXT)) == 0)
        {
                return tcp_receive_onvif_media_processing(tcp_socket_fd, recv_data, recv_size);
        }
        if (strncasecmp((const char *)recv_data, POST_SUBSCRIPTION_TEXT, strlen(POST_SUBSCRIPTION_TEXT)) == 0)
        {
                return tcp_receive_subscription_processing(tcp_socket_fd, recv_data, recv_size);
        }
        if (strncasecmp((const char *)recv_data, POST_ANALYTICS_TEXT, strlen(POST_ANALYTICS_TEXT)) == 0)
        {
                return tcp_receive_analytics_processing(tcp_socket_fd, recv_data, recv_size);
        }
        if (strncasecmp((const char *)recv_data, POST_EVENT_TEXT, strlen(POST_EVENT_TEXT)) == 0)
        {
                return tcp_receive_event_processing(tcp_socket_fd, recv_data, recv_size);
        }
        if (strncasecmp((const char *)recv_data, GET_SNAPSHOT_JPG_TEXT, strlen(GET_SNAPSHOT_JPG_TEXT)) == 0)
        {
                return tcp_receive_snapshot_jpg_processing(tcp_socket_fd, recv_data, recv_size);
        }

        SAT_DEBUG("%s", recv_data);
        return false;
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
                        while ((recv_len = sat_socket_tcp_receive(client_fd, receive_data, DOOR_CAMERA_RECEIVE_BUFFER_MAX, 1000)) > 0)
                        {
                                tcp_receive_data_parsing_processing(client_fd, receive_data, recv_len);
                        }
                        sat_socket_close(client_fd);
                }
        }
        return NULL;
}

#define UDHCPC_TIMEOUT_MAX (300)
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
        sprintf(cmd, "ifconfig eth0 %s netmask %s", user_data_get()->network.ip, user_data_get()->network.mask[0] != 0 ? user_data_get()->network.mask : "255.0.0.0");
        system(cmd);
        SAT_DEBUG("%s ", cmd);
        return true;
}

static int convert_a_string_to_an_integer_number(const char *str, int len)
{
        int val = 0;
        for (int i = 0; i < len; i++)
        {
                if ((str[i] >= '0') && (str[i] <= '9'))
                {
                        val = val * 16 + (str[i] - '0');
                }
                else if ((str[i] >= 'A') && (str[i] <= 'F'))
                {
                        val = val * 16 + ((str[i] - 'A') + 10);
                }
                else if ((str[i] >= 'a') && (str[i] <= 'f'))
                {
                        val = val * 16 + ((str[i] - 'a') + 10);
                }
        }
        return val;
}

static bool obtain_ipaddress_based_on_mac(void)
{
        char mac[64] = {0};
        if (sat_ip_mac_addres_get("eth0", NULL, mac) == false)
        {
                SAT_DEBUG("if(sat_ip_mac_addres_get(\"eth0\",NULL,mac) == false)");
                return false;
        }

        /*获取mac的xx:xx:xx:xx:xx:xx 低字节*/
        char *str = mac;
        for (int i = 0; i < 3; i++)
        {
                str = strchr(str, ':');
                if (str == NULL)
                {
                        SAT_DEBUG("char *str = strchar(mac, ':');%d", i);
                        return false;
                }
                str++;
        }
        if (strlen(str) != 8)
        {
                SAT_DEBUG("char *str = %s", str);
                return false;
        }

        int ip_part[3] = {0};
        ip_part[0] = convert_a_string_to_an_integer_number(str, 2);
        ip_part[1] = convert_a_string_to_an_integer_number(str + 3, 2);
        ip_part[2] = convert_a_string_to_an_integer_number(str + 6, 2);

        char ip[32] = {0};
        sprintf(ip, "%d.%d.%d.%d", 10, ip_part[0], ip_part[1], ip_part[2]);

        char cmd[128] = {0};
        sprintf(cmd, "ifconfig eth0 %s netmask %s", ip, "255.0.0.0");
        system(cmd);
        SAT_DEBUG("%s ", cmd);
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
static bool automatic_ip_setting(void)
{
        /* 在开机脚本已经做了udhcpc后台运行，此处检测3sec，如果没有获取到IP，将执行下一步动作*/
        if (ipaddr_udhcp_server_get_wait() == false)
        {
                system("killall udhcpc");
                /*手动设置的IP信息*/
                if (0) //(user_data_get()->network.ip[0] != '\0')
                {
                        obtain_aipddress_based_on_manual();
                }
                else
                {
                        obtain_ipaddress_based_on_mac();
                }
                add_multicase_routing_addres();
        }

        // char ip[128] = {0};
        // sat_ip_mac_addres_get("eth0", ip, NULL);
        // setenv("SIP", ip, 1);
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
        int value[4] = {0};
        static char multicase_ip[32] = {0};

        if (user_data_get()->register_device_count < 0)
        {
                return "224.0.0.0";
        }
        char *p = strstr(user_data_get()->register_device[0], "sip:");
        if ((p == NULL) || ((p + 1) == NULL))
        {
                return NULL;
        }
        const char *username = p + 4;

        memset(multicase_ip, 0, sizeof(multicase_ip));
        value[0] = 225;
        value[1] = ((username[3] - 48) * 100 + (username[4] - 48) * 10 + (username[5] - 48)) & 0x1F;
        value[2] = (username[6] - 48) * 100 + (username[7] - 48) * 10 + (username[8] - 48);
        value[3] = (username[9] - 48) * 100 + (username[10] - 48) * 10;
        sprintf(multicase_ip, "%d.%d.%d.%d", value[0], value[1], value[2], value[3]);

        SAT_DEBUG("sip:%s,multicase ip:%s", username, multicase_ip);
        return multicase_ip;
}

/***********************************TCP 发送************************************************/

/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能:向doorcamera 查询是否在线
*****************************************************************/
bool sat_ipcamera_device_name_get(const char *sip_uri, int timeout)
{
        char name[64] = {0};
        char *ip = strchr(sip_uri, '@');
        if ((ip == NULL) || ((ip + 1) == NULL))
        {
                return false;
        }
        return ipc_camera_device_name_get(name, ip + 1, 80, "CIP-710QPT", "12345678", timeout);
}