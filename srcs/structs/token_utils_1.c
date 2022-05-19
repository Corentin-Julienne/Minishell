/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:09:27 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/28 17:07:06 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*token_new(char *item)
{
	t_token		*new;
	
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->item = item;
	new->type = -1;
	new->used = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*token_last(t_token *token)
{
	size_t		size;

	if (!token)
		return (NULL);
	size = token_size(token);
	while (size - 1 > 0)
	{
		token = token->next;
		size--;
	}
	return (token);
}

int	token_size(t_token *token)
{
	size_t		size;
	t_token		*token_2;

	if (!token)
		return (0);
	token_2 = token;
	size = 0;
	while (token_2 != NULL)
	{
		size++;
		token_2 = token_2->next;
	}
	return (size);
}
