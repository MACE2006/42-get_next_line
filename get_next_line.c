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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 10

static char	*append(char *stash, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin(stash ? stash : "", buf);
	free(stash);
	return (tmp);
}

static char	*read_to_stash(int fd, char *stash)
{
	char	*buf;
	int		bytes;
	char	*tmp;

	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	bytes = 1;
	while (bytes > 0 && (!stash || !ft_strchr(stash, '\n')))
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(stash);
			free(buf);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		buf[bytes] = '\0';
		tmp = append(stash, buf);
		if (!tmp)
		{
			free(buf);
			return (NULL);
		}
		stash = tmp;
	}
	free(buf);
	return (stash);
}

static char	*extract_line(char *stash)
{
	size_t	len;
	size_t	i;
	char	*line;

	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = ft_calloc(len + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*update_stash(char *stash)
{
	char	*nl;
	size_t	len;
	size_t	i;
	char	*new;

	nl = ft_strchr(stash, '\n');
	if (!nl || !*(nl + 1))
	{
		free(stash);
		return (NULL);
	}
	len = ft_strlen(nl + 1);
	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
	{
		free(stash);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		new[i] = (nl + 1)[i];
		i++;
	}
	new[i] = '\0';
	free(stash);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	if (BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = update_stash(stash);
	return (line);
}

// size_t  ft_strlcpy(char *dst, const char *src, size_t size)
// {
//   size_t  i;
//   i = 0;
// }

int main(int argc, char **argv) {
  int fd;
  char *line;
  fd = open(argv[1], O_RDONLY);
  line = get_next_line(fd);
  printf("%s", line);
  free(line);
  get_next_line(-1);
  (void)argc;
}
