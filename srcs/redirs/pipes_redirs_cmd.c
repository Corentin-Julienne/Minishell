/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redir_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:59:33 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/25 17:46:41 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	return (gd_token);
}

static size_t	calc_cmd_len(t_token *cmd_token)
{
	size_t		cmd_len;

	cmd_len = 0;
	while (cmd_token && (cmd_token->type == CMD || cmd_token->type == ARG))
	{
		cmd_len++;
		cmd_token = cmd_token->next;
	}
	return (cmd_len);
}

/*  this func transform the tokens into a str array with CMD as arr[0],
followed then the flag and args, ended by NULL */

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
		cmd_arr[i] = ft_strdup(cmd_token->item);
		if (!cmd_arr[i])
		{
			free_problem_str_arr(cmd_arr, i);
			return (NULL);
		}
		cmd_token = cmd_token->next;
		i++;
	}
	cmd_arr[i] = NULL;
	return (cmd_arr);
}

/* based on parsing result, this function should take care of redirections,
pipes and cmd exec in a relevant way */

int	pipes_redirs_cmd(t_shell *shell, t_token *token, int iter)
{
	t_token		*redir_token;
	t_token		*cmd_token;

	if (shell->nb_pipes != 0)
		redirect_to_pipe(shell, iter);
	redir_token = goto_relevant_token(token, iter);
	cmd_token = redir_token;
	while (redir_token && redir_token->type != PIPE)
	{
		if (redir_token->type >= 2 && redir_token->type <= 5 // need to be handled when no path provided
			&& redir_token->next)
			operate_redir(shell, redir_token->type, redir_token->next->item);
		redir_token = redir_token->next;
	}
	while (cmd_token && cmd_token->type != PIPE)
	{
		if (cmd_token->type == CMD)
		{
			cmd_exec(shell, rtn_cmd_arr(cmd_token));
			break ;
		}
		cmd_token = cmd_token->next;
	}
	return (0);
}
