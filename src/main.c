/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:30:14 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/23 15:22:43 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int g_exit_code;

void print_error(t_minishell *cmd, int flag)
{
	if (flag == 1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd->args->cmd[0], 2);
		ft_putstr_fd(": command not found", 2);
		ft_putstr_fd("\n", 2);
	}
}

t_args	*ft_new(void *content)
{
	t_args	*list;

	list = malloc(sizeof(*list));
	if (!list)
		return (NULL);
	list->cmd = ft_split(content, ' ');
	list->next = NULL;
	return (list);
}

t_args	*ft_last(t_args *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_add_back(t_args **lst, t_args *new)
{
	t_args	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_last(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

int get_path1(t_minishell *cmd, t_args *arg)
{
	char	**path_split;
	char	*sub_path;
	char	*exe;
	int		i;
	
	i = 0;
	if (!cmd->args->cmd[0])
		return (0);
	path_split = ft_split(get_path(cmd->envs), ':');
	if (!path_split)
		return (0);
	while (path_split[++i])
	{
		sub_path = ft_strjoin(path_split[i], "/");
		exe = ft_strjoin(sub_path, arg->cmd[0]);
		free(sub_path);
		if (access(exe, F_OK | X_OK) == 0)
			break ;
		free(exe);
		exe = NULL;
	}
	free(exe);
	free_str(path_split);
	return (exe == NULL ? 0 : 1);
}

char	*dynamic_prompt(void)
{
	char	*prompt;
	char 	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	prompt = NULL;
	prompt = ft_strjoin("minishell:", cwd);
	prompt = ft_strjoin_free(prompt, "$ ");
	return (prompt);
}

void signals_manager(int signal)
{

	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

char	*get_input(void)
{
	char	*prompt;
	char	*buffer;

	prompt = dynamic_prompt();
	buffer = readline(prompt);
	free(prompt);
	if (!buffer)
	{
		printf("exit\n");
		exit(0);
	}
	if (!ft_strlen(buffer))
		return (free(buffer), NULL);
	if (buffer && *buffer)
    	add_history(buffer);
	return (buffer);
}

int main(int argc, char **argv, char **envp)
{
	char		*buffer;
	t_minishell *cmd;
	int			flag;
	int			i;
	(void)argv;
	
	i = 0;
	flag = 0;
	if (argc != 1)
		return (ft_putendl_fd("Too much arguments", 1), 1);
	cmd = (t_minishell *)malloc(sizeof(t_minishell));
	if (!cmd)
		return (0);
	signal(SIGINT, signals_manager);
	signal(SIGQUIT, SIG_IGN);
	cmd->envs = dup_env(envp);
	buffer = NULL;
	while (1)
	{
		cmd->is_pipe = 0;
		buffer = get_input();
		if (!buffer)
			continue ;
		if (ft_strncmp(buffer, "$?", 2) == 0)
		{
			while (ft_strncmp(buffer + i, "$?", 2) == 0)
			{
				ft_putnbr_fd(cmd->exit_code, 1);
				i += 2;
			}
			ft_putstr_fd("\n", 1);
			i = 0;
			continue ;
		}
		if (parse_all_minishell(cmd, buffer))
			continue ;
		if (!cmd->args)
			continue ;
		if (get_path1(cmd, cmd->args) || is_builtin(cmd) == TRUE || (ft_strncmp(buffer, "./", 2) == 0) || (access(cmd->args->cmd[0], F_OK | X_OK) == 0))
			command_execute(cmd);
		else
		{
			print_error(cmd, 1);
			g_exit_code = 127;
		}
		free_tokens(&cmd->tokens_start);
		free_args(&cmd->args_start);
		// free(buffer);
	}
	return (0);
}
