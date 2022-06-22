/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:36:12 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/21 20:45:29 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


// first part of the if/else statements of builtin cd. Norminette issues
int	built_in_cd_home(t_shell *shell, char **cmd_args, char *pwd, int code)
{
	char	*home;

	home = find_pwd_path(shell->env_list, "HOME");
	if (home == NULL)
	{
		free(pwd);
		return (0);
	}
	code = chdir(home);
	change_env_var(shell->env_list, "PWD", home);
	printf("%s\n", find_pwd_path(shell->env_list, "PWD"));
	assign_old_pwd(shell, cmd_args[1], code, pwd);
	return (0);
}

// simply the rest of the if/else statements of builtin cd. Norminette issues
int	built_in_cd_else(t_shell *shell, char **cmd_args, int code, char *pwd)
{
	char	*home;

	home = find_pwd_path(shell->env_list, "HOME");
	if (!(ft_strlen(cmd_args[1]) == 1
			&& ft_strncmp(cmd_args[1], "-", 1) == 0))
		cmd_args[1] = expand_double_dot(cmd_args[1], shell->env_list);
	code = change_directory(shell, cmd_args[1], home);
	assign_old_pwd(shell, cmd_args[1], code, pwd);
	return (0);
}

// fonction to handle the built in cd
// a few mentions:
	// cd without any argument will drive to home if home is in the env
	// 	will do the same with ~ or --
	// cd with 2 arguments returns an error
	// cd - will drive to the previous pwd. returns an error if it is NULL
	// cd with an argument will drive you to that path unless it is not
	// 	a valid path
int	built_in_cd(t_shell *shell, char **cmd_args)
{
	char		*pwd;
	int			success_code;
	int			exit_code;

	success_code = 0;
	exit_code = 0;
	pwd = ft_strdup(find_pwd_path(shell->env_list, "PWD"));
	if (!cmd_args[1] || (ft_strlen(cmd_args[1]) == 2
			&& ft_strncmp(cmd_args[1], "--", 2) == 0)
		|| (ft_strlen(cmd_args[1]) == 1
			&& ft_strncmp(cmd_args[1], "~", 1) == 0))
		exit_code = built_in_cd_home(shell, cmd_args, pwd, success_code);
	else if (cmd_args[2])
	{
		printf("bash: cd: too many arguments\n");
		exit_code = 1;
	}
	else
		exit_code = built_in_cd_else(shell, cmd_args, success_code, pwd);
	return (exit_code);
}
