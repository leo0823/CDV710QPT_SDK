#ifndef _ONVIF_USER_TOKEN_H_
#define _ONVIF_USER_TOKEN_H_
#include <stdbool.h>
#include <stdlib.h>

/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能: 口令格式获取
*****************************************************************/
size_t onvif_xml_fomrat_by_token(char *data, const char *ip, const char *user, const char *password, int argc, char **argv);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能: 摘要格式获取
*****************************************************************/
size_t onvif_xml_fomrat_by_digest(char *data, const char *ip, const char *user, const char *password, const char *math, const char *uri, const char *qop, const char *realm, const char *nonce, int argv, char **argc);
#endif