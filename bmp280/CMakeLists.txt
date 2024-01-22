aux_source_directory(. DIR_LCD_SRCS4)

add_library(bmp280 ${DIR_LCD_SRCS4})

target_link_libraries(bmp280 PUBLIC pico_stdlib hardware_i2c) 