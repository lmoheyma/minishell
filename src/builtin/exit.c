/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:36:47 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/20 22:28:48 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_exit(t_minishell *cmd)
{
	//free all
	// atoi
	//check si arg > 2
	(void)cmd;
	ft_putstr_fd("exit\n", 1);
	exit(0);
	//return (0);
}