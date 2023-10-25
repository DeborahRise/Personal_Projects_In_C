#include "gosh.h"

/**
 * gosh_read_line - reads the input string.
 *
 * @i_EOF: return value of getline function
 * Return: input string
 */
char *gosh_read_line(int *i_EOF)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_EOF = getline(&input, &bufsize, stdin);

	return (input);
}
