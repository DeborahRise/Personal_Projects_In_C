#include "gosh.h"

/**
 * gosh_print_string - a function that prints strings
 * @djlist2: argument  passed from va_arg(list, char*)
 * Return: count of printed characters
 */

int gosh_print_string(va_list djlist2)
{
	char *s;
	int i, len;

	s = va_arg(djlist2, char *);
	if (s == NULL)
	{
		s = "(null)";
		len = s_len(s);
		for (i = 0; i < len; i++)
			s_write(s[i]);
		return (len);
	}
	else
	{
		len = s_len(s);
		for (i = 0; i < len; i++)
			s_write(s[i]);
		return (len);
	}
}
