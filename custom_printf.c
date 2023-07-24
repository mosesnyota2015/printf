#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include "main.h"

int _printf(const char *format, ...) {
    
    int count = 0; 
    char *buffer = NULL; 
    int buffer_size = 0; 
    char *temp_str = NULL;
    char ch;
    int num;
    int str_len;
    int temp_num;
    int digits;
    int i;
    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++; 

            switch (*format) {
                case 'c':
                    ch = (char)va_arg(args, int);
                    count += write(1, &ch, 1);
                    break;

                case 's':
                    temp_str = va_arg(args, char*);
                    str_len = 0;
                    while (temp_str[str_len] != '\0')
                        str_len++;
                    count += write(1, temp_str, str_len);
                    break;

                case 'd':
                case 'i':
                    num = va_arg(args, int);
                    temp_num = num;
                    digits = 0;
                    
                    if (num == 0) {
                        count += write(1, "0", 1);
                    }
                    else if (num < 0) {
                        count += write(1, "-", 1);
                        temp_num = -temp_num;
                    }

                    while (temp_num > 0) {
                        temp_num /= 10;
                        digits++;
                    }

                    if (buffer_size < digits) {
                        free(buffer);
                        buffer_size = digits + 1;
                        buffer = (char*)malloc(buffer_size);
                        if (!buffer)
                            return -1; 
                    }

                    for (i = digits - 1; i >= 0; i--) {
                        buffer[i] = '0' + (num % 10);
                        num /= 10;
                    }

                    count += write(1, buffer, digits);
                    break;

                case '%':
                    count += write(1, "%", 1);
                    break;

                default:
                    count += write(1, format, 1);
                    break;
            }
        }
        else {
            count += write(1, format, 1);
        }

        format++;
    }

    free(buffer);
    va_end(args);

    return count;
}
