/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:38:02 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/02/01 12:21:29 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <wait.h>

# define TRUE 1
# define FALSE 0
# define PATH_MAX 4096

extern int			g_exit_code;

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}					t_env;

typedef struct s_tokens
{
	char			*content;
	char			*type;
	struct s_tokens	*next;
}					t_tokens;

typedef struct s_args
{
	char			**cmd;
	struct s_args	*next;
}					t_args;

typedef struct s_write_params
{
	int				i;
	int				j;
	int				k;
	char			trigger;
}					t_write_params;

typedef struct s_minishell
{
	t_env			*envs;
	int				fd_in;
	int				fd_out;
	int				is_pipe;
	int				nb_cmd;
	t_args			*args;
	t_args			*args_start;
	t_tokens		*tokens;
	t_tokens		*tokens_start;
	t_write_params	*write_params;
}					t_minishell;

// Env
t_env				*dup_env(char **envp);
char				**env_tab(t_env *env);
t_env				*new_env_node(void *content);
void				add_back_node_env(t_env **lst, t_env *new);
int					is_env_var_set(t_env *env, char *str);
void				add_to_env(t_env *env, char *str);
t_env				*empty_start_env(t_env *env);

// Free
void				free_env(t_env *env);
void				free_2d_array(char **str);
void				free_all(t_minishell *cmd);
void				free_fd_arg_token(t_minishell *cmd);

// Pwd
void				add_pwd_to_env(t_env *env, char *str);
void				add_oldpwd_to_env(t_env *env, char *str);
char				*get_pwd(t_env *env, char *str);
void				change_var(t_env *env, char *str, char **str_split);
void				change_pwd_var(t_env *env, char *pwd, int path_len,
						char *str);

// CD
int					ft_cd(t_minishell *cmd);
char				*get_home(t_env *env);
char				*check_pwd(void);

// Export
int					ft_strlcpy2(char *dest, const char *src, size_t size);
void				export_error(char *str);
void				change_var2(t_env *env, char **str_split,
						char *str_w_equals, char *str_big);
int					check_valid_identifer(char **str_split);

// Builtin
int					is_builtin(t_minishell *cmd);
int					exec_builtin(t_minishell *cmd);
t_args				*ft_last(t_args *lst);
int					last_arg_is_builtin(t_minishell *cmd);
void				fork_builtin(t_minishell *cmd);
int					is_env_buitin(t_minishell *cmd);
int					is_builtin_arg(t_args *arg);

int					ft_env(t_minishell *cmd);
int					ft_echo(t_minishell *cmd);
int					ft_export(t_minishell *cmd);
int					ft_pwd(t_minishell *cmd);
int					ft_unset(t_minishell *cmd);
int					ft_exit(t_minishell *cmd);

// Pipe
void				exec_pipe_command(t_minishell *cmd);
void				add_pipe(t_minishell *cmd, t_args *arg);

// Signals
void				signals_manager(int signal);
void				signals_manager_child(int signal);

// Execute command
void				command_execute(t_minishell *cmd);
void				fork_process(t_minishell *cmd);
void				exec_simple_command(t_minishell *cmd, t_args *arg);
void				exec_absolute_path(t_minishell *cmd, t_args *arg);
void				exit_code_and_exit(t_minishell *cmd, t_args *arg,
						char **path_split);

// Path
int					get_path1(t_minishell *cmd, t_args *arg);
int					check_all_arg(t_minishell *cmd);

// Utils
char				*get_path(t_env *env);
void				print_error(t_minishell *cmd, int flag);
void				free_str(char **str);
char				**ft_last_cmd(t_minishell *minishell);
int					ft_strcmp(const char *str, const char *str2);
void				print_error_str(char *str);
int					ft_atol(char *str, long long *res);

// Here-doc
void				ft_here_doc(t_minishell *minishell, char *argv);
int					add_line_to_fd(char *argv, int fd[2],
						t_minishell *minishell);
char				*ft_strcat(char *dest, char *src);
void				write_heredoc_eof(int fd);
void				ft_heredoc2(char *line, char *lim, char *buffer,
						int *running);

// Exit
int					ft_exit_code(t_args *arg);

// Args

t_args				*create_arg(t_minishell *minishell);
int					setup_args(t_minishell *minishell);

// Error

void				ft_err(t_minishell *minishell, char *err, int code);
void				free_tokens(t_tokens **tokens);
void				free_args(t_args **args);
int					check_only_null_env_var(char *cmd, int *j,
						t_minishell *minishell);

// Files

int					setup_files(t_minishell *minishell);
int					replace_infile(t_minishell *minishell, char *path);
int					replace_outfile(t_minishell *minishell, char *path);
int					replace_append_outfile(t_minishell *minishell, char *path);

// Global Parse

int					get_elem(char *cmd);
int					check_chev(char *cmd);
int					check_pipe(char *cmd);
int					check_empty(char *cmd);
int					check_ng(char *cmd);
int					all_char(char *cmd, char c);
void				init_vars(t_minishell *minishell);
int					parse_all_minishell(t_minishell *minishell, char *cmd);

// Tokens

int					set_token_type(t_tokens *token, char *str, int *i);
int					write_loop(t_minishell *minishell, t_tokens *token,
						char *cmd, t_write_params *params);
void				write_word(t_minishell *minishell, t_tokens *token,
						char *cmd);
t_tokens			*create_token(char *cmd, int *i, t_minishell *minishell);
int					setup_tokens(t_minishell *minishell, char *cmd);

// Utils

int					is_spaces(char c);
int					is_special_char(char c);
void				skip_spaces(char *str, int *i);
int					is_cmd(char *type);
void				skip_special_char(char *str, int *i);

// Utils2

int					nb_special_char(t_minishell *minishell, t_tokens *token,
						char *cmd, int *i);
int					ft_cmdsize(t_args *args);
t_write_params		*init_write_params(t_minishell *minishell);
int					int_len(int nb);

// Vars

int					get_len(char *str);
int					get_env_var_size_loop(t_env *env, char *str, int *i);
int					get_env_var_size(t_env *env, char *str, int *i,
						int trigger);
char				**get_env_var_content_loop(t_env *env, char *str);
char				**get_env_var_content(t_env *env, char *str);

// Vars2

int					check_env_start(char c);
int					write_env_var(t_minishell *minishell, char *content,
						char *cmd);
char				**set_exit_code(char **j);
void				ft_free_tab_s(char **s);
int					get_len_for_env(char *str, char *sub_path);

// Split args

int					count_str(char const *s);
char				**ft_split_args(char *s);

#endif
