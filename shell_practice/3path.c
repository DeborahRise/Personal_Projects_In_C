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
	snprintf(path, sizeof(path), "%s/%s", directory, command);
	return access(path, X_OK) == 0;
}

int main(void) {
	char *gcmd = NULL, *gprompt = "($) ";
	ssize_t ret;
	size_t gsize = 0;
	pid_t gpid;

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
					char *directory = strtok(path, ":");
					int found = 0; // Flag to indicate command found

					while (directory != NULL) {
						if (fileExistsInDirectory(av[0], directory)) {
							found = 1; // Set flag if command is found
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
						}
						directory = strtok(NULL, ":");
					}

					// If the loop completes without finding the command, display an error
					if (!found) {
						fprintf(stderr, "Command not found: %s\n", av[0]);
					}
				}
			}
		} else {
			break;
		}
	}

	free(gcmd);
	return 0;
}

