#include "gosh.h"
/**
 * _gcmdpath_expandr - expands a relative paths into it's absolute path
 * @rel_path: the relative path
 * Return: ptr to the absolute path on success. NULL otherwise.
 */
char *_gcmdpath_expandr(char *rel_path)
{
	char *abs_path = NULL, *temp = NULL,
		 rel_ids[] = {'.', '/', '~', '\0'}, c = *rel_path;
	int i = 0;

	while (rel_ids[i])
	{
		if (c == rel_ids[i])
			break;
		i++;
	}
	if (!i)
	{
		if (rel_path[1] == '.' && (rel_path[2] == '/'))
		{
			temp = _getparent_path(_get_env("PWD"));
			if (!temp)
				return (NULL); /* ../bin/ls  / */
			return (abs_path = _getfull_path(rel_path,
						temp, 1));
		}
		else if (rel_path[1] == '/')
			return (abs_path = _getfull_path(rel_path,
						_get_env("PWD"), 1));
		return (abs_path = NULL);
	}
	else if (i == 1)
		abs_path = _getfull_path(rel_path, "/", 1); /* PIN */
	else if (i == 2)
	{
		if (rel_path[1] == '/')
			return (abs_path = _getfull_path(rel_path,
						_get_env("HOME"), 1));
		return (abs_path = NULL);
	}
	return (abs_path);
}
