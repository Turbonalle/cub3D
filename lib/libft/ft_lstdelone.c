/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:06:37 by marvin            #+#    #+#             */
/*   Updated: 2023/02/22 08:43:28 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		(*del)(lst->content);
		free(lst);
	}
}