# SmartDevice
基于STM32F103实现的智能设备
该项目用来熟悉HAL库的使用、学习应用层软件架构设计、网络通信和FreeRTOS的实际运用。
开发流程如下：
一、设计系统框架
    1.整个系统包括三个模块
        （1）input system    用来管理输入，包括按键、串口和网络
        （2）device system   用来管理设备，包括LED、OLED（SSD1306）和风扇
        （3）net system      用来实现网络信息传输，通过ESP8266和AT指令，传递必要操作和信息
    2.每个模块都有抽象层，保证软件的兼容性和扩展性（目前仅包括裸机，后续将引入FreeRTOS）
        （1）Kernal Abstract Layer    用来抽象内核，即可兼容裸机或RTOS
        （2）Chip Abstract Layer      用来抽象芯片，即可兼容STM32或NXP等

二、编程开发
    1.SubSystems文件夹下，实现所有的子系统，包括添加设备、初始化设备等接口，用户可在
        （1）Input下实现输入子系统的功能
        （2）Devices下实现设备子系统的功能
        （3）Net下实现网络子系统的功能
        （4）system_type.h下实现所有的结构体、错误码、宏定义等
    2.KAL文件夹下，即为内核抽象层
    3.CAL文件夹下，即为芯片抽象层
    4.ModuleDriver，即为模块所需的驱动（以下排序仅按照字母排序，和开发先后无关）
        （1）ascii_font，用于存放字库
        （2）fan_driver，实现风扇的初始化和转动
        （3）iic_driver，用GPIO模拟实现I2C功能，包括引脚初始化、start、stop、ack、getAck、writeByteData等功能
        （4）key_driver，按键作为输入系统的一部分，将其作为中断入口，实现
        （5）led_driver，用于初始化LED、指定灯的开关
        （6）oled_driver，根据参考手册，将oled的各种命令和字符显示封装成接口
        （7）ring_buffer，用于事件缓冲区的实现，可处理来自不同渠道的输入事件
        （8）uart_driver，用于实现printf的重定义、单个字节的缓冲区以及Uart1和Uart3之间的数据交换功能

三、功能测试
    



TIP：
本工程完全不符合ASPICE流程，但也做到了一个开发测试较为标准的流程
1.代码并非最标准的代码，如需要符合标准Misra C的代码，还需用polyspace检查
2.测试并非专业测试，仅测试功能是否实现，若需要单元测试，还需用CUnit编写覆盖函数（后续可能会实现）




