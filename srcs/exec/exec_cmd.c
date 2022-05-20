/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:01:30 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/20 13:46:29 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	exec_built_in(char **args, t_shell *shell)
// {
// 	if (!ft_strcmp(args[0], "cd"))
// 		built_in_cd(args, shell);
// 	else if (!ft_strcmp(args[0], "echo"))
// 		built_in_echo(args);
// 	else if (!ft_strcmp(args[0], "env"))
// 		built_in_env(shell);
// 	else if (!ft_strcmp(args[0], "exit"))
// 		built_in_exit(args, shell);
// 	else if (!ft_strcmp(args[0], "export"))
// 		built_in_export(shell, args);
// 	else if (!ft_strcmp(args[0], "pwd"))
// 		built_in_pwd();
// 	else if (!ft_strcmp(args[0], "unset"))
// 		built_in_unset(shell, args);
// }

/*  check if the cmd is a built-in or an external cmd 
return 1 if built-in, 0 otherwise */

static int		is_built_in(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		return (1);
	else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		return (1);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		return (1);
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		return (1);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		return (1);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		return (1);
	return (0);
}

/* execute only in a child process !!!! even the builtins ! */

void	cmd_exec(t_shell *shell, char **cmd_args)
{
	if (is_built_in(cmd_args[0]) == 1)
		builtin_exec(); // to implement
	else
		path_cmd_exec(shell, cmd_args);
}
