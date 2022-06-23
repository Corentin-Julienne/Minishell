/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:59:00 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/21 20:26:06 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* refresh the shell values between two user inputs */

void	reset_shell_struct(t_shell *shell)
{
	shell->i = 0;
	shell->item_length = 0;
	shell->fd_in = -1;
	shell->fd_out = -1;
	shell->nb_seq = -1;
	shell->seq_used = -1;
	shell->nb_pipes = -1;
	if (shell->pids_arr)
	{
		free(shell->pids_arr);
		shell->pids_arr = NULL;
	}
	if (shell->pipes)
	{
		free(shell->pipes);
		shell->pipes = NULL;
	}
	if (access(".heredoc_tmp", F_OK) == 0)
		unlink(".heredoc_tmp");
}

/* fulfill shell struct, exit on failure
put the return value to 0
malloc a copy of envp (to facilitate further modification) */

void	init_shell_struct(t_shell *shell, char **envp)
{
	shell->i = 0;
	shell->item_length = 0;
	shell->exit_status = 0;
	shell->env = envdup(envp, -1);
	shell->env_list = ft_arg_to_chained_list(envp);
	shell->paths = NULL;
	shell->user_input = NULL;
	shell->fd_in = -1;
	shell->fd_out = -1;
	shell->std_fdin = dup(STDIN_FILENO);
	shell->std_fdout = dup(STDOUT_FILENO);
	shell->nb_seq = -1;
	shell->seq_used = -1;
	shell->nb_pipes = -1;
	shell->pipes = NULL;
	shell->pids_arr = NULL;
}
