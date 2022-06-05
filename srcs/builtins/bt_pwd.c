/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:37:13 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/05 01:26:32 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// need to check if PATH_MAX actually enabled in school 19 MacOS

int	built_in_pwd(t_shell *shell, char *cmd_args)
{
	char	*cwd;

	cwd = (char *)malloc(sizeof(char) * MAX_PATH);
	if (!cwd)
		return (-1); // change that
	cwd = getcwd(cwd, MAX_PATH);
	if (!cwd)
		return (-1); // change that
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
