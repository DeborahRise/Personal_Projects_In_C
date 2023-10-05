#include <stdio.h>
#include <stdlib.h>

/**
 *
 */

int main()
{
	int val;
	size_t n = 0;
	char *cmd = NULL;


	printf("$");

	val = getline(&cmd, &n, stdin);
	if (val == -1)
		return (-1);
	printf("%s %lu", cmd, n);

	free(cmd);


	return (0);


}
