#include "ant_hrm_rx.h"
ble_hrs_t                        m_hrs; 
static uint8_t                          m_ant_network_key[] = ANT_HRMRX_NETWORK_KEY; /**< ANT PLUS network key. */
//ble_hrs_t                        m_hrs;  

/**@brief Start receiving the ANT HRM data.
 */
void ant_hrm_rx_start(void)
{
    uint32_t err_code = sd_ant_channel_open(ANT_HRMRX_ANT_CHANNEL);
    APP_ERROR_CHECK(err_code);
}

/**@brief Initialize the ANT HRM reception.
 */
void ant_hrm_rx_init(void)
{
    uint32_t err_code;
    
    err_code = sd_ant_network_address_set(ANTPLUS_NETWORK_NUMBER, m_ant_network_key);
    APP_ERROR_CHECK(err_code);
    
    err_code = sd_ant_channel_assign(ANT_HRMRX_ANT_CHANNEL,
                                     ANT_HRMRX_CHANNEL_TYPE,
                                     ANTPLUS_NETWORK_NUMBER,
                                     ANT_HRMRX_EXT_ASSIGN);
    APP_ERROR_CHECK(err_code);

    err_code = sd_ant_channel_id_set(ANT_HRMRX_ANT_CHANNEL,
                                     ANT_HRMRX_DEVICE_NUMBER,
                                     ANT_HRMRX_DEVICE_TYPE,
                                     ANT_HRMRX_TRANS_TYPE);
    APP_ERROR_CHECK(err_code);
    
    err_code = sd_ant_channel_radio_freq_set(ANT_HRMRX_ANT_CHANNEL, ANTPLUS_RF_FREQ);
    APP_ERROR_CHECK(err_code);
    
    err_code = sd_ant_channel_period_set(ANT_HRMRX_ANT_CHANNEL, ANT_HRMRX_MSG_PERIOD);
    APP_ERROR_CHECK(err_code);
}

/**@brief Handle received ANT data message.
 * 
 * @param[in]  p_evt_buffer   The buffer containing received data. 
 */
void ant_data_messages_handle(uint8_t * p_evt_buffer)
{
    static uint32_t s_previous_beat_count = 0;    // Heart beat count from previously received page
    uint32_t        err_code;
    uint32_t        current_page;
    uint8_t         beat_count;
    uint8_t         computed_heart_rate;
    uint16_t        beat_time;

    // Decode the default page data present in all pages
    beat_time           = uint16_decode(&p_evt_buffer[ANT_BUFFER_INDEX_MESG_DATA + 4]);
    beat_count          = (uint8_t)p_evt_buffer[ANT_BUFFER_INDEX_MESG_DATA + 6];
    computed_heart_rate = (uint8_t)p_evt_buffer[ANT_BUFFER_INDEX_MESG_DATA + 7];

    // Decode page specific data
    current_page = p_evt_buffer[ANT_BUFFER_INDEX_MESG_DATA];
    switch (current_page & ~ANT_HRM_TOGGLE_MASK)
    {
        case ANT_HRM_PAGE_4:
            // Ensure that there is only one beat between time intervals.
            if ((beat_count - s_previous_beat_count) == 1)
            {
                uint16_t prev_beat = uint16_decode(&p_evt_buffer[ANT_BUFFER_INDEX_MESG_DATA + 2]);
                
                // Subtracting the event time gives the R-R interval
                ble_hrs_rr_interval_add(&m_hrs, beat_time - prev_beat);
            }

            s_previous_beat_count = beat_count;
            break;
          
        case ANT_HRM_PAGE_0:
        case ANT_HRM_PAGE_1:
        case ANT_HRM_PAGE_2:
        case ANT_HRM_PAGE_3:
        default:
            // No implementation needed.
            break;
    }
    
    // Notify the received heart rate measurement
    err_code = ble_hrs_heart_rate_measurement_send(&m_hrs, computed_heart_rate);
    if (
        (err_code != NRF_SUCCESS)
        &&
        (err_code != NRF_ERROR_INVALID_STATE)
        &&
        (err_code != BLE_ERROR_NO_TX_BUFFERS)
        &&
        (err_code != BLE_ERROR_GATTS_SYS_ATTR_MISSING)
    )
    {
        APP_ERROR_HANDLER(err_code);
    }
}


/**@brief ANT RX event handler.
 *
 * @param[in]   p_ant_evt   Event received from the stack.
 */
void on_ant_evt_rx(ant_evt_t * p_ant_evt)
{
    uint32_t message_id = p_ant_evt->evt_buffer[ANT_BUFFER_INDEX_MESG_ID];

    switch (message_id)
    {
        case MESG_BROADCAST_DATA_ID:
        case MESG_ACKNOWLEDGED_DATA_ID:
            ant_data_messages_handle(p_ant_evt->evt_buffer);
            break;

        default:
            // No implementation needed.
            break;
    }
}


/**@brief ANT CHANNEL_CLOSED event handler.
 */
void on_ant_evt_channel_closed(void)
{
#ifdef BONDING_ENABLE
    uint32_t err_code;
    uint32_t count;

    // We do not have any activity on the radio at this time, so it is safe to store bonds
    err_code = ble_bondmngr_bonded_centrals_store();
    APP_ERROR_CHECK(err_code);

    err_code = pstorage_access_status_get(&count);
    if ((err_code == NRF_SUCCESS) && (count == 0))
#endif // BONDING_ENABLE
    {        
        storage_access_complete_handler();
    }
}


/**@brief Application's Stack ANT event handler.
 *
 * @param[in]   p_ant_evt   Event received from the stack.
 */
void on_ant_evt(ant_evt_t * p_ant_evt)
{
    if (p_ant_evt->channel == ANT_HRMRX_ANT_CHANNEL)
    {
        switch (p_ant_evt->event)
        {
            case EVENT_RX:
                on_ant_evt_rx(p_ant_evt);
                break;

            case EVENT_CHANNEL_CLOSED:
                on_ant_evt_channel_closed();
                break;

            default:
                // No implementation needed.
                break;
        }
    }
}


