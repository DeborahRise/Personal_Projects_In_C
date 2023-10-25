#include "gosh.h"

/**
 * s_write - custom putchar function
 * @c: parameter passed
 * Return: write call system
 */

int s_write(char c)
{
	return (write(1, &c, 1));
}
