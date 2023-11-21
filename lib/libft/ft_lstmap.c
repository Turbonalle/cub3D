/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:35:24 by marvin            #+#    #+#             */
/*   Updated: 2023/11/21 10:49:19 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*i;

	if (!lst && !f)
		return (NULL);
	temp = NULL;
	while (lst)
	{
		if (!(i = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&temp, del);
			return (NULL);
		}
		ft_lstadd_back(&temp, i);
		lst = lst->next;
		i = i->next;
	}
	return (temp);
}