#ifndef MAIN_H__
#define MAIN_H__
#include <stdint.h>
#include <string.h>
#include "nordic_common.h"
#include "nrf.h"
#include "app_error.h"
#include "nrf_gpio.h"
#include "nrf51_bitfields.h"
#include "ble.h"
#include "ble_hci.h"
#include "ble_srv_common.h"
#include "ble_advdata.h"
#include "ble_hrs.h"
#include "ble_dis.h"
#include "ble_conn_params.h"
#include "boards.h"
#include "ble_sensorsim.h"
#include "softdevice_handler.h"
#include "app_timer.h"
#include "ble_bondmngr.h"
#include "ble_flash.h"
#include "ble_debug_assert_handler.h"
#include "ant_parameters.h"
#include "ant_interface.h"

#define ANT_HRMRX_ANT_CHANNEL           0                                            /**< Default ANT Channel. */



void storage_access_complete_handler(void);
void ant_hrm_rx_start(void);
void ant_hrm_rx_init(void);
void on_ant_evt(ant_evt_t *p_ant_evt);
#endif

