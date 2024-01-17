/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init_additional.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:00:22 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 00:14:21 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	init_enemy_dir(t_enemy *enemy, int i, char spec)
{
	if (spec == 'e' || spec == 'l')
		enemy[i].angle = to_radians(0);
	if (spec == 's' || spec == 'k')
		enemy[i].angle = to_radians(90);
	if (spec == 'w' || spec == 'j')
		enemy[i].angle = to_radians(180);
	if (spec == 'n' || spec == 'i')
		enemy[i].angle = to_radians(270);
}

static int	enemy_starting_point(cub3d_t *cub3d, int enemy_i)
{
	int	i;
	int	j;

	i = -1;
	while (cub3d->level->map[++i])
	{
		j = -1;
		while (cub3d->level->map[i][++j])
		{
			if (ft_strchr(ENEMIES, cub3d->level->map[i][j]))
			{
				cub3d->enemy[enemy_i].pos.x = j + 0.5;
				cub3d->enemy[enemy_i].pos.y = i + 0.5;
				init_enemy_dir(cub3d->enemy, enemy_i, cub3d->level->map[i][j]);
				if (ft_strchr("ijkl", cub3d->level->map[i][j]))
					cub3d->level->map[i][j] = 'h';
				else
					cub3d->level->map[i][j] = '0';
				return (SUCCESS);
			}
		}
	}
	return (FAIL);
}

void	set_enemy_stats(cub3d_t *cub3d, int i)
{
	cub3d->enemy[i].dir_player = 0;
	cub3d->enemy[i].is_spinning = 0;
	cub3d->enemy[i].is_walking = 0;
	cub3d->enemy[i].is_eating = 0;
	cub3d->enemy[i].is_hunting = FALSE;
	cub3d->enemy[i].dir.x = 0;
	cub3d->enemy[i].dir.y = 0;
	cub3d->enemy[i].freeze_start = 0;
	cub3d->enemy[i].pos_screen.x = -WIDTH;
	cub3d->enemy[i].pos_screen.y = -HEIGHT;
	cub3d->enemy[i].state = IDLE;
	cub3d->enemy[i].visible = FALSE;
	cub3d->enemy[i].dist_to_player = 100;
	enemy_starting_point(cub3d, i);
}

void	init_file_paths(char **idle_file_paths, char **walking_file_paths,
	char **hunting_file_paths)
{
	idle_file_paths[0] = FRAME_PATH_ENEMY_IDLE;
	idle_file_paths[1] = FRAME_PATH_ENEMY_IDLE_RIGHT;
	idle_file_paths[2] = FRAME_PATH_ENEMY_IDLE_RIGHT_45;
	idle_file_paths[3] = FRAME_PATH_ENEMY_IDLE_STRAIGHT;
	idle_file_paths[4] = FRAME_PATH_ENEMY_IDLE_LEFT_45;
	idle_file_paths[5] = FRAME_PATH_ENEMY_IDLE_LEFT;
	walking_file_paths[0] = FRAME_PATH_ENEMY_WALKING;
	walking_file_paths[1] = FRAME_PATH_ENEMY_WALKING_RIGHT;
	walking_file_paths[2] = FRAME_PATH_ENEMY_WALKING_RIGHT_45;
	walking_file_paths[3] = FRAME_PATH_ENEMY_WALKING_STRAIGHT;
	walking_file_paths[4] = FRAME_PATH_ENEMY_WALKING_LEFT_45;
	walking_file_paths[5] = FRAME_PATH_ENEMY_WALKING_LEFT;
	hunting_file_paths[0] = FRAME_PATH_ENEMY_HUNTING;
	hunting_file_paths[1] = FRAME_PATH_ENEMY_HUNTING_RIGHT;
	hunting_file_paths[2] = FRAME_PATH_ENEMY_HUNTING_RIGHT_45;
	hunting_file_paths[3] = FRAME_PATH_ENEMY_HUNTING_STRAIGHT;
	hunting_file_paths[4] = FRAME_PATH_ENEMY_HUNTING_LEFT_45;
	hunting_file_paths[5] = FRAME_PATH_ENEMY_HUNTING_LEFT;
}
