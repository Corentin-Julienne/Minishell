/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:54:12 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/19 21:42:59 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*delete_quotes(char *item, int open, int close)
{
	char	*new_item;
	char	*in_quotes;

	new_item = ft_substr(item, 0, open);
	in_quotes = ft_substr(item, open + 1, close - open - 1);
	item += close + 1;
	new_item = ft_strjoin_and_free(new_item, in_quotes);
	if (*item != '\0')
		new_item = ft_strjoin(new_item, item);
	return (new_item);
}

void	detect_single_quotes(t_token *token, int *i)
{
	int		open;
	int		close;
	char	*new_item;

	if (is_closed('\'', token->item, *i) == true)
	{
		open = *i;
		(*i)++;
		while (token->item[*i] != '\'')
			(*i)++;
		close = *i;
		new_item = delete_quotes(token->item, open, close);
		free(token->item);
		token->item = ft_strdup(new_item);
		free(new_item);
		*i = close - 1;
	}
}

void	detect_double_quotes(t_token *token, int *i)
{
	int		open;
	int		close;
	char	*new_item;

	if (is_closed('"', token->item, *i) == true)
	{
		open = *i;
		(*i)++;
		while (token->item[*i] != '"')
			(*i)++;
		close = *i;
		new_item = delete_quotes(token->item, open, close);
		free(token->item);
		token->item = ft_strdup(new_item);
		free(new_item);
		*i = close - 1;
	}
}

void	detect_quotes_for_deletion(t_token *token)
{
	int			_double;
	int			i;

	_double = 0;
	i = 0;
	while (token->item[i] != '\0')
	{
		if (token->item[i] == '\'' && _double == 0)
			detect_single_quotes(token, &i);
		else if (token->item[i] == '"' && _double == 0)
			detect_double_quotes(token, &i);
		i++;
	}
}
