#include "debs.h"

/**
 * sprint - a function that prints strings
 * @s: argument  passed from va_arg(list, char*)
 * Return: count of printed characters
 */

int sprint(char *s)
{
	int i, len;

	if (s == NULL)
	{
		s = "(null)";
		len = slen(s);
		for (i = 0; i < len; i++)
			swrite(s[i]);
		return (len);
	}
	else
	{
		len = slen(s);
		for (i = 0; i < len; i++)
			swrite(s[i]);
		return (len);
	}
}
