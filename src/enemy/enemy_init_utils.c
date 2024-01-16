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
	//printf("init_frame_group\n");
	while (i < NUM_FRAMES_ENEMY_IDLE)
	{
		//printf("init_frame_group i: %d\n", i);
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

int	init_enemy_frames(cub3d_t *cub3d)
{
	int		dir_index;
	int		i;

	char	*idle_file_paths[] = {FRAME_PATH_ENEMY_IDLE, FRAME_PATH_ENEMY_IDLE_RIGHT, FRAME_PATH_ENEMY_IDLE_RIGHT_45, FRAME_PATH_ENEMY_IDLE_STRAIGHT, FRAME_PATH_ENEMY_IDLE_LEFT_45, FRAME_PATH_ENEMY_IDLE_LEFT};
	char	*walking_file_paths[] = {FRAME_PATH_ENEMY_WALKING, FRAME_PATH_ENEMY_WALKING_RIGHT, FRAME_PATH_ENEMY_WALKING_RIGHT_45, FRAME_PATH_ENEMY_WALKING_STRAIGHT, FRAME_PATH_ENEMY_WALKING_LEFT_45, FRAME_PATH_ENEMY_WALKING_LEFT};
	// char	*hunting_file_paths[] = {FRAME_PATH_ENEMY_HUNTING, FRAME_PATH_ENEMY_HUNTING_LEFT, FRAME_PATH_ENEMY_HUNTING_LEFT_45, FRAME_PATH_ENEMY_HUNTING_RIGHT, FRAME_PATH_ENEMY_HUNTING_RIGHT_45, FRAME_PATH_ENEMY_HUNTING_STRAIGHT};
	//printf("init_enemy_frames\n");
	dir_index = 0;
	while (dir_index < NUM_ENEMY_DIRECTIONS)
	{
		//printf("init_enemy_frames dir_index: %d\n", dir_index);
		if (!init_frame_group(cub3d->frames_idle[dir_index], idle_file_paths[dir_index]))
		{
			// TODO: handle errors
			return (err("Failed to init enemy frames"));
		}
		if (!init_frame_group(cub3d->frames_walking[dir_index], walking_file_paths[dir_index]))
		{
			i = 0;
			while (i < NUM_FRAMES_ENEMY_IDLE)
				mlx_delete_texture(cub3d->frames_idle[dir_index][i++]);
			// TODO: handle errors
			return (err("Failed to init enemy frames"));
		}
		// if (!init_frame_group(cub3d->frames_hunt_paths[dir_index], hunting_file_paths[dir_index]))
		// {
		// 	i = 0;
		// 	while (i < NUM_FRAMES_ENEMY_IDLE)
		// 	{
		// 		mlx_delete_texture(cub3d->frames_walking[dir_index][i]);
		// 		mlx_delete_texture(cub3d->frames_idle[dir_index][i]);
		// 		i++;
		// 	}
		// }
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
