/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:41:53 by vvagapov          #+#    #+#             */
/*   Updated: 2023/12/01 11:04:37 by slampine         ###   ########.fr       */
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

void	free_cub3d(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (cub3d->texture[i].path)
			free(cub3d->texture[i].path);
		// if (cub3d->texture[i].img)
		// 	free(cub3d->texture[i].img);
	}
	free_list(cub3d->map_list);
	free(cub3d->rays);
	i = -1;
	while (cub3d->map[++i])
		free(cub3d->map[i]);
	if (cub3d->map)
		free(cub3d->map);
	if (cub3d->num_enemies)
		free(cub3d->enemy);
	i = -1;
	while (++i < NUM_DOORS_MAX)
	{
		free_keys(cub3d->key_groups[i].keys);
		free_doors(cub3d->door_groups[i].door_positions);
	}
}
