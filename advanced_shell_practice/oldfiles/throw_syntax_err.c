#include "gosh.h"

/**
 * throw_syntax_err - throws a syntax error if one exists
 * in command string entered.
 * @num: the number of arguments passed. Used to create the
 *       response string.
 * Return: -1 always.
 */
int throw_syntax_err(int num, ...)
{
	va_list chars;
	char *err_token;
	int i = 0;

	err_token = malloc(num + 1);
	if (!err_token)
		return (-2);
	va_start(chars, num);
	while (i < num)
	{
		err_token[i] = va_arg(chars, int);
		i++;
	}
	err_token[i] = '\0';
	va_end(chars);

	gosh_printf("-gosh: syntax error near unexpected token `%s'\n",
			err_token);
	return (-1);
}
