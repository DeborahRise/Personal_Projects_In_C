#ifndef DEB_H
#define DEB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

char *stok(char *str, char *delim);
size_t slen(const char *str);
int sprint(char *s);
char *scat(char *dest, char *src);
int scmp(char *s1, char *s2);
char *scopy(char *dest, char *src);
int swrite(char c);
#endif
