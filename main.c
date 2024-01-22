#include "LCD_1in8.h"
#include "user_init/user_init.h"
#include "buttons_init/buttons_init.h"
#include "user_data/user_data.h"
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/rtc.h"
#include "hardware/gpio.h"
#include "bmp280.h"
#include "stdbool.h"

bool disp_mode = true; //display mode button => change display
uint8_t moment_laps = 0; //temporary laps couter => reset every 1 sec
uint32_t total_laps = 0; //total laps counter to get precise distance
uint32_t lap_time = 0; //one turn of the wheel time [ms]
float trip_distance = 0; 
uint8_t trip_kcal = 0;
uint8_t trip_cadence = 0;
float wheel_size = 0; //[meters]
float velocity_val = 0; // velocity value
int32_t temperature = 0; 
int32_t pressure = 0;
int32_t raw_temperature; //MBP280 calibrate temperature parameter
int32_t raw_pressure; //BMP280 calibrate pressure parameter
float altitude = 0; //altitude [m] => meters above sea level
struct bmp280_calib_param params; //calibration structure BMP280 
uint32_t last_mag_sens_time = 0; //debouncing => magnetic sensor
uint32_t last_button_press_time = 0; //debouncing => left, mode and right buttons
bool left_diode_flag = false; // left diode flag 1 - flasher active, 0 - flasher inactive
bool right_diode_flag = false; //right diode flag 1 - flasher active, 0 - flasher inactive
bool diode_state = true; //current LED diode state
uint8_t diode_blink_counter = 0;

void interrupt_handler() //magnetic sensor handler
{   
    uint32_t current_time = (us_to_ms(time_us_32()));
    if(gpio_get(mag_sensor) == 0 && (current_time - last_mag_sens_time > 200))
    {
        moment_laps++;
        total_laps++;
        lap_time = current_time - last_mag_sens_time; //one bike wheel lap time
        last_mag_sens_time = current_time;
    }

    if(gpio_get(menu_button) == 0 && (current_time - last_button_press_time > 200))
    {
        disp_mode = !disp_mode;
        last_button_press_time = current_time;
    }

    if(gpio_get(left_button) == 0 && (current_time - last_button_press_time > 200)) //blink left diode
    {
        left_diode_flag = true;
        last_button_press_time = current_time;
    }

    if(gpio_get(right_button) == 0 && (current_time - last_button_press_time > 200)) //blink right diode
    {
        right_diode_flag = true;
        last_button_press_time = current_time;
    }
}

bool sec_handler(struct repeating_timer *t) // 1 sec handler
{
    trip_distance = distance(total_laps,wheel_size);
    trip_kcal = kcal(trip_distance);
    trip_cadence = cadence(moment_laps);

    bmp280_read_raw(&raw_temperature, &raw_pressure);
    velocity_val = velocity(wheel_size, lap_time); // get valocity function
    temperature = bmp280_convert_temp(raw_temperature, &params);
    pressure = bmp280_convert_pressure(raw_pressure, raw_temperature, &params);
    altitude = bmp280_altitude(pressure);

    if((us_to_ms(time_us_32()) - last_mag_sens_time) > 2000) // user stopped => reset velocity val
        velocity_val = 0;

    if((us_to_ms(time_us_32()) - last_mag_sens_time) > 180000) //sleep mode after 3 minutes inactivity => turn off LCD 
        gpio_put(LCD_Backlight, 0);
    
    else
        gpio_put(LCD_Backlight, 1);
    
    if((left_diode_flag == true) && (diode_blink_counter <= 10))
    {
        gpio_put(left_flasher, diode_state);
        diode_state = !diode_state;
        diode_blink_counter++;
        if(diode_blink_counter >= 10)
        {
            left_diode_flag = false; 
            diode_blink_counter = 0;
        }
    }

    if((right_diode_flag == true) && (diode_blink_counter <= 10))
    {
        gpio_put(right_flasher, diode_state);
        diode_state = !diode_state; 
        diode_blink_counter++;
        if(diode_blink_counter >= 10)
        {
            right_diode_flag = false;
            diode_blink_counter = 0;
        }
    }
    moment_laps = 0; // reset laps
    return true;
    
}

int main(void)
{   
    uint16_t *Buffer = lcd_init(); //spi buffer and lcd initialization
    if (Buffer == NULL) {
        return -1;
    }
    buttons_init(); //initialize buttons 
    bmp_init(); //initialize bmp 
    bmp280_get_calib_params(&params); //get BMP280 calibration parameters
    wheel_size = bike_init(Buffer); //initialize user settings
    time_init(Buffer); //user's time initialize
    struct repeating_timer t; //time management and cyclic function calls

    add_repeating_timer_ms(1000, sec_handler, NULL, &t); //execute every 1 sec
    gpio_set_irq_enabled_with_callback(mag_sensor, GPIO_IRQ_EDGE_FALL, true, &interrupt_handler); //magnitude sensor irq
    gpio_set_irq_enabled_with_callback(menu_button, GPIO_IRQ_EDGE_FALL, true, &interrupt_handler); //mode button irq
    gpio_set_irq_enabled_with_callback(left_button, GPIO_IRQ_EDGE_FALL, true, &interrupt_handler); //left button irq
    gpio_set_irq_enabled_with_callback(right_button, GPIO_IRQ_EDGE_FALL, true, &interrupt_handler); //right button irq

    while(1)
    {
        if(disp_mode)
        {
            Paint_Screen1(Buffer, velocity_val, trip_distance, trip_kcal, trip_cadence);
        }
        else if(!disp_mode)
        {
            Paint_Screen2(Buffer, temperature, pressure, altitude);
        }
    }

    free(Buffer); //free up memory
    return 0;
}