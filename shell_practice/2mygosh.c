#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 100

int main(void)
{
	char *gcmd = NULL, *gprompt = "($) ";
	ssize_t ret;
	size_t gsize = 0;
	pid_t gpid;

	while (1)
	{
		printf("($)");
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

				gpid = fork();

				if (gpid == -1)
				{
					perror("Fork error");
					return (-1);
				}

				if (gpid == 0)
				{
					if (execve(av[0], av, NULL) == -1)
					{
						perror(av[0]);
						return (-1);
					}
				}
				else
				{
					wait(NULL);
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
