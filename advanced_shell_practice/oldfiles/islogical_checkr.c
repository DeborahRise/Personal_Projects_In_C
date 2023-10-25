#include "gosh.h"

/**
 * islogical_checkr - checks if a command line has logical
 * operators
 * @cmdline: the command line
 * Return: 1 if there is at least one logical operator in command
 *	   0 otherwise.
 */
int islogical_checkr(char **cmdline)
{
	int is_logical = 0, i = 0;
	char *temp;

	if (!cmdline || !(*cmdline))
		return (-1);

	temp = s_chr(*cmdline, '#');
	if (temp)
		*temp = '\0';

	while ((*cmdline)[i] != '\0')
	{
		if ((*cmdline)[i] == '|' ||
				(*cmdline)[i] == '&' ||
				(*cmdline)[i] == ';')
		{
			is_logical = 1;
			break;
		}
		i++;
	}
	return (is_logical);
}
