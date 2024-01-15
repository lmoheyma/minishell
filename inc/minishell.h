/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:38:02 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/15 20:11:32 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define PATH_MAX 4096

typedef struct s_env
{
    char            *content;
    struct s_env    *next;
}    t_env;

typedef struct s_args
{
    char            **cmd;
    struct s_args    *next;
}    t_args;

typedef struct s_minishell
{
    t_env    *envs;
	//char	**envs;
    int        fd_in;
    int        fd_out;
    int        is_pipe;
    t_args    *args;
    int       nb_cmd;
    int       *pid;
}    t_minishell;


// Env
t_env	*dup_env(char **envp);
char	**env_tab(t_env *env);
t_env	*new_env_node(void *content);
void	add_back_node_env(t_env **lst, t_env *new);
int	is_env_var_set(t_env *env, char *str);

// CD
int ft_cd(t_minishell *cmd);
char	*get_home(t_env *env);

// Builtin
int is_builtin(t_minishell *cmd);
void exec_builtin(t_minishell *cmd);

int ft_env(t_minishell *cmd);
void ft_echo(t_minishell *cmd);
void ft_export(t_minishell *cmd);
void ft_pwd(void);
void ft_unset(t_minishell *cmd);
int ft_exit(t_minishell *cmd);

// Pipe
void    exec_pipe_command(t_minishell *cmd);
void	add_pipe(t_minishell *cmd, t_args *arg);

// Execute command
void command_execute(t_minishell *cmd);
void fork_process(t_minishell *cmd);
void	exec_simple_command(t_minishell *cmd, t_args *arg);
void	exec_last_command(t_minishell *cmd);

// Utils
char	*get_path(t_env *env);
void	free_str(char **str);
char	**ft_last_cmd(t_minishell *minishell);

// Here-doc
int	add_line_to_fd(char **argv, int fd[2]);


#endif