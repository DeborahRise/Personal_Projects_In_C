#include "gosh.h"

/**
* get_gcmdpath - generates and expands the absolute path to cmd arg.
* @agv: the executable or built in cmd passed by user
* Return: returns the path generated
*/

char  *get_gcmdpath(char **agv)
{
	char c = agv[0][0], *abs_path = NULL, *temp;

	if (c < 65 || (c > 90 && c < 97) || c > 122)
	{
		/* expansion should happen in here */
		temp = _gcmdpath_expandr(agv[0]);
		if (!temp)
			return (NULL);
		abs_path = temp;
	}
	else /* use $PATH variable to obtain absolute path */
	{
		temp = _getfull_path(agv[0], getenv("PATH"), 0);
		if (!temp)
			return (NULL);
		abs_path = temp;
	}
	return (abs_path);
}
