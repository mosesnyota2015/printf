#include "main.h"
#include <stdarg.h>
#include <stdlib.h>

/**
 * _printf - produces output according to a format
 * @format: char pointer
 * Return: int
 */

int _printf(const char *format, ...)
{
	int i = 0, cnt = 0;
	int (*func)(va_list);
	va_list args;

	va_start(args, format);

	if (format == NULL)
		return (-1);
	while (format[i])
	{
		if (format[i] != '%')
		{
			cnt += _putchar(format[i]);
			i++;
			continue;
		}
		if (format[i + 1] == '%')
		{
			cnt += _putchar(format[++i]);
			i++;
			continue;
		}
		func = get_func(format[++i]);
		if ((func) != NULL)
		{
			cnt += func(args);
		}
		else
		{
			if (format[i] == '\0')
				return (-1);
			cnt += _putchar(format[i - 1]);
			cnt += _putchar(format[i]);
		}
		i++;
	}
	va_end(args);
	return (cnt);
}


/**
 * get_base_len - return the length of the base
 * @n: int
 * @b: int
 * Return: int
 */
int get_base_len(int n, int b)
{
	int len = 0;

	while (n > 0)
	{
		n /= b;
		len++;
	}

	return (len);
}

/**
 * get_func - returns the correct func or null
 * @id: char
 * Return: function
 */

int (*get_func(const char id))(va_list args)
{
	prv_t prv[] = {
		{'c', print_char},
		{'s', print_str},
		{'b', print_bin},
		{'d', print_dec},
		{'i', print_dec},
		{'u', print_un_int},
		{'o', print_octa},
		{'x', print_hex},
		{'X', print_heX},
		{'S', print_non_prt},
		{'r', print_rev},
		{'R', print_rot},
		{'p', print_ptr}
	};

	const int PRV_LEN = 13;
	int i = 0;

	while (i < PRV_LEN)
	{
		if (id == prv[i].id)
			return (prv[i].f);
		i++;
	}

	return (NULL);
}
