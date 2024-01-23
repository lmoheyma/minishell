/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:35:08 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/23 22:18:55 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	only_n(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	print_arg(t_args *arg, int i)
{
	while (arg->cmd[i])
	{
		ft_putstr_fd(arg->cmd[i], 1);
		if (arg->cmd[i + 1] && arg->cmd[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
}

int	ft_echo(t_minishell *cmd)
{
	int		i;
	int		has_n;
	t_args	*arg;

	i = 1;
	has_n = 0;
	arg = cmd->args;
	if (!cmd->args->cmd[1])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	while (arg->cmd[i] && ((ft_strcmp(arg->cmd[i], "-n") == 0)
			|| (arg->cmd[i][0] == '-' && only_n(arg->cmd[i] + 1))))
	{
		has_n = 1;
		i++;
	}
	if (ft_strncmp(arg->cmd[1], "$?", 2) == 0)
	{
		ft_putnbr_fd(g_exit_code, 1);
		if (!has_n)
			write(1, "\n", 1);
		return (0);
	}
	print_arg(arg, i);
	if (!has_n)
		write(1, "\n", 1);
	return (0);
}
