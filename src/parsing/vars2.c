/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:24:30 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/24 11:27:50 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_env_start(char c)
{
	if (is_spaces(c) || !c || c == '?')
		return (1);
	else
		return (0);
}

int	write_env_var(t_minishell *minishell, char *content, char *cmd)
{
	char	**splitted_env_var;
	int		iter;

	iter = 0;
	if (check_env_start(cmd[minishell->write_params->i
				+ minishell->write_params->k + 1]))
	{
		content[minishell->write_params->i + minishell->write_params->j] = '$';
		minishell->write_params->j++;
		return (1);
	}
	splitted_env_var = get_env_var_content(minishell->envs, cmd
			+ minishell->write_params->i + minishell->write_params->k);
	if (!splitted_env_var)
		return (get_len(cmd + minishell->write_params->i
				+ minishell->write_params->k + 1) + 1);
	while (splitted_env_var[1][iter])
	{
		content[minishell->write_params->i + minishell->write_params->j
			+ iter] = splitted_env_var[1][iter];
		iter++;
	}
	minishell->write_params->j += iter;
	return (ft_strlen(splitted_env_var[0]) + 1);
}
