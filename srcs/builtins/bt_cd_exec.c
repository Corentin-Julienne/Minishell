/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:45:06 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/21 20:45:32 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// handles the arguments prefixed by a ~
int	handle_tilde(t_shell *shell, char *arg, char *home)
{
	char	*final_arg;
	int		success_code;

	final_arg = expand_tilde(home, arg);
	success_code = chdir(final_arg);
	if (success_code != 0)
	{
		printf("bash: cd: %s: No such file or directory\n", final_arg);
		free(final_arg);
		return (1);
	}
	else
	{
		change_env_var(shell->env_list, "PWD", final_arg);
		printf("%s\n", find_pwd_path(shell->env_list, "PWD"));
		free(final_arg);
	}
	return (0);
}

// handles the arguments prefixed by a -
int	handle_dash(t_shell *shell, char *arg)
{
	if (ft_strlen(arg) == 1)
	{
		if (spot_env_var(shell->env_list, "OLDPWD") == NULL)
			printf("bash: cd: OLDPWD not set\n");
		else
		{
			chdir(find_pwd_path(shell->env_list, "OLDPWD"));
			change_env_var(shell->env_list, "PWD",
				find_pwd_path(shell->env_list, "OLDPWD"));
			printf("%s\n", find_pwd_path(shell->env_list, "PWD"));
		}
	}
	else
	{
		printf("bash: cd: %c%c: invalid option\n", arg[0], arg[1]);
		return (1);
	}
	return (0);
}

// executes the change of directory according to the constraints
int	change_directory(t_shell *shell, char *arg, char *home)
{
	int		success_code;

	if (arg[0] == '-')
		success_code = handle_dash(shell, arg);
	else if (arg[0] == '~')
		success_code = handle_tilde(shell, arg, home);
	else
	{
		success_code = chdir(arg);
		if (success_code != 0)
			printf("bash: cd: %s: No such file or directory\n", arg);
		else
		{
			change_env_var(shell->env_list, "PWD", arg);
			printf("%s\n", find_pwd_path(shell->env_list, "PWD"));
		}
	}
	return (success_code);
}
