/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:57:48 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/18 21:55:50 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_last_cmd(t_minishell *minishell)
{
	t_args *temp;

	temp = minishell->args;
	while (temp)
	{
		if (!temp->next)
			return (temp->cmd);
		temp = temp->next;
	}
	return (temp->cmd);
}

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

// char	*get_path(char **envp)
// {
// 	int		i;
// 	int		j;
// 	char	*sub_path;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		j = 0;
// 		while (envp[i][j] != '=')
// 			j++;
// 		sub_path = ft_substr(envp[i], 0, j);
// 		if (ft_strncmp("PATH", sub_path, j) == 0)
// 		{
// 			free(sub_path);
// 			return (envp[i] + j + 1);
// 		}
// 		free(sub_path);
// 		i++;
// 	}
// 	return (0);
// }

char	*get_path(t_env *env)
{
	int		j;
	char	*sub_path;

	while (env)
	{
		j = 0;
		//printf("%s\n", env->content);
		while (env->content[j] != '=')
		{
			j++;
		}
		sub_path = ft_substr(env->content, 0, j);
		if (ft_strncmp("PATH", sub_path, j) == 0)
		{
			free(sub_path);
			return (env->content + j + 1);
		}
		free(sub_path);
		env = env->next;
	}
	return (0);
}

int	env_size(t_env *lst)
{
	int		len;

	len = 0;
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

char	**env_tab(t_env *env)
{
	char	**tab;
	int		i;

	tab = (char **)malloc(sizeof(char *) * (env_size(env) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (env)
	{
		tab[i] = env->content;
		env = env->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int	ft_strcmp(const char *str, const char *str2)
{
	size_t	i;

	i = 0;
	while (str[i] && str2[i])
	{
		if (str[i] != str2[i])
			return ((unsigned char)str[i] -(unsigned char)str2[i]);
		i++;
	}
	return (0);
}
