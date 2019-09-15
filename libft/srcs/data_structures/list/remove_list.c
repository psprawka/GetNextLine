/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 03:35:15 by psprawka          #+#    #+#             */
/*   Updated: 2018/10/08 13:48:52 by psprawka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_remove_list(t_node **list, t_node *node)
{
	t_node	*tmp;
	t_node	*prev;

	tmp = *list;
	prev = NULL;
	while (tmp)
	{
		if (tmp == node)
		{
			if (prev == NULL)
				*list = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
