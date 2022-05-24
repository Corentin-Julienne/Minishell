/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:59:33 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/24 17:41:14 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*goto_relevant_token(t_shell *shell, t_token *token, int iter)
{
	t_token		*gd_token;
	int			i;

	gd_token = token;
	i = 0;
	while (gd_token && i < shell->nb_pipes)
	{
		if (gd_token->type == PIPE)
			i++;
		gd_token = gd_token->next;
	}
	return (gd_token);
}

/* based on parsing result, this function should take care of redirections,
pipes and cmd exec in a relevant way */

void	child_process(t_shell *shell, t_token *token, int iter)
{
	t_token		*redir_token;
	t_token		*cmd_token;

	if (shell->nb_pipes != 0)
		redirect_to_pipe(shell, iter);
	redir_token = goto_relevant_token(shell, token, iter);
	cmd_token = redir_token;
	while (redir_token && redir_token->type != PIPE)
	{
		if (redir_token->type >= 2 && redir_token->type <= 5 // handle when no path provided
			&& redir_token->next);
			operate_redir(shell, redir_token->type, redir_token->next->item);
		redir_token = redir_token->next;
	}
	while (cmd_token && cmd_token->type != PIPE)
	{
		if (cmd_token->type == CMD)
		
		cmd_token = cmd_token->next;
	}
	
}
