/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:43:00 by slampine          #+#    #+#             */
/*   Updated: 2024/01/16 13:56:46 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int wall_on_path(cub3d_t *cub3d)
{
    int new_pos_x = (int)cub3d->player.new_pos.x;
    int new_pos_y = (int)cub3d->player.new_pos.y;

    int pos_x = (int)cub3d->player.pos.x;
    int pos_y = (int)cub3d->player.pos.y;


    // Check new_pos
    if (cub3d->level->map[new_pos_y][new_pos_x] == WALL ||
        is_locked_door(cub3d, new_pos_y, new_pos_x) == TRUE)
    {
        return 1;
    }

    // Check halfway between pos and new_pos
    int halfway_x = (pos_x + new_pos_x) / 2;
    int halfway_y = (pos_y + new_pos_y) / 2;
    if (cub3d->level->map[halfway_y][halfway_x] == WALL ||
        is_locked_door(cub3d, halfway_y, halfway_x) == TRUE)
    {
        return 1;
    }

    // Check 25% position
    int quarter_x = pos_x + (new_pos_x - pos_x) * 0.25;
    int quarter_y = pos_y + (new_pos_y - pos_y) * 0.25;
    if (cub3d->level->map[quarter_y][quarter_x] == WALL ||
        is_locked_door(cub3d, quarter_y, quarter_x) == TRUE)
    {
        return 1;
    }

    // Check 75% position
    int three_quarters_x = pos_x + (new_pos_x - pos_x) * 0.75;
    int three_quarters_y = pos_y + (new_pos_y - pos_y) * 0.75;
    if (cub3d->level->map[three_quarters_y][three_quarters_x] == WALL ||
        is_locked_door(cub3d, three_quarters_y, three_quarters_x) == TRUE)
    {
        return 1;
    }

    return 0;
}

int	new_pos_is_wall_collision(cub3d_t *cub3d)
{
	//TODO: FIX PLAYER RUNNNING THORUGH WALLS
	if (dist_between_d_vectors(cub3d->player.pos, cub3d->player.new_pos) >= 1)
	{
		printf("dist between pos and new pos: %f\n", dist_between_d_vectors(cub3d->player.pos, cub3d->player.new_pos));
		return (wall_on_path(cub3d));
	}
	return (cub3d->level->map[(int)cub3d->player.new_pos.y][(int)cub3d->player.new_pos.x] == WALL
		|| is_locked_door(cub3d, (int)cub3d->player.new_pos.y, (int)cub3d->player.new_pos.x) == TRUE);
}

int	pos_is_goal(cub3d_t *cub3d)
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

	if (new_pos_is_wall_collision(cub3d)/*  || there_is_a_wall_between_pos_and_new_pos(cub3d) */)
	{
		delta.x = cub3d->player.new_pos.x - cub3d->player.pos.x;
		delta.y = cub3d->player.new_pos.y - cub3d->player.pos.y;
		wall = find_end_point(cub3d, cub3d->player,
				cub3d->player.movement_angle, cub3d->player.new_pos);
			printf("WALL is %i\n",wall);
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
	item_collected_checker(cub3d);
	if (pos_is_goal(cub3d))
	{
		if (cub3d->player.thrown)
			cub3d->level->distractions[cub3d->level->num_distractions].img_distraction->instances[0].enabled = FALSE;
		level_finished(cub3d);
	}
}
