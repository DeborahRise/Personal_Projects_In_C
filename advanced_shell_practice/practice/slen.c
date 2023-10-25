#include "debs.h"

size_t slen(const char *str)
{
	size_t length = 0;

	if (str == NULL)
		return (0);

	while (str[length] != '\0')
	{
		length++;
	}

	return length;
}
