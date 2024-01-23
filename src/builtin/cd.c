/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:23:57 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/23 22:53:47 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*replace_home_alias(t_minishell *cmd, char *path)
{
	char	*sub_path;
	int		i;
	int		cmd_len;

	i = 0;
	cmd_len = ft_strlen(cmd->args->cmd[1]);
	if (!path)
		path = ft_strdup("");
	while (cmd->args->cmd[1][i] && cmd->args->cmd[1][i] != '~')
		i++;
	sub_path = ft_substr(cmd->args->cmd[1], 0, i);
	path = ft_strjoin_free(path, sub_path);
	free(sub_path);
	path = ft_strjoin_free(path, get_home(cmd->envs));
	i++;
	sub_path = ft_substr(cmd->args->cmd[1], i, cmd_len);
	path = ft_strjoin_free(path, sub_path);
	free(sub_path);
	return (path);
}

void	exec_cd(t_minishell *cmd, char *path)
{
	if (ft_strchr(cmd->args->cmd[1], '~'))
		path = replace_home_alias(cmd, path);
	else
		path = ft_strdup(cmd->args->cmd[1]);
	if (chdir(path) == -1)
		perror("cd");
}

int	ft_cd(t_minishell *cmd)
{
	char	*path;
	char	cwd[PATH_MAX];
	char	old_cwd[PATH_MAX];

	if (cmd->args->cmd[1] && cmd->args->cmd[2])
		return (ft_putstr_fd("bash: cd: too many arguments\n", 1), 1);
	path = NULL;
	getcwd(old_cwd, sizeof(old_cwd));
	if (!cmd->args->cmd[1])
	{
		if (!get_home(cmd->envs))
			return (ft_putendl_fd("cd: HOME not set", 1), 1);
		chdir(get_home(cmd->envs));
	}
	else
		exec_cd(cmd, path);
	free(path);
	getcwd(cwd, sizeof(cwd));
	add_oldpwd_to_env(cmd->envs, old_cwd);
	add_pwd_to_env(cmd->envs, cwd);
	return (0);
}
