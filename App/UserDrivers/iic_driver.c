#include "iic_driver.h"


void us_delay(uint32_t nCount)
{
    uint16_t counter = 0;
	
	while(nCount--)
	{
		counter=10; 
		
		while(counter--) ;    
	}
}

#define IIC_Delay()     us_delay(1)

void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();IIC_Delay();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; // 设置为开漏模式
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    GPIO_InitStruct.Pin = SCL_Pin;         // 选择LED的引脚
    HAL_GPIO_Init(SCL_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = SDA_Pin;         // 选择LED的引脚
    HAL_GPIO_Init(SDA_GPIO_Port, &GPIO_InitStruct);

}

void IIC_Start(void)
{
    SCL_H;
    SDA_H;
    IIC_Delay();
    SDA_L;
    IIC_Delay();
}

void IIC_Stop(void)
{
   
    SDA_L;
    SCL_H;
    IIC_Delay();
    SDA_H;
    IIC_Delay();
}

uint32_t IIC_GetAck(void)
{
    uint32_t nCount = 0;
    SDA_H;                  /*开漏模式下写1，数据线拉高，释放控制权*/
    SCL_L;                  /*时钟线拉低，此时数据不可更改，只能交换，允许从机发送ack*/
    IIC_Delay();

    SCL_H;                  /*时钟线拉高，读取数据*/
    IIC_Delay();

    while (SDA_IN != 0)    /*判断从机是否产生ack，若没有响应，就等待超时*/
    {
        nCount++;
        if(nCount == 1000)
        {
            SCL_L; 
            return 1;
        }
    }

    SCL_L;                  /*时钟线拉低，让主机等待从机处理接收数据*/
    
    return 0 ;
}

void IIC_ACK(void)
{
    SCL_L;
    SDA_L;
    IIC_Delay();

    SCL_H;
    IIC_Delay();
}

void IIC_NACK(void)
{
    SCL_L;
    SDA_H;
    IIC_Delay();

    SCL_H;
    IIC_Delay();

}

void IIC_WriteByteData(uint8_t data)
{
    for(uint32_t i = 0; i < 8; i++)
    {
        SCL_L;                  /*时钟线拉低，交换数据*/
        IIC_Delay();

        if(data & 0x80)
        {
            SDA_H;
        }
        else
        {
            SDA_L;
        }

        data = data << 1;
        SCL_H;                  /*时钟线拉高，读取数据*/
        IIC_Delay();
    }

    SCL_L;
    IIC_Delay();
    IIC_GetAck();
}

uint8_t IIC_ReadByteData(uint8_t ack)
{
    uint8_t rxdata = 0;
    SCL_L;    
    IIC_Delay();

    for(uint32_t i = 0; i < 8; i++)
    {
        SCL_H;                  /*时钟线拉高，读取数据*/
        IIC_Delay();

        rxdata = rxdata << 1;
        if(SDA_IN == 1)
        {
            rxdata |= 0x01;
        }
        else if (SDA_IN == 0)
        {
            rxdata |= 0x00;
        }

        SCL_L;                  /*时钟线拉低，读取数据*/
        IIC_Delay();
    }

    if(ack == 0)
    {
        IIC_ACK();
    }
    else if (ack == 1)
    {
        IIC_NACK();
    }
    
    return rxdata;
}
