#include "gosh.h"

/**
 * add_gosh_sep_node_end - adds a separator found at the end
 * of a goshell sep_list.
 * @head: head of the linked list.
 * @separator: separator found (| ; &).
 * Return: address of the head.
 */
gosh_sep_list *add_gosh_sep_node_end(gosh_sep_list **head, char separator)
{
	gosh_sep_list *new, *temp;

	new = malloc(sizeof(gosh_sep_list));
	if (new == NULL)
		return (NULL);

	new->g_separator = separator;
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
 * free_gosh_sep_list - frees a gosh_sep_list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_gosh_sep_list(gosh_sep_list **head)
{
	gosh_sep_list *temp;
	gosh_sep_list *curr;

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

/**
 * add_gosh_line_end - adds a command line at the end
 * of a gosh_cmd_line.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
gosh_cmd_line *add_gosh_line_node_end(gosh_cmd_line **head, char *gcmd_line)
{
	gosh_cmd_line *new, *temp;

	new = malloc(sizeof(gosh_cmd_line));
	if (new == NULL)
		return (NULL);

	new->gcmd_line = gcmd_line;
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
 * free_gosh_cmd_line - frees a gosh_cmd_line
 * @head: head of the linked list.
 * Return: no return.
 */
void free_gosh_cmd_line(gosh_cmd_line **head)
{
	gosh_cmd_line *temp;
	gosh_cmd_line *curr;

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
