#ifndef CLI_H
#define CLI_H

#include "stdint.h"
#include "stdbool.h"
#include "ringbuff.h"


#define CLI_MAX_LINE_LEN    128
#define CLI_MAX_ARGS        8
#define CLI_DELIMETERS      " \t"
#define CLI_UART_BUFF_LEN   255
#define CLI_MAX_LINES       4
#define CLI_MIN_ASCII       32
#define CLI_MAX_ASCII       126

extern char cli_uart_byte[];

typedef struct cli_handle_t
{
    bool prev_CR;
    char *delimeters;
} cli_handle_t;

//cmd_table taken from Making Embedded Systems - Elecia White
typedef struct cli_cmd_t
{
    char *cmd;
    void (*execute)(int argc, char **argv);
    char *helptext;
} cli_cmd_t;

/**
 * @brief initialize the CLI module 
 * 
 */
void cli_init();

/**
 * @brief Function to be called within UART IRQ.
 * Does light processing on the incoming byte and 
 * places it into a buffer. 
 * 
 * @param new_char 
 */
void cli_char_received(char new_char);

/**
 * @brief Pops all data from the ringbuffer and processes
 * it into string.
 * 
 * @param str 
 * @return int 
 */
int cli_ringbuff_to_str(char *str);

/**
 * @brief Take an input string and break it into several 
 * tokens based on spaces: ' '.
 * 
 * @param input_str input string
 * @param argv array of strings to hold tokens 
 * 
 * @return number of tokens
 */
int cli_tokenizer(char *input_str, char **argv);

void cli_invoker(int argc, char **argv);

#endif //CLI_H