/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:57:48 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/23 22:57:34 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_last_cmd(t_minishell *minishell)
{
	t_args	*temp;

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
	int	i;

	i = 0;
	while (str2[i])
	{
		if (str[i] != str2[i])
			return ((unsigned char)str[i] - (unsigned char)str2[i]);
		i++;
	}
	if (str[i] != str2[i])
		return ((unsigned char)str[i] - (unsigned char)str2[i]);
	return (0);
}
