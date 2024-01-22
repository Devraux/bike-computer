aux_source_directory(. DIR_LCD_SRCS3)

add_library(user_data ${DIR_LCD_SRCS3})

include_directories(../LCD_lib/Config)
include_directories(../LCD_lib/GUI)
include_directories(../LCD_lib/LCD)
include_directories(../LCD_lib/Fonts)
include_directories(../bmp280)

target_link_libraries(user_data PUBLIC Config GUI LCD Fonts pico_stdlib hardware_irq hardware_gpio hardware_rtc bmp280)