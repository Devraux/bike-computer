Author: Krzysztof Plonka
Date: 22.12.2023

Description:
This program is a bike computer that allows the user to measure:
- velocity
- distance
- current time and data 
- pressure
- kcal
- trip distance
- current cadence
- altitude
- LED flasher

This program is also a project from the TM2 lecture.

Project files and document description:
- bmp280: contains bmp280 sensor functions and allows measuring pressure and temperature
- buttons_init: contains button initialization instructions, 
- LCD_lib: contains the LCD library and enables operation of the LCD
- user_data: includes conversion functions and functions for displaying data on the screen
- user_init: allows to initialize user data like wheel diameter, time, data, and display also short user manual
- main.c: consolidates the call of all functions in one place 

![IMG20240120202152](https://github.com/Devraux/bike-computer/assets/121176761/0fca0b99-7f20-473f-bb3b-6f96e107f0dc)

