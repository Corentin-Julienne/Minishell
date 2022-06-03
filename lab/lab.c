/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:36:11 by cjulienn          #+#    #+#             */
/*   Updated: 2022/06/03 16:27:39 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void	child_process(char **envp)
{
	char		**args;
	const char	*path;

	args = (char **)malloc(sizeof(char) * 2);
	if (!args)
		printf("oups\n");
	path = "../so_long";
	args[0] = "so_long";
	args[1] = NULL;
	if (execve(path, args, envp) == -1)
		printf("marche ap\n");
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;

	(void)argc;
	(void)argv;
	pid = fork();
	if (pid == -1)
	{
		printf("oups !\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		child_process(envp);
	else
		waitpid(pid, NULL, 0);
	return (0);
}
