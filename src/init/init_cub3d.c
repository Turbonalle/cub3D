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

	if (cub3d->rays)
		free(cub3d->rays);
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
	while (cub3d->level->map[i])
	{
		j = 0;
		while (cub3d->level->map[i][j])
		{
			if (cub3d->level->map[i][j] == 'm')
				cub3d->level->num_distractions++;
			j++;
		}
		i++;
	}
}

void	init_timer(cub3d_t *cub3d)
{
	cub3d->timer.pos.x = cub3d->img->width * 0.95;
	cub3d->timer.pos.y = cub3d->img->height * 0.05;
}

static void	set_init_stats(cub3d_t *cub3d)
{
	cub3d->state = STATE_START;
	cub3d->active = 1;
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

int	init_cub3d(cub3d_t *cub3d)
{
	int i;

	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", TRUE);
	if (!cub3d->mlx)
		return (!err("Failed to initialize mlx"));
	cub3d->img = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->img || (mlx_image_to_window(cub3d->mlx, cub3d->img, 0, 0) < 0))
		return (!err("Failed to create image"));
	printf("Created main image\n");
	cub3d->rays = NULL;
	if (!init_rays(cub3d))
		return (!err("Failed to malloc rays"));
	set_keys(&cub3d->keys);
	set_init_stats(cub3d);
	init_start_menu(cub3d, &cub3d->start_menu);
	init_level_menu(cub3d, &cub3d->level_menu);
	init_name_menu(cub3d, &cub3d->name_menu);
	init_gameover_menu(cub3d, &cub3d->gameover_menu);
	if (!init_hearts(cub3d))
		return (err("Failed to init hearts"));
	init_halo(cub3d);
	init_timer(cub3d);
	cub3d->distraction_texture = mlx_load_png(TEXTURE_MUSHROOM);
	if (!cub3d->distraction_texture)
		return (err("Failed to load mushroom texture"));
	else
		printf("Loaded mushroom texture\n");
	init_pause_menu(cub3d, &cub3d->pause_menu);
	i = -1;
	while (++i < LEVELS + 1)
		cub3d->levels[i].records = NULL;
	cub3d->start_timestamp = mlx_get_time();
	return (SUCCESS);
}
