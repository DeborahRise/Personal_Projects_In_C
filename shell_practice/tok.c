#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
 * tok - a custom strtok function
 * @str: the string to be tokenized
 * @delim: the delimeters to tokenize by
 * Return: a char pointer to token.
 */

char *tok(char *str, char *delim)
{
	static char *GRAND = NULL;

	int i, k, found, del = strlen(delim);
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
	while (copy[i] != '\0')
	{
		found = 0;
		for (k = 0; k < del; k++)
		{
			if (copy[i] == delim[k])
			{
				found = 1;
				break;
			}
		}
		if (!found)
		{
			break;
		}
		i++;
	}
	copy = copy + i;

	i = 0;
	while (copy[i] != '\0')
	{
		k = 0;
		while (k < del)
		{
			if (copy[i] == delim[k])
			{
				copy[i] = '\0';
				k = 0;
				while (k < del && copy[i+1])
				{
					if (copy [i + 1] != delim[k])
					{
						k++;
					}
					else
					{
						i++;
						k = 0;
					}
				}
				if (copy[i + 1])
				{
					GRAND = copy + i + 1;
					return (copy);
				}
				else
				{
					GRAND = NULL;
					return (copy);
				}
			}
			k++;
		}
		i++;
	}
	GRAND = NULL;
	return (copy);
}

int main()
{
	char *str = ":::so, that;wont/work? why though?";
	char *delim = ":,;/? ";
	char *token = tok(str, delim);
	while(token)
	{
		printf("%s\n", token);
		token = tok(NULL, delim);
	}


	return (0);

}
