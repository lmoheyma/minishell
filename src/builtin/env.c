/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:31:39 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/14 14:23:58 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*new_env_node(void *content)
{
	t_env	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

t_env	*last_env_node(t_env *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	add_back_node_env(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst)
	{
		if (*lst)
		{
			last = last_env_node(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

t_env	*dup_env(char **envp)
{
	int	i;
	t_env *env;
	t_env	*first;

	i = 0;
	env = NULL;
	add_back_node_env(&env, new_env_node(envp[i]));
	first = env;
	i++;
	while (envp[i])
		add_back_node_env(&env, new_env_node(envp[i++]));
	env = first;
	return (env);
}

void print_env(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		printf("%s\n", env->content);
		env = env->next;
	}
}

int ft_env(t_minishell *cmd)
{
	print_env(cmd->envs);
	return (0);
}