#include "gosh.h"
/**
 * _env_exec - executes the env command
 * @agv: the arguments vector
 * Return: -1 on error, 0 on success.
 */

int _env_exec(char **agv)
{
	int n;
	char **env = environ;

	if (agv[1])
		return (-1);

	while (*env != NULL)
	{
		n = s_put(*env), env++;
		s_write('\n');
		if (n < 0)
			return (-1);
	}
	n = s_write('\n');
	if (n < 1)
		return (-1);
	return (0);
}
