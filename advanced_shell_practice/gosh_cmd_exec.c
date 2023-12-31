#include "gosh.h"

/**
 * gosh_c_dir - checks ":" if is in the current directory.
 * @path: type char pointer char.
 * @i: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int gosh_c_dir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * gosh_which - locates a command
 *
 * @cmd: command name
 * @g_environ: environment variable
 * Return: location of the command.
 */
char *gosh_which(char *cmd, char **g_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _get_env("PATH", g_environ);
	if (path)
	{
		ptr_path = s_dup(path);
		len_cmd = s_len(cmd);
		token_path = s_tok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (gosh_c_dir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = s_len(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			s_copy(dir, token_path);
			s_cat(dir, "/");
			s_cat(dir, cmd);
			s_cat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = s_tok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * gosh_is_executable - determines if is an executable
 *
 * @gosh_gosh: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int gosh_is_executable(go_shell *gosh_gosh)
{
	struct stat st;
	int i;
	char *input;

	input = gosh_gosh->g_args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	get_error(gosh_gosh, 127);
	return (-1);
}

/**
 * gosh_check_error_cmd - verifies if user has permissions to access
 *
 * @dir: destination directory
 * @gosh_gosh: data structure
 * Return: 1 if there is an error, 0 if not
 */
int gosh_check_error_cmd(char *dir, go_shell *gosh_gosh)
{
	if (dir == NULL)
	{
		get_error(gosh_gosh, 127);
		return (1);
	}

	if (s_cmp(gosh_gosh->g_args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(gosh_gosh, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(gosh_gosh->g_args[0], X_OK) == -1)
		{
			get_error(gosh_gosh, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * gosh_cmd_exec - executes command lines
 *
 * @gosh_gosh: data relevant (args and input)
 * Return: 1 on success.
 */
int gosh_cmd_exec(go_shell *gosh_gosh)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = gosh_is_executable(gosh_gosh);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = gosh_which(gosh_gosh->g_args[0], gosh_gosh->g_environ);
		if (gosh_check_error_cmd(dir, gosh_gosh) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = gosh_which(gosh_gosh->g_args[0], gosh_gosh->g_environ);
		else
			dir = gosh_gosh->g_args[0];
		execve(dir + exec, gosh_gosh->g_args, gosh_gosh->g_environ);
	}
	else if (pd < 0)
	{
		perror(gosh_gosh->agv[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	gosh_gosh->g_status = state / 256;
	return (1);
}
