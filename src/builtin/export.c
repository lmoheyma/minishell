/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:36:11 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/31 22:40:28 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	export_without_arg(t_minishell *cmd)
{
	t_env	*temp;
	t_env	*env;

	env = cmd->envs;
	if (!env)
		return ;
	temp = cmd->envs;
	while (env)
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd(env->content, 1);
		write(1, "\n", 1);
		env = env->next;
	}
	env = temp;
}

int	check_syntax(t_minishell *cmd, char *str)
{
	char	**str_split;

	(void)cmd;
	if (!ft_strchr(str, '=') && ft_isdigit(str[0]))
		return (export_error(str), 0);
	str_split = ft_split(str, '=');
	if (!str_split || !*str_split)
		return (free_2d_array(str_split), export_error(str), 0);
	if (!ft_strchr(str, '=') && !check_valid_identifer(str_split))
		return (export_error(str), 0);
	if (!ft_strchr(str, '='))
		return (0);
	if (str[0] == '=')
		return (export_error(str), 0);
	if (!check_valid_identifer(str_split))
		return (free_2d_array(str_split), export_error(str), 0);
	if (ft_isdigit(str_split[0][0]) || str_split[0][0] == '=')
		return (free_2d_array(str_split), export_error(str), 0);
	return (free_2d_array(str_split), 1);
}

void	change_var(t_env *env, char *str, char **str_split)
{
	char	*sub_path;
	char	*str_w_equals;
	char	*str_big;
	int		j;

	j = 0;
	str_w_equals = ft_strjoin(str_split[0], "=");
	str_big = ft_strjoin(str_w_equals, str_split[1]);
	while (env)
	{
		j = 0;
		while (env->content[j] != '=')
			j++;
		sub_path = ft_substr(env->content, 0, j);
		if (ft_strncmp(str, sub_path, j) == 0)
		{
			change_var2(env, str_split, str_w_equals, str_big);
		}
		free(sub_path);
		env = env->next;
	}
}

void	add_to_env(t_env *env, char *str)
{
	char	**str_split;

	str_split = ft_split(str, '=');
	if (is_env_var_set(env, str_split[0]))
		change_var(env, str, str_split);
	else
		add_back_node_env(&env, new_env_node(str));
	free_2d_array(str_split);
}

int	ft_export(t_minishell *cmd)
{
	t_args	*arg;
	int		i;

	i = 1;
	arg = cmd->args;
	if (!cmd->args->cmd[1])
		export_without_arg(cmd);
	else
	{
		while (arg->cmd[i])
		{
			if (check_syntax(cmd, arg->cmd[i]))
				add_to_env(cmd->envs, arg->cmd[i]);
			i++;
		}
	}
	return (g_exit_code);
}
