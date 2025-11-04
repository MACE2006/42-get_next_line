/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvorley <cvorley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:38:54 by cvorley           #+#    #+#             */
/*   Updated: 2025/10/31 19:49:43 by cvorley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

//headers
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

//main functions
char	*get_next_line(int fd);
char	*get_line(char *buffer);
void	shift_buffer(char *buffer);

//util functions
char	*ft_strchr(const char *string, int searchedChar );
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t elementCount, size_t elementSize);
size_t	ft_strlen(const char *theString);

#endif
