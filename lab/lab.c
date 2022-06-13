/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:36:11 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/11 17:46:49 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

static char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * strlen(s) + 1);
	if (!str)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	fulfill_env(char **dup_env, char **envp)
{
	int			i;

	i = 0;
	while (envp[i])
	{
		dup_env[i] = ft_strdup(envp[i]);
		if (!dup_env[i])
		{
			dprintf(STDERR_FILENO, "oups !\n");
			return (-1);
		}
		i++;
	}
	dup_env[i] = ft_strdup("DECOY=\"truc\"");
	dup_env[i + 1] = NULL;
	return (0);
}

static char	**envdup(char **envp)
{
	char		**dup_env;
	int			i;
	
	i = 0;
	while (envp[i])
		i++;
	dup_env = (char **)malloc(sizeof(char *) * (i + 2));
	if (!dup_env)
		return (NULL);
	fulfill_env(dup_env, envp);
	return (dup_env);
}

static void	inspect_main_env(char **envp)
{
	int			i;
	
	i = 0;
	while (envp && envp[i])
	{
		dprintf(STDERR_FILENO, "var %i : %s\n", i, envp[i]);
		i++;
	}
}


static void	child_process(char **envp)
{
	char		**args;
	const char	*path;

	args = (char **)malloc(sizeof(char) * 2);
	if (!args)
		printf("oups\n");
	path = "../minishell";
	args[0] = "minishell";
	args[1] = NULL;
	if (execve(path, args, envp) == -1)
		printf("marche ap\n");
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	char	**fake_new_env;

	(void)argc;
	(void)argv;
	dprintf(STDERR_FILENO, "this is the original env :\n");
	inspect_main_env(envp);
	dprintf(STDERR_FILENO, "\n\n--------------------------\n\n");
	fake_new_env = envdup(envp);
	pid = fork();
	if (pid == -1)
	{
		printf("oups !\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		child_process(fake_new_env);
	else
		waitpid(pid, NULL, 0);
	return (0);
}
