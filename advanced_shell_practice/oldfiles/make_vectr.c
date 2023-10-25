#include "gosh.h"

/**
 * make_vectr - makes a vector from a string
 * based usiing a delimiter
 * @inputstr: the string
 * @delim: the delimiting string
 * Return: ptr to the vecor on success.
 *         NULL otherwise or if error
 */
char **make_vectr(char *inputstr, char *delim)
{
	char **vectr, *str, *token;
	int n = 0, i = 0;

	if (!inputstr)
		return (NULL);

	str = s_dup(inputstr);
	while (str[i++])
	{
		if (str[i - 1] == *delim)
			n++;
	}
	n += 2, i = 0;
	vectr = malloc(sizeof(char *) * (n));
	if (!vectr)
		return (NULL);
	vectr[--n] = NULL, token = s_tok(str, delim);
	if (!token)
		vectr[0] = s_dup(str);
	else
	{
		while (i < n)
		{
			vectr[i] = s_dup(token);
			token = s_tok(NULL, delim);
			i++;
		}
	}
	return (vectr);
}
