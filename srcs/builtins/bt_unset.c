/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:20:12 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/13 11:26:22 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// finds the element of the linked list env that contains (if any does)
// the array of arguments passed. if they are found, they are destroyed
// and freed
int	built_in_unset(t_shell *shell, char **cmd_args)
{
	int		i;
	t_env	*tmp;
	t_env	*head;

	i = 1;
	head = shell->env_list;
	if (!cmd_args[1])
		return (0);
	while (cmd_args[i] != NULL)
	{
		if (target_node(&head, cmd_args[1]) != NULL)
		{
			tmp = target_node(&head, cmd_args[i]);
			ft_delete_list_node(&head, tmp);
		}
		i++;
	}
	return (0);
}
