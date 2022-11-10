/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:09:29 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/22 11:33:25 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	token_clear(t_token *head)
{
	t_token	*tmp;

	if (!head)
		return ;
	while (head->next)
	{
		tmp = head->next;
		free(head->item);
		free(head);
		head = tmp;
	}
	free(head->item);
	free(head);
	head = NULL;
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
