/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:01:30 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/26 17:01:55 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* used when a redirections are used in the main process
(case no pipe involved and only built_in is lauched) 
avoid 
*/

// static void	reset_fds()
// {
// 	// TO IMPLEMENT
// }

// static void	exec_built_in(t_shell *shell, char **cmd_args)
// {
// 	if (!ft_strncmp(cmd_args[0], "cd", 2) && ft_strlen(cmd_args[0]) == 2)
// 		built_in_cd(shell, cmd_args);
// 	else if (!ft_strncmp(cmd_args[0], "echo", 4)
// 		&& ft_strlen(cmd_args[0]) == 4)
// 		built_in_echo(shell, cmd_args);
// 	else if (!ft_strncmp(cmd_args[0], "env", 3)
// 		&& ft_strlen(cmd_args[0]) == 3)
// 		built_in_env(shell, cmd_args);
// 	else if (!ft_strncmp(cmd_args[0], "exit", 4)
// 		&& ft_strlen(cmd_args[0]) == 4)
// 		built_in_exit(shell, cmd_args);
// 	else if (!ft_strncmp(cmd_args[0], "export", 6)
// 		&& ft_strlen(cmd_args[0]) == 6)
// 		built_in_export(shell, cmd_args);
// 	else if (!ft_strncmp(cmd_args[0], "pwd", 3)
// 		&& ft_strlen(cmd_args[0]) == 3)
// 		built_in_pwd(shell, cmd_args);
// 	else if (!ft_strncmp(cmd_args[0], "unset", 5)
// 		&& ft_strlen(cmd_args[0]) == 5)
// 		built_in_unset(shell, cmd_args);
// }

/* return 0 if cmd is not a builtin, 1 otherwise */

static int	is_built_in(char *cmd)
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

/* add a fork when in the case for a  */

static void	exec_single_cmd(t_shell *shell, char **cmd_args)
{
	pid_t		pid;
	int			rtn_code;
	int			waitpid_status;

	pid = fork();
	if (pid == 1)
	{
		; // handle error
	}
	else if (pid == 0)
		path_cmd_exec(shell, cmd_args);
	else
	{
		rtn_code = -1;
		if (waitpid(pid, &waitpid_status, 0) == -1)
		{
			; // handle this in a clean way case syscall failure
		}
		if (WIFEXITED(waitpid_status))
			rtn_code = WEXITSTATUS(waitpid_status);
		if (rtn_code != -1)
			shell->exit_status = rtn_code;
	}
}

/* if no pipes, the builtin will be exec on the main process, 
and cmd that are not buildin would necessitate an additionnal fork,
because this func will be used in the main process
Otherwise, this func is launched from a child process, so 
built in AND cmd are executed in the child process
THEN, NO NEED TO FORK AGAIN !!!!*/

void	cmd_exec(t_shell *shell, char **cmd_args)
{
	if (is_built_in(cmd_args[0]) == 1)
	{
		// exec_built_in(shell, cmd_args);
		// reset_fds(); // implement that
		return ;
	}
	if (shell->nb_pipes == 0) // fork there
		exec_single_cmd(shell, cmd_args);
	else
		path_cmd_exec(shell, cmd_args);
}
