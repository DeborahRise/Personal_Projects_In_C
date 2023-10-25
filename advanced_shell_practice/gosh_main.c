#include "gosh.h"

/**
 * gosh_free_data - frees data structure
 * @gosh_gosh: data structure
 * Return: no return
 */
void gosh_free_data(go_shell *gosh_gosh)
{
	unsigned int i;

	for (i = 0; gosh_gosh->g_environ[i]; i++)
	{
		free(gosh_gosh->g_environ[i]);
	}

	free(gosh_gosh->g_environ);
	free(gosh_gosh->gpid);
}

/**
 * gosh_set_data - Initialize data structure
 *
 * @gosh_gosh: data structure
 * @agv: argument vector
 * Return: no return
 */
void gosh_set_data(go_shell *gosh_gosh, char **agv)
{
	unsigned int i;

	gosh_gosh->agv = agv;
	gosh_gosh->g_input = NULL;
	gosh_gosh->g_args = NULL;
	gosh_gosh->g_status = 0;
	gosh_gosh->g_counter = 1;

	for (i = 0; environ[i]; i++)
		;

	gosh_gosh->g_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		gosh_gosh->g_environ[i] = s_dup(environ[i]);
	}

	gosh_gosh->g_environ[i] = NULL;
	gosh_gosh->gpid = gosh_itoa(getpid());
}

/**
 * main - Entry point
 *
 * @agc: argument count
 * @agv: argument vector
 *
 * Return: 0 on success.
 */
int main(int agc, char **agv)
{
	go_shell gosh_gosh;
	(void) agc;

	signal(SIGINT, gosh_get_sigint);
	gosh_set_data(&gosh_gosh, agv);
	gosh_shell_loop(&gosh_gosh);
	gosh_free_data(&gosh_gosh);
	if (gosh_gosh.g_status < 0)
		return (255);
	return (gosh_gosh.g_status);
}
