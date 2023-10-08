#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 100


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
	char *directory;

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
						int ret_file = file_exist(av[0], directory);
						if (ret_file == 0)
						{
							gpid = fork();
							if (gpid == -1)
							{
								perror("Fork error");
								return (-1);
							}
							if (gpid == 0)
							{

								if (execvp(av[0], av) == -1)
								{
									perror(av[0]);
									return (-1);
								}
							}
							else
							{
								wait(NULL);
							}
							break;
						}
						directory = strtok(NULL, ":");
					}
				}
				if (directory == NULL) {
					fprintf(stderr, "Command not found: %s\n", av[0]);
				}
			}
		}
		else
		{
			break;
		}
	}

	free(gcmd);
	return 0;
}
