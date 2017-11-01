/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 12:41:27 by psprawka          #+#    #+#             */
/*   Updated: 2017/10/30 21:40:46 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char		*ft_strjoin_newline(char const *s1, char const *s2, int *only_nl)
{
	char	*f;
	int		i;
	
	if (!s1 || !s2)
		return (NULL);
	i = 0;
	if (!(f = (char *)malloc(ft_strlen((char *)s1) + ft_strlen_chr((char *)s2, '\n') + 1)))
		return (NULL);
	*only_nl = ((BUFF_SIZE == 1 && *s2 == '\n') ? 1 : 0);
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
//	printf("STRING: [%s]\ns[%d] = [%c]\n", s, *len, s[*len]);
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
	int		only_nl;

	only_nl = 0;
	while ((ret = read(fd, temp, BUFF_SIZE)) > 0)
	{
		*i = 0;
		temp[ret] = '\0';
		*line = (ret < 0 ? '\0': ft_strjoin_newline(*line, temp, &only_nl));
//		printf("ONLY_NL = %d\n", only_nl);
		if (only_nl == 1)
			return (1);
//		printf("HERE\n");
		while (*i < ret)
		{
			if (temp[*i] == '\n')
				return (1);
			*i += 1;
		}
		
		ft_strclr(temp);
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
	if (rest == NULL)
		rest = ft_memalloc(1);
	
	if (*rest != '\0')
	{

        *line = copy_new(rest, &i);
          if (rest[i] == '\n')
		  {
			  rest = ft_strsub(rest, i + 1, ft_strlen(rest) - i);
			  return (1);
		  }
		rest = ft_strsub(rest, i + 1, ft_strlen(rest) - i);
	}
	ret = find_line(line, fd, temp, &i);
	if (ret == 1 && BUFF_SIZE == 1)
		return (1);
//	printf("ret = %d\n", ret);
	if (ret == -1)
		return (-1);
	if (ret == 1)
		rest = ft_strsub(temp, i + 1, ft_strlen(temp) - i);
	if (*rest == '\0' && **line == '\0')
		return (0);
	return (1);
}

//int main(int argc, char **argv)
//{
//	char *line;
//	int fd;
//	int i;
//	int ret = 0;
//
//	if (argc != 2)
//		return (0);
//	fd = open(argv[1], O_RDONLY);
//	i = 0;
//	while ((ret = get_next_line(42, &line)) > 0)
//		printf("RET: [%d] Line: [%s]\n", ret, line);
//	printf("RET: [%d]\n",ret);
//	close(fd);
//	return 0;
//}
