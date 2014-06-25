
# check the TARGET_CHIP and BOARD
TARGET_CHIP := NRF51822_QFAA_CA
BOARD := BOARD_PCA10001


# check CFAGS remove extra -DNRF51 -DDEBUG_NRF_USER
CFLAGS += -DNRF51822_QFAA_CA
CFLAGS += -DBOARD_NRF6310 -DBOOTLOADER_BANKED -DBLE_STACK_SUPPORT_REQD

SDK_PATH = ../../../../../

C_SOURCE_FILES += main.c
C_SOURCE_FILES += ../bootloader.c
C_SOURCE_FILES += ../bootloader_util_gcc.c
C_SOURCE_FILES += ../dfu_dual_bank.c
C_SOURCE_FILES += ../dfu_single_bank.c
C_SOURCE_FILES += ../dfu_transport_ble.c
C_SOURCE_FILES += ../dfu_transport_serial.c
C_SOURCE_FILES += ../../../../../Source/app_common/app_gpiote.c
C_SOURCE_FILES += ../../../../../Source/app_common/app_scheduler.c
C_SOURCE_FILES += ../../../../../Source/app_common/app_timer.c
C_SOURCE_FILES += ../../../../../Source/app_common/app_uart.c
C_SOURCE_FILES += ../../../../../Source/app_common/crc16.c
C_SOURCE_FILES += ../../../../../Source/app_common/hci_mem_pool.c
C_SOURCE_FILES += ../../../../../Source/app_common/hci_slip.c
C_SOURCE_FILES += ../../../../../Source/app_common/hci_transport.c
C_SOURCE_FILES += ../../../../../Source/app_common/pstorage.c
C_SOURCE_FILES += ../../../../../Source/ble/ble_advdata.c
C_SOURCE_FILES += ../../../../../Source/ble/ble_conn_params.c
C_SOURCE_FILES += ../../../../../Source/ble/ble_services/ble_dfu.c
C_SOURCE_FILES += ../../../../../Source/ble/ble_services/ble_srv_common.c
C_SOURCE_FILES += ../../../../../Source/sd_common/softdevice_handler.c

INCLUDEPATHS += -I"../include"
INCLUDEPATHS += -I"../include/ble_transport"
INCLUDEPATHS += -I"../include/hci_transport"
INCLUDEPATHS += -I"../../../../../Include/sd_common"
INCLUDEPATHS += -I"../../../../../Include/app_common"
INCLUDEPATHS += -I"../../../../../Include/ble"
INCLUDEPATHS += -I"../../../../../Include/ble/ble_services"
INCLUDEPATHS += -I"../../../../../Include/s110"

OUTPUT_FILENAME := bootloader_gcc

DEVICE :=NRF51
DEVICE_VARIANT := xxaa
#DEVICE_VARIANT := xxab

USE_SOFTDEVICE := S110
#USE_SOFTDEVICE := s210

include $(SDK_PATH)Source/templates/gcc/Makefile.common

