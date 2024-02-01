/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:58:48 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/31 15:11:05 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	signal_heredoc(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	close(g_exit_code);
	g_exit_code = 130;
	exit(1);
}

void	ft_here_doc(t_minishell *minishell, char *argv)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		exit(0);
	if (minishell->fd_in != 0)
		close(minishell->fd_in);
	g_exit_code = fd[1];
	minishell->fd_in = fd[0];
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		add_line_to_fd(argv, fd, minishell);
	}
	waitpid(pid, NULL, 0);
	close(fd[1]);
}

int	add_line_to_fd(char *argv, int fd[2], t_minishell *cmd)
{
	int		running;
	char	*line;
	char	buffer[9000];
	char	lim[4096];

	ft_strlcpy(lim, argv, ft_strlen(argv) + 1);
	free_all(cmd);
	signal(SIGINT, signal_heredoc);
	close(fd[0]);
	running = 1;
	while (running)
	{
		line = readline("> ");
		if (!line)
		{
			free(line);
			write_heredoc_eof(fd[1]);
			if (running == 2)
				ft_putstr_fd(buffer, fd[1]);
			close(fd[1]);
			exit(0);
		}
		ft_heredoc2(line, lim, buffer, &running);
	}
	return (0);
}

void	ft_heredoc2(char *line, char *lim, char *buffer, int *running)
{
	if (ft_strcmp(line, lim) == 0)
	{
		free(line);
		ft_putstr_fd(buffer, g_exit_code);
		close(g_exit_code);
		exit(0);
	}
	if (*running == 1)
	{
		ft_strlcpy(buffer, line, ft_strlen(line) + 1);
		ft_strcat(buffer, "\n");
		*running = 2;
	}
	else
	{
		ft_strcat(buffer, line);
		ft_strcat(buffer, "\n");
	}
}
