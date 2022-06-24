/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:37:13 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/23 16:32:23 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// a simple function to find the pwd at the time
char	*find_pwd_path(t_env *head, char *var)
{
	char	*tmp;

	tmp = spot_env_var(head, var);
	if (tmp == NULL)
		return (NULL);
	while (tmp && *tmp != '=')
		tmp++;
	if (*tmp == '\0')
		return (NULL);
	return (++tmp);
}

// simple function that prints the pwd to the terminal then frees the vairable
int	built_in_pwd(t_shell *shell, char *cmd_args)
{
	char	*pwd;

	(void)shell;
	(void)cmd_args;
	pwd = malloc(sizeof(char) * MAX_PATH);
	pwd = getcwd(pwd, MAX_PATH);
	if (pwd == NULL)
	{
		free(pwd);
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
