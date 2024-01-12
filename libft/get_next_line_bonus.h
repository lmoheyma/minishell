/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoheyma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:50:48 by lmoheyma          #+#    #+#             */
/*   Updated: 2023/11/17 13:59:06 by lmoheyma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
void	*ft_calloc(size_t nbElement, size_t sizeElement);
void	ft_bzero(void *buffer, size_t size);
char	*read_from_file(char *big_buffer, int fd);
int		ft_strlen(char *str);
char	*ft_strchr(const char *str, int c);
char	*add_to_buffer(char *big_buffer, char *read_buffer);
char	*get_line(char *buffer);
char	*next_line(char *buffer);
char	*ft_strjoin(char *s1, char *s2);

#endif
