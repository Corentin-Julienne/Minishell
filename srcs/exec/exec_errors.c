/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:24:47 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/27 16:23:08 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* this function display a bash-like msg when command is not existing
=> if you write "greep" instead of "grep" for instance */

void	display_cmd_not_found(char **cmd_args, char **paths)
{
	if (ft_strchr(cmd_args[0], '/') || !paths)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_args[0], STDERR_FILENO);
		ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("minishell: Command not found: ", STDERR_FILENO);
		ft_putstr_fd(cmd_args[0], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

/* this function handle the case when access is denied because cmd exist
but the program don't have sufficient rigths to execute the cmd
exit the process with code 126, like bash */

void	handle_access_denied(char *path_with_cmd,
	t_shell *shell, char **cmd_args)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path_with_cmd, STDERR_FILENO);
	ft_putstr_fd(" : Permission denied\n", STDERR_FILENO);
	free_split(cmd_args);
	free(path_with_cmd);
	// put some child cleaner there
	free(shell); // not actually good, should clean everything
	exit(126);
}

/* use the access function to check wether the path reaching the cmd 
1) exists (F_OK flag) 2) has permission to execution (X_OK flag)
return 0 if F and X, 1 otherwise */

int	is_path_functionnal(char *path_with_cmd,
	t_shell *shell, char **cmd_args)
{
	if (access(path_with_cmd, F_OK) == 0)
	{
		if (access(path_with_cmd, X_OK) != 0)
		{
			handle_access_denied(path_with_cmd, shell, cmd_args);
			return (1);
		}
		else
			return (0);
	}
	else
		return (1);
}
