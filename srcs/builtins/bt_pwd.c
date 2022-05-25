/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 15:37:13 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/25 13:46:22 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// need to check if PATH_MAX actually enabled in school 19 MacOS

int	built_in_pwd(t_shell *shell, char *cmd_args)
{
	char	*buf;
	char	*cwd;

	buf = (char *)malloc(sizeof(char) * PATH_MAX);
	if (!buf)
		return (-1); // change that
	cwd = getcwd(buf, PATH_MAX);
	if (!cwd)
		return (-1); // change that
	free(buf);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
