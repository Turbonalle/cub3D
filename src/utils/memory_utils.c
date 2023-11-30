/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:41:53 by vvagapov          #+#    #+#             */
/*   Updated: 2023/11/24 10:12:26 by slampine         ###   ########.fr       */
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

void	free_cub3d(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (cub3d->level.texture[i].path)
			free(cub3d->level.texture[i].path);
		// if (cub3d->texture[i].img)
		// 	free(cub3d->texture[i].img);
	}
	i = -1;
	free_list(cub3d->level.map_list);
	free(cub3d->rays);
	while (cub3d->level.map[++i])
		free(cub3d->level.map[i]);
	if (cub3d->level.map)
		free(cub3d->level.map);
	if (cub3d->num_enemies)
		free(cub3d->enemy);
}
