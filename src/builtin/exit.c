/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:30:16 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/31 22:43:07 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_error_exit(char *str)
{
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	is_too_long(char *str, int i)
{
	int	nb_digits;

	nb_digits = ft_strlen(str + i);
	if (nb_digits > 19)
		return (1);
	if (nb_digits == 19)
	{
		if (str[0] == '-' && ft_strncmp(str + i, "9223372036854775808", 19) < 0)
			return (1);
		if ((str[0] == '+' || ft_isdigit(str[0])) && ft_strncmp(str + i,
				"9223372036854775807", 19) < 0)
			return (1);
	}
	return (0);
}

int	check_exit_syntax(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] == '0')
		i++;
	if (is_too_long(str, i))
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	ft_exit_code(t_args *arg)
{
	int			exit_code;
	long long	res;

	res = 0;
	exit_code = 2;
	if (!arg->cmd[1])
		exit_code = 0;
	else if (!check_exit_syntax(arg->cmd[1]))
		print_error_exit(arg->cmd[1]);
	else
	{
		if (ft_atol(arg->cmd[1], &res))
			exit_code = res % 256;
		else
			print_error_exit(arg->cmd[1]);
	}
	if (exit_code != 2 && arg->cmd[1] && arg->cmd[2])
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		exit_code = 256;
	}
	return (exit_code);
}

int	ft_exit(t_minishell *cmd)
{
	int		exit_code;
	t_args	*arg;

	arg = cmd->args;
	ft_putstr_fd("exit\n", 1);
	exit_code = ft_exit_code(arg);
	if (exit_code != 256)
		free_all(cmd);
	if (exit_code == 256)
		return (1);
	exit(exit_code);
}
