/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:58:37 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/31 13:40:22 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* use the waitpid func to wait for every process to exit
used to return the exit code of the process */

static int	wait_process_and_exit_status(t_shell *shell, t_token *token, int iter)
{
	int		waitpid_status;
	int		rtn_code;

	rtn_code = -1;
	if (waitpid(shell->pids_arr[iter], &waitpid_status, 0) == -1)
	{
		ft_putstr_fd("minishell : Waitpid syscall failure\n", STDERR_FILENO);
		free_case_err(shell, token);
	}
	if (WIFEXITED(waitpid_status))
		rtn_code = WEXITSTATUS(waitpid_status);
	return (rtn_code);
}

/* So, it should be one child process per cmd (including redirs and pipes)
Therefore, this function return an array of pid_t (one for every cmd)
not to be used for one builtin cmd without pipes !!!! */

static void	init_pids_arr(t_shell *shell, t_token *token, int nb_cmds)
{
	pid_t	*pids;

	pids = (pid_t *)malloc(sizeof(pid_t) * nb_cmds);
	if (!pids)
	{
		ft_putstr_fd("minishell : Unable to allocate memory\n", STDERR_FILENO);
		free_case_err(shell, token);
	}
	shell->pids_arr = pids;
}

/* the goal of this function is to fork and then exec a child process
where redirs, pipes and cmd exec are done */

static void	spawn_child_process(t_shell *shell, t_token *token, int iter)
{
	shell->pids_arr[iter] = fork();
	if (shell->pids_arr[iter] == -1)
	{
		ft_putstr_fd("minishell : Fork syscall failure\n", STDERR_FILENO);
		free_case_err(shell, token);
	}
	else if (shell->pids_arr[iter] == 0)
		pipes_redirs_cmd(shell, token, iter);
}

/* iterates on token to identificate the number of pipes and return it */

static void	count_pipes_num(t_token *token, t_shell *shell)
{
	shell->nb_pipes = 0;
	while (token)
	{
		if (token->type == PIPE)
			shell->nb_pipes++;
		token = token->next;
	}
}

/* "control tower" wich do the following jobs :
1) count the number of pipes present
2) if no pipes, launch redirection, then trigger exec cmd function
3) if pipes, activates the pipe array, then spawn every child process needed
4) close all pipes in the main process
5) use calls to waitpid to wait children to finish and retrieve exti code */

void	process_tokens(t_token *token, t_shell *shell)
{
	int			rtn_code;
	
	count_pipes_num(token, shell);
	shell->nb_cmds = shell->nb_pipes + 1;
	shell->cmds_used = 0;
	if (shell->nb_pipes == 0)
		pipes_redirs_cmd(shell, token, 0);
	else
	{
		pipes_activation(shell, shell->nb_pipes, token);
		init_pids_arr(shell, token, shell->nb_cmds);
		while (shell->cmds_used < shell->nb_cmds)
		{
			spawn_child_process(shell, token, shell->cmds_used);
			shell->cmds_used++;
		}
		close_all_pipes(shell, shell->nb_pipes);
		shell->i = -1;
		while (++shell->i < shell->nb_cmds)
			rtn_code = wait_process_and_exit_status(shell, token, shell->i);
		if (rtn_code != -1)
			shell->exit_status = rtn_code;
	}
}
