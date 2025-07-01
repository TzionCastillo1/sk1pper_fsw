#ifndef LOG_H
#define LOG_H

#ifdef __cplusplus 
extern "C" {
#endif /** __cplusplus */

typedef enum log_level_t
{
    LOG_NONE,
    LOG_ERROR,
    LOG_INFO,
    LOG_VERBOSE
} log_level_t;

void log_init();

void log_flash();

void log_error();

void log_set_verbosity(log_level_t desired_log_level);

void startlogTask();

#ifdef __cplusplus 
}
#endif /** __cplusplus */

#endif /** log_H */