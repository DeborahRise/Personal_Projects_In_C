#include "debs.h"
/**
 * tok - a custom strtok function
 * @str: string passed
 * @delim: delimeter
 * Return: pointer to token
 */

char *stok(char *str, char *delim)
{
	static char *GRAND = NULL;

	int i, k, found, del = strlen(delim);
	char *copy, *retstr;

	if (str == NULL)
	{
		str = GRAND;
	}

	if (str == NULL)
	{
		return (NULL);
	}

	copy = str;
	i = 0;
	while (copy[i] != '\0')
	{
		found = 0;
		for (k = 0; k < del && !found; k++)
		{
			if (copy[i] == delim[k])
				found = 1;
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
					GRAND = NULL, retstr = copy;

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
