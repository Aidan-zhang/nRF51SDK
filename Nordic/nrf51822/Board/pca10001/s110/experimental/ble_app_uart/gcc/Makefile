
# check the TARGET_CHIP and BOARD
TARGET_CHIP := NRF51822_QFAA_CA
BOARD := BOARD_PCA10001


# check CFAGS remove extra -DNRF51 -DDEBUG_NRF_USER
CFLAGS += -DNRF51822_QFAA_CA
CFLAGS += -DBOARD_PCA10001 -DNRF51 -DDEBUG_NRF_USER, -DBLE_STACK_SUPPORT_REQD

C_SOURCE_FILES += main.c
C_SOURCE_FILES += ../ble_nus.c
C_SOURCE_FILES += ../../../../../../Source/app_common/app_timer.c
C_SOURCE_FILES += ../../../../../../Source/ble/ble_advdata.c
C_SOURCE_FILES += ../../../../../../Source/ble/ble_conn_params.c
C_SOURCE_FILES += ../../../../../../Source/ble/ble_services/ble_srv_common.c
C_SOURCE_FILES += ../../../../../../Source/sd_common/softdevice_handler.c
C_SOURCE_FILES += ../../../../../../Source/ble/ble_debug_assert_handler.c
C_SOURCE_FILES += ../../../../../../Source/ble/ble_sensorsim.c
#C_SOURCE_FILES += ../../../../../../Source/simple_uart/simple_uart.c

INCLUDEPATHS += -I"../../../../../../Include/app_common"
INCLUDEPATHS += -I"../../../../../../Include/ble"
INCLUDEPATHS += -I"../../../../../../Include/ble/ble_services"
INCLUDEPATHS += -I"../../../../../../Include/s110"
INCLUDEPATHS += -I"../../../../../../Include/sd_common"

OUTPUT_FILENAME := ble_app_uart_gcc

SDK_PATH = ../../../../../../

DEVICE_VARIANT := xxaa
#DEVICE_VARIANT := xxab

USE_SOFTDEVICE := S110
#USE_SOFTDEVICE := s210

include $(SDK_PATH)Source/templates/gcc/Makefile.common

