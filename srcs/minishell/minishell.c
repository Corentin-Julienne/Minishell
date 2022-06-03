/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:58:57 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/03 17:35:26 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* this function prevent segfault during tokenisation process
by assessing if the user input is only composed of whitespace
return 1 if only whitespace, 0 otherwise */

static int	is_spaces_only(char *str)
{
	int		i;
	int		error;

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
		return (1);
	return (0);
}

/* the core of the shell
in an infinite loop, ask for input using readline,
then, if not composed of whitespaces only, add the input to the history,
tokenise the user input, process it, and then free it */

static void	miniloop(t_shell *shell)
{
	t_token		*token;

	add_history(shell->user_input);
	if (is_spaces_only(shell->user_input) == 1)
		return ;
	token = parse_user_input(shell);
	display_every_token(token); // debug func
	free(shell->user_input);
	shell->user_input = NULL;
	process_tokens(token, shell);
	token_clear(&token);
	reset_shell_struct(shell);
}

static int	minishell(t_shell *shell)
{
	while (42)
	{
		shell->user_input = readline("$> ");
		if (!shell->user_input)
			free_case_err(shell, NULL);
		if (ft_strlen(shell->user_input) > 0)
			miniloop(shell);
		if (shell->user_input)
		{
			free(shell->user_input);
			shell->user_input = NULL;
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
