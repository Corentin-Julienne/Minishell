/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:10:48 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/01 16:56:58 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* syntax errors handler.
works in a bash-like way, throwing an error msg, then 
cleaning the process and putting exit status to 258 */

void	handle_syntax_errors(t_token *pb_token) // change function prototype
{
	char	*following_token;
	
	if (!pb_token->next)
		following_token = "newline";
	else
		following_token = pb_token->next->item;	
	ft_putstr_fd(SYNT_ERR, STDERR_FILENO);
	ft_putstr_fd(following_token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	// free everything without exiting
	exit(258); // useful ?
}
