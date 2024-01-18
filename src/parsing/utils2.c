/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:26:28 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/18 14:06:29 by antoine          ###   ########.fr       */
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
	while ((cmd[*i] && !is_spaces(cmd[*i]) && !check_cmd) || (cmd[*i]
			&& !is_special_char(cmd[*i]) && check_cmd) || (cmd[*i]
			&& (trigger == '\'' || trigger == '\"')))
	{
		if (cmd[*i] == '\'' && trigger == '/')
			trigger = '\'';
		else if (cmd[*i] == '\"' && trigger == '/')
			trigger = '\"';
		else if (cmd[*i] == trigger && trigger != '/')
			trigger = '/';
		else if (cmd[*i] == '$')
			env_size += get_env_var_size(minishell->envs, cmd + *i + 1, i);
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

int	get_env_var_size(t_env *env, char *str, int *i)
{
	int		j;
	t_env	*temp;
	char	*sub_path;
	char	**splitted_env;

	temp = env;
	while (env)
	{
		j = 0;
		while (env->content[j] != '=')
			j++;
		sub_path = ft_substr(env->content, 0, j);
		if (ft_strncmp(str, sub_path, j) == 0)
		{
			free(sub_path);
			splitted_env = ft_split(env->content, '=');
			*i += (ft_strlen(splitted_env[0]) + 1);
			return (ft_strlen(splitted_env[1]) + 1);
		}
		free(sub_path);
		env = env->next;
	}
	env = temp;
	return (0);
}

char	**get_env_var_content(t_env *env, char *str)
{
	int		j;
	t_env	*temp;
	char	*sub_path;
	char	**splitted_env;

	str++;
	temp = env;
	while (env)
	{
		j = 0;
		while (env->content[j] != '=')
			j++;
		sub_path = ft_substr(env->content, 0, j);
		if (ft_strncmp(str, sub_path, j) == 0)
		{
			free(sub_path);
			splitted_env = ft_split(env->content, '=');
			return (splitted_env);
		}
		free(sub_path);
		env = env->next;
	}
	env = temp;
	return (NULL);
}

int	write_env_var(t_minishell *minishell, char *content, char *cmd)
{
	char	**splitted_env_var;
	int		iter;
	int		len;

	iter = 0;
	len = 0;
	splitted_env_var = get_env_var_content(minishell->envs, cmd
			+ minishell->write_params->i + minishell->write_params->k);
	if (!splitted_env_var)
	{
		while (cmd[minishell->write_params->i + minishell->write_params->k
			+ len] && !is_spaces(cmd[minishell->write_params->i
				+ minishell->write_params->k + len]))
			len++;
		return (len);
	}
	while (splitted_env_var[1][iter])
	{
		content[minishell->write_params->i + minishell->write_params->j
			+ iter] = splitted_env_var[1][iter];
		iter++;
	}
	minishell->write_params->j += iter;
	return (ft_strlen(splitted_env_var[0]) + 1);
}
