/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:42:59 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/23 17:35:13 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/stat.h>
#include <sys/file.h>

// has 2 roles:
// 	- if there is one or more arguments, it only takes into account
// 		the first argument given. It will use the function (allowed)
// 		stat, that refers to a struct stat to find out if the string
// 		passed as argument is a path to an existing folder or file.
// 		in any of those cases, it will return 126
// 	- if there is no argument given, env will print all the variables
// 		and their value to the stdin. each will be followed by a \n
int	built_in_env(t_shell *shell, char **cmd_args)
{
	t_env			*tmp;
	int				status;
	struct stat		stats;

	if (cmd_args[1])
	{
		status = stat(cmd_args[1], &stats);
		if (S_ISREG(stats.st_mode) || status != 0)
			printf("env: ‘%s’: No such file or directory\n", cmd_args[1]);
		else if (S_ISDIR(stats.st_mode))
			printf("env: ‘%s‘: Permission denied\n", cmd_args[1]);
		return (126);
	}
	tmp = shell->env_list;
	while (tmp != NULL)
	{
		if (ft_strchr(tmp->data, '=') != NULL)
			printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
	return (0);
}
