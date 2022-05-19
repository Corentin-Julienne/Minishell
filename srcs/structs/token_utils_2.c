/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:09:29 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/25 16:18:39 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	token_delone(t_token **token)
{
	t_token			*tmp;
	t_token			*tmp_2;

	tmp = *token;
	tmp_2 = *token;
	if (*token && (*token)->prev)
	{
		tmp = (*token)->prev;
		tmp->next = NULL;
	}
	if (*token && (*token)->next)
	{
		tmp_2 = (*token)->next;
		tmp_2->prev = NULL;
	}
	if (*token)
	{
		free(*token);
		*token = NULL;
	}
}

void	token_clear(t_token **token)
{
	t_token			*tmp;
	
	while (*token)
	{
		tmp = (*token)->next;
		token_delone(token);
		*token = tmp;
	}
}

void	token_add_front(t_token **token, t_token *new)
{	
	if (token && new)
	{
		new->next = *token;
		(*token)->prev = new;
		*token = new;
	}
}

void	token_add_back(t_token **token, t_token *new)
{
	t_token			*last_elem;

	if (!*token)
	{
		*token = new;
		return ;
	}
	if (token && new)
	{
		last_elem = token_last(*token);
		last_elem->next = new;
		new->prev = last_elem;
	}
}
