
# check the TARGET_CHIP and BOARD
TARGET_CHIP := NRF51822_QFAA_CA
BOARD := BOARD_PCA10001


# check CFAGS remove extra -DNRF51 -DDEBUG_NRF_USER
CFLAGS += -DNRF51822_QFAA_CA
CFLAGS += -DNRF51

C_SOURCE_FILES += main.c
C_SOURCE_FILES += ../../../../Source/ext_sensors/ds1624/ds1624.c
C_SOURCE_FILES += ../../../../Source/ext_sensors/synaptics_touchpad/synaptics_touchpad.c
C_SOURCE_FILES += ../../../../Source/nrf_delay/nrf_delay.c
C_SOURCE_FILES += ../../../../Source/twi_master/twi_sw_master.c

INCLUDEPATHS += -I"../../../../Include/ext_sensors"

OUTPUT_FILENAME := twi_sw_master_example_gcc
SDK_PATH = ../../../../../

DEVICE_VARIANT := xxaa
#DEVICE_VARIANT := xxab

USE_SOFTDEVICE := S110
#USE_SOFTDEVICE := s210

include $(SDK_PATH)Source/templates/gcc/Makefile.common
