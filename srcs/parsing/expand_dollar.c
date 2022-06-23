/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:52:07 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/22 13:40:25 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// creates a new string with the variable replaced and the relinks it to the
// token->item
char	*replace_variable(char *item, t_shell *shell, int i, char *var)
{
	char	*new_item;
	t_env	*tmp;
	char	*env;

	tmp = shell->env_list;
	new_item = ft_substr(item, 0, i);
	item += i;
	var++;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->data, var, ft_strlen(var)) == 0)
			env = convert_env_format(tmp->data, var);
		tmp = tmp->next;
	}
	new_item = ft_strjoin_and_free(new_item, env);
	item += ft_strlen(var) + 1;
	if (*item != '\0')
		new_item = ft_strjoin_and_free(new_item, item);
	free(env);
	return (new_item);
}

// goes into details with the decision to expand or not a variable
char	*dollar_hub(char *item, t_shell *shell, int i)
{
	char	*new_item;
	char	*var;

	var = isolate_variable(item, i);
	i++;
	new_item = NULL;
	if (item[i] == '\0')
		new_item = ft_strdup(item);
	else if (item[i] == '?')
		new_item = replace_exit_code(item, i - 1, ft_itoa(shell->exit_status));
	else if (ft_isalpha(item[i]) == 0
		|| (ft_isalpha(item[i]) == 1 && is_in_env(shell, var) == false))
		ft_rm_substr(item, var, &new_item);
	else if (ft_isalpha(item[i]) == 1 && is_in_env(shell, var) == true)
		new_item = replace_variable(item, shell, i - 1, var);
	free(var);
	return (new_item);
}

void	handle_single_quote(t_token *token, int *i)
{
	if (is_closed('\'', token->item, *i) == true)
	{
		(*i)++;
		while (token->item[*i] != '\'')
			(*i)++;
	}
}

// handles if a $ variable should be expanded or not
void	handle_dollar(t_token *token, t_shell *shell, int *i, int *_double)
{
	char	*tmp;

	tmp = token->item;
	token->item = dollar_hub(token->item, shell, *i);
	if (&tmp != &token->item)
		free(tmp);
	*i = -1;
	*_double = 0;
}

// parses the input and detects whether the current char is
// - $
// - "
// - '
void	detect_quotes(t_token *token, t_shell *shell)
{
	int			_double;
	int			i;

	_double = 0;
	i = 0;
	while (token->item[i] != '\0')
	{
		if (token->item[i] == '$')
			handle_dollar(token, shell, &i, &_double);
		else if (token->item[i] == '\'' && _double == 0)
			handle_single_quote(token, &i);
		else if (token->item[i] == '"' && _double == 0)
		{
			if (is_closed('"', token->item, i) == true)
				_double = 1;
		}
		else if (token->item[i] == '"' && _double == 1)
			_double = 0;
		i++;
	}
}
