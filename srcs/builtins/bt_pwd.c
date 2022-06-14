/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:37:13 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/13 11:27:21 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// a simple function to find the pwd at the time
char	*find_pwd_path(t_env *head, char *var)
{
	char	*tmp;

	tmp = spot_env_var(head, var);
	while (tmp && *tmp != '=')
		tmp++;
	if (*tmp == '\0')
		return (NULL);
	return (++tmp);
}

// simple function that prints the pwd to the terminal then frees the vairable
int	built_in_pwd(t_shell *shell, char *cmd_args)
{
	if (find_pwd_path(shell->env_list, "PWD") == NULL)
	{
		printf("bash: pwd: PWD not set\n");
		return (1);
	}
	printf("%s\n", find_pwd_path(shell->env_list, "PWD"));
	return (0);
}
