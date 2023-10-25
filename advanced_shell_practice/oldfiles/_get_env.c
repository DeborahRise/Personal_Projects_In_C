#include "gosh.h"

/**
 * _get_env - a custom getenv function
 * @envar: the environ variable passed as argument
 * Return: a char pointer to the address of value in variable
 */
char *_get_env(char *envar)
{
	int i = 0;
	char **env_address = environ, *curr_var, *var_name;

	while ((curr_var = s_dup(env_address[i])))
	{
		var_name = s_tok(curr_var, "=");
		if (s_cmp(var_name, envar) == 0)
			return (s_tok(NULL, "="));
		free(curr_var), i++;
	}
	return (NULL);
}
