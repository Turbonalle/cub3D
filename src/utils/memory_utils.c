/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:29:56 by slampine          #+#    #+#             */
/*   Updated: 2024/01/11 13:46:41 by slampine         ###   ########.fr       */
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
			free(info[i]);
		free(info);
	}
}

void	free_list(map_node_t *head)
{
	map_node_t	*temp;

	while (head)
	{
		temp = head->next;
		free(head->line);
		free(head);
		head = temp;
	}
}

void	free_record(record_t *record)
{
	if (record)
	{
		if (record->name)
			free(record->name);
		free(record);
	}
}

void	free_keys(key_node_t *head)
{
	key_node_t	*temp;

	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
}

void	free_doors(door_pos_t *head)
{
	door_pos_t	*temp;

	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
}
