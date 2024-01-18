/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distractions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:22:09 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 11:15:24 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	init_dist(t_cub3d *cub3d, int i, int j, int distr_index)
{
	cub3d->level->distractions[distr_index].pos.x = j + 0.5;
	cub3d->level->distractions[distr_index].pos.y = i + 0.5;
	cub3d->level->distractions[distr_index].collected = FALSE;
	cub3d->level->distractions[distr_index].thrown = FALSE;
	cub3d->level->distractions[distr_index].visible = FALSE;
	cub3d->level->distractions[distr_index].pos_screen.x = -WIDTH;
	cub3d->level->distractions[distr_index].pos_screen.y = -HEIGHT;
	cub3d->level->distractions[distr_index].dist_to_player = 100;
	cub3d->level->distractions[distr_index].img_distraction
		= mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->level->distractions[distr_index].img_distraction)
	{
		i = 0;
		while (i < distr_index)
		{
			mlx_delete_image(cub3d->mlx,
				cub3d->level->distractions[i].img_distraction);
			i++;
		}
		return (-1);
	}
	mlx_image_to_window(cub3d->mlx,
		cub3d->level->distractions[distr_index].img_distraction, 0, 0);
	return (distr_index + 1);
}

static int	parse_map_for_distractions(t_cub3d *cub3d)
{
	int	i;
	int	j;
	int	distr_index;

	i = 0;
	distr_index = 0;
	while (cub3d->level->map[i])
	{
		j = 0;
		while (cub3d->level->map[i][j])
		{
			if (cub3d->level->map[i][j] == 'm'
				|| cub3d->level->map[i][j] == 'r')
			{
				distr_index = init_dist(cub3d, i, j, distr_index);
				if (distr_index == -1)
					return (free(cub3d->level->distractions), FAIL);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	init_distractions(t_cub3d *cub3d)
{
	if (cub3d->level->num_distractions == 0)
		return (SUCCESS);
	cub3d->level->distractions = malloc(sizeof(t_distraction)
			* (cub3d->level->num_distractions + 1));
	if (!cub3d->level->distractions)
		return (FAIL);
	if (!parse_map_for_distractions(cub3d))
		return (FAIL);
	return (SUCCESS);
}
