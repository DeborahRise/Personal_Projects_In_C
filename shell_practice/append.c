#include <stdio.h>
#include <string.h>

int main(void)
{
	char a[] = "../bin/ls";
	char b[] = "root/user/local/";
	int x = strlen(b);
	for (int i = 3; a[i] != '\0'; i++)
		 {
			b[x] = a[i];
			x++;
		 }
	b[x] = '\0';
	printf("%s\n", b);
	return (0);
}
