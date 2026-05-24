#include "unity.h"

#include "ringbuff.h"

uint8_t buffer[255];
ringbuff_t ringbuff;

void setUp()
{
    ringbuff_init(&ringbuff, buffer, 255);
}

void tearDown()
{

}

void test_push_once()
{
    ringbuff_push(&ringbuff, 222);
    TEST_ASSERT_EQUAL_UINT8(222, buffer[0]);
}

void test_push_push_pop_push()
{
    ringbuff_push(&ringbuff, 222);
    ringbuff_push(&ringbuff, 223);
    uint8_t popped;
    ringbuff_pop(&ringbuff, &popped);
    ringbuff_push(&ringbuff, 224);
    TEST_ASSERT_EQUAL_UINT8(222, popped);
    TEST_ASSERT_EQUAL_UINT8(223, buffer[1]);
    TEST_ASSERT_EQUAL_UINT8(224, buffer[2]);

}

void test_push_push_pop_push_char()
{
    ringbuff_push(&ringbuff, 'H');
    ringbuff_push(&ringbuff, 'e');
    uint8_t popped;
    ringbuff_pop(&ringbuff, &popped);
    ringbuff_push(&ringbuff, 'y');
    TEST_ASSERT_EQUAL_CHAR('H', popped);
    TEST_ASSERT_EQUAL_CHAR('e', buffer[1]);
    TEST_ASSERT_EQUAL_CHAR('y', buffer[2]);

}