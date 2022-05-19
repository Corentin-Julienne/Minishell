/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:14:04 by cjulienn          #+#    #+#             */
/*   Updated: 2022/04/29 14:07:46 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Quote Removal
	After the preceding expansions, all unquoted occurrences of the charac-
	ters  \,  ', and " that did not result from one of the above expansions
	are removed.
*/

static char *assemble_parts(t_token *token, char *env_var_exp,
	size_t i, size_t j)
{
	char		*part_1;
	char		*part_3;
	char		*expanded_str;

	part_1 = ft_substr(token->item, 0, i);
	if (!part_1)
		return (NULL);
	part_3 = ft_substr(token->item, i + j, ft_strlen(token->item) - i + j);
	if (!part_3)
	{
		free(part_1);
		return (NULL);
	}
	expanded_str = ft_triple_join(part_1, env_var_exp, part_3);
	free(part_1);
	free(part_3);
	if (!expanded_str)
		return (NULL);
	return (part_1);
}

static int	insert_var(t_token *token, char *str_to_expand, size_t i, size_t j)
{
	
	char		*env_var_exp;
	char		*expanded_str;

	if (!str_to_expand)
		return (-1);
	env_var_exp = getenv(str_to_expand + 1);
	if (env_var_exp == NULL)
		env_var_exp = "";
	free(str_to_expand);
	expanded_str = assemble_parts(token, env_var_exp, i, j);
	if (!expanded_str)
		return (-1);
	free(token->item);
	token->item = expanded_str;
	return (0);
}

/* check if the part of the str reached by index is within double quotes
used to increment the quote_switch int variable
return 0 if it is not the case, 1 otherwise */

static int	is_within_double_quotes(t_token *token, size_t i, int quote_switch)
{
	if (token->item[i] == '"' && quote_switch % 2 == 0)
	{
		if (is_quote_valid(&token->item[i], '"'))
			return (1);
	}
	else if (token->item[i] == '"' && quote_switch % 2 != 0)
		return (1);
	return (0);
}

/* this func takes care of the $ expansions
check whether $ is within simple quotes or not (inhibit expansion)
then, when reaching a $ outside simple quotes check wether
it is expansionnable or not. use rpl_env_var perform expansion */

void	expand_env_var(t_token *token)
{
	int			quote_switch;
	size_t		i;
	size_t		j;

	quote_switch = 0;
	i = 0;
	j = 1;
	while (token->item[i++])
	{
		if (is_within_double_quotes(token, i, quote_switch))
			quote_switch++;
		else if (token->item[i] == '\'' && quote_switch % 2 == 0
			&& is_quote_valid(&token->item[i], '\''))
			i = i + calc_quote_length(token->item, i) - 1;
		else if (token->item[i] == '$')
		{
			while (token->item[i + j] && ft_isalnum(token->item[i + j]))
				j++;
			if (token->item[i + 1] && token->item[i + 1] == '?')
				insert_var(token, ft_substr(token->item, i, i + 1), i, i + 1);
			else if (token->item[i + 1] && ft_isalnum(token->item[i + 1]))
				insert_var(token, ft_substr(token->item, i, j), i, j);
		}
	}
}
