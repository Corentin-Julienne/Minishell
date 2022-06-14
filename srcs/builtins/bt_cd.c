/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:36:12 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/13 14:53:08 by xle-boul         ###   ########.fr       */
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
int	handle_dash(t_shell *shell, char *arg, char *home)
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
		success_code = handle_dash(shell, arg, home);
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

// simply the rest of the if/else statements of builtin cd. Norminette issues
void	built_in_cd_next(t_shell *shell, char **cmd_args, int code, char *pwd)
{
	char	*home;

	home = find_pwd_path(shell->env_list, "HOME");
	if (!(ft_strlen(cmd_args[1]) == 1
			&& ft_strncmp(cmd_args[1], "-", 1) == 0))
		cmd_args[1] = expand_double_dot(cmd_args[1], shell->env_list);
	code = change_directory(shell, cmd_args[1], home);
	assign_old_pwd(shell, cmd_args[1], code, pwd);
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
	char		*home;
	char		*pwd;
	int			success_code;

	pwd = ft_strdup(find_pwd_path(shell->env_list, "PWD"));
	home = find_pwd_path(shell->env_list, "HOME");
	if (!cmd_args[1] || ft_strlen(cmd_args[1]) == 2
		&& ft_strncmp(cmd_args[1], "--", 2) == 0
		|| ft_strlen(cmd_args[1]) == 1 && ft_strncmp(cmd_args[1], "~", 1) == 0)
	{
		success_code = chdir(home);
		change_env_var(shell->env_list, "PWD", home);
		printf("%s\n", find_pwd_path(shell->env_list, "PWD"));
		assign_old_pwd(shell, cmd_args[1], success_code, pwd);
	}
	else if (cmd_args[2])
	{
		printf("bash: cd: too many arguments\n");
		return (1);
	}
	else
		built_in_cd_next(shell, cmd_args, success_code, pwd);
	return (0);
}
