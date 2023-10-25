#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 *
 */

void logical_egde(char **cmdv)
{
	char *cmdv2 = strdup(cmdv);

	char *token = strtok(cmdv2, " "), temp;
	temp = (char *) malloc(sizeof(char) * strlen(cmdv) + 1);
	strcpy(temp, token);


	int i = 0;

	while (token)
	{
		cmdv[i] = token;
		if (strcmp(cmdv[i], "&&") == 0 || strcmp(cmdv[i], "||") == 0 || strcmp(cmdv[i], ";") == 0)
		{
			if (strcmp(cmdv[i + 1], "&&") == 0 || strcmp(cmdv[i + 1], "||") == 0 || strcmp(cmdv[i + 1], ";") == 0)
			{
				perror("syntax error around token %s\n", token);
			}
		}
		strcat(temp, " ");
		strcat(temp, token);
		token = strtok(NULL, " ");

		i++;
	}
}
