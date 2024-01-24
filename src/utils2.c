/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:16:27 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/23 22:57:54 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_args	*ft_last(t_args *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	print_error_str(char *str)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putstr_fd("\n", 2);
}

long int	ft_atol(char *str)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (ft_strncmp(str + i, "9223372036854775808", 19) == 0)
		return (LONG_MIN);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		// if ((unsigned long long)res * sign > 9223372036854775807ULL
		// 	|| (unsigned long long)res * sign < -9223372036854775808ULL)
		// 	return (print_error_exit(str), 2);
		i++;
	}
	return (res * sign);
}

int	is_builtin_arg(t_args *arg)
{
	if (ft_strcmp(arg->cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(arg->cmd[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(arg->cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(arg->cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(arg->cmd[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(arg->cmd[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(arg->cmd[0], "echo") == 0)
		return (1);
	else
		return (0);
}