/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:38:02 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/21 16:39:35 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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

extern int			g_pid;

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
}					t_write_params;

typedef struct s_minishell
{
	t_env			*envs;
	int				fd_in;
	int				fd_out;
	int				is_pipe;
	int				nb_cmd;
	int				exit_code;
	t_args			*args;
	t_tokens		*tokens;
	t_write_params	*write_params;
}					t_minishell;

// EXECUTION
// Env
t_env				*dup_env(char **envp);
char				**env_tab(t_env *env);
t_env				*new_env_node(void *content);
void				add_back_node_env(t_env **lst, t_env *new);
int					is_env_var_set(t_env *env, char *str);
void				add_to_env(t_env *env, char *str);

// Pwd
void				add_pwd_to_env(t_env *env, char *str);
void				add_oldpwd_to_env(t_env *env, char *str);
char				*get_pwd(t_env *env, char *str);
void 				change_var(t_env *env, char *str, char **str_split);
void				change_pwd_var(t_env *env, char *pwd, int path_len, char *str);

// CD
int					ft_cd(t_minishell *cmd);
char				*get_home(t_env *env);

// Export
int					ft_strlcpy2(char *dest, const char *src, size_t size);

// Builtin
int					is_builtin(t_minishell *cmd);
void				exec_builtin(t_minishell *cmd);
t_args				*ft_last(t_args *lst);
int					last_arg_is_builtin(t_minishell *cmd);
void 				fork_builtin(t_minishell *cmd);
int					is_env_buitin(t_minishell *cmd);

int					ft_env(t_minishell *cmd);
void				ft_echo(t_minishell *cmd);
void				ft_export(t_minishell *cmd);
void				ft_pwd(void);
void				ft_unset(t_minishell *cmd);
int					ft_exit(t_minishell *cmd);

// Pipe
void				exec_pipe_command(t_minishell *cmd);
void				add_pipe(t_minishell *cmd, t_args *arg);

// Execute command
void				command_execute(t_minishell *cmd);
void				fork_process(t_minishell *cmd);
void				exec_simple_command(t_minishell *cmd, t_args *arg);
void				exec_absolute_path(t_minishell *cmd, t_args *arg);

// Utils
char				*get_path(t_env *env);
void				print_error(t_minishell *cmd, int flag);
void				free_str(char **str);
char				**ft_last_cmd(t_minishell *minishell);
int					ft_strcmp(const char *str, const char *str2);
void 				print_error_str(char *str);

// Here-doc
int					add_line_to_fd(char **argv, int fd[2]);

// PARSING

void				parse_all_minishell(t_minishell *minishell, char *cmd);
void				setup_files(t_minishell *minishell);
void				replace_infile(t_minishell *minishell, char *path);
void				replace_outfile(t_minishell *minishell, char *path);
void				replace_append_outfile(t_minishell *minishell, char *path);

int					get_elem(char *cmd);
void				parse_all_minishell(t_minishell *minishell, char *cmd);

void				set_token_type(t_tokens *token, char *str, int *i);
void				write_word(t_minishell *minishell, t_tokens *token,
						char *cmd);
t_tokens			*create_token(char *cmd, int *i, t_minishell *minishell);
void				setup_tokens(t_minishell *minishell, char *cmd);

int					is_spaces(char c);
int					is_special_char(char c);
void				skip_spaces(char *str, int *i);
int					is_cmd(char *type);
void				skip_special_char(char *str, int *i);
int					nb_special_char(t_minishell *minishell, t_tokens *token,
						char *cmd, int *i);
int					ft_cmdsize(t_args *args);

void				create_args(t_minishell *minishell);

void				ft_err(t_minishell *minishell, char *err, int code);
void				free_tokens(t_tokens **tokens);
void				free_args(t_args **args);

int					get_env_var_size(t_env *env, char *str, int *i);
char				**get_env_var_content(t_env *env, char *str);
int					write_env_var(t_minishell *minishell, char *content,
						char *cmd);
t_write_params		*init_write_params(t_minishell *minishell);

#endif