/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:36:27 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/24 13:52:35 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	unset_first_node(t_env **env, char *var)
{
	t_env	*current;
	char	**var_split;

	current = *env;
	var_split = ft_split((*env)->content, '=');
	if (env && ft_strncmp(var_split[0], var, ft_strlen(var)) == 0)
	{
		*env = current->next;
		free(current->content);
		free(current);
		free_2d_array(var_split);
		return (1);
	}
	free_2d_array(var_split);
	return (0);
}

void	unset_var(t_env **env, char *var)
{
	char	**var_split;
	t_env	*current;
	t_env	*to_delete;
	int		flag;

	current = *env;
	flag = unset_first_node(env, var);
	while (!flag && current && current->next)
	{
		var_split = ft_split(current->next->content, '=');
		if (current->next && ft_strncmp(var_split[0], var, ft_strlen(var)) == 0)
		{
			to_delete = current->next;
			current->next = current->next->next;
			free(to_delete->content);
			free(to_delete);
			free_2d_array(var_split);
			break ;
		}
		current = current->next;
		free_2d_array(var_split);
	}
}

int	ft_unset(t_minishell *cmd)
{
	int	i;

	i = 1;
	if (!cmd->args->cmd[1])
		return (1);
	while (cmd->envs && cmd->args->cmd[i])
	{
		if (is_env_var_set(cmd->envs, cmd->args->cmd[i]))
			unset_var(&cmd->envs, cmd->args->cmd[i]);
		i++;
	}
	return (0);
}
