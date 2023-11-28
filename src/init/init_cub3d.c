/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:08:34 by slampine          #+#    #+#             */
/*   Updated: 2023/11/28 12:31:06 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	count_minimap_tilesize(cub3d_t *cub3d, int size_percentage)
{
	float	tile_size;
	float	minimap_width;
	float	minimap_height;

	minimap_width = (float)cub3d->img->width * (float)size_percentage / 100;
	tile_size = minimap_width / (float)cub3d->map_columns;
	minimap_height = (float)cub3d->img->height * (float)size_percentage / 100;
	if (tile_size * (float)cub3d->map_rows > minimap_height)
		tile_size = minimap_height / (float)cub3d->map_rows;
	return ((int)tile_size);
}

void	init_minimap(cub3d_t *cub3d)
{
	cub3d->minimap.size_percentage = MINIMAP_SIZE_PERCENTAGE;
	cub3d->minimap.tile_size = count_minimap_tilesize(cub3d, cub3d->minimap.size_percentage);
	cub3d->minimap.width = cub3d->minimap.tile_size * cub3d->map_columns;
	cub3d->minimap.height = cub3d->minimap.tile_size * cub3d->map_rows;
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
	cub3d->minimap.color_door = set_transparency(MINIMAP_COLOR_DOOR, cub3d->minimap.transparency);
}

void	set_initial_direction(cub3d_t *cub3d)
{
	if (cub3d->starting_dir == 'E')
		cub3d->player.angle = to_radians(0);
	else if (cub3d->starting_dir == 'S')
		cub3d->player.angle = to_radians(90);
	else if (cub3d->starting_dir == 'W')
		cub3d->player.angle = to_radians(180);
	else if (cub3d->starting_dir == 'N')
		cub3d->player.angle = to_radians(270);
	cub3d->player.dir.x = cos(cub3d->player.angle);
	cub3d->player.dir.y = sin(cub3d->player.angle);
}

void	set_keys(keypress_t *keys)
{
	keys->w = FALSE;
	keys->a = FALSE;
	keys->s = FALSE;
	keys->d = FALSE;
	keys->fisheye = FALSE;
	keys->left = FALSE;
	keys->right = FALSE;
	keys->mouse_left = FALSE;
	keys->mouse_right = FALSE;
	
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

void	count_enemies(cub3d_t *cub3d)
{
	int	i;
	int	j;

	i = 0;
	while (cub3d->map[i])
	{
		j = 0;
		while (cub3d->map[i][j])
		{
			if (ft_strchr(ENEMIES, cub3d->map[i][j]))
				cub3d->num_enemies++;
			j++;
		}
		i++;
	}
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
	// cub3d->state = STATE_START;
	cub3d->state = STATE_GAME;	// REMOVE LATER
	cub3d->player.pos.x = cub3d->starting_pos.x + 0.5;
	cub3d->player.pos.y = cub3d->starting_pos.y + 0.5;
	cub3d->mouse_set_pos.x = 0;
	cub3d->mouse_set_pos.y = 0;
	cub3d->on_minimap = FALSE;
	cub3d->fov = FOV;
	cub3d->fisheye = 0;
	cub3d->prev = 0;
	cub3d->num_enemies = 0;
	count_enemies(cub3d);
	set_initial_direction(cub3d);
	set_keys(&cub3d->keys);
	init_minimap(cub3d);
	init_start_menu(cub3d, &cub3d->start_menu);
	init_pause_menu(cub3d, &cub3d->pause_menu);
	return (SUCCESS);
}
