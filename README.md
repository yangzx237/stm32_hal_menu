# STM32 OLED Encoder Menu

This project implements a simple multi-level menu system using STM32 and an OLED display.

## Hardware

MCU: STM32F103C8T6  
Display: SSD1306 OLED (I2C interface)  
Input: HW-040 rotary encoder  

## Project

The project is based on STM32 HAL and created with STM32CubeMX and Keil MDK.

Main components in the project:

Core  
- main.c: program entry  
- menu.c / menu.h: menu system implementation  
- oled.c / oled.h: SSD1306 OLED driver  
- encoder.c / encoder.h: rotary encoder driver  
- font8x16.c / font8x16.h: 8x16 ASCII font

Drivers  
- CMSIS  
- STM32F1xx HAL Driver

The rotary encoder is used to navigate and operate the menu, and the OLED displays the menu interface.
