/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:54:30 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/19 16:58:15 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* contains utils to actually have feedback on minishell features
NOT TO INCLUDE IN THE REPO FOR EVAL !!!!! */

/* this func is used to check if the tokenisation process actualluy succeeded */

void	display_every_token(t_token *token)
{
	int			i;

	i = 0;
	while (token)
	{
		printf("token [%i] = [%s]\n", i, token->item);
		token = token->next;
		i++;
	}
}
