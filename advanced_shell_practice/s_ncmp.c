#include "gosh.h"

/**
 * s_ncmp - a custom strncmp function
 * @s1: the home string input
 * @s2: the given string input
 * @n: the number of bytes in char to be compared
 * Return: 0 if 2 strings are equal or difference of 2 strings
 */

int s_ncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
		{
			return ((int)(unsigned char)s1[i] - (int)(unsigned char)s2[i]);
		}
		if (s1[i] == '\0' || s2[i] == '\0')
		{
			return (0);
		}
	}
	return (0);
}
