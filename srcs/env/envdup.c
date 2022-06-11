/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:16:09 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/10 18:06:28 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* fulfill the allocated array with env values */

static int	fulfill_env(char **dup_env, char **envp, int pass)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if (i != pass)
			dup_env[j] = ft_strdup(envp[i]);
		else
			j--;
		if (i != pass && !dup_env[j])
		{
			free_problem_str_arr(dup_env, j);
			return (-1);
		}
		i++;
		j++;
	}
	dup_env[j] = NULL;
	return (0);
}

/* envdup is a strdup for the env. However, if pass >= 0, it removes a variable 
(and pass it the index of the variable to remove) */

char	**envdup(char **envp, int pass)
{
	char		**dup_env;
	int			i;

	i = 0;
	while (envp[i])
		i++;
	if (pass == -1)
		dup_env = (char **)malloc(sizeof(char *) * (i + 1));
	else
		dup_env = (char **)malloc(sizeof(char *) * i);
	if (!dup_env)
		return (NULL);
	if (fulfill_env(dup_env, envp, pass) == -1)
		return (NULL);
	return (dup_env);
}
