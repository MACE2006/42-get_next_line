/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvorley <cvorley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:38:27 by cvorley           #+#    #+#             */
/*   Updated: 2025/10/28 13:11:29 by cvorley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#define BUFFER_SIZE 42

char	*ft_get_buffer(char	*buffer, int fd)
{
	char	*nextBuff;
	int		bytes_read;
	
	nextBuff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!nextBuff)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, nextBuff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (nextBuff);
			return (NULL);
		}
		nextBuff[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, nextBuff);
	}
	free (nextBuff);
	return (buffer);
}

char	*ft_get_line(char	*buffer)
{
	char	*str;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	str = (char *)malloc (sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		str[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
	{
		str[i] = buffer[i];
		i++;
	}
	str[i] = '\0';
	printf("%s", str);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = ft_get_buffer(buffer, fd);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	// printf("%s", buffer);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;
	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
}