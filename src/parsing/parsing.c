/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:56:47 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/16 12:29:18 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_elem(char *cmd, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	parse_all_minishell(t_minishell *minishell, char *cmd)
{
	if (get_elem(cmd, '\"') % 2 != 0 || get_elem(cmd, '\'') % 2 != 0)
		return ;
	setup_tokens(minishell, cmd);
	create_args(minishell);
	// while (minishell->tokens)
	// {
	// 	printf("End Token : %s - %s\n", minishell->tokens->content,
	// 		minishell->tokens->type);
	// 	minishell->tokens = minishell->tokens->next;
	// }
	// while (minishell->args)
	// {
	// 	printf("Args : %s\n", minishell->args->cmd[1]);
	// 	minishell->args = minishell->args->next;
	// }
	minishell->nb_cmd = ft_cmdsize(minishell->args);
	if (minishell->nb_cmd > 1)
		minishell->is_pipe = 1;
}
