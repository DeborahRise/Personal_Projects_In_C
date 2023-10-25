#include "gosh.h"

/**
 * check_env - checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @in: input string
 * @data: data structure
 * Return: no return
 */
void check_env(gosh_variables **h, char *in, go_shell *data)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = data->g_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = s_len(_envr[row] + chr + 1);
				add_gosh_variables_node(h, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	add_gosh_variables_node(h, j, NULL, 0);
}

/**
 * check_vars - check if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int check_vars(gosh_variables **h, char *in, char *st, go_shell *data)
{
	int i, lst, lpd;

	lst = s_len(st);
	lpd = s_len(data->gpid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_gosh_variables_node(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				add_gosh_variables_node(h, 2, data->gpid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_gosh_variables_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_gosh_variables_node(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_gosh_variables_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_gosh_variables_node(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_gosh_variables_node(h, 0, NULL, 0);
			else
				check_env(h, in + i, data);
		}
	}

	return (i);
}

/**
 * replaced_input - replaces string into variables
 *
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *replaced_input(gosh_variables **head, char *input,
		char *new_input, int nlen)
{
	gosh_variables *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->g_len_var) && !(indx->g_len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->g_len_var && !(indx->g_len_val))
			{
				for (k = 0; k < indx->g_len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->g_len_val; k++)
				{
					new_input[i] = indx->g_val[k];
					i++;
				}
				j += (indx->g_len_var);
				i--;
			}
			indx = indx->g_next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * rep_var - calls functions to replace string into vars
 *
 * @input: input string
 * @gosh_gosh: data structure
 * Return: replaced string
 */
char *rep_var(char *input, go_shell *gosh_gosh)
{
	gosh_variables *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = gosh_itoa(gosh_gosh->g_status);
	head = NULL;

	olen = check_vars(&head, input, status, gosh_gosh);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->g_len_val - indx->g_len_var);
		indx = indx->g_next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_gosh_variables_list(&head);

	return (new_input);
}
