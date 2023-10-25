#include "gosh.h"
/**
 * _slops_comp - compares if two characters equate to a logical op
 * @s_lops: the s logical operator
 * @a: the first char
 * @b: the second char
 * Return: -1 if syntax error is noticed.
 *          0 if they don't match, 1 if there is a match.
 */
int _slops_comp(char *s_lops, char a, char b)
{
	int a_match = 0, b_match = 0, i = 0;

	if (a == b)
	{
		while (s_lops[i])
		{
			if (s_lops[i] == a)
			{
				a_match = 1;
				break;
			}
			i++;
		}
		return (a_match);
	}
	else
	{
		while (s_lops[i])
		{
			if (s_lops[i] == a)
			{
				a_match = 1;
				break;
			}
			i++;
		}
		i = 0;
		while (s_lops[i])
		{
			if (s_lops[i] == b)
			{
				b_match = 1;
				break;
			}
			i++;
		}
		if (a_match && b_match)
			return (-1);
		return (0);
	}
}
