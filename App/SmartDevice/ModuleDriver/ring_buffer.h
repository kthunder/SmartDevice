/*  防止输入设备的数据丢失，设计一个环形缓冲区将数据缓存 
    改模块包含读写环形缓冲区的函数操作
*/
#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include "system_type.h"

extern int PutEventIntoBuffer(InputEvent inputEvent);
extern int GetEventFromBuffer(InputEvent *pInputEvent);

#endif


