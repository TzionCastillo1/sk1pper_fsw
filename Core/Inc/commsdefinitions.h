#ifndef COMMSDEFINITIONS_H
#define COMSSDEFINITIONS_H

#ifdef __cplusplus
extern "C" {
#endif /** __cplusplus */

#include "stdint.h"

/** -------------------- Packet Definition ----------- */
typedef struct comms_packet_t
{
    uint8_t start; // Start byte marker -> 0x3F
    uint8_t len; // Length of payload
    uint16_t seq; // Sequence of packet
    uint32_t millis; //time since boot (ms)
    uint8_t payloadid; // ID representing the type of message
    uint8_t payload[32]; // data payload -> encoded message
    uint16_t checksum; // TBDuint8_t start;
} comms_packet_t;

/** --------------------- Message Definitions -------- */

typedef struct comms_msg_heartbeat_t
{
    uint8_t system_mode;
    uint8_t system_state;
} comms_msg_heartbeat_t;

typedef struct comms_msg_sys_status_t
{
    uint16_t sensor_health;
    uint16_t v_battery;
    uint8_t packet_loss_rate;
} comms_msg_sys_status_t;

typedef struct comms_msg_attitude_t
{
    float roll;
    float pitch;
    float yaw;
    float pitchrate;
    float yawrate;
    float rollrate;
} comms_msg_attitude_t;

typedef struct local_position_ned_t
{
    float x;
    float y;
    float z;
    float xrate;
    float yrate;
    float zrate;
} local_position_ned_t;


/** --------------------- Command Definitions -------- */

/** -------------------- Enum Definitions ------------ */
typedef enum comms_payload_id_t
{
    HEARTBEAT,
    SYS_STATUS,
    ATTITUDE,
    LOCAL_POSITION_NED,
    FLIGHT_STATUS,
    CMD_ABORT = 64, /** Commands start at id 64 */
    CMD_ARM_DISARM,
    CMD_TAKEOFF,
    CMD_LAND
} comms_payload_id_t;

typedef enum sys_arm_t
{
    SYS_ARM,
    SYS_DISARM
} sys_arm_t;

/**
typedef enum sys_mode_t
{

} sys_mode_t;
*/

Could all of these states be represented through a bit mask?

XXXXXXXX

typedef sys_state_t
{
    SYS_DISARMED = ,
    SYS_ARMED
} sys_state_t;

typedef sys_arm_substate_t
{
    SYS_STANDBY,
    SYS_FLIGHT
} sys_arm_substate_t;

typedef sys_flight_substate_t
{
    SYS_TAKEOFF,
    SYS_HOVER,
    SYS_LAND
} sys_flight_substate_t;


#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** COMMSDEFINITIONS_H */