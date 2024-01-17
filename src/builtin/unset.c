/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:36:27 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/16 16:30:23 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void unset_var(t_env **env, char *var)
{
	char	**var_split;
	t_env	*current;
	t_env	*to_delete;
	int		flag;

	current = *env;
	var_split = ft_split((*env)->content, '=');
	flag = 0;
	if (env && ft_strncmp(var_split[0], var, ft_strlen(var)) == 0)
	{
		*env = current->next;
		free(current);	
		flag = 1;
	}
	while (!flag && current && current->next)
	{
		var_split = ft_split(current->next->content, '=');
		if (current->next && ft_strncmp(var_split[0], var, ft_strlen(var)) == 0)
		{
			to_delete = current->next;
			current->next = current->next->next;
			free(to_delete);
			break ;
		}
		current = current->next;
		free(var_split);
	}
	if (flag)
		free(var_split);
}

void ft_unset(t_minishell *cmd)
{
	int	i;

	i = 1;
	while (cmd->envs && cmd->args->cmd[i])
	{
		if (is_env_var_set(cmd->envs, cmd->args->cmd[i]))
			unset_var(&cmd->envs, cmd->args->cmd[i]);
		i++;
	}
}