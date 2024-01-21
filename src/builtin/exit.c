/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:36:47 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/21 01:59:40 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// long int	ft_atolong(const char *nptr)
// {
// 	long int	nb;
// 	int			sign;
// 	char		*str;

// 	nb = 0;
// 	sign = 1;
// 	str = (char *)nptr;
// 	while (ft_isspace(*str))
// 		str++;
// 	if (*str == '-')
// 		sign = -1;
// 	if (*str == '-' || *str == '+')
// 		str++;
// 	if (ft_strncmp(str, "9223372036854775808", 19) == 0)
// 		return (LONG_MIN);
// 	while (ft_isdigit(*str))
// 		nb = nb * 10 + *str++ - '0';
// 	return (nb * sign);
// }


int ft_exit_code(t_args *arg)
{
	int exit_code;
	
	if (!arg->cmd[1])
		exit_code = 0;
	else if (!check_exit_syntax(arg->cmd[1]))
	{
		// print error
		exit_code = 255;
	}
	else
		exit_code = ft_atolong(arg->cmd[1]) % 256;
	if (exit_code != 255 && arg->cmd[1] && arg->cmd[2])
	{
		// too many arg
		exit_code = 256;
	}
	return (exit_code);
}

int check_exit_syntax(char *str)
{
	int	i;
	
	//skip space ?
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] == '0')
		i++;
	// if long; return 0;
	// while arg[i] && is digit; i++
	// if arg[i]; return 0;
	return (1);
}

int is_long(char *str, int i)
{
	// if nb digits > 19; return 0
	// if nb digits == 19 
		// if str[0] == '-' && strncp < 0; return 0
		// if str[0] == '+' && strncp < 0; return 0
	return (1);
}

int ft_exit(t_minishell *cmd)
{
	int exit_code;
	t_args *arg;
	
	arg = cmd->args;
	ft_putstr_fd("exit\n", 1);
	exit_code = ft_exit_code(arg);
	if (exit_code == 256)
		return (1);
	exit(exit_code);
}