#include <stdio.h>
#include <string.h>

/**
 * main - a program to handle the semicolon, logical && and || operator in my custom shell
 */

int main(void)
{
	char *aa = "ls -la ; echo whatever && cat file.c || cat file2.c";

	char *a = strdup(aa);

	int i = 0;
	while (a[i] != '\0')
	{
		if (a[i] == ";")
		{
			int n_semi = i;
			for (i = 0; i < n_semi; i++)
			{
				char *semi;
				semi[i] = a[i];
			}
				gcmd_exec(semi);

		}
		else if (a[i] == "&&")
		{
			int n_and = i;
			char *and;
			for (i = 0; i < n_and; i++)
			{
				and [i] = a[i];
			}
			int ret = gcmd_exec(and);
			if ret != 0;
			break;
		}
		else if (a[i] == "||")
		{
			int n_or = i;
			char *or;
			for (i = 0; i < n_or; i ++)
			{
				or[i] = a[i];
			}
			int ret = gcmd_exec(or);
			if ret = 0;
			break;
		}
		i = i + 1;
		a = aa + i;
 	}
return (0);
}
