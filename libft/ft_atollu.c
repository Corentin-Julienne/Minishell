/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atollu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 13:21:38 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/24 11:51:40 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define LL_MAX 9223372036854775807

typedef struct s_atoi
{
	int						i;	
	unsigned long long int	lln;
	char					*str_bis;
}				t_atoi;
/* converts a string to corresponding integer */

static char	*ft_trim_string(const char *str, t_atoi *n)
{
	n->i = 1;
	if (!str)
		return (0);
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\r' || *str == '\f' || *str == ' ')
		str++;
	if (*str == '-')
		n->i = -1;
	if (*str == '+' || *str == '-')
		str++;
	return ((char *)str);
}

unsigned long long int	ft_atollu(const char *str)
{
	t_atoi	n;

	n.lln = 0;
	n.str_bis = ft_trim_string(str, &n);
	if (!n.str_bis)
		return (0);
	while (48 <= *n.str_bis && *n.str_bis <= 57)
	{
		n.lln = n.lln * 10 + (*n.str_bis - 48);
		n.str_bis++;
	}
	return (n.lln);
}

// int main()
// {
// 	char s[] = "-9223372036854775809";
// 	printf("%llu\n", ft_atolli(s));
// 	return 0;
// }
