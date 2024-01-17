/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:56:47 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/17 16:23:54 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	setup_files(t_minishell *minishell)
{
	t_tokens	*tmp;

	tmp = minishell->tokens;
	while (tmp)
	{
		if (ft_strncmp(tmp->type, "in_file", 7) == 0)
			replace_infile(minishell, tmp->content);
		if (ft_strncmp(tmp->type, "out_file", 8) == 0)
			replace_outfile(minishell, tmp->content);
		if (ft_strncmp(tmp->type, "append_out_file", 15) == 0)
			replace_append_outfile(minishell, tmp->content);
		tmp = tmp->next;
	}
}

void	replace_infile(t_minishell *minishell, char *path)
{
	close(minishell->fd_in);
	minishell->fd_in = open(path, O_RDONLY);
	if (minishell->fd_in < 0)
		ft_err(minishell, "In file open");
}

void	replace_outfile(t_minishell *minishell, char *path)
{
	close(minishell->fd_out);
	minishell->fd_out = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (minishell->fd_out < 0)
		ft_err(minishell, "Out file open");
}

void	replace_append_outfile(t_minishell *minishell, char *path)
{
	close(minishell->fd_out);
	minishell->fd_out = open(path, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (minishell->fd_out < 0)
		ft_err(minishell, "Out file open");
}
