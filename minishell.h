#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define RESET "\033[0m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"

/******************************************************************************/
/*                                 MACROS                                     */
/******************************************************************************/

# define PASS 0
# define FAIL 1

extern int	g_signal_code;

/******************************************************************************/
/*                                  STRUCTS                                   */
/******************************************************************************/

typedef struct s_token
{
	char				*string;
	char				*store_string;
	int					type;
	int					status;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

typedef struct s_fds_io
{
	char				*filein;
	char				*fileout;
	char				*heredoc_del;
	bool				heredoc_quotes;
	bool				heredoc_input;
	bool				flag;
	int					fd_in;
	int					fd_out;
	int					store_stdin;
	int					store_stdout;
}						t_fds_io;

typedef struct s_envar
{
	char				*key;
	char				*value;
	char				*original;
	struct s_envar		*prev;
	struct s_envar		*next;
}						t_env;

typedef struct s_command
{
	char				*command;
	char				*path;
	char				**args;
	bool				pipe_output;
	int					*pipe_fd;
	pid_t				pid;
	t_fds_io			*file;
	struct s_command	*prev;
	struct s_command	*next;
}						t_command;

typedef struct s_data
{
	t_token				*token;
	int					exit_status;
	char				*user_input;
	char				**env_cpy;
	int					error_code;
	bool				empty_env;
	t_env				*env;
	t_command			*cmd;
}						t_data;

/******************************************************************************/
/*                                  ENUMS                                     */
/******************************************************************************/

enum					e_token_types
{
	TOKEN_SPACES = 1,
	TOKEN_WORD = 2,
	TOKEN_VAR = 3,
	TOKEN_PIPE = 4,
	TOKEN_INPUT = 5,
	TOKEN_TRUNC = 6,
	TOKEN_HEREDOC = 7,
	TOKEN_APPEND = 8,
	TOKEN_END
};

enum					e_token_status
{
	DEFAULT = 1,
	SINGLEQUOTE = 2,
	DBLQUOTE
};

enum					e_builtin_cmd
{
	bi_CD = 1,
	bi_ECHO,
	bi_ENV,
	bi_EXIT,
	bi_EXPORT,
	bi_PWD,
	bi_UNSET
};

enum					e_ctrl_lst
{
	TOK = 1,
	CMD,
	ENV,
	ALL
};

/******************************************************************************/
/*                                  MAIN                                      */
/******************************************************************************/

int						ft_start_minishell(t_data *data);
int						ft_data_sig_start(t_data *data, char **env);

/******************************************************************************/
/*                                 SIGNALS                                    */
/******************************************************************************/

void					ft_new_line(int sig);
void					ft_reset_line(int sig);
void					ft_handle_sigquit(void);
void					ft_init_signals(void);
void					ft_disable_signals(void);

/******************************************************************************/
/*                               DATA INIT                                    */
/******************************************************************************/

void					ft_init_file(t_fds_io *file);
t_fds_io				*ft_create_new_file(void);

void					ft_init_token(t_token *token);
t_token					*ft_tok_lstnew(char *str, int tok_type);
void					ft_tok_add_node(t_token **head, char *str, int type);

void					ft_init_env(t_env *env);
int						ft_strfind(char *str, char c);
t_env					*ft_env_lstnew(char *str);
void					ft_env_add_node(t_env **head, char *str);

void					ft_init_command(t_command *cmd);
t_command				*ft_cmd_lstnew(void);
void					ft_cmd_add_node(t_command **head);

void					ft_print_welcome(void);
void					ft_print_exit(void);

int						ft_init_data(t_data *data, char **envar);
int						ft_init_check(t_data *data);
char					**ft_copy_env(char **envar);
void					ft_env_lst_create(t_data *data, char **envar);

/******************************************************************************/
/*                               BUILT_INS                                    */
/******************************************************************************/

int						ft_cd(t_data *data, char **args);
char					*ft_cd_pathfinder(t_data *data, int ctrl);
int						ft_valid_arguments(char **array);
int						ft_execute_cd(t_data *data, char *path);

void					ft_refresh_directory(t_data *data, char *new_wd);

int						ft_unset(t_data *data, char **args);

int						ft_pwd(t_data *data, char **args);

int						ft_export(t_data *data, char **args);
int						ft_edit_or_add(t_data *data, char *args);
int						ft_format_check(char *args);
int						ft_empty_export(t_data *data);

void					ft_swap(char **a, char **b);
int						ft_partition(char **lst, int low, int high);
void					ft_quicksort(char **order, int low, int high);
void					ft_quicksort_prep(t_data *data, char **order,
							int count);

int						ft_env(t_data *data, char **args);

int						ft_echo(t_data *data, char **args, bool flag);
void					ft_print_args(char **args, int start);
int						ft_flag_check(char *str);

int						ft_exit(t_data *data, char **args);
int						ft_skip(char *num_str, int *a);
int						ft_extract_num(t_data *data, char *num_str, int *ctrl,
							int a);
long					ft_atol(const char *str);

/******************************************************************************/
/*                                 LEXER                                      */
/******************************************************************************/

int						ft_quote_syntax_check(t_data *data, char *input,
							int len, int a);
int						ft_empty_inputs(char *usr_i);
int						ft_id_tok_type(char *usr_i, int a);

char					*ft_fill_token(char *src, int pos, int len);
int						ft_generate_token(t_data *d, int pos, int start,
							int tok);
int						ft_token_creation(t_data *data, char *usr_in, int curr,
							int *a);
int						ft_fetch_current_flag(int flag, char *usr_in, int a);
int						ft_token_start(t_data *data, char *user_input, int len);

int						ft_tok_syntax(t_token *t);
void					ft_special_message(t_token *t);
int						ft_grammar_check(t_data *data);

int						ft_isspace(char c);
void					ft_find_variables(t_data *data);
int						ft_expand_syntax(char *s, int pos);

int						ft_special(char c);
char					*ft_special_expand(t_data *data, char c);
char					*ft_og_var_value(t_data *data, t_token *tok, int a);
int						ft_varlen(char *var);
void					ft_replace_null_var(t_token *t, char *var, int a);

void					ft_strcpy_remote(char *str1, char *str2, int *a);
char					*ft_new_expanded(char *str, char *exp_var, int len,
							int a);
void					ft_replace_exp_var(t_token *t, char *str, char *var,
							int a);
void					ft_expand_token(t_data *data, t_token *token, int a);
void					ft_expand_checker(t_data *data, t_token *t);

void					ft_handle_quotes(t_token *tok, int len, int a, int b);
char					ft_quote_char(int flag);
int						ft_quotelen(char *str, int a, int len);
int						ft_find_quotes(char *str);

void					ft_expand_var_quote(t_data *data);
int						ft_lex_user_input(t_data *data);
int						ft_process_user_input(t_data *data);
int						ft_start(t_data *data);

/******************************************************************************/
/*                                 PARSER                                     */
/******************************************************************************/

int						ft_division_check(char *str);
char					**ft_increase_size(t_command *curr, size_t old_size);
void					ft_fill_single_command(t_command *cmd, const char *arg,
							int count);
void					ft_fill_multi_command(t_command *cmd, const char *arg);
void					ft_handle_var_word(t_data *data, t_token **tok);

void					ft_parse_input(t_token *t, t_fds_io *f);
void					ft_parse_append(t_token *t, t_fds_io *f);
void					ft_parse_trunc(t_token *t, t_fds_io *f);
void					ft_handle_redirect(t_data *data, t_token **token);

bool					ft_if_quoted(char *str);
void					ft_parse_heredoc(t_token **token, t_command *cmd);
void					ft_heredoc_input(t_command *cmd, t_data *data);
char					*ft_expand_heredoc(char *line, t_data *data);
void					ft_readline_heredoc(int write_fd, t_fds_io *io,
							t_data *data);
int						ft_line_handle(t_fds_io *io, char **line, t_data *data);

void					ft_handle_pipe(t_data *data, t_token **token);
void					ft_parse_tokens(t_data *data);

/******************************************************************************/
/*                              ENVIRONMENT                                   */
/******************************************************************************/

t_env					*ft_env_find_node(t_data *data, char *search);
int						ft_env_new_node(t_data *data, char *content);
int						ft_env_edit_node(t_data *data, char *trgt,
							char *content);
int						ft_env_remove_node(t_data *data, char *trgt);
int						ft_env_insert_node(t_data *data, t_env *new);

void					ft_update_last_cmd(t_data *data);
int						ft_update_shlvl(t_data *data);
char					**ft_force_create_env(void);
int						ft_check_newenv(char **env);

int						ft_reset_env(t_data *data);
char					**ft_recreate_env(t_env *og_env);
int						ft_env_append_create(t_data *data, char *key,
							char *args);
int						ft_update_oldpwd(t_data *data);

/******************************************************************************/
/*                                EXECUTION                                   */
/******************************************************************************/

char					*ft_raw_path_extract(t_data *data);
char					**ft_final_path(char **paths);
char					**ft_env_extraction(t_data *data);
char					*ft_sys_cmd_line(char *cmd, char **exec_paths);
char					*ft_command_create(t_data *data, char *cmd);

int						ft_cmd_fds_prep(t_fds_io *f);
int						ft_std_io_backup(t_fds_io *f);
int						ft_dup2_redirect(t_fds_io *f);
int						ft_pipe_create(t_data *data);

int						ft_builtin_exec(t_data *data, t_command *cmd);
int						ft_identify_builtin(char *cmd);
int						ft_builtin_trigger(t_data *data, t_command *cmd,
							int cmd_id);

int						ft_cmd_exec_prep(t_data *data, t_command *cmd,
							t_fds_io *file);
int						ft_system_exec(t_data *data, t_command *cmd);
char					*ft_local_command(char *cmd);
int						ft_cmd_dir_check(char *cmd);
int						ft_cmd_dir_find(char *cmd);

int						ft_execution_trigger(t_data *data);
int						ft_exec_init_check(t_data *data);
int						ft_child_process(t_data *data);
int						ft_parent_process(t_data *data);
int						ft_command_execute(t_data *data, t_command *cmd);

/******************************************************************************/
/*                              EXIT & ERROR                                  */
/******************************************************************************/

void					ft_safe_str(void *str);
void					ft_safe_array(void ***array);
void					ft_full_exit(t_data *d, int error_code);
void					ft_free_data_struct(t_data *d);
void					ft_reset_stdin_stdout(t_fds_io *fds);
void					ft_lstclear_ctrl(t_data *data, int ctrl);

void					ft_command_close_fd(t_command *cmd);
void					ft_child_close_pipe(t_data *d, t_command *c);
void					ft_parent_close_pipe(t_data *d);

char					*ft_dup_or_join(char *s1, char *s2);
char					*ft_check_quotes(char *final, char *cmd, char *dtl);
int						ft_error_message(char *cmd, char *dtl, char *msg,
							int err_code);
void					ft_messaging(char *msg, char *dtl);
void					ft_print_error(char *message);

void					ft_tok_lstclear(t_token **lst);
void					ft_tok_delnode(t_token *node);

void					ft_cmd_lstclear(t_command **lst);
void					ft_cmd_delnode(t_command *node);

void					ft_env_lstclear(t_env **lst);
void					ft_env_delnode(t_env *node);

/******************************************************************************/
/*                                 UTILS                                      */
/******************************************************************************/

int						ft_len(char *str);
char					*ft_fetch_comp(char *prompt);
int						ft_check_home(char *cwd);
char					*ft_edit_cwd(char *prompt, int a);
char					*ft_get_prompt(bool empty_env);

t_command				*ft_last_command(t_command *cmd);
int						ft_env_lstsize(t_env *lst);
int						ft_cmd_lstsize(t_command *lst);
int						ft_tok_lstsize(t_token *lst);

int						ft_is_set(char const *s, char c);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strtrim_front(char const *s1, char const *set);
char					*ft_strtrim(char const *s1, char const *set);

// debugging

void					ft_print_data(t_data *data);
void					test_print_cmd_list(t_data *data);
void					print_token_list(t_token **tokens);

#endif