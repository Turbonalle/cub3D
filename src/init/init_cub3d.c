#include "../incl/cub3d.h"

int	count_minimap_tilesize(cub3d_t *cub3d, int size_percentage)
{
	float	tile_size;
	float	minimap_width;
	float	minimap_height;

	minimap_width = (float)cub3d->img->width * (float)size_percentage / 100;
	tile_size = minimap_width / (float)cub3d->level->map_columns;
	minimap_height = (float)cub3d->img->height * (float)size_percentage / 100;
	if (tile_size * (float)cub3d->level->map_rows > minimap_height)
		tile_size = minimap_height / (float)cub3d->level->map_rows;
	return ((int)tile_size);
}

int	init_minimap(cub3d_t *cub3d)
{
	cub3d->minimap.size_percentage = MINIMAP_SIZE_PERCENTAGE;
	cub3d->minimap.tile_size = count_minimap_tilesize(cub3d, cub3d->minimap.size_percentage);
	cub3d->minimap.width = cub3d->minimap.tile_size * cub3d->level->map_columns;
	cub3d->minimap.height = cub3d->minimap.tile_size * cub3d->level->map_rows;
	cub3d->minimap.img = mlx_new_image(cub3d->mlx, cub3d->minimap.width, cub3d->minimap.height);
	if (!cub3d->minimap.img || (mlx_image_to_window(cub3d->mlx, cub3d->minimap.img, 0, 0) < 0))
		return(err("Failed to create minimap image"));
	cub3d->minimap.pos.x = 0;
	cub3d->minimap.pos.y = 0;
	cub3d->orig_minimap_pos.x = 0;
	cub3d->orig_minimap_pos.y = 0;
	cub3d->mouse_set_pos.x = 0;
	cub3d->mouse_set_pos.y = 0;
	cub3d->on_minimap = FALSE;
	cub3d->minimap.transparency = MINIMAP_TRANSPARENCY;
	cub3d->minimap.color_player = set_transparency(MINIMAP_COLOR_PLAYER, cub3d->minimap.transparency);
	cub3d->minimap.color_playerdir = set_transparency(MINIMAP_COLOR_PLAYERDIR, cub3d->minimap.transparency);
	cub3d->minimap.color_fov = set_transparency(MINIMAP_COLOR_FOV, cub3d->minimap.transparency);
	cub3d->minimap.color_floor = set_transparency(MINIMAP_COLOR_FLOOR, cub3d->minimap.transparency);
	cub3d->minimap.color_wall = set_transparency(MINIMAP_COLOR_WALL, cub3d->minimap.transparency);
	cub3d->minimap.color_empty = set_transparency(MINIMAP_COLOR_EMPTY, cub3d->minimap.transparency);
	cub3d->minimap.color_enemy = set_transparency(MINIMAP_COLOR_ENEMY, cub3d->minimap.transparency);
	cub3d->minimap.color_shroom = set_transparency(MINIMAP_COLOR_SHROOM, cub3d->minimap.transparency);
	cub3d->minimap.color_key_1 = set_transparency(MINIMAP_COLOR_KEY_1, cub3d->minimap.transparency);
	cub3d->minimap.color_key_2 = set_transparency(MINIMAP_COLOR_KEY_2, cub3d->minimap.transparency);
	cub3d->minimap.color_key_3 = set_transparency(MINIMAP_COLOR_KEY_3, cub3d->minimap.transparency);
	cub3d->minimap.color_key_4 = set_transparency(MINIMAP_COLOR_KEY_4, cub3d->minimap.transparency);
	return (1);
}

void	set_initial_direction(cub3d_t *cub3d)
{
	if (cub3d->level->starting_dir == 'E')
		cub3d->player.angle = to_radians(0);
	else if (cub3d->level->starting_dir == 'S')
		cub3d->player.angle = to_radians(90);
	else if (cub3d->level->starting_dir == 'W')
		cub3d->player.angle = to_radians(180);
	else if (cub3d->level->starting_dir == 'N')
		cub3d->player.angle = to_radians(270);
	cub3d->player.dir.x = cos(cub3d->player.angle);
	cub3d->player.dir.y = sin(cub3d->player.angle);
}

void	set_keys(keypress_t *keys)
{
	keys->q = FALSE;
	keys->w = FALSE;
	keys->e = FALSE;
	keys->r = FALSE;
	keys->t = FALSE;
	keys->y = FALSE;
	keys->u = FALSE;
	keys->i = FALSE;
	keys->o = FALSE;
	keys->p = FALSE;
	keys->a = FALSE;
	keys->s = FALSE;
	keys->d = FALSE;
	keys->f = FALSE;
	keys->g = FALSE;
	keys->h = FALSE;
	keys->j = FALSE;
	keys->k = FALSE;
	keys->l = FALSE;
	keys->z = FALSE;
	keys->x = FALSE;
	keys->c = FALSE;
	keys->v = FALSE;
	keys->b = FALSE;
	keys->n = FALSE;
	keys->m = FALSE;
	keys->space = FALSE;
	keys->shift = FALSE;
	keys->enter = FALSE;
	keys->escape = FALSE;
	keys->backspace = FALSE;
	keys->up = FALSE;
	keys->down = FALSE;
	keys->left = FALSE;
	keys->right = FALSE;
	keys->mouse_left = FALSE;
	keys->mouse_right = FALSE;
}

int	init_rays(cub3d_t *cub3d)
{
	int	i;

	cub3d->rays = malloc(sizeof(ray_t) * WIDTH);
	if (!cub3d->rays)
		return (FAIL);
	i = -1;
	while (++i < (int)cub3d->img->width)
	{
		cub3d->rays[i].end.x = 0;
		cub3d->rays[i].end.y = 0;
		cub3d->rays[i].angle = 0;
		cub3d->rays[i].length = 0;
		cub3d->rays[i].target = 0;
		cub3d->rays[i].wall = 0;
		cub3d->rays[i].door_dir = 0;
	}
	return (SUCCESS);
}

void	count_enemies(cub3d_t *cub3d)
{
	int	i;
	int	j;

	i = 0;
	cub3d->num_enemies = 0;
	while (cub3d->level->map[i])
	{
		j = 0;
		while (cub3d->level->map[i][j])
		{
			if (ft_strchr(ENEMIES, cub3d->level->map[i][j]))
				cub3d->num_enemies++;
			j++;
		}
		i++;
	}
}

void	count_distractions(cub3d_t *cub3d)
{
	int	i;
	int	j;

	i = 0;
	cub3d->level->num_distractions = 0;
	//cub3d->level->num_poison = 0;
	while (cub3d->level->map[i])
	{
		j = 0;
		while (cub3d->level->map[i][j])
		{
			if (cub3d->level->map[i][j] == 'm' || cub3d->level->map[i][j] == 'r')
				cub3d->level->num_distractions++;
			/* else if (cub3d->level->map[i][j] == 'p')
				cub3d->level->num_poison++; */
			j++;
		}
		i++;
	}
}

void	init_timer(cub3d_t *cub3d)
{
	cub3d->timer.pos.x = cub3d->img->width * 0.96;
	cub3d->timer.pos.y = cub3d->img->height * 0.05;
}

static void	set_init_stats(cub3d_t *cub3d)
{
	cub3d->state = STATE_START;
	cub3d->mouse_set_pos.x = 0;
	cub3d->mouse_set_pos.y = 0;
	cub3d->on_minimap = FALSE;
	cub3d->fov = FOV;
	cub3d->n_levels = LEVELS;
	cub3d->num_enemies = 0;
	cub3d->leaderboard.n_entries = N_ENTRIES;
	cub3d->speedrun = FALSE;
	cub3d->player.health = HEARTS;
	cub3d->player.mushroom_count = 0;
	cub3d->player.hit_timestamp = 0;
}

static void	free_levels(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i < LEVELS + 1)
	{
		free_list(cub3d->levels[i].map_list);
		free_backup(cub3d->levels[i]);
		i++;
	}
	free(cub3d->levels);
}

void	free_start_menu(start_menu_t *menu)
{
	if (menu->title.texture)
		mlx_delete_texture(menu->title.texture);
	if (menu->exit.texture)
		mlx_delete_texture(menu->exit.texture);
	if (menu->start.texture)
		mlx_delete_texture(menu->start.texture);
	if (menu->level.texture)
		mlx_delete_texture(menu->level.texture);
	if (menu->exit_hover.texture)
		mlx_delete_texture(menu->exit_hover.texture);
	if (menu->start_hover.texture)
		mlx_delete_texture(menu->start_hover.texture);
	if (menu->level_hover.texture)
		mlx_delete_texture(menu->level_hover.texture);
	if (menu->arrow_exit.texture)
		mlx_delete_texture(menu->arrow_exit.texture);
	if (menu->arrow_start.texture)
		mlx_delete_texture(menu->arrow_start.texture);
	if (menu->arrow_level.texture)
		mlx_delete_texture(menu->arrow_level.texture);
}

void	free_level_menu(level_menu_t *menu)
{
	int	i;

	i = -1;
	if (menu->title.texture)
		mlx_delete_texture(menu->title.texture);
	if (menu->back.texture)
		mlx_delete_texture(menu->back.texture);
	if (menu->leaderboard.texture)
		mlx_delete_texture(menu->leaderboard.texture);
	if (menu->back_hover.texture)
		mlx_delete_texture(menu->back_hover.texture);
	if (menu->leaderboard_hover.texture)
		mlx_delete_texture(menu->leaderboard_hover.texture);
	while (++i < LEVELS)
	{
		if (menu->minilevels[i].number.texture)
			mlx_delete_texture(menu->minilevels[i].number.texture);
	}
}

void	free_name_menu(name_menu_t *menu)
{
	if (menu->title_win.texture)
		mlx_delete_texture(menu->title_win.texture);
	if (menu->title_top3.texture)
		mlx_delete_texture(menu->title_top3.texture);
	if (menu->back.texture)
		mlx_delete_texture(menu->back.texture);
	if (menu->back_hover.texture)
		mlx_delete_texture(menu->back_hover.texture);
	if (menu->timer.texture)
		mlx_delete_texture(menu->timer.texture);
}

void	free_gameover_menu(gameover_menu_t *menu)
{
	if (menu->title_win.texture)
		mlx_delete_texture(menu->title_win.texture);
	if (menu->title_gameover.texture)
		mlx_delete_texture(menu->title_gameover.texture);
	if (menu->back.texture)
		mlx_delete_texture(menu->back.texture);
	if (menu->back_hover.texture)
		mlx_delete_texture(menu->back_hover.texture);
	if (menu->restart.texture)
		mlx_delete_texture(menu->restart.texture);
	if (menu->restart_hover.texture)
		mlx_delete_texture(menu->restart_hover.texture);
	if (menu->arrow_back.texture)
		mlx_delete_texture(menu->arrow_back.texture);
	if (menu->arrow_restart.texture)
		mlx_delete_texture(menu->arrow_restart.texture);
	if (menu->timer.texture)
		mlx_delete_texture(menu->timer.texture);
}

void	free_intro(cub3d_t *cub3d)
{
	if (cub3d->intro.texture)
		mlx_delete_texture(cub3d->intro.texture);
}

void	free_hearts(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	while (++i < HEARTS)
	{
		if (cub3d->hearts[i].full.texture)
			mlx_delete_texture(cub3d->hearts[i].full.texture);
		if (cub3d->hearts[i].empty.texture)
			mlx_delete_texture(cub3d->hearts[i].empty.texture);
	}
}

void	free_shroom(cub3d_t *cub3d)
{
	if (cub3d->shroom && cub3d->shroom->shroom.texture)
	{
		printf("shroom needs freeing\n");
		mlx_delete_texture(cub3d->shroom->shroom.texture);
	}
	if (cub3d->shroom)
		free(cub3d->shroom);
	if (cub3d->distraction_texture)
		mlx_delete_texture(cub3d->distraction_texture);
	if (cub3d->distraction_thrown_texture)
		mlx_delete_texture(cub3d->distraction_thrown_texture);
}

void	free_door_textures(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (cub3d->door[i].texture)
			mlx_delete_texture(cub3d->door[i].texture);
		i++;
	}
}

void	free_star_textures(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i < NUM_FRAMES_STARS)
	{
		if (cub3d->stars[i].texture)
			mlx_delete_texture(cub3d->stars[i].texture);
		if (cub3d->stars[i].path)
			free(cub3d->stars[i].path);
		i++;
	}
}

void	free_pause_menu(pause_menu_t *menu)
{
	if (menu->title.texture)
		mlx_delete_texture(menu->title.texture);
}

void	free_leaderboard(leaderboard_t *board)
{
	if (board->title.texture)
		mlx_delete_texture(board->title.texture);
	if (board->back.texture)
		mlx_delete_texture(board->back.texture);
	if (board->back_hover.texture)
		mlx_delete_texture(board->back_hover.texture);
}

void	free_enemy_frames(cub3d_t *cub3d)
{
	int	j;
	int	i;

	j = 0;
	while (j < NUM_ENEMY_DIRECTIONS)
	{
		i = 0;
		while (i < NUM_FRAMES_ENEMY_IDLE)
		{
			if (cub3d->frames_idle[j][i])
				mlx_delete_texture(cub3d->frames_idle[j][i]);
			i++;
		}
		i = 0;
		while (i < NUM_FRAMES_ENEMY_WALKING)
		{
			if (cub3d->frames_walking[j][i])
				mlx_delete_texture(cub3d->frames_walking[j][i]);
				i++;
		}
		j++;
	}
}

int	handle_message_extra(int i)
{
	if (i == 12)
		return (err("Failed to load mushroom texture"));
	if (i == 13)
		return (err("Failed to load door textures"));
	if (i == 14)
		return (err("Failed to load goal textures"));
	if (i == 15)
		return (err("Failed to init pause menu"));
	if (i == 16)
		return (err("Failed to read records"));
	if (i == 17)
		return (err("Failed to init leaderboard"));
	if (i == 18)
		return (err("Failed to init enemy_frames"));
	if (i == 19)
		return (err("Failed to init floor"));
	return (1);
}

int handle_message(int i)
{
	if (i == 0)
		return (err("Failed to initialize mlx"));
	if (i == 1)
		return (err("Failed to create image"));
	if (i == 2)
		return (err("Failed to malloc rays"));
	if (i == 3)
		return (err("Failed to init start menu"));
	if (i == 4)
		return (err("Failed to init level menu"));
	if (i == 5)
		return (err("Failed to init name menu"));
	if (i == 6)
		return (err("Failed to init gameover menu"));
	if (i == 7)
		return (err("Failed to init intro"));
	if (i == 8)
		return (err("Failed to init hearts"));
	if (i == 9)
		return (err("Failed to init shroom counter"));
	if (i == 10)
		return (err("Failed to init halo"));
	if (i == 11)
		return (err("Failed to load mushroom thrown texture"));
	return(handle_message_extra(i));
}

int	free_all(cub3d_t *cub3d, int i)
{
	//TODO: handle shrooms 
	free_records(cub3d);
	printf("after free records\n");
	free_levels(cub3d);
	if (cub3d->rays)
		free(cub3d->rays);
	free_start_menu(&cub3d->start_menu);
	free_level_menu(&cub3d->level_menu);
	free_name_menu(&cub3d->name_menu);
	free_gameover_menu(&cub3d->gameover_menu);
	free_intro(cub3d);
	printf("before free hearts\n");
	free_hearts(cub3d);
	printf("after free hearts\n");
	free_shroom(cub3d);
	printf("after free shroom\n");
	free_door_textures(cub3d);
	printf("after free doors\n");
	free_star_textures(cub3d);
	printf("after free stars\n");
	free_pause_menu(&cub3d->pause_menu);
	printf("after free pause menu\n");
	free_leaderboard(&cub3d->leaderboard);
	printf("after free leaderboard\n");
	free_enemy_frames(cub3d);
	if (cub3d->floor.texture)
		mlx_delete_texture(cub3d->floor.texture);
	printf("after deleting floor texture\n");
	
	return (handle_message(i));
}

int	init_cub3d(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	while (++i < LEVELS + 1)
		cub3d->levels[i].records = NULL;
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", FALSE);
	if (!cub3d->mlx)
		return (free_all(cub3d, 0));
	cub3d->img = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->img || (mlx_image_to_window(cub3d->mlx, cub3d->img, 0, 0) < 0))
		return (free_all(cub3d, 1));
	printf("Created main image\n");
	if (!init_rays(cub3d))
		return (free_all(cub3d, 2));
	set_keys(&cub3d->keys);
	set_init_stats(cub3d);
	printf("init start menu\n");
	if (!init_start_menu(cub3d, &cub3d->start_menu))
		return (free_all(cub3d, 3));
	printf("init level menu\n");
	if (!init_level_menu(cub3d, &cub3d->level_menu))
		return (free_all(cub3d, 4));
	printf("init name menu\n");
	if (!init_name_menu(cub3d, &cub3d->name_menu))
		return (free_all(cub3d, 5));
	if (!init_gameover_menu(cub3d, &cub3d->gameover_menu))
		return (free_all(cub3d, 6));
	if (!init_intro(cub3d))
		return (free_all(cub3d, 7));
	if (!init_hearts(cub3d))
		return (free_all(cub3d, 8));
	printf("after init hearts\n");
	if (!init_shroom(cub3d))
		return (free_all(cub3d, 9));
	if (!init_halo(cub3d))
		return (free_all(cub3d, 10));
	init_timer(cub3d);
	cub3d->distraction_thrown_texture = mlx_load_png(TEXTURE_MUSHROOM_THROWN);
	if (!cub3d->distraction_thrown_texture)
		return (free_all(cub3d, 11));
	cub3d->distraction_texture = mlx_load_png(TEXTURE_MUSHROOM);
	if (!cub3d->distraction_texture)
		return (free_all(cub3d, 12));
	if (!init_door_textures(cub3d))
		return (free_all(cub3d, 13));
	if (!init_stars_textures(cub3d))
		return (free_all(cub3d, 14));
	if (!init_pause_menu(cub3d, &cub3d->pause_menu))
		return (free_all(cub3d, 15));
	cub3d->start_timestamp = mlx_get_time();
	cub3d->prev_frame_update_timestamp = 0;
	cub3d->player.num_completed = 0;
	return (SUCCESS);
}
