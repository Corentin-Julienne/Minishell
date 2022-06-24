/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 19:55:23 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/23 22:00:59 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_len
{
	size_t	max;
	size_t	min;
	size_t	data;
	size_t	prev;
	size_t	len;
}		t_len;

char	*find_maximum_string(t_env *head)
{
	char	*max;
	t_len	l;

	max = head->data;
	l.max = ft_strlen(max);
	l.data = ft_strlen(head->data);
	if (l.max < l.data)
		l.len = l.data;
	else
		l.len = l.max;
	while (head != NULL)
	{
		if (ft_strncmp(max, head->data, l.len) < 0)
			max = head->data;
		head = head->next;
	}
	return (max);
}

// actual function to compares strings to one another and find the lowest ascii
// score
void	find_minimum_string(t_env *head, int i, char *min, char **env)
{
	t_env	*tmp;
	t_len	l;

	tmp = head;
	while (tmp != NULL)
	{
		l.min = ft_strlen(min);
		l.data = ft_strlen(tmp->data);
		if (i > 0)
			l.prev = ft_strlen(env[i - 1]);
		l.len = l.min;
		if (l.min < l.data)
			l.len = l.data;
		if ((i == 0 && ft_strncmp(tmp->data, min, l.len) < 0))
			min = tmp->data;
		l.len = l.min;
		if (l.min < l.prev)
			l.len = l.prev;
		if (i > 0 && ft_strncmp(tmp->data, min, l.len) < 0
			&& ft_strncmp(env[i - 1], tmp->data, l.len) < 0)
			min = tmp->data;
		tmp = tmp->next;
	}
	env[i] = ft_strdup(min);
}

// iterates through the env to find the lowest (alphabetically) unused
// variable and copies it to the array of strings
char	**sort_env(t_env *head, char **env)
{
	int		i;
	char	*min;

	i = 0;
	while (i < list_length(head))
	{
		min = find_maximum_string(head);
		find_minimum_string(head, i, min, env);
		i++;
	}
	return (env);
}

// to print the env alphabetically, it takes a few steps:
// 	- create a string that is likely to have the highest ascii value
// 		to compare to the actual env variables
// 	- create an array of strings to copy each variable and value into
// 	- compare each element of the linked list to eachother and find
// 		the lowest ascii score one (with ft_strncmp). Once found,
// 		copy it the the first string of the array of strings
// 	- iterate until all the variables are copied
// 	- print each entry to the stdin
// 	- free the array of pointers
void	print_env_export(t_env *head)
{
	char	**sorted_env;
	int		i;

	sorted_env = malloc(sizeof(char *) * (list_length(head)));
	if (!sorted_env)
		return ;
	sorted_env = sort_env(head, sorted_env);
	i = 0;
	while (i < list_length(head))
	{
		print_export(sorted_env[i]);
		free(sorted_env[i]);
		i++;
	}
	free(sorted_env);
}

// has 2 roles:
// 	- if export doesn't get any argument: it will print the env variables
// 		and their value prefixed with "declare -x ". These will be
// 		alphabetically sorted.
// 	- if export gets 1 or more arguments: if the format is x=y, it will
// 		create a variable x of value y into the env.
int	built_in_export(t_shell *shell, char **cmd_args)
{
	int		i;
	int		exit_code;
	t_env	*env;

	i = 1;
	exit_code = 0;
	env = shell->env_list;
	if (!cmd_args[i])
		print_env_export(shell->env_list);
	else
	{
		while (cmd_args[i])
		{
			exit_code += add_env_variable(cmd_args[i], &env);
			i++;
		}
	}
	if (exit_code > 0)
		return (1);
	return (0);
}
