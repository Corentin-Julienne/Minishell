/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:02:11 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/19 18:44:06 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* will check wether the user already wrote the all path (checking the 
presence or abscence of a slash)
if not the case, it will "glue" together the path and the cmd,
then returning it */

static char	*join_cmd_to_path(t_shell *shell, char **cmd_args, int i)
{
	char	*path;
	char	*cmd_slash;

	cmd_slash = ft_strchr(cmd_args[0], '/');
	if (cmd_slash && cmd_slash[0] == '/')
		return (cmd_args[0]);
	path = ft_strjoin(shell->paths[i], cmd_args[0]);
	if (!path)
	{
		ft_putstr_fd("minishell : Unable to allocate memory\n", STDERR_FILENO);
		free_split(cmd_args);
		// some cleaner for the child process case of malloc error
	}
	return (path);
}

/* will try to assess every path. When one valid path is found,
will execute execve. Execve will kill the process, resolve leaks and exec cmd
otherwise, if no valid path is found, we clean the child process
and exit with code 127 (AKA cmd not found) */

static void	trigger_execve(t_shell *shell, char *path_with_cmd,
	char **cmd_args)
{
	shell->i = 0;
	while (shell->paths[shell->i])
	{
		path_with_cmd = join_cmd_to_path(shell, cmd_args, shell->i);
		if (is_path_functionnal(path_with_cmd, shell, cmd_args) == 0)
			execve(path_with_cmd, cmd_args, shell->env);
		free(path_with_cmd);
		shell->i++;
	}
	display_cmd_not_found(cmd_args, shell->paths);
	free_split(cmd_args);
	exit(127);
}

/* split the arg str, then recuperating path in PATH cmd
if no path provided, because the env variable path was suppressed,
display a cmd not found bash-like msg and exit with code 127
otherwise, use execve in the next function to trigger the cmd execution */

void	cmd_exec(t_shell *shell, char *cmd)
{
	char		**cmd_args;
	char		*path_with_cmd;

	cmd_args = ft_split(cmd, ' '); // change this with parsing ?
	if (!cmd_args)
	{
		// some cleaning tool for child process
		exit(EXIT_FAILURE);
	}
	shell->paths = recup_paths(shell);
	if (!shell->paths)
	{
		display_cmd_not_found(cmd_args, NULL);
		exit(127);
	}
	trigger_execve(shell, path_with_cmd, cmd_args);
}
