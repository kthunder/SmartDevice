#ifndef SYSTEM_TYPE_H
#define SYSTEM_TYPE_H

#include "stddef.h"

#define TIME_T                          int
#define INPUT_BUF_LEN                   100
#define BUFFER_SIZE                     10

#define RETURN_SUCCESS                  0X00
#define NULL_POINT                      0x01
#define BUFFER_FULL                     0x02
#define BUFFER_EMPTY                    0x03
#define NOT_FOUND                       0x03

#define INA_Pin                         GPIO_PIN_6
#define INA_GPIO_Port                   GPIOE
#define WHITE_Pin                       GPIO_PIN_7
#define WHITE_GPIO_Port                 GPIOF
#define BLUE_Pin                        GPIO_PIN_8
#define BLUE_GPIO_Port                  GPIOF
#define GREEN_Pin                       GPIO_PIN_9
#define GREEN_GPIO_Port                 GPIOF
#define SCL_Pin                         GPIO_PIN_10
#define SCL_GPIO_Port                   GPIOF
#define SDA_Pin                         GPIO_PIN_11
#define SDA_GPIO_Port                   GPIOF
#define KEY1_Pin                        GPIO_PIN_14
#define KEY1_GPIO_Port                  GPIOE
#define KEY2_Pin                        GPIO_PIN_15
#define KEY2_GPIO_Port                  GPIOE
#define INB_Pin                         GPIO_PIN_6
#define INB_GPIO_Port                   GPIOC
#define USART1_TX_Pin                   GPIO_PIN_9
#define USART1_TX_GPIO_Port             GPIOA
#define USART1_RX_Pin                   GPIO_PIN_10
#define USART1_RX_GPIO_Port             GPIOA
#define I2C1_SCL_Pin                    GPIO_PIN_6
#define I2C1_SCL_GPIO_Port              GPIOB
#define I2C1_SDA_Pin                    GPIO_PIN_7
#define I2C1_SDA_GPIO_Port              GPIOB


typedef enum
{
    INPUT_EVENT_TYPE_KEY                = 0,
    INPUT_EVENT_TYPE_TOUCH              = 1,
    INPUT_EVENT_TYPE_NET                = 2,
    INPUT_EVENT_TYPE_STDIO              = 3
}INPUT_EVENT_TYPE;

typedef struct InputEvent
{
    TIME_T time;
    INPUT_EVENT_TYPE eType;
    int iX;
    int iY;
    int iKey;
    int iPressure;
    char str[INPUT_BUF_LEN];
}InputEvent;

typedef struct InputDevice
{
    char* name;
    int (*GetInputEvent)(InputEvent *pInputEvent);
    void (*DeviceInit)(void);
    void (*DeviceDeInit)(void);

    struct InputDevice* next;   
}InputDevice;


typedef struct InputEventBuffer
{
    unsigned int pWrite;
    unsigned int pRead;
    InputEvent buffer[BUFFER_SIZE];
}InputEventBuffer;

typedef enum
{
    KEY1        = 1,
    KEY2        = 2
}INPUT_KEY_TYPE;

#define ISR(x)              void x##_IRQHandler(void)

#define KEY1_STATE          HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin);
#define KEY2_STATE          HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin);


typedef enum
{
    LED_WHITE                           = 0,
    LED_BLUE                            = 1,
    LED_GREEN                           = 2
}LED_LIGHT;

typedef struct LedDevice
{
    int which;
    int (*Init)(struct LedDevice *pLedDevice);
    int (*Control)(struct LedDevice *pLedDevice, int iStatus);
    void (*SelectColor)(struct LedDevice *pLedDevice, int iColor);
}LedDevice;

typedef struct DisplayDevice
{
    char *name;
    void *FrameBufferBase;
    int iXresolution;
    int iYresolution;
    int iBitPerPic;
    int (*Init)(struct DisplayDevice *pOledDevice);
    void (*Flash)(struct DisplayDevice *pOledDevice);
}DisplayDevice;




#endif