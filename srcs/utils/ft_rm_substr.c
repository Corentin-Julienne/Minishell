/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_substr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:54:44 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/13 16:57:10 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* this func check wether substr is contained within str
return the starting index of the substr if it is the case,
0 otherwise */

static int	is_substr_in_str(const char *str, const char *substr)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (substr && str[i] == substr[0])
		{
			while (substr && substr[j] && str && str[i + j])
			{
				if (substr[j] != str[i + j])
					break ;
				j++;
			}
			if (substr[j] == '\0')
				return (i);
			j = 0;
		}
		i++;
	}
	return (-1);
}

static char	*handle_complex_cases(const char *str, const char *substr,
	int start, size_t len)
{
	char		*first_part;
	char		*last_part;
	char		*new_str;

	first_part = ft_substr(str, 0, start);
	last_part = ft_substr(str, start + len,
			ft_strlen(str) - ft_strlen(substr) - ft_strlen(first_part));
	new_str = ft_strjoin(first_part, last_part);
	if (first_part)
	{
		free(first_part);
		first_part = NULL;
	}
	if (last_part)
	{
		free(last_part);
		last_part = NULL;
	}
	return (new_str);
}

/* ft_rm_substr withdraw a substring substr to the string str
if substr is not present in str, it return 0 and *new_str is set to NULL
in case there is a malloc err, the rtn code is -1 and
*new_str is also set to NULL
when substr is present in str, rtn code is 0 and
*new_str is the result (using malloc) of the substraction of substr :
e.g if str = "this is an example" and substr = " example",
set *new_str would be equal to "this is an"*/

int	ft_rm_substr(const char *str, const char *substr, char **new_str)
{
	int				start;
	size_t			len;

	start = is_substr_in_str(str, substr);
	if (start == -1)
		return (0);
	len = ft_strlen(substr);
	if (start == 0)
		*new_str = ft_substr(str, len, ft_strlen(str) - len);
	else if (ft_strlen(substr) == (start + ft_strlen(substr)))
		*new_str = ft_substr(str, 0, ft_strlen(str) - ft_strlen(substr));
	else
		*new_str = handle_complex_cases(str, substr, start, len);
	if (*new_str)
		return (1);
	else
		return (-1);
}
