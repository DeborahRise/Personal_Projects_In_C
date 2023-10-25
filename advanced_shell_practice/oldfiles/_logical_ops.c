#include "gosh.h"
/**
 * _logical_ops - handles logical operations in the shell
 * @comd: the command string from user
 * @func_ret: return value tracker in main
 * @currcmd: the current command being executed.
 * Return: 0 if successfully run, -1 if error occurs.
 */

int _logical_ops(char *comd, char **currcmd, int *func_ret);

int _logical_ops(char *comd, char **currcmd, int *func_ret)
{
	char *command = s_dup(comd), *token,
		 *prev_command = NULL, **cmdlinev, **tokensv, *temp = NULL;
	int ret = 0, n = 0;

	tokensv = make_vectr(command, " ");
	if (!tokensv)
		return (-1);
	n = 0;
	while ((token = tokensv[n]))
	{
		if (s_cmp(token, "&&") == 0 || s_cmp(token, "||") == 0)
		{
			if (prev_command != NULL)
			{
				cmdlinev = make_vectr(prev_command, " ");
				if (!cmdlinev)
					return (-1);
				*currcmd = cmdlinev[0];
				ret = gcmd_exec(cmdlinev, func_ret);
			}
			if ((s_cmp(token, "&&") == 0 && ret != 0)
					|| (s_cmp(token, "||") == 0
						&& ret == 0))
			{
				prev_command = NULL;
				break;
			}
			else
				token = tokensv[++n], prev_command = token;
		}
		else
		{
			if (!prev_command && token)
				prev_command = s_dup(token);
			else if (prev_command && token)
			{
				ret = s_len(prev_command) +
					s_len(token) + 2;
				temp = (char *)malloc(ret);
				s_copy(temp, prev_command);
				s_cat(temp, " "), free(prev_command);
				s_cat(temp, token), prev_command = NULL;
				prev_command = s_dup(temp), free(temp);
			}
			else
				break;
		}
		n++;
	}
	if (prev_command && !token)
	{
		cmdlinev = make_vectr(prev_command, " .");
		*currcmd = cmdlinev[0], ret = gcmd_exec(cmdlinev, func_ret);
	}
	return (ret);
}
