/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:36:12 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/25 04:39:19 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// second part of the conditions
// it is worth to mention that this function throws the row
// argument into a parser that will handle all the syntaxic
// parameters that CD encounters in minishell
int	built_in_cd_conditions(char **cmd_args, t_shell *shell,
		char **final_path, char *pwd)
{
	int	exit_code;

	exit_code = 0;
	if (!cmd_args[1] || (ft_strlen(cmd_args[1]) == 2
			&& ft_strncmp(cmd_args[1], "--", 2) == 0))
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
		bt_cd_error_handler(3, NULL);
		exit_code = 1;
	}
	return (exit_code);
}

// first part of a long series of conditions that CD has to meet.
int	built_in_cd_conditions_main(char **cmd_args, t_shell *shell,
		char **final_path, char *pwd)
{
	int	exit_code;

	exit_code = 0;
	if (cmd_args[1] && !cmd_args[2] && cmd_args[1][0] == '-' &&
		ft_strlen(cmd_args[1]) == 1)
		exit_code = deal_with_dash(shell, pwd, final_path);
	else if (cmd_args[1] && !cmd_args[2] && cmd_args[1][0] == '-'
			&& cmd_args[1][1] != '-')
	{
		bt_cd_error_handler(2, cmd_args[1]);
		exit_code = 1;
	}
	else if (built_in_cd_conditions(cmd_args, shell, final_path, pwd) != 0)
	{
		exit_code = 1;
	}
	return (exit_code);
}

int	special_case_home(char **cmd_args, char *final_path, t_shell *shell, int go)
{
	int		exit_code;
	t_env	*env;

	env = shell->env_list;
	exit_code = 0;
	if ((!cmd_args[1] && spot_env_var(env, "HOME") != NULL)
		|| (cmd_args[1] && ft_strncmp(cmd_args[1], "--", 2) == 0
			&& ft_strlen(cmd_args[1]) == 2
			&& spot_env_var(env, "HOME") != NULL))
		exit_code = change_dir(final_path, find_var_path(env, "HOME"), go);
	else if ((!cmd_args[1] && spot_env_var(env, "HOME") == NULL)
		|| (cmd_args[1] && ft_strncmp(cmd_args[1], "--", 2) == 0
			&& ft_strlen(cmd_args[1]) == 2
			&& spot_env_var(env, "HOME") == NULL))
	{
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		exit_code = change_dir(final_path, find_var_path(env, "HOME"), go);
	}
	else
		exit_code = change_dir(final_path, cmd_args[1], go);
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
	int			go;

	exit_code = 0;
	final_path = NULL;
	go = 0;
	pwd = define_pwd();
	go = built_in_cd_conditions_main(cmd_args, shell, &final_path, pwd);
	special_case_home(cmd_args, final_path, shell, go);
	assign_old_pwd(shell, cmd_args[1], exit_code, pwd);
	if (final_path)
		free(final_path);
	free(pwd);
	return (exit_code);
}
