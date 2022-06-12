/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 19:55:23 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/12 23:18:53 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// actual function to compares strings to one another and find the lowest ascii
// score
char	*find_minimum_string(t_env *head, int i, char *min, char **env)
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
	t_env	*tmp;
	char	*min;

	tmp = head;
	i = 0;
	while (i < list_length(head))
	{
		tmp = head;
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
	char	*highest;
	int		i;

	highest = ft_strdup("~~~~~~~~~~~~~~~~~~~~~~~~");
	sorted_env = malloc(sizeof(char *) * (list_length(head)));
	if (!sorted_env)
		return ;
	sorted_env = sort_env(head, highest, sorted_env);
	free(highest);
	i = 0;
	while (i < list_length(head))
	{
		printf("declare -x %s\n", sorted_env[i]);
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
int built_in_export(t_shell *shell, char **cmd_args)
{
	char	**args;
	int		i;

	i = 0;
	if (!cmd_args[1])
		print_env_export(shell->env_list);
	else
	{
		while (cmd_args[i])
		{
			args = ft_split(cmd_args[1], '=');
			while (args[i] != NULL)
			{
				printf("%s\n", args[i]);
				i++;
			}
		}
	}
	return (0);
}