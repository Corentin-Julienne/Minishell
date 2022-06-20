/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 23:23:04 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/20 21:40:41 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*isolate_variable(char *item, int i)
{
	char	*var;
	int		len;

	item += i;
	len = 1;
	while (ft_isalnum(item[len]) == 1)
		len++;
	var = ft_strldup(item, len);
	return (var);
}

bool	is_in_env(t_shell *shell, char *var)
{
	t_env	*tmp;

	var++;
	tmp = shell->env_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(var, tmp->data, ft_strlen(var)) == 0
			&& tmp->data[ft_strlen(var)] == '=')
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

bool	is_closed(char c, char *item, int i)
{
	i++;
	while (item[i] != '\0')
	{
		if (item[i] == c)
			return (true);
		i++;
	}
	return (false);
}

char	*convert_env_format(char *env, char *var)
{
	char	*new_env;
	int		len;

	len = (int)ft_strlen(var) + 1;
	env += len;
	new_env = ft_strdup(env);
	return (new_env);
}

char	*replace_exit_code(char *item, int i, char *exit_code)
{
	char	*new_item;

	new_item = ft_substr(item, 0, i);
	new_item = ft_strjoin_and_free(new_item, exit_code);
	item += (i + 2);
	if (*item != '\0')
		new_item = ft_strjoin_and_free(new_item, item);
	return (new_item);
}
