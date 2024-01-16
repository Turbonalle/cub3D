/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:43:00 by slampine          #+#    #+#             */
/*   Updated: 2024/01/16 21:10:46 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

// int wall_on_path(cub3d_t *cub3d, dvector_t *delta)
// {
// 	(void)delta;
	
//     double new_pos_x = cub3d->player.new_pos.x;
//     double new_pos_y = cub3d->player.new_pos.y;
//     double pos_x = cub3d->player.pos.x;
//     double pos_y = cub3d->player.pos.y;


//     // Check new_pos
//     if (cub3d->level->map[(int)new_pos_y][(int)new_pos_x] == WALL ||
//         is_locked_door(cub3d, (int)new_pos_y, (int)new_pos_x) == TRUE)
//     {
//         return 1;
//     }

//     // Check halfway between pos and new_pos
//     double halfway_x = (pos_x + new_pos_x) / 2;
//     double halfway_y = (pos_y + new_pos_y) / 2;
//     if (cub3d->level->map[(int)halfway_y][(int)halfway_x] == WALL ||
//         is_locked_door(cub3d, (int)halfway_y, (int)halfway_x) == TRUE)
//     {
//         return 1;
//     }

//     // Check 25% position
//     double quarter_x = pos_x + (new_pos_x - pos_x) * 0.25;
//     double quarter_y = pos_y + (new_pos_y - pos_y) * 0.25;
//     if (cub3d->level->map[(int)quarter_y][(int)quarter_x] == WALL ||
//         is_locked_door(cub3d, (int)quarter_y, (int)quarter_x) == TRUE)
//     {
//         return 1;
//     }

//     // Check 75% position
//     double three_quarters_x = pos_x + (new_pos_x - pos_x) * 0.75;
//     double three_quarters_y = pos_y + (new_pos_y - pos_y) * 0.75;
//     if (cub3d->level->map[(int)three_quarters_y][(int)three_quarters_x] == WALL ||
//         is_locked_door(cub3d, (int)three_quarters_y, (int)three_quarters_x) == TRUE)
//     {
//         return 1;
//     }
//     return 0;
// }

// int	new_pos_is_wall_collision(cub3d_t *cub3d, dvector_t *delta)
// {
// 	if (dist_between_d_vectors(cub3d->player.pos, cub3d->player.new_pos) >= 1)
// 	{
// 		return (wall_on_path(cub3d, delta));
// 	}
// 	return (cub3d->level->map[(int)cub3d->player.new_pos.y][(int)cub3d->player.new_pos.x] == WALL
// 		|| is_locked_door(cub3d, (int)cub3d->player.new_pos.y, (int)cub3d->player.new_pos.x) == TRUE);
// }

int	pos_is_goal(cub3d_t *cub3d)
{
	return (cub3d->level->map[(int)cub3d->player.pos.y][(int)cub3d->player.pos.x] == 'G');
}

// int	corner_collision(cub3d_t *cub3d)
// {
// 	return ((cub3d->level->map[(int)cub3d->player.new_pos.y][(int)cub3d->player.pos.x] == WALL
// 		|| is_locked_door(cub3d, (int)cub3d->player.new_pos.y, (int)cub3d->player.pos.x))
// 		&& (cub3d->level->map[(int)cub3d->player.pos.y][(int)cub3d->player.new_pos.x] == WALL
// 		|| is_locked_door(cub3d, (int)cub3d->player.pos.y, (int)cub3d->player.new_pos.x)));
// }

void	collision_checker(cub3d_t *cub3d)
{
	dvector_t	delta;
	int			wall;

	delta.x = cub3d->player.new_pos.x - cub3d->player.pos.x;
	delta.y = cub3d->player.new_pos.y - cub3d->player.pos.y;
	wall = find_end_point(cub3d, &cub3d->player,
			cub3d->player.movement_angle, cub3d->player.new_pos);
	if (wall)
	{
		printf("wall: %d\n", wall);
		// wall = find_end_point(cub3d, &cub3d->player,
		// 		cub3d->player.movement_angle, cub3d->player.new_pos);
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
	// else if (corner_collision(cub3d))
	// 	cub3d->player.new_pos = cub3d->player.pos;
	else
		cub3d->player.pos = cub3d->player.new_pos;
	item_collected_checker(cub3d);
	if (pos_is_goal(cub3d))
	{
		if (cub3d->player.thrown)
			cub3d->level->distractions[cub3d->level->num_distractions].img_distraction->instances[0].enabled = FALSE;
		level_finished(cub3d);
	}
}
