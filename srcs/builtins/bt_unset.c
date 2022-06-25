/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:20:12 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/25 05:44:13 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	bt_unset_error_handler(int err, char *arg)
{
	if (err == 0)
	{
		ft_putstr_fd("bash: unset: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	}
}

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
		if (var_is_valid(cmd_args[i]) == false)
			bt_unset_error_handler(0, cmd_args[i]);
		else
		{
			if (target_node(&head, cmd_args[i]) != NULL)
			{
				tmp = target_node(&head, cmd_args[i]);
				ft_delete_list_node(&head, tmp);
			}
		}
		i++;
	}
	return (0);
}
