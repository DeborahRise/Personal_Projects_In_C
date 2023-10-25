#include "gosh.h"

/**
 * s_dup - duplicates a string in memory
 * @str: the string
 * Return: ptr to duplicated string if successful. NULL otherwise
 */
char *s_dup(char *str)
{
	char *new_str;
	size_t len = 0;

	if (!str)
		return (NULL);
	while (str[len])
		len++;
	new_str = malloc(sizeof(char) * (len + 1));

	if (!new_str)
		return (NULL);
	len = 0;
	while (str[len])
	{
		new_str[len] = str[len];
		len++;
	}
	new_str[len] = '\0';
	return (new_str);
}
