/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:12:40 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/24 16:57:48 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_spaces(str[i]) && ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0'
				&& str[i] <= '9')))
		i++;
	return (i);
}

int	get_env_var_size_loop(t_env *env, char *str, int *i)
{
	int		j;
	char	*sub_path;
	char	**splitted_env;

	j = 0;
	while (env->content[j] != '=')
		j++;
	sub_path = ft_substr(env->content, 0, j);
	if (ft_strncmp(str, sub_path, get_len_for_env(str, sub_path)) == 0)
	{
		free(sub_path);
		splitted_env = ft_split(env->content, '=');
		*i += (ft_strlen(splitted_env[0]) + 1);
		return (ft_strlen(splitted_env[1]) - (ft_strlen(splitted_env[0]) + 1));
	}
	free(sub_path);
	return (0);
}

int	get_env_var_size(t_env *env, char *str, int *i)
{
	t_env	*temp;
	int		j;

	j = 0;
	temp = env;
	if (str[0] == '?')
		return (*i += 1, int_len(g_exit_code));
	if (!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z')
			|| (str[0] >= '0' && str[0] <= '9')))
		return (*i += 1, 0);
	while (env)
	{
		j = get_env_var_size_loop(env, str, i);
		if (j != 0)
			return (j);
		env = env->next;
	}
	env = temp;
	return (*i += get_len(str), get_len(str) * -1);
}

char	**get_env_var_content_loop(t_env *env, char *str)
{
	int		j;
	char	*sub_path;
	char	**splitted_env;

	j = 0;
	while (env->content[j] != '=')
		j++;
	sub_path = ft_substr(env->content, 0, j);
	if (ft_strncmp(str, sub_path, get_len_for_env(str, sub_path)) == 0)
	{
		free(sub_path);
		splitted_env = ft_split(env->content, '=');
		return (splitted_env);
	}
	free(sub_path);
	return (NULL);
}

char	**get_env_var_content(t_env *env, char *str)
{
	char	**j;
	t_env	*temp;

	str++;
	temp = env;
	j = NULL;
	if (str[0] == '?')
		return (j = set_exit_code(j), j);
	if (!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z')
			|| (str[0] >= '0' && str[0] <= '9')))
		return (0);
	while (env)
	{
		j = get_env_var_content_loop(env, str);
		if (j)
			return (j);
		env = env->next;
	}
	env = temp;
	return (NULL);
}
