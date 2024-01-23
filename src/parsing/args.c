/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:38:40 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/23 16:02:57 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	create_args(t_minishell *minishell)
{
	t_tokens	*save;
	int			depart;

	depart = 1;
	minishell->args_start = NULL;
	save = minishell->tokens;
	while (minishell->tokens || depart)
	{
		if (depart)
			depart = 0;
		if (is_cmd(minishell->tokens->type))
		{
			minishell->args = ft_calloc(sizeof(t_args), 1);
			if (!minishell->args)
				return (1);
			if (!minishell->args_start)
				minishell->args_start = minishell->args;
			minishell->args->cmd = ft_split_args(minishell->tokens->content);
			// minishell->args->cmd = ft_split(minishell->tokens->content, ' ');
			minishell->args->next = NULL;
			minishell->args = minishell->args->next;
		}
		minishell->tokens = minishell->tokens->next;
	}
	minishell->args = minishell->args_start;
	minishell->tokens = save;
	return (0);
}
