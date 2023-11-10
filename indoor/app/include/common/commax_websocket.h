#ifndef _COMMAX_WEBSOKET_H_
#define _COMMAX_WEBSOKET_H_

/*commax incoming receive process */
bool commax_sip_incoming_receive_process(const char *ip, int timeout);
/*asterisk init*/
bool commax_sip_asterisk_server_init(const char *from_sip_conf, const char *to_sip_conf, const char *from_extensions_conf, const char *to_extensions_conf, const char *commax_server_ip, const char *asterisk_register_usernmae);
#endif