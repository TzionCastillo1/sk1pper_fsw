#include "cli.h"
#include "string.h"
#include "stdbool.h"
#include "printf/printf.h"
#include "cli_cmd.h"
#include "ringbuff.h"

char uart_buff[CLI_UART_BUFF_LEN];
ringbuff_t uart_ringbuff;

char line_buff[CLI_MAX_LINE_LEN];
uint8_t line_pos = 0;

bool prev_CR = false;
bool complete_line = false;

int curs_pos = 0;

void cli_init()
{
    ringbuff_init(&uart_ringbuff, uart_buff, CLI_UART_BUFF_LEN);
    printf_("Version: ");
    printf_("Sk1pper>\r\n");
}

void cli_char_received(char new_char)
{

    switch(new_char)
    {
        case ('\r'):
            ringbuff_push(&uart_ringbuff, '\0');
            prev_CR = true;
            // Echo CRLF
            printf_("%c\n", new_char);
            curs_pos = 0;
            break;
        case ('\n'):
            if (prev_CR = false)
            {
                ringbuff_push(&uart_ringbuff, '\0');
            }
            printf_("%c", new_char);
            curs_pos = 0;
            prev_CR = false;
            break;
        //Handle delete and backspace the same
        case (0x7F):
        case ('\b'):
            if (curs_pos > 0)
            {
                curs_pos--;
                ringbuff_pop_tail(&uart_ringbuff, NULL);
                //Print VT100 destructive backspace sequence.
                printf_("\b \b");
            }
            prev_CR = false;
            break;
        default:
            if (new_char >= CLI_MIN_ASCII && new_char <= CLI_MAX_ASCII)
            {
                ringbuff_push(&uart_ringbuff, new_char);
                printf_("%c", new_char);
                curs_pos++;
            }
            prev_CR = false;
            break;
    }
}

int cli_ringbuff_to_str(char *str)
{
    char new_char;
    int rbf_ret = ringbuff_pop(&uart_ringbuff, &new_char);
    while (rbf_ret)
    {
        line_buff[line_pos++] = (char)new_char;
        if (new_char == '\0')
        {
            int ret = line_pos;
            //reset the index in the line
            line_pos = 0;
            //push the complete line out
            strcpy(str, line_buff);
            //Not sure if this will be useful,
            // but returning string length
            return ret;
        }
        rbf_ret = ringbuff_pop(&uart_ringbuff, &new_char);
    }
    return 0;
}

int cli_tokenizer(char *input_str, char **argv)
{
    int argc = 0;
    char *saveptr;

    char *token = strtok_r(input_str, CLI_DELIMETERS, &saveptr);
    while ((token != NULL) && (argc < CLI_MAX_ARGS))
    {
        //Post increment
        argv[argc++] = token;
        token = strtok_r(NULL, CLI_DELIMETERS, &saveptr);
    }

    return argc;
}

void cli_invoker(int argc, char **argv)
{
    if (argc > 0)
    {
        // Check if we have reached the end of the table
        for(int idx = 0; cmd_table[idx].cmd[0] != '\0'; idx++)
        {
            if (strncmp(cmd_table[idx].cmd, argv[0], strlen(cmd_table[idx].cmd)) == 0) //Use strlen instead of sizeof
            {
                cmd_table[idx].execute(argc, argv);
            }
        }

    }
    printf_("Sk1pper>");
}