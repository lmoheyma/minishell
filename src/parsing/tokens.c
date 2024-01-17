/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:20:58 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/16 11:23:10 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_token_type(t_tokens *token, char *str, int *i)
{
	if (ft_strncmp(str + *i, "<<", 2) == 0)
		token->type = "here_doc";
	else if (ft_strncmp(str + *i, ">>", 2) == 0)
		token->type = "append_out_file";
	else if (ft_strncmp(str + *i, "<", 1) == 0)
		token->type = "in_file";
	else if (ft_strncmp(str + *i, ">", 1) == 0)
		token->type = "out_file";
	else if (ft_strncmp(str + *i, "|", 1) == 0)
		token->type = "pipe";
	else
		token->type = "simple_cmd";
	skip_special_char(str, i);
	skip_spaces(str, i);
}

int	handle_quotes_escapes(char *cmd, int *i, int *j, int *trigger)
{
	if ((cmd[*i + *j] == '\'' || cmd[*i + *j] == '\"') && !(*trigger))
	{
		*trigger = 1;
		(*j)++;
	}
	else if ((cmd[*i + *j] == '\'' || cmd[*i + *j] == '\"') && (*trigger))
	{
		*trigger = 0;
		(*j)++;
	}
	else if (cmd[*i + *j] == '\\')
		(*j)++;
	else
		return (1);
	return (0);
}

void	write_word(t_tokens *token, char *cmd)
{
	int	i;
	int	j;
	int	trigger;
	int	check_cmd;

	i = 0;
	j = 0;
	trigger = 0;
	check_cmd = is_cmd(token->type);
	while ((cmd[i + j] && !is_spaces(cmd[i + j]) && !check_cmd) || (cmd[i + j]
			&& !is_special_char(cmd[i + j]) && check_cmd) || (cmd[i + j]
			&& trigger))
	{
		if (handle_quotes_escapes(cmd, &i, &j, &trigger))
		{
			token->content[i] = cmd[i + j];
			i++;
		}
	}
	token->content[i] = '\0';
}

t_tokens	*create_token(char *cmd, int *i)
{
	int			quotes_count;
	int			j;
	t_tokens	*token;

	j = 0;
	token = malloc(sizeof(t_tokens));
	if (!token)
		return (NULL);
	set_token_type(token, cmd, i);
	quotes_count = nb_special_char(token, cmd + *i, &j);
	token->content = malloc(sizeof(char) * (j - quotes_count + 1));
	if (!token->content)
		return (NULL);
	write_word(token, cmd + *i);
	*i += j;
	return (token);
}

void	setup_tokens(t_minishell *minishell, char *cmd)
{
	int			i;
	t_tokens	*save;

	i = 0;
	skip_spaces(cmd, &i);
	if (i >= ft_strlen(cmd))
		return ;
	minishell->tokens = create_token(cmd, &i);
	if (!minishell->tokens)
		return ;
	save = minishell->tokens;
	minishell->tokens->next = NULL;
	skip_spaces(cmd, &i);
	while (cmd[i])
	{
		minishell->tokens->next = create_token(cmd, &i);
		if (!minishell->tokens->next)
			return ;
		minishell->tokens = minishell->tokens->next;
		minishell->tokens->next = NULL;
		skip_spaces(cmd, &i);
	}
	minishell->tokens = save;
}
