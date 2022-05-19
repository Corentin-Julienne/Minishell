/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 13:28:45 by cjulienn          #+#    #+#             */
/*   Updated: 2021/09/03 15:50:32 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char		*line = NULL;
	static int		iter = -1;
	char			*buffer;
	ssize_t			reader;

	iter++;
	buffer = manage_errors(fd);
	if (!buffer)
		return (NULL);
	reader = 1;
	while (ft_strchr(line, '\n') == NULL && reader > 0)
	{
		reader = read(fd, buffer, BUFFER_SIZE);
		if (reader < 0)
			break ;
		buffer[reader] = '\0';
		if (!line)
			line = ft_protec_strdup("");
		line = ft_strjoin_and_free(line, buffer);
		if (!line)
			return (ft_free_and_return(&buffer, NULL));
	}
	free(buffer);
	return (ft_output(reader, &line, iter));
}
