/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:20:58 by aleite-b          #+#    #+#             */
/*   Updated: 2024/02/01 09:47:02 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	set_token_type(t_tokens *token, char *str, int *i)
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
	if (!str[*i] || (ft_strncmp(token->type, "pipe", 4) && (ft_strncmp(str + *i,
					"<<", 2) == 0 || ft_strncmp(str + *i, ">>", 2) == 0
				|| ft_strncmp(str + *i, "<", 1) == 0 || ft_strncmp(str + *i,
					">", 1) == 0)))
		return (1);
	else
		return (0);
}

int	write_loop(t_minishell *minishell, t_tokens *token, char *cmd,
		t_write_params *params)
{
	if (cmd[params->i + params->k] == '\\' && params->trigger == '/')
	{
		token->content[params->i + params->j] = cmd[params->i + params->k + 1];
		params->i++;
		params->k++;
		return (1);
	}
	else if (cmd[params->i + params->k] == '$' && params->trigger != '\''
		&& ft_strncmp(token->type, "here_doc", 8))
	{
		params->k += write_env_var(minishell, token->content, cmd);
		return (1);
	}
	if (cmd[params->i + params->k] == '\'' && params->trigger == '/')
		params->trigger = '\'';
	else if (cmd[params->i + params->k] == '\"' && params->trigger == '/')
		params->trigger = '\"';
	else if (cmd[params->i + params->k] == params->trigger
		&& params->trigger != '/')
		params->trigger = '/';
	return (0);
}

void	write_word(t_minishell *minishell, t_tokens *token, char *cmd)
{
	int				check_cmd;
	t_write_params	*params;

	params = init_write_params(minishell);
	if (!params)
		return ;
	params->trigger = '/';
	check_cmd = is_cmd(token->type);
	while ((cmd[params->i + params->k] && !is_spaces(cmd[params->i + params->k])
			&& !is_special_char(cmd[params->i + params->k]) && !check_cmd)
		|| (cmd[params->i + params->k] && !is_special_char(cmd[params->i
					+ params->k]) && check_cmd) || (cmd[params->i + params->k]
			&& (params->trigger == '\'' || params->trigger == '\"')))
	{
		if (write_loop(minishell, token, cmd, params))
			continue ;
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
	if (check_only_null_env_var(cmd, &j, minishell))
		return (ft_err(minishell, "", 0), NULL);
	token = ft_calloc(sizeof(t_tokens), 1);
	if (!token)
		return (ft_err(minishell, "Token Malloc err\n", 1), NULL);
	j = 0;
	if (set_token_type(token, cmd, i))
		return (ft_err(minishell, "bash: syntax error near unexpected token\n",
				2), NULL);
	var_size = nb_special_char(minishell, token, cmd + *i, &j);
	token->content = ft_calloc(sizeof(char), (j + var_size + 1));
	if (!token->content)
		return (ft_err(minishell, "Token Content Malloc err\n", 1), NULL);
	write_word(minishell, token, cmd + *i);
	if (ft_strlen(token->content) < 1)
		return (ft_err(minishell,
				"bash: syntax error near unexpected token '|'\n", 2), NULL);
	token->next = NULL;
	*i += j;
	return (token);
}

int	setup_tokens(t_minishell *minishell, char *cmd)
{
	int	i;

	i = 0;
	skip_spaces(cmd, &i);
	if (cmd[i] == '|')
		return (ft_err(minishell,
				"bash: syntax error near unexpected token `|'\n", 2), 1);
	if (i >= ft_strlen(cmd))
		return (ft_err(minishell, "", 2), 1);
	minishell->tokens = create_token(cmd, &i, minishell);
	if (!minishell->tokens)
		return (1);
	minishell->tokens_start = minishell->tokens;
	skip_spaces(cmd, &i);
	while (cmd[i])
	{
		minishell->tokens->next = create_token(cmd, &i, minishell);
		if (!minishell->tokens->next)
			return (1);
		minishell->tokens = minishell->tokens->next;
		skip_spaces(cmd, &i);
	}
	minishell->tokens = minishell->tokens_start;
	return (0);
}
