/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:36:30 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/03 16:03:17 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* clean the content of a child process. Leaks unfriendly function :) */

void	clean_child_process(t_shell *shell)
{
	if (shell->env)
		free_split(shell->env);
	if (shell->paths)
		free_split(shell->paths);
	close(shell->std_fdin);
	close(shell->std_fdout);
	if (shell->pipes)
	{
		free(shell->pipes);
		shell->pipes = NULL;
	}
	if (shell->pids_arr)
	{
		free(shell->pids_arr);
		shell->pids_arr = NULL;
	}
	free(shell);
}

/* this function avoid leaks and kill the main process when an error occurs */

void	free_case_err(t_shell *shell, t_token *token)
{
	if (shell->env)
		free_split(shell->env);
	if (shell->paths)
		free_split(shell->paths);
	if (shell->user_input)
	{
		free(shell->user_input);
		shell->user_input = NULL;
	}
	if (shell->pipes)
	{
		free(shell->pipes);
		shell->pipes = NULL;
	}
	if (shell->pids_arr)
	{
		free(shell->pids_arr);
		shell->pids_arr = NULL;
	}
	free(shell);
	shell = NULL;
	if (token)
		token_clear(&token);
	exit(EXIT_FAILURE);
}

/* in case of a probleme of alloc during the split,
use that func to free every malloqud str in the array,
then the array itself */

void	free_problem_str_arr(char **split, int i)
{
	int		j;

	j = 0;
	while (j < i)
	{
		free(split[j]);
		split[j] = NULL;
		j++;
	}
	free(split);
	split = NULL;
}

/* free the product of a ft_split. Free every string in the array,
and then the array itself */

void	free_split(char **split)
{
	size_t		i;

	i = 0;
	while(split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}