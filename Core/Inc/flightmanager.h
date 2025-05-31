#ifndef FLIGHTMANAGER_H
#define FLIGHTMANAGER_H

typedef enum flight_state_t
{
    FLIGHT_STATE_DISARMED = 0    
} flight_state_t;

typedef enum flight_events_t
{
    FLIGHT_EVENT_FAULT = -1
} flight_events_t;

void flightmanager_init();

void flightmanager_start();

flight_state_t flightmanager_get_state();

void flightmanager_push_event();

#endif /** FLIGHTMANAGER_H */