#include "gosh.h"

/**
 * cmp_env_name - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _get_env - get an environment variable
 * @name: name of the environment variable
 * @g_environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_get_env(const char *name, char **g_environ)
{
	char *ptr_env;
	int i, mov;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (i = 0; g_environ[i]; i++)
	{
		/* If name and env are equal */
		mov = cmp_env_name(g_environ[i], name);
		if (mov)
		{
			ptr_env = g_environ[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * gosh_env - prints the evironment variables
 *
 * @gosh_gosh: data relevant.
 * Return: 1 on success.
 */
int gosh_env(go_shell *gosh_gosh)
{
	int i, j;

	for (i = 0; gosh_gosh->g_environ[i]; i++)
	{

		for (j = 0; gosh_gosh->g_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, gosh_gosh->g_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	gosh_gosh->g_status = 0;

	return (1);
}
