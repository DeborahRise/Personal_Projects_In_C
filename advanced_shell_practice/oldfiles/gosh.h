#ifndef _GOSH_H
#define _GOSH_H

/*Libraries */
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdarg.h>

#define MAX_A_VAR_SIZE 50
#define MAX_A_NAME 50
#define MAX_A_VALUE 100

/**
 * struct format - struct for printf specifiers
 * @id: type char pointer of the specifier
 * @f: type pointer to function for the conversion specifier
 */

typedef struct format
{
	char *id;
	int (*f)();
} gosh_struct;


/**
 * struct alias - struct for printf specifiers
 * @a_name: the alias name
 * @a_value: the alias value
 */

struct alias
{
	char a_name[MAX_A_NAME];
	char a_value[MAX_A_VALUE];
};

/* External Variables */
extern int errno;
extern char **environ;
int gosh_atoi(char *s);
int s_ncmp(char *s1, char *s2, size_t n);
int gosh_print_dec_number(va_list djlist2);
char *s_ncpy(char *dest, char *src, int n);
char *s_ncat(char *dest, char *src, int n);
int gosh_printf(const char *format, ...);
int gosh_print_int_number(va_list djlist2);
int gosh_print_string(va_list djlist2);
int gosh_print_char(va_list djlist2);
int gosh_print_unint_number(va_list djlist2);
char *s_chr(char *str, char c);
ssize_t get_line(char **line, size_t *sz, FILE *stream);
int handle_err(char *msg, int val);
int gcmd_exec(char **agv, int *func_ret);
char *s_tok(char *str, char *delim);
size_t s_len(const char *str);
int s_put(char *s);
char *s_cat(char *dest, char *src);
int s_cmp(char *s1, char *s2);
char *s_copy(char *dest, char *src);
int s_write(char c);
void _exit_exec(char **agv);
char *_get_env(char *envar);
int _env_exec(char **agv);
int _setenv_exec(char **agv);
int _unsetenv_exec(char **agv);
char **get_args(char *gcmdln);
char  *get_gcmdpath(char **agv);
char *_gcmdpath_expandr(char *rel_path);
char *_getfull_path(char *rel_path, char *cwd, int slashed);
char *_getparent_path(char *cwd);
int gcmd_fork(char *full_path, char **agv);
int _chdir_helper(char *full_path, char *cwd);
int ch_dir(char *dest);
int logical_exec(char *comd, int *func_ret);
int islogical_checkr(char **cmdline);
int _slops_comp(char *s_lops, char a, char b);
int _syntax_checkr(char **cmdstr, char *gcmdln);
int _logical_ops(char *comd, char **currcmd, int *func_ret);
int throw_syntax_err(int num, ...);
int _cpyto_cmdstr(char *token, char **cmdstr);
char *comment_handler(char *gcmd);
int echo_echo(char **agv, int *func_ret);
int cat_cat(char **agv);
int touch_touch(char **agv);
char *s_dup(char *str);
char **make_vectr(char *str, char *delim);
int alias_handler(char **agv);
struct alias *gosh_find_alias(char *name);
int gosh_define_alias(char *name, char *value);
int gosh_print_aliases(void);
char *_dequoter(char *strval);
#endif
