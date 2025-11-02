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

char *free_join(char *buffer, char *next_buff) {
  char *tmp;

  tmp = ft_strjoin(buffer, next_buff);
  free(buffer);
  return (tmp);
}

char *ft_get_buffer(char *ebuf, int fd) {
  char *buffer;
  int byte_reader;

  if (!ebuf)
    ebuf = ft_calloc(1, 1);
  buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
  byte_reader = 1;
  while (byte_reader > 0) {
    byte_reader = read(fd, buffer, BUFFER_SIZE);
    if (byte_reader == -1) {
      free(buffer);
      return (NULL);
    }
    buffer[byte_reader] = 0;
    ebuf = free_join(ebuf, buffer);
    if (strchr(buffer, '\n'))
      break;
  }
  free(buffer);
  return (ebuf);
}

char *ft_get_line(char *buffer) {
  char *line;
  int i;

  i = 0;
  if (!buffer[i])
    return (NULL);
  while (buffer[i] && buffer[i] != '\n')
    i++;
  line = ft_calloc(i + 2, sizeof(char));
  i = 0;
  while (buffer[i] && buffer[i] != '\n') {
    line[i] = buffer[i];
    i++;
  }
  if (buffer[i] && buffer[i] == '\n')
    line[i++] = '\n';
  return (line);
}

void *ft_get_new_buffer(char *buffer) {
  char *line;
  int i;
  int j;

  i = 0;
  while (buffer[i] && buffer[i] != '\n')
    i++;
  if (!buffer[i]) {
    free(buffer);
    return (NULL);
  }
  line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
  i++;
  j = 0;
  while (buffer[i])
    line[j++] = buffer[i++];
  free(buffer);
  return (line);
}

char *get_next_line(int fd) {
  static char *buffer;
  char *line;

  if (fd < 0 || BUFFER_SIZE <= 0)
    return (NULL);
  buffer = ft_get_buffer(buffer, fd);
  if (!buffer)
    return (NULL);
  line = ft_get_line(buffer);
  buffer = ft_get_new_buffer(buffer);
  if (!buffer)
    buffer = NULL;
  return (line);
}

//int main(int argc, char **argv) {
//  int fd;
//  char *line;
//  fd = open(argv[1], O_RDONLY);
//  line = get_next_line(fd);
//  printf("%s", line);
//  free(line);
//  (void)argc;
//}
