/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_change_env_variable.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:39:46 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/25 02:03:45 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Utility to create a new variable in the env and place it
void	create_env_var(t_env *head, char *name, char *value)
{
	t_env	*tmp;
	t_env	*new;

	tmp = head;
	printf("value = %s\n", value);
	while (tmp->next)
	{
		if (spot_env_var(head, name) != NULL)
			return ;
		tmp = tmp->next;
	}
	new = ft_create_new_node(name);
	new->data = ft_strjoin_and_free(new->data, "=");
	if (value != NULL)
		new->data = ft_strjoin_and_free(new->data, value);
	ft_add_at_tail(&head, new);
}

// utility to check if a variable exists within the env
// returns the string if it does and NULL if not
char	*spot_env_var(t_env *head, char *var)
{
	t_env	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		if (ft_strncmp(var, tmp->data, ft_strlen(var)) == 0)
			return (tmp->data);
		tmp = tmp->next;
	}
	return (NULL);
}

// utility to change an env variable. it parses the variables until it finds
// a match to the given string var then replaces its content with the given
// string new_var.
void	change_env_var(t_env *head, char *name, char *value)
{
	t_env	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		if (ft_strncmp(name, tmp->data, ft_strlen(name)) == 0)
		{
			free(tmp->data);
			tmp->data = ft_strdup(name);
			tmp->data = ft_strjoin_and_free(tmp->data, "=");
			if (value != NULL)
				tmp->data = ft_strjoin_and_free(tmp->data, value);
			break ;
		}
		tmp = tmp->next;
	}
}
