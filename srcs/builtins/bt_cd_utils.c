/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:30:12 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/23 16:09:10 by xle-boul         ###   ########.fr       */
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
	else if (spot_env_var(shell->env_list, "OLDPWD") == NULL)
		create_env_var(shell->env_list, "OLDPWD", pwd);
	else if (spot_env_var(shell->env_list, "OLDPWD") != NULL)
		change_env_var(shell->env_list, "OLDPWD", pwd);
	free(pwd);
}

// replaces the ~ by home path
char	*expand_tilde(char *home, char *arg)
{
	char	*final_arg;

	final_arg = ft_strdup(home);
	arg++;
	final_arg = ft_strjoin_and_free(final_arg, arg);
	return (final_arg);
}

void	double_dot_loop(t_env *arg, t_env *path)
{
	t_env	*new;

	while (arg != NULL)
	{
		if (arg->next && ft_strncmp(arg->data, ".", ft_strlen(arg->data)) == 0)
			arg = arg->next;
		else if (ft_strncmp(arg->data, "..", ft_strlen(arg->data)) == 0)
		{
			ft_delete_list_node(&path, last_node(&path));
			arg = arg->next;
		}
		else
		{
			new = ft_create_new_node(arg->data);
			ft_add_at_tail(&path, new);
			arg = arg->next;
		}
	}
}

// this whole mess has to be normalized. It basically finds out if
// there is a ../ or ./ in the path and converts the path to a format
// that will fit into the variable pwd
char	*double_dot_convert_to_lists(t_env *path, char **final_arg)
{
	t_env	*arg;
	t_env	*tmp_path;
	t_env	*tmp_arg;
	char	*final_pwd;

	arg = ft_arg_to_chained_list(final_arg);
	if (ft_strncmp(arg->data, "~", 1) == 0)
		ft_delete_list_node(&arg, arg);
	tmp_path = path;
	tmp_arg = arg;
	double_dot_loop(arg, path);
	final_pwd = ft_strdup("/");
	path = tmp_path;
	while (tmp_path != NULL)
	{
		final_pwd = ft_strjoin_and_free(final_pwd, tmp_path->data);
		final_pwd = ft_strjoin_and_free(final_pwd, "/");
		tmp_path = tmp_path->next;
	}
	free_list(path);
	free_list(tmp_arg);
	return (final_pwd);
}

// handles the path given in argument and treats the ../ and ./ accordingly
char	*expand_double_dot(char *arg, t_env *head)
{
	char	**pwd;
	t_env	*path;
	char	**final_arg;
	char	*final_pwd;

	final_arg = ft_split(arg, '/');
	if (ft_strncmp(final_arg[0], "~", 1) == 0)
		pwd = ft_split(find_pwd_path(head, "HOME"), '/');
	else if (ft_strncmp(arg, "/", 1) == 0)
		pwd = NULL;
	else
		pwd = ft_split(find_pwd_path(head, "PWD"), '/');
	if (pwd != NULL)
		path = ft_arg_to_chained_list(pwd);
	else
		path = ft_create_new_node("/");
	final_pwd = double_dot_convert_to_lists(path, final_arg);
	if (pwd != NULL)
		free_split(pwd);
	free_split(final_arg);
	return (final_pwd);
}
