#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

/**
 *
 */

int main(int ac, char **av, char **envp)
{


	pid_t forkpid;

	forkpid = fork();

	if (forkpid == -1)
		return (-1);
	if (forkpid == 0)
	{
	if (execve(av[1], av, NULL) == -1)
			return (-1);
	printf("child\n");
	}
	else
	{
		wait(NULL);
		printf("parent\n");
	}
	return (0);
}
