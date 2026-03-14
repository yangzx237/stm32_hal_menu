#ifndef __OLED_H
#define __OLED_H

#include "stm32f1xx_hal.h"
extern I2C_HandleTypeDef hi2c1;

#define oledAddr 0x78
void oledSendCmd(uint8_t cmd);
void oledSendData(uint8_t data);
void oledClear(void);
void oledSetCursor(uint8_t page, uint8_t col);
void oledShowChar(uint8_t page, uint8_t col, char ch);
void oledShowString(uint8_t page, uint8_t col, const char *str);
void oledShowNum(uint8_t page, uint8_t col, uint16_t num);
void oledInit(void);

#endif
