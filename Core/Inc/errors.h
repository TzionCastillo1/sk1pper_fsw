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
    DEBUG = -2,
    INFO = -1,
    NO_ERR = 0,
    ERR_GENERIC,
} error_t;

#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** ERRORS_H */