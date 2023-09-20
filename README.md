# 2023/09/20
> 1. 增加画面调整接口，实现获取，写入还未完成
# 2023/09/18
> 1. 修复部分IPC获取RTSP流出现段错误的问题
> 2. 修复IPC修改密码后无法正常使用
> 3. 修复修改门口机密码后，再次绑定无法监控视频

# 2023/09/11
> 修改onvif协议，适配onvif 19版本以上


# 2023/09/06
> 1. 完善室内机铃声播放次数的接口
> 2. 增加接口让目标设备执行相应的shell 脚本
```c
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 15:21:6
** 说明: 发送shell cmd 执行命名
** ip: 对象IP，
** port: 对象端口
** user： 对象用户名
** password: 对象密码
** cmd: shell命令
** timeout : 超时时间
***********************************************/
bool sat_ipcamera_report_data(char *ip, int port, const char *user, const char *password, const char *cmd, int timeout);
```
> 3. 在user_newtork.c增加函数执行对方发送的shell脚本
```c 
static bool tcp_device_serverce_xml_process_shellcmd(int tcp_socket_fd, char *recv_string);
```

# 2023/09/05
> 1. 修复数据同步错误的问题，因为容易错误，故特此记录错误原因：
```c
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 15:21:6
** 说明: 数据同步处理.注意：此接口只有ID1处理
** type: 0:user_data,1:network_data,2:asterisk data
** flag: bit0:1发送到室内分机，bit1:1发送到门口机,bit2:1发送给主机
** data:需要同步的数据
** size:同步数据的大小
** inline_t:最后刷新注册的时间戳到现在的时间差判定是否在线
** timeout：发送超时
** param: 预留参数，如果需要发送给门口机，则需要传送绑定的设备信息
***********************************************/
bool sat_ipcamera_data_sync(char type, char flag, const char *data, int size, int inline_t, int timeout, void *param);

/****************************************************************
**@日期: 2022-09-20
**@作者: leo.liu
**@功能: 数据同步
*****************************************************************/
bool ipc_camera_device_sync_data(char *data_type, char *data, const char *ip, int port, const char *user, const char *password, int timeout)；
/*sat_ipcamera_data_sync()会将data数据会将data进行编码，但是只是进行一次编码，后续发送都是引用编码后的数据，但是此函数内部会调用
ipc_camera_device_sync_data()这个函数，这个函数会将编码的buffer数据改变，内容会发送得到的返回值，故需要修改重新填充base64编码的数据*/
```
> 2. 修改sip通话接口，增加参数区分app接听or室内机接听
```c
/*
 * @日期: 2022-09-06
 * @作者: leo.liu
 * @注释: 同意通话
 */
bool sat_linphone_answer(long id, bool is_tuya_anwser);
```
# 2023/09/01
> 1. 修改门口机的呼叫逻辑，在按键按下去的时候，如果之前是呼入状态，那么可以直接打断，进行呼出。
> 2. 修改室内机，增加分机同步信号到室内机功能
```c
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 15:21:6
** 说明: 数据同步处理.注意：此接口只有ID1处理
** type: 0:user_data,1:network_data
** flag: bit0:1发送到室内分机，bit1:1发送到门口机,bit2:1发送给主机
** data:需要同步的数据
** size:同步数据的大小
** inline_t:最后刷新注册的时间戳到现在的时间差判定是否在线
** timeout：发送超时
** param: 预留参数，如果需要发送给门口机，则需要传送绑定的设备信息
***********************************************/
bool sat_ipcamera_data_sync(char type, char flag, const char *data, int size, int inline_t, int timeout, void *param);
```
> 3. 修改门口机，将呼叫最长时间设置为3300秒
# 2023/08/22
> 1. 修复通话接口参数设置错误问题。（<0 当前通话，0xFFFF接收全部通话,其余，指定通话）
> 2. 修复绑定门口机，设备名称不显示的问题：\
        `因为判断sizeof长度使sip，与rtsp一致，故
        rtsp url与 sip url的数组长度要一致，否则会出现越界处理`
> 3. 室内机增加铃声播放次数接口，指定循环播放次数
```c
/***********************************************
** 作者: leo.liu
** 日期: 2022-10-19 8:57:42
** 说明: 铃声播放
***********************************************/
bool sat_linphone_audio_play_start(const char *file, int reount);
```

# 2023/08/21
> 1. 增加Asterik 数据同步
> 2. 增加数据同步到门口机
> 3. 将室内机呼出和呼入时间控制由用户控制，将门口机的呼入和呼出时间最大设置为40秒


# 2023/08/17
> 1. 修改Asterks 服务器的逻辑，群组呼叫未接通之前，挂断的时候将挂断群组所有设备
> 2. 修改逻辑，将符合COMMAX产品应用场景

# 2023/08/10
> 1. 修复音量控制接口没有作用

# 2023/08/09
> 1. 修复户户通没有声音

# 2023/08/08
修复的问题：
> 1. 修复设备注册后不显示设备名称；
> 2. 修复移动侦测开启后不触发的问题；
> 3. 优化设备启动流程；
> 4. 优化门口机，支持8台设备同时拉取RTSP流
> 5. 设置RTSP码流分辨率为1024x600

已知的问题:
> 1. 版本显示页面UI错乱
> 2. 监控页面点击通话后，挂断图标不居中显示

# 2023/08/07
备注说明:使用TF卡升级之前，请在设备上进行格式化后再升级
增加视频渲染处理回调函数
```c
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 9:53:56
** 说明:第一帧画面渲染到lcd上面的注册函数
***********************************************/
void first_refresh_lcd_cmd_callback_register(void (*callback)(int arg1, int arg2));
```
# 2023/08/02
> 1.    增加获取注册服务器在线设备接口:
 ```c
const asterisk_register_info* asterisk_register_info_get(void) 
```
> 2.    增加同步数据接口: 

```c
/**********************************************
** 作者: leo.liu 
** 日期: 2023-1-5 15:21:6
** 说明: 数据同步处理.注意：此接口只有ID1处理
** type: 0:user_data,1:network_data
** flag: bit0:1发送到室内分机，bit1:1发送到门口机
** data:需要同步的数据
** size:同步数据的大小
** inline_t:最后刷新注册的时间戳到现在的时间差判定是否在线
** timeout：发送超时
***********************************************/
bool sat_ipcamera_data_sync(char type, char flag, const char *data, int size, int inline_t, int timeout);
```
> 3.    增加接收到同步事件后的处理接口
```c
/***********************************************
** 作者: leo.liu
** 日期: 2023-1-5 9:53:56
** 说明:数据同步处理函数
***********************************************/
void sync_data_cmd_callback_register(void (*callback)(char flag,  char *str, int size, int pos, int max));

```

# 2023/07/29
> 1. 修复照片加载死机问题 
> 2. SIP注册和呼叫添加别名显示 
> 3. 增加前期媒体建立连接接口函数

# 2023/07/28
> 1. 添加sip server 功能; 
> 2. 添加sip server 群呼功能; 
> 3. 呼叫失败应用注册函数：
`void user_linphone_call_busy_register(user_linphone_func callback)` 
> 4. 呼叫用户正忙应用注册函数:
` void user_linphone_call_busy_register(user_linphone_func callback)` 
> 5. 修复应用莫名其妙段错误;

# 2023/07/12
> 1. 优化缩略图显示异常 
> 2. 修复wifi热点分配不到IP的问题 
> 3. 优化lvgl解码速度慢的问题 
> 4. 修复wifi热点无法搜索到涂鸦设备 
> 5. 增加门口机手动设置IP功能

# 2023/07/11
> 1. 修复TF卡升级检测不到tf卡 
> 2. 修复缩略图显示异常 
> 3. 修复mp3播放设置铃声之后死机 

# 2023/06/29
>1. 修复铃声停止播放接口调用后不会立即停止铃声 
>2. 增加铃声音量调节接口:
       ` bool sat_linphone_audio_play_volume_set(int volume);`
>3. 增加通话音量调节接口：
       ` bool sat_linphone_audio_talk_volume_set(int volume);`

# 2023/06/20

门口机增加onvfi协议功能

# 2023/06/09

修改移动侦测独立库

# 2023/06/07

1.优化守护进程偶尔机率闪退重启 \
2.修复WIFI上电因环境变量问题无法自动连接的问题，在profile下面的环境变量在引用程序中无法使用，但是终端却能使用，所以建议后续环境变量最好在rcS中建立，因不同平台profile还是很大差异。\
3.修复intercom点击通话无法接通的问题。\
4.优化移动侦测第一帧误触发 \
5.修复cctv无法触发移动侦测

# 2023/06/06

1.修复户户通功能

# 2023/06/05

1.修复wifi在线的情况下导致TCP/IP层端口被占用问题。\
2.添加移动侦测功能。\
3.TUYA功能增加双向对讲

# 2023/06/02

1.将网络相关的绑定指定网卡eth0(包括sip,onvif,rtp/rtcp等) \
2.修复二维码显示异常的问题

# 2023/05/31

1.门口机增加夜视开灯识别功能：

> 在打开视频流之后检测GPIO65为高电平后将GPIO81拉高；\
> 在打开视频流之后检测GPIO65为低电平，或者关闭视频流的时候拉低GPIO81。

2.修复室内机文件系统接口相关的问题，获取文件信息错误。 \
3.修复重启后CCTV切换宕机的问题。

# 2023/05/30

1.优化TF卡相关的接口，检测到TF卡错误，提示格式化 \
2.增加格式化TF卡接口，删除多余的分区。比如有mmcblkp0~n,格式化的时候将删除所有分区，最后挂载mmcblk0设备 \
3.实现layout_setting_storage_space.c的功能，显示flash的容量和tf的相关的内存信息 \
4.添加涂鸦dp点处理接口

# 2023/05/29

1.优化门口机丢包问题 \
2.合并邓嘉伟的最新代码

# 2023/05/27

1.修复媒体文件数量为0的情况下，缩略图工作不正常\
2.修复因修改网络通讯导致室内机无法升级门口机\
3.修复门口机呼叫时检测因绑定设备不在线导致长时间阻塞的问题 \
4.优化udhcpc，wpa等占用5060端口导致sip任务失败的问题 \
ush

# 2023/05/26

1.修改室内机和室外机网络通讯使用http协议 \
2.室外机增加RTSP推流服务器 \
3.适配commax的plus tool工具，通过此工具可以发现设备和查看设备的视频流

# 2023/05/08

## 发行说明

1.增加monitor_open（bool refresh）参数，是否显示到lcd。主要用于后台视频流录制和抓拍功能。

# 2023/05/05

## 发行说明

1.增加接口在layout_quit函数知道跳转的目标页面: const sat_layout_info *sat_next_layout_get(void); \
2.修复获取sensor错误通道值:  float user_sensor_value_get(int ch)

### 修改的文件

        indoor/app/include/common/sat_main_event.h
        indoor/app/lib/common/libuser_common.a 
        indoor/app/layout/common/user_gpio.c 

# 2023/05/04

## 增加读取当前sensor的通道电压值

        indoor/app/layout/common/user_gpio.c 
        indoor/app/layout/common/user_gpio.h

# 2023/05/04

## 发行说明

1. 增加涂鸦SDK的接入，相关的事件在layout_logo中注册
2. 在layout_logo.c中执行tuya事件注册函数，注册相关的事件处理 \
        void tuya_event_cmd_register(bool (*callback)(TUYA_CMD cmd, int arg1));

### 修改内容

        indoor/app/lib/common/libuser_common.a 
        indoor/app/lib/share/libmediastreamer2.a 
        indoor/app/lib/share/libtuya.a 
        indoor/app/include/common/sat_main_event.h 
        indoor/app/layout/layout_define.h 
        indoor/app/layout/layout_logo.c

### 新增加的文件

        indoor/app/layout/common/tuya_common.c 
        indoor/app/layout/common/tuya_common.h       
