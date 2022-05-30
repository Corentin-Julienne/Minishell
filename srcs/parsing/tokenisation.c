/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:04:56 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/30 13:28:01 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* return 1 if pipe or < or >, 
return 2 if << or >> */

static size_t	manage_chevrons_length(char *user_input, size_t i)
{
	char	*cutted_str;
	size_t	len;
	
	cutted_str = &user_input[i];
	len = ft_strlen(cutted_str);
	if (user_input[i] == '<' && len > 1)
	{
		if (user_input[i + 1] == '<')
			return (2);
	}
	else if (user_input[i] == '>' && len > 1)
	{
		if (user_input[i + 1] == '>')
			return (2);
	}
	return (1);
}

/* this will calculate the length of the token :
=> if it is a quote, calc the length until next quote (if present)
=> redir and pipes count as a single token
=> if blank space and not inside quote, then stop there 
*/

static size_t	calc_token_length(char *user_input)
{
	size_t		i;

	i = 0;
	while (user_input[i])
	{
		if (user_input[i] == '\'' || user_input[i] == '"')
			i = i + calc_quote_length(user_input, i) - 1;
		else if (user_input[i] == '|' || user_input[i] == '<'
			|| user_input[i] == '>')
		{
			if (i > 0)
				break ;
			else
				return (manage_chevrons_length(user_input, i));
		}
		else if (user_input[i] == ' ')
			break ;
		i++;
	}
	return (i);
}

/* the goal is to cut every token :
1) move the pointer forward for removing whitespaces
2) calc the length of the token (a strlen for tokens, basically)
3) malloc memory for create a str with the token
4) copy the token in the malloqued char*
5) return the malloqued token
*/

char	*isolate_item(char *user_input, t_shell *shell, t_token *token)
{
	char	*item;

	while (user_input[0] == ' ')
		user_input++;
	shell->j = 0;
	shell->j = calc_token_length(user_input);
	item = (char *)malloc(sizeof(char) * (shell->j + 1));
	if (!item)
		free_parent_case_err(shell, token);
	ft_strlcpy(item, user_input, shell->j + 1);
	return (item);
}
