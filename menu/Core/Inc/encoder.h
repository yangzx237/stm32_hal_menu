#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f1xx_hal.h"
extern TIM_HandleTypeDef htim2;

typedef enum
{
		ENCODER_NONE,
		ENCODER_CW,
		ENCODER_CCW,
		ENCODER_PRESS
}EncoderEvent;

EncoderEvent encoderRotation(void);
EncoderEvent encoderPress(void);
EncoderEvent encoderGetEvent(void);

#endif
