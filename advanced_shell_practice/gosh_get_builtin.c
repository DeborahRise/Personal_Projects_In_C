#include "gosh.h"

/**
 * gosh_get_builtin - builtin that pais the command in the arg
 * @cmd: command
 * Return: a builtin command function pointer
 */
int (*gosh_get_builtin(char *cmd))(go_shell *)
{
	gosh_builtin builtin[] = {
		{ "env", gosh_env },
		{ "exit", gosh_exit_shell },
		{ "setenv", gosh_setenv },
		{ "unsetenv", gosh_unsetenv },
		{ "cd", gosh_cd_shell },
		{ "help", gosh_get_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].g_builtin_name; i++)
	{
		if (s_cmp(builtin[i].g_builtin_name, cmd) == 0)
			break;
	}

	return (builtin[i].g_function);
}
