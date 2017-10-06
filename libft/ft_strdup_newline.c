/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_newline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 11:52:39 by psprawka          #+#    #+#             */
/*   Updated: 2017/10/04 11:52:42 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_newline(char *src)
{
	char	*copy;
	int		i;
	
	i = 0;
	while (src[i] != '\0' && src[i] != '\n')
		i++;
	copy = (char*)malloc(i + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (src[i] != '\0' && src[i] != '\n')
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
