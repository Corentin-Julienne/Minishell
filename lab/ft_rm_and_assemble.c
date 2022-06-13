/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_and_assemble.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:29:12 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/13 16:53:38 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*new;
	size_t		i;

	i = 0;
	if (len < ft_strlen(s))
		new = (char *)malloc(sizeof(char) * len + 1);
	else
		new = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!new)
		return (NULL);
	if (start > ft_strlen(s))
	{
		new[i] = '\0';
		return (new);
	}
	while (i <= len - 1 && s[i + start] != '\0' && len > 0)
	{
		new[i] = s[i + start];
		i++;
	}
	new[i] = '\0';
	return (new);
}

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

// char	*ft_rm_substr(const char *str, const char *substr)
// {
// 	int			start;
// 	size_t		len;

// 	start = is_substr_in_str(str, substr);
// 	if (start == -1)
// 		return (NULL);
// 	len = ft_strlen(substr);
// 	if (start == 0)
// 		return (ft_substr(str, len, ft_strlen(str) - len));
// 	else if (ft_strlen(substr) == (start + ft_strlen(substr)))
// 		return (ft_substr(str, 0, ft_strlen(str) - ft_strlen(substr)));
// 	return (handle_complex_cases(str, substr, start, len));
// }

// main de test

int	main(void)
{
	char		*test;
	char		*subtest;
	char		*new_str;
	int			i;
	int			rtn;
	
	printf("tests for ft_rm_substr function\n");
	i = 1;

	// test [unit]
	printf("\n\ntest %i :\n", i);
	i++;
	test = "this is an example";
	subtest = "this is";
	printf("str = [%s]\n", test);
	printf("subtest = [%s]\n", subtest);
	rtn = ft_rm_substr(test, subtest, &new_str);
	printf("result = [%s] || rtn code == %d\n", new_str, rtn);
	free(new_str);
	new_str = NULL;

	// test [unit]
	printf("\n\ntest %i :\n", i);
	i++;
	test = "this is an example";
	subtest = "is an ";
	printf("str = [%s]\n", test);
	printf("subtest = [%s]\n", subtest);
	rtn = ft_rm_substr(test, subtest, &new_str);
	printf("result = [%s] || rtn code == %d\n", new_str, rtn);
	free(new_str);
	new_str = NULL;
	
	// test [unit]
	printf("\n\ntest %i :\n", i);
	i++;
	test = "this is an example";
	subtest = "example";
	printf("str = [%s]\n", test);
	printf("subtest = [%s]\n", subtest);
	rtn = ft_rm_substr(test, subtest, &new_str);
	printf("result = [%s] || rtn code == %d\n", new_str, rtn);
	free(new_str);
	new_str = NULL;

	// test [unit]
	printf("\n\ntest %i :\n", i);
	i++;
	test = "this is an example";
	subtest = "s";
	printf("str = [%s]\n", test);
	printf("subtest = [%s]\n", subtest);
	rtn = ft_rm_substr(test, subtest, &new_str);
	printf("result = [%s] || rtn code == %d\n", new_str, rtn);
	free(new_str);
	new_str = NULL;

	// test [unit]
	printf("\n\ntest %i :\n", i);
	i++;
	test = "this is an example";
	subtest = "t";
	printf("str = [%s]\n", test);
	printf("subtest = [%s]\n", subtest);
	rtn = ft_rm_substr(test, subtest, &new_str);
	printf("result = [%s] || rtn code == %d\n", new_str, rtn);
	free(new_str);
	new_str = NULL;

	// test [unit]
	printf("\n\ntest %i :\n", i);
	i++;
	test = "this is an example";
	subtest = NULL;
	printf("str = [%s]\n", test);
	printf("subtest = [%s]\n", subtest);
	rtn = ft_rm_substr(test, subtest, &new_str);
	printf("result = [%s] || rtn code == %d\n", new_str, rtn);
	free(new_str);
	new_str = NULL;

	// test [unit]
	printf("\n\ntest %i :\n", i);
	i++;
	test = NULL;
	subtest = "this is";
	printf("str = [%s]\n", test);
	printf("subtest = [%s]\n", subtest);
	rtn = ft_rm_substr(test, subtest, &new_str);
	printf("result = [%s] || rtn code == %d\n", new_str, rtn);
	free(new_str);
	new_str = NULL;

	// test [unit]
	printf("\n\ntest %i :\n", i);
	i++;
	test = NULL;
	subtest = NULL;
	printf("str = [%s]\n", test);
	printf("subtest = [%s]\n", subtest);
	rtn = ft_rm_substr(test, subtest, &new_str);
	printf("result = [%s] || rtn code == %d\n", new_str, rtn);
	free(new_str);
	new_str = NULL;

	// test [unit]
	printf("\n\ntest %i :\n", i);
	i++;
	test = "this is an example";
	subtest = "";
	printf("str = [%s]\n", test);
	printf("subtest = [%s]\n", subtest);
	rtn = ft_rm_substr(test, subtest, &new_str);
	printf("result = [%s] || rtn code == %d\n", new_str, rtn);
	free(new_str);
	new_str = NULL;

	// test [unit]
	printf("\n\ntest %i :\n", i);
	i++;
	test = "this is an example";
	subtest = "eruoijsvoiv";
	printf("str = [%s]\n", test);
	printf("subtest = [%s]\n", subtest);
	rtn = ft_rm_substr(test, subtest, &new_str);
	printf("result = [%s] || rtn code == %d\n", new_str, rtn);
	free(new_str);
	new_str = NULL;

	
	printf("end of tests ! hope everything were fine !!! goodbye !\n\n");
	return (0);
}
