#ifndef LINK_MGR_H
#define LINK_MGR_H

#include "mavlink.h"
#include "errors.h"

/**
 * @brief Initialize the link manager 
 * 
 * @return error_t 
 */
error_t link_mgr_init(void);

/**
 * @brief send scaled imu message 
 * 
 * @param acc array containing accelerometer values [x, y, z] 
 * @param gyro array containing gyro values [x, y, z]
 * @return error_t 
 */
error_t link_mgr_send_imu_scaled(float acc[3], float gyro[3]);

/**
 * @brief send altitude message 
 * 
 * @param alt 
 * @return error_t 
 */
error_t link_mgr_send_alt(float alt);

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
 * @brief Sends all params in param list 
 * 
 * @return error_t 
 */
error_t link_mgr_send_params();

/**
 * @brief process data currently in internal buffer, calls message handler if
 * applicable
 * 
 * @return error_t 
 */
error_t link_mgr_process();

/**
 * @brief callback function to be called from UART receive IRQ 
 * 
 * @param new_byte byte to be added to internal buffer
 */
void link_mgr_byte_received(char new_byte);

#endif /** LINK_MGR_H */