/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manipulatations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:26:38 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/14 21:58:56 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// returns the length (as in how many elements) of a linked list
int	list_length(t_env *head)
{
	t_env	*tmp;
	int		len;

	tmp = head;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

// frees memory allocated to a linked list. Receives a pointer to
// the first element of that list
void	free_list(t_env *head)
{
	t_env	*tmp;

	if (!head)
		return ;
	while (head->next)
	{
		tmp = head->next;
		free(head->data);
		free(head);
		head = tmp;
	}
	free(head->data);
	free(head);
	head = NULL;
}

// finds target element from a string passed in argument. Compares it
// with ft_strncmp for safety and returns a pointer to the element
// that has data that matches it
t_env	*target_node(t_env **head, char *var)
{
	t_env	*tmp;

	tmp = *head;
	if (!tmp)
		return (NULL);
	while (tmp != NULL)
	{
		if ((ft_strncmp(tmp->data, var, ft_strlen(var)) == 0
			&& tmp->data[ft_strlen(var)] == '=')
			|| (ft_strncmp(tmp->data, var, ft_strlen(var)) == 0
			&& tmp->data[ft_strlen(var)] == '\0'))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

// returns a pointer to the last element of a linked list
t_env	*last_node(t_env **head)
{
	t_env	*tmp;

	tmp = *head;
	if (!tmp)
		return (NULL);
	if (!tmp->next)
		return (tmp);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
