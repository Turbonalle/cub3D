/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init_additional.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:00:22 by slampine          #+#    #+#             */
/*   Updated: 2024/01/19 14:39:21 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	init_enemy_dir(t_enemy *enemy, int i, char spec)
{
	// printf("init_enemy_dir: enemy[%d]\n", i);
	// printf("init_enemy_dir: spec = %c\n", spec);
	if (spec == 'e' || spec == 'l')
		enemy[i].angle = to_radians(0);
	if (spec == 's' || spec == 'k')
		enemy[i].angle = to_radians(90);
	if (spec == 'w' || spec == 'j')
		enemy[i].angle = to_radians(180);
	if (spec == 'n' || spec == 'i')
		enemy[i].angle = to_radians(270);
	// printf("init_enemy_dir: enemy[%d].angle = %f\n", i, enemy[i].angle);
}

static int	enemy_starting_point(t_cub3d *cub3d, int enemy_i)
{
	int	i;
	int	j;

	i = -1;
	// printf("enemy_starting_point: while (cub3d->level->map[++i])\n");
	while (cub3d->level->map[++i])
	{
		j = -1;
		// printf("enemy_starting_point: while (cub3d->level->map[%d][++j])\n", i);
		while (cub3d->level->map[i][++j])
		{
			// printf("enemy_starting_point: if (ft_strchr(ENEMIES, cub3d->level->map[%d][%d]))\n", i, j);
			if (ft_strchr(ENEMIES, cub3d->level->map[i][j]))
			{
				// printf("enemy_starting_point: cub3d->enemy[%d].pos.x = j + 0.5\n", enemy_i);
				cub3d->enemy[enemy_i].pos.x = j + 0.5;
				cub3d->enemy[enemy_i].pos.y = i + 0.5;
				// printf("enemy_starting_point: init_enemy_dir()\n");
				init_enemy_dir(cub3d->enemy, enemy_i, cub3d->level->map[i][j]);
				// printf("enemy_starting_point: if (ft_strchr(\"ijkl\", cub3d->level->map[%d][%d]))\n", i, j);
				if (ft_strchr("ijkl", cub3d->level->map[i][j]))
				{
					// printf("enemy_starting_point: cub3d->level->map[%d][%d] = 'h'\n", i, j);
					cub3d->level->map[i][j] = 'h';
				}
				else
				{
					// printf("enemy_starting_point: cub3d->level->map[%d][%d] = '0'\n", i, j);
					cub3d->level->map[i][j] = '0';
				}
				// printf("enemy_starting_point: return (SUCCESS)\n");
				return (SUCCESS);
			}
		}
	}
	// printf("enemy_starting_point: return (FAIL)\n");
	return (FAIL);
}

void	set_enemy_stats(t_cub3d *cub3d, int i)
{
	// printf("set_enemy_stats: enemy[%d]\n", i);
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
	// printf("set_enemy_stats: enemy[%d] init_frames()\n", i);
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
	walking_file_paths[0] = FRAME_PATH_WALKING;
	walking_file_paths[1] = FRAME_PATH_WALKING_RIGHT;
	walking_file_paths[2] = FRAME_PATH_WALKING_RIGHT_45;
	walking_file_paths[3] = FRAME_PATH_WALKING_STRAIGHT;
	walking_file_paths[4] = FRAME_PATH_WALKING_LEFT_45;
	walking_file_paths[5] = FRAME_PATH_WALKING_LEFT;
	hunting_file_paths[0] = FRAME_PATH_HUNTING;
	hunting_file_paths[1] = FRAME_PATH_HUNTING_RIGHT;
	hunting_file_paths[2] = FRAME_PATH_HUNTING_RIGHT_45;
	hunting_file_paths[3] = FRAME_PATH_HUNTING_STRAIGHT;
	hunting_file_paths[4] = FRAME_PATH_HUNTING_LEFT_45;
	hunting_file_paths[5] = FRAME_PATH_HUNTING_LEFT;
}
