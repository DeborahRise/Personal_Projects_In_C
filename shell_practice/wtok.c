#include <stdio.h>
char *CHARPTR = NULL;
char *_strtok(char *str, char *d)
{
	char *str_cpy;
	int i = 0;
	str_cpy = str;
	if (!str_cpy)
	{
		if (!CHARPTR)
			return (NULL);
		while (CHARPTR[i] != *d)
		{
			if (CHARPTR[i] == '\0')
			{
				str_cpy = CHARPTR, CHARPTR = NULL;
				return(str_cpy);
			}
			i++;
		}
		CHARPTR[i]  = '\0';
		str_cpy = CHARPTR, CHARPTR += (i + 1);
		return (str_cpy);
	}
	while (str_cpy[i] != *d)
	{
		if (str_cpy[i] == '\0')
			return (str_cpy);
		i++;
	}
	str_cpy[i] = '\0', CHARPTR = (str_cpy + (i + 1));
	return (str_cpy);
}
int main(void)
{
	char *str = "this is incredible";
	char *tok;

	tok = _strtok(str, " ");
	while (tok)
	{
		printf("%s\n", tok);
		tok = _strtok(NULL, " ");
	}
	return (0);
}
