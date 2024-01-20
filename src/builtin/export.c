/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:36:11 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/20 21:38:42 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	export_error(char *str)
{
	ft_putstr_fd("export: '", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("': not a valid identifier\n", 1);
}

int	is_env_var_set(t_env *env, char *str)
{
	int		j;
	t_env	*temp;
	char	*sub_path;

	temp = env;
	while (env)
	{
		j = 0;
		while (env->content[j] != '=')
			j++;
		sub_path = ft_substr(env->content, 0, j);
		if (ft_strcmp(str, sub_path) == 0)
		{
			free(sub_path);
			env = temp;
			return (1);
		}
		free(sub_path);
		env = env->next;
	}
	env = temp;
	return (0);
}

void	export_without_arg(t_minishell *cmd)
{
	t_env	*temp;
	t_env	*env;

	env = cmd->envs;
	if (!env)
		return ;
	temp = cmd->envs;
	while (env)
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd(env->content, 1);
		write(1, "\n", 1);
		env = env->next;
	}
	env = temp;
}

int	check_syntax(t_minishell *cmd, char *str)
{
	char	**str_split;

	(void)cmd;
	if (str[0] == '=')
		return (export_error(str), 0);
	str_split = ft_split(str, '=');
	if (!str_split || !*str_split)
		return (export_error(str), 0);
	if (ft_strchr(str_split[0], '%') || ft_strchr(str_split[0], '@')
		|| ft_strchr(str_split[0], '-') || ft_strchr(str_split[0], '}')
		|| ft_strchr(str_split[0], '{') || ft_strchr(str_split[0], '*')
		|| ft_strchr(str_split[0], '#') || ft_strchr(str_split[0], '!')
		|| ft_strchr(str_split[0], '+') || ft_strchr(str_split[0], '?')
		|| ft_strchr(str_split[0], '.'))
		return (export_error(str), 0);
	if (ft_isdigit(str_split[0][0]) || str_split[0][0] == '=')
		return (export_error(str), 0);
	return (1);
}

int	ft_strlcpy2(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i++] = '=';
		dest[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

void	change_var(t_env *env, char *str, char **str_split)
{
	char	*sub_path;
	int		j;

	j = 0;
	while (env)
	{
		j = 0;
		while (env->content[j] != '=')
			j++;
		sub_path = ft_substr(env->content, 0, j);
		if (ft_strncmp(str, sub_path, j) == 0)
		{
			if (!str_split[1] && !env->content)
				return ;
			j++;
			if (!str_split[1])
				ft_strlcpy2(env->content, str_split[0], ft_strlen(str));
			else
				ft_strlcpy(env->content + j, str_split[1], ft_strlen(str));
		}
		free(sub_path);
		env = env->next;
	}
}

void	add_to_env(t_env *env, char *str)
{
	char	**str_split;

	str_split = ft_split(str, '=');
	if (is_env_var_set(env, str_split[0]))
		change_var(env, str, str_split);
	else
		add_back_node_env(&env, new_env_node(str));
}

void	ft_export(t_minishell *cmd)
{
	t_args	*arg;
	int		i;

	i = 1;
	arg = cmd->args;
	if (!cmd->args->cmd[1])
		export_without_arg(cmd);
	else
	{
		while (arg->cmd[i])
		{
			if (check_syntax(cmd, arg->cmd[i]))
				add_to_env(cmd->envs, arg->cmd[i]);
			i++;
		}
	}
}
