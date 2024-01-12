/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:38:02 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/12 13:30:49 by lmoheyma         ###   ########.fr       */
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

#define TRUE 1
#define FALSE 0

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
    //t_env    *envs;
	char	**envs;
    int        fd_in;
    int        fd_out;
    int        is_pipe;
    t_args    *args;
    int       nb_cmd;
    int       *pid;
}    t_minishell;

// Builtin
int is_builtin(t_minishell *cmd);
int exec_builtin(t_minishell *cmd);

// Pipe
void exec_pipe_command(t_minishell *cmd);
void	add_pipe(t_minishell *cmd, t_args *arg);

// Execute command
void command_execute(t_minishell *cmd);
void fork_process(t_minishell *cmd);
void	exec_simple_command(t_minishell *cmd, t_args *arg);
void	exec_last_command(t_minishell *cmd);

// Utils
char	*get_path(char **envp);
void	free_str(char **str);
char	**ft_last_cmd(t_minishell *minishell);

// Here-doc
int	add_line_to_fd(char **argv, int fd[2]);


#endif