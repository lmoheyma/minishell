/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:56:47 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/16 10:36:09 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	replace_files(t_minishell *minishell, char *path, char c, int trigger)
{
	if (c == '<' && access(path, F_OK | R_OK) != 0)
		return ;
	else
	{
		if (minishell->fd_in)
			close(minishell->fd_in);
		minishell->fd_in = open(path, O_RDONLY);
	}
	if (c == '<' && access(path, F_OK | R_OK | W_OK) != 0)
		return ;
	else
	{
		if (minishell->fd_in)
			close(minishell->fd_in);
		if (trigger)
			minishell->fd_in = open(path, O_WRONLY | O_CREAT | O_APPEND, 00777);
		else
			minishell->fd_in = open(path, O_WRONLY | O_CREAT | O_TRUNC, 00777);
	}
}

char	*file_path(char *cmd, char c, int *trigger, int *i)
{
	char	*str;
	int		j;

	printf("1 : %s\n", cmd);
	j = 0;
	while (cmd[*i] != '\0' && cmd[*i] != c)
		*i += 1;
	printf("3 : %s\n", cmd + *i);
	if (cmd[*i] != '\0' && cmd[*i + 1] == c)
	{
		*trigger = 1;
		*i += 1;
	}
	while (cmd[*i] && (cmd[*i] == ' ' || (cmd[*i] <= 9 && cmd[*i] >= 13)))
		*i += 1;
	j = *i;
	while (cmd[*i] && (cmd[j] != ' ' || (cmd[j] >= 9 && cmd[j] <= 13)))
		j++;
	str = malloc(sizeof(char) * (j - *i + 1));
	if (!str)
		return (NULL);
	while (cmd[*i] && (cmd[*i] != ' ' || (cmd[*i] >= 9 && cmd[*i] <= 13)))
	{
		str[j] = cmd[*i];
		*i += 1;
		j++;
	}
	printf("2 : %s\n", str);
	return (str);
}
// gerer 3 4 chevrons

char	*file_set(t_minishell *minishell, char *cmd, char c)
{
	int		i;
	int		trigger;
	char	*str;
	(void)minishell;

	i = 0;
	trigger = 0;
	// while (cmd[i])
	// {
		str = file_path(cmd, c, &trigger, &i);
		printf("I = %d\n", i);
		// if (str)
		// 	replace_files(minishell, str, c, trigger);
		free(str);
	// }
	return (str);
}

void	set_files(t_minishell *minishell, char *cmd)
{
	file_set(minishell, cmd, '<');
	// file_set(minishell, cmd, '>');
	printf("1");
}
