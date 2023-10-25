#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main() {
    char input[] = "ls -l && echo 'Hello' || echo 'World' && pwd";

	char delim[] = "& ";
    char *token = strtok(input, delim);
    char *prev_command = NULL;
    int prev_result = 1;
	/* Initialize to 1 to allow the first command to execute */

    while (token != NULL) {
        if (strcmp(token, "&&") == 0)
		{
           /* Handle logical AND operator */
            prev_command = strtok(NULL, " ");
            if (prev_command != NULL)
			{
                int result = get_args()(prev_command);
                if (result != 0)
				{
                    /* If the previous command fails, stop execution */
                    break;
                }
                prev_result = result;
            }
        }
		else if (strcmp(token, "||") == 0)
		{
            /* Handle logical OR operator */
            prev_command = strtok(NULL, " ");
            if (prev_command != NULL)
			{
                int result = get_args(prev_command);
                if (result == 0)
				{
                    /* If the previous command succeeds, stop execution */
                    break;
                }
                prev_result = result;
            }
        }
		else
		{
            /* Execute the command */
            int result = get_args(token);
            prev_result = result;
        }

        token = strtok(NULL, " ");
    }

    return 0;
}

