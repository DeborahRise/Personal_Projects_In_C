#include "gosh.h"
/**
 * ch_dir - changes cwd to another location
 * @dest: the absolute path to the destination
 * Return: path to the new location. NULL if failed.
 */

int ch_dir(char *dest);

int ch_dir(char *dest)
{
	char *cwd = getcwd(NULL, 0), *full_path = NULL,
		 rel_ids[] = {'.', '/', '~', ' ', '-', '\0'},
		 c = dest ? *dest : '~';
	int i = 0;

	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		full_path = _getfull_path(dest, cwd, 1);
		return (_chdir_helper(full_path, cwd));
	}
	while (rel_ids[i])
	{
		if (c == rel_ids[i])
			break;
		i++;
	}
	if (!i)
	{
		if ((dest[1] == '.' && dest[2] == '/') || (dest[1] == '.'
					&& (dest[2] == '\0' || dest[2] == ' ')))
		{
			full_path = _getparent_path(_get_env("PWD"));
			return (_chdir_helper(full_path, cwd));
		}
		if (dest[1] == '/' || dest[1] == '\0' || dest[1] == ' ')
		{
			full_path = _getfull_path(dest, _get_env("PWD"), 1);
			return (_chdir_helper(full_path, cwd));
		}
		return (-1);
	}
	else if (i == 1)
	{
		full_path = _getfull_path(dest, "/", 1);
		return (_chdir_helper(full_path, cwd));
	}
	else if (i == 2 || i == 3 || (dest[0] == ' '
				|| dest[0] == '\0'))
		return (_chdir_helper(_get_env("HOME"), cwd));
	else if (i == 4 && (dest[1] == ' ' || dest[1] == '\0'))
	{
		full_path = _get_env("OLDPWD");
		return (_chdir_helper(full_path, cwd));
	}
	return (-1);
}
