/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:29:56 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:49:06 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	free_info(char **info)
{
	int	i;

	i = -1;
	if (info)
	{
		while (info[++i])
		{
			free(info[i]);
			info[i] = NULL;
		}
		free(info);
		info = NULL;
	}
}

void	free_list(t_map_node *head)
{
	t_map_node	*temp;

	while (head)
	{
		temp = head->next;
		if (head->line)
			free(head->line);
		head->line = NULL;
		free(head);
		head = temp;
	}
}

void	free_record(t_record *record)
{
	if (record)
	{
		if (record->name)
			free(record->name);
		free(record);
	}
}

void	free_keys(t_key_node *head)
{
	t_key_node	*temp;

	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
}

void	free_doors(t_door_pos *head)
{
	t_door_pos	*temp;

	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
}
