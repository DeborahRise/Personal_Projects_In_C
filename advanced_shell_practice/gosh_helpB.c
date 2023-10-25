#include "gosh.h"

/**
 * gaux_help - Help info.
 * Return: no return
 */
void gaux_help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, s_len(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, s_len(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, s_len(help));
}
/**
 * gaux_help_alias - alias Help information.
 * Return: no return
 */
void gaux_help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, s_len(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, s_len(help));
}
/**
 * gaux_help_cd - cd Help information .
 * Return: no return
 */
void gaux_help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, s_len(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, s_len(help));
}
