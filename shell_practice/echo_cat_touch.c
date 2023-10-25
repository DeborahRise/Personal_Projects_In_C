#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 100

void removeComments(char *command) {
    char *commentPos = strchr(command, '#');
    if (commentPos != NULL) {
        *commentPos = '\0';  // Null-terminate the command at the '#' character
    }
}

int main(void) {
    char *gcmd = NULL, *gprompt = "($) ";
    ssize_t ret;
    size_t gsize = 0;
    pid_t gpid;
    int last_exit_status = 0;  // Initialize to 0

    while (1) {
        write(1, gprompt, strlen(gprompt));

        ret = getline(&gcmd, &gsize, stdin);
        if (ret < 0) {
            return -1;
        }

        if (ret > 0 && gcmd[0] != '\n') {
            gcmd[ret - 1] = '\0';  // Remove trailing newline

            removeComments(gcmd);

            char *token = strtok(gcmd, " ");
            if (token != NULL) {
                if (strcmp(token, "echo") == 0) {
                    // Handle the echo command
                    token = strtok(NULL, " ");
                    while (token != NULL) {
                        printf("%s ", token);
                        token = strtok(NULL, " ");
                    }
                    printf("\n");
                } else if (strcmp(token, "cat") == 0) {
                    // Handle the cat command
                    token = strtok(NULL, " ");
                    while (token != NULL) {
                        int fd = open(token, O_RDONLY);
                        if (fd == -1) {
                            perror(token);
                            return -1;
                        }
                        char buffer[MAX_INPUT_SIZE];
                        ssize_t bytes_read;
                        while ((bytes_read = read(fd, buffer, MAX_INPUT_SIZE)) > 0) {
                            write(1, buffer, bytes_read);
                        }
                        close(fd);
                        token = strtok(NULL, " ");
                    }
                } else if (strcmp(token, "touch") == 0) {
                    // Handle the touch command
                    token = strtok(NULL, " ");
                    while (token != NULL) {
                        int fd = open(token, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
                        if (fd == -1) {
                            perror(token);
                            return -1;
                        }
                        close(fd);
                        token = strtok(NULL, " ");
                    }
                } else if (strcmp(token, "exit") == 0) {
                    // Handle the "exit" command
                    free(gcmd);
                    return last_exit_status;
                } else {
                    gpid = fork();
                    if (gpid == -1) {
                        perror("Fork error");
                        return -1;
                    }
                    if (gpid == 0) {
                        // Execute the command with arguments
                        if (execvp(token, &token) == -1) {
                            perror(token);
                            return -1;
                        }
                    } else {
                        wait(&last_exit_status);
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
l
