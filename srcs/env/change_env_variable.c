/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 21:39:46 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/10 18:06:12 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// utility to change an env variable. it parses the variables until it finds
// a match to the given string var then replaces its content with the given
// string new_var.
void	change_env_var(t_shell **shell, char *var, char *new_var)
{
	int		i;
	char	*env_var;

	i = 0;
	while ((*shell)->env[i] != NULL)
	{
		if (strncmp(var, (*shell)->env[i], ft_strlen(var)) == 0)
		{
			free((*shell)->env[i]);
			(*shell)->env[i] = ft_strdup("PWD=");
			(*shell)->env[i] = ft_strjoin((*shell)->env[i], new_var);
			break ;
		}
		i++;
	}
}
