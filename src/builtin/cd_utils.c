/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:06:31 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/24 16:50:11 by lmoheyma         ###   ########.fr       */
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

void	add_pwd_to_env(t_env *env, char *str)
{
	char	cwd[PATH_MAX];
	char	*new_pwd;

	if (is_env_var_set(env, "PWD"))
		change_pwd_var(env, str, ft_strlen(str) + 1, "PWD");
	else
	{
		free(str);
		new_pwd = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));  // A MODIFIER
		add_back_node_env(&env, new_env_node(new_pwd));
		free(new_pwd);
	}
}

void	add_oldpwd_to_env(t_env *env, char *str)
{
	if (is_env_var_set(env, "OLDPWD"))
	{
		change_pwd_var(env, str, ft_strlen(str) + 1, "OLDPWD");
	}
	else
		free(str);
}

void	change_pwd_var(t_env *env, char *pwd, int path_len, char *str)
{
	char	*sub_path;
	int		j;

	(void)path_len;
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
			free(env->content);
			env->content = pwd;
		}
		free(sub_path);
		env = env->next;
	}
}
