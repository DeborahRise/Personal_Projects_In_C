#include "gosh.h"

/**
 * gosh_print_unint_number - a function that prints unsigned int
 * @djlist2: paramater from va-arg(list, unsigned int)
 * Return: count of output
 */
int gosh_print_unint_number(va_list djlist2)
{
	unsigned int n = va_arg(djlist2, unsigned int);
	int num, last = n % 10, digit, exp = 1;
	int  i = 1;

	n = n / 10;
	num = n;

	if (last < 0)
	{
		s_write('-');
		num = -num;
		n = -n;
		last = -last;
		i++;
	}
	if (num > 0)
	{
		while (num / 10 != 0)
		{
			exp = exp * 10;
			num = num / 10;
		}
		num = n;
		while (exp > 0)
		{
			digit = num / exp;
			s_write(digit + '0');
			num = num - (digit * exp);
			exp = exp / 10;
			i++;
		}
	}
	s_write(last + '0');

	return (i);
}
