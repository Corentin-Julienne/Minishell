/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 11:37:22 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/16 16:35:43 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	duplicates a string into a new one, using malloc to assign memory */

char	*ft_strldup(const char *s, size_t n)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	while (i < (int)n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
int main()
{
	char	s[] = "bl";
	char	*str;
	int		i = 0;

	str = ft_strdup((char *)s);
	printf("%d\n%s\n%s\n", strcmp(s, str), s, str);
	while (str[i] != '\0')
	{
		printf("%c &str[i] = %p, &s[i] = %p\n", str[i], &str[i], &s[i]);
		i++;
	}
	return (0);
}
*/
