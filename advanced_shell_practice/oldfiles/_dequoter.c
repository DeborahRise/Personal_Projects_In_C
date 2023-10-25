#include "gosh.h"
/**
 * _dequoter - removes quotation marks before and after strings
 * @strval: the string to be dequoted
 * Return: the string without quotation marks or NULL if error occurs.
 */
char *_dequoter(char *strval)
{
	char a = '\'', b = '\"', c = '\0', *newstr;
	size_t i = 0, len = strlen(strval), sz = 0, max = len - 2;
	ssize_t n;

	if ((*strval == a && strval[len - 1]  != a) ||
			(*strval == b && strval[len - 1] != b))
	{
		n = write(1, "> ", 2);
		if (n <= 0)
			return (NULL);
		n = read(0, &c, 1);
		if (n < 0 || c != strval[0])
			return (NULL);
		sz = n + len;
	}
	if ((*strval == a && strval[len - 1] == a) ||
			(*strval == b && strval[len - 1] == b))
	{
		newstr = malloc(sz ? sz + len : len);
		if (!newstr)
			return (NULL);
		for (i = 1; i <= max; i++)
			newstr[i - 1] = strval[i];
		if (sz)
			newstr[i - 1] = c, newstr[i] = '\0';
		else
			newstr[i - 1] = '\0';
		return (newstr);
	}
	return (NULL);
}
