/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsorted_utills.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:32:35 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:15:34 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	draw_border_image(t_minilevel *minilevel)
{
	unsigned int	row;
	unsigned int	col;

	row = -1;
	while (++row < minilevel->border->height)
	{
		col = -1;
		while (++col < minilevel->border->width)
		{
			if (row < MINILEVEL_BORDER_THICKNESS
				|| row >= minilevel->border->height - MINILEVEL_BORDER_THICKNESS
				|| col < MINILEVEL_BORDER_THICKNESS
				|| col >= minilevel->border->width - MINILEVEL_BORDER_THICKNESS)
				mlx_put_pixel(minilevel->border, col, row,
					MINILEVEL_BORDER_COLOR);
		}
	}
}

void	free_start_menu(t_start_menu *menu)
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

int	count_minimap_tilesize(t_cub3d *cub3d, int size_percentage)
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

static int	init_minimap_rest(t_cub3d *cub3d)
{
	cub3d->minimap.color_player
		= set_transparency(MINIMAP_COLOR_PLAYER, cub3d->minimap.transparency);
	cub3d->minimap.color_playerdir
		= set_transparency(MINIMAP_COLOR_DIR, cub3d->minimap.transparency);
	cub3d->minimap.color_fov
		= set_transparency(MINIMAP_COLOR_FOV, cub3d->minimap.transparency);
	cub3d->minimap.color_floor
		= set_transparency(MINIMAP_COLOR_FLOOR, cub3d->minimap.transparency);
	cub3d->minimap.color_wall
		= set_transparency(MINIMAP_COLOR_WALL, cub3d->minimap.transparency);
	cub3d->minimap.color_empty
		= set_transparency(MINIMAP_COLOR_EMPTY, cub3d->minimap.transparency);
	cub3d->minimap.color_enemy
		= set_transparency(MINIMAP_COLOR_ENEMY, cub3d->minimap.transparency);
	cub3d->minimap.color_shroom
		= set_transparency(MINIMAP_COLOR_SHROOM, cub3d->minimap.transparency);
	cub3d->minimap.color_key_1
		= set_transparency(MINIMAP_COLOR_KEY_1, cub3d->minimap.transparency);
	cub3d->minimap.color_key_2
		= set_transparency(MINIMAP_COLOR_KEY_2, cub3d->minimap.transparency);
	cub3d->minimap.color_key_3
		= set_transparency(MINIMAP_COLOR_KEY_3, cub3d->minimap.transparency);
	cub3d->minimap.color_key_4
		= set_transparency(MINIMAP_COLOR_KEY_4, cub3d->minimap.transparency);
	return (SUCCESS);
}

int	init_minimap(t_cub3d *cub3d)
{
	cub3d->minimap.size_percentage = MINIMAP_SIZE_PERCENTAGE;
	cub3d->minimap.tile_size
		= count_minimap_tilesize(cub3d, cub3d->minimap.size_percentage);
	cub3d->minimap.width = cub3d->minimap.tile_size * cub3d->level->map_columns;
	cub3d->minimap.height = cub3d->minimap.tile_size * cub3d->level->map_rows;
	cub3d->minimap.img = mlx_new_image(cub3d->mlx,
			cub3d->minimap.width, cub3d->minimap.height);
	if (!cub3d->minimap.img || (mlx_image_to_window(cub3d->mlx,
				cub3d->minimap.img, 0, 0) < 0))
		return (FAIL);
	cub3d->minimap.pos.x = 0;
	cub3d->minimap.pos.y = 0;
	cub3d->orig_minimap_pos.x = 0;
	cub3d->orig_minimap_pos.y = 0;
	cub3d->mouse_set_pos.x = 0;
	cub3d->mouse_set_pos.y = 0;
	cub3d->on_minimap = FALSE;
	cub3d->minimap.transparency = MINIMAP_TRANSPARENCY;
	return (init_minimap_rest(cub3d));
}
