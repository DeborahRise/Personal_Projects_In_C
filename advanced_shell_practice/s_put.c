#include "gosh.h"

/**
 * s_put - a function that prints strings
 * @s: argument  passed
 * Return: count of printed characters
 */

int s_put(char *s)
{
	int n;

	if (s == NULL)
		s = "(null)";
	n = write(1, s, s_len(s));
	return (n);
}
