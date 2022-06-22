/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:59:29 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/22 22:18:35 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// reads the temporary file create .heredoc_tmp and prints its content to the
// stdout. uses get_next_line to do so
void	print_heredoc(char *delimiter)
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
	if (delimiter != NULL)
	{
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) != 0)
			printf("%s\n", line);
	}
	free(line);
	close(fd);
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
static void	handle_here_doc(t_shell *shell, char *delimiter, t_token *token)
{
	char		*user_input;
	char		*prompt;

	prompt = "heredoc> ";
	if (token->next != NULL && ft_strncmp(token->next->item, "|", 1) == 0)
		prompt = "pipe heredoc> ";
	user_input = NULL;
	while (42)
	{
		user_input = readline(prompt);
		if (!user_input)
		{
			printf("\n");
			print_heredoc(NULL);
			break ;
		}
		if (!ft_strncmp(user_input, delimiter, ft_strlen(delimiter))
			&& user_input[ft_strlen(delimiter)] == '\0')
			break ;
		ft_putstr_fd(user_input, shell->fd_in);
		ft_putstr_fd("\n", shell->fd_in);
		free(user_input);
		user_input = NULL;
	}
	print_heredoc(delimiter);
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

/* when an input redir fail cause of a file is not actually existing,
we want to stop the process to run (not execute other cmds),
then return 1 as an exit code
if within CHILD process, just return exit code of 1
if in PARENT process, we want to go back to another loop of minishell */

static void	handle_no_existing_file(t_shell *shell, t_token *token, int process)
{
	if (process == PARENT)
		shell->exit_status = EXIT_FAILURE;
	else
	{
		token_clear(token);
		clean_child_process(shell);
		exit(EXIT_FAILURE);
	}
}

/* operate_redir should take the parsing parameter and perform
a SINGLE redir per call, based on the parameter */

int	operate_redir(t_shell *shell, t_token *redir_tk,
	t_token *token, int process)
{
	int			type;
	char		*path;

	type = redir_tk->type;
	path = redir_tk->next->item;
	file_opener(shell, type, path);
	if (type == REDIR_INPUT || type == HERE_DOC)
	{
		if (type == REDIR_INPUT && shell->fd_in == -1)
		{
			handle_no_existing_file(shell, token, process);
			return (-1);
		}
		if (type == HERE_DOC)
			handle_here_doc(shell, path, token);
		dup2(shell->fd_in, STDIN_FILENO);
		close(shell->fd_in);
	}
	else if (type == REDIR_OUTPUT || type == RO_APPEND)
	{
		dup2(shell->fd_out, STDOUT_FILENO);
		close(shell->fd_out);
	}
	return (0);
}
