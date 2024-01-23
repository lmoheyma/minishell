/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:35:31 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/23 20:15:46 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void signals_manager_child(int signal)
{

	if (signal == SIGINT)
	{
		printf("\n");
	}
	else if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 1);
	}
}

void command_execute(t_minishell *cmd)
{
	t_args	*last_arg;

	last_arg = ft_last(cmd->args);
	if (last_arg_is_builtin(cmd) == TRUE && cmd->is_pipe && ft_strcmp(last_arg->cmd[0], "echo"))
		return ;
	if (is_builtin(cmd) == TRUE && !cmd->is_pipe)
	{
		if (is_env_buitin(cmd) == TRUE) //cd, export, unset, exit
			exec_builtin(cmd);
		else
			fork_builtin(cmd); // echo, env, pwd
	}
	else if (cmd->is_pipe)
	{
		printf("pipe\n");
		exec_pipe_command(cmd);
	}
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
	{
		signal(SIGQUIT, signals_manager_child);
		dup2(cmd->fd_out, STDOUT_FILENO);
		dup2(cmd->fd_in, STDIN_FILENO);
		if ((access(cmd->args->cmd[0], F_OK | X_OK) == 0))
			exec_absolute_path(cmd, cmd->args);
		else
			exec_simple_command(cmd, cmd->args);
	}
	else
	{
		signal(SIGQUIT, signals_manager_child);
		signal(SIGINT, signals_manager_child);
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);	
		signal(SIGINT, signals_manager);
		signal(SIGQUIT, SIG_IGN);
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
			if (execve(exe, arg->cmd, env_tab(cmd->envs)) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		free(exe);
	}
	if (!is_builtin_arg(arg))
		print_error_str(arg->cmd[0]);
	free_str(path_split);
	exit(EXIT_FAILURE);
}

void	exec_absolute_path(t_minishell *cmd, t_args *arg)
{
	execve(arg->cmd[0], arg->cmd, env_tab(cmd->envs));
	perror("execve");
	exit(EXIT_FAILURE);
}
