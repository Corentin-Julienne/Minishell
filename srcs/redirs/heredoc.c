/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 10:31:20 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/23 11:00:28 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// reads the temporary file create .heredoc_tmp and prints its content to the
// stdout. uses get_next_line to do so
void	print_heredoc(void)
{
	char	*line;
	int		fd;

	fd = open(".heredoc_tmp", O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return ;
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

void	heredoc_loop(t_shell *shell, char *delimiter,
	char *user_input, char *prompt)
{
	while (19)
	{
		user_input = readline(prompt);
		if (!user_input)
		{
			printf("^D\n");
			break ;
		}
		if (!ft_strncmp(user_input, delimiter, ft_strlen(delimiter))
			&& user_input[ft_strlen(delimiter)] == '\0')
		{
			free(user_input);
			print_heredoc();
			break ;
		}
		ft_putstr_fd(user_input, shell->fd_in);
		ft_putstr_fd("\n", shell->fd_in);
		free(user_input);
		user_input = NULL;
	}
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
void	handle_here_doc(t_shell *shell, char *delimiter, t_token *token)
{
	char		*user_input;
	char		*prompt;

	prompt = "heredoc> ";
	if (token->next != NULL && ft_strncmp(token->next->item, "|", 1) == 0)
		prompt = "pipe heredoc> ";
	user_input = NULL;
	heredoc_loop(shell, delimiter, user_input, prompt);
}
