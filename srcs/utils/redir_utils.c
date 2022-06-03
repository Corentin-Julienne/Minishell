/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:10:48 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/03 16:52:32 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* this function check wether the user want to exec
only a builtin without any pipes
this is important to know because it is the only case where
spawning a child process is not required and can indeed make
some buitin execution fail (such as cd) */

int	is_forking_required(t_token *token, t_shell *shell)
{
	if (shell->nb_pipes != 0)
		return (1);
	while (token && token->type != CMD)
		token = token->next;
	if (!token || is_built_in(token->item) == 0)
		return (1);
	return (0);
}

/* syntax errors handler.
works in a bash-like way, throwing an error msg, then 
cleaning the process and putting exit status to 258 */

int	handle_syntax_errors(t_token *pb_token, int process,
	t_shell *shell, t_token *token)
{
	char	*following_token;

	if (!pb_token->next)
		following_token = "newline";
	else
		following_token = pb_token->next->item;
	ft_putstr_fd(SYNT_ERR, STDERR_FILENO);
	ft_putstr_fd(following_token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	if (process == CHILD)
	{
		token_clear(&token);
		clean_child_process(shell); 
		exit(258);
	}
	shell->exit_status = 258;
	return (-1);
}
