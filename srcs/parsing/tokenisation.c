/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:04:56 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/14 22:40:15 by xle-boul         ###   ########.fr       */
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
		{
			if (is_quote_valid(&user_input[i], user_input[i]) == 1)
				i = i + calc_quote_length(user_input, i) - 1;
		}
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
3) if token length == 0, then return NULL
4) malloc memory for create a str with the token
5) copy the token in the malloqued char*
6) add the size of the whitespace in shell->item_length to be able to
move ui_copy later
7) return the malloqued token
*/

char	*isolate_item(char *user_input, t_shell *shell, t_token *token)
{
	char	*item;
	size_t	free_space_len;

	free_space_len = 0;
	while (user_input[0] == ' ')
	{
		free_space_len++;
		user_input++;
	}
	shell->item_length = 0;
	shell->item_length = calc_token_length(user_input);
	if (shell->item_length == 0)
		return (NULL);
	item = (char *)malloc(sizeof(char) * (shell->item_length + 1));
	if (!item)
		free_case_err(shell, token);
	ft_strlcpy(item, user_input, shell->item_length + 1);
	shell->item_length += free_space_len;
	return (item);
}
