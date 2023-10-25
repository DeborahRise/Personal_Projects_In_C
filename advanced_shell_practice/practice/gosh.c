#include "debs.h"

/**
 * main - a gosh custom shell
 * Return: exits or -1 on error
 */

#define MAX_INPUT_SIZE 100

int main(void)
{
	char *gcmd = NULL, *gprompt = "($) ";
	char *token, *av[MAX_INPUT_SIZE];
	ssize_t ret;
	size_t gsize = 0;
	pid_t gpid;

	while (1)
	{
		/* write(1, gprompt, slen(gprompt)); */
		sprint(gprompt);
		ret = getline(&gcmd, &gsize, stdin);
		if (ret < 0)
			return (-1);

		if (ret > 0 && gcmd[0] != '\n')
		{
			gcmd[ret - 1] = '\0';
			token = stok(gcmd, " ");

			if (token != NULL)
			{
				int ac = 0;

				while (token != NULL && ac < MAX_INPUT_SIZE - 1)
				{
					av[ac] = token;
					token = stok(NULL, " ");
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
	return (0);
}
