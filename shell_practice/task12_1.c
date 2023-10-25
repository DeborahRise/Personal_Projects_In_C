#include <stdio.h>
#include <string.h>

/* Function to execute a command (you should implement this) */
int gcmd_exec(const char *command)
{
	/* Implement code to execute the command */
	printf("Executing: %s\n", command);
	return 0;
}

int main(void)
   {
	char *aa = "ls -la ; echo whatever && cat file.c || cat file2.c";
	char *a = strdup(aa);

	char *token = strtok(a, " ");
	char *prev_command = NULL;
	int ret = 0;

	while (token != NULL) {
		if (strcmp(token, ";") == 0 || strcmp(token, "&&") == 0 || strcmp(token, "||") == 0)
		{
			if (prev_command != NULL)
			{
				ret = gcmd_exec(prev_command);
				if (strcmp(token, "&&") == 0 && ret != 0)
				{
					break;
				}
				else if (strcmp(token, "||") == 0 && ret == 0)
				{
					break;
				}
			}
			prev_command = NULL;
		}
		else
		{
			if (prev_command == NULL)
			{
				prev_command = strdup(token);
			}
			else
			{
				char *temp = malloc(strlen(prev_command) + strlen(token) + 2);
				strcpy(temp, prev_command);
				strcat(temp, " ");
				strcat(temp, token);
				free(prev_command);
				prev_command = temp;
			}
		}
		token = strtok(NULL, " ");
	}

	if (prev_command != NULL)
	{
		ret = gcmd_exec(prev_command);
	}

	return (ret);
}

