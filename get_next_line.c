/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvorley <cvorley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:38:27 by cvorley           #+#    #+#             */
/*   Updated: 2025/10/31 20:18:43 by cvorley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 1000000

char	*free_join(char *buffer, char *next_buff)
{
	char	*tmp;

	tmp = ft_strjoin(buffer, next_buff);
	free (buffer);
	return (tmp);
}

char	*ft_get_buffer(char *buffer, int fd)
{
	char	*text;
	int		bytes_read;

	text = (char *) malloc(1 * sizeof(char));
	if (!text)
		return (NULL);
	text[0] = '\0';
	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read > 0)
	{
		if (buffer[0] == '\0')
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read <= 0)
				break ;
			buffer[bytes_read] = '\0'; 
		}
		text = free_join(text, buffer);
		if (!ft_strchr(buffer, '\n'))
			buffer[0] = '\0';
	}
	return (text);
}

char	*ft_get_line(char	*buffer)
{
	char	*str;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	str = ft_calloc(i + (buffer[i] == '\n') + 2, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		str[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

void	*ft_get_new_buffer(char *buffer)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] && buffer[i] == '\n')
		i++;
	while (buffer[i])
		buffer[j++] = buffer[i++];
	buffer[j] = '\0';
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*text;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	text = ft_get_buffer(buffer, fd);
	if (!text)
		return (NULL);
	line = ft_get_line(text);
	free (text);
	ft_get_new_buffer(buffer);
	return (line);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	(void)argc;
}

