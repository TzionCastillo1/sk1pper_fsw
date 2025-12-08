#include "unity.h"
#include "example.h"

void setUp(void)
{}

void tearDown(void)
{}

void test_addTwoInts(void)
{
    TEST_ASSERT_EQUAL_INT(40, addTwoInts(30, 10));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_addTwoInts);
    return UNITY_END();
}