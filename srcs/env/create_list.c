/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:48:13 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/11 20:11:34 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_env	*target_node(t_env **head, char *var)
{
	t_env	*tmp;

	tmp = *head;
	if (!tmp)
		return (NULL);
	while (tmp->next)
	{
		if (ft_strncmp((*head)->data, var, ft_strlen(var)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

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
	free(del);
}

// cree un element de la liste chainee avec son numero
// correspondant
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

// place l'element de la liste chainee au bout de la liste
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

// transforme les arguments en une liste chainee
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
