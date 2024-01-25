/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:26:28 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/25 07:50:04 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	nb_special_char(t_minishell *minishell, t_tokens *token, char *cmd, int *i)
{
	char	trigger;
	int		env_size;

	trigger = '/';
	env_size = 0;
	while ((cmd[*i] && !is_spaces(cmd[*i]) && !is_special_char(cmd[*i])
			&& !is_cmd(token->type)) || (cmd[*i] && !is_special_char(cmd[*i])
			&& is_cmd(token->type)) || (cmd[*i] && (trigger == '\''
				|| trigger == '\"')))
	{
		if (cmd[*i] == '\'' && trigger == '/')
			trigger = '\'';
		else if (cmd[*i] == '\"' && trigger == '/')
			trigger = '\"';
		else if (cmd[*i] == trigger && trigger != '/')
			trigger = '/';
		else if (cmd[*i] == '$' && trigger != '\'' && ft_strncmp(token->type,
				"here_doc", 8))
		{
			env_size += get_env_var_size(minishell->envs, cmd + *i + 1, i);
			continue ;
		}
		*i += 1;
	}
	return (env_size);
}

int	ft_cmdsize(t_args *args)
{
	int		i;
	t_args	*tmp;

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

int	get_len_for_env(char *str, char *sub_path)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && !is_spaces(str[i]) && ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0'
				&& str[i] <= '9')))
		i++;
	while (sub_path[j] && !is_spaces(sub_path[j]) && ((sub_path[j] >= 'a'
				&& sub_path[j] <= 'z') || (sub_path[j] >= 'A'
				&& sub_path[j] <= 'Z') || (sub_path[j] >= '0'
				&& sub_path[j] <= '9')))
		j++;
	if (i > j)
		return (i);
	else
		return (j);
}

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

int	int_len(int nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb *= -1;
		count++;
	}
	while (nb > 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}
