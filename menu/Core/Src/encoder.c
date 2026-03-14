#include "encoder.h"
#include "oled.h"

//硬件编码器外设，顺时针旋转cnt计数加1，逆时针旋转cnt计数-1
 EncoderEvent encoderRotation()
{
		static int16_t last_cnt = 0;
		
		int16_t cnt = __HAL_TIM_GET_COUNTER(&htim2);

//编码器倍频计数，也就是转一个刻度累计4个脉冲，设置阈值以降低灵敏度，
//清空cnt寄存器以保证后续能正常触发，不然会累加或者累减
	
//二次修改，不采用清空cnt寄存器的操作，这样在快速旋转中容易卡死，程序读取到的值一直处于错误区间，
//采用记录cnt差值的方式
		int16_t diff = cnt - last_cnt;
    if(diff >= 2)
			{
				last_cnt += 2;
				return ENCODER_CW;
			}
    else if(diff <= -2)
			{
				last_cnt -= 2;
				return ENCODER_CCW;
			}
    return ENCODER_NONE;
}

//从延时消抖改为状态机消抖，降低双击的频率
//确认按下稳定再触发事件
EncoderEvent encoderPress()
{
		static uint8_t state = 0;
		static uint16_t cnt = 0;
	
		uint8_t key = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2);
	
		switch(state)
		{
			case 0://等待按键按下
				if(key == 0)
				{
					cnt = 0;
					state = 1;
				}
			break;
			
			case 1://消抖
				if(key == 0)
				{
					if(++cnt > 3)
					{
						state = 2;
						return ENCODER_PRESS;
					}
				}
				else state = 0;
			break;
				
			case 2 ://等待释放
				if(key == 1) state = 0;
			break;
		}
		return ENCODER_NONE;
}

EncoderEvent encoderGetEvent()
{	
		EncoderEvent event = encoderRotation();

		if(event != ENCODER_NONE) return event;
	
		return encoderPress();
}
