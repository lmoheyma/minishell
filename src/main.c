/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:30:14 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/12 18:18:35 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

t_minishell	*simple_init(char *line, char **envp)
{
	t_minishell *cmd;
	t_args *arg;

	arg = NULL;
	cmd = (t_minishell *)malloc(sizeof(t_minishell));
	ft_add_back(&arg, ft_new(line));
	//ft_add_back(&arg, ft_new("head"));
	ft_add_back(&arg, ft_new("wc -l"));
	cmd->args = arg;
	cmd->envs = envp;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->is_pipe = 0;
	cmd->nb_cmd = 2;
	return (cmd);
}

void print_args(t_args *arg)
{
	int i;
	int	j;

	i = -1;
	j = 0;
	if (!arg)
		return ;
	while (arg)
	{
		while (++i < 2)
			printf("args[%d][%d] -> %s ", j, i, arg->cmd[i]);
		arg = arg->next;
		i = -1;
		j++;
		if (arg)
			printf("\n");
	}
	printf("\n");
}

int get_path1(t_minishell *cmd, t_args *arg)
{
	char	**path_split;
	char	*sub_path;
	char	*exe;
	int		i;
	
	i = 0;
	path_split = ft_split(get_path(cmd->envs), ':');
	while (path_split[++i])
	{
		sub_path = ft_strjoin(path_split[i], "/");
		exe = ft_strjoin(sub_path, arg->cmd[0]);
		free(sub_path);
		if (access(exe, F_OK | X_OK) == 0)
			break ;
		free(exe);
	}
	free_str(path_split);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	char		*buffer;
	size_t		buffer_size;
	//t_args *arg = NULL;
	t_minishell *cmd;
	(void)argc;
	(void)argv;
	(void)envp;
	
	buffer_size = 2048;
	buffer = (char *)malloc(sizeof(char) * buffer_size);
	if (!buffer)
		return (0);
	while (1)
	{
		//printf("Avant de lire l'input\n");
		buffer = readline("minishell>");
		//printf("Apres de lire l'input\n");
		cmd = simple_init(buffer, envp);
		//print_args(cmd->args);
		command_execute(cmd);
		free(cmd);
		free(buffer);
		//free(line);
	}
	return (0);
}
