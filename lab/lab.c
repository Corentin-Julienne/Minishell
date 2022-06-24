/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:36:11 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/11 17:46:49 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

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
	if (strlen(&str[i]) >= 2 && str[i + 1] == sep)
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


int	main(int argc, char **argv)
{
	size_t		quote_size;

	if (argc != 2)
		return (1);
	quote_size = calc_quote_length(argv[1], 0);
	printf("the str %s have quotes of size %zu\n", argv[1], quote_size);
	return (0);
}
