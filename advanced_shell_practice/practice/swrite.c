#include "debs.h"

/**
 * swrite - custom putchar function
 * @c: parameter passed
 * Return: write call system
 */

int swrite(char c)
{
	return (write(1, &c, 1));

}
