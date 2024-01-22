# include "user_data.h"

float velocity(float wheel_size, uint32_t lap_time)
{  
    float lap_time_sec = lap_time / 1000.0f; //ms to sec conversion
    float velocity = (3.14 * wheel_size) / lap_time_sec; //velocity formula
    velocity = velocity * 3.6; // km/h conversion
    return velocity;
}

float kcal(float distance)
{
    // Burned Calories = average burned callories per 1km => small hills, flat terrain
    float kcal = 0;
    kcal = distance * 25;
    return kcal; //per 1 meter 
}

float distance(uint32_t laps,float wheel_size)
{
    float distance = 0;
    distance = 3.14 * laps * wheel_size; // distance = 2 * 3.14 * r * 1/2 => (1/2) because r is radios of the circle 
    distance = distance * 0.001; // m => km
    return distance; // km
}

uint8_t cadence(uint8_t laps)
{
    return laps; //cadence
}

void Paint_Screen1(uint16_t *Buffer, float velocity, float distance, uint8_t kcal, uint8_t cadence)
{
    Paint_Clear(GRAY);
    Paint_DrawString_EN(18,1,"Velocity:",&Font16,WHITE,GRAY);
    Paint_DrawNum(5,20,velocity,&Font24,1,GBLUE,GRAY);
    Paint_DrawString_EN(80,25,"km/h",&Font16,WHITE,GRAY);

    Paint_DrawString_EN(18,50,"Distance:",&Font16,WHITE,GRAY);
    Paint_DrawNum(1,65,distance,&Font24,2,GBLUE,GRAY);
    Paint_DrawString_EN(105,70,"km",&Font16,WHITE,GRAY);

    Paint_DrawString_EN(1,100,"kcal:",&Font16,WHITE,GRAY);
    Paint_DrawNum(5,120,kcal,&Font24,0,GBLUE,GRAY);

    Paint_DrawString_EN(75,100,"Cad.:",&Font16,WHITE,GRAY);
    Paint_DrawNum(80,120,cadence,&Font24,0,GBLUE,GRAY);

    LCD_1IN8_Display(Buffer);
}

void Paint_Screen2(uint16_t *Buffer, int32_t temperature, int32_t pressure,float altitude)
{
    datetime_t current_datetime;
    rtc_get_datetime(&current_datetime);

    Paint_Clear(GRAY);
    Paint_DrawString_EN(40,1,"Time:",&Font16,WHITE,GRAY);
    Paint_DrawNum(9,19,current_datetime.hour,&Font24,0,GBLUE,GRAY);
    Paint_DrawString_EN(41,22,":",&Font16,WHITE,GRAY);
    Paint_DrawNum(49,19,current_datetime.min,&Font24,0,GBLUE,GRAY);
    Paint_DrawString_EN(80,22,":",&Font16,WHITE,GRAY);
    Paint_DrawNum(89,19,current_datetime.sec,&Font24,0,GBLUE,GRAY);

    Paint_DrawString_EN(40,40,"Date:",&Font16,WHITE,GRAY);
    Paint_DrawNum(17,58,current_datetime.day,&Font16,0,GBLUE,GRAY);
    Paint_DrawString_EN(37,57,":",&Font16,WHITE,GRAY);
    Paint_DrawNum(45,58,current_datetime.month,&Font16,0,GBLUE,GRAY);
    Paint_DrawString_EN(65,57,":",&Font16,WHITE,GRAY);
    Paint_DrawNum(72,58,current_datetime.year,&Font16,0,GBLUE,GRAY);

    Paint_DrawString_EN(1,80,"Pres:",&Font16,WHITE,GRAY);
    Paint_DrawNum(1,100,pressure/100,&Font16,0,GBLUE,GRAY);

    float temperature_float = temperature / 100.0f;
    Paint_DrawString_EN(70,80,"Temp:",&Font16,WHITE,GRAY);
    Paint_DrawNum(75,100,temperature_float,&Font16,1,GBLUE,GRAY);

    Paint_DrawString_EN(20,120,"Altitude",&Font16,WHITE,GRAY);
    Paint_DrawNum(35,140,altitude,&Font16,1,GBLUE,GRAY);

    LCD_1IN8_Display(Buffer);
}