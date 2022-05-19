/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triple_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:35:46 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/27 17:46:06 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int ft_assemble_parts(char *copy, const char *s2,
	const char *s3, size_t i)
{
	size_t			j;
	size_t			k;

	j = 0;
	j = 0;
	while (s2[j])
	{
		copy[i] = s2[j];
		i++;
		j++;
	}
	while (s3[k])
	{
		copy[i] = s3[k];
		i++;
		k++;
	}
	return (i);
}

char	*ft_triple_join(const char *s1, const char *s2, const char *s3)
{
	char			*copy;
	int				size;
	size_t			i;
	
	if (!s1 || !s2 || !s3)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	copy = (char *)malloc(size * sizeof(char));
	if (!(copy))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	i = ft_assemble_parts(copy, s2, s3, i);
	copy[i] = '\0';
	return (copy);
}
