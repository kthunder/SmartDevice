#include "oled_driver.h"

static ADDR_MODE addr_mode = PAGE_ADDRESSING_MODE;

void Oled_WriteCmd(uint8_t cmd)
{
    IIC_Start();
    IIC_WriteByteData(OLED_WRITE_ADDRESS);
    IIC_WriteByteData(0X00);
    IIC_WriteByteData(cmd);
    IIC_Stop();
}

void Oled_WriteData(uint8_t data)
{
    IIC_Start();
    IIC_WriteByteData(OLED_WRITE_ADDRESS);
    IIC_WriteByteData(0X40);
    IIC_WriteByteData(data);
    IIC_Stop();
}

uint32_t Oled_WriteNByteData(uint8_t *pata, uint16_t len)
{
    if(pata == NULL)
    {
        return 1;
    }

    IIC_Start();
    IIC_WriteByteData(OLED_WRITE_ADDRESS);
    IIC_WriteByteData(0X40);
    
    for(uint16_t i = 0; i < len; i++)
    {
        IIC_WriteByteData(pata[i]);
    }

    IIC_Stop();

    return 0;
}


/* 1. fundamental command*/
void Oled_SetContrastValue(uint8_t data)
{
    Oled_WriteCmd(0x81);
    Oled_WriteCmd(data);
}

/* 2. scrolling command*/
uint32_t Oled_H_Scroll(H_SCROLL_DIR dir, uint8_t start, uint8_t frame_freq, uint8_t end)
{
    if((dir != H_RIGHT) && (dir != H_LEFT))
    {
        return 1;
    }

    if((start > 7) || (frame_freq > 7) || (end > 7))
    {
        return 1;
    }

    if(start > end)
    {
        return 1;
    }

    Oled_WriteCmd(dir);
    Oled_WriteCmd(0x00);
    Oled_WriteCmd(start);
    Oled_WriteCmd(frame_freq);
    Oled_WriteCmd(end);
    Oled_WriteCmd(0x00);
    Oled_WriteCmd(0xff);

    return 0;
}

uint32_t Oled_HV_Scroll(HV_SCROLL_DIR dir, uint8_t start, uint8_t frame_freq, uint8_t end, uint8_t offset)
{
    if((dir != HV_RIGHT) && (dir != HV_LEFT))
    {
        return 1;
    }

    if((start > 7) || (frame_freq > 7) || (end > 7) ||(offset > 0x3F))
    {
        return 1;
    }

    if(start > end)
    {
        return 1;
    }

    Oled_WriteCmd(dir);
    Oled_WriteCmd(0x00);
    Oled_WriteCmd(start);
    Oled_WriteCmd(frame_freq);
    Oled_WriteCmd(end);
    Oled_WriteCmd(offset);

    return 0;
}

uint32_t Oled_V_Scroll(uint8_t rows, uint8_t row_num)
{
    if((rows > 0x3F) || (row_num > 0x7F))
    {
        return 1;
    }
    Oled_WriteCmd(rows);
    Oled_WriteCmd(row_num);
    
    return 0;
}

/* 3. address set command*/
uint32_t Oled_SetColAddr_Page(uint8_t col)
{
    if(addr_mode != PAGE_ADDRESSING_MODE)
    {
        return 1;
    }

    if(col > 0x7F)
    {
        return 1;
    }

    Oled_WriteCmd((0x00 + (col&0x0F)));
    Oled_WriteCmd((0x10 + (col >> 4)));

    return 0;
}

uint32_t Oled_SetAddressMode(ADDR_MODE addrMode)
{
    if(addrMode > 2)
    {
        return 1;
    }

    Oled_WriteCmd(addrMode);

    return 0;
}

uint32_t Oled_SetColAddr_HV(uint8_t start, uint8_t end)
{
    if(addr_mode == PAGE_ADDRESSING_MODE)
    {
        return 1;
    }

    if((start > 0x7F) || (end > 0x7F))
    {
        return 1;
    }

    Oled_WriteCmd(start);
    Oled_WriteCmd(end);

    return 0;
}

uint32_t Oled_SetPageAddr_HV(uint8_t start, uint8_t end)
{
    if((start > 0x7) || (end > 0x7))
    {
        return 1;
    }

    Oled_WriteCmd(0x22);
    Oled_WriteCmd(start);
    Oled_WriteCmd(end);

    return 0;
}

uint32_t Oled_SetPageAddr_Page(uint8_t start)
{
    if(start > 7)
    {
        return 1;
    }

    Oled_WriteCmd((0xB0 + start));

    return 0;
}

/* hardware configuration command*/
uint32_t Oled_SetDisplayStartLine(uint8_t line)
{
    if(line > 63)
    {
        return 1;
    }

    Oled_WriteCmd((0x40 + line));

    return 0;
}

uint32_t Oled_SetMultiplexRatio(uint8_t ratio)
{
    if ((ratio < 15) || (ratio > 64))
    {
        return 1;
    }

    Oled_WriteCmd(0xA8);
    Oled_WriteCmd(ratio);
    
    return 0;
}

uint32_t Oled_SetDisplayOffset(uint8_t offset)
{
    if (offset > 63)
    {
        return 1;
    }
    
    Oled_WriteCmd(0xD3);
    Oled_WriteCmd(offset);

    return 0;
}

uint32_t Oled_SetComPins(COM_PIN pin, COM_REMAP remap)
{
    if ((pin > 1) || (remap > 1))
    {
        return 1;
    }
    
    Oled_WriteCmd(0xDA);
    Oled_WriteCmd((0X02 + (pin << 4) + (remap << 5)));

    return 0;
}

/* clock command*/
uint32_t Oled_SetClockDivider(uint8_t div, uint8_t freq)
{
    if ((div > 0x0f) || (freq > 0x0f))
    {
        return 1;
    }

    Oled_WriteCmd(0xD5);
    Oled_WriteCmd(div + (freq << 4));

    return 0;
}

uint32_t Oled_SetPreCharge(uint8_t phase1, uint8_t phase2)
{
    if ((phase1 > 0x0f) || (phase2 > 0x0f))
    {
        return 1;
    }

    Oled_WriteCmd(0xD9);
    Oled_WriteCmd(phase1 + (phase2 << 4));

    return 0;
}

uint32_t Oled_SetVCOLevel(VCOMH_LEVEL level)
{
    if (level > 2)
    {
        return 1;
    }

    Oled_WriteCmd(0xDB);
    Oled_WriteCmd(level<< 4);

    return 0;
}

/* charge pump command*/
uint32_t Oled_SetChargePump(CHARGE_PUMP_STATE state)
{
    if (state> 1)
    {
        return 1;
    }

    Oled_WriteCmd(0x8D);
    Oled_WriteCmd(0x10 + (state << 2));

    return 0;
}

void Oled_Init(void)
{
    Oled_SetAddressMode(PAGE_ADDRESSING_MODE);
    Oled_SetMultiplexRatio(0x3F);
    Oled_SetDisplayOffset(0x00);
    Oled_SetDisplayStartLine(0x00);
    OLED_SEG_NOREMAP;
    NORMAL_SCAN;
    Oled_SetComPins(0x00, 0x00);
    Oled_SetContrastValue(0x7F);
    ENTIRE_DISP_OFF;
    DIS_NORMAL;
    Oled_SetClockDivider(0x00, 0x08);
    Oled_SetChargePump(PUMP_ENABLE);
    DIS_ON;
}

/* fundamental driver */
void Oled_SetPosition(uint8_t page, uint8_t col)
{
    Oled_SetPageAddr_Page(page);
    Oled_SetColAddr_Page(col);
}


void OLED_SetCursor(uint8_t Y, uint8_t X)
{
	Oled_WriteCmd(0xB0 | Y);					//设置Y位置
	Oled_WriteCmd(0x10 | ((X & 0xF0) >> 4));	//设置X位置高4位
	Oled_WriteCmd(0x00 | (X & 0x0F));			//设置X位置低4位
}
 
void OLED_Clear(void)
{  
	uint8_t i, j;
	for (j = 0; j < 8; j++)
	{
		OLED_SetCursor(j, 0);
		for(i = 0; i < 128; i++)
		{
			Oled_WriteData(0x00);
		}
	}
}
