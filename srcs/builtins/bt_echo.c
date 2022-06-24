/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:37:04 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/23 11:44:52 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdbool.h>

// a little boolean tool to detect if the -n flag is present.
// returns true if it is, false if not
bool	check_n_flag(char *arg)
{
	int	i;

	i = 2;
	if (!arg || !(ft_strncmp(arg, "-n", 2) == 0))
		return (false);
	if (ft_strncmp(arg, "-n", 2) == 0 && ft_strlen(arg) > 2)
	{
		while (arg[i] != '\0')
		{
			if (arg[i] != 'n')
				return (false);
			i++;
		}
	}
	return (true);
}

// prints the content of the string, removing the '\' when encountered
void	print_echo(t_shell *shell, char *line)
{
	int	i;

	i = 0;
	(void)shell;
	while (line[i] != '\0')
	{
		write(1, &line[i], 1);
		i++;
	}
	write(1, " ", 1);
}

// prints the last argument, removing the '\' when encountered
void	print_echo_end(t_shell *shell, char *line)
{
	int	i;

	i = 0;
	(void)shell;
	while (line[i] != '\0')
	{
		write(1, &line[i], 1);
		i++;
	}
}

// simple printing function that will print whatever argument follows
// the command. as is, it is followed by a new line. the flag -n cancels
// that new line.
int	built_in_echo(t_shell *shell, char **cmd_args)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	i = 1;
	if (!cmd_args[i])
	{
		printf("\n");
		return (0);
	}
	while (check_n_flag(cmd_args[i]) == true)
	{
		n_flag = true;
		i++;
	}
	if (!cmd_args[i])
		return (0);
	while (cmd_args[i + 1] != NULL)
		print_echo(shell, cmd_args[i++]);
	print_echo_end(shell, cmd_args[i]);
	if (n_flag == false)
		printf("\n");
	return (0);
}
