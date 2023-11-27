/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:13:26 by marvin            #+#    #+#             */
/*   Updated: 2023/11/21 10:49:04 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*temp;

	if (lst && del)
	{
		current = *lst;
		temp = *lst;
		while (temp)
		{
			temp = temp->next;
			del(current->content);
			free(current);
			current = temp;
		}
		*lst = 0;
	}
}