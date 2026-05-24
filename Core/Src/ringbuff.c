#include "ringbuff.h"
#include "string.h"


uint8_t ringbuff_init(ringbuff_t *ringbuff, uint8_t *buff, uint32_t size)
{
    ringbuff->head = 0;
    ringbuff->tail = 0;
    ringbuff->size = size;
    ringbuff->buff = buff;
}

uint8_t ringbuff_pop(ringbuff_t *ringbuff, uint8_t *val)
{
    uint8_t ret = 0;
    if (ringbuff->head < ringbuff->tail)
    {
        ret = 1;
        if (val != NULL)
        {
            *val = ringbuff->buff[ringbuff->head];
        }
        ringbuff->head = (ringbuff->head + 1) % ringbuff->size;
    }
    return ret;
}

uint8_t ringbuff_pop_tail(ringbuff_t *ringbuff, uint8_t *val)
{
    uint8_t ret = 0;
    //Don't pop from the tail if there is nothing in the buffer 
    //(head and tail are the same)
    if (ringbuff->head != ringbuff->tail)
    {
        ret = 1;
        if (val != NULL)
        {
            *val = ringbuff->buff[ringbuff->tail-1];
        }
        ringbuff->tail = (ringbuff->tail - 1) % ringbuff->size;
    }
    return ret;
}

uint8_t ringbuff_push(ringbuff_t *ringbuff, uint8_t val)
{
    uint8_t ret = 0;
    if ( ( (ringbuff->tail + 1) % ringbuff->size) != ringbuff->head)
    {
        ringbuff->buff[ringbuff->tail] = val;
        ringbuff->tail = (ringbuff->tail + 1) % ringbuff->size;
    }
}