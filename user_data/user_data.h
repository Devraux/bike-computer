#include "GUI_Paint.h"
#include "pico/stdlib.h" 
#include "LCD_1in8.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "pico.h"
#include <stdio.h>
#include "hardware/rtc.h"

float velocity(float wheel_size, uint32_t lap_time);
float kcal(float distance);
float distance(uint32_t laps,float wheel_size);
uint8_t cadence(uint8_t laps);
void Paint_Screen1(uint16_t *Buffer, float velocity, float distance, uint8_t kcal, uint8_t cadence);
void Paint_Screen2(uint16_t *Buffer,int32_t temperature, int32_t pressure, float altitude);




