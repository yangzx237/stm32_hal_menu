#ifndef __MENU_H
#define __MENU_H

#include "encoder.h"

extern TIM_HandleTypeDef htim3;

typedef enum
{
		MENU_MAIN,
		MENU_LED,
		MENU_LED_SWITCH,
		MENU_LED_BRIGHTNESS,
		MENU_LED_BRIGHTNESS_CCR3
}MenuState;

void menuUpdate(EncoderEvent event);
void menuDisplay(void);

#endif
