#ifndef LINK_MGR_H
#define LINK_MGR_H

#include "mavlink.h"
#include "errors.h"
#include "stdint.h"

#define LINK_MGR_END_OF_TABLE (-1)

typedef struct link_mgr_cmd_t
{
    uint32_t id;
    void (*execute)(mavlink_message_t *msg);
}link_mgr_cmd_t;

typedef struct send_params_sm_t
{
    bool idle;
    int idx;
    int param_count;
    int expiration_time;
    int delay_ticks;
} send_params_sm_t;

extern send_params_sm_t send_params_sm;

typedef error_t (*link_mgr_tx_func_t)(char *data, uint16_t len);

/**
 * @brief Initialize the link manager 
 * 
 * @return error_t 
 */
error_t link_mgr_init();

/**
 * @brief send scaled imu message 
 * 
 * @param acc array containing accelerometer values [x, y, z] 
 * @param gyro array containing gyro values [x, y, z]
 * @return error_t 
 */
error_t link_mgr_send_imu_scaled();

/**
 * @brief send altitude message 
 * 
 * @param alt 
 * @return error_t 
 */
error_t link_mgr_send_alt();

/** TODO: */
error_t link_mgr_send_att();

/**
 * @brief sends parameter with name key 
 * 
 * @param key name of parameter to be sent 
 * @return error_t 
 */
error_t link_mgr_send_param(char *key);

/**
 * @brief Send Heartbeat message 
 * 
 * @return error_t 
 */
error_t link_mgr_send_heartbeat();

/**
 * @brief process data currently in internal buffer, calls message handler if
 * applicable
 * 
 * @return error_t 
 */
error_t link_mgr_rx_msg_process();

/**
 * @brief send periodic messages accordign to outbound message time table 
 * 
 * @param time_delta_ticks
 * @return error_t 
 */
error_t link_mgr_tx_msgs(uint32_t time_delta_ticks);

/**
 * @brief Provide the Send Params state machine with the latest tick time.
 * If in the transmit state, this will trigger a parameter transmission
 * after the delay time is reached 
 * 
 * @param time_ticks system time in ticks
 * @return error_t 
 */
error_t link_mgr_send_params(uint32_t time_delta_ticks);

/**
 * @brief callback function to be called from UART receive IRQ 
 * 
 * @param new_byte byte to be added to internal buffer
 */
void link_mgr_byte_received(char new_byte);

#endif /** LINK_MGR_H */