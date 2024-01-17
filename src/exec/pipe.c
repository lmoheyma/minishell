/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:58:27 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/16 20:40:40 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void exec_pipe_command(t_minishell *cmd)
{
	int	i;
	t_args *arg;
	int pid;

	i = -1;
	arg = cmd->args;
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		g_pid = pid;
		while (++i < cmd->nb_cmd - 1)
		{
			add_pipe(cmd, arg);
			arg = arg->next;
		}
		exec_simple_command(cmd, arg);
	}
	else
	{
		g_pid = pid;
		waitpid(pid, NULL, 0);
		kill(pid, SIGTERM);
	}
}

void	add_pipe(t_minishell *cmd, t_args *arg)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec_simple_command(cmd, arg);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}
