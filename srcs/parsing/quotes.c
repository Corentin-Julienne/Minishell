/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:51:38 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/29 13:57:28 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* this func is used when the quotted part do not start at index 0 
first if condition refers to the case when the quoted part
is at the end of the string (two strings to join)
else, it refers to the case where the quotted part
is in the middle of the string (three strings to assemble) */

static char *other_cases(t_token *token, char *trm_str,
	int i, size_t quote_length)
{
	char		*new_str;
	char		*part_1;
	char		*part_3;

	part_1 = ft_substr(token->item, 0, i);
	if (i + quote_length == ft_strlen(token->item))
	{
		part_3 = NULL;
		new_str = ft_strjoin(part_1, trm_str);
	}
	else
	{
		part_3 = ft_substr(token->item, i + quote_length,
			ft_strlen(token->item) - i - quote_length);
		new_str = ft_triple_join(part_1, trm_str, part_3);
	}
	free_three_ptn((void *)part_1, (void *)part_3, NULL);
	return (new_str);
}

/* this func is used to discriminate between 3 cases :
- the quotted part is at the beginning of the string (index 0) 
- the quotted part is in the middle of the string (func other_cases)
- the quotted part is at the end of the string (func other_cases)
- the quotted part represent the integrality of the string
*/

static char	*assemble_parts(t_token *token, char *trm_str,
	int i, size_t quote_length)
{
	char		*new_str;
	char		*part_3;

	if (!trm_str)
		return (NULL);
	if (i == 0 && token->type != S_QUOTES && token->type != D_QUOTES)
	{
		part_3 = ft_substr(token->item, ft_strlen(trm_str),
			ft_strlen(token->item) - quote_length);
		new_str = ft_strjoin(trm_str, part_3);
		if (!part_3 || !new_str)
		{
			free_three_ptn((void *)part_3, (void *)new_str, (void *)trm_str);
			return (NULL);
		}
		else
			free(part_3);
	}
	else if (token->type == S_QUOTES || token->type == D_QUOTES)
		return (trm_str);
	else
		new_str = other_cases(token, trm_str, i, quote_length);
	free(trm_str);
	return (new_str);
}

/* this func iterates on a given token->item
when it encounters a closed quote, suppress the quotes in the string */

int	remove_quotes(t_token *token)
{
	char		*trm_str;
	char		*new_str;
	size_t		quote_length;
	int			i;

	i = -1;
	while (token->item[++i])
	{
		if ((token->item[i] == '"' || token->item[i] == '\'') && 
			is_quote_valid(&token->item[i], token->item[i]))
		{
			quote_length = calc_quote_length(token->item, i);
			if (quote_length == 2)
				trm_str = ft_strdup("");
			else
				trm_str = ft_substr(token->item, i + 1, quote_length - 1);
			new_str = assemble_parts(token, trm_str, i, quote_length);
			if (!new_str)
				return (-1); // handle malloc error within func or for trm_str
			free(token->item);
			token->item = new_str;
			i = -1;
		}
	}
	return (0);
}

/* return 1 if quote is valid (i.e. is NOT unclosed),
and 1 otherwise */

int	is_quote_valid(char *item, char sep)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	while (item[i])
	{
		if (item[i] == sep && i != 0)
		{
			res = 1;
			break ;
		}
		i++;
	}
	return (res);
}

/* calc the length of the quote (for tokenisation purpose)
return -1 if unclosed quote,
the length of the quote otherwise
[!!!! include the quotes in the length !!!!]
e.g : "truc" = 6, "" = 2, "y" = 3
*/

size_t	calc_quote_length(char *str, size_t i)
{
	char	sep;
	char	*sub_str;
	size_t	j;

	sep = str[i];
	j = i;
	sub_str = &str[i];
	if (!is_quote_valid(sub_str, sep))
		return (-1);
	if (ft_strlen(&str[i] >= 2) && str[i + 1] == sep)
		return (2);
	while (str[i])
	{
		if (str[i] == sep && i != 0)
		{
			i++;
			break ;
		}
		i++;
	}
	return (i - j);
}
