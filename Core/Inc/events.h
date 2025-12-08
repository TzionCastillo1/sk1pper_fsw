#ifndef EVENTS_H
#define EVENTS_H

#ifdef __cplusplus
extern "C" {
#endif /** __plusplus */

typedef enum event_t
{
    EVT_IDLE,
    EVT_ENTRY,
    EVT_EXIT,
    EVT_GO,
    EVT_NOGO,
    EVT_ARM,
    EVT_DISARM,
    EVT_LAUNCH,
    EVT_LAND,
    EVT_HOVER,
    EVT_LANDED,
} event_t;

#ifdef __cplusplus
}
#endif /** __plusplus */

#endif /** EVENTS_H */