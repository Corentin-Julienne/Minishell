/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:36:12 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/25 01:48:54 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	built_in_cd_conditions(char **cmd_args, t_shell *shell,
		char **final_path, char *pwd)
{
	int	exit_code;

	exit_code = 0;
	if (!cmd_args[1] || (ft_strlen(cmd_args[1]) == 2
			&& ft_strncmp(cmd_args[1], "--", 2) == 0)
		|| (ft_strlen(cmd_args[1]) == 1
			&& ft_strncmp(cmd_args[1], "~", 1) == 0))
	{
		if (spot_env_var(shell->env_list, "HOME") == NULL)
			return (1);
		*final_path = bt_cd_parser(find_var_path(shell->env_list,
					"HOME"), shell, pwd);
	}
	else if (cmd_args[1] && !cmd_args[2])
		*final_path = bt_cd_parser(cmd_args[1], shell, pwd);
	else if (cmd_args[2])
	{
		printf("minishell: cd: too many arguments\n");
		exit_code = 1;
	}
	return (exit_code);
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
	char		*pwd;
	int			exit_code;
	char		*final_path;

	exit_code = 0;
	final_path = NULL;
	pwd = define_pwd();
	// if (!cmd_args[2] && cmd_args[1][0] == '-' && ft_strlen(cmd_args[1]) == 1)
	// 	deal_with_dash(shell, pwd);
	// else if (!cmd_args[2] && cmd_args[1][0] == '-'
	// 		&& cmd_args[1][1] != '-')
	// {
	// 	bt_cd_error_handler(2, cmd_args[1]);
	// 	free(pwd);
	// 	return (1);
	// }
	if (built_in_cd_conditions(cmd_args, shell, &final_path, pwd) != 0)
	{
		free(pwd);
		return (1);
	}
	exit_code = change_directory(final_path, cmd_args[1]);
	assign_old_pwd(shell, cmd_args[1], exit_code, pwd);
	if (final_path)
		free(final_path);
	free(pwd);
	return (exit_code);
}
