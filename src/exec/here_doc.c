/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:58:48 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/30 15:01:10 by aleite-b         ###   ########.fr       */
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
	{
		close(minishell->fd_in);
		unlink("dev");
	}
	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
		add_line_to_fd(argv, fd, minishell);
	waitpid(pid, &status, 0);
	minishell->fd_in = open("dev", O_RDONLY, 0777);
	dup2(minishell->fd_in, 0);
	if (status)
		g_exit_code = INT_MAX;
	close(fd[1]);
}

int	add_line_to_fd(char *argv, int fd[2], t_minishell *cmd)
{
	char	*line;
	int		dev_fd;

	dev_fd = open("dev", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	signal(SIGINT, signal_heredoc);
	close(fd[0]);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, argv) == 0 || g_exit_code == INT_MAX)
		{
			free(line);
			free_all(cmd);
			close(dev_fd);
			exit(0);
		}
		ft_putendl_fd(line, cmd->fd_in);
		free(line);
	}
	return (0);
}
