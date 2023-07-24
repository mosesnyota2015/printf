#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "main.h"


int _printf(const char *format, ...)
{

    int count = 0; /* To store the number of characters printed */

    char *buffer = NULL; /* To store formatted output temporarily */
    int buffer_size = 0; /* To keep track of the buffer size */
    int str_len;
    int digits = 1; /* For at least one digit (0 case) */
    unsigned int temp_num;
    int i;

    char *temp_str = NULL; /* To store temporary strings */

    va_list args;
    va_start(args, format);

    while (*format)
    {
        if (*format == '%')
        {
            format++; /* Move past the '%' */

            switch (*format)
            {
                char ch;
                int num;
                unsigned int unum; /* For handling negative numbers */
                void *addr;

            case 'c':
                ch = (char)va_arg(args, int);
                count += write(1, &ch, 1);
                break;

            case 's':
                temp_str = va_arg(args, char *);
                str_len = 0;
                while (temp_str[str_len] != '\0')
                    str_len++;
                count += write(1, temp_str, str_len);
                break;

            case 'd':
            case 'i':
                num = va_arg(args, int);

                /* Handle negative numbers */
                if (num < 0)
                {
                    count += write(1, "-", 1);
                    unum = -num;
                }
                else
                {
                    unum = num;
                }

                /* Count the number of digits in the integer */
                digits = 1; /* For at least one digit (0 case) */
                temp_num = unum;
                while (temp_num >= 10)
                {
                    temp_num /= 10;
                    digits++;
                }

                /* Reallocate buffer if necessary */
                if (buffer_size < digits)
                {
                    free(buffer);
                    buffer_size = digits + 1;
                    buffer = (char *)malloc(buffer_size);
                    if (!buffer)
                        return -1; /* Memory allocation error */
                }

                /* Convert the integer to a string and store it in the buffer */
                for (i = digits - 1; i >= 0; i--)
                {
                    buffer[i] = '0' + (unum % 10);
                    unum /= 10;
                }

                /* Print the integer string */
                count += write(1, buffer, digits);
                break;

            case 'u':
                unum = va_arg(args, unsigned int);

                /* Count the number of digits in the integer */
                digits = 1; /* For at least one digit (0 case) */
                temp_num = unum;
                while (temp_num >= 10)
                {
                    temp_num /= 10;
                    digits++;
                }

                /* Reallocate buffer if necessary */
                if (buffer_size < digits)
                {
                    free(buffer);
                    buffer_size = digits + 1;
                    buffer = (char *)malloc(buffer_size);
                    if (!buffer)
                        return -1; /* Memory allocation error */
                }

                /* Convert the integer to a string and store it in the buffer */
                for (i = digits - 1; i >= 0; i--)
                {
                    buffer[i] = '0' + (unum % 10);
                    unum /= 10;
                }

                /* Print the integer string */
                count += write(1, buffer, digits);
                break;

            case 'o':
                unum = va_arg(args, unsigned int);

                /* Count the number of octal digits in the integer */
                digits = 1; /* For at least one digit (0 case) */
                temp_num = unum;
                while (temp_num >= 8)
                {
                    temp_num /= 8;
                    digits++;
                }

                /* Reallocate buffer if necessary */
                if (buffer_size < digits)
                {
                    free(buffer);
                    buffer_size = digits + 1;
                    buffer = (char *)malloc(buffer_size);
                    if (!buffer)
                        return -1; /* Memory allocation error */
                }

                /* Convert the integer to an octal string and store it in the buffer */
                for (i = digits - 1; i >= 0; i--)
                {
                    buffer[i] = '0' + (unum % 8);
                    unum /= 8;
                }

                /* Print the octal string */
                count += write(1, buffer, digits);
                break;

            case 'x':
            case 'X':
                unum = va_arg(args, unsigned int);

                /* Count the number of hexadecimal digits in the integer */
                digits = 1; /* For at least one digit (0 case) */
                temp_num = unum;
                while (temp_num >= 16)
                {
                    temp_num /= 16;
                    digits++;
                }

                /* Reallocate buffer if necessary */
                if (buffer_size < digits)
                {
                    free(buffer);
                    buffer_size = digits + 1;
                    buffer = (char *)malloc(buffer_size);
                    if (!buffer)
                        return -1; /* Memory allocation error */
                }

                /* Convert the integer to a hexadecimal string and store it in the buffer */
                for (i = digits - 1; i >= 0; i--)
                {
                    int rem = unum % 16;
                    if (rem < 10)
                    {
                        buffer[i] = '0' + rem;
                    }
                    else
                    {
                        buffer[i] = (*format == 'x') ? ('a' + rem - 10) : ('A' + rem - 10);
                    }
                    unum /= 16;
                }

                /* Print the hexadecimal string */
                count += write(1, buffer, digits);
                break;

            case 'p':

                addr = va_arg(args, void*);

                /* Convert the address to a hexadecimal string and store it in the buffer */
                buffer_size = sizeof(void*) * 2 + 3; /* Size of address + "0x" + null terminator */ 
                buffer = (char*)malloc(buffer_size);
                if (!buffer)
                    return -1; /* Memory allocation error */

                snprintf(buffer, buffer_size, "0x%lx", (unsigned long)addr);

                /* Print the address string */
                count += write(1, buffer, buffer_size - 1);
                break;




            case '%':
                count += write(1, "%", 1);
                break;

            default:
                count += write(1, "%", 1);
                count += write(1, format, 1);
                break;
            }
        }
        else
        {
            count += write(1, format, 1);
        }

        format++;
    }

    free(buffer);
    va_end(args);

    return count;
}
