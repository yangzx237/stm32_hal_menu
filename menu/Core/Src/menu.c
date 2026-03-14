#include "menu.h"
#include "oled.h"

MenuState menu = MENU_MAIN;

uint8_t main_index = 0;
uint8_t led_index = 0;
uint8_t led_switch_index = 0;
uint8_t led_brightness_index = 0;
uint8_t led_brightness_ccr3_index = 0;
uint16_t ccr3 = 0;
uint8_t edit_mode = 0;

// 需要检查各个index的值，不然会出现上溢出，也就是255之后是0或者下溢出，也就是0下面是255
//负责处理逻辑，不负责显示内容
void menuUpdate(EncoderEvent event)
{
		switch(menu)
		{
			case MENU_MAIN:
				if(event == ENCODER_CW)
				{
					if(main_index < 1) main_index++;
				}
				if(event == ENCODER_CCW)
				{
					if(main_index > 0) main_index--;
				}
				if(event == ENCODER_PRESS)
				{
					if(main_index == 0) menu = MENU_LED;
				}
			break;
			
			case MENU_LED:
				if(event == ENCODER_CW)
				{
					if(led_index < 2) led_index++;
				}
				if(event == ENCODER_CCW)
				{
					if(led_index > 0) led_index--;
				}
				if(event == ENCODER_PRESS)
				{
					if(led_index == 0) menu = MENU_LED_SWITCH;
					else if (led_index == 1) menu = MENU_LED_BRIGHTNESS;
					else menu = MENU_MAIN;
				}
			break;
					
			case MENU_LED_SWITCH:
				if(event == ENCODER_CW)
				{
					if(led_switch_index < 2) led_switch_index++;
				}
				if(event == ENCODER_CCW)
				{
					if(led_switch_index > 0) led_switch_index--;
				}
				if(event == ENCODER_PRESS)
				{
					if(led_switch_index == 0)
					{
						__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,999);
						ccr3 = 999;
						menu = MENU_LED;
					}
					else if(led_switch_index == 1)
					{
						__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,0);
						ccr3 = 0;
						menu = MENU_LED;
					}						
					else menu = MENU_LED;
				}
			break;
			
			case MENU_LED_BRIGHTNESS:
				if(event == ENCODER_CW)
				{
					if(led_brightness_index < 1) led_brightness_index++;
				}
				if(event == ENCODER_CCW)
				{
					if(led_brightness_index > 0) led_brightness_index--;
				}
				if(event == ENCODER_PRESS)
				{
					if(led_brightness_index == 0) menu = MENU_LED_BRIGHTNESS_CCR3;
					if(led_brightness_index == 1) menu = MENU_LED;
				}
			break;
				
			case MENU_LED_BRIGHTNESS_CCR3:
				if(edit_mode == 0)//选择模式
				{
					if(event == ENCODER_CW)
					{
						if(led_brightness_ccr3_index < 1) led_brightness_ccr3_index++;
					}
					if(event == ENCODER_CCW)
					{
						if(led_brightness_ccr3_index > 0) led_brightness_ccr3_index--;
					}
					if(event == ENCODER_PRESS)
					{
						if(led_brightness_ccr3_index == 0) edit_mode = 1;//进入编辑模式
						else menu = MENU_LED_BRIGHTNESS;
					}
				}
				else
				{
					if(event == ENCODER_CW)
					{
						if(ccr3 < 950) ccr3 += 50;
						else ccr3 = 999;
						__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,ccr3);
					}
					if(event == ENCODER_CCW)
					{
						if(ccr3 >= 50) ccr3 -= 50;
						else ccr3 = 0;
						__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,ccr3);
					}
					if(event == ENCODER_PRESS)
					{
						edit_mode = 0;//退出编辑模式
					}
				}
				break;
		}
}

void menuDisplay()
{
		switch(menu)
		{
			case MENU_MAIN:
				oledShowString(0,0,"MAIN MENU   ");
				if(main_index == 0)
				{
					oledShowString(2,0,"> LED CTRL  ");
					oledShowString(4,0,"  MOTOR CTRL");
					oledShowString(6,0,"            ");
				}
				else
				{
					oledShowString(2,0,"  LED CTRL  ");
					oledShowString(4,0,"> MOTOR CTRL");
					oledShowString(6,0,"            ");
				 }
			break;
			
			case MENU_LED:
				oledShowString(0,0,"LED CTRL    ");
				if(led_index == 0) 
				{
					oledShowString(2,0,"> STATE     ");
					oledShowString(4,0,"  BRIGHTNESS");
					oledShowString(6,0,"  BACK      ");
				}
				else if(led_index == 1)
				{
					oledShowString(2,0,"  STATE     ");
					oledShowString(4,0,"> BRIGHTNESS");
					oledShowString(6,0,"  BACK      ");
				}
				else
				{						
					oledShowString(2,0,"  STATE     ");
					oledShowString(4,0,"  BRIGHTNESS");
					oledShowString(6,0,"> BACK      ");
				}
			break;
			
			case MENU_LED_SWITCH:
				oledShowString(0,0,"STATE       ");
				if(led_switch_index == 0)
				{
					oledShowString(2,0,"> ON        ");
					oledShowString(4,0,"  OFF       ");
					oledShowString(6,0,"  BACK      ");
				}
				else if(led_switch_index == 1) 
				{
					oledShowString(2,0,"  ON        ");
					oledShowString(4,0,"> OFF       ");
					oledShowString(6,0,"  BACK      ");
				}
							
				else
				{
					oledShowString(2,0,"  ON        ");
					oledShowString(4,0,"  OFF       ");
					oledShowString(6,0,"> BACK      ");
				}
				break;
				
			case MENU_LED_BRIGHTNESS:
				oledShowString(0,0,"BRIGHTNESS  ");
				if(led_brightness_index == 0)
				{	
					oledShowString(2,0,"> CCR3:     ");
					oledShowNum(2,64,ccr3);
					oledShowString(4,0,"  BACK      ");
					oledShowString(6,0,"            ");
				}
				else
				{	
					oledShowString(2,0,"  CCR3:     ");
					oledShowNum(2,64,ccr3);
					oledShowString(4,0,"> BACK      ");
					oledShowString(6,0,"            ");
				}	
			break;
				
			case MENU_LED_BRIGHTNESS_CCR3:
				if(edit_mode) oledShowString(0,0,"CCR3***     ");
				else oledShowString(0,0,"CCR3        ");
				if(led_brightness_ccr3_index == 0)
				{
					oledShowString(2,0,"> VALUE:    ");
					oledShowString(4,0,"  BACK      ");
				}
				else
				{
					oledShowString(2,0,"  VALUE:    ");
					oledShowString(4,0,"> BACK      ");
				}
					oledShowNum(2,72,ccr3);
			break;
		}
}
