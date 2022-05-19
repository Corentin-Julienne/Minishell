/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:37:09 by cjulienn          #+#    #+#             */
/*   Updated: 2021/12/15 16:52:14 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* exit as a shell built-in close the programm with an exit code. exit can take up to 1 argument. 
exit alone close the program with an exit code of 0 (success), but exit with an exit code of 1 if 
there is more than one argument. If the argument is not a valid numeric value, it has an exit code of 128.
if the argument is a number but too great to be an int, the rtn value is 255

It display the str "exit\n", then displaying the error message if appropriate, then exit the program */

static size_t	count_args(char **args)
{
	size_t		args_num;

	args_num = 0;
	while (args && args[args_num])
		args_num++;
	return (args_num);
}

static int	are_args_valid(char **args)
{
	int			args_valid;
	int			i;

	args_valid = 1;
	i = 0;
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
			args_valid = 0;
		i++;	
	}
	return (args_valid);
}

void	built_in_exit(char **args, t_shell *shell)
{
	int			args_valid;
	size_t		args_num;

	args_num = count_args(args);
	if (args_num > 2)
		shell->rtn = 1;
	else if (args_num == 1)
		shell->rtn = 0;
	args_valid = are_args_valid(args);
	if (!args_valid)
		shell->rtn = 128;
	else
		shell->rtn = str_to_exitval(args[1]);
	if (shell->rtn == -1)
		shell->rtn = 255;
	printf("exit\n");
	if (shell->rtn != 0)
		printf("Minishell : %s\n", strerror(errno)); // check this
	exit(shell->rtn);
}
