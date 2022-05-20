/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:59:33 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/20 20:10:35 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* based on parsing result, this function should take care of redirections,
pipes and cmd exec in a relevant way */

void	child_process(t_shell *shell)
{
	// TO IMPLEMENT
}

/* So, it should be one child process per cmd (including redirs and pipes)
Therefore, this function return an array of pid_t (one for every cmd) */

void	init_pids_arr(t_shell *shell)
{
	pid_t	*pids;

	pids = (pid_t *)malloc(sizeof(pid_t) * shell->nbr_cmds);
	if (!pids)
	{
		ft_putstr_fd("minishell : Unable to allocate memory\n", STDERR_FILENO);
		// add some cleaner here then EXIT_FAILURE
	}
	shell->pids_arr = pids;
}

/* use the waitpid func to wait for evry process to exit
used to return the exit code of the process */

static int	wait_process_and_exit_status(t_shell *shell, int iter)
{
	int		waitpid_status;
	int		rtn_code;

	rtn_code = -1;
	if (waitpid(shell->pids_arr[iter], &waitpid_status, 0) == -1)
	{
		// handle this in a clean way case syscall failure
	}
	if (WIFEXITED(waitpid_status))
		rtn_code = WEXITSTATUS(waitpid_status);
	return (rtn_code);
}

/* the goal of this function is to fork and then exec a child process
where redirs, pipes and cmd exec are done
NO OPERATIONS OF THIS TYPE SHOULD HAPPEN OUTSIDE OF A CHILD PROCESS !!! */

void	spawn_child_process(t_shell *shell, char *cmd, int iter)
{	
	int		rtn_code;
	
	shell->pids_arr[iter] = fork();
	if (shell->pids_arr[iter] == -1)
	{
		// handle this in a clean way
	}
	else if (shell->pids_arr[iter] == 0)
		child_process(shell);
	else
	{
		rtn_code = wait_process_and_exit_status(shell, iter);
		if (rtn_code != -1)
			shell->exit_status = rtn_code;
	}
}
