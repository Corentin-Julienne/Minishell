/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:45:06 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/25 01:46:32 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	deal_with_dash(t_shell *shell, char *arg)
{
	if (spot_env_var(shell->env_list, "OLDPWD") == NULL)
		bt_cd_error_handler(1, arg);
	else if (spot_env_var(shell->env_list, "OLDPWD") != NULL)
	{
		chdir(find_var_path(shell->env_list, "OLDPWD"));
		change_env_var(shell->env_list, "PWD",
			find_var_path(shell->env_list, "OLDPWD"));
		printf("%s\n", find_var_path(shell->env_list, "PWD"));
	}
	else
	{
		bt_cd_error_handler(2, arg);
		return (1);
	}
	return (0);
}

int	change_directory(char *final_path, char *arg)
{
	int	exit_code;

	exit_code = chdir(final_path);
	if (exit_code != 0)
	{
		bt_cd_error_handler(0, arg);
		return (exit_code);
	}
	printf("%s\n", final_path);
	return (exit_code);
}
