#ifndef SYSTEM_EVENTS_H
#define SYSTEM_EVENTS_H

typedef enum sys_event_id_t
{
    SYS_EVENT_ARM,
    SYS_EVENT_DISARM,
    SYS_EVENT_PARAM_CHANGED
} sys_event_id_t;

typedef enum gnc_event_id_t
{
    GNC_EVENT_SENSOR_UPDATE,
    GNC_EVENT_CNTRL_TICK,
    GNC_EVENT_SYSTEM,
} gnc_event_id_t;

typedef struct gnc_event_t
{
    gnc_event_id_t id;
    union 
    {
        parameter_t parameter;
        sensor_data_t sensor;
        sys_event_id_t sys;
    } data;
     
} gnc_event_t;

#endif // SYSTEM_EVENTS_H