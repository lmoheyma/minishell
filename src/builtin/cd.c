/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:23:57 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/18 22:26:04 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_home(t_env *env)
{
	int		j;
	char	*sub_path;

	while (env)
	{
		j = 0;
		// printf("%s\n", env->content);
		while (env->content[j] != '=')
		{
			j++;
		}
		sub_path = ft_substr(env->content, 0, j);
		if (ft_strncmp("HOME", sub_path, j) == 0)
		{
			free(sub_path);
			return (env->content + j + 1);
		}
		free(sub_path);
		env = env->next;
	}
	return (0);
}

char	*replace_home_alias(t_minishell *cmd)
{
	char	*sub_path;
	char	*path;
	int		i;
	int		cmd_len;

	i = 0;
	cmd_len = ft_strlen(cmd->args->cmd[1]);
	path = ft_strdup("");
	while (cmd->args->cmd[1][i] && cmd->args->cmd[1][i] != '~')
		i++;
	sub_path = ft_substr(cmd->args->cmd[1], 0, i);
	path = ft_strjoin(path, sub_path);
	free(sub_path);
	path = ft_strjoin(path, get_home(cmd->envs));
	i++;
	sub_path = ft_substr(cmd->args->cmd[1], i, cmd_len);
	path = ft_strjoin(path, sub_path);
	free(sub_path);
	return (path);
}

int	ft_cd(t_minishell *cmd)
{
	char	*path;

	path = NULL;
	if (!get_home(cmd->envs))
		return (ft_putendl_fd("cd: HOME not set", 1),0);
	if (!cmd->args->cmd[1])
	{
		if (chdir(get_home(cmd->envs)) == -1)
			perror("cd");
		return (0);
	}
	if (ft_strchr(cmd->args->cmd[1], '~'))
		path = replace_home_alias(cmd);
	else
		path = ft_strdup(cmd->args->cmd[1]);
	if (chdir(path) == -1)
		perror("cd");
	// exit(EXIT_SUCCESS);
	return (0);
}
