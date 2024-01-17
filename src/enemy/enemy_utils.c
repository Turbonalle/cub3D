/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:34:33 by slampine          #+#    #+#             */
/*   Updated: 2024/01/17 12:35:34 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	check_if_door_unlocked(cub3d_t *cub3d, int xcoord, int ycoord)
{
	char	index;

	index = cub3d->level->map[ycoord][xcoord];
	if (all_keys_found(cub3d, index - 'A'))
		return (1);
	return (0);
}

static double	dist_to_door(vector_t v_map_check, dvector_t pos)
{
	dvector_t	help;
	double		dist;

	if (v_map_check.x == 1)
		help.x = v_map_check.x - 0.5;
	else
		help.x = v_map_check.x + 0.5;
	if (v_map_check.y == 1)
		help.y = v_map_check.y - 0.5;
	else
		help.y = v_map_check.y + 0.5;
	dist = dist_between_d_vectors(help, pos);
	return (dist);
}

int	wall_or_door_found(cub3d_t *cub3d, vector_t v_map_check)
{
	if (v_map_check.x >= 0
		&& v_map_check.x < cub3d->level->map_columns
		&& v_map_check.y >= 0
		&& v_map_check.y < cub3d->level->map_rows
		&& cub3d->level->map[v_map_check.y][v_map_check.x] == WALL)
		return (1);
	if (v_map_check.x >= 0
		&& v_map_check.x < cub3d->level->map_columns && v_map_check.y >= 0
		&& v_map_check.y < cub3d->level->map_rows
		&& (cub3d->level->map[v_map_check.y][v_map_check.x] == 'A'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'B'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'C'
		|| cub3d->level->map[v_map_check.y][v_map_check.x] == 'D'))
	{
		if (dist_to_door(v_map_check, cub3d->player.pos) > 2)
			return (1);
		if (check_if_door_unlocked(cub3d, v_map_check.x, v_map_check.y))
			return (0);
		else
			return (1);
	}
	return (0);
}
