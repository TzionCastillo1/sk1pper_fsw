/**
 * @file flightmanager.h
 * @author Tzion Castillo (tzionmcastillo@gmail.com)
 * @brief This module is responsible for handling the high level flight control.
 * @version 0.1
 * @date 2026-01-10
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef FLIGHTMANAGER_H
#define FLIGHTMANAGER_H

#include "stdbool.h"
#include "stdint.h"

/** return values for functions */
typedef enum flight_state_t
{
    FM_STATUS_OK = 0,
    FM_STATUS_ERROR,
    FM_STATUS_INVALID_STATE,
    FM_STATUS_PREARM_FAILED,
    FM_STATUS_SAFETY_VIOLATION,
    FM_STATUS_MODE_UNSUPPORTED   
} FlightManager_Status_t;

typedef enum
{
    FM_MODE_MANUAL = 0,
    FM_MODE_STABILIZE,
    FM_MODE_AUTO,
    FM_MODE_LAND
} FlightManager_Mode_t;

typedef struct
{
    bool armed;
    FlightManager_Mode_t mode;
    bool ready_to_arm;
    uint32_t flight_time_ms;
    bool is_flying;
} FlightManager_State_t;


/**
 * @brief Initialize the flight manager 
 * 
 * Must be called once at startup before any other flight manager functions.
 * Initializes internal states and performs system checks.
 * 
 * @return FM_STATUS_OK on success
 */
FlightManager_Status_t FlightManager_init();

/**
 * @brief Arm/Disarm the flight manager
 * 
 * Attempts to arm/disarm the flight manager. 
 * Performs pre-arm checks for healthy attitude, telemetry link, and battery voltage
 * 
 * @return FM_STATUS_OK on success, FM_STATUS_PREARM_FAILED on failure
 */
FlightManager_Status_t FlightManager_set_armed();

/**
 * @brief Set the flight manager mode
 * 
 * Attempt to set the flight manager mode via the flight manager state machine.
 * Transitions may be dependent on state of armed of the vehicle.
 * 
 * @return  FM_STATUS_OK on success 
 *          FM_STATUS_MODE_UNSUPPORTED for invalid state
 *          FM_STATUS_INVALID_STATE for unallowed transition
 */
FlightManager_Status_t FlightManager_set_mode();

/**
 * @brief Immediately stop flight
 * 
 * Disable all actuators immediately.
 * This is a safety function that bypasses disarm logic
 * 
 */
void FlightManager_e_stop();

/**
 * @brief Start the current mission
 * 
 * Attempts to start the current mission.
 * Checks for armed state of vehicle.
 * 
 * @return  FM_STATUS_OK on success
 *          FM_STATUS_INVALID_STATE for disarmed vehicle
 */
FlightManager_Status_t FlightManager_start_mission();

/**
 * @brief Report the current state of the vehicle
 * 
 * Returns a copy of the vehicles current state.
 * Can be called from any context
 * 
 * @param state Pointer to struct to fill with current state
 * 
 * @return FM_STATUS_OK
 */
FlightManager_Status_t FlightManager_get_state(FlightManager_State_t *state);

/** move these ones to the c file, should be private */
FlightManager_Status_t FlightManager_push_event();

typedef enum flight_events_t
{
    FLIGHT_EVENT_FAULT = -1
} flight_events_t;

#endif /** FLIGHTMANAGER_H */