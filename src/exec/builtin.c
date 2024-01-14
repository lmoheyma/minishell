/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:54:13 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/14 17:35:56 by lmoheyma         ###   ########.fr       */
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

int is_builtin(t_minishell *cmd)
{
	if (ft_strncmp(cmd->args->cmd[0], "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd->args->cmd[0], "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd->args->cmd[0], "env", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd->args->cmd[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd->args->cmd[0], "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd->args->cmd[0], "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd->args->cmd[0], "echo", 2) == 0)
		return (1);
	else
		return (0);
}

void exec_builtin(t_minishell *cmd)
{
	if (ft_strncmp(cmd->args->cmd[0], "cd", 2) == 0)
		ft_cd(cmd);
	else if (ft_strncmp(cmd->args->cmd[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd->args->cmd[0], "env", 3) == 0)
		ft_env(cmd);
	else if (ft_strncmp(cmd->args->cmd[0], "export", 7) == 0)
		ft_export(cmd);
	else if (ft_strncmp(cmd->args->cmd[0], "unset", 5) == 0)
		ft_unset(cmd);
	else if (ft_strncmp(cmd->args->cmd[0], "exit", 4) == 0)
		ft_exit(cmd);
	else if (ft_strncmp(cmd->args->cmd[0], "echo", 2) == 0)
		ft_echo(cmd);
}
