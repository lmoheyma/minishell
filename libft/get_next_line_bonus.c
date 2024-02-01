/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <lmoheyma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:50:13 by lmoheyma          #+#    #+#             */
/*   Updated: 2024/01/31 14:23:12 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*add_to_buffer(char *big_buffer, char *read_buffer)
{
	char	*tmp;

	tmp = ft_strjoin(big_buffer, read_buffer);
	free(big_buffer);
	return (tmp);
}

char	*read_from_file(char *res, int fd)
{
	char	*buffer;
	int		bytes;

	bytes = 1;
	if (!res)
		res = ft_calloc(1, 1);
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = 0;
		res = add_to_buffer(res, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

char	*get_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*next_line(char *buffer)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	res = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!res)
		return (NULL);
	i++;
	while (buffer[i])
	{
		res[j++] = buffer[i++];
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*big_buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	big_buffer[fd] = read_from_file(big_buffer[fd], fd);
	if (!big_buffer[fd])
		return (NULL);
	line = get_line(big_buffer[fd]);
	big_buffer[fd] = next_line(big_buffer[fd]);
	return (line);
}

/*
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int	fd;
	char	*next_line;

	fd = open("empty", O_RDWR);
	next_line = get_next_line(fd);
	printf("%s", next_line);
	close(fd);
	return (0);
}*/
