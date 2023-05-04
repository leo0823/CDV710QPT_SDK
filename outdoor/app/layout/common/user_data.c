
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
        .network = {.ip = "10.193.1.12", .mask = "255.0.0.0"},
        .device = {.name = "Door2", .number = "010193001012", .password = "123456789"},
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
** 函数作用：检验数据是否合法
** 返回参数说明：
***/
static void user_data_check_valid(void)
{
        bool resave = false;
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
        SAT_DEBUG("register cont:%d", user_data.register_device_count);

        for (int i = 0; i < user_data.register_device_count; i++)
        {
                for (int j = 0; j < 12; j++)
                {
                        user_data_check_range_out(register_device[i][j], '0', '9');
                }
                SAT_DEBUG("register device :%s", user_data.register_device[i]);
        }

        for (int i = 0; i < user_data.register_device_count; i++)
        {
                for (int j = i + 1; j < user_data.register_device_count; j++)
                {
                        if (strncmp(user_data.register_device[i], user_data.register_device[j], 12) == 0)
                        {
                                if (j < (user_data.register_device_count - 1))
                                {
                                        memmove(&(user_data.register_device[j]), &(user_data.register_device[j + 1]), sizeof(user_data.register_device[j])*(user_data.register_device_count - j - 1));
                                }
                                user_data.register_device_count--;
                                resave = true;
                        }
                }
        }

        SAT_DEBUG(" device name:%s", user_data.device.name);
        SAT_DEBUG(" device number:%s", user_data.device.number);
        SAT_DEBUG(" device password:%s", user_data.device.password);

        if (resave == true)
        {
                user_data_save();
        }
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
