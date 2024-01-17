/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:49:13 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/17 14:57:05 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_env(t_minishell *minishell, char **envp)
{
	t_env	*save;

	minishell->envs = malloc(sizeof(t_env));
	if (!minishell->envs)
		return ;
	minishell->envs->content = *envp;
	save = minishell->envs;
	minishell->envs->next = NULL;
	envp++;
	while (*envp)
	{
		minishell->envs->next = malloc(sizeof(t_env));
		if (!minishell->envs->next)
			return ;
		minishell->envs->next->content = *envp;
		envp++;
		minishell->envs = minishell->envs->next;
	}
	minishell->envs = save;
}
