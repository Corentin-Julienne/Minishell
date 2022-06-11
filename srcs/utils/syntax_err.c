/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:23:29 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/10 18:16:44 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* syntax errors handler.
works in a bash-like way, throwing an error msg, then 
putting exit status to 258 */

static void	handle_syntax_errors(t_token *pb_token, t_shell *shell)
{
	char	*following_token;

	if (!pb_token->next)
		following_token = "newline";
	else
		following_token = pb_token->next->item;
	ft_putstr_fd(SYNT_ERR_MSG, STDERR_FILENO);
	ft_putstr_fd(following_token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	shell->exit_status = SYNTAX_ERR;
}

/* is_redir_err checks wether there is a redirection metachar (< << >> >)
without actual target (i.e. file)
return 0 if no err, 1 otherwise */

static int	is_redir_err(t_token *check_err)
{
	if (check_err->type < REDIR_INPUT || check_err->type > RO_APPEND)
		return (0);
	if (!check_err->next || (check_err->next
			&& check_err->next->type != REDIR_ARG))
		return (1);
	else
		return (0);
}

/* is_pipe_err checks wether there is a pipe syntax error,
that can be two pipes following each other with nothing between them,
or the last/first token is a pipe */

static int	is_pipe_err(t_token *check_err)
{
	if (check_err->type != PIPE)
		return (0);
	if (!check_err->next || (check_err->next && check_err->next->type == PIPE)
		|| !check_err->prev)
		return (1);
	else
		return (0);
}

/* this function checks if there is a syntax error among token
return 0 if not,
1 otherwise and 1) print error message and 2) put shell->exit status to 258 */

int	is_syntax_err(t_token *token, t_shell *shell)
{
	t_token		*check_err;

	check_err = token;
	while (check_err)
	{
		if (is_redir_err(check_err) == 1 || is_pipe_err(check_err) == 1)
		{
			handle_syntax_errors(check_err, shell);
			return (1);
		}
		check_err = check_err->next;
	}
	return (0);
}
