/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:23:57 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/13 20:38:02 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_cd(t_minishell *cmd)
{
	// char	*oldpwd;
	// char	*pwd;
	//printf("%s\n", cmd->args->cmd[1]);
	if (chdir(cmd->args->cmd[1]) == -1)
		perror("chdir()");
	return (0);
}
