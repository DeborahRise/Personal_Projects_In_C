#include "gosh.h"

/**
 * gaux_help_env - builtin env Help info
 * Return: no return
 */
void gaux_help_env(void)
{
	char *help = "env: env [option] [name=value] [command [g_args]]\n\t";

	write(STDOUT_FILENO, help, s_len(help));
	help = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, help, s_len(help));

}
/**
 * gaux_help_setenv - setenv Help info
 * Return: no return
 */
void gaux_help_setenv(void)
{

	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, s_len(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, s_len(help));
	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, s_len(help));
}
/**
 * gaux_help_unsetenv - unsetenv Help info
 * Return: no return
 */
void gaux_help_unsetenv(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, s_len(help));
	help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help, s_len(help));
}


/**
 * gaux_help_general - builtin help Entry point for help info
 * Return: no return
 */
void gaux_help_general(void)
{
	char *help = "($) bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, s_len(help));
	help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, help, s_len(help));
	help = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, help, s_len(help));
	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, s_len(help));
	help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, s_len(help));
	help = "[g_args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help, s_len(help));
	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, s_len(help));
}
/**
 * gaux_help_exit - exit builint Help information
 * Return: no return
 */
void gaux_help_exit(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, s_len(help));
	help = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, help, s_len(help));
	help = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, help, s_len(help));
}
