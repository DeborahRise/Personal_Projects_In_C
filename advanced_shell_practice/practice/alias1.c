#include "gosh.h"

/**
 * gosh_print_aliases - a function that prints alias to stdout
 * @alias_list: the list containing aliases
 * @alias_count: the number of entered alias
 * Return: void
 */
int gosh_print_aliases(struct alias alias_list[], int *alias_count)
{
	int i;

	for (i = 0; i < *alias_count; i++)
	{
		gosh_printf("alias %s='%s'\n",
				alias_list[i].a_name,
				alias_list[i].a_value);
	}
	return (0);
}

/**
 * gosh_find_alias - Function to find an alias by name
 * @alias_list: the list containing aliases
 * @alias_count: the number of entered alias
 * @name: name searched
 * struct alias - Represents an alias in the custom shell
 * Return: alias_list of data type struct alias.
 */
struct alias *gosh_find_alias(struct alias alias_list[],
		int *alias_count, char *name)
{
	struct alias;

	int i;

	for (i = 0; i < *alias_count; i++)
	{
		if (s_cmp(name, alias_list[i].a_name) == 0)
		{
			return (&alias_list[i]);
		}
	}
	return (NULL);
}

/**
 * gosh_define_alias - Function to define or update an alias
 * @alias_list: the list containing aliases
 * @alias_count: the number of entered alias
 * @name: name passed
 * @value: value passed
 * Return: alias_list of data type struct alias.
 */
int gosh_define_alias(struct alias alias_list[],
		int *alias_count, char *name, char *value)
{
	struct alias *existing = gosh_find_alias(alias_list, alias_count, name);

	if (existing)
	{
		/* Update an existing alias */
		s_ncpy(existing->a_value, value, MAX_A_VALUE);
	}
	else if (*alias_count < MAX_A_VAR_SIZE)
	{
		/* Define a new alias */
		s_ncpy(alias_list[*alias_count].a_name, name, MAX_A_NAME);
		s_ncpy(alias_list[*alias_count].a_value, value, MAX_A_VALUE);
		(*alias_count)++;
	}
	else
	{
		gosh_printf("Alias limit exceeded. Unable to define alias.\n");
		return (-1);
	}
	return (0);
}

