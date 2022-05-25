/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:01:30 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/25 13:41:41 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* execute only in a child process !!!! even the builtins ! */

void	cmd_exec(t_shell *shell, char **cmd_args)
{
	if (!ft_strncmp(cmd_args[0], "cd", 2) && ft_strlen(cmd_args[0]) == 2)
		built_in_cd(shell, cmd_args);
	else if (!ft_strncmp(cmd_args[0], "echo", 4)
		&& ft_strlen(cmd_args[0]) == 4)
		built_in_echo(shell, cmd_args);
	else if (!ft_strncmp(cmd_args[0], "env", 3)
		&& ft_strlen(cmd_args[0]) == 3)
		built_in_env(shell, cmd_args);
	else if (!ft_strncmp(cmd_args[0], "exit", 4)
		&& ft_strlen(cmd_args[0]) == 4)
		built_in_exit(shell, cmd_args);
	else if (!ft_strncmp(cmd_args[0], "export", 6)
		&& ft_strlen(cmd_args[0]) == 6)
		built_in_export(shell, cmd_args);
	else if (!ft_strncmp(cmd_args[0], "pwd", 3)
		&& ft_strlen(cmd_args[0]) == 3)
		built_in_pwd(shell, cmd_args);
	else if (!ft_strncmp(cmd_args[0], "unset", 5)
		&& ft_strlen(cmd_args[0]) == 5)
		built_in_unset(shell, cmd_args);
	else
		path_cmd_exec(shell, cmd_args);
}
