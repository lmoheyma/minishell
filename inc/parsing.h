/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:15:25 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/16 10:35:08 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_tokens
{
	char			*content;
	char			*type;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_args
{
	char			**cmd;
	struct s_args	*next;
}	t_args;

typedef struct s_minishell
{
	t_env		*envs;
	int			fd_in;
	int			fd_out;
	int			is_pipe;
	t_args		*args;
	t_tokens	*tokens;
}	t_minishell;

void		parse_all_minishell(t_minishell *minishell, char *cmd);
void		init_env(t_minishell *minishell, char **envp);
void		set_files(t_minishell *minishell, char *cmd);

int			get_elem(char *cmd, char c);
void		parse_all_minishell(t_minishell *minishell, char *cmd);

void		set_token_type(t_tokens *token, char *str, int *i);
int			handle_quotes_escapes(char *cmd, int *i, int *j, int *trigger);
void		write_word(t_tokens *token, char *cmd);
t_tokens	*create_token(char *cmd, int *i);
void		setup_tokens(t_minishell *minishell, char *cmd);

int			is_spaces(char c);
int			is_special_char(char c);
void		skip_spaces(char *str, int *i);
int			is_cmd(char *type);
void		skip_special_char(char *str, int *i);
int			nb_special_char(t_tokens *token, char *cmd, int *i);

void		create_args(t_minishell *minishell);

#endif