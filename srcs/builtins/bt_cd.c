/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:37:02 by cjulienn          #+#    #+#             */
/*   Updated: 2021/12/22 16:22:03 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*expand_tilde(char **args, char *home)
{
	char	*part_two;
	char	*path;
	int		type;
	
	if (!args[1] && (!ft_strcmp(args[1], "~") || !ft_strcmp(args[1], "--")))
		return (ft_strjoin(home, "/")); // check if / needed or not
	else if (!ft_strncmp(args[1], "~", 1) || !ft_strncmp(args[1], "--", 2))
	{
		if (!ft_strncmp(args[1], "--", 2))
			type = 2;
		else
			type = 1;
		part_two = ft_substr(args[1], type, ft_strlen(args[1]) - type);
		if (!part_two)
			return (NULL); // change that
		path = ft_strjoin(home, part_two);
		free(part_two);
		if (!path)
			return (NULL); // change that
		return (path);
	}
	else
		return (args[1]);
}

static int update_pwd(t_shell *shell, char *path, char *cwd)
{
	char		*old_pwd;
	char		*new_pwd;

	shell->i = 0;
	old_pwd = ft_strjoin("OLDPWD=", cwd);
	new_pwd = ft_strjoin("PWD=", path);
	if (!old_pwd || !new_pwd)
		return (1); // check that
	if (getenv("OLDPWD") == NULL)
		add_env_var(shell, old_pwd);
	else
	{
		while (!ft_strncmp(shell->env[shell->i], "OLDPWD=", 7))
			shell->i++;
		update_env(shell, cwd, shell->i);
	}
	shell->i = 0;
	while (!ft_strncmp(shell->env[shell->i], "PWD=", 4))
		shell->i++;
	update_env(shell, cwd, shell->i);
	free(old_pwd);
	free(new_pwd);
	return (0);
}

static int	change_dir(char **args, char *path, t_shell *shell)
{
	char	*cwd;
	char	*buf;

	buf = (char *)malloc(sizeof(char) * PATH_MAX);
	if (!buf)
		return (1); // change that
	cwd = getcwd(buf, PATH_MAX);
	free(buf);
	if (chdir(path) != 0)
		return (1);
	if (update_pwd(shell, path, cwd) == 1);
		return (1);
	free(cwd);
	return (0);
}

int	built_in_cd(char **args, t_shell *shell)
{
	char	*home;
	char	*path;
	
	home = getenv("HOME");
	if (args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO); // check that
		return (1);
	}
	else if ((!args[1] || !ft_strncmp(args[1], "--", 2) 
|| !ft_strncmp(args[1], "~", 1)) && home == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (1);
	}
	path = expand_tilde(args, home);
	if (!path)
		return (1); // change that
	return (change_dir(args, path, shell));
}
