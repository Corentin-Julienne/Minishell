/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:36:12 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/09 12:46:14 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// second part of handling the tilde
int	handle_tilde_else(t_shell *shell, char *arg, char *home)
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
		change_env_var(&shell, "PWD=", final_arg);
		printf("%s\n", shell->env[19]);
		free(final_arg);
	}
}

// handles the arguments prefixed by a ~
int	handle_tilde(t_shell *shell, char *arg, char *home)
{
	if (ft_strlen(arg) == 1)
	{
		chdir(home);
		change_env_var(&shell, "PWD=", home);
		printf("%s\n", shell->env[19]);
	}
	else
		handle_tilde_else(shell, arg, home);
	return (0);
}

// handles the arguments prefixed by a -
int	handle_dash(t_shell *shell, char *arg, char *home)
{
	if (ft_strlen(arg) == 1)
	{
		if (shell->old_pwd == NULL)
			printf("bash: cd: OLDPWD not set\n");
		else
		{
			chdir(shell->old_pwd);
			change_env_var(&shell, "PWD=", shell->old_pwd);
			printf("%s\n", shell->env[19]);
		}
	}
	else if (ft_strlen(arg) == 2 && ft_strncmp(arg, "--", 2) == 0)
	{
		chdir(home);
		change_env_var(&shell, "PWD=", home);
		printf("%s\n", shell->env[19]);
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
	char	*new_pwd;

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
			new_pwd = find_pwd();
			change_env_var(&shell, "PWD=", new_pwd);
			printf("%s\n", shell->env[19]);
			free(new_pwd);
		}
	}
	return (success_code);
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
	int			success_code;
	char		*pwd;

	home = getenv("HOME");
	pwd = find_pwd();
	if (!cmd_args[1])
	{
		success_code = chdir(home);
		change_env_var(&shell, "PWD=", home);
		printf("%s\n", shell->env[19]);
		assign_old_pwd(shell, home, success_code, pwd);
	}
	else if (cmd_args[2])
	{
		printf("bash: cd: too many arguments\n");
		return (1);
	}
	else
	{
		success_code = change_directory(shell, cmd_args[1], home);
		assign_old_pwd(shell, cmd_args[1], success_code, pwd);
	}
	return (0);
}
