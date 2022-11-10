/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:30:12 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/25 03:45:54 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// conditions to figure out if OLDPWD and PWD exist in env
void	old_pwd_conditions(t_shell *shell, char *pwd)
{
	if (spot_env_var(shell->env_list, "PWD") != NULL)
	{
		if (spot_env_var(shell->env_list, "OLDPWD") == NULL)
			create_env_var(shell->env_list, "OLDPWD",
				ft_strchr(spot_env_var(shell->env_list, "PWD"), '=') + 1);
		else if (spot_env_var(shell->env_list, "OLDPWD") != NULL)
			change_env_var(shell->env_list, "OLDPWD",
				ft_strchr(spot_env_var(shell->env_list, "PWD"), '=') + 1);
	}
	else
	{
		if (spot_env_var(shell->env_list, "OLDPWD") == NULL)
			create_env_var(shell->env_list, "OLDPWD", pwd);
		else if (spot_env_var(shell->env_list, "OLDPWD") != NULL)
			change_env_var(shell->env_list, "OLDPWD", pwd);
	}
}

// function to properly assign the path to old_pwd. careful though:
// if its value hasn't been assigned because it is the first cd command,
// its value remains NULL.
// a few key points:
// 	- if OLDPWD didn't exist prior to a cd movement, it is created
// 	- if PWD exists in the env, it will take its value
// 	- if PWD doesn't exist in the env, it'll take getcwd's value
// keep in mind it's a pointer to a malloc'd memory space, thus it has to
// be freed before exiting minishell.
void	assign_old_pwd(t_shell *shell, char *arg, int success_code, char *pwd)
{
	char	*new_pwd;

	if ((arg && arg[0] == '-' && ft_strlen(arg) == 1
			&& spot_env_var(shell->env_list, "OLDPWD") == NULL)
		|| success_code != 0)
		return ;
	old_pwd_conditions(shell, pwd);
	new_pwd = define_pwd();
	if (spot_env_var(shell->env_list, "PWD") != NULL)
		change_env_var(shell->env_list, "PWD", new_pwd);
	free(new_pwd);
}

// simple function that returns the pwd. it is malloc'd
char	*define_pwd(void)
{
	char	*pwd;

	pwd = malloc(sizeof(char) * MAX_PATH);
	if (!pwd)
		return (NULL);
	pwd = getcwd(pwd, MAX_PATH);
	return (pwd);
}

// initiates the creation of a chained list containing each chunck
// (a chunk = any text following a '/')
void	path_list_create(char *arg, t_env **path)
{
	char	**split;
	t_env	*new;
	int		i;

	i = 0;
	split = ft_split(arg, '/');
	while (split[i])
	{
		new = ft_create_new_node(split[i]);
		ft_add_at_tail(path, new);
		i++;
	}
	free_split(split);
}

// handles the path given in argument and treats the ../ and ./ accordingly
