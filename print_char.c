#include "main.h"

/**
 * print_char - prints a char
 * @args: va_list
 * Return: int
 */

int print_char(va_list args)
{
	return (_putchar(va_arg(args, int)));
}
