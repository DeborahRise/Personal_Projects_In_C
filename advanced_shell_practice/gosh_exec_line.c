#include "gosh.h"

/**
 * exec_line - for commands and  builtins
 *
 * @gosh_gosh: data relevant (g_args)
 * Return: 1 on success.
 */
int exec_line(go_shell *gosh_gosh)
{
	int (*builtin)(go_shell *gosh_gosh);

	if (gosh_gosh->g_args[0] == NULL)
		return (1);

	builtin = gosh_get_builtin(gosh_gosh->g_args[0]);

	if (builtin != NULL)
		return (builtin(gosh_gosh));

	return (gosh_cmd_exec(gosh_gosh));
}
