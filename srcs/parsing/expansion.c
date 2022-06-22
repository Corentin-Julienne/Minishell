/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:38:14 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/21 20:53:58 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// this function has two roles, which follow one another.
// first one:
// 	it detects the quotes, single and double that it encounters when
// 	parsing the input. it will define if the quotes are valid or not.
// 	in other words, if it is closed or within another set of quotes.
// 	it then applies the expansion of the existing $ variables in the env.
// second one:
// 	once all the applicable expansions are done, it parses a second time
// 	through the input and applies the same principles over the quotes.
// 	but this time it is to decide whether or not they should be removed
// 	from the output.
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
