/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:43:00 by slampine          #+#    #+#             */
/*   Updated: 2024/01/15 16:16:46 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	new_pos_is_wall_collision(cub3d_t *cub3d)
{
	//TODO: FIX PLAYER RUNNNING THORUGH WALLS
	return (cub3d->level->map[(int)cub3d->player.new_pos.y][(int)cub3d->player.new_pos.x] == WALL
		|| is_locked_door(cub3d, (int)cub3d->player.new_pos.y, (int)cub3d->player.new_pos.x) == TRUE);
}

int pos_is_goal(cub3d_t *cub3d)
{
	return (cub3d->level->map[(int)cub3d->player.pos.y][(int)cub3d->player.pos.x] == 'G');
}

int	corner_collision(cub3d_t *cub3d)
{
	return ((cub3d->level->map[(int)cub3d->player.new_pos.y][(int)cub3d->player.pos.x] == WALL
		|| is_locked_door(cub3d, (int)cub3d->player.new_pos.y, (int)cub3d->player.pos.x))
		&& (cub3d->level->map[(int)cub3d->player.pos.y][(int)cub3d->player.new_pos.x] == WALL
		|| is_locked_door(cub3d, (int)cub3d->player.pos.y, (int)cub3d->player.new_pos.x)));
}

void	collision_checker(cub3d_t *cub3d)
{
	dvector_t	delta;
	int			wall;

	item_collected_checker(cub3d);
	printf("current pos = %f,%f\n new pos = %f,%f\n",cub3d->player.pos.x,cub3d->player.pos.y,cub3d->player.new_pos.x,cub3d->player.new_pos.y);
	if (new_pos_is_wall_collision(cub3d))
	{
		delta.x = cub3d->player.new_pos.x - cub3d->player.pos.x;
		delta.y = cub3d->player.new_pos.y - cub3d->player.pos.y;
		wall = find_end_point(cub3d, cub3d->player,
				cub3d->player.movement_angle, cub3d->player.new_pos);
		if (wall == WE || wall == EA)
		{
			if (cub3d->level->map[(int)cub3d->player.new_pos.y][(int)cub3d->player.pos.x] != WALL && !is_locked_door(cub3d, (int)cub3d->player.new_pos.y, (int)cub3d->player.pos.x))
				cub3d->player.pos.y = cub3d->player.new_pos.y;
		}
		else if (wall == NO || wall == SO)
		{
			if (cub3d->level->map[(int)cub3d->player.pos.y][(int)cub3d->player.new_pos.x] != WALL && !is_locked_door(cub3d, (int)cub3d->player.pos.y, (int)cub3d->player.new_pos.x))
				cub3d->player.pos.x = cub3d->player.new_pos.x;
		}
	}
	else if (corner_collision(cub3d))
	{
		cub3d->player.new_pos = cub3d->player.pos;
	}
	else
	{
		cub3d->player.pos = cub3d->player.new_pos;
	}
	if (pos_is_goal(cub3d))
	{
		if (cub3d->player.thrown)
			cub3d->level->distractions[cub3d->level->num_distractions].img_distraction->instances[0].enabled = FALSE;
		level_finished(cub3d);
	}
}
