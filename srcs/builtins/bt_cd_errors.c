/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 01:35:07 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/25 01:42:51 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	bt_cd_error_handler(int err, char *arg)
{
	if (err == 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	if (err == 1)
		ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
	if (err == 2)
	{
		ft_putstr_fd("bash: cd: ", STDERR_FILENO);
		ft_putchar_fd(arg[0], STDERR_FILENO);
		ft_putchar_fd(arg[1], STDERR_FILENO);
		ft_putendl_fd(": invalid option", STDERR_FILENO);
	}
}
