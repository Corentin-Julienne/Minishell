/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:30:12 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/11 13:46:14 by xle-boul         ###   ########.fr       */
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
	size_t	final_len_arg;
	char	*final_arg;

	final_arg = ft_strdup(home);
	arg++;
	final_arg = ft_strjoin_and_free(final_arg, arg);
	return (final_arg);
}

void	double_dot_convert_to_lists(char **pwd, char **final_arg)
{
	t_env	*arg;
	t_env	*path;
	t_env	*tmp_path;
	t_env	*tmp_arg;
	t_env	*new;

	arg = ft_arg_to_chained_list(final_arg);
	path = ft_arg_to_chained_list(pwd);
	tmp_path = path;
	while (arg != NULL)
	{
		if (ft_strncmp(arg->data, "..", ft_strlen(arg->data)) == 0)
		{
			ft_delete_list_node(&path, last_node(&path));
			arg = arg->next;
		}
		else if (arg->next && ft_strncmp(arg->data, ".", ft_strlen(arg->data)) == 0)
			arg = arg->next;
		else
		{
			new = ft_create_new_node(arg->data);
			ft_add_at_tail(&path, new);
			arg = arg->next;
		}
	}
	while (tmp_path != NULL)
	{
		if (tmp_path != NULL)
		{
			printf("finished_work = %s\n", tmp_path->data);
			tmp_path = tmp_path->next;
		}
	}
}

char	*expand_double_dot(char *arg, t_env *head)
{
	char	**pwd;
	char	**final_arg;

	final_arg = ft_split(arg, '/');
	pwd = ft_split(find_pwd_path(head, "PWD"), '/');
	double_dot_convert_to_lists(pwd, final_arg);
	free_split(pwd);
	free_split(final_arg);
}
