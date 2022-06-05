/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:41:56 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/30 16:19:46 by cjulienn         ###   ########.fr       */
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
