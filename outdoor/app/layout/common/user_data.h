#ifndef _USER_DATA_H_
#define _USER_DATA_H_
#include "stdbool.h"
#include <time.h>
#define DEVICE_MAX 8
typedef struct
{
        char ip[32];
        char mask[32];
} user_network_info;
typedef struct
{
        char number[128];
        char name[64];
        char password[10];
} network_device_info;

typedef struct
{
        user_network_info network;
        network_device_info device;

        int register_device_count;
        char register_device[DEVICE_MAX][64];
} user_data_info;

bool user_data_save(void);
bool user_data_init(void);
user_data_info *user_data_get(void);
void user_data_reset(void);

#endif
