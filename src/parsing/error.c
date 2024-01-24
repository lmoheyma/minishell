/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:17:40 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/24 14:54:53 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_err(t_minishell *minishell, char *err, int code)
{
	free_tokens(&minishell->tokens_start);
	free_args(&minishell->args_start);
	if (code)
		g_exit_code = code;
	ft_putstr_fd(err, 2);
}

void	free_tokens(t_tokens **tokens)
{
	t_tokens	*tmp;

	while (*tokens)
	{
		tmp = (*tokens)->next;
		free((*tokens)->content);
		free(*tokens);
		*tokens = tmp;
	}
}

void	free_args(t_args **args)
{
	t_args	*tmp;
	int		i;

	i = 0;
	if (!args || !*args)
		return ;
	while (*args)
	{
		tmp = (*args)->next;
		i = 0;
		if (!(*args)->cmd || !(*(*args)->cmd))
			return ;
		while ((*args)->cmd[i])
			free((*args)->cmd[i++]);
		free((*args)->cmd);
		free(*args);
		*args = tmp;
	}
}
