#include "gosh.h"

/**
 * gosh_cd_shell - changes current directory
 *
 * @gosh_gosh: data relevant
 * Return: 1 on success
 */
int gosh_cd_shell(go_shell *gosh_gosh)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = gosh_gosh->g_args[1];

	if (dir != NULL)
	{
		ishome = s_cmp("$HOME", dir);
		ishome2 = s_cmp("~", dir);
		isddash = s_cmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_to_home(gosh_gosh);
		return (1);
	}

	if (s_cmp("-", dir) == 0)
	{
		cd_previous(gosh_gosh);
		return (1);
	}

	if (s_cmp(".", dir) == 0 || s_cmp("..", dir) == 0)
	{
		cd_dot(gosh_gosh);
		return (1);
	}

	cd_to(gosh_gosh);

	return (1);
}
