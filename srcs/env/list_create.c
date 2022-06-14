/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:48:13 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/14 14:30:59 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// deletes target element of the linked list and reconnects previous
// element with next element, if they exist
// frees the allocated memory of the content and the node itself
void	ft_delete_list_node(t_env **head, t_env *del)
{
	if (!(*head) || !del)
		return ;
	if (*head == del)
		*head = del->next;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
		del->prev->next = del->next;
	free(del->data);
	free(del);
}

// create a new element of a linked list. So far, this element isn't
// pointing to or pointed from a linked list.
t_env	*ft_create_new_node(char *line)
{
	t_env	*node;

	if (!line)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->data = ft_strdup(line);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

// appends the new element at the tail of the linked list pointed to by
// head
void	ft_add_at_tail(t_env **head, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (!(*head))
	{
		*head = new;
		return ;
	}
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

// copies content of the array of strings into a linked list containing
// those strings
t_env	*ft_arg_to_chained_list(char **env)
{
	int		i;
	t_env	*head;
	t_env	*new;

	if (!env)
		return (NULL);
	head = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		new = ft_create_new_node(env[i]);
		ft_add_at_tail(&head, new);
		i++;
	}
	return (head);
}
