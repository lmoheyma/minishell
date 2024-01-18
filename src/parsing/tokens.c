/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:20:58 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/18 17:11:00 by antoine          ###   ########.fr       */
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

void	write_word(t_minishell *minishell, t_tokens *token, char *cmd)
{
	char			trigger;
	int				check_cmd;
	t_write_params	*params;

	params = init_write_params(minishell);
	if (!params)
		return ;
	trigger = '/';
	check_cmd = is_cmd(token->type);
	while ((cmd[params->i + params->k] && !is_spaces(cmd[params->i + params->k])
			&& !check_cmd) || (cmd[params->i + params->k]
			&& !is_special_char(cmd[params->i + params->k]) && check_cmd)
		|| (cmd[params->i + params->k] && (trigger == '\'' || trigger == '\"')))
	{
		if (cmd[params->i + params->k] == '\'' && trigger == '/')
			trigger = '\'';
		else if (cmd[params->i + params->k] == '\"' && trigger == '/')
			trigger = '\"';
		else if (cmd[params->i + params->k] == trigger && trigger != '/')
			trigger = '/';
		else if (cmd[params->i + params->k] == '$')
			params->k += write_env_var(minishell, token->content, cmd);
		token->content[params->i + params->j] = cmd[params->i + params->k];
		params->i++;
	}
	token->content[params->i + params->j] = '\0';
	free(params);
}

t_tokens	*create_token(char *cmd, int *i, t_minishell *minishell)
{
	int			j;
	int			var_size;
	t_tokens	*token;

	j = 0;
	token = malloc(sizeof(t_tokens));
	if (!token)
		return (ft_err(minishell, "Token Malloc err"), NULL);
	set_token_type(token, cmd, i);
	var_size = nb_special_char(minishell, token, cmd + *i, &j);
	token->content = malloc(sizeof(char) * (j + var_size + 1));
	if (!token->content)
		return (ft_err(minishell, "Token Content Malloc err"), NULL);
	write_word(minishell, token, cmd + *i);
	if (ft_strlen(token->content) < 1)
		return (ft_err(minishell,
				"bash: syntax error near unexpected token '|'"), NULL);
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
		return (ft_err(minishell, ""));
	minishell->tokens = create_token(cmd, &i, minishell);
	if (!minishell->tokens)
		return ;
	save = minishell->tokens;
	minishell->tokens->next = NULL;
	skip_spaces(cmd, &i);
	while (cmd[i])
	{
		minishell->tokens->next = create_token(cmd, &i, minishell);
		if (!minishell->tokens->next)
			return ;
		minishell->tokens = minishell->tokens->next;
		minishell->tokens->next = NULL;
		skip_spaces(cmd, &i);
	}
	minishell->tokens = save;
}
