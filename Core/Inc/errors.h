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
    NO_ERR,
    ERR_GENERIC,
} error_t;

#ifdef __cplusplus
}
#endif /** __cplusplus */

#endif /** ERRORS_H */