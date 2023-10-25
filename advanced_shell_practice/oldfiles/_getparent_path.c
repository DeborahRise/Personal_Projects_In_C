#include "gosh.h"
/**
 * _getparent_path - gets the abs path of the parent of cwd
 * @cwd: absolute path to cwd
 * Return: pointer to parent string,
 */
char *_getparent_path(char *cwd)
{
	size_t i, j;
	char *parent = NULL;

	if (cwd)
	{
		i = s_len(cwd) - 1;

		/* find the last occurence of ''/'' */
		while (cwd[i] != '/')
			i--;
		if (!i)
			parent = malloc(2), i = 1;
		else
			parent = malloc(i);
		if (!parent)
			return (NULL);
		for (j = 0; j < i; j++)
			parent[j] = cwd[j];
		parent[j] = '\0';
	}
	return (parent);
}
