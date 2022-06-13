/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:20:12 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/12 13:36:22 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int built_in_unset(t_shell *shell, char **cmd_args)
{
	int		i;
	t_env	*tmp;
	t_env	*head;

	i = 1;
	head = shell->env_list;
	printf("arg = %s\n", cmd_args[i]);
	if (!cmd_args[1])
		return (0);
	while (cmd_args[i] != NULL)
	{
		if (target_node(&head, cmd_args[1]) != NULL)
		{
			tmp = target_node(&head, cmd_args[i]);
			printf("node = %s\n", tmp->data);
			ft_delete_list_node(&head, tmp);
		}
		i++;
	}
	return (0);
}
