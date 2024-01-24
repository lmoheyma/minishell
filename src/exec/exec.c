/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:35:31 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/25 00:46:16 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	command_execute(t_minishell *cmd)
{
	if (is_builtin(cmd) == TRUE && !cmd->is_pipe)
	{
		if (is_env_buitin(cmd) == TRUE)
			exec_builtin(cmd);
		else
			fork_builtin(cmd);
	}
	else if (cmd->is_pipe)
	{
		exec_pipe_command(cmd);
	}
	else if (!cmd->is_pipe)
		fork_process(cmd);
}

void	child(t_minishell *cmd)
{
	signal(SIGQUIT, signals_manager_child);
	dup2(cmd->fd_out, STDOUT_FILENO);
	dup2(cmd->fd_in, STDIN_FILENO);
	if ((access(cmd->args->cmd[0], F_OK | X_OK) == 0))
		exec_absolute_path(cmd, cmd->args);
	else
		exec_simple_command(cmd, cmd->args);
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
}

void	parent( int pid)
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

void	fork_process(t_minishell *cmd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		child(cmd);
	}
	else
	{
		parent(pid);
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
				g_exit_code = 126;
				perror("execve");
			}
			exit(EXIT_FAILURE);
		}
		free(exe);
	}
	if (!is_builtin_arg(arg))
	{
		if (arg->cmd[0] != NULL && access(arg->cmd[0], F_OK) && ft_memchr(arg->cmd[0], '/', ft_strlen(arg->cmd[0])) == NULL)
			print_error_str(arg->cmd[0]);
		else if (access(arg->cmd[0], X_OK) == -1)
			perror("bash");
		if (errno == EACCES || errno == ENOTDIR)
			g_exit_code = 126;
		else if (errno == ENOENT || errno != 0)
			g_exit_code = 127;
	}
	else if (ft_strcmp(arg->cmd[0], "exit") == 0 && arg->cmd[1])
		g_exit_code = ft_exit_code(arg);
	free_str(path_split);
	free_all(cmd);
	exit(g_exit_code);
}

void	exec_absolute_path(t_minishell *cmd, t_args *arg)
{
	g_exit_code = 0;
	execve(arg->cmd[0], arg->cmd, env_tab(cmd->envs));
	perror("execve");
	g_exit_code = 127;
	exit(EXIT_FAILURE);
}
