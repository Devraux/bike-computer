aux_source_directory(. DIR_LCD_SRCS)

add_library(user_init ${DIR_LCD_SRCS})

include_directories(../LCD_lib/GUI)
include_directories(../LCD_lib/LCD)
include_directories(../LCD_lib/Config)

target_link_libraries(user_init PUBLIC Config GUI LCD pico_stdlib hardware_irq hardware_gpio hardware_rtc)