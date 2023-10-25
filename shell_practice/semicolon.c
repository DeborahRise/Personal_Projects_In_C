
if (ret > 0 && gcmd[0] != '\n')
{
	gcmd[ret - 1] = '\0';

/* 	the strchr function that checks for the presence of certain characters */
/* where str is gcmd and char c is either &&, ||, or ; */

char *s_chr(char *str, char c)
{
	while (*str != '\0')
	{
		if (*str == c)
		{
			return (char *)str;
		}
		str++;
	}
	return NULL;
}
if (s_chr(gcmd, &&) != NULL)
{
	tokenise the string using && as delim.
	char *and[] = specialtok(gcmd, &&);
	/* note, it will return a 2d array */
	parse the array again for the presence of || using the s_chr() func.
	for (i = 0; and[] != NULL; i++)
}



/* first step now will be to Split input */
/* by semicolon to separate multiple commands */
char **semicolon_ops(gcmd, delim)
{
char *commands[MAX_INPUT_SIZE];
char *token = strtok(gcmd, ";");
int num_commands = 0;

while (token != NULL && num_commands < MAX_INPUT_SIZE)
{
	/* creating an array of commands */
	commands[num_commands] = token;
	token = strtok(NULL, ";");
	num_commands++;
}
}

/* Execute each command */
for (int i = 0; i < num_commands; i++)
{
	int func_ret_val = get_args(commands[i]);

}


