/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:54:13 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/12 15:22:28 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	char **builtin;
	int	nb_builtin;
	int	i;

	nb_builtin = 6;
	builtin = (char **)malloc(sizeof(char *) * nb_builtin);
	if (!builtin)
		return (0);
	builtin = fill_builtin_tab(builtin);
	i = -1;
	while (++i < nb_builtin)
	{
		if (cmd->args->cmd[0] == builtin[i])
			return (TRUE);
	}
	free(builtin);
	return (FALSE);
}

int exec_builtin(t_minishell *cmd)
{
	(void)cmd;
	return (0);
}
