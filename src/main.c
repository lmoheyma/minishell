/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:30:14 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/31 21:37:11 by lmoheyma         ###   ########.fr       */
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

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ft_strdup("minishell> "));
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
		free_all(cmd);
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
		{
			free_fd_arg_token(cmd);
			continue ;
		}
		if (check_all_arg(cmd) || is_builtin(cmd) == TRUE || (ft_strncmp(buffer,
					"./", 2) == 0) || (access(cmd->args->cmd[0],
					F_OK | X_OK) == 0))
			command_execute(cmd);
		else
		{
			print_error(cmd, 1);
			g_exit_code = 127;
		}
		free_fd_arg_token(cmd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*buffer;
	t_minishell	*cmd;

	(void)argv;
	buffer = NULL;
	if (argc != 1)
		return (ft_putendl_fd("Too much arguments", 1), 1);
	cmd = (t_minishell *)malloc(sizeof(t_minishell));
	if (!cmd)
		return (0);
	parse_all_minishell(cmd, "start");
	free_tokens(&cmd->tokens_start);
	free_args(&cmd->args_start);
	signal(SIGINT, signals_manager);
	signal(SIGQUIT, SIG_IGN);
	cmd->envs = dup_env(envp);
	g_exit_code = 0;
	main_loop(cmd, buffer);
	free(cmd);
	return (0);
}
