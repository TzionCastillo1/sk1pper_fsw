#ifndef UART_H
#define UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "errors.h"
#include "stdint.h"
#include "stm32f405xx.h"

typedef struct uart_handle_t uart_handle_t;

uart_handle_t uart_init(uint8_t tx_pin, uint8_t rx_pin, uart_configuration_t configuration, uint32_t baud_rate);

error_t uart_stop(uart_handle_t *uart_handle);

error_t uart_start_interrupt(uart_handle_t *uart_handle);

error_t uart_start_polling(uart_handle_t *uart_handle);

error_t uart_write_byte(uart_handle_t *uart_handle, char byte);

error_t uart_write_bytes(uart_handle_t *uart_handle, char *byte_array, uint16_t array_length);

error_t uart_set_callback(uart_handle_t *uart_handle, uart_callback_function_t callback_function);


#ifdef __cplusplus
}
#endif

#endif /** UART_H */