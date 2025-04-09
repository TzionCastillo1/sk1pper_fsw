#ifndef COMMSCODEC_H
#define COMMSCODEC_H

#ifdef __cplusplus
extern "C" {
#endif /** __cplusplus */

#include "stdint.h"
#include "commsdefinitions.h"

/**
 * @brief Takes in a byte array and decodes it into an over-the-wire packet.
 * @param byteArray byte array to be decoded. 
 * @param decodedPacket destination for the decoded packet
 * 
 */
void commsDecodePacket(uint8_t byteArray);

/**
 * @brief Takes in an over-the-wire packet and turns it into a byte array.
 * @param payload 
 * @param 
 */
void commsEncodePacket();



#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** COMMSCODEC_H */