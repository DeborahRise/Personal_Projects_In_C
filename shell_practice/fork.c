#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

/**
 *
 */

int main()
{


	pid_t forkpid;
	char *av[] = {"/bin/ls", "-l", "/tmp", NULL};

	forkpid = fork();

	if (forkpid == -1)
		return (-1);
	if (forkpid == 0)
	{
		if (execve(av[0], av, NULL) == -1)
			return (-1);
		printf("child\n");
	}
	else
	{
		wait(NULL);
		printf("pid is %u\n ppid is %u\n forkpid in parent is %u\n", getpid(), getppid(), forkpid);
	}
	return (0);
}
