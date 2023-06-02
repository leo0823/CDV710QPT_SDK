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
## 发行说明:
1.增加monitor_open（bool refresh）参数，是否显示到lcd。主要用于后台视频流录制和抓拍功能。   

# 2023/05/05
## 发行说明：
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



# 2023/05/04:
## 发行说明：
1. 增加涂鸦SDK的接入，相关的事件在layout_logo中注册
2. 在layout_logo.c中执行tuya事件注册函数，注册相关的事件处理 \
        void tuya_event_cmd_register(bool (*callback)(TUYA_CMD cmd, int arg1));
### 修改内容: 
        indoor/app/lib/common/libuser_common.a 
        indoor/app/lib/share/libmediastreamer2.a 
        indoor/app/lib/share/libtuya.a 
        indoor/app/include/common/sat_main_event.h 
        indoor/app/layout/layout_define.h 
        indoor/app/layout/layout_logo.c

### 新增加的文件
        indoor/app/layout/common/tuya_common.c 
        indoor/app/layout/common/tuya_common.h       



