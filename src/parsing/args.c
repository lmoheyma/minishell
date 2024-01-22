/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:38:40 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/22 09:43:58 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	create_args(t_minishell *minishell)
{
	t_tokens	*save;
	t_args		*first_arg;
	t_args		**current_arg;

	current_arg = &minishell->args;
	first_arg = NULL;
	save = minishell->tokens;
	while (minishell->tokens)
	{
		if (is_cmd(minishell->tokens->type))
		{
			minishell->args = malloc(sizeof(t_args));
			if (!minishell->args)
				return ;
			minishell->args->cmd = ft_split_args(minishell->tokens->content);
			// minishell->args->cmd = ft_split(minishell->tokens->content, ' ');
			minishell->args->next = NULL;
			if (!first_arg)
				first_arg = minishell->args;
			*current_arg = minishell->args;
			current_arg = &(*current_arg)->next;
			minishell->args = *current_arg;
		}
		minishell->tokens = minishell->tokens->next;
	}
	minishell->args = first_arg;
	minishell->tokens = save;
}
