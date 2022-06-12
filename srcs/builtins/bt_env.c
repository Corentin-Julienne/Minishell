/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:42:59 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/11 19:41:40 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_dir(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
		i++;
	i--;
	printf("i = %d\nletter = %c\n", i, arg[i]); //fonction pour reperer s'il s'agit d'un directory
	return (true);
}

int	built_in_env(t_shell *shell, char **cmd_args)
{
	t_env	*tmp;

	if (cmd_args[1])
	{
		if (is_dir(cmd_args[1]) == 0)
			printf("env: ‘%s‘: Permission denied\n", cmd_args[1]);
		else if (is_dir(cmd_args[1]) != 0)
			printf("env: ‘%s’: No such file or directory\n", cmd_args[1]);
		return (126);
	}
	tmp = shell->env_list;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
	return (0);
}