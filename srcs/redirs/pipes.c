/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:59:31 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/20 20:09:22 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* close every useless pipe in a given child process
MEANT TO BE USED IN CHILD PROCESSES ONLY !!!!*/

static void	close_useless_pipes(t_shell *shell, int type, int iter)
{
	int			i;

	i = 0;
	while (i < shell->nb_pipes * 2)
	{
		if (i != ((iter * 2) - 2) && i != ((iter * 2) + 1))
			close(shell->pipes[i]);
		i++;
	}
	if (type == IN_PIPE)
		close(shell->pipes[(iter * 2) + 1]);
	else if (type == OUT_PIPE)
		close(shell->pipes[(iter * 2) - 2]);
}

/* pipes_activation return an array of activated pipes
the size of the array is determined by the num of pipes multiplicated by 2 */

void	pipes_activation(t_shell *shell, int num_pipes)
{
	int		i;

	shell->pipes = (int *)malloc(sizeof(int) * (num_pipes * 2));
	if (!shell->pipes)
	{
		// handle this in a clean way
	}
	i = 0;
	while (i < num_pipes)
	{
		if (pipe(shell->pipes + (2 * i)) == -1)
		{
			// handle this in a clean way
		}
		i++;
	}
}

/* close all pipes. Useful when in parent process */

void	close_all_pipes(t_shell *shell, int num_pipes)
{
	int		i;

	i = 0;
	while (i < (num_pipes * 2))
	{
		close(shell->pipes[i]);
		i++;
	}
}

/* redirect to pipe close all useless pipes, then 
dup2 the stdin, stdout or both , then close the used pipes */

void	redirect_to_pipe(t_shell *shell, int type, int iter)
{
	close_useless_pipes(shell, type, iter);
	if (type == COMBINED)
	{
		if (dup2(shell->pipes[(iter * 2) - 2], STDIN_FILENO) == -1)
			; // handle correctly
		if (dup2(shell->pipes[(iter * 2) + 1], STDOUT_FILENO) == -1)
			; // handle correctly
		close(shell->pipes[(iter * 2) - 2]);
		close(shell->pipes[(iter * 2) + 1]);
	}
	else if (type == IN_PIPE)
	{
		if (dup2(shell->pipes[1], STDOUT_FILENO) == -1)
			; // handle correctly
		close(shell->pipes[1]);
	}
	else
	{
		if (dup2(shell->pipes[(iter * 2) - 2], STDIN_FILENO) == -1)
			; // handle correctly
		close(shell->pipes[(iter * 2) - 2]);
	}
}
