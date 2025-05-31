#include "flightmanager.h"

static flight_state_t flight_state;

void flightmanager_init()
{
    flight_state = FLIGHT_STATE_DISARMED;
}

void flightmanager_start()
{

}

flight_state_t flightmanager_get_state()
{
    return flight_state;
}

void flightmanager_push_event()
{
    flight_state = FLIGHT_STATE_DISARMED;
}
