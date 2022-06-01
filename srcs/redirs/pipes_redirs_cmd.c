/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redirs_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:59:33 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/01 16:57:58 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* calculate the len of the cmd_arr
iterate througth token until the end or when a pipe is encountered
increment length if token type is CMD or ARG */

static size_t	calc_cmd_len(t_token *cmd_token)
{
	size_t		cmd_len;

	cmd_len = 0;
	while (cmd_token && cmd_token->type != PIPE)
	{
		if (cmd_token->type == CMD || cmd_token->type == ARG)
			cmd_len++;
		cmd_token = cmd_token->next;
	}
	return (cmd_len);
}

/* use cacl_cmd_len to calculate the size of the str array,
then malloc it and return the array with the cmd at index 0
and the args at the following indexes, and terminate by NULL */

static char	**rtn_cmd_arr(t_token *cmd_token)
{
	size_t		cmd_len;
	size_t		i;
	char		**cmd_arr;

	cmd_len = calc_cmd_len(cmd_token);
	cmd_arr = (char **)malloc(sizeof(char *) * (cmd_len + 1));
	if (!cmd_arr)
		return (NULL);
	i = 0;
	while (i < cmd_len)
	{
		if(cmd_token->type == CMD || cmd_token->type == ARG)
		{
			cmd_arr[i] = ft_strdup(cmd_token->item);
			if (!cmd_arr[i])
			{
				free_problem_str_arr(cmd_arr, i);
				return (NULL);
			}
			i++;
		}
		cmd_token = cmd_token->next;
	}
	cmd_arr[cmd_len] = NULL;
	return (cmd_arr);
}

/* every sequences of tokens between pipes is treatead separately
this function will go to the first token after the pipe num iter,
or to the beginning of the tokens if iter == 0
NB : case there is nothing between two pipes (no tokens),
we throw an error (err msg AND exit code 258) */

static t_token	*goto_relevant_token(t_token *token, int iter)
{
	t_token		*gd_token;
	int			i;

	gd_token = token;
	i = 0;
	while (gd_token && i < iter)
	{
		if (gd_token->type == PIPE)
			i++;
		gd_token = gd_token->next;
	}
	if (gd_token->type == PIPE)
		handle_syntax_errors(gd_token);
	return (gd_token);
}

/* check if 1) token->type is a redirection metacharacter,
return 0 otherwise
if it is the case, it check if there is a next token
OR there is a next token but not of REDIR_ARG type
if that assumption is true (i.e syntax error), it return -1
and 1 otherwise (redirection, with correct syntax) */

static int	redir_status(t_token *redir_tk)
{
	if (redir_tk->type < REDIR_INPUT || redir_tk->type > RO_APPEND)
		return (0);
	if (!redir_tk->next || (redir_tk->next
		&& redir_tk->next->type != REDIR_ARG))
		return (-1);
	else
		return (1);
}

/* based on parsing result, this function should take care of redirections,
pipes and cmd exec in a relevant way
1) go to the token correspond to this iteration (i.e at the beginning
or just after the n pipe)
2) if pipes, redirect ot pipes
3) check if there any redirection, if no syntax err, perform them,
otherwise, throw an error with exit status 258
4) exec cmd if there is one, otherwise free cmd_arr and return
*/

void	pipes_redirs_cmd(t_shell *shell, t_token *token, int iter)
{
	t_token		*redir_tk;
	t_token		*cmd_tk;
	char		**cmd_arr;

	redir_tk = goto_relevant_token(token, iter);
	if (shell->nb_pipes != 0)
		redirect_to_pipe(shell, iter);
	cmd_tk = redir_tk;
	while (redir_tk && redir_tk->type != PIPE)
	{
		if (redir_status(redir_tk) == -1)
			handle_syntax_errors(redir_tk);
		else if (redir_status(redir_tk) == 1)
			operate_redir(shell, redir_tk->type, redir_tk->next->item, token);
		redir_tk = redir_tk->next;
	}
	cmd_arr = rtn_cmd_arr(cmd_tk);
	if (cmd_arr && cmd_arr[0] == NULL)
	{
		free_split(cmd_arr);
		return ;
	}
	else if (!cmd_arr)
		free_case_err(shell, token);
	cmd_exec(shell, cmd_arr, token);
}
