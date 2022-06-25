/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:45:06 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/25 03:25:54 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// the specific case of cd - is handled here. it moves back to the
// OLDPWD, if it exists in the env
int	deal_with_dash(t_shell *shell, char *arg, char **final_path)
{
	if (spot_env_var(shell->env_list, "OLDPWD") == NULL)
	{
		bt_cd_error_handler(1, arg);
		return (1);
	}
	else if (spot_env_var(shell->env_list, "OLDPWD") != NULL)
		*final_path = ft_strdup(find_var_path(shell->env_list, "OLDPWD"));
	else
	{
		bt_cd_error_handler(2, arg);
		return (1);
	}
	return (0);
}

// executes the change of directory and returns the status code from
// chdir
int	change_directory(char *final_path, char *arg, int go)
{
	int	exit_code;

	if (go == 0)
	{
		exit_code = chdir(final_path);
		if (exit_code != 0)
		{
			bt_cd_error_handler(0, arg);
			return (exit_code);
		}
		if (!(ft_strncmp(arg, ".", 1) == 0 && ft_strlen(arg) == 1))
			printf("%s\n", final_path);
		return (exit_code);
	}
	return (go);
}
