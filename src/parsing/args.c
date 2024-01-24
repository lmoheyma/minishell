/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:38:40 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/24 09:30:01 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_args	*create_arg(t_minishell *minishell)
{
	t_args	*arg;

	arg = ft_calloc(sizeof(t_args), 1);
	if (!arg)
		return (NULL);
	arg->cmd = ft_split_args(minishell->tokens->content);
	arg->next = NULL;
	return (arg);
}

int	setup_args(t_minishell *minishell)
{
	minishell->args_start = NULL;
	while (minishell->tokens)
	{
		if (is_cmd(minishell->tokens->type))
		{
			if (!minishell->args_start)
			{
				minishell->args = create_arg(minishell);
				if (!minishell->args)
					return (1);
				minishell->args_start = minishell->args;
			}
			else
			{
				minishell->args->next = create_arg(minishell);
				if (!minishell->args->next)
					return (1);
				minishell->args = minishell->args->next;
			}
		}
		minishell->tokens = minishell->tokens->next;
	}
	minishell->args = minishell->args_start;
	minishell->tokens = minishell->tokens_start;
	return (0);
}
