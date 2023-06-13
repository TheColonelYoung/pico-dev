file(GLOB_RECURSE ALOHAL_SOURCES "ALOHAL/*")

add_library(alohal ${ALOHAL_SOURCES})

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

target_include_directories(alohal PUBLIC ALOHAL)

set(FPU_FLAGS "-mfloat-abi=hard -mfpu=fpv4-sp-d16")
set(MCU_FLAGS "-mcpu=cortex-m4 ${FPU_FLAGS} -mthumb -mthumb-interwork -ffunction-sections -fdata-sections -g -fno-common -fmessage-length=0 -specs=nosys.specs -specs=nano.specs -u _printf_float")

set(CMAKE_C_FLAGS "${MCU_FLAGS}")

target_compile_definitions(alohal PUBLIC
    ${MCU_SHORT_ID}xx
    ${MCU_SERIES}
    USE_HAL_DRIVER
    MCU_FAMILY_STM32_L4
)

target_include_directories(alohal PUBLIC
    ../source/Drivers/CMSIS/Device/ST/${MCU_SERIES}xx/Include
    ../source/Drivers/${MCU_SERIES}xx_HAL_Driver/Inc
    ../source/Drivers/${MCU_SERIES}xx_HAL_Driver/Inc/Legacy
    ../source/Drivers/CMSIS/Include
    ../source/Core/Inc
)
