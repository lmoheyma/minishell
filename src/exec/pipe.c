/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:58:27 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/23 23:35:43 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	child_pipe(t_minishell *cmd, t_args *arg)
{
	int	i;

	i = -1;
	signal(SIGQUIT, signals_manager_child);
	while (++i < cmd->nb_cmd - 1)
	{
		add_pipe(cmd, arg);
		arg = arg->next;
	}
	dup2(cmd->fd_out, STDOUT_FILENO);
	dup2(cmd->fd_in, STDIN_FILENO);
	if ((access(arg->cmd[0], F_OK | X_OK) == 0))
		exec_absolute_path(cmd, arg);
	else
		exec_simple_command(cmd, arg);
}

void	exec_pipe_command(t_minishell *cmd)
{
	t_args	*arg;
	int		pid;

	arg = cmd->args;
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		child_pipe(cmd, arg);
	}
	else
	{
		signal(SIGQUIT, signals_manager_child);
		signal(SIGINT, signals_manager_child);
		waitpid(pid, NULL, 0);
		kill(pid, SIGTERM);
		signal(SIGINT, signals_manager);
		signal(SIGQUIT, SIG_IGN);
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
		if ((access(arg->cmd[0], F_OK | X_OK) == 0))
			exec_absolute_path(cmd, cmd->args);
		else
			exec_simple_command(cmd, arg);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}
