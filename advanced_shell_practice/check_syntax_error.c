#include "gosh.h"

/**
 * g_rpt_char - counts the repetitions of a char
 *
 * @input: input string
 * @i: index
 * Return: repetitions
 */
int g_rpt_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (g_rpt_char(input - 1, i + 1));

	return (i);
}

/**
 * g_error_sep_ops - finds syntax errors
 *
 * @input: input string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int g_error_sep_ops(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (g_error_sep_ops(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = g_rpt_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = g_rpt_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (g_error_sep_ops(input + 1, i + 1, *input));
}

/**
 * g_1st_char - finds index of the first char
 *
 * @input: input string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
int g_1st_char(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * g_print_syntax_error - prints when a syntax error is found
 *
 * @gosh_gosh: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void g_print_syntax_error(go_shell *gosh_gosh, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *g_counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	g_counter = gosh_itoa(gosh_gosh->g_counter);
	length = s_len(gosh_gosh->agv[0]) + s_len(g_counter);
	length += s_len(msg) + s_len(msg2) + s_len(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(g_counter);
		return;
	}
	s_copy(error, gosh_gosh->agv[0]);
	s_cat(error, ": ");
	s_cat(error, g_counter);
	s_cat(error, msg2);
	s_cat(error, msg);
	s_cat(error, msg3);
	s_cat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(g_counter);
}

/**
 * check_syntax_error - intermediate function to
 * find and print a syntax error
 *
 * @gosh_gosh: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int g_check_syntax_error(go_shell *gosh_gosh, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = g_1st_char(input, &begin);
	if (f_char == -1)
	{
		g_print_syntax_error(gosh_gosh, input, begin, 0);
		return (1);
	}

	i = g_error_sep_ops(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		g_print_syntax_error(gosh_gosh, input, begin + i, 1);
		return (1);
	}

	return (0);
}
