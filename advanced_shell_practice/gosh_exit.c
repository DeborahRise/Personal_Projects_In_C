#include "gosh.h"

/**
 * gosh_exit_shell - exits the shell
 *
 * @gosh_gosh: data relevant (g_status and g_args)
 * Return: 0 on success.
 */
int gosh_exit_shell(go_shell *gosh_gosh)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (gosh_gosh->g_args[1] != NULL)
	{
		ustatus = gosh_atoi(gosh_gosh->g_args[1]);
		is_digit = g_isdigit(gosh_gosh->g_args[1]);
		str_len = s_len(gosh_gosh->g_args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error(gosh_gosh, 2);
			gosh_gosh->g_status = 2;
			return (1);
		}
		gosh_gosh->g_status = (ustatus % 256);
	}
	return (0);
}
