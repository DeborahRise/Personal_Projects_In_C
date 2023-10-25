#ifndef _GOSH_H
#define _GOSH_H

#include <sys/types.h>
#include <signal.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

#define TOK_DELIMETER " \n\a\t\r"
#define TOK_BUFF_SIZE 128
#define BUFF_SIZE 1024

/* An "environment" strings struct pointer */
extern char **environ;


/**
 * struct gosh - everything we need
 * @agv: argv vectors
 * @g_input: user input
 * @g_args: command line vectors
 * @g_status: shell status
 * @g_counter: number of lines
 * @g_environ: environment variable
 * @gpid: shell process ID
 */
typedef struct gosh
{
	char **agv;
	char *g_input;
	char **g_args;
	int g_status;
	int g_counter;
	char **g_environ;
	char *gpid;
} go_shell;

/**
 * struct gosh_separator - single linked list
 * @g_separator:  & ; |
 * @g_next: next node
 * Description: separators list
 */
typedef struct gosh_separator
{
	char g_separator;
	struct gosh_separator *g_next;
} gosh_sep_list;

/**
 * struct gosh_cmd_line - single linked list
 * @gcmd_line: command line
 * @g_next: next node
 * Description: command lines list
 */
typedef struct gosh_cmd_line
{
	char *gcmd_line;
	struct gosh_cmd_line *g_next;
} gosh_cmd_line;

/**
 * struct gosh_variables - single linked list
 * @g_len_var: length of the variable
 * @g_val: value of the variable
 * @g_len_val: length of the value
 * @g_next: next node
 * Description: variable list
 */
typedef struct gosh_variables
{
	int g_len_var;
	char *g_val;
	int g_len_val;
	struct gosh_variables *g_next;
} gosh_variables;

/**
 * struct gosh_builtin - Builtin commands struct.
 * @g_builtin_name:  builtin, e.g alias, cd, exit, env etc
 * @g_function: a pointer function.
 */
typedef struct gosh_builtin
{
	char *g_builtin_name;
	int (*g_function)(go_shell *gosh_gosh);
} gosh_builtin;

/* gaux_listsI.c */
gosh_sep_list *add_gosh_sep_node_end(gosh_sep_list **head, char separator);
void free_gosh_sep_list(gosh_sep_list **head);
gosh_cmd_line *add_gosh_line_node_end(gosh_cmd_line **head, char *gcmd_line);
void free_gosh_cmd_line(gosh_cmd_line **head);

/* gaux_listsII.c */
gosh_variables *add_gosh_variables_node(gosh_variables **head,
		int lvar, char *val, int lval);
void free_gosh_variables_list(gosh_variables **head);

/* gaux_strI funcs */
char *s_cat(char *dest, char *src);
char *s_copy(char *dest, char *src);
int s_cmp(char *s1, char *s2);
char *s_chr(char *str, char c);
int s_spn(char *s, char *accept);

/* gaux_strII.c */
char *s_dup(char *str);
int s_len(const char *s);
int comp_chars(char str[], const char *delim);
char *s_tok(char *str, char *delim);
int g_isdigit(const char *s);

/* aux_strIII.c */
void g_rev_string(char *s);

/* gaux_mem_mem.c */
void g_memcpy(void *newptr, const void *ptr, unsigned int size);
void *g_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **g_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* gosh_check_syntax_error.c */
int g_rpt_char(char *input, int i);
int g_error_sep_ops(char *input, int i, char last);
int g_1st_char(char *input, int *i);
void g_print_syntax_error(go_shell *gosh_gosh,
		char *input, int i, int boolean);
int g_check_syntax_error(go_shell *gosh_gosh, char *input);

/* gosh_shell_loop.c */
char *gosh_without_comment(char *input);
void gosh_shell_loop(go_shell *gosh_gosh);

/* gosh_read_line.c */
char *gosh_read_line(int *i_eof);

/* gosh_split.c */
char *gosh_swap_char(char *input, int boolean);
void gosh_add_nodes(gosh_sep_list **head_s,
		gosh_cmd_line **head_l, char *g_input);
void gosh_go_next(gosh_sep_list **list_s,
		gosh_cmd_line **list_l, go_shell *gosh_gosh);
int gosh_split_commands(go_shell *gosh_gosh, char *g_input);
char **gosh_split_line(char *g_input);

/* gosh_rep_var.c */
void check_env(gosh_variables **h, char *in, go_shell *data);
int check_vars(gosh_variables **h, char *in, char *st, go_shell *data);
char *replaced_input(gosh_variables **head,
		char *input, char *new_input, int nlen);
char *rep_var(char *input, go_shell *gosh_gosh);

/* gosh_get_line.c */
void gosh_bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t gosh_get_line(char **lineptr, size_t *n, FILE *stream);

/* gosh_exec_line */
int exec_line(go_shell *gosh_gosh);

/* gosh_cmd_exec.c */
int gosh_c_dir(char *path, int *i);
char *gosh_which(char *cmd, char **g_environ);
int gosh_is_executable(go_shell *gosh_gosh);
int gosh_check_error_cmd(char *dir, go_shell *gosh_gosh);
int gosh_cmd_exec(go_shell *gosh_gosh);

/* gosh_envI.c */
int cmp_env_name(const char *nenv, const char *name);
char *_get_env(const char *name, char **g_environ);
int gosh_env(go_shell *gosh_gosh);

/* gosh_envII.c */
char *gosh_copy_info(char *name, char *value);
void gosh_set_env(char *name, char *value, go_shell *gosh_gosh);
int gosh_setenv(go_shell *gosh_gosh);
int gosh_unsetenv(go_shell *gosh_gosh);

/* gosh_cd.c */
void cd_dot(go_shell *gosh_gosh);
void cd_to(go_shell *gosh_gosh);
void cd_previous(go_shell *gosh_gosh);
void cd_to_home(go_shell *gosh_gosh);

/* gosh_cd_shell.c */
int gosh_cd_shell(go_shell *gosh_gosh);

/* get_builtin */
int (*gosh_get_builtin(char *cmd))(go_shell *gosh_gosh);

/* gosh_exit.c */
int gosh_exit_shell(go_shell *gosh_gosh);

/* gaux_stdlib.c */
int gosh_get_len(int n);
char *gosh_itoa(int n);
int gosh_atoi(char *s);

/* gaux_errorI.c */
char *s_cat_cd(go_shell *, char *, char *, char *);
char *gosh_error_get_cd(go_shell *gosh_gosh);
char *error_not_found(go_shell *gosh_gosh);
char *gosh_error_exit_shell(go_shell *gosh_gosh);

/* aux_error2.c */
char *error_get_alias(char **args);
char *gosh_error_env(go_shell *gosh_gosh);
char *error_syntax(char **args);
char *error_permission(char **args);
char *g_error_path_126(go_shell *gosh_gosh);


/* get_error.c */
int get_error(go_shell *gosh_gosh, int eval);

/* get_sigint.c */
void gosh_get_sigint(int sig);

/* gaux_help.c */
void gaux_help_env(void);
void gaux_help_setenv(void);
void gaux_help_unsetenv(void);
void gaux_help_general(void);
void gaux_help_exit(void);

/* gaux_helpII.c */
void gaux_help(void);
void gaux_help_alias(void);
void gaux_help_cd(void);

/* get_help.c */
int gosh_get_help(go_shell *gosh_gosh);

#endif
