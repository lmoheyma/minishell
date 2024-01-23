/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:56:47 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/23 14:10:29 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	setup_files(t_minishell *minishell)
{
	t_tokens	*tmp;

	tmp = minishell->tokens;
	while (tmp)
	{
		if (ft_strncmp(tmp->type, "in_file", 7) == 0)
			if (replace_infile(minishell, tmp->content))
				return (1);
		if (ft_strncmp(tmp->type, "out_file", 8) == 0)
			if (replace_outfile(minishell, tmp->content))
				return (1);
		if (ft_strncmp(tmp->type, "append_out_file", 15) == 0)
			if (replace_append_outfile(minishell, tmp->content))
				return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	replace_infile(t_minishell *minishell, char *path)
{
	if (minishell->fd_in != 0)
		close(minishell->fd_in);
	minishell->fd_in = open(path, O_RDONLY);
	if (minishell->fd_in < 0)
		return (ft_err(minishell, "bash: No such file or directory\n", 1), 1);
	return (0);
}

int	replace_outfile(t_minishell *minishell, char *path)
{
	if (minishell->fd_out != 1)
		close(minishell->fd_out);
	minishell->fd_out = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (minishell->fd_out < 0)
		return (ft_err(minishell, "bash: No such file or directory\n", 1), 1);
	return (0);
}

int	replace_append_outfile(t_minishell *minishell, char *path)
{
	if (minishell->fd_out != 1)
		close(minishell->fd_out);
	minishell->fd_out = open(path, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (minishell->fd_out < 0)
		return (ft_err(minishell, "bash: No such file or directory\n", 1), 1);
	return (0);
}
