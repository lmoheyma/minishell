/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:59:23 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/02/01 12:32:01 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_fd_arg_token(t_minishell *cmd)
{
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	free_tokens(&cmd->tokens_start);
	free_args(&cmd->args_start);
}

void	write_heredoc_eof(int fd)
{
	ft_putstr_fd("bash: warning: here-document ", fd);
	ft_putendl_fd("at line,delimited by end-of-file", fd);
}

char	*check_pwd(void)
{
	char	*cwd_malloc;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		cwd_malloc = ft_strdup("PWD=");
		ft_putstr_fd("error retrieving current directory\n", 1);
	}
	else
		cwd_malloc = ft_strjoin("PWD=", cwd);
	return (cwd_malloc);
}
