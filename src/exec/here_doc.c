/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:58:48 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/25 10:26:41 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_here_doc(t_minishell *minishell, char *argv)
{
	int	fd[2];
	int	pid;

	if (minishell->fd_in != 0)
		close(minishell->fd_in);
	minishell->fd_in = 0;
	if (pipe(fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
		add_line_to_fd(argv, fd);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	waitpid(pid, NULL, 0);
}

int	add_line_to_fd(char *argv, int fd[2])
{
	int		running;
	char	*line;

	running = 1;
	close(fd[0]);
	while (running)
	{
		line = readline("> ");
		if (ft_strncmp(line, argv, ft_strlen(argv)) == 0)
		{
			free(line);
			exit(0);
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	return (0);
}
