/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:11:24 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/23 22:12:07 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	export_error(char *str)
{
	ft_putstr_fd("export: '", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("': not a valid identifier\n", 1);
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
