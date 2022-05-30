/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:59:29 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/30 16:24:29 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* this function check using access wether the path of
the target fd is valid or not,
display an err msg if path is not valid */

static void	file_opener(t_shell *shell, int type, char *path)
{	
	if (type == REDIR_INPUT)
	{
		if (access(path, F_OK) != 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		}
		shell->fd_in = open(path, O_RDONLY);
	}
	else if (type == REDIR_OUTPUT)
		shell->fd_out = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		shell->fd_out = open(path, O_RDWR | O_CREAT | O_APPEND, 0644);
}

/* operate_redir should take the parsing parameter and perform
a SINGLE redir per call, based on the parameter */

void	operate_redir(t_shell *shell, int type, char *path)
{
	file_opener(shell, type, path);
	if (type == REDIR_INPUT)
	{
		dup2(shell->fd_in, STDIN_FILENO);
		close(shell->fd_in);
	}
	else if (type == REDIR_OUTPUT || type == RO_APPEND)
	{
		dup2(shell->fd_out, STDOUT_FILENO);
		close(shell->fd_out);
	}
}
