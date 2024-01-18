/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:59:50 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:15:34 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	init_enemy_texture_from_path(mlx_texture_t **frame, int i,
	char *path)
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

static int	init_frame_group(mlx_texture_t **frames_array, char *path)
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

int	init_enemy_frames(t_cub3d *cub3d)
{
	int		dir_index;
	char	*idle_file_paths[6];
	char	*walking_file_paths[6];
	char	*hunting_file_paths[6];

	init_file_paths(idle_file_paths, walking_file_paths, hunting_file_paths);
	dir_index = 0;
	while (dir_index < NUM_ENEMY_DIRECTIONS)
	{
		if (!init_frame_group(cub3d->frames_idle[dir_index],
				idle_file_paths[dir_index]))
			return (err("Failed to init enemy frames"));
		if (!init_frame_group(cub3d->frames_walking[dir_index],
				walking_file_paths[dir_index]))
			return (free_enemy_frames(cub3d),
				err("Failed to init enemy frames"));
		if (!init_frame_group(cub3d->frames_hunting[dir_index],
				hunting_file_paths[dir_index]))
			return (free_enemy_frames(cub3d),
				err("Failed to init enemy frames"));
		dir_index++;
	}
	return (SUCCESS);
}

static void	init_frame_indexes(t_cub3d *cub3d)
{
	cub3d->curr_frame_index_idle = 0;
	cub3d->prev_frame_index_idle = 0;
	cub3d->curr_frame_index_walking = 0;
	cub3d->prev_frame_index_walking = 0;
	cub3d->curr_frame_index_hunting = 0;
	cub3d->prev_frame_index_hunting = 0;
}

int	init_enemy(t_cub3d *cub3d)
{
	int	i;

	i = -1;
	if (cub3d->num_enemies == 0)
		return (SUCCESS);
	cub3d->enemy = malloc(sizeof(t_enemy) * cub3d->num_enemies);
	if (!cub3d->enemy)
		return (FAIL);
	init_frame_indexes(cub3d);
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
			return (FAIL);
		}
		mlx_image_to_window(cub3d->mlx, cub3d->enemy[i].img_curr_frame, 0, 0);
	}
	return (SUCCESS);
}
