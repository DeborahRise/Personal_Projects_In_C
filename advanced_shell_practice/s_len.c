#include "gosh.h"
/**
 * s_len - finds length of string
 * @str: string
 * Return: length of string
 */

int s_len(const char *str)
{
	size_t length = 0;

	if (str == NULL)
		return (0);

	while (str[length] != '\0')
	{
		length++;
	}

	return (length);
}
