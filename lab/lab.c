/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:36:11 by cjulienn          #+#    #+#             */
/*   Updated: 2022/05/30 21:20:22 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void	child_process(char **envp)
{
	char		**args;
	const char	*path;

	args = (char **)malloc(sizeof(char) * 4);
	if (!args)
		printf("oups\n");
	path = "/bin/echo";
	args[0] = "ec\"ho";
	args[1] = "tr\"uc";
	args[3] = NULL;
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
