#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *GRAND = NULL;
/**
 *
 */

char *tok(char *str, char *delim)
{
	int i;

	if (str == NULL)
	{
		if (GRAND != NULL)
		{

		str = GRAND;
		str = tok(str, delim);
		}
		return (NULL);
	}

	char *copy = malloc(sizeof(char*) * strlen(str) + 1);
	/* strcpy(copy, str); */
	copy = str;



	while (copy[i] != *delim && copy[i])
	{
		i++;
	}
	GRAND = copy + i + 1;
	copy[i] = '\0';

	return (copy);
}

int main()
{
	char *str = "When will you?";
	char *delim = " ";
	char *token = tok(str, delim);
	printf("%s", token);

	return (0);

}
