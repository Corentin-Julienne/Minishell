/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:01:30 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/10 15:34:33 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* exec built in will execute a given builtin, then return its return code,
to be implemented as an exit code for the last foreground pipeline */

static int	exec_built_in(t_shell *shell, char **cmd_args)
{
	if (!ft_strncmp(cmd_args[0], "cd", 2) && ft_strlen(cmd_args[0]) == 2)
		return (built_in_cd(shell, cmd_args));
	else if (!ft_strncmp(cmd_args[0], "echo", 4)
		&& ft_strlen(cmd_args[0]) == 4)
		return (built_in_echo(shell, cmd_args));
	// else if (!ft_strncmp(cmd_args[0], "env", 3)
	// 	&& ft_strlen(cmd_args[0]) == 3)
	// 	return (built_in_env(shell, cmd_args));
	else if (!ft_strncmp(cmd_args[0], "exit", 4)
		&& ft_strlen(cmd_args[0]) == 4)
		built_in_exit(shell, cmd_args);
	// else if (!ft_strncmp(cmd_args[0], "export", 6)
	// 	&& ft_strlen(cmd_args[0]) == 6)
	// 	return (built_in_export(shell, cmd_args));
	else if (!ft_strncmp(cmd_args[0], "pwd", 3)
		&& ft_strlen(cmd_args[0]) == 3)
		return (built_in_pwd(shell, cmd_args[0]));
	// else if (!ft_strncmp(cmd_args[0], "unset", 5)
	// 	&& ft_strlen(cmd_args[0]) == 5)
	// 	return (built_in_unset(shell, cmd_args));
	return (-1);
}

/* return 0 if cmd is not a builtin, 1 otherwise */

int	is_built_in(const char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 2) && ft_strlen(cmd) == 2)
		return (1);
	else if (!ft_strncmp(cmd, "echo", 4) && ft_strlen(cmd) == 4)
		return (1);	
	else if (!ft_strncmp(cmd, "env", 3) && ft_strlen(cmd) == 3)
		return (1);
	else if (!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4)
		return (1);
	else if (!ft_strncmp(cmd, "export", 6) && ft_strlen(cmd) == 6)
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 3) && ft_strlen(cmd) == 3)
		return (1);
	else if (!ft_strncmp(cmd, "unset", 5) && ft_strlen(cmd) == 5)
		return (1);
	return (0);
}

/* this function check if there is no cmd in the sequence
if this is the case free the cmds_args and return an appropriate exit status
triggered in a CHILD process only
Otherwise, if a cmd is present, return and do nothing */

static void	handle_no_cmd(char **cmd_args, t_shell *shell)
{
	if (cmd_args[0] != NULL)
		return ;
	free_split(cmd_args);
	clean_child_process(shell);
	exit(EXIT_SUCCESS);
}

/* if no pipes, the builtin will be exec on the main process
(process will be equal to PARENT),
otherwise in case there is pipes or a single sequences implying
an external cmd, process will be equal to CHILD (the "else" path)
1) in the PARENT case, we execute the built-in, reboot the fd if there
were changes, then put the exit code to the rtn code of the triggered builtin
2) in the CHILD case, we execute the builtin if the cmd is a builtin,
otherwise we execute the external cmd  
NB : if their is no cmd (aka cmd_args[0] = NULL), then we exit if in child process,
and of course we free everything before */

void	cmd_exec(t_shell *shell, char **cmd_args, t_token *token, int process)
{
	int			exit_code;
	
	exit_code = 0;
	if (process == PARENT) // no leaks killing needed there (parent process)
	{
		shell->exit_status = exec_built_in(shell, cmd_args);
		dup2(shell->std_fdin, STDIN_FILENO);
		dup2(shell->std_fdout, STDOUT_FILENO);
		free_split(cmd_args);
	}
	else
	{
		token_clear(&token);
		handle_no_cmd(cmd_args, shell);
		if (is_built_in(cmd_args[0]) == 1)
		{
			exit_code = exec_built_in(shell, cmd_args);
			free_split(cmd_args);
			clean_child_process(shell);
			exit(exit_code);
		}
		else
			path_cmd_exec(shell, cmd_args);
	}
}
