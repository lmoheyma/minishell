/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:58:11 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/23 15:49:40 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_write_params	*init_write_params(t_minishell *minishell)
{
	t_write_params	*params;

	params = ft_calloc(sizeof(t_write_params), 1);
	if (!params)
		return (ft_err(minishell, "Write Params Malloc err\n", 1), NULL);
	minishell->write_params = params;
	params->i = 0;
	params->j = 0;
	params->k = 0;
	return (params);
}
