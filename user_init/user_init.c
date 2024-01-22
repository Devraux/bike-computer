#include "user_init.h"

int8_t mode_switch_counter = 0; // mode switch counter
int8_t user_wheel_size = 0; // wheel size(inches)
int8_t hour = 0; // hour value
int8_t minute = 0; // minute value
int16_t year = 2024; //year value
int8_t month = 1; // month value
int8_t day = 1; //day value
uint32_t last_button_press = 0; //debouncing

void button_handler()
{
  uint32_t current_time = us_to_ms(time_us_32());//debouncing

  if(gpio_get(left_button) == 0 && (current_time - last_button_press > 200))
  {
    user_wheel_size--;
    hour++;
    year--;
    month--;
    day--;

    if (hour >= 24)
      hour = 0;
    if (user_wheel_size < 0)
      user_wheel_size = 0;
    if(month <= 0)
      month = 1;
    if(day <= 0)
      day = 1;
    last_button_press = current_time;
  }

    else if (gpio_get(menu_button) == 0 && (current_time - last_button_press > 200))
    {
      mode_switch_counter++;
      last_button_press = current_time;
    }

    else if (gpio_get(right_button) == 0 && (current_time - last_button_press > 200))
    {
      user_wheel_size++;
      minute++;
      year++;
      month++;
      day++;

      if(minute >= 60)
        minute = 0;
      if(day > 31)
      day = 1;
      if(month > 12)
        month = 1;

      last_button_press = current_time;
    }
}

float bike_init(uint16_t *Buffer)
{
    float wheel_size_inch = 0; 
    Paint_SetScale(65);
    
    gpio_set_irq_enabled_with_callback(left_button, GPIO_IRQ_EDGE_FALL, true, &button_handler);
    gpio_set_irq_enabled_with_callback(menu_button, GPIO_IRQ_EDGE_FALL, true, &button_handler);
    gpio_set_irq_enabled_with_callback(right_button,  GPIO_IRQ_EDGE_FALL, true, &button_handler);

    Paint_Clear(GRAY);
    Paint_DrawString_EN(5,10,"Welcome",&Font24,GBLUE,GRAY);
    LCD_1IN8_Display(Buffer);
    sleep_ms(1000);
    
    while(mode_switch_counter <=1)
    {
      Paint_Clear(GRAY);
      Paint_DrawString_EN(1,1,"Enter your wheel  size(inches):",&Font12,WHITE,GRAY); 
      Paint_DrawString_EN(1,90,"If the diameter ofyour wheel is     already correct   press mode button twice",&Font12,WHITE,GRAY);
      Paint_DrawNum(50,30,user_wheel_size,&Font16,0,GBLUE,GRAY);
      LCD_1IN8_Display(Buffer);
    }

    wheel_size_inch = 0.0254 * user_wheel_size; //conversion from inches to meters
    
    mode_switch_counter = 0; //reset mode counter value

    return wheel_size_inch;
}

void time_init(uint16_t *Buffer)
{
  mode_switch_counter = 0; //reset values
  hour = 0; //reset values
  minute = 0; //reset values
  rtc_init(); // Pi pico RTC initializaition
  datetime_t t; // structure necessary to Pico RTC config


  while(mode_switch_counter <=1) // minute and hour setting
  {
    Paint_Clear(GRAY);
    Paint_DrawString_EN(1,1,"Set the time(left button - hours,   right button -    minutes):",&Font12,WHITE,GRAY); 
    Paint_DrawString_EN(1,110,"If the time is    already correct   press mode button twice",&Font12,WHITE,GRAY);
    Paint_DrawString_EN(1,55,"H:",&Font16,WHITE,GRAY);
    Paint_DrawString_EN(1,70,"M:",&Font16,WHITE,GRAY);
    Paint_DrawNum(40,55,hour,&Font16,0,GBLUE,GRAY);
    Paint_DrawNum(40,70,minute,&Font16,0,GBLUE,GRAY);
    LCD_1IN8_Display(Buffer);
  }

  t.min = minute; //save and set data
  t.hour = hour; //save and set data
  mode_switch_counter = 0;// reset values
  year = 2024; //reset year counter
  
  while(mode_switch_counter <=1)//year setting
  {
    Paint_Clear(GRAY);
    Paint_DrawString_EN(1,1,"Enter year: ",&Font12,WHITE,GRAY); 
    Paint_DrawString_EN(1,110,"If the year is    already correct   press mode button twice",&Font12,WHITE,GRAY);
    Paint_DrawNum(20,20,year,&Font24,0,GBLUE,GRAY);
    LCD_1IN8_Display(Buffer);
  }

  mode_switch_counter = 0; //reset mode conunter
  month = 1; //month reset
  t.year = year; //save and set year

  while(mode_switch_counter <=1)//month setting
  {
    Paint_Clear(GRAY);
    Paint_DrawString_EN(1,1,"Enter month: ",&Font12,WHITE,GRAY);
    Paint_DrawString_EN(1,110,"If the month is   already correct   press mode button twice",&Font12,WHITE,GRAY); 
    Paint_DrawNum(50,20,month,&Font24,0,GBLUE,GRAY);
    LCD_1IN8_Display(Buffer);
  }

  mode_switch_counter = 0; //reset value
  day = 1; //reset value
  t.month = month; //save and set month 


  while(mode_switch_counter <=1) //day setting
  {
    Paint_Clear(GRAY);
    Paint_DrawString_EN(1,1,"Enter day: ",&Font12,WHITE,GRAY);
    Paint_DrawString_EN(1,110,"If the day is     already correct   press mode button twice",&Font12,WHITE,GRAY); 
    Paint_DrawNum(50,20,day,&Font24,0,GBLUE,GRAY);
    LCD_1IN8_Display(Buffer);
  }

  mode_switch_counter = 0;
  t.day = day; //save and set day
  t.dotw = 1; //save and set dotw

  rtc_set_datetime(&t); //set time and data to RTC structure in Pico
  sleep_us(64); // Pi Pico documentation delay required

  display_guide(Buffer); // display short user guide

  disable_irq();// disable irq from buttons
}

void disable_irq()
{
  gpio_set_irq_enabled(left_button, GPIO_IRQ_EDGE_FALL, false); // turn off irq
  gpio_set_irq_enabled(menu_button, GPIO_IRQ_EDGE_FALL, false); // turn off irq
  gpio_set_irq_enabled(right_button, GPIO_IRQ_EDGE_FALL, false); // turn off irq
}

void display_guide(uint16_t *Buffer)
{
  Paint_Clear(GRAY);
  Paint_DrawString_EN(1,1,"Quick user guide: 1. Left button -   turn left signal", &Font12, WHITE, GRAY); 
  Paint_DrawString_EN(1,50,"2. Right button -  turn right signal", &Font12, WHITE, GRAY);
  Paint_DrawString_EN(1,89,"3. Middle button    (mode button)-    switch displays", &Font12, WHITE, GRAY);
  Paint_DrawString_EN(1,129,"4. Press mode button twice to accept",&Font12,WHITE,GRAY);
  LCD_1IN8_Display(Buffer);

  while(mode_switch_counter <=1) // do nothing => wait for user acceptation
  {
    Paint_DrawString_EN(0,0,"",&Font12,GBLUE,GRAY);
    LCD_1IN8_Display(Buffer);
  }
}

uint16_t* lcd_init()
{
  if(DEV_Module_Init()!=0)
  {
    return NULL;
  }
  LCD_1IN8_Init(VERTICAL);
  LCD_1IN8_Clear(GRAY);
  UDOUBLE Imagesize = LCD_1IN8_HEIGHT*LCD_1IN8_WIDTH*2;
  UWORD *Buffer;
  if((Buffer = (UWORD *)malloc(Imagesize)) == NULL)
  {
    exit(0);// exit if makng buffer goes wrong
  }
  Paint_NewImage((UBYTE *)Buffer,LCD_1IN8.WIDTH,LCD_1IN8.HEIGHT, 0, WHITE);
  return Buffer;
}