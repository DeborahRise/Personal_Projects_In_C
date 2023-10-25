#include "gosh.h"

/**
 * gosh_get_help - function that retrieves help messages according builtin
 * @gosh_gosh: data structure (g_args and input)
 * Return: Return 0
 */
int gosh_get_help(go_shell *gosh_gosh)
{

	if (gosh_gosh->g_args[1] == 0)
		gaux_help_general();
	else if (s_cmp(gosh_gosh->g_args[1], "setenv") == 0)
		gaux_help_setenv();
	else if (s_cmp(gosh_gosh->g_args[1], "env") == 0)
		gaux_help_env();
	else if (s_cmp(gosh_gosh->g_args[1], "unsetenv") == 0)
		gaux_help_unsetenv();
	else if (s_cmp(gosh_gosh->g_args[1], "help") == 0)
		gaux_help();
	else if (s_cmp(gosh_gosh->g_args[1], "exit") == 0)
		gaux_help_exit();
	else if (s_cmp(gosh_gosh->g_args[1], "cd") == 0)
		gaux_help_cd();
	else if (s_cmp(gosh_gosh->g_args[1], "alias") == 0)
		gaux_help_alias();
	else
		write(STDERR_FILENO, gosh_gosh->g_args[0],
				s_len(gosh_gosh->g_args[0]));

	gosh_gosh->g_status = 0;
	return (1);
}
