/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:43:12 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/25 05:49:13 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	bt_export_error_handler(int err, char *arg)
{
	if (err == 0)
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	}
}

bool	var_is_valid(char *arg)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	if (ft_isalpha(arg[i]) == 0)
		return (false);
	while (arg[i] != '\0')
	{
		if (arg[i] == '=')
			trigger = 1;
		if ((arg[i] == '@' || arg[i] == '!' || arg[i] == '"'
				|| arg[i] == '\\' || arg[i] == '\'' || arg[i] == ' ')
			&& trigger == 0)
			return (false);
		i++;
	}
	return (true);
}

int	add_env_variable(char *arg, t_env **env)
{
	t_env	*new;
	t_env	*tmp;

	tmp = *env;
	while (tmp != NULL)
	{
		if (var_is_valid(arg) == false)
		{
			bt_export_error_handler(0, arg);
			return (1);
		}
		if (ft_strncmp(arg, tmp->data, ft_strlen_export(arg)) == 0
			&& ft_strlen_export(tmp->data) == ft_strlen_export(arg))
		{
			ft_delete_list_node(env, tmp);
			break ;
		}
		tmp = tmp->next;
	}
	new = ft_create_new_node(arg);
	ft_add_at_tail(env, new);
	return (0);
}

// prints every entry with the value between quotes ("")
void	print_export(char *env_export)
{
	int	i;

	i = 0;
	write(1, "declare -x ", 12);
	while (env_export[i] != '\0')
	{
		write (1, &env_export[i], 1);
		if (env_export[i] == '=')
			write(1, "\"", 1);
		i++;
	}
	if (ft_strchr(env_export, '=') != NULL)
		write(1, "\"", 1);
	write(1, "\n", 1);
}
