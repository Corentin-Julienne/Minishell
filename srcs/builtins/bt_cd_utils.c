/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:30:12 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/25 02:04:25 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// function to properly assign the path to old_pwd. careful though:
// if its value hasn't been assigned because it is the first cd command,
// its value remains NULL.
// keep in mind it's a pointer to a malloc'd memory space, thus it has to
// be freed before exiting minishell.
void	assign_old_pwd(t_shell *shell, char *arg, int success_code, char *pwd)
{
	if ((arg && arg[0] == '-' && ft_strlen(arg) == 1
			&& spot_env_var(shell->env_list, "OLDPWD") == NULL)
		|| success_code != 0)
		return ;
	if (spot_env_var(shell->env_list, "PWD") != NULL)
	{
		if (spot_env_var(shell->env_list, "OLDPWD") == NULL)
			create_env_var(shell->env_list, "OLDPWD",
				ft_strchr(spot_env_var(shell->env_list, "PWD"), '='));
		else if (spot_env_var(shell->env_list, "OLDPWD") != NULL)
			change_env_var(shell->env_list, "OLDPWD",
				ft_strchr(spot_env_var(shell->env_list, "PWD"), '='));
	}
	else
	{
		if (spot_env_var(shell->env_list, "OLDPWD") == NULL)
			create_env_var(shell->env_list, "OLDPWD", pwd);
		else if (spot_env_var(shell->env_list, "OLDPWD") != NULL)
			change_env_var(shell->env_list, "OLDPWD", pwd);
	}
	if (spot_env_var(shell->env_list, "PWD") != NULL)
		change_env_var(shell->env_list, "PWD", define_pwd());
}

char	*define_pwd(void)
{
	char	*pwd;

	pwd = malloc(sizeof(char) * MAX_PATH);
	if (!pwd)
		return (NULL);
	pwd = getcwd(pwd, MAX_PATH);
	return (pwd);
}

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
