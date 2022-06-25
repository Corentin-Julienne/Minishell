/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:55:21 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/25 01:24:05 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	deal_with_tilde(char **arg, t_shell *shell, t_env **path)
{
	t_env	*new;
	char	**home;
	int		i;

	(*arg)++;
	if (spot_env_var(shell->env_list, "HOME") != NULL)
	{
		new = ft_create_new_node("/");
		ft_add_at_tail(path, new);
		home = ft_split((find_var_path(shell->env_list, "HOME")), '/');
		i = 0;
		while (home[i])
		{
			new = ft_create_new_node(home[i]);
			ft_add_at_tail(path, new);
			i++;
		}
		free_split(home);
	}
}

void	deal_with_rest(char *pwd, t_env **path)
{
	char	**current;
	t_env	*new;
	int		i;

	i = 0;
	current = ft_split(pwd, '/');
	new = ft_create_new_node("/");
	ft_add_at_tail(path, new);
	while (current[i])
	{
		new = ft_create_new_node(current[i]);
		ft_add_at_tail(path, new);
		i++;
	}
	free_split(current);
}

void	analyse_first_char(t_env **path, char **arg, t_shell *shell, char *pwd)
{
	t_env	*new;

	if ((*arg)[0] == '/')
	{
		new = ft_create_new_node("/");
		ft_add_at_tail(path, new);
	}
	else if ((*arg)[0] == '~')
		deal_with_tilde(arg, shell, path);
	else
		deal_with_rest(pwd, path);
}

char	*glue_path(t_env *path)
{
	char	*final_path;
	t_env	*tmp;

	tmp = path;
	final_path = ft_strdup(tmp->data);
	if (tmp->next != NULL)
	{
		tmp = tmp->next;
		while (tmp->next != NULL)
		{
			final_path = ft_strjoin_and_free(final_path, tmp->data);
			final_path = ft_strjoin_and_free(final_path, "/");
			tmp = tmp->next;
		}
		final_path = ft_strjoin_and_free(final_path, tmp->data);
	}
	return (final_path);
}

char	*bt_cd_parser(char *arg, t_shell *shell, char *pwd)
{
	t_env	*path;
	char	*final_path;

	path = NULL;
	analyse_first_char(&path, &arg, shell, pwd);
	path_list_create(arg, &path);
	reshape_arg(path);
	final_path = glue_path(path);
	if (path)
		free_list(path);
	return (final_path);
}
