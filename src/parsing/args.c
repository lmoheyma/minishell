/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:38:40 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/23 21:09:08 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls1                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:38:40 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/23 21:08:19 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	create_args(t_minishell *minishell)
{
	t_tokens	*save;

	minishell->args_start = NULL;
	save = minishell->tokens;
	while (minishell->tokens)
	{
		if (is_cmd(minishell->tokens->type))
		{
			if (!minishell->args_start)
			{
				printf("d");
				minishell->args = ft_calloc(sizeof(t_args), 1);
				if (!minishell->args)
					return (1);
				minishell->args->cmd = ft_split_args(minishell->tokens->content);
				minishell->args_start = minishell->args;
				minishell->args->next = NULL;
			}
			else
			{
				printf("f");
				minishell->args->next = ft_calloc(sizeof(t_args), 1);
				if (!minishell->args->next)
					return (1);
				minishell->args->next->cmd = ft_split_args(minishell->tokens->content);
				// minishell->args->cmd = ft_split(minishell->tokens->content, ' ');
				minishell->args = minishell->args->next;
				minishell->args->next = NULL;
			}
		}
		minishell->tokens = minishell->tokens->next;
	}
	minishell->args = minishell->args_start;
	minishell->tokens = save;
	return (0);
}
