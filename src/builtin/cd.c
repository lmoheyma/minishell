/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:23:57 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/23 15:59:53 by lmoheyma         ###   ########.fr       */
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
	path = NULL;
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
	char	cwd[PATH_MAX];
	char	old_cwd[PATH_MAX];

	if (cmd->args->cmd[1] && cmd->args->cmd[2])
		return(ft_putstr_fd("bash: cd: too many arguments\n", 1), 1);
	path = NULL;
	getcwd(old_cwd, sizeof(old_cwd));
	if (!cmd->args->cmd[1])
	{
		if (!get_home(cmd->envs))
			return (ft_putendl_fd("cd: HOME not set", 1), 1);
		chdir(get_home(cmd->envs));
			//perror("cd");
	}
	else
	{
		if (ft_strchr(cmd->args->cmd[1], '~'))
			path = replace_home_alias(cmd);
		else
			path = ft_strdup(cmd->args->cmd[1]);
		if (chdir(path) == -1)
			perror("cd");
	}
	free(path);
	getcwd(cwd, sizeof(cwd));
	add_oldpwd_to_env(cmd->envs, old_cwd);
	add_pwd_to_env(cmd->envs, cwd);
	return (0);
}

void add_pwd_to_env(t_env *env, char *str)
{
	char	cwd[PATH_MAX];
	char	*new_pwd;

	if (is_env_var_set(env, "PWD"))
		change_pwd_var(env, str, ft_strlen(str) + 1, "PWD");
	else
	{
		new_pwd = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
		add_back_node_env(&env, new_env_node(new_pwd));
	}
}

void add_oldpwd_to_env(t_env *env, char *str)
{
	if (is_env_var_set(env, "OLDPWD"))
		change_pwd_var(env, str, ft_strlen(str) + 1, "OLDPWD");
}

char	*get_pwd(t_env *env, char *str)
{
	int		j;
	char	*sub_path;

	while (env)
	{
		j = 0;
		while (env->content[j] != '=')
			j++;
		sub_path = ft_substr(env->content, 0, j);
		if (ft_strncmp(str, sub_path, j) == 0)
		{
			free(sub_path);
			return (env->content);
		}
		free(sub_path);
		env = env->next;
	}
	return (0);
}

void change_pwd_var(t_env *env, char *pwd, int path_len, char *str)
{
	char	*sub_path;
	int		j;
	
	j = 0;
	while (env)
	{
		j = 0;
		while (env->content[j] != '=')
			j++;
		sub_path = ft_substr(env->content, 0, j);
		if (ft_strncmp(str, sub_path, j) == 0)
		{
			if (!pwd && !env->content)
				return ;
			j++;
			// if (!str_split[1])
			// 	ft_strlcpy2(env->content, str_split[0], path_len);
			// else
			ft_strlcpy(env->content + j, pwd, path_len);
		}
		free(sub_path);
		env = env->next;
	}
}
