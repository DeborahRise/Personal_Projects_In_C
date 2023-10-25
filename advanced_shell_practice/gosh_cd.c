#include "gosh.h"
/**
 * cd_dot - changes to the parent directory
 * @gosh_gosh: data relevant (environ)
 * Return: no return
 */
void cd_dot(go_shell *gosh_gosh)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cps_tok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = s_dup(pwd);
	gosh_set_env("OLDPWD", cp_pwd, gosh_gosh);
	dir = gosh_gosh->g_args[1];
	if (s_cmp(".", dir) == 0)
	{
		gosh_set_env("PWD", cp_pwd, gosh_gosh);
		free(cp_pwd);
		return;
	}
	if (s_cmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cps_tok_pwd = cp_pwd;
	g_rev_string(cps_tok_pwd);
	cps_tok_pwd = s_tok(cps_tok_pwd, "/");
	if (cps_tok_pwd != NULL)
	{
		cps_tok_pwd = s_tok(NULL, "\0");

		if (cps_tok_pwd != NULL)
			g_rev_string(cps_tok_pwd);
	}
	if (cps_tok_pwd != NULL)
	{
		chdir(cps_tok_pwd);
		gosh_set_env("PWD", cps_tok_pwd, gosh_gosh);
	}
	else
	{
		chdir("/");
		gosh_set_env("PWD", "/", gosh_gosh);
	}
	gosh_gosh->g_status = 0;
	free(cp_pwd);
}

/**
 * cd_to - changes to a directory given
 * by the user
 *
 * @gosh_gosh: data relevant (directories)
 * Return: no return
 */
void cd_to(go_shell *gosh_gosh)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = gosh_gosh->g_args[1];
	if (chdir(dir) == -1)
	{
		get_error(gosh_gosh, 2);
		return;
	}

	cp_pwd = s_dup(pwd);
	gosh_set_env("OLDPWD", cp_pwd, gosh_gosh);

	cp_dir = s_dup(dir);
	gosh_set_env("PWD", cp_dir, gosh_gosh);

	free(cp_pwd);
	free(cp_dir);

	gosh_gosh->g_status = 0;

	chdir(dir);
}

/**
 * cd_previous - changes to the previous directory
 *
 * @gosh_gosh: data relevant (environ)
 * Return: no return
 */
void cd_previous(go_shell *gosh_gosh)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = s_dup(pwd);

	p_oldpwd = _get_env("OLDPWD", gosh_gosh->g_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = s_dup(p_oldpwd);

	gosh_set_env("OLDPWD", cp_pwd, gosh_gosh);

	if (chdir(cp_oldpwd) == -1)
		gosh_set_env("PWD", cp_pwd, gosh_gosh);
	else
		gosh_set_env("PWD", cp_oldpwd, gosh_gosh);

	p_pwd = _get_env("PWD", gosh_gosh->g_environ);

	write(STDOUT_FILENO, p_pwd, s_len(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	gosh_gosh->g_status = 0;

	chdir(p_pwd);
}

/**
 * cd_to_home - changes to home directory
 *
 * @gosh_gosh: data relevant (environ)
 * Return: no return
 */
void cd_to_home(go_shell *gosh_gosh)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = s_dup(pwd);

	home = _get_env("HOME", gosh_gosh->g_environ);

	if (home == NULL)
	{
		gosh_set_env("OLDPWD", p_pwd, gosh_gosh);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(gosh_gosh, 2);
		free(p_pwd);
		return;
	}

	gosh_set_env("OLDPWD", p_pwd, gosh_gosh);
	gosh_set_env("PWD", home, gosh_gosh);
	free(p_pwd);
	gosh_gosh->g_status = 0;
}
