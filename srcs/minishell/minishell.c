/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:58:57 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/24 16:04:13 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* this function prevent segfault during tokenisation process
by assessing if the user input is only composed of whitespace */

static int	is_spaces_only(char *str)
{
	int 	res;
	int		i;
	int		error;

	res = 0;
	i = 0;
	error = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ')
			error++;
		i++;
	}
	if (error == 0)
		res = 1;
	return (res);
}

static int	minishell(t_shell *shell)
{
	char		*user_input;
	t_token		*token;

	user_input = NULL;
	while (42)
	{
		user_input = readline("$> ");
		if (ft_strlen(user_input) && !is_spaces_only(user_input))
		{
			shell->user_input = user_input;
			add_history(user_input);
			token = parse_user_input(shell);
			display_every_token(token); // test func
			free(user_input);
			user_input = NULL;
			process_tokens(token, shell); // process actual complete tokens
			token_clear(token); // free_function
		}
	}
	return (0);
}

/* the main fonction just init the shell struct and launch minishell func */

int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;

	(void)argc;
	(void)argv;
	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		exit(EXIT_FAILURE);
	init_shell_struct(shell, envp);
	minishell(shell);
	return (0);
}
