/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 19:55:23 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/15 14:46:34 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// actual function to compares strings to one another and find the lowest ascii
// score
void	find_minimum_string(t_env *head, int i, char *min, char **env)
{
	t_env	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		if (i == 0 && ft_strncmp(tmp->data, min, ft_strlen(tmp->data)) < 0)
			min = tmp->data;
		else if (i > 0 && ft_strncmp(tmp->data, min,
				ft_strlen(tmp->data)) < 0
			&& ft_strncmp(env[i - 1], tmp->data,
				ft_strlen(env[i - 1])) < 0)
			min = tmp->data;
		tmp = tmp->next;
	}
	env[i] = ft_strdup(min);
}

// iterates through the env to find the lowest (alphabetically) unused
// variable and copies it to the array of strings
char	**sort_env(t_env *head, char *highest, char **env)
{
	int		i;
	char	*min;

	i = 0;
	while (i < list_length(head))
	{
		min = highest;
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
	sorted_env = sort_env(head, "~", sorted_env);
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

	i = 1;
	exit_code = 0;
	if (!cmd_args[i])
		print_env_export(shell->env_list);
	else
	{
		while (cmd_args[i])
		{
			exit_code += add_env_variable(cmd_args[i], shell->env_list);
			i++;
		}
	}
	if (exit_code > 0)
		return (1);
	return (0);
}
