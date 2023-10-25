#include "gosh.h"

/**
 * gosh_print_char - prints a char.
 * @djlist2: arguments.
 * Return: 1.
 */
int gosh_print_char(va_list djlist2)
{
	char s;

	s = va_arg(djlist2, int);
	s_write(s);
	return (1);
}
