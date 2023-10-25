#include "gosh.h"
/**
 * _getfull_path - gets the abs path of the parent of the cwd
 * @rel_path: the relative path
 * @cwd: absolute path to cwd.
 * @slashed: 1 if to tokenise by slashes(/) or 0 if by (:)
 * Return: pointer to parent string on success.
 *         NULL if access fails or abs_path is NULL. cd goshell
 */

char *_getfull_path(char *rel_path, char *cwd, int slashed);

char *_getfull_path(char *rel_path, char *cwd, int slashed)
{
	char *temp = NULL, *full_path = NULL, *cwd_cpy;
	size_t i = 0, j = 0, len_rel = rel_path ? s_len(rel_path) : 0,
		   len_cw = cwd ? s_len(cwd) : 0, found = 0;

	if (slashed) /* ../enters here if rel paths are provided */
	{
		if (*rel_path == '/')
			full_path = rel_path;
		else
		{
			while (rel_path[i] != '/' && rel_path[i])
			{
				i++;
				if (rel_path[i] == '/')
					found = 1;
			}
			if (i == len_rel)
				i = 0;
			full_path = malloc((len_rel - i) + len_cw + 2);
			if (!full_path)
				return (NULL);
			while (cwd[j])
				full_path[j] = cwd[j], j++;
			if (found)
				i++;
			if (len_cw != 1)
				full_path[j++] = '/';
			while (rel_path[i])
				full_path[j] = rel_path[i], i++, j++;
			full_path[j] = '\0';
		}
		return (access(full_path, F_OK | X_OK) == 0 ?
				full_path : NULL);
	}
	else /* tokenise PATH and find command */
	{
		cwd_cpy = strdup(cwd);
		temp = s_tok(cwd_cpy, ":");
		while (temp)
		{
			full_path = malloc((s_len(temp)) +
					s_len(rel_path) + 2);
			if (!full_path)
				return (NULL);
			while (temp[i])
				full_path[i] = temp[i], i++;
			full_path[i++] = '/';
			while (rel_path[j])
				full_path[i] = rel_path[j], i++, j++;
			full_path[i] = '\0';
			if (access(full_path, F_OK | X_OK) == 0)
				return (full_path);

			temp = s_tok(NULL, ":"), i = j = 0;
			free(full_path);
			full_path = NULL;

		}
		return (full_path);
	}
}
