#include "gosh.h"
/**
 * _unsetenv_exec - executes the unsetenv command
 * @agv: arguments vector
 * Return: 0 on success, -1 otherwise
 */

int _unsetenv_exec(char **agv)
{
	int i = 0;

	/*handle excess arguments */
	while (agv[i])
		i++;
	if (i > 3 || i < 2)
	{
		gosh_printf("%s: error: %s one parameter at a time\n", __FILE__, agv[0]);
		return (-1);
	}

	/* proceed to unset */
	if (unsetenv(agv[1]) != 0)
		return (-1);

	return (0);
}
