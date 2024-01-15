/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:36:27 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/15 20:57:46 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void unset_var(t_env *env, char *var)
{
	t_env	*temp;
	char	**var_split;

	var_split = ft_split(env->content, '=');
	temp = env;
	if (env->next && ft_strncmp(var_split[0], var, ft_strlen(var)) == 0)
	{
		printf("%s\n", env->next->content);
		return ;
	}
	while (env)
	{
		var_split = ft_split(env->content, '=');
		if (env->next && ft_strncmp(var_split[0], var, ft_strlen(var)) == 0)
		{
			printf("%s\n", env->next->content);
		}
		env = env->next;
		free(var_split);
	}
	env = temp;
}

void ft_unset(t_minishell *cmd)
{
	int	i;

	i = 1;
	while (cmd->args->cmd[i])
	{
		if (is_env_var_set(cmd->envs, cmd->args->cmd[i]))
			unset_var(cmd->envs, cmd->args->cmd[i]);
		i++;
	}
	
}