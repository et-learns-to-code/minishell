/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:37:56 by etien             #+#    #+#             */
/*   Updated: 2024/11/19 13:46:18 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// The main function will prompt the user for input in a while loop.
// The input will be added to the readline history and then checked
// for syntax errors. If there is an error, the program will not do
// anything and will continue prompting the user for input.
// If the input passes the syntax check, it will be parsed to construct
// the abstract syntax tree (AST). The commands will then be executed.
// Finally, the AST will be freed and the loop restarts.
int	main(void)
{
	char	*input;
	t_cmd	*ast;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		add_history(input);
		if (syntax_error(input))
			continue ;
		ast = parse_cmd(input);
		run_cmd_control(input, ast);
		free_ast(ast);
	}
	return (EXIT_SUCCESS);
}