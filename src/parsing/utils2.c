/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:26:28 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/24 11:32:45 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	nb_special_char(t_minishell *minishell, t_tokens *token, char *cmd, int *i)
{
	char	trigger;
	int		check_cmd;
	int		env_size;

	trigger = '/';
	env_size = 0;
	check_cmd = is_cmd(token->type);
	while ((cmd[*i] && !is_spaces(cmd[*i]) && !is_special_char(cmd[*i])
			&& !check_cmd) || (cmd[*i] && !is_special_char(cmd[*i])
			&& check_cmd) || (cmd[*i] && (trigger == '\'' || trigger == '\"')))
	{
		if (cmd[*i] == '\'' && trigger == '/')
			trigger = '\'';
		else if (cmd[*i] == '\"' && trigger == '/')
			trigger = '\"';
		else if (cmd[*i] == trigger && trigger != '/')
			trigger = '/';
		else if (cmd[*i] == '$')
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
	int		i;
	char	*s;

	i = 0;
	if (ft_strlen(str) > ft_strlen(sub_path))
		s = str;
	else
		s = sub_path;
	while (s[i] && !is_spaces(s[i]) && ((s[i] >= 'a' && s[i] <= 'z')
			|| (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9')))
		i++;
	return (i);
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
