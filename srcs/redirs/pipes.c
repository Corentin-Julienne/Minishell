/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:59:31 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/27 17:24:58 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* close every useless pipe in a given child process
MEANT TO BE USED IN CHILD PROCESSES ONLY !!!!*/

static void	close_useless_pipes(t_shell *shell, int iter)
{
	int			i;

	i = 0;
	while (iter == 0 && i < shell->nb_pipes)
	{
		if (i != 1)
			close(shell->pipes[i]);
		i++;
	}
	while (iter > 0 && i < (shell->nb_pipes * 2))
	{
		if (i != ((iter * 2) - 2) && i != ((iter * 2) + 1))
			close(shell->pipes[i]);
		i++;
	}
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
		dprintf(2, "pipe arr malloc failed\n");
	}
	i = 0;
	while (i < num_pipes)
	{
		if (pipe(shell->pipes + (2 * i)) == -1)
		{
			dprintf(2, "a pipe activation failed\n");
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
		if (close(shell->pipes[i]) == -1)
			dprintf(2, "pipe closing problem [close_all_pipes]\n");
		i++;
	}
}

/* redirect to pipe close all useless pipes, then 
dup2 the stdin, stdout or both , then close the used pipes */

void	redirect_to_pipe(t_shell *shell, int iter)
{
	close_useless_pipes(shell, iter);
	if (iter == shell->nb_pipes) // check that
	{
		if (dup2(shell->pipes[(iter * 2) - 2], STDIN_FILENO) == -1)
			ft_putstr_fd("redir to STDIN failed\n", 2); // handle correctly
		if (close(shell->pipes[(iter * 2) - 2]) == -1)
			dprintf(2, "pipe closing problem [close_useless_pipes]\n");
	}
	else if (iter == 0)
	{
		if (dup2(shell->pipes[1], STDOUT_FILENO) == -1)
			ft_putstr_fd("redir to STDOUT failed\n", 2); // handle correctly
		if (close(shell->pipes[1]) == -1)
			dprintf(2, "pipe closing problem [close_useless_pipes]\n");
	}
	else
	{
		if (dup2(shell->pipes[(iter * 2) - 2], STDIN_FILENO) == -1)
			ft_putstr_fd("intermediate STDIN pipe redir failed\n", 2); // handle correctly
		if (close(shell->pipes[(iter * 2) - 2]) == -1)
			dprintf(2, "pipe closing problem [close_useless_pipes]\n");
		if (dup2(shell->pipes[(iter * 2) + 1], STDOUT_FILENO) == -1)
			ft_putstr_fd("intermediate STDOUT pipe redir failed\n", 2); // handle correctly
		if (close(shell->pipes[(iter * 2) + 1]) == -1)
			dprintf(2, "pipe closing problem [close_useless_pipes]\n");
	}
}
