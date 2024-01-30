/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:24:30 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/30 15:07:48 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_free_tab_s(char **s)
{
	int		i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

int	check_env_start(char c)
{
	if (is_spaces(c) || is_special_char(c) || c == '\'' || c == '\"' || !c)
		return (1);
	else
		return (0);
}

int	write_env_var(t_minishell *minishell, char *content, char *cmd)
{
	char	**splitted_env_var;
	int		iter;

	iter = 0;
	if (check_env_start(cmd[minishell->write_params->i
				+ minishell->write_params->k + 1]))
	{
		content[minishell->write_params->i + minishell->write_params->j] = '$';
		minishell->write_params->j++;
		return (1);
	}
	splitted_env_var = get_env_var_content(minishell->envs, cmd
			+ minishell->write_params->i + minishell->write_params->k);
	if (!splitted_env_var)
		return (get_len(cmd + minishell->write_params->i
				+ minishell->write_params->k + 1) + 1);
	while (splitted_env_var[1][iter])
	{
		content[minishell->write_params->i + minishell->write_params->j
			+ iter] = splitted_env_var[1][iter];
		iter++;
	}
	minishell->write_params->j += iter;
	iter = ft_strlen(splitted_env_var[0]) + 1;
	return (ft_free_tab_s(splitted_env_var), iter);
}

char	**set_exit_code(char **j)
{
	j = malloc(sizeof(char *) * 3);
	j[0] = malloc(sizeof(char) * 2);
	j[0][0] = '?';
	j[0][1] = '\0';
	j[1] = ft_itoa(g_exit_code);
	j[2] = NULL;
	return (j);
}

int	get_len_for_env(char *str, char *sub_path)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && !is_spaces(str[i]) && ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0'
				&& str[i] <= '9')))
		i++;
	while (sub_path[j] && !is_spaces(sub_path[j]) && ((sub_path[j] >= 'a'
				&& sub_path[j] <= 'z') || (sub_path[j] >= 'A'
				&& sub_path[j] <= 'Z') || (sub_path[j] >= '0'
				&& sub_path[j] <= '9')))
		j++;
	if (i > j)
		return (i);
	else
		return (j);
}
