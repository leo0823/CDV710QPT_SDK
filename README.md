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



