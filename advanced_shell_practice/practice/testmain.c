#include "debs.h"
/**
 * main - test file
 * Return: 0 on success
 */

int main(void)
{

	char str[] = ":::so, that;wont/work? why though?";
	char *delim = ":,;/? ";
	int a = slen(str), b = slen(delim);
	char *token = stok(str, delim);
	int stoken = slen(token);


	while (token)
	{
		printf("%s\n", token);
		token = stok(NULL, delim);
	}

	printf("str len :%d\n delim len:%d\n len token: %d\n", a, b, stoken);
	return (0);
}
