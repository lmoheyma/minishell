/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:23:57 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/02/01 12:20:50 by lmoheyma         ###   ########.fr       */
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

int	exec_cd(t_minishell *cmd, char *path)
{
	if (ft_strchr(cmd->args->cmd[1], '~'))
	{
		if (!get_home(cmd->envs))
		{
			chdir("..");
			free(path);
			return (0);
		}
		else
			path = replace_home_alias(cmd, path);
	}
	else
		path = ft_strdup(cmd->args->cmd[1]);
	if (chdir(path) == -1)
	{
		free(path);
		perror("cd");
		return (1);
	}
	free(path);
	return (0);
}

void	change_old_and_pwd(t_minishell *cmd, char *oldcwd_malloc,
		char *cwd_malloc)
{
	if (!oldcwd_malloc || !cwd_malloc || !*cwd_malloc || !*oldcwd_malloc)
		return ;
	add_oldpwd_to_env(cmd->envs, oldcwd_malloc);
	add_pwd_to_env(cmd->envs, cwd_malloc);
}

int	ft_cd(t_minishell *cmd)
{
	char	*path;
	char	*cwd_malloc;
	char	*oldcwd_malloc;
	char	old_cwd[PATH_MAX];

	if (cmd->args->cmd[1] && cmd->args->cmd[2])
		return (ft_putstr_fd("bash: cd: too many arguments\n", 2), 1);
	if (getcwd(old_cwd, sizeof(old_cwd)) == NULL)
		oldcwd_malloc = ft_strdup("OLDPWD=");
	else
		oldcwd_malloc = ft_strjoin("OLDPWD=", old_cwd);
	path = NULL;
	if (!cmd->args->cmd[1])
	{
		if (!get_home(cmd->envs))
			return (free(oldcwd_malloc), ft_putendl_fd("cd: HOME not set", 1),
				1);
		chdir(get_home(cmd->envs));
	}
	else
		g_exit_code = exec_cd(cmd, path);
	free(path);
	cwd_malloc = check_pwd();
	return (change_old_and_pwd(cmd, oldcwd_malloc, cwd_malloc), g_exit_code);
}
