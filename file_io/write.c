#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fp;
	char str[23];

	fp = fopen("debie.txt", "w");
	if (fp == NULL)
	{
		printf("an error occured");
		exit(1);
	}

	printf("what u wanna write:");
	scanf("%s", str);
	fputs(str, fp);
	fclose(fp);
	return (0);
}
