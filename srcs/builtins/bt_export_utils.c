/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:43:12 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/14 14:52:30 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_env_variable(char *arg, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strncmp(arg, tmp->data, ft_strlen_export(arg)) == 0
			&& ft_strlen_export(tmp->data) == ft_strlen_export(arg))
		{
			ft_delete_list_node(&env, tmp);
			break ;
		}
		tmp = tmp->next;
	}
	new = ft_create_new_node(arg);
	ft_add_at_tail(&env, new);
}

// prints every entry with the value between quotes ("")
void	print_export(char *env_export)
{
	int	i;

	i = 0;
	write(1, "declare -x ", 12);
	while (env_export[i] != '\0')
	{
		write (1, &env_export[i], 1);
		if (env_export[i] == '=')
			write(1, "\"", 1);
		i++;
	}
	write(1, "\"\n", 3);
}
