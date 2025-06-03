#ifndef DEBUG_H
#define DEBUG_H

#ifdef __cplusplus 
extern "C" {
#endif /** __cplusplus */


void debug_init();

void debug_flash();

void debug_error();

void startDebugTask();

#ifdef __cplusplus 
}
#endif /** __cplusplus */

#endif /** DEBUG_H */