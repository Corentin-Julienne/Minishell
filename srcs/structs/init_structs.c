/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:59:00 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/25 17:42:16 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* change the shell values between two user inputs */

void	reset_shell_struct(t_shell *shell)
{
	free(shell->pids_arr);
	shell->pids_arr = NULL;
	shell->nb_pipes = 0;
	shell->cmds_used = 0;
	shell->nbr_cmds = 0;
	shell->fd_in = -1; // change this ?
	shell->fd_out = -1; // change this ?
}

/* fulfill shell struct, exit on failure
put the return value to 0
malloc a copy of envp (to facilitate further modification) */

void	init_shell_struct(t_shell *shell, char **envp)
{
	shell->env = NULL;
	shell->paths = NULL;
	shell->pids_arr = NULL;
	shell->user_input = NULL;
	shell->exit_status = 0;
	shell->env = envdup(envp, -1);
	if (!shell->env)
	{
		free(shell);
		exit(EXIT_FAILURE);
	}
	shell->nb_pipes = 0;
	shell->cmds_used = 0;
	shell->fd_in = -1;
	shell->fd_out = -1;
}
