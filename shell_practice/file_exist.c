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
