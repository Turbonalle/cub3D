#include "../incl/cub3d.h"

int add_key(cub3d_t *cub3d, int i, int j, int key_group_index)
{
	key_node_t	*new_key;

	new_key = malloc(sizeof(key_node_t));
	if (!new_key)
		return (FAIL);
	new_key->pos.x = j + 0.5;
	new_key->pos.y = i + 0.5;
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

int	init_key_frames(key_group_t *key_group)
{
	int 	i;
	char	*file_path;
	char	*file_name;
	char	*file_name_extension;
	
	// TODO: protect mallocs
	key_group->textures_frames = malloc(sizeof(mlx_texture_t *) * NUM_FRAMES_KEY);
	i = 0;
	while (i < NUM_FRAMES_KEY)
	{
		//TODO: protect mallocs
		file_name = ft_itoa(i + 1);
		file_name_extension = ft_strjoin(file_name, ".png");
		file_path = ft_strjoin(key_group->texture_dir, file_name_extension);
		printf("full file path: %s\n", file_path);
		key_group->textures_frames[i] = mlx_load_png(file_path);
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
		cub3d->level->key_groups[i].curr_frame_index = 0;
		cub3d->level->key_groups[i].prev_frame_index = -1;
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
	// TODO:handle errors
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
			temp->pos_screen.x = -WIDTH;
			temp->pos_screen.y = -HEIGHT;
			temp->visible = FALSE;
			temp->dist_to_player = 100;
			
			temp->img_curr_frame = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
			printf("created %d key img_curr_frame image, pointer: %p\n", count, temp->img_curr_frame);
			mlx_image_to_window(cub3d->mlx, temp->img_curr_frame, 0, 0);
			// TODO: handle errors
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
			init_key_frames(&cub3d->level->key_groups[i]);
		}
		i++;
	}
	draw_key_counts(cub3d);
	return (SUCCESS);
}
