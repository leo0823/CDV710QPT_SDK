#ifndef _COMMAX_WEBSOKET_H_
#define _COMMAX_WEBSOKET_H_
/*ip传输*/
const char *commax_transport_ip_get(void);
/*commax incoming receive process */
bool commax_sip_incoming_receive_process(const char *ip, int timeout);
/*asterisk init*/
bool commax_sip_asterisk_server_init(const char *from_sip_conf, const char *to_sip_conf, const char *from_extensions_conf, const char *to_extensions_conf, const char *commax_server_ip, const char *asterisk_register_usernmae);
/*修改服务器lobbyphone的密码*/
bool commax_https_server_lobbyphone_change_password(const char *server_ip, const char *port, char *lo_dong, char *lo_ho, char *pwd, char *reslut_msg, int msg_max, int timeout);
/*大厅机开锁*/
bool commax_https_lobbyphone_open_the_door(const char *ip, const char *port, int timeout);
#endif