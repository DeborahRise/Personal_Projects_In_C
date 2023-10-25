#include "gosh.h"
/**
 * _syntax_checkr - checks for 2 edge cases.
 * 1. Empty commands/syntax errors
 * (multiple operators and separators)
 * Trailing white spaces
 * @cmdstr: the command string
 * @gcmdln: the argument passed by user
 * Return: should be added to other functions.
 */
int _syntax_checkr(char **cmdstr, char *gcmdln)
{
	int i, matched, ret;
	char *cmdl = s_dup(gcmdln), *token,
		 *lops[] = {";", "&&", "||", NULL};

	*cmdstr = (char *)malloc(s_len(gcmdln) + 1);
	if (!(*cmdstr))
		return (-1);
	(*cmdstr)[0] = '\0';
	if (*cmdl == ';' || *cmdl == '&' || *cmdl == '|')
	{
		if (cmdl[1] == ';' || cmdl[1] == '&' || cmdl[1] == '|')
			return (throw_syntax_err(2, *cmdl, cmdl[1]));
		return (throw_syntax_err(1, *cmdl));
	}
	token = s_tok(cmdl, " ");
	while (token)
	{
		i = matched = 0;
		while (lops[i])
		{
			if (s_cmp(token, lops[i]) == 0)
			{
				matched = 1;
				break;
			}
			i++;
		}
		if (matched || s_len(token) == 1)
			s_cat((*cmdstr), " "), s_cat((*cmdstr), token);
		else
		{
			ret = _cpyto_cmdstr(token, cmdstr);
			if (ret < 0)
				return (ret);
		}
		token = s_tok(NULL, " ");
	}
	return (0);
}
