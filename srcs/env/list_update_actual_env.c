/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_update_actual_env.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:19:56 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/14 15:08:26 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**update_env(t_env *head, char **old_env)
{
	int		i;
	t_env	*tmp;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof(char *) * (list_length(head) + 1));
	if (!new_env || !head)
		return (NULL); //a changer pour une sortie gracieuse
	tmp = head;
	while (tmp != NULL)
	{
		new_env[i] = ft_strdup(tmp->data);
		i++;
		tmp = tmp->next;
	}
	new_env[i] = NULL;
	free_split(old_env);
	return (new_env);
}
