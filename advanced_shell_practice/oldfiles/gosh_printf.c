#include "gosh.h"
/**
 * gosh_printf - a custom made printf function
 * @format: argument expecting variadic arguments
 * Return: count of printed characters
 */

int gosh_printf(const char *format, ...)
{
	gosh_struct gosh_table[] = {
		{"%s", gosh_print_string}, {"%c", gosh_print_char},
		{"%i", gosh_print_int_number},
		{"%u", gosh_print_unint_number}, {"%d", gosh_print_dec_number}
	};

	va_list djlist2;
	int j = 0, i, _printflen = 0;

	va_start(djlist2, format);
	if (!format || (format[0] == '%' && format[1] == '\0'))
		return (-1);
Here:
	while (format[j])
	{
		i = 3;
		while (i >= 0)
		{
			if (gosh_table[i].id[0] == format[j] &&
					gosh_table[i].id[1] == format[j + 1])
			{
				_printflen += gosh_table[i].f(djlist2);
				j = j + 2;
				goto Here;
			}
			i--;
		}
		s_write(format[j]);
		_printflen++;
		j++;
	}
	va_end(djlist2);
	return (_printflen);
}
