#include <stdio.h>
#include <unistd.h>
extern char **environ;

int main(void)
{
	char *e;

	e = *environ;
	printf("%s\n", e);
	return (0);

}

