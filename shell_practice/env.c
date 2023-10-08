#include <stdio.h>

extern char **environ;

int main()
{
    // Print all environment variables
    for (char **e = environ; *e != NULL; e++) {
        printf("%s\n", *e);
    }

    return 0;
}

