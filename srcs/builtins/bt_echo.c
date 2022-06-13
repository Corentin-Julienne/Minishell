/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:37:04 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/12 23:45:07 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdbool.h>

// a little boolean tool to detect if the -n flag is present.
// returns true if it is, false if not
bool	check_n_flag(char *arg)
{
	if (!arg || !(ft_strncmp(arg, "-n", 2) == 0 && ft_strlen (arg) == 2))
		return (false);
	return (true);
}

// prints the content of the string, removing the '\' when encountered
void	print_echo(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '\\')
			write(1, &line[i], 1);
		i++;
	}
	write(1, " ", 1);
}

// prints the last argument, removing the '\' when encountered
void	print_echo_end(char *line)
{
	int	i;
	int	len;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\\' && line[i + 1] != '\0' && line[i + 1] == '\\')
		{
			write (1, "\\", 1);
			i++;
		}
		// inserer ici les cas heredoc:
			// - si un ' ou un " est ouvert mais pas ferme
					// fonction qui retourne le nombre de ' dans les arg
					// fonction qui retourne le nombre de " dans les arg
					// fonction qui regarder si la derniere lettre est \
			// - si le dernier char est \
		else if (line[i] != '\\')
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
	if (check_n_flag(cmd_args[i]) == true)
	{
		n_flag = true;
		i++;
	}
	if (!cmd_args[i])
		return (0);
	while (cmd_args[i + 1] != NULL)
		print_echo(cmd_args[i++]);
	print_echo_end(cmd_args[i]);
	if (n_flag == false)
		printf("\n");
	return (0);
}
