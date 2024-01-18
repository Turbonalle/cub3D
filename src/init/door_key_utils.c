/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_key_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:45:57 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:45:51 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	count_keys(t_cub3d *cub3d, int i)
{
	t_key_node	*temp;
	int			count;

	temp = cub3d->level->key_groups[i].keys;
	count = 0;
	while (temp)
	{
		temp->pos_screen.x = -WIDTH;
		temp->pos_screen.y = -HEIGHT;
		temp->visible = FALSE;
		temp->dist_to_player = 100;
		temp->img_curr_frame = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
		if (!temp->img_curr_frame || (mlx_image_to_window(cub3d->mlx,
					temp->img_curr_frame, 0, 0) < 0))
			return (-1);
		temp = temp->next;
		count++;
	}
	return (count);
}

int	free_doors_and_keys(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		free_doors(cub3d->level->door_groups[i].door_positions);
		free_keys(cub3d->level->key_groups[i].keys);
		i++;
	}
	return (FAIL);
}
