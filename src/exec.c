/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:35:31 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/12 18:19:00 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void command_execute(t_minishell *cmd)
{
	// if (is_builtin(cmd) == TRUE)
	// 	exec_builtin(cmd);
	if (cmd->is_pipe)
		exec_pipe_command(cmd);
	else if (!cmd->is_pipe)
		fork_process(cmd);
}

void fork_process(t_minishell *cmd)
{
	int pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
		exec_simple_command(cmd, cmd->args);
	else
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
}

void	exec_simple_command(t_minishell *cmd, t_args *arg)
{
	char	**path_split;
	char	*sub_path;
	char	*exe;
	int		i;

	i = -1;
	path_split = ft_split(get_path(cmd->envs), ':');
	while (path_split[++i])
	{
		sub_path = ft_strjoin(path_split[i], "/");
		exe = ft_strjoin(sub_path, arg->cmd[0]);
		free(sub_path);
		if (access(exe, F_OK | X_OK) == 0)
		{
			if (execve(exe, arg->cmd, cmd->envs) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		free(exe);
	}
	free_str(path_split);
	//return (0);
}

void	exec_last_command(t_minishell *cmd)
{
	char	**path_split;
	char	*sub_path;
	char	*exe;
	char	**last_cmd;
	int		i;

	i = -1;
	last_cmd = ft_last_cmd(cmd);
	path_split = ft_split(get_path(cmd->envs), ':');
	while (path_split[++i])
	{
		sub_path = ft_strjoin(path_split[i], "/");
		exe = ft_strjoin(sub_path, last_cmd[0]);
		free(sub_path);
		if (access(exe, F_OK | X_OK) == 0)
		{
			if (execve(exe, last_cmd, cmd->envs) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		free(exe);
	}
	free_str(path_split);
	//return (0);
}
