/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:38:14 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/19 21:03:45 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_token(t_token *token, t_shell *shell)
{
	t_token	*tmp;

	tmp = token;
	while (tmp != NULL)
	{
		detect_quotes(tmp, shell);
		tmp = tmp->next;
	}
	tmp = token;
	while (tmp != NULL)
	{
		detect_quotes_for_deletion(tmp);
		tmp = tmp->next;
	}
}
