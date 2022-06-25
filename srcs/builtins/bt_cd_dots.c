/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_dots.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 00:28:31 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/25 03:24:17 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	deal_with_dot(t_env **tmp, t_env *path)
{
	if ((*tmp)->prev != NULL)
	{
		ft_delete_list_node(tmp, *tmp);
		(*tmp) = path;
	}
}

void	deal_with_double_dots(t_env **tmp, t_env *path)
{
	if ((*tmp)->prev != NULL && !(ft_strncmp((*tmp)->prev->data, "/", 1) == 0
			&& ft_strlen((*tmp)->prev->data) == 1))
		ft_delete_list_node(tmp, (*tmp)->prev);
	if (!(ft_strncmp((*tmp)->data, "/", 1) == 0
			&& ft_strlen((*tmp)->data) == 1))
		ft_delete_list_node(tmp, *tmp);
	(*tmp) = path;
}

// handles the . and .. mentioned before
void	reshape_arg(t_env *path)
{
	t_env	*tmp;

	tmp = path;
	while (tmp != NULL)
	{
		if (tmp->data[0] == '.' && ft_strlen(tmp->data) == 1)
			deal_with_dot(&tmp, path);
		else if (ft_strlen(tmp->data) == 2
			&& ft_strncmp(tmp->data, "..", 2) == 0)
			deal_with_double_dots(&tmp, path);
		tmp = tmp->next;
	}
}
