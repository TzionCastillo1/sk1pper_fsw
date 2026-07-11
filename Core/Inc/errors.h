#ifndef ERRORS_H
#define ERRORS_H

#ifdef __cplusplus
extern "C" {
#endif /** __cplusplus */

/**
 * @brief 
 * NOTE: the errors can be expanded on if need be
 */
typedef enum error_t
{
    //Generic
    ERROR_OK,
    ERROR_GENERIC,

    //Hardware


    //Sensors
    ERROR_SENSOR_INIT_FAIL,
    
    //Storage

    //Parameter Manager
    ERROR_PARAM_NOT_FOUND,
    ERROR_PARAM_INVALID_VALUE,
    ERROR_PARAM_WRITE_FAIL,

    //CLI
    ERROR_CLI_UNKOWN_CMD,
    ERROR_CLI_INVALID_ARGS,
    ERROR_CLI_BUFFER_FULL,

    //Control

} error_t;

#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** ERRORS_H */