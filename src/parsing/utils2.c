/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:26:28 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/16 11:24:11 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	nb_special_char(t_tokens *token, char *cmd, int *i)
{
	int	trigger;
	int	count;
	int	check_cmd;

	trigger = 0;
	count = 0;
	check_cmd = is_cmd(token->type);
	while ((cmd[*i] && !is_spaces(cmd[*i]) && !check_cmd) || (cmd[*i]
			&& !is_special_char(cmd[*i]) && check_cmd) || (cmd[*i] && trigger))
	{
		if ((cmd[*i] == '\'' || cmd[*i] == '\"') && !trigger)
		{
			trigger = 1;
			count++;
		}
		else if ((cmd[*i] == '\'' || cmd[*i] == '\"') && !trigger)
		{
			trigger = 1;
			count++;
		}
		else if (cmd[*i] == '\\')
			count++;
		*i += 1;
	}
	return (count);
}

int    ft_cmdsize(t_args *args)
{
    int        i;
    t_args    *tmp;

    i = 0;
    if (!args)
        return (0);
    tmp = args;
    while (tmp)
    {
        tmp = tmp->next;
        i++;
    }
    return (i);
}

