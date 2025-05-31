#include "unity.h"
#include "dispatcher.h"


void setUp()
{
}

void tearDown()
{

}

/**
 * What does a subscriber look like? 
 * 
 */
void test_RegisterSubscriberWithTopic()
{

    dispatcher_add_subscriber(&subscriber_queue_handle, msg_id);

}

void test_DeregisterSubscriberWithTopic()
{

}

void test_RouteMessage()
{

}

int main()
{
    /**
     * TODO: Implement the following test list:
     * Register subscribers with topics
     * Deregister subscribers with topics
     * Route a message to a subscriber
     * Do nothing when an unsupported message has been received
     * Add to the a subscriber's queue when a complete, supported message has been received 
     */

    UNITY_BEGIN();
    return UNITY_END();
}