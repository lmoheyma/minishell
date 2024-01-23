/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:54:13 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/23 22:19:30 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin(t_minishell *cmd)
{
	if (ft_strcmp(cmd->args->cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->args->cmd[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->args->cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->args->cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->args->cmd[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->args->cmd[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd->args->cmd[0], "echo") == 0)
		return (1);
	else
		return (0);
}

int	exec_builtin(t_minishell *cmd)
{
	dup2(cmd->fd_out, STDOUT_FILENO);
	if (ft_strcmp(cmd->args->cmd[0], "cd") == 0)
		g_exit_code = ft_cd(cmd);
	else if (ft_strcmp(cmd->args->cmd[0], "pwd") == 0)
		g_exit_code = ft_pwd(cmd);
	else if (ft_strcmp(cmd->args->cmd[0], "env") == 0)
		g_exit_code = ft_env(cmd);
	else if (ft_strcmp(cmd->args->cmd[0], "export") == 0)
		g_exit_code = ft_export(cmd);
	else if (ft_strcmp(cmd->args->cmd[0], "unset") == 0)
		g_exit_code = ft_unset(cmd);
	else if (ft_strcmp(cmd->args->cmd[0], "exit") == 0)
		g_exit_code = ft_exit(cmd);
	else if (ft_strcmp(cmd->args->cmd[0], "echo") == 0)
		g_exit_code = ft_echo(cmd);
	return (g_exit_code);
}

int	last_arg_is_builtin(t_minishell *cmd)
{
	t_args	*arg;

	arg = ft_last(cmd->args);
	if (ft_strcmp(arg->cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(arg->cmd[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(arg->cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(arg->cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(arg->cmd[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(arg->cmd[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(arg->cmd[0], "echo") == 0)
		return (1);
	else
		return (0);
}

void	fork_builtin(t_minishell *cmd)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		g_exit_code = exec_builtin(cmd);
		free_env(cmd->envs);
		exit(g_exit_code);
	}
	else
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
		if (ft_strcmp(cmd->args->cmd[0], "exit") == 0)
			exit(0);
	}
}

int	is_env_buitin(t_minishell *cmd)
{
	t_args	*arg;

	arg = ft_last(cmd->args);
	if (ft_strcmp(arg->cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(arg->cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(arg->cmd[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(arg->cmd[0], "exit") == 0)
		return (1);
	else
		return (0);
}
