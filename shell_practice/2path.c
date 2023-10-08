#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 100

// Function to check if a file exists in a given directory
int fileExistsInDirectory(const char *command, const char *directory) {
	char path[MAX_INPUT_SIZE];
	size_t i = 0;

	// Copy the directory path to the 'path' variable
	while (directory[i] != '\0' && i < MAX_INPUT_SIZE - 1) {
		path[i] = directory[i];
		i++;
	}

	// Append a '/' character to separate the directory and command
	if (i < MAX_INPUT_SIZE - 1) {
		path[i] = '/';
		i++;
	}

	// Copy the command to the 'path' variable
	size_t j = 0;
	while (command[j] != '\0' && i < MAX_INPUT_SIZE - 1) {
		path[i] = command[j];
		i++;
		j++;
	}

	// Null-terminate the 'path' string
	path[i] = '\0';

	return access(path, X_OK) == 0;
}

int main(void) {
	char *gcmd = NULL, *gprompt = "($) ";
	ssize_t ret;
	size_t gsize = 0;
	pid_t gpid;
	char *directory;

	while (1) {
		write(1, gprompt, strlen(gprompt));

		ret = getline(&gcmd, &gsize, stdin);
		if (ret < 0) {
			return (-1);
		}

		if (ret > 0 && gcmd[0] != '\n') {
			gcmd[ret - 1] = '\0'; // Remove trailing newline
			char *token = strtok(gcmd, " ");

			if (token != NULL) {
				int ac = 0;
				char *av[MAX_INPUT_SIZE];

				while (token != NULL && ac < MAX_INPUT_SIZE - 1) {
					av[ac] = token;
					token = strtok(NULL, " ");
					ac++;
				}

				av[ac] = NULL; // Terminate the av array with NULL

				// Check if the command exists in the directories specified in PATH
				char *path = getenv("PATH");
				if (path != NULL) {
					directory = strtok(path, ":");
					while (directory != NULL) {
						if (fileExistsInDirectory(av[0], directory)) {
							gpid = fork();
							if (gpid == -1) {
								perror("Fork error");
								return (-1);
							}
							if (gpid == 0) {
								// Execute the command with arguments
								if (execvp(av[0], av) == -1) {
									perror(av[0]);
									return (-1);
								}
							} else {
								wait(NULL);
							}
							break; // Exit the loop if the command is found
						}
						directory = strtok(NULL, ":");
					}
				}

				// If the loop completes without finding the command, display an error
				if (directory == NULL) {
					fprintf(stderr, "Command not found: %s\n", av[0]);
				}
			}
		} else {
			break;
		}
	}

	free(gcmd);
	return 0;
}
