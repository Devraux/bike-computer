aux_source_directory(. DIR_LCD_SRCS2)

add_library(buttons_init ${DIR_LCD_SRCS2})

include_directories(../LCD_lib/Config)
include_directories("C:/VSARM/sdk/pico/pico-sdk/src/rp2_common/hardware_gpio")

target_link_libraries(buttons_init PUBLIC pico_stdlib hardware_irq hardware_gpio)