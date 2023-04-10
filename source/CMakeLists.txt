cmake_minimum_required(VERSION 3.15)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico-bin)

pico_sdk_init()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Set the build type (Debug or Release)
set(CMAKE_BUILD_TYPE Debug)

# Set the Pico SDK build type
set(PICO_DEFAULT_BUILD_TYPE Debug)

add_executable(sample main.cpp sensor_test.cpp)

set(FREERTOS_CFG_DIRECTORY "${CMAKE_SOURCE_DIR}/config")
set(FREERTOS_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/../library/freeRTOS")

# Add FreeRTOS as a library
add_library(FreeRTOS STATIC
    ${FREERTOS_SRC_DIRECTORY}/event_groups.c
    ${FREERTOS_SRC_DIRECTORY}/list.c
    ${FREERTOS_SRC_DIRECTORY}/queue.c
    ${FREERTOS_SRC_DIRECTORY}/stream_buffer.c
    ${FREERTOS_SRC_DIRECTORY}/tasks.c
    ${FREERTOS_SRC_DIRECTORY}/timers.c
    ${FREERTOS_SRC_DIRECTORY}/portable/MemMang/heap_3.c
    ${FREERTOS_SRC_DIRECTORY}/portable/GCC/ARM_CM0/port.c
)

# Build FreeRTOS
target_include_directories(FreeRTOS PUBLIC
    ${FREERTOS_CFG_DIRECTORY}/
    ${FREERTOS_SRC_DIRECTORY}/include
    ${FREERTOS_SRC_DIRECTORY}/portable/GCC/ARM_CM0
)

pico_enable_stdio_usb(sample 1)
pico_enable_stdio_uart(sample 1)
pico_add_extra_outputs(sample)

target_link_libraries(sample FreeRTOS pico_stdlib)
