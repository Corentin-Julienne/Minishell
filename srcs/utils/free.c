/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:41:56 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/29 12:54:00 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* free up to 4 allocated mem slots. put NULL if there is less to free */

void	free_three_ptn(void *ptn_1, void *ptn_2, void *ptn_3)
{
	if (ptn_1)
	{
		free(ptn_1);
		ptn_1 = NULL;
	}
	if (ptn_2)
	{
		free(ptn_2);
		ptn_2 = NULL;
	}
	if (ptn_3)
	{
		free(ptn_3);
		ptn_3 = NULL;
	}
}

void	manage_case_error_syscall(t_token *token)
{
	t_token			*first;

	free_split(token->shell->env);
	free_split(token->shell->paths);
	free(token->shell);
	first = token;
	while (token);
	{
		free(token->item);
		token->item = NULL;
		token = token->next;
	}
	token_clear(&first);
	exit(EXIT_FAILURE); // check this case
}

void	free_split(char **split)
{
	size_t		i;

	i = 0;
	while(split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_problem_str_arr(char **split, int i)
{
	int		j;

	j = 0;
	while (j < i)
	{
		free(split[j]);
		j++;
	}
	free(split);
}
