#include "gosh.h"
/**
 * gcmd_exec - handles command selection and execution
 * @agv: arguments vector
 * @func_ret: return value tracker in main
 * Return: 0 on success, -1 on error
 */

int gcmd_exec(char **agv, int *func_ret);

int gcmd_exec(char **agv, int *func_ret)
{
	char *s_cmds[] = {"exit", "env", "setenv", "unsetenv", "cd",
		"echo", "cat", "touch", "alias", NULL}, *full_path;
	int j = 0, i = 0, match = 0;

	if (!(**agv))
		return (-1);
	do {
		j = 0;
		while (s_cmds[j++])
		{
			if (s_cmp(agv[i], s_cmds[j - 1]) == 0)
			{
				match = 1;
				break;
			}
		}
		if (match)
			break;
	} while (++i < 1);
	if (match)
	{
		switch (j)
		{
			case 1:
				_exit_exec(agv);
				break;
			case 2:
				return (_env_exec(agv));
			case 3:
				return (_setenv_exec(agv));
			case 4:
				return (_unsetenv_exec(agv));
			case 5:
				return (ch_dir(agv[1]));
			case 6:
				return (echo_echo(agv, func_ret));
			case 7:
				return (cat_cat(agv));
			case 8:
				return (touch_touch(agv));
			case 9:
				return (alias_handler(agv));
			default:
				return (-1);
		}
	}
	else
	{
		/* Execute other commands */
		full_path = get_gcmdpath(agv);
		if (!full_path)
		{
			perror(agv[0]);
			return (-1);
		}
		else /* proceed to forking */
		{
			return (gcmd_fork(full_path, agv));
		}
	}
	return (0);
}
