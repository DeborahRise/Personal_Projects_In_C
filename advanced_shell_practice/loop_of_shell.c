#include "gosh.h"

/**
 * gosh_without_comment - deletes comments from the input
 *
 * @in: input string
 * Return: input without comments
 */
char *gosh_without_comment(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = g_realloc(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * gosh_shell_loop - Looping through shell
 * @gosh_gosh: data relevant (agv, input, g_args)
 *
 * Return: no return.
 */
void gosh_shell_loop(go_shell *gosh_gosh)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "($) ", 4);
		input = gosh_read_line(&i_eof);
		if (i_eof != -1)
		{
			input = gosh_without_comment(input);
			if (input == NULL)
				continue;

			if (g_check_syntax_error(gosh_gosh, input) == 1)
			{
				gosh_gosh->g_status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, gosh_gosh);
			loop = gosh_split_commands(gosh_gosh, input);
			gosh_gosh->g_counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
