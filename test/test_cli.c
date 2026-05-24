#include "unity.h"

#include "cli.h"
#include "cli_cmd_stubs.h"
#include "ringbuff.h"

//Including the mock so that no cmd_table is built to prevent multiple definitions errors
#include "mock_cli_cmd.h"
//#include "mock_ring_buff.h"

TEST_SOURCE_FILE("Core/Src/cli_cmd.c")

void setUp()
{
    cli_stub_reset();
}

void tearDown()
{

}

//Invoker tests
void test_cli_invokes_set()
{
    int argc = 1;
    char *argv[] = {"set"};
    printf("%s", argv[0]);

    cli_invoker(argc, argv);
    TEST_ASSERT_TRUE(cli_stub_set_called);
}

void test_cli_invokes_get()
{
    int argc = 2;
    char *argv[] = {"get", "batt_voltage"};
    printf("%s", argv[0]);

    cli_invoker(argc, argv);
    TEST_ASSERT_TRUE(cli_stub_get_called);

}

void test_cli_invokes_help()
{
    int argc = 1;
    char *argv[] = {"help"};
    printf("%s", argv[0]);

    cli_invoker(argc, argv);
    TEST_ASSERT_TRUE(cli_stub_help_called);

}

void test_cli_invokes_nothing()
{
    int argc = 1;
    char *argv[] = {"selfdestruct"};
    printf("%s", argv[0]);

    cli_invoker(argc, argv);
    TEST_ASSERT_FALSE(cli_stub_help_called);
    TEST_ASSERT_FALSE(cli_stub_get_called);
    TEST_ASSERT_FALSE(cli_stub_set_called);
}

//tokenizer tests
void test_cli_tokenizer_single_token()
{
    char input[] = "help";
    char *argv[CLI_MAX_ARGS];
    int argc = cli_tokenizer(input, argv);

    TEST_ASSERT_EQUAL_STRING("help", argv[0]);
    TEST_ASSERT_EQUAL_INT32(1, argc);
}

void test_cli_tokenizer_double_token()
{
    char input[] = "get battery_voltage";
    char *argv[CLI_MAX_ARGS];
    int argc = cli_tokenizer(input, argv);

    TEST_ASSERT_EQUAL_STRING("get", argv[0]);
    TEST_ASSERT_EQUAL_STRING("battery_voltage", argv[1]);
    TEST_ASSERT_EQUAL_INT32(2, argc);
}

void test_cli_tokenizer_eight_token()
{
    char input[] = "0 1 2 3 4 5 6 7";
    char *argv[CLI_MAX_ARGS];
    int argc = cli_tokenizer(input, argv);

    TEST_ASSERT_EQUAL_STRING("0", argv[0]);
    TEST_ASSERT_EQUAL_STRING("1", argv[1]);
    TEST_ASSERT_EQUAL_STRING("2", argv[2]);
    TEST_ASSERT_EQUAL_STRING("3", argv[3]);
    TEST_ASSERT_EQUAL_STRING("4", argv[4]);
    TEST_ASSERT_EQUAL_STRING("5", argv[5]);
    TEST_ASSERT_EQUAL_STRING("6", argv[6]);
    TEST_ASSERT_EQUAL_STRING("7", argv[7]);
    TEST_ASSERT_EQUAL_INT32(8, argc);
}

void test_cli_tokenizer_nine_token()
{
    char input[] = "0 1 2 3 4 5 6 7 8";
    char *argv[CLI_MAX_ARGS];
    int argc = cli_tokenizer(input, argv);

    TEST_ASSERT_EQUAL_STRING("0", argv[0]);
    TEST_ASSERT_EQUAL_STRING("1", argv[1]);
    TEST_ASSERT_EQUAL_STRING("2", argv[2]);
    TEST_ASSERT_EQUAL_STRING("3", argv[3]);
    TEST_ASSERT_EQUAL_STRING("4", argv[4]);
    TEST_ASSERT_EQUAL_STRING("5", argv[5]);
    TEST_ASSERT_EQUAL_STRING("6", argv[6]);
    TEST_ASSERT_EQUAL_STRING("7", argv[7]);
    TEST_ASSERT_EQUAL_INT32(8, argc);
}

/** Ring buffer processing */
void test_cli_char_rcvr()
{
    cli_init();
    char input[] = "test strinf\bg!\r";
    for (int idx = 0; idx < strlen(input); idx++)
    {
        cli_char_received(input[idx]);
    }

    char line[256];
    cli_ringbuff_to_str(line);
    TEST_ASSERT_EQUAL_STRING("test string!", line);
}