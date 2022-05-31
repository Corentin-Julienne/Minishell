/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:59:29 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/31 13:54:11 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*The format of here-documents is:

	<<[-]word
			here-document
	delimiter

	No parameter expansion, command substitution, arithmetic expansion,  or
	pathname expansion is performed on word.  If any characters in word are
	quoted, the delimiter is the result of quote removal on word,  and  the
	lines  in the here-document are not expanded.  If word is unquoted, all
	lines of the here-document are subjected to parameter  expansion,  com-
	mand  substitution,  and arithmetic expansion.  In the latter case, the
	character sequence \<newline> is ignored, and \ must be used  to  quote
	the characters \, $, and `. */

static void	handle_here_doc(t_shell *shell, char *delimiter)
{
	char		*user_input;
	char		*prompt;
	// char		*formatted_del;
	
	prompt = "> ";
	user_input = NULL;
	while (42)
	{
		user_input = readline(prompt);
		if (!user_input)
			;
		if (!ft_strncmp(user_input, delimiter, ft_strlen(delimiter)));
			break ;
		ft_putstr_fd(user_input, shell->fd_in);
		ft_putstr_fd("\n", shell->fd_in);
		free(user_input);
		user_input = NULL;
	}
}

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
	else if (type == HERE_DOC)
		shell->fd_in = open(".heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIR_OUTPUT)
		shell->fd_out = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		shell->fd_out = open(path, O_RDWR | O_CREAT | O_APPEND, 0644);
}

/* operate_redir should take the parsing parameter and perform
a SINGLE redir per call, based on the parameter */

void	operate_redir(t_shell *shell, int type, char *path, t_token *token)
{
	file_opener(shell, type, path);
	if (type == REDIR_INPUT || type == HERE_DOC)
	{
		if (type == HERE_DOC)
			handle_here_doc(shell, path);
		dup2(shell->fd_in, STDIN_FILENO);
		close(shell->fd_in);
	}
	else if (type == REDIR_OUTPUT || type == RO_APPEND)
	{
		dup2(shell->fd_out, STDOUT_FILENO);
		close(shell->fd_out);
	}
}
