/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw_grid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:08:59 by slampine          #+#    #+#             */
/*   Updated: 2023/11/28 13:44:22 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void draw_square(cub3d_t *cub3d, int col, int row, int size, int color)
{
	
	vector_t end;
	int x;

	end.x = col + size;
	end.y = row + size;
	x = col;
	while (row < end.y)
	{
		col = x;
		while (col < end.x)
		{
			mlx_put_pixel(cub3d->minimap.img, col, row, color);
			col++;
		}
		row++;
	}
}

void draw_correct_square(cub3d_t *cub3d, int row, int column)
{
	if (cub3d->map[row][column] == '0')
	{
		draw_square(cub3d,
					column * cub3d->minimap.tile_size,
					row * cub3d->minimap.tile_size,
					cub3d->minimap.tile_size, cub3d->minimap.color_floor);
	}
	else if (cub3d->map[row][column] == '1')
	{
		draw_square(cub3d,
					column * cub3d->minimap.tile_size,
					row * cub3d->minimap.tile_size,
					cub3d->minimap.tile_size, cub3d->minimap.color_wall);
	}
	else if (cub3d->map[row][column] == '-' || cub3d->map[row][column] == '|' || is_door(cub3d->map[row][column]) > -1)
	{
		draw_square(cub3d,
					column * cub3d->minimap.tile_size,
					row * cub3d->minimap.tile_size,
					cub3d->minimap.tile_size, cub3d->minimap.color_door);
	}
	else if (is_key(cub3d->map[row][column]) > -1)
	{
		draw_square(cub3d,
					column * cub3d->minimap.tile_size,
					row * cub3d->minimap.tile_size,
					cub3d->minimap.tile_size, cub3d->minimap.color_key);
	}
	else
	{
		draw_square(cub3d,
					column * cub3d->minimap.tile_size,
					row * cub3d->minimap.tile_size,
					cub3d->minimap.tile_size, cub3d->minimap.color_empty);
	}
}

void	draw_minimap(cub3d_t *cub3d)
{
	int	row;
	int	column;

	row = -1;
	while (++row < cub3d->map_rows)
	{
		column = -1;
		while (++column < cub3d->map_columns)
			draw_correct_square(cub3d, row, column);
	}
}

void draw_minimap_border(cub3d_t *cub3d)
{
	int row;
	int column;

	column = -1;
	while (++column < (int)cub3d->minimap.img->width)
	{
		mlx_put_pixel(cub3d->minimap.img, column, 0, RED);
		mlx_put_pixel(cub3d->minimap.img, column, cub3d->minimap.img->height - 1, RED);
	}
	row = -1;
	while (++row < (int)cub3d->minimap.img->height)
	{
		mlx_put_pixel(cub3d->minimap.img, 0, row, RED);
		mlx_put_pixel(cub3d->minimap.img, cub3d->minimap.img->width - 1, row, RED);
	}
}
