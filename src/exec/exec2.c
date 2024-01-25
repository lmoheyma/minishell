/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 01:09:27 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/25 01:13:12 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_code_and_exit(t_minishell *cmd, t_args *arg, char **path_split)
{
	if (!is_builtin_arg(arg))
	{
		if (arg->cmd[0] != NULL && access(arg->cmd[0], F_OK)
			&& ft_memchr(arg->cmd[0], '/', ft_strlen(arg->cmd[0])) == NULL)
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
