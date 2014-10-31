/* Copyright (c) 2012 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

#include "main_cbsc_tx.h"
#include "cbsc_tx.h"
#include "cbsc_tx_defines.h"
#include "ant_interface.h"
#include "ant_parameters.h"
#include "app_error.h"
#include "nrf_soc.h"
#include "main.h"
#define ANTPLUS_NETWORK_NUMBER        0                   /**< Network number. */
#define ANT_EVENT_MSG_BUFFER_MIN_SIZE 32u                 /**< Minimum size of ANT event message buffer. */

#define CBSC_TX_CHANNEL_TYPE          CHANNEL_TYPE_MASTER /**< Master Channel. */
#define CBSC_TX_TRANS_TYPE            1u                  /**< Transmission Type. */
#define CBSC_TX_DEVICE_NUMBER         1u                  /**< Device Number. */
#define CBSC_EXT_ASSIGN               0                   /**< ANT Ext Assign. */
#define CBSC_DEVICE_TYPE              0x79u               /**< Bike speed and cadence Device Type. */
#define CBSC_RF_FREQ                  0x39u               /**< RF Channel 57 (2457 MHz). */
#define CBSC_MSG_PERIOD               0x1F96u             /**< Decimal 8086 (~4.05Hz). */
#define CBSC_NETWORK_KEY              {0,0,0,0,0,0,0,0}   /**< The network key used. */

static const uint8_t m_network_key[] = CBSC_NETWORK_KEY;  /**< ANT network key. */


/**@brief Function for configuring the ANT channel.
 */
static __INLINE void channel_open(void)
{    
    // Set Network Address.
    uint32_t err_code = sd_ant_network_address_set(ANTPLUS_NETWORK_NUMBER, (uint8_t*)m_network_key);
    APP_ERROR_CHECK(err_code);
    
    // Set Channel Number.
    err_code = sd_ant_channel_assign(CBSC_TX_ANT_CHANNEL, 
                                     CBSC_TX_CHANNEL_TYPE, 
                                     ANTPLUS_NETWORK_NUMBER, 
                                     CBSC_EXT_ASSIGN);
    APP_ERROR_CHECK(err_code);
    
    // Set Channel ID.
    err_code = sd_ant_channel_id_set(CBSC_TX_ANT_CHANNEL, 
                                     CBSC_TX_DEVICE_NUMBER, 
                                     CBSC_DEVICE_TYPE, 
                                     CBSC_TX_TRANS_TYPE);
    APP_ERROR_CHECK(err_code);

    // Set Channel RF frequency.
    err_code = sd_ant_channel_radio_freq_set(CBSC_TX_ANT_CHANNEL, CBSC_RF_FREQ);
    APP_ERROR_CHECK(err_code);

    // Set Channel period.
    err_code = sd_ant_channel_period_set(CBSC_TX_ANT_CHANNEL, CBSC_MSG_PERIOD);
    APP_ERROR_CHECK(err_code);
  
    // Open Channel.
    err_code = sd_ant_channel_open(CBSC_TX_ANT_CHANNEL);
    APP_ERROR_CHECK(err_code);
}


void main_cbsc_tx_run(void)
{
    // Open the ANT channel and initialize the profile module.        
    channel_open();   
    uint32_t err_code = cbsc_tx_initialize();
    APP_ERROR_CHECK(err_code);
    
    uint8_t ant_channel;        
    uint8_t event_message_buffer[ANT_EVENT_MSG_BUFFER_MIN_SIZE];     
    uint8_t event = NO_EVENT;      
    
    // Extract and process all pending events, while maximizing application sleep.     
    for (;;) 
    {             
        err_code = sd_app_evt_wait();
        APP_ERROR_CHECK(err_code);
        
        // Extract and process all pending ANT stack events.
        while (sd_ant_event_get(&ant_channel, &event, event_message_buffer) == NRF_SUCCESS)
        {                    
            err_code = cbsc_tx_channel_event_handle(event);
            APP_ERROR_CHECK(err_code);
        }            
    } 
}


/**@brief Function for handling protocol stack IRQ.
 *
 * Interrupt is generated by the ANT stack upon sending event to the application. 
 */
//void SD_EVT_IRQHandler(void)
//{
     
//}