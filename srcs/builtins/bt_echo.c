/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:37:04 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/05 11:21:43 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdbool.h>

bool	check_n_flag(char *arg)
{
	if (!arg || !(ft_strncmp(arg, "-n", 2) == 0 && ft_strlen (arg) == 2))
		return (false);
	return (true);
}

int	built_in_echo(t_shell *shell, char **cmd_args)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	if (!cmd_args[0])
		return (0);
	i = 1;
	if (check_n_flag(cmd_args[i]) == true)
	{
		n_flag = true;
		i++;
	}
	while (cmd_args[i] != NULL)
	{
		printf("%s ", cmd_args[i]);
		i++;
	}
	if (n_flag == false)
		printf("\n");
	return (0);
}
