

/*******************************************************************************
 * @file		 user_main.c
 * @version	 v1.0.0
 * @copyright	 COPYRIGHT &copy; 2022 CSG
 * @author 	 kayshi
 * @date		 2022-10-8
 * @brief
 * @attention
 * Modification History
 * DATE		 DESCRIPTION
 * ------------------------
 * - 2022-10-8  SYK Created
 *******************************************************************************/
#include <stdlib.h>
#include "lvgl.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <mqueue.h>
#include <ctype.h>
#include <signal.h>

#include "common/ssd20x_common.h"
#include "common/sat_main_event.h"
#include "layout_define.h"
// #include "dds/topic_table.h"
#if 0
dds_inherit_listener
#endif

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-13 8:7:34
** 说明: 编译日期显示
***********************************************/
// #include "dmalloc.h"

/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 10:7:35
** 说明: 初始化内核
***********************************************/
static void linux_kerner_init(void)
{
        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2022-12-9 13:53:54
        ** 说明: 暂时处理上电打开功放
        ***********************************************/
        system("echo 12 > /sys/class/gpio/export");
        system("echo out > /sys/class/gpio/gpio12/direction");
        system("echo 1 > /sys/class/gpio/gpio12/value");

        system("ifconfig eth0 txqueuelen 10000");
        system("echo 10485760 > /proc/sys/net/core/wmem_max");
        system("echo 10485760 > /proc/sys/net/core/rmem_max");

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2023-1-5 14:2:17
        ** 说明: 设置环境变量
        ex :"010001001011" -> 010.001.001.011
                BYTE1. 010(固定部分).
                BYTE2. 001 -> 0x01
                                bit[7]=0:
                                bit[6:0] 栋号

                                bit[7]=1:
                                        分机(门口机/室内分机)
                                        bit[6:5]=00:室内分机
                                        bit[6:5]=10:户外机
                                        bit[6:5]=01:CCTV

                BYTE3. 001 楼层号SS
                BYTE4. 001 百分位和十分位 - 房号
                           个位 -BYTE2 bit[7]=0
                                                1:室内机
                                                3:Gateway IP systemD
                                                7:Lobby IP system
                                                9:Guard Phone IP system
                                                5:KIOSK IP system
                                   -BYTE2 bit[7]=1
                                                个位分机ID号
        ***********************************************/
        setenv("SIP", network_data_get()->sip_user, 1);
}

/*
 * @日期: 2022-08-06
 * @作者: leo.liu
 * @功能: lvgl 心跳任务
 * @return:
 */
static void *lv_sys_tick_task(void *arg)
{
        struct timeval tv1, tv2;
        gettimeofday(&tv2, NULL);

        while (1)
        {
                gettimeofday(&tv1, NULL);
                lv_tick_inc(tv1.tv_sec * 1000 + tv1.tv_usec / 1000 - tv2.tv_sec * 1000 - tv2.tv_usec / 1000);
                gettimeofday(&tv2, NULL);
                usleep(1000);
        }

        return NULL;
}

/***
** 日期: 2022-04-25 14:22
** 作者: leo.liu
** 函数作用：lvgl的任务调度以及心跳包线程
** 返回参数说明：
***/
static void lv_task_scheduling_start(void)
{
        pthread_t task_id;

        _sat_layout_goto(sat_playout_get(logo), LV_SCR_LOAD_ANIM_FADE_OUT);
        pthread_create(&task_id, sat_pthread_attr_get(), lv_sys_tick_task, NULL);

        while (1)
        {
                lv_task_handler();
                usleep(1000);
        }
}

/*
 * @日期: 2022-08-06
 * @作者: leo.liu
 * @功能: 主函数入口
 * @return:
 */
int main(int argc, char *argv[])
{
        signal(SIGPIPE, SIG_IGN);

        user_data_init();
        network_data_init();

        linux_kerner_init();

        /*
         * @日期: 2022-08-06
         * @作者: leo.liu
         * @注释: 平台sdk初始化
         */
        platform_sdk_init();

        /*lv_task_handler
         * @日期: 2022-08-08
         * @作者: leo.liu
         * @注释: lvgl core初始化
         */
        lv_init();

        /*
         * @日期: 2022-08-08
         * @作者: leo.liu
         * @注释:注册显示设备
         */
        lv_port_disp_init();

        /*
         * @日期: 2022-08-08
         * @作者: leo.liu
         * @注释: 注册输入设备
         */
        lv_port_indev_init();

        /*
         * @日期: 2022-08-08
         * @作者: leo.liu
         * @注释: 主任务初始化
         */
        sat_mian_task_init();

        /***********************************************
        ** 作者: leo.liu
        ** 日期: 2022-11-9 10:15:48
        ** 说明: 创建信令任务
        ***********************************************/
        // create_app_topic_task();
        // char* p = malloc(110*1024*1024);
        // if(p != NULL)
        //{
        //	printf("------malloc(19*1024*1024);-----\n");
        //}

        /*
         * @日期: 2022-08-08
         * @作者: leo.liu
         * @注释: 开启任务调度
         */
        lv_task_scheduling_start();

        return 0;
}
