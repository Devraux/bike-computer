#include "GUI_Paint.h"
#include "pico/stdlib.h" 
#include "LCD_1in8.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/rtc.h"
#include "pico.h"
#include <stdio.h>
#include "stdbool.h"

#define left_button 16
#define menu_button 3
#define right_button 2

void button_handler(); //button handler => interrupt handler
float bike_init(uint16_t *Buffer); // bike wheel size initialization, 
void time_init(uint16_t *Buffer); // user's time initialization
void display_guide(uint16_t *Buffer); // user guide
void disable_irq(); //disable irq from buttons 
uint16_t *lcd_init(); //lcd init