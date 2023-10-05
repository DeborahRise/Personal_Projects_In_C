#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/**
 * main - a simple sheall mimick
 * Return: 0;
 */

int main(void)
{
	char *cmd = NULL, *delim = " \n", *cmd_cpy = NULL, **argv = NULL, *token = NULL;
	size_t space = 0;
	int argc = 0, i = 0, val;

	pid_t pid;

	while (1)
	{

		printf("gosh:):");

		if (getline(&cmd, &space, stdin) == -1)
			return (-1);

		cmd_cpy = strdup(cmd);

		token = strtok(cmd, delim);

		while (token)
		{
			printf("%s\n", token);
			token = strtok(NULL , delim);
			argc++;

		}
		printf("%d\n", argc);
		argv = malloc(sizeof(char *) * argc);

		token = strtok(cmd_cpy, delim);

		while (token)
		{
			argv[i] = token;
			printf("%s\n", argv[i]);
			token = strtok(NULL , delim);
			i++;

		}

		pid = fork();
		if (pid == -1)
			return (-1);

		if (pid == 0)
		{
			val = execve(argv[0], argv, NULL);
			if (val == -1)
				perror("error");
		}
		else
		{
			wait(NULL);
			printf("done\n");
			free(cmd_cpy), free(cmd), free(argv);

		}



	}
	return (0);
}
