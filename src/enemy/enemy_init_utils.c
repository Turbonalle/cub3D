/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 22:19:42 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/16 22:24:39 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	init_enemy_texture_from_path(mlx_texture_t **frame, int i, char *path)
{
	char	*file_path;

	file_path = create_file_path(i, path);
	if (!file_path)
		return (FAIL);
	*frame = mlx_load_png(file_path);
	if (!(*frame))
	{
		free(file_path);
		return (FAIL);
	}
	free(file_path);
	return (SUCCESS);
}

int	init_frame_group(mlx_texture_t **frames_array, char *path)
{
	int	i;

	i = 0;
	while (i < NUM_FRAMES_ENEMY_IDLE)
	{
		if (init_enemy_texture_from_path(&frames_array[i], i, path) == FAIL)
		{
			while (i)
				mlx_delete_texture(frames_array[--i]);
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

static void	init_file_paths(char **idle_file_paths, char **walking_file_paths)
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
}
/* =  {FRAME_PATH_ENEMY_IDLE, FRAME_PATH_ENEMY_IDLE_RIGHT,
FRAME_PATH_ENEMY_IDLE_RIGHT_45, FRAME_PATH_ENEMY_IDLE_STRAIGHT,
FRAME_PATH_ENEMY_IDLE_LEFT_45, FRAME_PATH_ENEMY_IDLE_LEFT}; */
/*  = {FRAME_PATH_ENEMY_WALKING, FRAME_PATH_ENEMY_WALKING_RIGHT,
FRAME_PATH_ENEMY_WALKING_RIGHT_45, FRAME_PATH_ENEMY_WALKING_STRAIGHT,
FRAME_PATH_ENEMY_WALKING_LEFT_45, FRAME_PATH_ENEMY_WALKING_LEFT}; */

int	init_enemy_frames(cub3d_t *cub3d)
{
	int		dir_index;
	int		i;
	char	*idle_file_paths[6];
	char	*walking_file_paths[6];

	init_file_paths(idle_file_paths, walking_file_paths);
	dir_index = 0;
	while (dir_index < NUM_ENEMY_DIRECTIONS)
	{
		if (!init_frame_group(cub3d->frames_idle[dir_index],
				idle_file_paths[dir_index]))
			// TODO: make sure errors are handled
			return (err("Failed to init enemy frames"));
		if (!init_frame_group(cub3d->frames_walking[dir_index],
				walking_file_paths[dir_index]))
		{
			i = 0;
			while (i < NUM_FRAMES_ENEMY_IDLE)
				mlx_delete_texture(cub3d->frames_idle[dir_index][i++]);
			return (err("Failed to init enemy frames"));
		}
		dir_index++;
	}
	return (SUCCESS);
}

int	init_enemy(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	if (cub3d->num_enemies == 0)
		return (1);
	cub3d->enemy = malloc(sizeof(t_enemy) * cub3d->num_enemies);
	if (!cub3d->enemy)
		return (0);
	cub3d->curr_frame_index_idle = 0;
	cub3d->prev_frame_index_idle = 0;
	while (++i < cub3d->num_enemies)
	{
		set_enemy_stats(cub3d, i);
		cub3d->enemy[i].img_curr_frame
			= mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
		if (!cub3d->enemy[i].img_curr_frame)
		{
			while (i)
				mlx_delete_image(cub3d->mlx, cub3d->enemy[--i].img_curr_frame);
			free(cub3d->enemy);
			return (0);
		}
		mlx_image_to_window(cub3d->mlx, cub3d->enemy[i].img_curr_frame, 0, 0);
	}
	return (1);
}
