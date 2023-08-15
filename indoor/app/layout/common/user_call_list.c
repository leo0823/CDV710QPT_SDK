#include "user_call_list.h"

#define USER_CALL_LIST_PATH "/app/data/user_call_list.cfg"

typedef struct
{
	int type;
    CALL_LOG_TYPE ch;
    int duration;
	struct tm time;
} call_list_info;

static int call_list_total = 0;
static call_list_info call_list[128];

static bool call_list_sync(void)
{
    system("rm -rf " USER_CALL_LIST_PATH);
	int fd = open(USER_CALL_LIST_PATH, O_CREAT | O_WRONLY);
	if (fd < 0)
	{
		return false;
	}
	if(write(fd, call_list, sizeof(call_list_info) * call_list_total) < 0)
	{
		perror("write failed\n");
	}
	close(fd);
	return true;
}
/***
**   日期:2022-06-20 09:56:23
**   作者: leo.liu
**   函数作用：加载列表
**   参数说明:
***/
bool call_list_init(void)
{
	call_list_total = 0;
	memset(call_list, 0, sizeof(call_list));
	int fd = open(USER_CALL_LIST_PATH, O_RDONLY);
	if (fd < 0)
	{
		return false;
	}
	call_list_info info;
	int len = sizeof(call_list_info);
	int read_len = 0;
	while ((read_len = read(fd, &info, len)) == len)
	{
		call_list[call_list_total++] = info;
		if (call_list_total == 128)
		{
			break;
		}
	}
	printf("call_list_total is %d\n",call_list_total);
	close(fd);
	call_list_sync();
	return true;
}
/***
**   日期:2022-06-20 10:01:56
**   作者: leo.liu
**   函数作用：添加一个呼叫信息
**   参数说明:
***/
bool call_list_add(int type, int ch,int duration,struct tm *tm)
{
	if (call_list_total == 128)
	{
		memmove(&call_list[0], &call_list[1], ((call_list_total) - 1) * sizeof(call_list_info));
        call_list_total--;
	}
	call_list[call_list_total].type = type;
	call_list[call_list_total].ch = ch;
	call_list[call_list_total].time = *tm;
	call_list[call_list_total].duration = duration;
	call_list_total++;
	call_list_sync();
	return true;
}
/***
**   日期:2022-06-20 10:02:35
**   作者: leo.liu
**   函数作用：删除所有列表
**   参数说明:
***/
bool call_list_del_all(void)
{
	remove(USER_CALL_LIST_PATH);
	system("sync");
	call_list_total = 0;
	memset(call_list, 0, sizeof(call_list));
	return true;
}

/***
** 日期: 2022-05-17 13:53
** 作者: leo.liu
** 函数作用：删除一个列表
** 返回参数说明：
***/
bool call_list_del(int index)
{
    memmove(&call_list[index], &call_list[index + 1], (((call_list_total) - 1) - index) * sizeof(call_list_info));
    call_list_total-- ;
    call_list_sync();
    return true;
}
/***
**   日期:2022-06-20 10:14:01
**   作者: leo.liu
**   函数作用：获取列表
**   参数说明:
***/
bool call_list_get(int index, CALL_LOG_TYPE * type, int *ch,int *duration,struct tm *tm)
{
	if (index >= call_list_total)
	{
		return false;
	}
	*type = call_list[index].type;
    *ch = call_list[index].ch;
	*tm = call_list[index].time;
	*duration = call_list[index].duration;
	return true;
}
/***
**   日期:2022-06-20 10:20:05
**   作者: leo.liu
**   函数作用：获取总数
**   参数说明:
***/
int call_list_total_get(void)
{
	return call_list_total;
}
