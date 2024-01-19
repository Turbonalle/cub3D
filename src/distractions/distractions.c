/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distractions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:22:09 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/19 14:39:21 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	init_dist(t_cub3d *cub3d, int i, int j, int distr_index)
{
	// printf("init_dist: setting distraction[%d] values\n", distr_index);
	cub3d->level->distractions[distr_index].pos.x = j + 0.5;
	cub3d->level->distractions[distr_index].pos.y = i + 0.5;
	cub3d->level->distractions[distr_index].collected = FALSE;
	cub3d->level->distractions[distr_index].thrown = FALSE;
	cub3d->level->distractions[distr_index].visible = FALSE;
	cub3d->level->distractions[distr_index].pos_screen.x = -WIDTH;
	cub3d->level->distractions[distr_index].pos_screen.y = -HEIGHT;
	cub3d->level->distractions[distr_index].dist_to_player = 100;
	// printf("init_dist: mlx_new_image\n");
	cub3d->level->distractions[distr_index].img_distraction
		= mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	// printf("init_dist: checking if image is NULL\n");
	if (!cub3d->level->distractions[distr_index].img_distraction)
	{
		i = 0;
		while (i < distr_index)
		{
			// printf("init_dist: mlx_delete_image(%d)\n", i);
			mlx_delete_image(cub3d->mlx,
				cub3d->level->distractions[i].img_distraction);
			i++;
		}
		return (-1);
	}
	// printf("init_dist: mlx_put_image_to_window()\n");
	mlx_image_to_window(cub3d->mlx,
		cub3d->level->distractions[distr_index].img_distraction, 0, 0);
	// printf("init_dist: return distr_index + 1\n");
	return (distr_index + 1);
}

static int	parse_map_for_distractions(t_cub3d *cub3d)
{
	int	i;
	int	j;
	int	distr_index;

	i = 0;
	distr_index = 0;
	// printf("parse_map_for_distractions: while (cub3d->level->map[%d])\n", i);
	while (cub3d->level->map[i])
	{
		j = 0;
		// printf("parse_map_for_distractions: while (cub3d->level->map[%d][%d])\n", i, j);
		while (cub3d->level->map[i][j])
		{
			// printf("parse_map_for_distractions: if (cub3d->level->map[%d][%d] == 'm' || cub3d->level->map[%d][%d] == 'r')\n", i, j, i, j);
			if (cub3d->level->map[i][j] == 'm'
				|| cub3d->level->map[i][j] == 'r')
			{
				// printf("parse_map_for_distractions: init_dist()\n");
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
	// printf("init_distractions\n");
	if (cub3d->level->num_distractions == 0)
		return (1);
	// printf("init_distractions: malloc()\n");
	cub3d->level->distractions = malloc(sizeof(t_distract)
			* (cub3d->level->num_distractions + 1));
	// printf("init_distractions: checking if cub3d->level->distractions is NULL\n");
	if (!cub3d->level->distractions)
		return (FAIL);
	// printf("init_distractions: parse_map_for_distractions()\n");
	if (!parse_map_for_distractions(cub3d))
		return (FAIL);
	// printf("init_distractions: return SUCCESS\n");
	return (SUCCESS);
}
