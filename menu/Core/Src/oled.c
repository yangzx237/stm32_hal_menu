#include "oled.h"
#include "font8x16.h"

void oledSendCmd(uint8_t cmd)
{
		uint8_t buf[2] = {0x00,cmd};
		
		HAL_I2C_Master_Transmit(&hi2c1,oledAddr,buf,2,100);
}

void oledSendData(uint8_t data)
{
		uint8_t buf[2] = {0x40,data};
		
		HAL_I2C_Master_Transmit(&hi2c1,oledAddr,buf,2,100);
}

void oledClear()
{
		for(uint8_t page = 0;page < 8; page++)
		{
				oledSendCmd(0xb0 + page);
				oledSendCmd(0x10);
				oledSendCmd(0x00);
				
				for(uint8_t col = 0; col < 128; col++)
				{
						oledSendData(0x00);
				}
		}
}

void oledSetCursor(uint8_t page, uint8_t col)
{
	page = (page > 7) ? 7 : page;
	col = (col > 127) ? 127 : col;
	
	oledSendCmd(0xb0 + page);
	oledSendCmd(0x10 + (col >> 4));
	oledSendCmd(0x00 + (col & 0x0f));
}

void oledShowChar(uint8_t page, uint8_t col, char ch)
{
		if(ch < 32 || ch > 126) ch = ' ';
		
		oledSetCursor(page, col);
		for(uint8_t i = 0; i < 8; i++) oledSendData(Font8x16[ch - 32][i]);
		
		oledSetCursor(page + 1, col);
		for(uint8_t i = 0; i < 8; i++) oledSendData(Font8x16[ch - 32][i + 8]);
}

void oledShowString(uint8_t page, uint8_t col, const char *str)//const ·ÀÖ¹ÄÚ²¿ÐÞ¸Ä×Ö·û´®
{
		while(*str)
		{
				oledShowChar(page, col, *str);
			
				col += 8;
			
				if(col > 120)
				{
						col = 0;
						page += 2;
				}
				str ++;
		}
}
void oledShowNum(uint8_t page, uint8_t col, uint16_t num)
{
		char buf[10];
		int i = 0;
		
		if(num == 0)
		{
				oledShowChar(page, col, '0');
				return;
		}
		
		while(num > 0)
		{
				buf[i++] = num % 10 + '0';
				num /= 10;
		}
		
		for(int j = i - 1; j >= 0; j--)
		{
				oledShowChar(page, col, buf[j]);
				col += 8;
		}
}

void oledInit()
{
		HAL_Delay(100);

    oledSendCmd(0xAE);
    oledSendCmd(0x20);
    oledSendCmd(0x10);
    oledSendCmd(0xB0);
    oledSendCmd(0xC8);
    oledSendCmd(0x00);
    oledSendCmd(0x10);
    oledSendCmd(0x40);
    oledSendCmd(0x81);
    oledSendCmd(0xFF);
    oledSendCmd(0xA1);
    oledSendCmd(0xA6);
    oledSendCmd(0xA8);
    oledSendCmd(0x3F);
    oledSendCmd(0xA4);
    oledSendCmd(0xD3);
    oledSendCmd(0x00);
    oledSendCmd(0xD5);
    oledSendCmd(0xF0);
    oledSendCmd(0xD9);
    oledSendCmd(0x22);
    oledSendCmd(0xDA);
    oledSendCmd(0x12);
    oledSendCmd(0xDB);
    oledSendCmd(0x20);
    oledSendCmd(0x8D);
    oledSendCmd(0x14);
    oledSendCmd(0xAF);

    oledClear();
		
		HAL_Delay(100);
}
