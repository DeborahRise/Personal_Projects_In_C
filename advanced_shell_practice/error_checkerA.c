#include "gosh.h"

/**
 * s_cat_cd - cd error concatenation function
 *
 * @gosh_gosh:  relevant data input (directory)
 * @g_message: to be printed
 * @g_error: message displayed
 * @g_ver_str: counter lines
 * Return: message indicating error
 */
char *s_cat_cd(go_shell *gosh_gosh, char *g_message,
		char *g_error, char *g_ver_str)
{
	char *illegal_gosh;

	s_copy(g_error, gosh_gosh->agv[0]);
	s_cat(g_error, ": ");
	s_cat(g_error, g_ver_str);
	s_cat(g_error, ": ");
	s_cat(g_error, gosh_gosh->g_args[0]);
	s_cat(g_error, g_message);
	if (gosh_gosh->g_args[1][0] == '-')
	{
		illegal_gosh = malloc(3);
		illegal_gosh[0] = '-';
		illegal_gosh[1] = gosh_gosh->g_args[1][1];
		illegal_gosh[2] = '\0';
		s_cat(g_error, illegal_gosh);
		free(illegal_gosh);
	}
	else
	{
		s_cat(g_error, gosh_gosh->g_args[1]);
	}

	s_cat(g_error, "\n");
	s_cat(g_error, "\0");
	return (g_error);
}

/**
 * gosh_error_get_cd - error message for cd command in get_cd
 * @gosh_gosh: (directory) data
 * Return: Error message
 */
char *gosh_error_get_cd(go_shell *gosh_gosh)
{
	int length, len_id;
	char *g_error, *g_ver_str, *g_message;

	g_ver_str = gosh_itoa(gosh_gosh->g_counter);
	if (gosh_gosh->g_args[1][0] == '-')
	{
		g_message = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		g_message = ": can't cd to ";
		len_id = s_len(gosh_gosh->g_args[1]);
	}

	length = s_len(gosh_gosh->agv[0]) + s_len(gosh_gosh->g_args[0]);
	length += s_len(g_ver_str) + s_len(g_message) + len_id + 5;
	g_error = malloc(sizeof(char) * (length + 1));

	if (g_error == 0)
	{
		free(g_ver_str);
		return (NULL);
	}

	g_error = s_cat_cd(gosh_gosh, g_message, g_error, g_ver_str);

	free(g_ver_str);

	return (g_error);
}

/**
 * error_not_found - generic error message for command not found
 * @gosh_gosh: counter, arguments
 * Return: Error message
 */
char *error_not_found(go_shell *gosh_gosh)
{
	int length;
	char *g_error;
	char *g_ver_str;

	g_ver_str = gosh_itoa(gosh_gosh->g_counter);
	length = s_len(gosh_gosh->agv[0]) + s_len(g_ver_str);
	length += s_len(gosh_gosh->g_args[0]) + 16;
	g_error = malloc(sizeof(char) * (length + 1));
	if (g_error == 0)
	{
		free(g_error);
		free(g_ver_str);
		return (NULL);
	}
	s_copy(g_error, gosh_gosh->agv[0]);
	s_cat(g_error, ": ");
	s_cat(g_error, g_ver_str);
	s_cat(g_error, ": ");
	s_cat(g_error, gosh_gosh->g_args[0]);
	s_cat(g_error, ": not found\n");
	s_cat(g_error, "\0");
	free(g_ver_str);
	return (g_error);
}

/**
 * gosh_error_exit_shell - generic error message
 * @gosh_gosh: counter, arguments
 * Return: Error message
 */

char *gosh_error_exit_shell(go_shell *gosh_gosh)
{
	int length;
	char *g_error;
	char *g_ver_str;

	g_ver_str = gosh_itoa(gosh_gosh->g_counter);
	length = s_len(gosh_gosh->agv[0]) + s_len(g_ver_str);
	length += s_len(gosh_gosh->g_args[0]) + s_len(gosh_gosh->g_args[1]) + 23;
	g_error = malloc(sizeof(char) * (length + 1));
	if (g_error == 0)
	{
		free(g_ver_str);
		return (NULL);
	}
	s_copy(g_error, gosh_gosh->agv[0]);
	s_cat(g_error, ": ");
	s_cat(g_error, g_ver_str);
	s_cat(g_error, ": ");
	s_cat(g_error, gosh_gosh->g_args[0]);
	s_cat(g_error, ": Illegal number: ");
	s_cat(g_error, gosh_gosh->g_args[1]);
	s_cat(g_error, "\n\0");
	free(g_ver_str);

	return (g_error);
}
