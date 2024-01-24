/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:43:15 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/24 22:33:24 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int check_all_arg(t_minishell *cmd)
{
	t_args *arg;
	int value;

	value = 0;
	arg = cmd->args;
	while (arg)
	{
		value = get_path1(cmd, arg);
		if (value)
			return (1);
		arg = arg->next;
	}
	return (0);
}

int	get_path1(t_minishell *cmd, t_args *arg)
{
	char	**path_split;
	char	*sub_path;
	char	*exe;
	int		i;

	i = 0;
	if (!arg->cmd[0])
		return (0);
	path_split = ft_split(get_path(cmd->envs), ':');
	if (!path_split)
		return (0);
	while (path_split[++i])
	{
		sub_path = ft_strjoin(path_split[i], "/");
		exe = ft_strjoin(sub_path, arg->cmd[0]);
		free(sub_path);
		if (access(exe, F_OK | X_OK) == 0)
			break ;
		free(exe);
		exe = NULL;
	}
	free(exe);
	if (exe == NULL)
		return (free_str(path_split), 0);
	return (free_str(path_split), 1);
}

char	*get_path(t_env *env)
{
	int		j;
	char	*sub_path;

	while (env)
	{
		j = 0;
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
