/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 19:55:23 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/11 22:06:16 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_minimum_string(t_env *head, int i, char *min, char **env)
{
	t_env	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		if (i == 0 && ft_strncmp(tmp->data, min, ft_strlen(tmp->data)) < 0)
			min = tmp->data;
		else if (env[i - 1] && ft_strncmp(tmp->data, min,
					ft_strlen(tmp->data)) < 0
					&& ft_strncmp(env[i - 1], tmp->data,
					ft_strlen(env[i - 1])) < 0)
			min = tmp->data;
		tmp = tmp->next;
	}
	env[i] = ft_strdup(min);
}

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

void	print_env_export(t_env *head)
{
	char	**sorted_env;
	char	*highest;
	int		i;

	highest = ft_strdup("~~~~~~~~~~~~~~~~~~~~~~~~");
	sorted_env = malloc(sizeof(char *) * (list_length(head)));
	if (!sorted_env)
		return ;
	sorted_env[list_length(head)] = NULL;
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

int built_in_export(t_shell *shell, char **cmd_args)
{
	if (!cmd_args[1])
		print_env_export(shell->env_list);
	return (0);
}