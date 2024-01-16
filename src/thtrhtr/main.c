/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleite-b <aleite-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:08:38 by aleite-b          #+#    #+#             */
/*   Updated: 2024/01/16 10:20:13 by aleite-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;
	char		*buff;

	(void)buff;
	(void)argc;
	(void)argv;
	init_env(&minishell, envp);
	parse_all_minishell(&minishell, "< ubidsfk nadsk bfkhabn fkahsdn fkas dfkjndsakjf nsdakj | kldfsanjkl nasjlfnasdl fjnlsa d | dsfmnaflj nadsljnf asldjn flajsd");
	// while (1)
	// {
	// 	buff = readline("minishell> ");
	// 	printf("%s\n", buff);
	// 	parse_all_minishell(&minishell, buff);
	// 	free(buff);
	// }
}
