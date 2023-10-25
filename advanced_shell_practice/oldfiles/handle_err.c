#include "gosh.h"

/**
 * handle_err - Handles errors with pointers
 * @msg: the error prefix to print. A null terminated string
 * @val: the errno number, or value representing the error gotten
 * Return: Always NULL
 */

int handle_err(char *msg, int val)
{
	perror(msg);
	return (val);
}
