/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvorley <cvorley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:38:27 by cvorley           #+#    #+#             */
/*   Updated: 2025/10/31 10:26:16 by cvorley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 42

char	*ft_get_buffer(char *buffer, int fd)
{
	char	*next_buff;
	int		bytes_read;

	next_buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!next_buff)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, next_buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (next_buff);
			return (NULL);
		}
		next_buff[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, next_buff);
	}
	free (next_buff);
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
	return (str);
}

char	*ft_get_new_buffer(char *buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if(!buffer[i])
	{
		free (buffer);
		return (NULL);
	}
	new_buffer = (char *) malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!new_buffer)
		return (NULL);
	i++;
	j = 0;
	while(buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free (buffer);
	return (new_buffer);
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
	buffer = ft_get_new_buffer(buffer);
	if (!line[0])
		line = NULL;
	return (line);
}

//int	main(void)
//{
//	int		fd;
//	char	*line;
//	fd = open("test.txt", O_RDONLY);
//	line = get_next_line(fd);
//	printf("%s", line);
//	while (line)
//	{
//		line = get_next_line(fd);
//	
//	}
//}

