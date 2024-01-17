/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_zoom.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:09:03 by slampine          #+#    #+#             */
/*   Updated: 2024/01/17 11:10:21 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	get_new_percentage_zoom_in(int current_size_percentage)
{
	int	new_size_percentage;

	new_size_percentage = current_size_percentage + MINIMAP_ZOOM_INCREMENT;
	if (new_size_percentage > MINIMAP_MAX_SIZE_PERCENTAGE)
		new_size_percentage = MINIMAP_MAX_SIZE_PERCENTAGE;
	return (new_size_percentage);
}

vector_t	get_new_pos(cub3d_t *cub3d, unsigned int new_height,
	unsigned int new_width)
{
	vector_t	new_pos;

	new_pos.x = cub3d->minimap.pos.x - (new_width - cub3d->minimap.width) / 2;
	new_pos.y = cub3d->minimap.pos.y - (new_height - cub3d->minimap.height) / 2;
	if (new_pos.x < 0)
		new_pos.x = 0;
	if (new_pos.y < 0)
		new_pos.y = 0;
	if (new_pos.x + new_width > cub3d->img->width)
		new_pos.x = cub3d->img->width - new_width;
	if (new_pos.y + new_height > cub3d->img->height)
		new_pos.y = cub3d->img->height - new_height;
	return (new_pos);
}

void	zoom_in_minimap(cub3d_t *cub3d)
{
	int				new_size_percentage;
	unsigned int	new_width;
	unsigned int	new_height;
	unsigned int	new_tile_size;
	vector_t		new_pos;

	new_size_percentage
		= get_new_percentage_zoom_in(cub3d->minimap.size_percentage);
	new_tile_size = count_minimap_tilesize(cub3d, new_size_percentage);
	new_width = new_tile_size * cub3d->level->map_columns;
	new_height = new_tile_size * cub3d->level->map_rows;
	if (new_width > cub3d->img->width || new_height > cub3d->img->height)
		return ;
	new_pos = get_new_pos(cub3d, new_height, new_width);
	cub3d->minimap.size_percentage = new_size_percentage;
	cub3d->minimap.tile_size = new_tile_size;
	cub3d->minimap.width = new_width;
	cub3d->minimap.height = new_height;
	cub3d->minimap.pos = new_pos;
	mlx_delete_image(cub3d->mlx, cub3d->minimap.img);
	cub3d->minimap.img = mlx_new_image(cub3d->mlx, cub3d->minimap.width,
			cub3d->minimap.height);
	if (!cub3d->minimap.img || (mlx_image_to_window(cub3d->mlx, cub3d->minimap
				.img, cub3d->minimap.pos.x, cub3d->minimap.pos.y) < 0))
		err("Failed to create minimap image");
}

static int	get_new_percentage_zoom_out(int current_size_percentage)
{
	int	new_size_percentage;

	new_size_percentage = current_size_percentage - MINIMAP_ZOOM_INCREMENT;
	if (new_size_percentage < MINIMAP_MIN_SIZE_PERCENTAGE)
		new_size_percentage = MINIMAP_MIN_SIZE_PERCENTAGE;
	return (new_size_percentage);
}

void	zoom_out_minimap(cub3d_t *cub3d)
{
	int				new_size_percentage;
	unsigned int	new_width;
	unsigned int	new_height;
	unsigned int	new_tile_size;
	vector_t		new_pos;

	new_size_percentage
		= get_new_percentage_zoom_out(cub3d->minimap.size_percentage);
	new_tile_size = count_minimap_tilesize(cub3d, new_size_percentage);
	if (new_tile_size < 1)
		new_tile_size = 1;
	new_width = new_tile_size * cub3d->level->map_columns;
	new_height = new_tile_size * cub3d->level->map_rows;
	new_pos.x = cub3d->minimap.pos.x + (cub3d->minimap.width - new_width) / 2;
	new_pos.y = cub3d->minimap.pos.y + (cub3d->minimap.height - new_height) / 2;
	cub3d->minimap.size_percentage = new_size_percentage;
	cub3d->minimap.tile_size = new_tile_size;
	cub3d->minimap.width = new_width;
	cub3d->minimap.height = new_height;
	cub3d->minimap.pos = new_pos;
	mlx_delete_image(cub3d->mlx, cub3d->minimap.img);
	cub3d->minimap.img = mlx_new_image(cub3d->mlx, cub3d->minimap.width,
			cub3d->minimap.height);
	if (!cub3d->minimap.img
		|| (mlx_image_to_window(cub3d->mlx, cub3d->minimap.img,
				cub3d->minimap.pos.x, cub3d->minimap.pos.y) < 0))
		err("Failed to create minimap image");
}
