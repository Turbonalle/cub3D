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

int	init_enemy_frames(cub3d_t *cub3d)
{
	int		i;
	char	*file_path;

	i = 0;
	while (i < NUM_FRAMES_ENEMY_IDLE)
	{
		file_path = create_file_path(i, FRAME_PATH_ENEMY_IDLE);
		if (!file_path)
		{
			while (i)
				mlx_delete_texture(cub3d->frames_idle[--i]);
			return (0);
		}
		cub3d->frames_idle[i] = mlx_load_png(file_path);
		free(file_path);
		if (!cub3d->frames_idle[i])
		{
			while (i)
				mlx_delete_texture(cub3d->frames_idle[--i]);
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < NUM_FRAMES_ENEMY_WALKING)
	{
		file_path = create_file_path(i, FRAME_PATH_ENEMY_WALKING);
		if (!file_path)
		{
			while (i)
				mlx_delete_texture(cub3d->frames_walking[--i]);
			i = 0;
			while (i < NUM_FRAMES_ENEMY_IDLE)
				mlx_delete_texture(cub3d->frames_idle[i++]);
			return (0);
		}
			cub3d->frames_walking[i] = mlx_load_png(file_path);
		free(file_path);
		if (!cub3d->frames_walking[i])
		{
			while (i)
				mlx_delete_texture(cub3d->frames_walking[--i]);
			i = 0;
			while (i < NUM_FRAMES_ENEMY_IDLE)
				mlx_delete_texture(cub3d->frames_idle[i++]);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	set_enemy_stats(cub3d_t *cub3d, int i)
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
}

int	init_enemy(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	if (cub3d->num_enemies == 0)
		return (1);
	cub3d->enemy = malloc(sizeof(t_enemy) * cub3d->num_enemies);
	if (!cub3d->enemy)
		return (0);
	cub3d->curr_frame_index_idle = 0;
	cub3d->prev_frame_index_idle = 0;
	while (i < cub3d->num_enemies)
	{
		enemy_starting_point(cub3d, i);
		set_enemy_stats(cub3d, i);
		cub3d->enemy[i].dist_to_player = 100;
		cub3d->enemy[i].img_curr_frame
			= mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
		if (!cub3d->enemy[i].img_curr_frame)
		{
			while (i)
			{
				mlx_delete_image(cub3d->mlx, cub3d->enemy[--i].img_curr_frame);
			}
			free(cub3d->enemy);
			return (0);
		}
		mlx_image_to_window(cub3d->mlx, cub3d->enemy[i].img_curr_frame, 0, 0);
		i++;
	}
	return (1);
}
