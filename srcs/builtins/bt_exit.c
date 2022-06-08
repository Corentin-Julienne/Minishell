/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:47:54 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/07 21:54:38 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	built_in_exit(t_shell *shell, char **cmd_args)
{
	printf("%d\n", shell->exit_status);
	free_case_exit(shell);
	exit(EXIT_SUCCESS);
}