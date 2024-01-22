#include <stdio.h>
#include "pico.h"
#include "hardware/gpio.h"

#define left_button 16   //left button
#define menu_button 3    //menu button
#define right_button 2   //right button
#define mag_sensor 7     //magnetic velocity sensor
#define LCD_Backlight 17 //TFT LCD backlight
#define left_flasher 18  //left diode flasher => turn left
#define right_flasher 19 //right diode flasher => turn right

void buttons_init(); // button initialization func