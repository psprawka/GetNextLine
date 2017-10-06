/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 12:36:54 by psprawka          #+#    #+#             */
/*   Updated: 2017/09/28 12:36:57 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 3
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct	s_line
{
	int				fd;
	char			*rest;
	struct s_line	*next;
	
}				t_line;


int			get_next_line(const int fd, char **line);
t_line		*ft_list_find(t_line *begin_list, int fd, int (*cmp)());
t_line		*ft_listnew(void const *rest, int fd);

#endif
