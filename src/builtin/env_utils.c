/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:08:53 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/24 13:53:29 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*new_env_node(void *content)
{
	t_env	*node;
	char	*str;
	
	str = ft_strdup(content);
	node = malloc(sizeof(*node));
	if (!node || !str)
		return (NULL);
	node->content = str;
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

t_env	*empty_start_env(t_env *env)
{
	char	*str;
	char	cwd[PATH_MAX];
	char	*pwd;

	str = ft_strdup("");
	pwd = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	str = ft_strjoin(str, "PATH=/home/lmoheyma/bin:/home/lmoheyma/bin");
	str = ft_strjoin(str, ":/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin");
	str = ft_strjoin(str, ":/sbin:/bin:/usr/games:/usr/local/games:/snap/bin");
	add_back_node_env(&env, new_env_node(pwd));
	add_back_node_env(&env, new_env_node("SHLVL=1"));
	add_back_node_env(&env, new_env_node(str));
	add_back_node_env(&env, new_env_node("_=/usr/bin/env"));
	return (env);
}
