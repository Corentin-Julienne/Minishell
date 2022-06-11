/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:02:11 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/10 13:22:37 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* this function check if the path is provided by the user
by checking if there is a '/' in the first arg (i.e. the cmd)
return 1 if it is the case, 0 otherwise */

static int	is_path_already_provided(const char *first_arg)
{
	char	*cutted_cmd;

	cutted_cmd = ft_strchr(first_arg, '/');
	if (cutted_cmd && cutted_cmd[0] == '/')
		return (1);
	return (0);
}

/* will check wether the user already wrote the all path (checking the 
presence or abscence of a slash)
if not the case, it will "glue" together the path and the cmd,
then returning it */

static char	*join_cmd_to_path(t_shell *shell, char **cmd_args, int i)
{
	char	*path;

	if (is_path_already_provided(cmd_args[0]) == 1)
		return (cmd_args[0]);
	path = ft_strjoin(shell->paths[i], cmd_args[0]);
	if (!path)
	{
		ft_putstr_fd(MALLOC_ERR_MSG, STDERR_FILENO);
		free_split(cmd_args);
		clean_child_process(shell);
		exit(EXIT_FAILURE);
	}
	return (path);
}

/* in case the cmd is not found (i.e. no path provided,
PATH ENV variable deleted, no "homemade programm"
or not found using the paths), return exit code 127 and clean to avoid leaks */

static void	case_cmd_not_found(t_shell *shell, char **cmd_args)
{
	display_cmd_not_found(cmd_args, shell->paths);
	free_split(cmd_args);
	clean_child_process(shell);
	exit(CMD_NOT_FOUND);
}

/* try to execut a command without the paths, in case the programm
path is specified by the user directly or
is within the current working directory */

static void	try_cmd_without_paths(t_shell *shell, char **cmd_args)
{
	char		*first_arg;

	first_arg = cmd_args[0];
	if (is_path_functionnal(first_arg, shell, cmd_args) == 0)
	{
		dprintf(STDERR_FILENO, "go to execve !\n"); // debug only
		if (execve(first_arg, cmd_args, shell->env) == -1)
			dprintf(STDERR_FILENO, "execve did not run as intended\n"); // debug only
	}
}

/* split the arg str, then recuperating path in PATH cmd
if no path provided, because the env variable path was suppressed,
display a cmd not found bash-like msg and exit with code 127
otherwise, use execve :
It will try to assess every path. When one valid path is found,
will execute execve. Execve will kill the process, resolve leaks and exec cmd
otherwise, if no valid path is found, we clean the child process
and exit with code 127 (AKA cmd not found) */

void	path_cmd_exec(t_shell *shell, char **cmd_args)
{
	char		*path_with_cmd;

	try_cmd_without_paths(shell, cmd_args);
	shell->paths = recup_paths(shell, cmd_args);
	if (!shell->paths)
		case_cmd_not_found(shell, cmd_args);
	shell->i = 0;
	while (shell->paths[shell->i])
	{
		path_with_cmd = join_cmd_to_path(shell, cmd_args, shell->i);
		if (is_path_functionnal(path_with_cmd, shell, cmd_args) == 0)
			execve(path_with_cmd, cmd_args, shell->env);
		free(path_with_cmd);
		path_with_cmd = NULL;
		shell->i++;
	}
	case_cmd_not_found(shell, cmd_args);
}
