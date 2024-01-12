/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:57:48 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/11 18:18:47 by lmoheyma         ###   ########.fr       */
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

char	*get_path(char **envp)
{
	int		i;
	int		j;
	char	*sub_path;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		sub_path = ft_substr(envp[i], 0, j);
		if (ft_strncmp("PATH", sub_path, j) == 0)
		{
			free(sub_path);
			return (envp[i] + j + 1);
		}
		free(sub_path);
		i++;
	}
	return (0);
}
