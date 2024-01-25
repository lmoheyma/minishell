/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:58:48 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/25 16:04:13 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	signal_heredoc(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit(1);
}

void	ft_here_doc(t_minishell *minishell, char *argv)
{
	int	fd[2];
	int	pid;
	int	status;

	status = 0;
	if (pipe(fd) == -1)
		exit(0);
	if (minishell->fd_in != 0)
		close(minishell->fd_in);
	minishell->fd_in = fd[0];
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		add_line_to_fd(argv, fd, minishell);
	}
	waitpid(pid, &status, 0);
	if (status)
		g_exit_code = INT_MAX;
	close(fd[1]);
}

int	add_line_to_fd(char *argv, int fd[2], t_minishell *cmd)
{
	int		running;
	char	*line;
	char	*buffer;

	buffer = ft_strdup("");
	signal(SIGINT, signal_heredoc);
	close(fd[0]);
	running = 1;
	while (running)
	{
		line = readline("> ");
		if (ft_strcmp(line, argv) == 0 || g_exit_code == INT_MAX)
		{
			free(line);
			ft_putstr_fd(buffer, fd[1]);
			free(buffer);
			close(fd[1]);
			free_all(cmd);
			exit(0);
		}
		line = ft_strjoin_free(line, "\n");
		buffer = ft_strjoin_free(buffer, line);
		free(line);
	}
	return (0);
}
