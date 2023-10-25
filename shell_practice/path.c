#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

extern char **environ;

#define MAX_INPUT_SIZE 100

char *pathname(const char *command, const char *directory)
{
	char *pathname = NULL;
	size_t len = strlen(directory) + strlen(command) + 2; // +2 for '/' and '\0'

	pathname = (char *)malloc(sizeof(char) * len);
	if (pathname == NULL)
	{
		perror("malloc");
		return NULL;
	}
	size_t i = 0;


	while (directory[i] != '\0' && i < len - 1)
	{
		pathname[i] = directory[i];
		i++;
	}


	if (i < len - 1)
	{
		pathname[i] = '/';
		i++;
	}

	size_t j = 0;
	while (command[j] != '\0' && i < len - 1)
	{
		pathname[i] = command[j];
		i++;
		j++;
	}
	pathname[i] = '\0';
	if (access(pathname,  F_OK | X_OK) == 0)
	{
		return (pathname);
	}
	else
	{
		free(pathname);
		return (NULL);
	}
}




int file_exist(const char *command, const char *directory)
{
	char path[MAX_INPUT_SIZE];
	size_t i = 0;
	int Kup;


	while (directory[i] != '\0' && i < MAX_INPUT_SIZE - 1)
	{
		path[i] = directory[i];
		i++;
	}


	if (i < MAX_INPUT_SIZE - 1)
	{
		path[i] = '/';
		i++;
	}

	size_t j = 0;
	while (command[j] != '\0' && i < MAX_INPUT_SIZE - 1) {
		path[i] = command[j];
		i++;
		j++;
	}
	path[i] = '\0';
	printf("the path is: %s\n", path);
	Kup = (access(path, F_OK | X_OK));
	printf("kup: %d\n", Kup);
	if (Kup == 0)
		return (0);
	else
		return (-1);
}
int main(void)
{
	char *gcmd = NULL, *gprompt = "($) ";
	ssize_t ret;
	size_t gsize = 0;
	pid_t gpid;
	char *directory, *pathstep;

	while (1)
	{
		write(1, gprompt, strlen(gprompt));
		ret = getline(&gcmd, &gsize, stdin);
		if (ret < 0)
			return (-1);

		if (ret > 0 && gcmd[0] != '\n')
		{
			gcmd[ret - 1] = '\0';
			char *token = strtok(gcmd, " ");

			if (token != NULL)
			{
				if (strcmp(token, "exit") == 0)
				{
					/* Handle the "exit" command */
					token = strtok(NULL, " ");
					int status = 0;
					if (token != NULL)
					{
						status = atoi(token);
					}
					free(gcmd);
					exit(status);
				}
				else if (strcmp(token, "env") == 0)
				{
					// Handle the "env" command to print the environment
					char **env = environ;
					while (*env != NULL)
					{
						printf("%s\n", *env);
						env++;
					}
				}
				else if (strcmp(token, "setenv") == 0)
				{

					token = strtok(NULL, " ");
					char *value = strtok(NULL, " ");
					if (token != NULL && value != NULL)
					{
						if (setenv(token, value, 1) != 0)
						{
							fprintf(stderr, "Failed to set environment variable: %s=%s\n", token, value);
						}
					}
					else
					{
						fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
					}
				}
				else if (strcmp(token, "unsetenv") == 0)
				{
					token = strtok(NULL, " ");
					if (token != NULL)
					{
						if (unsetenv(token) != 0)
						{
							fprintf(stderr, "Failed to unset environment variable: %s\n", token);
						}
					}
					else
					{
						fprintf(stderr, "Usage: unsetenv VARIABLE\n");
					}
				}
				else
				{
					int ac = 0;
					char *av[MAX_INPUT_SIZE];

					while (token != NULL && ac < MAX_INPUT_SIZE - 1)
					{
						av[ac] = token;
						token = strtok(NULL, " ");
						ac++;
					}

					av[ac] = NULL;

					char *path = getenv("PATH");
					printf("PATH IS: %s\n", path);
					if (path != NULL)
					{
						directory = strtok(path, ":");
						while (directory != NULL)
						{
							printf("directory is: %s\n", directory);
							pathstep = pathname(av[0], directory);
							printf("pathstep is %s\n", pathstep);
							if (pathstep != NULL)
							{
								printf("pathstep22 is %s\n", pathstep);
								gpid = fork();
								if (gpid == -1)
								{
									perror("Fork error");
									return (-1);
								}
								if (gpid == 0)
								{

									if (execve(pathstep, av, NULL) == -1)
									{
										perror(pathstep);
										return (-1);
									}
								}
								else
								{
									wait(NULL);
								}
								free(pathstep);

								break;

							}

							directory = strtok(NULL, ":");
						}
					}
					if (directory == NULL)
					{
						fprintf(stderr, "Command not found: %s\n", av[0]);
					}
				}
			}
		}
		else
		{
			break;
		}

	}
	free(pathstep);
	free(gcmd);
	return 0;

}
