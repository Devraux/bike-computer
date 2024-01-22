# include "buttons_init.h"

void buttons_init()
{
    stdio_init_all();

    gpio_init(left_button); // left button
    gpio_set_dir(left_button, GPIO_IN);
    gpio_pull_up(left_button);    


    gpio_init(right_button); // right button
    gpio_set_dir(right_button, GPIO_IN);
    gpio_pull_up(right_button);


    gpio_init(menu_button); //mode button
    gpio_set_dir(menu_button, GPIO_IN);
    gpio_pull_up(menu_button);


    gpio_init(mag_sensor); //magnetic sensor
    gpio_set_dir(mag_sensor, GPIO_IN);
    gpio_pull_up(mag_sensor);

    gpio_init(LCD_Backlight); //LCD TFT Backlight
    gpio_set_dir(LCD_Backlight, GPIO_OUT);
    gpio_put(LCD_Backlight, 1); // turn on LCD display default

    gpio_init(left_flasher); //LCD TFT Backlight
    gpio_set_dir(left_flasher, GPIO_OUT);
    gpio_put(left_flasher, 0); // turn on LCD display default

    gpio_init(right_flasher); //LCD TFT Backlight
    gpio_set_dir(right_flasher, GPIO_OUT);
    gpio_put(right_flasher, 0); // turn on LCD display default
}