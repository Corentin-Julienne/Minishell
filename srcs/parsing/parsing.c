/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:49:57 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/29 16:37:36 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// /* bash allows CMDS to work regardless of the case
// e.g echo will works but also Echo or eChO */

// static void	*lowercase_cmds(t_token *token)
// {
// 	int			i;

// 	i = 0;
// 	while (token->item[i])
// 	{
// 		if (token->item[i] >= 97 && token->item[i] <= 122)
// 			token->item[i] = token->item[i] - 32;
// 		i++;
// 	}
// }

static void	is_within_quotes(t_token *token)
{
	if (token->item[0] == '\''
		&& token->item[ft_strlen(token->item) - 1] == '\'')
		token->is_quotted = S_QUOTES;
	else if (token->item[0] == '"'
		&& token->item[ft_strlen(token->item) - 1] == '"')
		token->is_quotted = D_QUOTES;
	else
		token->is_quotted = 0;
}

/* find thew type of the token (among | < < >> >>)
check also if the token is entirely surrounded
by simple or double quotes (with is_within_quotes func)
ARG can be flags, commandes, arguments for function or > >> < << */

static void	find_token_type(t_token *token)
{		
	while (token)
	{
		if (!ft_strncmp(token->item, "|", 1)
			&& ft_strlen(token->item) == 1)
			token->type = PIPE;
		else if (!ft_strncmp(token->item, "<<", 2)
			&& ft_strlen(token->item) == 2)
			token->type = HERE_DOC;
		else if (!ft_strncmp(token->item, ">>", 2)
			&& ft_strlen(token->item) == 2)
			token->type = RO_APPEND;
		else if (!ft_strncmp(token->item, "<", 1)
			&& ft_strlen(token->item) == 1)
			token->type = REDIR_INPUT;
		else if (!ft_strncmp(token->item, ">", 1)
			&& ft_strlen(token->item) == 1)
			token->type = REDIR_OUTPUT;
		else
			token->type = ARG;
		is_within_quotes(token);
		token = token->next;
	}
}

/* as asked by the subject, we need to expand the env variables (preceded by $)*/

int	modify_tokens(t_token *token)
{
	int				i;
	char			*expanded_token;

	while (token)
	{
		expand_env_var(token);
		if (remove_quotes(token) == -1)
			; // handle this
		if (token->type == CMD)
			lowercase_cmds(token);
		token = token->next;
	}
	return (0);
}

/* the parse_user_input func is converting the string user_input
into tokens. Tokens are words, quotted expressions separated
by space or | < << >> >, or | < << >> >.
every token is a part of a linked list containing the str,
the type of the token, if it is surrounded by closed quotes or not
*/

t_token	*parse_user_input(t_shell *shell)
{
	t_token		*tokens;
	t_token		*new_elem;
	char		*item;
	int			i;

	tokens = NULL;
	i = 0;
	while (shell->user_input)
	{
		item = isolate_item(shell);
		if (!ft_strlen(item))
		{
			free(item);
			break ;
		}
		new_elem = token_new(item);
		if (!new_elem)
			return (NULL); // change this !!!
		new_elem->shell = shell;
		token_add_back(&tokens, new_elem);
		i++;
	}
	find_token_type(tokens);
	modify_tokens(tokens);
	return (tokens);
}
