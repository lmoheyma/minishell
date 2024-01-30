/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:58:27 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/30 01:14:09 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	child_pipe(t_minishell *cmd, t_args *arg)
{
	int	i;
	int pid[cmd->nb_cmd - 1];

	i = -1;
	signal(SIGQUIT, signals_manager_child);
	while (++i < cmd->nb_cmd - 1)
	{
		add_pipe(cmd, arg, &pid[i]);
		arg = arg->next;
	}
	dup2(cmd->fd_out, STDOUT_FILENO);
	dup2(cmd->fd_in, STDIN_FILENO);
	i = -1;
	if ((access(arg->cmd[0], F_OK | X_OK) == 0))
		exec_absolute_path(cmd, arg);
	else
		exec_simple_command(cmd, arg);
	while (++i < cmd->nb_cmd - 1)
		waitpid(pid[i], NULL, 0);
}

void	parent_pipe(int pid)
{
	signal(SIGQUIT, signals_manager_child);
	signal(SIGINT, signals_manager_child);
	waitpid(pid, &g_exit_code, 0);
	if (WIFEXITED(g_exit_code) == TRUE)
		g_exit_code = WEXITSTATUS(g_exit_code);
	else if (WIFSIGNALED(g_exit_code) == TRUE)
	{
		if (WTERMSIG(g_exit_code) == SIGINT
			|| WTERMSIG(g_exit_code) == SIGQUIT)
			g_exit_code += 128;
	}
	kill(pid, SIGTERM);
	signal(SIGINT, signals_manager);
	signal(SIGQUIT, SIG_IGN);
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
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
	}
	else
	{
		parent_pipe(pid);
	}
}

void	add_pipe(t_minishell *cmd, t_args *arg, int *pid_tab)
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
		*pid_tab = pid;
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
