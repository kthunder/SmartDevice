/*
    该文件用于管理输入子系统，包括按键输入、网络输入和标准输入

*/

#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include "system_type.h"
#include "input_kal.h"
#include "general_kal.h"

extern InputDevice* g_InputDevice;

extern void AddInputDevices();
extern void InitInputDevices();

#endif


