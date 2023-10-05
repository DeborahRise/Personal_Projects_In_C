#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
 *
 */

char *tok(char *str, char *delim)
{
static char *GRAND = NULL;

	int i;
	char *copy;

	if (str == NULL)
	{
		str = GRAND;
	}

	if (str == NULL)
	{
		return (NULL);
	}


	copy = strdup(str);


	i = 0;
	while (copy[i] != *delim && copy[i])
	{
		i++;
	}
	if (copy[i] == '\0')
	{

		GRAND = NULL;
	}
	else
	{
		copy[i] = '\0';
		GRAND = str + i + 1;
	}

	return (copy);
}

int main()
{
	char *str = "When will you?";
	char *delim = " ";
	char *token = tok(str, delim);
	while(token)
	{
	printf("%s\n", token);
	token = tok(NULL, delim);
	}

	return (0);

}
