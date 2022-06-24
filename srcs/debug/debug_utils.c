/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:54:30 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/14 22:42:38 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* contains utils to actually have feedback on minishell features
NOT TO INCLUDE IN THE REPO FOR EVAL !!!!! */

/* this func is used to check if the tokenisation process actually succeeded */

void	display_every_token(t_token *token)
{
	int			i;

	i = 0;
	while (token)
	{
		dprintf(STDERR_FILENO, "token [%i] = [%s] | type = %d\n",
			i, token->item, token->type);
		token = token->next;
		i++;
	}
}

void	inspect_char_arr(char **arr)
{
	int			i;

	i = 0;
	while (arr && arr[i])
	{
		dprintf(STDERR_FILENO, "[%i] = [%s]\n", i, arr[i]);
		i++;
	}
}

void	inspect_exit_code(t_shell *shell)
{
	dprintf(STDERR_FILENO, "current exit code : %d\n", shell->exit_status);
}

void	inspect_main_env(char **envp)
{
	int			i;

	i = 0;
	while (envp && envp[i])
	{
		dprintf(STDERR_FILENO, "var %i : %s\n", i, envp[i]);
		i++;
	}
}

void	leaks_killing(void)
{
	system("leaks minishell");
}
