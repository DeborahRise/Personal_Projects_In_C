#include "gosh.h"
/**
 * logical_exec - executes logical and/or operations delimited with
 * ; sequentially.
 * @gcmdln: the user-entered command from stdin
 * @func_ret: return value tracker in main
 * Return: 0 on success, -1 on failure
 */
int logical_exec(char *gcmdln, int *func_ret)
{
	size_t cols = 0, i = 0;
	char *cmdstr, **cmdv, *cmdline, *currcmd;
	int retval, syntax_err;

	syntax_err = _syntax_checkr(&cmdstr, gcmdln);
	if (!syntax_err)
	{
		while (cmdstr[i])
		{
			if (cmdstr[i] == ';')
				cols++;
			i++;
		}
		cols++, i = 0;
		cmdv = malloc(sizeof(char *) * (cols + 1));
		cmdv[cols] = NULL, cmdline = s_tok(cmdstr, ";");
		if (cmdline)
		{
			while (cols > 0)
			{
				cmdv[i] = cmdline;
				cmdline = s_tok(NULL, ";");
				cols--, i++;
			}
		}
		else
			cmdv[0] = s_dup(cmdstr);
		for (i = 0; cmdv[i]; i++)
		{
			retval = _logical_ops(cmdv[i], &currcmd, func_ret);
			*func_ret = retval;
			if (retval != 0)
				perror(currcmd);
		}
		return (0);
	}
	else
		return (-1);
}
