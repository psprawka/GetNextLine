/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 12:41:27 by psprawka          #+#    #+#             */
/*   Updated: 2017/10/10 12:41:29 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char		*ft_strjoin_newline(char const *s1, char const *s2)
{
	char	*f;
	int		i;
	
	if (!s1 || !s2)
		return (NULL);
	i = 0;
	if (!(f = (char *)malloc(ft_strlen((char *)s1)
							 + ft_strlen_chr((char *)s2, '\n') + 1)))
		return (NULL);
	while (s1[i])
	{
		f[i] = s1[i];
		i++;
	}
	while (*s2 && *s2 != '\n')
	{
		f[i] = *s2++;
		i++;
	}
	f[i] = '\0';
	return (f);
}

static char		*copy_new(char *s, int *len)
{
	int		i;
	char	*new;
	i = 0;
	
	while ((s[*len] != '\n') && (s[*len] != '\0'))
		*len += 1;
	new = (char *)malloc(*len + 1);
	while ((s[i] != '\n') && (s[i] != '\0'))
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}


static int		find_line(char **line, int fd, char *temp, int *i)
{
	int		ret;

	while ((ret = read(fd, temp, BUFF_SIZE)) > 0)
	{
		*i = 0;
		temp[ret] = '\0';
		*line = (ret < 0 ? '\0': ft_strjoin_newline(*line, temp));
		while (*i < ret)
		{
			if (temp[*i] == '\n')
				return (1);
			*i += 1;
		}
		
		ft_strclr(temp);
//		ft_bzero(temp, BUFF_SIZE + 1);
	}
	if (ret < 0)
		return (-1);
	if (ret == 0)
		return (0);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	*rest;
	char		temp[BUFF_SIZE + 1];
	int			i;
	int			ret;

	i = 0;
	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	*line = ft_memalloc(1);
	if (rest != NULL)
	{
        printf("line: %s, rest: %s\n", *line, rest);
        *line = copy_new(rest, &i);
        
            rest = ft_strsub(rest, i + 1, ft_strlen(rest) - i);
//        printf("AFTER: i = %d, line %s, rest pocztek%skoniec\n", i, *line, rest);
//        printf("HEEEEREEEEE\n");
        if (rest[i] != '\0')
            rest = NULL;
            return (1);
	}
	else
		rest = ft_memalloc(1);
	ret = find_line(line, fd, temp, &i);
	if (ret == -1)
		return (-1);
    
	if (ret == 1)
		rest = ft_strsub(temp, i + 1, ft_strlen(temp) - i);
    if (rest[0] == '\0')
        free(rest);
	if (*rest == '\0' && **line == '\0')
		return (0);
	return (1);
}

int main(int argc, char **argv)
{
	char *line;
	int fd;
	int i;
	int ret = 0;

	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	i = 0;
	while ((ret = get_next_line(fd, &line)))
		printf("RET: [%d] Line: [%s]\n", ret, line);
	printf("RET: [%d]\n",ret);
	close(fd);
	return 0;
}
