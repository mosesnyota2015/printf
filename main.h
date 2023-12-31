#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdlib.h>

/**
 * struct prv - struct prv
 * @id: chat
 * @f: func pointer
 */

typedef struct prv
{
	char id;
	int (*f)(va_list args);
} prv_t;

int _printf(const char *format, ...);

int (*get_func(const char id))(va_list);

int _putchar(int ch);

int print_char(va_list args);

int print_str(va_list args);

int print_bin(va_list args);
int cnvrt_to_bin(unsigned int n, int *cnt);

int print_dec(va_list args);
int cnvrt_to_dec(int n, int *cnt);

int print_un_int(va_list args);
int cnvrt_to_un_int(unsigned int n, int *cnt);

int print_octa(va_list args);
int cnvrt_to_octa(unsigned int n, int *cnt);

int print_hex(va_list args);
int cnvrt_to_hex(unsigned int n, int *cnt);

int print_heX(va_list args);
int cnvrt_to_heX(unsigned int n, int *cnt);

int get_base_len(int n, int b);

int print_non_prt(va_list args);

int print_rev(va_list args);
int get_str_len(char *s);

int print_rot(va_list args);

int print_ptr(va_list args);
int cnvrt_to_mem_addr(unsigned long int n, int *ptr);

#endif
