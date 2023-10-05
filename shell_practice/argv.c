#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	int i, x = 0;
	for (i = 0; av[i]; i++)
	{
		x += atoi(av[i]);

		printf("%d is the sum of %s\n", x, av[i]);

	}
	return (0);
}
