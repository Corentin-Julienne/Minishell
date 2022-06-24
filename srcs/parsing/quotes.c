/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:51:38 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/24 13:48:12 by xle-boul         ###   ########.fr       */
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

int	calc_quote_length(char *str, int i)
{
	char	sep;
	int		j;

	sep = str[i];
	j = i;
	while (str[i])
	{
		if (str[i] == sep && i != j)
		{
			i++;
			break ;
		}
		i++;
	}
	return (i - j);
}
