# SmartDevice
该项目用来熟悉HAL库的使用以及学习应用层软件架构设计。
总共分为三个部分，每个部分都有专门的内核抽象层，保证软件的兼容性和扩展性（目前仅包括裸机，后续将引入FreeRTOS）

一、input system    用来管理输入，包括按键、串口和网络
二、device system   用来管理设备，包括LED、OLED（SSD1306）和风扇
三、net system      用来实现网络信息传输，通过ESP8266和AT指令，传递必要操作和信息

