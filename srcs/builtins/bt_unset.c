/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:37:15 by cjulienn          #+#    #+#             */
/*   Updated: 2021/12/15 20:10:57 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	rm_env_var(t_shell *shell, int index)
{
	char		**tmp;

	tmp = envdup(shell->env, index, shell);
	if (!tmp)
		return ; // change that
	free(shell->env);
	shell->env = tmp;
}

static int	find_index(t_shell *shell, char *arg)
{
	size_t		index;
	int			find;

	index = 0;
	find = 0;
	while (shell->env[index])
	{
		if (!strncmp(arg, shell->env[index], ft_strlen(arg)))
		{
			find = 1;
			break;
		}
		index++;
	}
	if (find == 0)
		return (-1);
	return (index);
}

int built_in_unset(t_shell *shell, char **args)
{
	int			index;
	int			i;
	int			rtn;

	rtn = 0;
	i = 1;
	while (args[i])
	{
		index = find_index(shell, args[i]);
		if (index == -1)
			rtn++;
		else
			rm_env_var(shell, index);
		i++;
	}
	return (rtn);	
}
