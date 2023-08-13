cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(firmware C CXX ASM)
set(CMAKE_C_STANDARD 17)

add_executable(app
    main.c
    )

pico_sdk_init()

# create map/bin/hex file etc.
pico_add_extra_outputs(app)

pico_enable_stdio_usb(app 0)
pico_enable_stdio_uart(app 1)

# pull in common dependencies
target_link_libraries(firmware pico_stdlib)
