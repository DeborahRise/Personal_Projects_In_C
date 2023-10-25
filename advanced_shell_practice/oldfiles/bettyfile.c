#include <stdio.h>
#include <unistd.h>

/**
 * main - Entry point
 * Description goes here
 * Return: 0 always
 */
int main(void)
{
	int n;
	char str[] = "Some beautiful code that passes Betty\n";

	n = write(1, str, s_len(str));
	if (n < 0)
		return (-1);
	return (0);
}
