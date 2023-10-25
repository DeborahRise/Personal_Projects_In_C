#include "gosh.h"
#include <stdio.h>
#include <string.h>

/**
 *
 */

char *logical_control(char *gcmd)
{
	char *av[1024];
	char *token = strtok(gcmd, " ");
	int ac = 0;
	while (token != NULL)
	{
		av[ac] = token;
		token = strtok(NULL, " ");
		ac++;
	}
	av[ac] = NULL;
int i = 0;
	while (av[i])
	{
		if (strcmp(av[i], "&&") == 0 || strcmp(av[i], "||") == 0 || strcmp(av[i], ";") == 0)
			i++;
	}
	if (i >= ac)
		perror("Error");
i = 0;
	while (av[i])
	{
		int func_ret_val = get_args (av[i]);
		i++;
		switch (av[i])
		{
			case &&:
				if (func_ret_val == 0)
					get_args(av[i]);
			case ||:
				if (func_ret_val != 0)
					get_args(av[i]);
			case ";":
				get_args(av[i]);
			default:
				 get_args(av[i] );
		}
	}
}int gcmd_exec(char **agv)
