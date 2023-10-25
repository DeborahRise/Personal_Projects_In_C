#include "gosh.h"

/**
 * s_chr - function that checks for the presence of certain characters
 * @str: where str is gcmd
 * @c: character searched for.
 * Return: the pointer to character if found, else NULL
 */

char *s_chr(char *str, char c)
{
	while (*str != '\0')
	{
		if (*str == c)
		{
			return ((char *)str);
		}
		str++;
	}
	return (NULL);
}
