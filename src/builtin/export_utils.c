/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:11:24 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/02/01 12:32:12 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	export_error(char *str)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exit_code = 1;
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
	return (i);
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

void	change_var2(t_env *env, char **str_split, char *str_w_equals,
		char *str_big)
{
	if (!str_split[1] && !env->content)
		return ;
	if (!str_split[1])
	{
		free(env->content);
		env->content = str_w_equals;
		free(str_big);
	}
	else
	{
		free(env->content);
		env->content = str_big;
		free(str_w_equals);
	}
}

int	check_valid_identifer(char **str_split)
{
	if (ft_strchr(str_split[0], '%') || ft_strchr(str_split[0], '@')
		|| ft_strchr(str_split[0], '-') || ft_strchr(str_split[0], '}')
		|| ft_strchr(str_split[0], '{') || ft_strchr(str_split[0], '*')
		|| ft_strchr(str_split[0], '#') || ft_strchr(str_split[0], '!')
		|| ft_strchr(str_split[0], '+') || ft_strchr(str_split[0], '?')
		|| ft_strchr(str_split[0], '.'))
		return (0);
	return (1);
}
