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

void	init_minimap(cub3d_t *cub3d)
{
	cub3d->minimap.size_percentage = MINIMAP_SIZE_PERCENTAGE;
	cub3d->minimap.tile_size = count_minimap_tilesize(cub3d, cub3d->minimap.size_percentage);
	cub3d->minimap.width = cub3d->minimap.tile_size * cub3d->level->map_columns;
	cub3d->minimap.height = cub3d->minimap.tile_size * cub3d->level->map_rows;
	cub3d->minimap.img = mlx_new_image(cub3d->mlx, cub3d->minimap.width, cub3d->minimap.height);
	if (!cub3d->minimap.img || (mlx_image_to_window(cub3d->mlx, cub3d->minimap.img, 0, 0) < 0))
		err("Failed to create minimap image");
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
	cub3d->minimap.color_key_1 = set_transparency(MINIMAP_COLOR_KEY_1, cub3d->minimap.transparency);
	cub3d->minimap.color_key_2 = set_transparency(MINIMAP_COLOR_KEY_2, cub3d->minimap.transparency);
	cub3d->minimap.color_key_3 = set_transparency(MINIMAP_COLOR_KEY_3, cub3d->minimap.transparency);
	cub3d->minimap.color_key_4 = set_transparency(MINIMAP_COLOR_KEY_4, cub3d->minimap.transparency);
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
	keys->fisheye = FALSE;	// WHAT IS THIS FOR?
}

int	init_rays(cub3d_t *cub3d)
{
	int	i;

	// If screen has been resized, we free first want to free the old rays
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

int add_key(cub3d_t *cub3d, int i, int j, int key_group_index)
{
	key_node_t	*new_key;

	new_key = malloc(sizeof(key_node_t));
	if (!new_key)
		return (FAIL);
	new_key->pos.x = j;
	new_key->pos.y = i;
	new_key->collected = FALSE;
	new_key->next = cub3d->level->key_groups[key_group_index].keys;
	cub3d->level->key_groups[key_group_index].keys = new_key;
	return (SUCCESS); 
}

int	init_key(cub3d_t *cub3d, int i, int j, int key_group_index)
{
	if (add_key(cub3d, i, j, key_group_index) == FAIL)
		return (FAIL);
	cub3d->level->door_groups[key_group_index].num_keys_left++;
	cub3d->level->key_groups[key_group_index].num_keys_total++;
	draw_key_counts(cub3d);
	return (SUCCESS);
}

int add_door_pos(cub3d_t *cub3d, int i, int j, int door_group_index)
{
	door_pos_t	*new_pos;

	new_pos = malloc(sizeof(door_pos_t));
	if (!new_pos)
		return (FAIL);
	new_pos->pos.x = j;
	new_pos->pos.y = i;
	new_pos->next = cub3d->level->door_groups[door_group_index].door_positions;
	cub3d->level->door_groups[door_group_index].door_positions = new_pos;
	return (SUCCESS);
}

int	init_door(cub3d_t *cub3d, int i, int j, int door_group_index)
{
	cub3d->level->door_groups[door_group_index].index = door_group_index;
	if (add_door_pos(cub3d, i, j, door_group_index) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	get_key_index(char symbol)
{
	int	res;

	res = symbol - 'a';
	if (res < 0 || res >= NUM_DOORS_MAX)
		return (-1);
	return res;
}

int	get_door_index(char symbol)
{
	int	res;

	res = symbol - 'A';
	if (res < 0 || res >= NUM_DOORS_MAX)
		return (-1);
	return res;
}

int	init_key_frames(cub3d_t *cub3d, key_group_t *key_group)
{
	int 	i;
	char	*file_path;
	char	*file_name;
	char	*file_name_extension;
	
	printf("init_key_frames called\n");
	key_group->num_frames = NUM_FRAMES_KEY;
	key_group->curr_frame = 0;
	// TODO: protect mallocs
	key_group->textures_frames = malloc(sizeof(mlx_texture_t *) * NUM_FRAMES_KEY);
	key_group->frames = malloc(sizeof(mlx_image_t *) * NUM_FRAMES_KEY);
	i = 0;
	while (i < NUM_FRAMES_KEY)
	{
		//TODO: protect mallocs
		file_name = ft_itoa(i + 1);
		file_name_extension = ft_strjoin(file_name, ".png");
		file_path = ft_strjoin(key_group->texture_dir, file_name_extension);
		printf("full file path: %s\n", file_path);
		key_group->textures_frames[i] = mlx_load_png(file_path);
		key_group->frames[i] = mlx_texture_to_image(cub3d->mlx, key_group->textures_frames[i]);
		mlx_image_to_window(cub3d->mlx, key_group->frames[i], 500, 500);
		key_group->frames[i]->instances[0].enabled = false;
		free(file_name);
		free(file_name_extension);
		free(file_path);
		i++;
	}
	return 1;
}

int	init_doors_and_keys(cub3d_t *cub3d)
{
	int	i;
	int	j;
	int	door_key_index;

	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		cub3d->level->door_groups[i].index = i;
		cub3d->level->door_groups[i].door_positions = NULL;
		cub3d->level->door_groups[i].num_keys_left = 0;

		cub3d->level->key_groups[i].index = i;
		cub3d->level->key_groups[i].keys = NULL;
		cub3d->level->key_groups[i].num_keys_total = 0;
		cub3d->level->key_groups[i].curr_frame = 0;
		cub3d->level->key_groups[i].num_frames = 0;
		cub3d->level->key_groups[i].frames = NULL;
		cub3d->level->key_groups[i].img_key_icon = NULL;
		cub3d->level->key_groups[i].img_text_key_count = NULL;
		cub3d->level->key_groups[i].textures_frames = NULL;
		cub3d->level->key_groups[i].texture_key_icon = NULL;
		i++;
	}
	i = 0;
	while (cub3d->level->map[i])
	{
		j = 0;
		while (cub3d->level->map[i][j])
		{
			door_key_index = get_door_index(cub3d->level->map[i][j]);
			if (door_key_index != -1)
			{
				if (init_door(cub3d, i, j, door_key_index) == FAIL)
					return (FAIL);
			}
			door_key_index = get_key_index(cub3d->level->map[i][j]);
			if (door_key_index != -1)
			{
				if (init_key(cub3d, i, j, door_key_index) == FAIL)
					return (FAIL);
			}
			j++;
		}
		i++;
	}
	int	active_key_groups;
	active_key_groups = 0;
	cub3d->level->key_groups[0].texture_key_icon = mlx_load_png(TEXTURE_KEY_1);
	cub3d->level->key_groups[1].texture_key_icon = mlx_load_png(TEXTURE_KEY_2);
	cub3d->level->key_groups[2].texture_key_icon = mlx_load_png(TEXTURE_KEY_3);
	cub3d->level->key_groups[3].texture_key_icon = mlx_load_png(TEXTURE_KEY_4);
	cub3d->level->key_groups[0].texture_dir = FRAME_PATH_KEY_1;
	cub3d->level->key_groups[1].texture_dir = FRAME_PATH_KEY_2;
	cub3d->level->key_groups[2].texture_dir = FRAME_PATH_KEY_3;
	cub3d->level->key_groups[3].texture_dir = FRAME_PATH_KEY_4;
	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		// Count keys
		key_node_t *temp = cub3d->level->key_groups[i].keys;
		int count = 0;
		while (temp)
		{
			temp = temp->next;
			count++;
		}
		cub3d->level->key_groups[i].num_keys_total = count;
		// Create key image if needed
		if (count)
		{
			cub3d->level->key_groups[i].key_icon_coords.x = cub3d->mlx->width * 0.05;
			cub3d->level->key_groups[i].key_icon_coords.y = cub3d->mlx->height * 0.9 - cub3d->mlx->height * 0.05 * active_key_groups;
			cub3d->level->key_groups[i].img_key_icon = mlx_texture_to_image(cub3d->mlx, cub3d->level->key_groups[i].texture_key_icon);
			if (!cub3d->level->key_groups[i].img_key_icon ||
				(mlx_image_to_window(cub3d->mlx,
				cub3d->level->key_groups[i].img_key_icon,
				cub3d->level->key_groups[i].key_icon_coords.x,
				cub3d->level->key_groups[i].key_icon_coords.y
				) < 0))
				err("Failed to create key count image");
			active_key_groups++;

			init_key_frames(cub3d, &cub3d->level->key_groups[i]);
			
		}
		i++;
	}
			draw_key_counts(cub3d);
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

void	init_timer(cub3d_t *cub3d)
{
	cub3d->timer.pos.x = cub3d->img->width * 0.95;
	cub3d->timer.pos.y = cub3d->img->height * 0.05;
}

int	init_cub3d(cub3d_t *cub3d)
{
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", TRUE);
	if (!cub3d->mlx)
		return (!err("Failed to initialize mlx"));
	cub3d->img = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->img || (mlx_image_to_window(cub3d->mlx, cub3d->img, 0, 0) < 0))
		return (!err("Failed to create image"));
	cub3d->rays = NULL;
	if (!init_rays(cub3d))
		return (!err("Failed to malloc rays"));
	cub3d->state = STATE_START;
	cub3d->mouse_set_pos.x = 0;
	cub3d->mouse_set_pos.y = 0;
	cub3d->on_minimap = FALSE;
	cub3d->fov = FOV;
	cub3d->n_levels = 9;
	cub3d->num_enemies = 0;
	set_keys(&cub3d->keys);
	init_start_menu(cub3d, &cub3d->start_menu);
	init_level_menu(cub3d, &cub3d->level_menu);
	if (!init_leaderboard(cub3d, &cub3d->leaderboard))
		return (FAIL);
	init_pause_menu(cub3d, &cub3d->pause_menu);
	init_name_menu(cub3d, &cub3d->name_menu);
	init_timer(cub3d);
	int i = -1;
	while (++i < 10)
		cub3d->levels[i].records = NULL;
	cub3d->start_timestamp = mlx_get_time();
	return (SUCCESS);
}
