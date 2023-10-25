#include "gosh.h"

/**
 * gosh_error_env - _get_env error message
 * @gosh_gosh: arguments g_counter
 * Return: error message.
 */
char *gosh_error_env(go_shell *gosh_gosh)
{
	int length;
	char *g_error;
	char *g_ver_str;
	char *g_message;

	g_ver_str = gosh_itoa(gosh_gosh->g_counter);
	g_message = ": Unable to add/remove from environment\n";
	length = s_len(gosh_gosh->agv[0]) + s_len(g_ver_str);
	length += s_len(gosh_gosh->g_args[0]) + s_len(g_message) + 4;
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
	s_cat(g_error, g_message);
	s_cat(g_error, "\0");
	free(g_ver_str);

	return (g_error);
}
/**
 * g_error_path_126 - g_error message for path and failure denied permission.
 * @gosh_gosh: data relevant (counter, arguments).
 *
 * Return: message of error.
 */
char *g_error_path_126(go_shell *gosh_gosh)
{
	int length;
	char *g_ver_str;
	char *g_error;

	g_ver_str = gosh_itoa(gosh_gosh->g_counter);
	length = s_len(gosh_gosh->agv[0]) + s_len(g_ver_str);
	length += s_len(gosh_gosh->g_args[0]) + 24;
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
	s_cat(g_error, ": Permission denied\n");
	s_cat(g_error, "\0");
	free(g_ver_str);
	return (g_error);
}
