/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_zoom_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:27:40 by jbagger           #+#    #+#             */
/*   Updated: 2024/01/17 16:50:47 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static vector_t	get_new_pos(cub3d_t *cub3d, unsigned int new_height,
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

static int	get_new_percentage_zoom_in(int current_size_percentage)
{
	int	new_size_percentage;

	new_size_percentage = current_size_percentage + MINIMAP_ZOOM_INCREMENT;
	if (new_size_percentage > MINIMAP_MAX_SIZE_PERCENTAGE)
		new_size_percentage = MINIMAP_MAX_SIZE_PERCENTAGE;
	return (new_size_percentage);
}

static int	new_minimap_image(cub3d_t *cub3d)
{
	mlx_delete_image(cub3d->mlx, cub3d->minimap.img);
	cub3d->minimap.img = NULL;
	if (cub3d->minimap.tile_size * cub3d->level->map_columns
		> (int)cub3d->img->width || cub3d->minimap.tile_size
		* cub3d->level->map_rows > (int)cub3d->img->height)
		return (err("Minimap is too big"));
	cub3d->minimap.img = mlx_new_image(cub3d->mlx, cub3d->minimap.width,
			cub3d->minimap.height);
	if (!cub3d->minimap.img || (mlx_image_to_window(cub3d->mlx, cub3d->minimap
				.img, cub3d->minimap.pos.x, cub3d->minimap.pos.y) < 0))
		return (err("Failed to create minimap image"));
	return (SUCCESS);
}

int	zoom_in_minimap(cub3d_t *cub3d)
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
		return (SUCCESS);
	new_pos = get_new_pos(cub3d, new_height, new_width);
	cub3d->minimap.size_percentage = new_size_percentage;
	cub3d->minimap.tile_size = new_tile_size;
	cub3d->minimap.width = new_width;
	cub3d->minimap.height = new_height;
	cub3d->minimap.pos = new_pos;
	return (new_minimap_image(cub3d));
}