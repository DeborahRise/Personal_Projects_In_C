#include "gosh.h"

/**
 * add_gosh_variables_node - adds a variable at the end
 * of a gosh_variables list.
 * @head: head of the linked list.
 * @lvar: length of the variable.
 * @val: value of the variable.
 * @lval: length of the value.
 * Return: address of the head.
 */
gosh_variables *add_gosh_variables_node(gosh_variables **head,
		int lvar, char *val, int lval)
{
	gosh_variables *new, *temp;

	new = malloc(sizeof(gosh_variables));
	if (new == NULL)
		return (NULL);

	new->g_len_var = lvar;
	new->g_val = val;
	new->g_len_val = lval;

	new->g_next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->g_next != NULL)
			temp = temp->g_next;
		temp->g_next = new;
	}

	return (*head);
}

/**
 * free_gosh_variables_list - frees a gosh_variable list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_gosh_variables_list(gosh_variables **head)
{
	gosh_variables *temp;
	gosh_variables *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->g_next;
			free(temp);
		}
		*head = NULL;
	}
}
