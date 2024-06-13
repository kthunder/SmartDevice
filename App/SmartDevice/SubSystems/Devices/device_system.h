/*
    该文件用于管理设备子系统，包括GPIO控制（led）、风扇控制和OLED控制

*/
#ifndef DEVICE_SYSTEM_H
#define DEVICE_SYSTEM_H

#include "system_type.h"
#include "device_kal.h"
#include "string.h"

extern void AddDisplayDevice();
extern void InitDisplayDevices();
extern DisplayDevice* GetDisplayDevice(char *which);


#endif