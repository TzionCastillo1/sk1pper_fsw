#include "unity.h"
#include "hermescodec.h"
#include "hermesdefinitions.h"
#include "stdio.h"
#include "string.h"

void setUp(void)
{}

void tearDown(void)
{}

/*
void test_hermesEncodeDecodePacket(void)
{
    hermes_msg_attitude_t startAttitudeMsg = 
    {
        .roll = 1.0,
        .pitch = 1.0,
        .yaw = 3.8,
    };

    hermes_packet_t testPacket;

    hermesPackPayload(&testPacket, &startAttitudeMsg, sizeof(startAttitudeMsg), HERMES_ID_ATTITUDE, 1000);

    uint8_t hermesBuff[64];
    hermesSerializePacket(&testPacket, hermesBuff, sizeof(hermesBuff));

    hermes_packet_t hermesNewPacket;
    int newPacket = 0;
    
    while (!newPacket)
    {
        newPacket = hermesParseByte(hermesBuff[index], &hermesNewPacket)
    }


}
    */

void test_hermesSerializePacketmemcpy(void)
{
    hermes_packet_t testPacket = {
        .start = 0x3F,
        .len = sizeof(hermes_msg_attitude_t),
        .seq = 1,
        .millis = 1000,
        .payloadID = HERMES_ID_ATTITUDE,
        .payload = {0},
        .checksum = 0xFFFF,
    };

    hermes_msg_attitude_t attitudeMsg = 
    {
        .pitch = 1.0,
        .roll = 1.0,
    };

    memcpy(testPacket.payload, &attitudeMsg, sizeof(hermes_msg_attitude_t));

    uint8_t expectedArray[] = {0, 0, 0x80, 0x3F};

    for (int index = 0; index < 8; index++)
    {
        printf("%u\n", testPacket.payload[index]);
    }

    TEST_ASSERT_EQUAL_UINT8_ARRAY(expectedArray, testPacket.payload, 4);

}

void test_hermesEncodeDecode(void)
{
    hermes_packet_t testPacket;
    hermes_msg_heartbeat_t heartbeat = {0, SYS_STATE_ARMED};
    
    hermesPackPayload(&testPacket, &heartbeat, sizeof(heartbeat), HERMES_ID_HEARTBEAT, 100);

    uint8_t txBufferLength = 64;
    uint8_t txBuffer[txBufferLength];
    hermesSerializePacket(&testPacket, txBuffer, txBufferLength);

    hermes_packet_t recvPacket = {0};
    uint8_t systemMode;
    for (int index = 0; index < sizeof(heartbeat) + 11; index++)
    {
        if(hermesParseByte(txBuffer[index], &recvPacket))
        {
            switch(recvPacket.payloadID)
            {
                case(HERMES_ID_HEARTBEAT):
                    systemMode = recvPacket.payload[0];
            }
        }
    }

    //TEST_ASSERT_EQUAL(0 ,systemMode);
    TEST_ASSERT_EQUAL(HERMES_ID_HEARTBEAT, recvPacket.payloadID);
    TEST_ASSERT_EQUAL(100, recvPacket.millis);
    //TEST_ASSERT_EQUAL(heartbeat.system_state, SYS_STATE_ARMED);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_hermesEncodeDecode);
    RUN_TEST(test_hermesSerializePacketmemcpy);
    return UNITY_END();
}