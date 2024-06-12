#ifndef IIC_DRIVER_H
#define IIC_DRIVER_H

#include "stm32f1xx_hal.h"
#include "system_type.h"
#include "stdio.h"

#define SCL_H HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, 1)
#define SCL_L HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, 0)

#define SDA_H HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, 1)
#define SDA_L HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, 0)

#define SDA_IN HAL_GPIO_ReadPin(SDA_GPIO_Port, SDA_Pin)

extern void IIC_Init(void);
extern void IIC_Start(void);
extern void IIC_Stop(void);
extern uint32_t IIC_GetAck(void);
extern void IIC_WriteByteData(uint8_t data);
extern uint8_t IIC_ReadByteData(uint8_t ack);


#endif