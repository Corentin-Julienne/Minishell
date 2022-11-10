/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 21:37:46 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/14 14:17:50 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* returns the amount of characters a string contains (careful, starts at 0) */

size_t	ft_strlen_export(const char *s)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		if (*s == '=')
			break ;
		i++;
		s++;
	}
	return (i);
}
