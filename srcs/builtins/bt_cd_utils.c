/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:30:12 by xle-boul          #+#    #+#             */
/*   Updated: 2022/06/07 21:06:04 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// function to properly assign the path to old_pwd. careful though:
// if its value hasn't been assigned because it is the first cd command,
// its value remains NULL.
// keep in mind it's a pointer to a malloc'd memory space, thus it has to
// be freed before exiting minishell.
void	assign_old_pwd(t_shell *shell, char *arg, int success_code, char *pwd)
{
	if ((arg && arg[0] == '-' && ft_strlen(arg) == 1 && shell->old_pwd == NULL)
		|| success_code != 0)
	{
		free(pwd);
		return ;
	}
	if (shell->old_pwd != NULL)
		free(shell->old_pwd);
	shell->old_pwd = ft_strdup(pwd);
	free(pwd);
}

// a simple function to find the pwd at the time
char	*find_pwd(void)
{
	char	*pwd;

	pwd = malloc(sizeof(char) * MAX_PATH);
	if (!pwd)
		return (NULL);
	pwd = getcwd(pwd, MAX_PATH);
	return (pwd);
}

// replaces the ~ by home path
char	*expand_tilde(char *home, char *arg)
{
	size_t	final_len_arg;
	char	*final_arg;

	final_len_arg = ft_strlen(home) + ft_strlen(arg);
	final_arg = malloc(sizeof(char) * final_len_arg - 1);
	if (!final_arg)
		return (NULL);
	final_arg = ft_strdup(home);
	arg++;
	final_arg = ft_strjoin(final_arg, arg);
	return (final_arg);
}
