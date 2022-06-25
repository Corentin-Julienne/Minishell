/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 10:31:20 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/25 05:23:21 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redirect_heredoc(t_shell *shell)
{
	shell->fd_in = open(".heredoc_tmp", O_RDONLY);
	dup2(shell->fd_in, STDIN_FILENO);
	close(shell->fd_in);
}

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

static char	*obtain_trimmed_ui(t_shell *shell)
{
	char	*cutted_ui;
	char	*user_input;

	write(shell->std_fdout, "> ", ft_strlen("> "));
	user_input = get_next_line(shell->std_fdin);
	if (!user_input)
		return (NULL);
	cutted_ui = ft_substr(user_input, 0, ft_strlen(user_input) - 1);
	if (!cutted_ui)
	{
		free(user_input);
		return (NULL);
	}
	free(user_input);
	return (cutted_ui);
}

void	handle_here_doc(t_shell *shell, char *delimiter)
{
	char		*cutted_ui;

	while (19)
	{
		cutted_ui = obtain_trimmed_ui(shell);
		if (cutted_ui == NULL)
		{
			printf("^D\n");
			break ;
		}
		if (!ft_strncmp(cutted_ui, delimiter, ft_strlen(delimiter))
			&& cutted_ui[ft_strlen(delimiter)] == '\0')
		{
			free(cutted_ui);
			break ;
		}
		ft_putstr_fd(cutted_ui, shell->fd_in);
		ft_putstr_fd("\n", shell->fd_in);
		free(cutted_ui);
		cutted_ui = NULL;
	}
	close(shell->fd_in);
	redirect_heredoc(shell);
}
