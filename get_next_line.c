/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 12:36:32 by psprawka          #+#    #+#             */
/*   Updated: 2017/09/28 12:36:34 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>

static char		*save_the_rest(int *i, char *rest)
{
	rest = ft_strsub(rest, *i + 1, ft_strlen(rest) - *i - 1);
	return (rest);
}

static int		ft_find_line(char **line, char *temp, int fd, int *i)
{
	int		characters;
	
	while ((characters = read(fd, temp, BUFF_SIZE)) > 0)
	{
		temp[BUFF_SIZE + 1] == '\0';
		while (temp[*i] != '\0' && temp[*i] != '\n')
			*i += 1;
		
		*line = ft_strjoin_newline(*line, temp);
		printf("HERE \n");
		
		if (temp[*i] == '\0' && (*i != (BUFF_SIZE + 1)))
				return (0);
		if (temp[*i] == '\n')
			return (1);
		*i = 0;
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char	*rest = NULL;
	char		temp[BUFF_SIZE + 1];
	char		*chj;
	int			if_end;
	int			i;
	
	if (fd < 0 || BUFF_SIZE < 1)
		return (-1);
	
	ft_strclr(*line);
	i = 0;
	
	if (rest != NULL)
	{
		chj = rest;;
		while (chj[i])
		{
			if (chj[i] == '\n')
			{
				rest = ft_strsub(chj, i, ft_strlen(chj) - i - 1);
				*line = ft_strdup_newline(chj);
				return (1);
			}
			i++;
		}
		*line = rest;
	}
	
	if_end = ft_find_line(line, temp, fd, &i);
	rest = save_the_rest(&i, temp);
	return (if_end);
}

int main()
{
	int			fd;
	char		*line;
	
	fd = open("file.txt", O_RDONLY);
	
	while (get_next_line(fd, &line))
		printf("%s\n", line);
	close(fd);
	return 0;
}
