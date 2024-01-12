/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:58:48 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/11 20:18:36 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_here_doc(char **argv)
{
	int	fd[2];
	int	pid;

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

int	add_line_to_fd(char **argv, int fd[2])
{
	int		running;
	char	*line;

	running = 1;
	close(fd[0]);
	while (running)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(line);
			exit(0);
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
	return (0);
}
