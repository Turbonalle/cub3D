/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_zoom_out.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:09:03 by slampine          #+#    #+#             */
/*   Updated: 2024/01/17 16:59:01 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	get_new_percentage_zoom_out(int current_size_percentage)
{
	int	new_size_percentage;

	new_size_percentage = current_size_percentage - MINIMAP_ZOOM_INCREMENT;
	if (new_size_percentage < MINIMAP_MIN_SIZE_PERCENTAGE)
		new_size_percentage = MINIMAP_MIN_SIZE_PERCENTAGE;
	return (new_size_percentage);
}

static void	set_tile_size(cub3d_t *cub3d, int new_size_percentage,
	unsigned int *new_tile_size)
{
	*new_tile_size = count_minimap_tilesize(cub3d, new_size_percentage);
	if (*new_tile_size < 1)
		*new_tile_size = 1;
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

int	zoom_out_minimap(cub3d_t *cub3d)
{
	int				new_size_percentage;
	unsigned int	new_width;
	unsigned int	new_height;
	unsigned int	new_tile_size;
	vector_t		new_pos;

	new_size_percentage
		= get_new_percentage_zoom_out(cub3d->minimap.size_percentage);
	set_tile_size(cub3d, new_size_percentage, &new_tile_size);
	new_width = new_tile_size * cub3d->level->map_columns;
	new_height = new_tile_size * cub3d->level->map_rows;
	new_pos.x = cub3d->minimap.pos.x + (cub3d->minimap.width - new_width) / 2;
	new_pos.y = cub3d->minimap.pos.y + (cub3d->minimap.height - new_height) / 2;
	cub3d->minimap.size_percentage = new_size_percentage;
	cub3d->minimap.tile_size = new_tile_size;
	cub3d->minimap.width = new_width;
	cub3d->minimap.height = new_height;
	cub3d->minimap.pos = new_pos;
	return (new_minimap_image(cub3d));
}
