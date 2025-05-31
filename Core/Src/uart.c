#include "uart.h"

typedef void (*uart_callback_function_t)(char);

typedef enum uart_transmission_length
{
    SINGLE_BYTE_LENGTH = 1,
} uart_transmission_length;

typedef enum uart_configuration_t
{
    UART_CONFIG_ERR = -1,
    UART_CONFIG_A = 1, /** 8N1 */
} uart_configuration_t;

struct uart_handle_t
{
    uart_callback_function_t callback_function;
    uint8_t tx_pin;
    uint8_t rx_pin;
    uart_configuration_t configuration;
    uint32_t baud_rate;
};

static void uart_configure()
{

}

uart_handle_t uart_init(uint8_t tx_pin, uint8_t rx_pin, uart_configuration_t configuration, uint32_t baud_rate)
{
    uart_handle_t new_uart_handle;
    if((tx_pin > -1) && (rx_pin > -1) && (baud_rate > 0) && (configuration > 0))
    {
        new_uart_handle.tx_pin = tx_pin;
        new_uart_handle.rx_pin = rx_pin;
        new_uart_handle.configuration = configuration;
        new_uart_handle.baud_rate = baud_rate;
    }
    else 
    {
        new_uart_handle.tx_pin = -1;
        new_uart_handle.rx_pin = -1;
        new_uart_handle.configuration = -1;
        new_uart_handle.baud_rate = -1;
    }

    /** TODO:
     * Enable the USART by writing the UE bit in USART_CR1 to 1
     * program the M bit in USART_CR1 to define the word length
     * Set Stop bits through control register 2
     * Configure DMA if needed
     * Set the baud rate using the USART_BRR register
     * 
    */
    USART



    return new_uart_handle;
}

error_t uart_stop(uart_handle_t *uart_handle)
{

}

error_t uart_start_interrupt(uart_handle_t *uart_handle)
{

}

error_t uart_start_polling(uart_handle_t *uart_handle)
{

}

error_t uart_write_byte(uart_handle_t *uart_handle, char byte)
{
    uart_write_bytes(uart_handle, &byte, SINGLE_BYTE_LENGTH);
}

error_t uart_write_bytes(uart_handle_t *uart_handle, char *byte_array, uint16_t array_length)
{
    for (int byte; byte < array_length; byte++)
    {
        uart_write_byte()
    }

}

error_t uart_set_callback(uart_handle_t *uart_handle, uart_callback_function_t callback_function)
{

}
