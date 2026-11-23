cmake_minimum_required(VERSION 3.20)

project(lgt92 LANGUAGES C ASM)

set(APP_DIR "${PROJECT_SOURCE_DIR}/Projects/Multi/Applications/LoRa/DRAGINO-LRWAN(AT)")
set(HAL_DIR "${PROJECT_SOURCE_DIR}/Drivers/STM32L0xx_HAL_Driver")
set(CMSIS_DEVICE_DIR "${PROJECT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32L0xx")
set(BSP_COMPONENTS_DIR "${PROJECT_SOURCE_DIR}/Drivers/BSP/Components")
set(LORA_DIR "${PROJECT_SOURCE_DIR}/Middlewares/Third_Party/Lora")
set(LINKER_SCRIPT "${APP_DIR}/gcc/gcc-stm32l072cz.ld")

add_executable(lgt92
    "${APP_DIR}/src/at.c"
    "${APP_DIR}/src/bsp.c"
    "${APP_DIR}/src/command.c"
    "${APP_DIR}/src/debug.c"
    "${APP_DIR}/src/hw_gpio.c"
    "${APP_DIR}/src/hw_rtc.c"
    "${APP_DIR}/src/hw_spi.c"
    "${APP_DIR}/src/lora.c"
    "${APP_DIR}/src/main.c"
    "${APP_DIR}/src/stm32l0xx_hal_msp.c"
    "${APP_DIR}/src/stm32l0xx_hw.c"
    "${APP_DIR}/src/stm32l0xx_it.c"
    "${APP_DIR}/src/tiny_sscanf.c"
    "${APP_DIR}/src/tiny_vsnprintf.c"
    "${APP_DIR}/src/vcom.c"

    "${BSP_COMPONENTS_DIR}/flash_eraseprogram/flash_eraseprogram.c"
    "${BSP_COMPONENTS_DIR}/gpio_exti/gpio_exti.c"
    "${BSP_COMPONENTS_DIR}/gps/gps.c"
    "${BSP_COMPONENTS_DIR}/iwdg/iwdg.c"
    "${BSP_COMPONENTS_DIR}/IIC/IIC.c"
    "${BSP_COMPONENTS_DIR}/filter/filter.c"
    "${BSP_COMPONENTS_DIR}/mpu9250/mpu9250.c"
    "${BSP_COMPONENTS_DIR}/sx1276/sx1276.c"
    "${BSP_COMPONENTS_DIR}/usart/bsp_usart2.c"
    "${PROJECT_SOURCE_DIR}/Drivers/BSP/STM32L0xx_Nucleo/stm32l0xx_nucleo.c"
    "${PROJECT_SOURCE_DIR}/Drivers/BSP/sx1276mb1las/sx1276mb1las.c"

    "${CMSIS_DEVICE_DIR}/Source/Templates/system_stm32l0xx.c"
    "${CMSIS_DEVICE_DIR}/Source/Templates/gcc/startup_stm32l072xx.s"

    "${HAL_DIR}/Src/stm32l0xx_hal.c"
    "${HAL_DIR}/Src/stm32l0xx_hal_adc.c"
    "${HAL_DIR}/Src/stm32l0xx_hal_adc_ex.c"
    "${HAL_DIR}/Src/stm32l0xx_hal_cortex.c"
    "${HAL_DIR}/Src/stm32l0xx_hal_dma.c"
    "${HAL_DIR}/Src/stm32l0xx_hal_flash.c"
    "${HAL_DIR}/Src/stm32l0xx_hal_flash_ex.c"
    "${HAL_DIR}/Src/stm32l0xx_hal_gpio.c"
    "${HAL_DIR}/Src/stm32l0xx_hal_i2c.c"
    "${HAL_DIR}/Src/stm32l0xx_hal_i2c_ex.c"
    "${HAL_DIR}/Src/stm32l0xx_hal_iwdg.c"
    "${HAL_DIR}/Src/stm32l0xx_hal_pwr.c"
    "${HAL_DIR}/Src/stm32l0xx_hal_pwr_ex.c"
    "${HAL_DIR}/Src/stm32l0xx_hal_rcc.c"
    "${HAL_DIR}/Src/stm32l0xx_hal_rcc_ex.c"
    "${HAL_DIR}/Src/stm32l0xx_hal_rtc.c"
    "${HAL_DIR}/Src/stm32l0xx_hal_rtc_ex.c"
    "${HAL_DIR}/Src/stm32l0xx_hal_spi.c"
    "${HAL_DIR}/Src/stm32l0xx_hal_tim.c"
    "${HAL_DIR}/Src/stm32l0xx_hal_tim_ex.c"
    "${HAL_DIR}/Src/stm32l0xx_hal_uart.c"
    "${HAL_DIR}/Src/stm32l0xx_hal_uart_ex.c"

    "${LORA_DIR}/Mac/LoRaMac.c"
    "${LORA_DIR}/Mac/LoRaMacCrypto.c"
    "${LORA_DIR}/Mac/region/Region.c"
    "${LORA_DIR}/Mac/region/RegionCommon.c"
    "${LORA_DIR}/Mac/region/RegionEU868.c"
    "${LORA_DIR}/Core/lora-test.c"
    "${LORA_DIR}/Utilities/delay.c"
    "${LORA_DIR}/Utilities/low_power_manager.c"
    "${LORA_DIR}/Utilities/queue.c"
    "${LORA_DIR}/Utilities/timeServer.c"
    "${LORA_DIR}/Utilities/trace.c"
    "${LORA_DIR}/Utilities/utilities.c"
    "${LORA_DIR}/Crypto/aes.c"
    "${LORA_DIR}/Crypto/cmac.c"
)

target_include_directories(lgt92 PRIVATE
    "${APP_DIR}/inc"
    "${PROJECT_SOURCE_DIR}/Drivers/BSP/STM32L0xx_Nucleo"
    "${HAL_DIR}/Inc"
    "${CMSIS_DEVICE_DIR}/Include"
    "${PROJECT_SOURCE_DIR}/Drivers/CMSIS/Include"
    "${BSP_COMPONENTS_DIR}/Common"
    "${BSP_COMPONENTS_DIR}/sx1276"
    "${PROJECT_SOURCE_DIR}/Drivers/BSP/sx1276mb1las"
    "${BSP_COMPONENTS_DIR}/flash_eraseprogram"
    "${BSP_COMPONENTS_DIR}/gpio_exti"
    "${BSP_COMPONENTS_DIR}/iwdg"
    "${BSP_COMPONENTS_DIR}/filter"
    "${BSP_COMPONENTS_DIR}/gps"
    "${BSP_COMPONENTS_DIR}/mpu9250"
    "${BSP_COMPONENTS_DIR}/IIC"
    "${BSP_COMPONENTS_DIR}/usart"
    "${LORA_DIR}/Crypto"
    "${LORA_DIR}/Mac"
    "${LORA_DIR}/Mac/region"
    "${LORA_DIR}/Phy"
    "${LORA_DIR}/Utilities"
    "${LORA_DIR}/Core"
)

target_compile_definitions(lgt92 PRIVATE
    STM32L072xx
    USE_STM32L0XX_NUCLEO
    USE_HAL_DRIVER
    USE_SHT
    REGION_EU868
)

target_link_options(lgt92 PRIVATE
    -mcpu=cortex-m0plus
    -mthumb
    --specs=nano.specs
    --specs=nosys.specs
    -Wl,--gc-sections
    "-T${LINKER_SCRIPT}"
    "-Wl,-Map=${CMAKE_BINARY_DIR}/lgt92.map"
)
target_link_libraries(lgt92 PRIVATE m)

set_target_properties(lgt92 PROPERTIES
    OUTPUT_NAME lgt92
    SUFFIX .elf
    LINK_DEPENDS "${LINKER_SCRIPT}"
)

add_custom_command(TARGET lgt92 POST_BUILD
    COMMAND "${CMAKE_OBJCOPY}" -O ihex "$<TARGET_FILE:lgt92>" "${CMAKE_BINARY_DIR}/lgt92.hex"
    COMMENT "Generating Intel HEX image"
    VERBATIM
)
