#include "gosh.h"

/**
 * gosh_swap_char - swaps | and & for non-printed chars
 *
 * @g_input: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *gosh_swap_char(char *g_input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; g_input[i]; i++)
		{
			if (g_input[i] == '|')
			{
				if (g_input[i + 1] != '|')
					g_input[i] = 16;
				else
					i++;
			}

			if (g_input[i] == '&')
			{
				if (g_input[i + 1] != '&')
					g_input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; g_input[i]; i++)
		{
			g_input[i] = (g_input[i] == 16 ? '|' : g_input[i]);
			g_input[i] = (g_input[i] == 12 ? '&' : g_input[i]);
		}
	}
	return (g_input);
}

/**
 * gosh_add_nodes - add separators and command lines in the lists
 *
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @g_input: input string
 * Return: no return
 */
void gosh_add_nodes(gosh_sep_list **head_s,
		gosh_cmd_line **head_l, char *g_input)
{
	int i;
	char *line;

	g_input = gosh_swap_char(g_input, 0);

	for (i = 0; g_input[i]; i++)
	{
		if (g_input[i] == ';')
			add_gosh_sep_node_end(head_s, g_input[i]);

		if (g_input[i] == '|' || g_input[i] == '&')
		{
			add_gosh_sep_node_end(head_s, g_input[i]);
			i++;
		}
	}

	line = s_tok(g_input, ";|&");
	do {
		line = gosh_swap_char(line, 1);
		add_gosh_line_node_end(head_l, line);
		line = s_tok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * gosh_go_next - go to the next command line stored
 *
 * @list_s: g_separator list
 * @list_l: command line list
 * @gosh_gosh: data structure
 * Return: no return
 */
void gosh_go_next(gosh_sep_list **list_s,
		gosh_cmd_line **list_l, go_shell *gosh_gosh)
{
	int loop_sep;
	gosh_sep_list *ls_s;
	gosh_cmd_line *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (gosh_gosh->g_status == 0)
		{
			if (ls_s->g_separator == '&' || ls_s->g_separator == ';')
				loop_sep = 0;
			if (ls_s->g_separator == '|')
				ls_l = ls_l->g_next, ls_s = ls_s->g_next;
		}
		else
		{
			if (ls_s->g_separator == '|' || ls_s->g_separator == ';')
				loop_sep = 0;
			if (ls_s->g_separator == '&')
				ls_l = ls_l->g_next, ls_s = ls_s->g_next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->g_next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * gosh_split_commands - splits command lines according to
 * the g_separators ;, | and &, and executes them
 *
 * @gosh_gosh: data structure
 * @g_g_input: input string
 * Return: 0 to exit, 1 to continue
 */
int gosh_split_commands(go_shell *gosh_gosh, char *g_input)
{

	gosh_sep_list *head_s, *list_s;
	gosh_cmd_line *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	gosh_add_nodes(&head_s, &head_l, g_input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		gosh_gosh->g_input = list_l->gcmd_line;
		gosh_gosh->g_args = gosh_split_line(gosh_gosh->g_input);
		loop = exec_line(gosh_gosh);
		free(gosh_gosh->g_args);

		if (loop == 0)
			break;

		gosh_go_next(&list_s, &list_l, gosh_gosh);

		if (list_l != NULL)
			list_l = list_l->g_next;
	}

	free_gosh_sep_list(&head_s);
	free_gosh_cmd_line(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * gosh_split_line - tokenizes the g_input string
 *
 * @g_input: g_input string.
 * Return: string splitted.
 */
char **gosh_split_line(char *g_input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFF_SIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = s_tok(g_input, TOK_DELIMETER);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFF_SIZE;
			tokens = g_reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = s_tok(NULL, TOK_DELIMETER);
		tokens[i] = token;
	}

	return (tokens);
}
