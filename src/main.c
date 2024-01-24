/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:30:14 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/24 09:18:06 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		g_exit_code;

void	print_error(t_minishell *cmd, int flag)
{
	if (flag == 1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd->args->cmd[0], 2);
		ft_putstr_fd(": command not found", 2);
		ft_putstr_fd("\n", 2);
	}
}

char	*dynamic_prompt(void)
{
	char	*prompt;
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	prompt = NULL;
	prompt = ft_strjoin("minishell:", cwd);
	prompt = ft_strjoin_free(prompt, "$ ");
	return (prompt);
}

char	*get_input(t_minishell *cmd)
{
	char	*prompt;
	char	*buffer;

	prompt = dynamic_prompt();
	buffer = readline(prompt);
	free(prompt);
	if (!buffer)
	{
		printf("exit\n");
		free_env(cmd->envs);
		free_tokens(&cmd->tokens_start);
		free_args(&cmd->args_start);
		free(cmd);
		exit(0);
	}
	if (!ft_strlen(buffer))
		return (free(buffer), NULL);
	if (buffer && *buffer)
		add_history(buffer);
	return (buffer);
}

void	main_loop(t_minishell *cmd, char *buffer)
{
	while (1)
	{
		buffer = get_input(cmd);
		if (!buffer)
			continue ;
		if (parse_all_minishell(cmd, buffer))
			continue ;
		if (!cmd->args)
			continue ;
		if (get_path1(cmd, cmd->args) || is_builtin(cmd) == TRUE
			|| (ft_strncmp(buffer, "./", 2) == 0) || (access(cmd->args->cmd[0],
					F_OK | X_OK) == 0))
			command_execute(cmd);
		else
		{
			print_error(cmd, 1);
			g_exit_code = 127;
		}
		free_tokens(&cmd->tokens_start);
		free_args(&cmd->args_start);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*buffer;
	t_minishell	*cmd;
	int			flag;
	int			i;

	(void)argv;
	i = 0;
	flag = 0;
	buffer = NULL;
	if (argc != 1)
		return (ft_putendl_fd("Too much arguments", 1), 1);
	cmd = (t_minishell *)malloc(sizeof(t_minishell));
	if (!cmd)
		return (0);
	signal(SIGINT, signals_manager);
	signal(SIGQUIT, SIG_IGN);
	cmd->envs = dup_env(envp);
	main_loop(cmd, buffer);
	free(cmd);
	return (0);
}
