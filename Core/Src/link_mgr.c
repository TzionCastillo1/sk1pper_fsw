#include "link_mgr.h"
#include "link_mgr_cmd.h"
#include "param_mgr.h"
#include "ringbuff.h"
#include "mavlink.h"
#include "sensor_mgr.h"
#include "stm32f405_SpeedyBee.h"
#include "printf/printf.h"
//#include "usart.h"

//Support up to 4x full length messages
#define LM_UART_BUFF_LEN (MAVLINK_MAX_PACKET_LEN * 4)
#define PERIOD_TICK_5HZ (200)
#define PERIOD_TICK_1HZ (1000)


//static BSP_link_mgr_tx_func_t link_mgr_tx_func;

static char uart_rxbuff[LM_UART_BUFF_LEN];
static ringbuff_t uart_ringbuff;

static char uart_txbuff[LM_UART_BUFF_LEN];


send_params_sm_t send_params_sm =
{
    .idle = true,
    .idx = 0,
    .param_count = -1,
    .expiration_time = 0,
    .delay_ticks = PERIOD_TICK_5HZ,
};

error_t link_mgr_init()
{
    //BSP_link_mgr_tx_func = func;
    return ringbuff_init(&uart_ringbuff, uart_rxbuff, sizeof(uart_rxbuff));
}

error_t link_mgr_send_imu_scaled()
{
    uint8_t system_id = 42;
    uint8_t base_mode = 0;
    uint8_t custom_mode = 0;
    mavlink_message_t message;
    sensor_data_t data;
    sensormgr_get_all(&data);
    float gyro[3];
    float acc[3];

    sensormgr_get_acc(acc);
    sensormgr_get_gyro(gyro);
    mavlink_msg_scaled_imu_pack_chan(
    system_id,
    MAV_COMP_ID_AUTOPILOT1,
    MAVLINK_COMM_0,
    &message,
    0,//TODO: Create system time,
    (int16_t)(data.acc[0] * GS_TO_MGS),
    (int16_t)(data.acc[1] * GS_TO_MGS),
    (int16_t)(data.acc[2] * GS_TO_MGS),
    (int16_t)(data.gyro[0] * DPS_TO_MRADS),
    (int16_t)(data.gyro[1] * DPS_TO_MRADS),
    (int16_t)(data.gyro[2] * DPS_TO_MRADS),
    0,
    0,
    0,
    69.69420//TODO: IMU temperature
    );

    int len = mavlink_msg_to_send_buffer(uart_txbuff, &message);
    //synchronous tx should prevent us from overwritting buffer mid transmission
    //int status = HAL_UART_Transmit(&huart4, uart_txbuff, len, 100);
    int status = BSP_link_mgr_tx_func(uart_txbuff, len);
    return status;
}

error_t link_mgr_send_alt()
{
    float alt;
    float alt_at_boot;
    uint8_t system_id = 42;
    uint8_t base_mode = 0;
    uint8_t custom_mode = 0;
    mavlink_message_t message;

    sensormgr_get_baro_alt(&alt);
    mavlink_msg_altitude_pack_chan(
    system_id,
    MAV_COMP_ID_AUTOPILOT1,
    MAVLINK_COMM_0,
    &message,
    0,//TODO: Create system time,
    alt_at_boot,
    0,
    alt,
    -9999, /** TODO: Make an 'unknown' constant */
    -9999,
    -9999
    );      
    int len = mavlink_msg_to_send_buffer(uart_txbuff, &message);
    //synchronous tx should prevent us from overwritting buffer mid transmission
    //int status = HAL_UART_Transmit(&huart4, uart_txbuff, len, 100);
    int status = BSP_link_mgr_tx_func(uart_txbuff, len);
}

error_t link_mgr_send_heartbeat()
{
    uint8_t system_id = 42;
    uint8_t base_mode = 0;
    uint8_t custom_mode = 0;
    mavlink_message_t message;

    mavlink_msg_heartbeat_pack_chan(
    system_id,
    MAV_COMP_ID_AUTOPILOT1,
    MAVLINK_COMM_0,
    &message,
    MAV_TYPE_GENERIC,
    MAV_AUTOPILOT_GENERIC,
    base_mode,
    custom_mode,
    MAV_STATE_STANDBY
    );
    const int len = mavlink_msg_to_send_buffer(uart_txbuff, &message);
    //int status = HAL_UART_Transmit(&huart4, uart_txbuff, len, 100);
    int status = BSP_link_mgr_tx_func(uart_txbuff, len);
}

error_t link_mgr_rx_msg_process()
{
    mavlink_message_t new_msg;
    mavlink_status_t channel_status;
    uint8_t new_char;
    error_t status;

    while (ringbuff_pop(&uart_ringbuff, &new_char))
    {
        //Returns a 1 on succesful decoding
        if(mavlink_parse_char(MAVLINK_COMM_0, new_char, &new_msg, &channel_status))
        {
            //Debugg by sending to CLI
            //printf_("message id: %d", new_msg.msgid);
            //insert dispatcher code here
            // Check if we have reached the end of the table
            for(int idx = 0; lm_cmd_table[idx].id != LINK_MGR_END_OF_TABLE; idx++)
            {
                if (new_msg.msgid == lm_cmd_table[idx].id)
                {
                    lm_cmd_table[idx].execute(&new_msg);
                }
            }
        }
    }
}

error_t link_mgr_tx_msgs(uint32_t time_delta_ticks)
{
    error_t status = ERROR_OK;
    /******** Insert 10Hz code **************/
    if(status = link_mgr_send_params(time_delta_ticks)) return status;

    /******** Insert 5Hz code ***************/
    if((time_delta_ticks) % PERIOD_TICK_5HZ == 0)
    {
      /************** Scaled IMU Message ********************/
      if(status = link_mgr_send_imu_scaled()) return status; 
      /************** Altitude Message ********************/
      if(status = link_mgr_send_alt()) return status;
    }
    
    /******** Insert 1Hz code ***************/
    if((time_delta_ticks) % PERIOD_TICK_1HZ == 0)
    {
        if(status = link_mgr_send_heartbeat()) return status;
    }
    return status;
}

error_t link_mgr_send_params(uint32_t time_delta_ticks)
{
    error_t status = ERROR_OK;
    send_params_sm.param_count = param_mgr_get_count();
    if (send_params_sm.idle || (time_delta_ticks < send_params_sm.expiration_time))
    {
        return status;
    }
    else
    {
        /** TODO:
         * package
         * transmit
         * update expiration time
         * increment index
         * check for last index
         */
        char param_key[PARAM_KEY_MAX_LENGTH];
        float param_val;
        uint8_t system_id = 42;
        uint8_t base_mode = 0;
        uint8_t custom_mode = 0;
        mavlink_message_t message;

        if( (status = param_mgr_get_from_idx(send_params_sm.idx, param_key, &param_val)) == ERROR_OK)
        {
            printf_("%s: %f\r\n", param_key, param_val);
            mavlink_msg_param_value_pack_chan(system_id,
                                            MAV_COMP_ID_AUTOPILOT1,
                                            MAVLINK_COMM_0,
                                            &message,
                                            param_key,
                                            param_val,
                                            MAV_PARAM_TYPE_REAL32,
                                            send_params_sm.param_count,
                                            send_params_sm.idx);
            send_params_sm.expiration_time = time_delta_ticks + send_params_sm.delay_ticks;
            send_params_sm.idx++;
            if(send_params_sm.idx >= send_params_sm.param_count)
            {
                send_params_sm.idle = true;
                send_params_sm.idx = 0;
            }
            const int len = mavlink_msg_to_send_buffer(uart_txbuff, &message);
            //int tx_status = HAL_UART_Transmit(&huart4, uart_txbuff, len, 100);
            int status = BSP_link_mgr_tx_func(uart_txbuff, len);
        }
        else
        {
            printf_("Error Retrieving Parameters\r\n");
        }
        return status;
    }
}

void link_mgr_byte_received(char new_byte)
{
    //simply throw the byte into the ring buffer
    ringbuff_push(&uart_ringbuff, new_byte);
}