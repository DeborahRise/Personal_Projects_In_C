#include gosh.h

/*
 *
 */

void *ch_dir(char *str)
{
else if (strcmp(token, "cd") == 0)
{
	token = strtok(NULL, " ");
	if (token == NULL || strcmp(token, "~") == 0)
	{
		char *home_dir = getenv("HOME");
		if (home_dir != NULL)
		{
			if (chdir(home_dir) != 0)
			{
				perror("chdir");
			}
		}
		else
		{
			fprintf(stderr, "HOME environment variable not set.\n");
		}
	}
	else
	{
		/*first save current directory*/
		char *current_dir = getcwd(NULL, 0);
		if (current_dir != NULL)
		{
			setenv("OLDPWD", current_dir, 1);
			free(current_dir);
		}
		if (chdir(token) == 0)
		{
			/*Update the PWD environment variable*/

			char *new_pwd = getcwd(NULL, 0);
			if (new_pwd != NULL)
			{
				setenv("PWD", new_pwd, 1);
				free(new_pwd);
			}
		}
		else
			perror("chdir");

		if (strcmp(token, "-") == 0)
		{
			char *prev_dir = getenv("OLDPWD");
			if (prev_dir != NULL)
			{

				if (chdir(prev_dir) != 0)
				{
					perror("chdir");
				}
			}
			else
			{
				fprintf(stderr, "Usage: %s [DIRECTORY]\n", prev_dir);
			}
		}
	}
}
}
