/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:51:38 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/30 21:28:03 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* return 1 if quote is valid (i.e. is NOT unclosed),
and 0 otherwise */

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
	if (ft_strlen(&str[i]) >= 2 && str[i + 1] == sep)
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
