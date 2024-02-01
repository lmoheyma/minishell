/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:16:27 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/31 14:49:51 by lmoheyma         ###   ########.fr       */
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

int	ft_atol(char *str, long long *res)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (*res > LLONG_MAX / 10 || (*res == LLONG_MAX / 10 && (str[i]
					- '0') > LLONG_MAX % 10))
		{
			if (sign == -1 && *res == LLONG_MAX / 10 && (str[i]
					- '0') == (LLONG_MAX % 10 + 1))
				return (*res = LLONG_MIN, 1);
			return (0);
		}
		*res = *res * 10 + (str[i] - '0');
		i++;
	}
	return (*res *= sign, 1);
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

char	*ft_strcat(char *dest, char *src)
{
	char	*ptr;

	ptr = dest + ft_strlen(dest);
	while (*src)
		*ptr++ = *src++;
	*ptr = '\0';
	return (dest);
}
