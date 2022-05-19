/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:37:04 by cjulienn          #+#    #+#             */
/*   Updated: 2021/12/15 13:07:49 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*store_echo_output(char **args, int n_flag, size_t size)
{
	char	*output;
	int		i;

	if (n_flag == 1)
		i = 2;
	else
		i = 1;
	output = ft_strdup("");
	if (!output)
		return (NULL);
	while (args && args[i])
	{
		output = ft_strjoin_and_free(output, args[i]);
		if (size != (i - n_flag - 1))
			output = ft_strjoin_and_free(output, " ");
		i++;
	}
	return (output);
}

static size_t	echo_num_args(char **args)
{
	size_t	size;

	size = 0;
	while (args && args[size])
		size++;
	size--;
	return (size);
}

static int	is_flag_n(char **args)
{
	int	flag_num;

	if (!args[1])
		return (-1);
	flag_num = 0;
	if (!ft_strncmp(args[1], "-n", ft_strlen(args[1])) 
&& ft_strlen(args[1]) == ft_strlen("-n"))
		flag_num = 1;
	return (flag_num);
}

int	built_in_echo(char **args)
{
	size_t	size;
	int		n_flag;
	char	*output;

	n_flag = is_flag_n(args);
	if (n_flag == -1)
	{
		printf("");
		return (0);
	}
	size = echo_num_args(args) - n_flag;
	output = store_echo_output(args, n_flag, size);
	if (!output)
		return (1);
	if (n_flag == 0)
		printf("%s\n", output);
	else
		printf("%s", output);
	return (0);
}
