#include "gosh.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * logic_separator - a function that handles the semicolon
 * separator and logical operators in the goshell
 * @gcmd: command passed from stdin
 * Return: the execution status of the processes.
 */

int logic_separator(char *gcmd)
{
	char alt_gcmd = malloc(s_len(gcmd) + 1);
	char *token, *prev_cmd = NULL, *holder;
	int ret;

	s_copy(alt_gcmd, gcmd);
	token = s_tok(alt_gcmd, " ");

	while (token)
	{
		if (s_cmp(token, "&&") == 0 || s_cmp(token, "||") == 0 || s_cmp(token, ";") == 0)
		{
			if (prev_cmd)
			{
				ret = gcmd_exec(prev_cmd);
				if (s_cmp(token,"&&") == 0 && ret != 0)
				{
					break;
				}
				else if (s_cmp(token,"||") == 0 && ret == 0)
				{
					break;
				}
			}
			prev_cmd = NULL;
		}
		else
		{
			if (prev_cmd == NULL)
			{
				prev_cmd = malloc(s_len(token));
				s_copy(prev_cmd, token);
			}
			else
			{
				holder = malloc(s_len(prev_cmd) + s_len(token) + 2);
				s_copy(holder, prev_cmd);
				s_cat(holder, " ");
				s_cat(holder, token);
				free(prev_cmd);
				prev_cmd = holder;

			}
		}
		token = s_tok(NULL, " ");
	}
	if (prev_cmd)
	{
		ret = gcmd_exec(prev_cmd);
	}
	return (ret);
}
