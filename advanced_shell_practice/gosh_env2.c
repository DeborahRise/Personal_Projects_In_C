#include "gosh.h"

/**
 * gosh_copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *gosh_copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = s_len(name);
	len_value = s_len(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	s_copy(new, name);
	s_cat(new, "=");
	s_cat(new, value);
	s_cat(new, "\0");

	return (new);
}

/**
 * gosh_set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @gosh_gosh: data structure (environ)
 * Return: no return
 */
void gosh_set_env(char *name, char *value, go_shell *gosh_gosh)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; gosh_gosh->g_environ[i]; i++)
	{
		var_env = s_dup(gosh_gosh->g_environ[i]);
		name_env = s_tok(var_env, "=");
		if (s_cmp(name_env, name) == 0)
		{
			free(gosh_gosh->g_environ[i]);
			gosh_gosh->g_environ[i] = gosh_copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	gosh_gosh->g_environ = g_reallocdp(gosh_gosh->g_environ, i,
			sizeof(char *) * (i + 2));
	gosh_gosh->g_environ[i] = gosh_copy_info(name, value);
	gosh_gosh->g_environ[i + 1] = NULL;
}

/**
 * gosh_setenv - compares env variables names
 * with the name passed.
 * @gosh_gosh: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int gosh_setenv(go_shell *gosh_gosh)
{

	if (gosh_gosh->g_args[1] == NULL || gosh_gosh->g_args[2] == NULL)
	{
		get_error(gosh_gosh, -1);
		return (1);
	}

	gosh_set_env(gosh_gosh->g_args[1], gosh_gosh->g_args[2], gosh_gosh);

	return (1);
}

/**
 * gosh_unsetenv - deletes a environment variable
 *
 * @gosh_gosh: data relevant (env name)
 *
 * Return: 1 on success.
 */
int gosh_unsetenv(go_shell *gosh_gosh)
{
	char **reallocg_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (gosh_gosh->g_args[1] == NULL)
	{
		get_error(gosh_gosh, -1);
		return (1);
	}
	k = -1;
	for (i = 0; gosh_gosh->g_environ[i]; i++)
	{
		var_env = s_dup(gosh_gosh->g_environ[i]);
		name_env = s_tok(var_env, "=");
		if (s_cmp(name_env, gosh_gosh->g_args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(gosh_gosh, -1);
		return (1);
	}
	reallocg_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; gosh_gosh->g_environ[i]; i++)
	{
		if (i != k)
		{
			reallocg_environ[j] = gosh_gosh->g_environ[i];
			j++;
		}
	}
	reallocg_environ[j] = NULL;
	free(gosh_gosh->g_environ[k]);
	free(gosh_gosh->g_environ);
	gosh_gosh->g_environ = reallocg_environ;
	return (1);
}
