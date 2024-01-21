/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:54:13 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/21 18:39:04 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// void	free_builtin_tab(char **builtin, int nb_builtin)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < nb_builtin)
// 		free(builtin[i]);
// 	free(builtin);
// }

char	**fill_builtin_tab(char **builtin)
{
	builtin[0] = "echo";
	builtin[1] = "cd";
	builtin[2] = "pwd";
	builtin[3] = "export";
	builtin[4] = "unset";
	builtin[5] = "env";
	builtin[6] = "exit";
	return (builtin);
}

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

void	exec_builtin(t_minishell *cmd)
{	
	dup2(cmd->fd_out, STDOUT_FILENO);
	if (ft_strcmp(cmd->args->cmd[0], "cd") == 0)
		ft_cd(cmd);
	else if (ft_strcmp(cmd->args->cmd[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->args->cmd[0], "env") == 0)
		ft_env(cmd);
	else if (ft_strcmp(cmd->args->cmd[0], "export") == 0)
		ft_export(cmd);
	else if (ft_strcmp(cmd->args->cmd[0], "unset") == 0)
		ft_unset(cmd);
	else if (ft_strcmp(cmd->args->cmd[0], "exit") == 0)
		ft_exit(cmd);
	else if (ft_strcmp(cmd->args->cmd[0], "echo") == 0)
		ft_echo(cmd);
}

int	last_arg_is_builtin(t_minishell *cmd)
{
	t_args *arg;

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

void fork_builtin(t_minishell *cmd)
{
	int pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		exec_builtin(cmd);
	}
	else
	{
		//g_pid = pid;
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
		if (ft_strcmp(cmd->args->cmd[0], "exit") == 0)
			exit(0);
	}
}

int is_env_buitin(t_minishell *cmd)
{
	t_args *arg;

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

int	is_builtin_arg(t_args *arg)
{
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
