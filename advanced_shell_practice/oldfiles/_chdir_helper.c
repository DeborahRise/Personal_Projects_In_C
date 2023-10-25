#include "gosh.h"
/**
 * _chdir_helper - Change directory function helper
 * @full_path: Full path to directory
 * @cwd: Current working directory
 * Return: 0 on success, -1 on error
 */
int _chdir_helper(char *full_path, char *cwd)
{
	int retval;

	if (!full_path || !cwd)
		return (-1);
	setenv("OLDPWD", cwd, 1);
	retval = chdir(full_path);
	setenv("PWD", full_path, 1);
	return (retval);
}
