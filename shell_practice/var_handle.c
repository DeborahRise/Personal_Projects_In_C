#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 100

/* Function to remove comments from a command */
void Comment_handler(char *gcmd)
{
    char *commentPos = strchr(command, '#');
    if (commentPos != NULL)
	{
        *commentPos = '\0';
		/* Null-terminate the command at the '#' character */
    }
}


/* Function to replace a variable with its value in a string */
void replaceVariable(char *str, const char *variable, const char *value) {
	char *start = str;  // Pointer to the start of the input string
	char *result = str;  // Pointer to the result string

	/* Iterate through the input string */
	while (*str)
	{
		/* Check if the current position matches the variable */
		if (strncmp(str, variable, strlen(variable)) == 0)
		{
		 /* Variable found, replace it with the value */
			for (const char *val = value; *val; val++)
			{
				*result++ = *val;
				/* Copy the value character by character */
			}
			str += strlen(variable);
			/* Move the input string pointer past the variable */
		} else
		{
			/* Copy the character from the input string to the result string */
			*result++ = *str++;
		}
	}

	/* Null-terminate the result string */
	*result = '\0';
}

int main(void) {
	char *gcmd = NULL, *gprompt = "($) ";
	ssize_t ret;
	size_t gsize = 0;
	pid_t gpid;
	int last_exit_status = 0;  // Initialize to 0

	while (1)
	{
		write(1, gprompt, strlen(gprompt));

		ret = getline(&gcmd, &gsize, stdin);
		if (ret < 0)
		{
			return -1;
		}

		if (ret > 0 && gcmd[0] != '\n') {
			gcmd[ret - 1] = '\0';

			Comment_handler(gcmd);

			char *token = strtok(gcmd, " ");
			if (token != NULL) {
				if (strcmp(token, "echo") == 0)
				{
					/* Get the variable name */

					token = strtok(NULL, " ");

					if (token != NULL) {
						if (strcmp(token, "$?") == 0)
						{
							printf("%d\n", last_exit_status);
						}
						else if (strcmp(token, "$$") == 0)
						{
							printf("%d\n", getpid());
						}
					} else if (strcmp(token, "$PATH") == 0) {
						printf("%s\n", customPath);
						/* Replace with your custom PATH */
					}
				}
			}
			else
			{
				gpid = fork();
				if (gpid == -1)
				{
					perror("Fork error");
					return -1;
				}
				if (gpid == 0)
				{
					/* Execute the command with arguments */
					if (execve (pathname, av, env) == -1) {
						perror(token);
						return -1;
					}
				}
				else
				{
					wait(&last_exit_status);
				}
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

