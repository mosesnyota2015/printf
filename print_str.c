#include "main.h"
#include <string.h>

/**
 * pr_str - prints a string to standard output stream
 * @args: va_list variable lists
 * Return: int
 */


int pr_str(va_list args)
{
	char *s = va_arg(args, char *);
	int len = 0;

	if (s == NULL)
		s = "(null)";

	while (*s)
	{
		_putchar(*s);
		len++;
		s++;
	}


	return (len);
}
