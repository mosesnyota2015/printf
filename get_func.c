#include "main.h"
#include <stdlib.h>

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
