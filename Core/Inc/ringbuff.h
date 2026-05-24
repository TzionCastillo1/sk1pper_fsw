#ifndef RINGBUFF_H
#define RINGBUFF_H

#include "stdint.h"

typedef struct char_ringbuff_t
{
    uint8_t head;
    uint8_t tail;
    uint32_t size;
    uint8_t *buff;
} ringbuff_t;

uint8_t ringbuff_init(ringbuff_t *ringbuff, uint8_t *buff, uint32_t size);

/**
 * @brief Get the value at the head of the ring buffer and remove that item
 * from the buffer
 * 
 * @param ringbuff ringbuffer handle
 * @return uint8_t 
 */
uint8_t ringbuff_pop(ringbuff_t *ringbuff, uint8_t *val);

/**
 * @brief Pop the tail value
 * 
 * @param ringbuff 
 * @param val 
 * @return uint8_t 
 */
uint8_t ringbuff_pop_tail(ringbuff_t *ringbuff, uint8_t *val);

/**
 * @brief Push a new value to the tail 
 * 
 * @param ringbuff 
 * @param val 
 * @return uint8_t 
 */
uint8_t ringbuff_push(ringbuff_t *ringbuff, uint8_t val);

#endif /* RINGBUFF_H */