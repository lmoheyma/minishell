/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:31:39 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/23 22:53:55 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*dup_env(char **envp)
{
	int		i;
	t_env	*env;
	t_env	*first;

	i = 0;
	env = NULL;
	if (!*envp)
	{
		env = empty_start_env(env);
		return (env);
	}
	add_back_node_env(&env, new_env_node(envp[i]));
	first = env;
	i++;
	while (envp[i])
		add_back_node_env(&env, new_env_node(envp[i++]));
	env = first;
	return (env);
}

void	print_env(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		printf("%s\n", env->content);
		env = env->next;
	}
}

int	ft_env(t_minishell *cmd)
{
	print_env(cmd->envs);
	return (0);
}
