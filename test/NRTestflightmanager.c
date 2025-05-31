#include "unity.h"
#include "flightmanager.h"

void setUp()
{
    flightmanager_init();
    flightmanager_start();
}

void tearDown()
{

}



void test_SpindownOnFaultAfterSpinup()
{
    flightmanager_push_event(FLIGHT_EVENT_FAULT);
    flight_state_t flight_state = flightmanager_get_state();
    TEST_ASSERT_EQUAL(FLIGHT_STATE_SPINUP, flight_state);
}

void test_DisarmOnFaultBeforeSpinup()
{
    flightmanager_push_event(FLIGHT_EVENT_FAULT);
    flight_state_t flight_state = flightmanager_get_state();
    TEST_ASSERT_EQUAL(FLIGHT_STATE_DISARMED, flight_state);
}

void test_ReturnsState()
{
    flight_state_t flight_state = flightmanager_get_state();
    TEST_ASSERT_EQUAL(FLIGHT_STATE_DISARMED, flight_state);
}

void test_DisarmedAtStartup()
{
    flight_state_t flight_state = flightmanager_get_state();
    TEST_ASSERT_EQUAL(FLIGHT_STATE_DISARMED, flight_state);
}

int main()
{

    UNITY_BEGIN();
    RUN_TEST(test_DisarmedAtStartup);
    RUN_TEST(test_DisarmOnFault);
    /**
     * TODO: Implement the following tests:
     * enter
     * enter spindown phase if fault encountered between spinup and takeoff
     * enter descent phase if fault encountered during flight
     */
    return UNITY_END();
}