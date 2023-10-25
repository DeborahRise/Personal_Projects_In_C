#include "gosh.h"

/**
 * get_error - gets the the builtin, syntax or permission error
 * @gosh_gosh: data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int get_error(go_shell *gosh_gosh, int eval)
{
	char *error;

	switch (eval)
	{
		case -1:
			error = gosh_error_env(gosh_gosh);
			break;
		case 126:
			error = g_error_path_126(gosh_gosh);
			break;
		case 127:
			error = error_not_found(gosh_gosh);
			break;
		case 2:
			if (s_cmp("exit", gosh_gosh->g_args[0]) == 0)
				error = gosh_error_exit_shell(gosh_gosh);
			else if (s_cmp("cd", gosh_gosh->g_args[0]) == 0)
				error = gosh_error_get_cd(gosh_gosh);
			break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, s_len(error));
		free(error);
	}

	gosh_gosh->g_status = eval;
	return (eval);
}
