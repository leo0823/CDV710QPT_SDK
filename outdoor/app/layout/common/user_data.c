
#include "user_data.h"

#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "stdio.h"
#include "stdlib.h"
#include "user_key.h"
#include "memory.h"
#include "common/sat_user_common.h"

#define USER_DATA_PATH "/etc/config/user_data.cfg"

static user_data_info user_data =
    {
        {
            {0},
        },
};

static const user_data_info user_data_default =
    {
        .network = {.ip = {'\0'}, .mask = "255.0.0.0"},
        .device = {.name = "CIP-D20YS", .number = "010193001012", .password = "123456789"},
        .register_device_count = 0,
};

bool user_data_save(void)
{
        int fd = open(USER_DATA_PATH, O_WRONLY | O_CREAT);

        if (fd < 0)
        {
                printf("write open %s fail \n", USER_DATA_PATH);
                return false;
        }

        write(fd, &user_data, sizeof(user_data_info));

        close(fd);
        system("sync");
        return true;
}

#define user_data_check_range_out(cur, min, max)                                   \
        if ((user_##data.cur < min) || (user_##data.cur > max))                    \
        {                                                                          \
                printf("user data error %d(%d,%d) \n", user_##data.cur, min, max); \
                user_##data.cur = user_##data##_default.cur;                       \
        }

#define user_data_network_check_range_out(x, min, max) user_data_check_range_out(network.x, min, max)
#define user_data_sip_check_range_out(x, min, max) user_data_check_range_out(device.x, min, max)

/***
** 日期: 2022-05-05 08:47
** 作者: leo.liu
** 函数作用：检验数据是否已经存在
** 返回参数说明：
***/
bool detemine_existence_of_the_sip_uri(const char *uri)
{
        for (int i = 0; i < user_data.register_device_count; i++)
        {
                if (strcmp(user_data.register_device[i], uri) == 0)
                {
                        return true;
                }
        }
        return false;
}

static void printf_register_device(void)
{
        SAT_DEBUG("register cont:%d", user_data.register_device_count);
        for (int i = 0; i < user_data.register_device_count; i++)
        {
                SAT_DEBUG("%s", user_data.register_device[i]);
        }
}

static bool detemine_sip_uri_in_same_room(const char *uri)
{
        for (int i = 0; i < user_data.register_device_count; i++)
        {
                if (strncmp(uri + 4, user_data_get()->register_device[i] + 4, 11))
                {
                        printf_register_device();
                        return false;
                }
        }
        return true;
}
/***
** 日期: 2022-05-05 08:47
** 作者: leo.liu
** 函数作用：注册一个账号
** 返回参数说明：
***/
bool register_a_sip_uri(const char *uri)
{
        SAT_DEBUG("reigster sip uir:%s", uri);
        /*先判断此账号是否属于同一个户号下面的*/
        if (detemine_sip_uri_in_same_room(uri) == false)
        {
                /*不属于同一个房号，则删除该账号下所有注册的账号*/
                for (int i = 0; i < user_data.register_device_count; i++)
                {
                        memset(&user_data.register_device[i], 0, sizeof(user_data.register_device[i]));
                }
                user_data.register_device_count = 0;
        }

        /*属于同一个房间，判断注册的大于最大个数*/
        if (user_data.register_device_count > 7)
        {
                /*删除最前面的一个账号*/
                for (int i = 0; i < user_data.register_device_count - 1; i++)
                {
                        memcpy(&user_data.register_device[i], &user_data.register_device[i + 1], sizeof(user_data.register_device[i]));
                }
                user_data.register_device_count--;
        }

        memset(user_data.register_device[user_data.register_device_count], 0, sizeof(user_data.register_device[user_data.register_device_count]));
        strncpy(user_data.register_device[user_data.register_device_count++], uri, sizeof(user_data.register_device[user_data.register_device_count]));

        printf_register_device();
        return true;
}
/***
** 日期: 2022-05-05 08:47
** 作者: leo.liu
** 函数作用：删除一个sip用户
** 返回参数说明：
***/
bool delete_a_sip_uri(const char *uri)
{
        SAT_DEBUG("delete sip uir:%s", uri);
        printf_register_device();
        int delete_index = 0;
        /*删除最前面的一个账号*/
        for (delete_index = 0; delete_index < user_data.register_device_count; delete_index++)
        {
                if (strcmp(user_data.register_device[delete_index], uri) == 0)
                {
                        break;
                }
        }
        if (delete_index == user_data.register_device_count)
        {
                return false;
        }

        for (int i = delete_index; i < user_data.register_device_count; i++)
        {
                memcpy(&user_data.register_device[i], &user_data.register_device[i + 1], sizeof(user_data.register_device[i]));
        }
        user_data.register_device_count--;
        printf_register_device();
        return true;
}
/***
** 日期: 2022-05-05 08:47
** 作者: leo.liu
** 函数作用：检验数据是否合法
** 返回参数说明：
***/
static void user_data_check_valid(void)
{
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-1-5 14:33:3
        ** 说明: 本机IP,和掩码
        ***********************************************/
        for (int i = 0; i < strlen(user_data.network.ip); i++)
        {
                if (user_data.network.ip[i] != '.')
                {
                        user_data_network_check_range_out(ip[i], '0', '9');
                        break;
                }
        }
        SAT_DEBUG("IP:%s", user_data.network.ip);

        for (int i = 0; i < strlen(user_data.network.mask); i++)
        {
                if (user_data.network.mask[i] != '.')
                {
                        user_data_network_check_range_out(mask[i], '0', '9');
                        break;
                }
        }
        SAT_DEBUG("mask:%s", user_data.network.mask);

        for (int i = 0; i < strlen(user_data.device.number); i++)
        {
                user_data_sip_check_range_out(number[i], '0', '9');
        }
        SAT_DEBUG("number:%s", user_data.device.number);

        user_data_check_range_out(register_device_count, 0, 9);

        SAT_DEBUG(" device name:%s", user_data.device.name);
        SAT_DEBUG(" device number:%s", user_data.device.number);
        SAT_DEBUG(" device password:%s", user_data.device.password);
        printf_register_device();
}

bool user_data_init(void)
{
        int fd = open(USER_DATA_PATH, O_RDONLY);

        if (fd < 0)
        {
                printf("read open %s fail \n", USER_DATA_PATH);
                user_data = user_data_default;
                return false;
        }

        read(fd, &user_data, sizeof(user_data_info));

        close(fd);
        user_data_check_valid();
        return true;
}

user_data_info *user_data_get(void)
{
        return &user_data;
}

void user_data_reset(void)
{
        user_data = user_data_default;
        user_data_save();
        system("sync");
}
