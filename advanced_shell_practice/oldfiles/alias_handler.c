#include "gosh.h"

/**
 * alias_handler - controls execution of alias commands
 * @agv: arguments vector from the user
 * Return: 0 on success, -1 on error.
 */

int alias_handler(char **agv);
int alias_handler(char **agv)
{
	int i = 1, ret;
	char *temp, *name, *val, *entry;

	struct alias *found;

	if (!agv[1])
	{
		return (gosh_print_aliases());
	}
	else
	{
		while (agv[i])
		{
			entry = s_dup(agv[i]);
			temp = s_chr(entry, '=');
			if (temp)
			{
				name = s_tok(entry, "=");
				val = s_tok(NULL, "=");
				if (val[0] == '\'' || val[0] == '\"')
				{
					val = _dequoter(val);
					if (!val)
						return (-1);
				}
				ret = gosh_define_alias(name, val);
				if (ret < 0)
					gosh_printf("An error occurred\n");
			}
			else
			{
				found = gosh_find_alias(entry);
				if (!found)
					gosh_printf("-%s alias: %s not found\n", __FILE__, entry);
				else
					gosh_printf("alias %s='%s'\n", found->a_name, found->a_value);
			}
			free(entry);
			i++;
		}
	}
	return (0);
}

