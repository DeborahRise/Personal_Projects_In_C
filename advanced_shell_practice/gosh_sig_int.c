#include "gosh.h"

/**
 * gosh_get_sigint - Handle the crtl + c call in prompt
 * @sig: Signal handler
 */
void gosh_get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n($) ", 5);
}
