/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:37:11 by cjulienn          #+#    #+#             */
/*   Updated: 2021/12/24 15:55:43 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char **sort_env(t_shell *shell)
{
	char	**std_env;
	char	*tmp;

	std_env = envdup(shell->env, -1, shell);
	if (!std_env)
		return (NULL); // change that
	shell->i = 0;
	while (std_env[shell->i])
	{
		shell->j = shell->i + 1;
		while (std_env[shell->j])
		{
			if (ft_strcmp(std_env[shell->i], std_env[shell->j]) > 0)
			{
				tmp = std_env[shell->i];
				std_env[shell->i] = std_env[shell->j];
				std_env[shell->j] = tmp;
			}
			shell->j++;
		}
		shell->i++;
	}
	return (std_env);
}

static void print_env(t_shell *shell, char **env)
{
	int		equ_sign;
	char	*var;

	shell->i = 0;
	shell->j = 0;
	equ_sign = 0;
	while (env[shell->i])
	{
		printf("%s", "declare -x ");
		while (env[shell->i][shell->j])
		{
			if (env[shell->i][shell->j] != '=' || equ_sign > 0)
				printf("%c", env[shell->i][shell->j]);
			else
			{
				printf("%s", "=\"");
				equ_sign++;
			}
			shell->j++;
		}
		shell->j = 0;
		printf("%c\n", '"');
		shell->i++;
	}
}

static int	check_var_val(char *arg)
{
	int		res;

	// TODO
}

int built_in_export(t_shell *shell, char **args)
{
	char	**sorted_env;
	
	shell->i = 1;
	if (!args[1])
	{
		sorted_env = sort_env(shell);
		if (!sorted_env)
			return (1); // change that
		print_env(shell, sorted_env);
		free(sorted_env);
		return (0);
	}
	while (args && args[shell->i])
	{
		if (check_var_val(args[shell->i]))
		{
			// error message
			return (1);
		}
		add_env_var(shell, args[shell->i]);
		shell->i++;
	}
	return (0);
}
