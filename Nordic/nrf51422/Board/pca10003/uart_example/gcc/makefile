TARGET_CHIP := NRF51822_QFAA_CA
BOARD := BOARD_PCA10003
C_SOURCE_FILES += main.c
C_SOURCE_FILES += simple_uart.c

OUTPUT_FILENAME := uart_example_gcc
SDK_PATH = ../../../../


#Uncomment correct line if you have softdevice programmed on the chip.
DEVICE_VARIANT := xxaa
#DEVICE_VARIANT := xxab

#USE_SOFTDEVICE := S110
#USE_SOFTDEVICE := S210

include $(SDK_PATH)Source/templates/gcc/Makefile.common
