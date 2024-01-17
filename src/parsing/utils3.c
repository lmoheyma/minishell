/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:58:11 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/17 14:56:45 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_write_params	*init_write_params(t_minishell *minishell)
{
	t_write_params	*params;

	params = malloc(sizeof(t_write_params));
	if (!params)
		ft_err(minishell, "Write Params Malloc err");
	minishell->write_params = params;
	params->i = 0;
	params->j = 0;
	params->k = 0;
	return (params);
}
