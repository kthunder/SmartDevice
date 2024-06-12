#ifndef OLED_DRIVER_H
#define OLED_DRIVER_H

#include "stm32f1xx_hal.h"
#include "main.h"
#include "stdio.h"

#include "iic_driver.h"

#define OLED_WRITE_ADDRESS  0x78
#define OLED_READ_ADDRESS   0x79

/* 函数声明 */
extern void Oled_WriteCmd(uint8_t cmd);
extern void Oled_WriteData(uint8_t data);
extern uint32_t Oled_WriteNByteData(uint8_t *pata, uint16_t len);

/* 基础命令功能函数 */
extern void Oled_SetContrastValue(uint8_t data);
#define ENTIRE_DISP_ON      Oled_WriteCmd(0xA5)
#define ENTIRE_DISP_OFF     Oled_WriteCmd(0xA4)

#define DIS_NORMAL          Oled_WriteCmd(0xA6)
#define DIS_INVERSE         Oled_WriteCmd(0xA7)

#define DIS_ON              Oled_WriteCmd(0xAF)
#define DIS_OFF             Oled_WriteCmd(0xAE)

/* 滚动命令功能函数 */
typedef enum
{
    H_RIGHT         = 0,
    H_LEFT          = 1,
}H_SCROLL_DIR;

typedef enum
{
    HV_RIGHT         = 0,
    HV_LEFT          = 1,
}HV_SCROLL_DIR;

extern uint32_t Oled_H_Scroll(H_SCROLL_DIR dir, uint8_t start, uint8_t frame_time, uint8_t end);
extern uint32_t Oled_HV_Scroll(HV_SCROLL_DIR dir, uint8_t start, uint8_t frame_freq, uint8_t end, uint8_t offset);
extern uint32_t Oled_V_Scroll(uint8_t rows, uint8_t row_num);

#define SCROLL_ACTIVE       Oled_WriteCmd(0x2F)
#define SCROLL_DEACTIVE     Oled_WriteCmd(0x2E)


/* 地址设置功能函数 */
typedef enum
{
    HORIZONTAL_ADDRESSING_MoODE     = 0X00,
    VERTICAL_ADDRESSING_MoODE       = 0X01,
    PAGE_ADDRESSING_MODE            = 0X02
}ADDR_MODE;

extern uint32_t Oled_SetColAddr_Page(uint8_t col);
extern uint32_t Oled_SetAddressMode(ADDR_MODE addrMode);
extern uint32_t Oled_SetColAddr_HV(uint8_t start, uint8_t end);
extern uint32_t Oled_SetPageAddr_HV(uint8_t start, uint8_t end);
extern uint32_t Oled_SetPageAddr_Page(uint8_t page);

/* 硬件配置功能函数*/
extern uint32_t Oled_SetDisplayStartLine(uint8_t line);
#define OLED_SEG_REMAP      Oled_WriteCmd(0xA1)
#define OLED_SEG_NOREMAP    Oled_WriteCmd(0xA0)
extern uint32_t Oled_SetMultiplexRatio(uint8_t ratio);
#define NORMAL_SCAN         Oled_WriteCmd(0xc0)
#define REMAPPED_SCAN       Oled_WriteCmd(0xc8)
extern uint32_t Oled_SetDisplayOffset(uint8_t ratio);

typedef enum
{
    COM_PIN_SEQ              = 0,
    COM_ALT_PINS             = 1,
}COM_PIN;

typedef enum
{
    DISABLE_REMAP            = 0,
    ENABLE_REMAP             = 1,
}COM_REMAP;
extern uint32_t Oled_SetComPins(COM_PIN pin, COM_REMAP remap);

/* 时间功能函数*/
extern uint32_t Oled_SetClockDivider(uint8_t div, uint8_t freq);
extern uint32_t Oled_SetPreCharge(uint8_t phase1, uint8_t phase2);

typedef enum
{
    LEVEL0                  = 0,
    LEVEL1                  = 1,
    LEVEL2                  = 2,
}VCOMH_LEVEL;

extern uint32_t Oled_SetVCOLevel(VCOMH_LEVEL level);



/* 电荷碰撞功能函数*/
typedef enum
{
    PUMP_DISABLE            = 0,
    PUMP_ENABLE             = 1
}CHARGE_PUMP_STATE;

extern uint32_t Oled_SetChargePump(CHARGE_PUMP_STATE state);

/* 基本驱动函数 */
extern void Oled_Init(void);
extern void Oled_SetPosition(uint8_t page, uint8_t col);;
#endif