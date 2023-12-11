#ifndef _SAT_HTTPS_H_
#define _SAT_HTTPS_H_
#include <stdbool.h>
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/error.h"
#include "mbedtls/certs.h"
#include "mbedtls/net_sockets.h"
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能: 创建https句柄
*****************************************************************/
void *https_open(const char *host, const char *port, int timeout);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能: 发送数据
*****************************************************************/
int https_write(const void *handle, const char *data, int size);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能: 接收数据
*****************************************************************/
int https_read(void *handle, char *data, int length);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能: 关闭连接
*****************************************************************/
int https_close(void *handle);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能: 获取body数据
*****************************************************************/
int https_data_body_parse(char *data, int data_size, int *body_length);
/****************************************************************
**@日期: 2022-09-21
**@作者: leo.liu
**@功能: aes-cbc-256解密数据
*****************************************************************/
size_t aes_256_cbc_encrypt_data(unsigned char *input_data, const unsigned char key[32], unsigned char iv[16], unsigned char *output, int output_len, int block_size);
#endif