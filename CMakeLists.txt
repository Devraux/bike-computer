cmake_minimum_required(VERSION 3.27.4)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(bike_computer C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(LCD_lib/Config)
add_subdirectory(LCD_lib/Infrared)
add_subdirectory(LCD_lib/Icm20948)
add_subdirectory(LCD_lib/LCD)
add_subdirectory(LCD_lib/Fonts)
add_subdirectory(LCD_lib/GUI)
add_subdirectory(user_init)
add_subdirectory(buttons_init)
add_subdirectory(user_data)
add_subdirectory(bmp280)

include_directories(./LCD_lib/Config)
include_directories(./LCD_lib/GUI)
include_directories(./LCD_lib/Icm20948)
include_directories(./LCD_lib/LCD)
include_directories(./LCD_lib/Infrared)
include_directories(./user_init)
include_directories(./buttons_init)
include_directories(./user_data)
include_directories(./bmp280)

add_executable(${PROJECT_NAME} 
    main.c
)

# enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} LCD Config pico_stdlib hardware_spi hardware_timer hardware_irq hardware_gpio hardware_rtc user_init buttons_init user_data bmp280)
