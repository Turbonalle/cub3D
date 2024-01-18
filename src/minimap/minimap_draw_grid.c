/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw_grid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:31:12 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 13:40:25 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	draw_correct_square(t_cub3d *cub3d, int row, int column)
{
	int			index;
	t_vector	coord;

	index = get_door_index(cub3d->level->map[row][column]);
	coord.x = column * cub3d->minimap.tile_size;
	coord.y = row * cub3d->minimap.tile_size;
	if (index > -1)
	{
		if (cub3d->speedrun == 0)
			draw_square(cub3d->minimap.img, coord, cub3d->minimap.tile_size,
				get_hidden_color(cub3d, index, row, column));
		else
			draw_square(cub3d->minimap.img, coord, cub3d->minimap.tile_size,
				cub3d->minimap.color_door_locked);
	}
	else if (ft_strchr("0mo", cub3d->level->map[row][column])
			|| get_key_index(cub3d->level->map[row][column]) > -1)
		draw_square(cub3d->minimap.img, coord, cub3d->minimap.tile_size,
			cub3d->minimap.color_floor);
	else if (ft_strchr("1hr", cub3d->level->map[row][column]))
		draw_square(cub3d->minimap.img, coord, cub3d->minimap.tile_size,
			cub3d->minimap.color_wall);
	else
		draw_square(cub3d->minimap.img, coord, cub3d->minimap.tile_size,
			cub3d->minimap.color_empty);
}

void	draw_extras(t_cub3d *cub3d, int row, int column)
{
	int			index;
	t_vector	pos;

	index = get_key_index(cub3d->level->map[row][column]);
	pos.x = column * cub3d->minimap.tile_size;
	pos.y = row * cub3d->minimap.tile_size;
	if (index > -1)
	{
		if (next_to_hidden(cub3d, row, column))
		{
			draw_square(cub3d->minimap.img, pos, cub3d->minimap.tile_size,
				cub3d->minimap.color_wall);
		}
		else
		{
			draw_circle(cub3d->minimap.img,
				pos,
				cub3d->minimap.tile_size / 2,
				get_door_key_color(cub3d, index));
		}
		draw_shroom(cub3d, row, column, pos);
	}
}

void	draw_minimap(t_cub3d *cub3d)
{
	int	row;
	int	column;

	row = -1;
	while (++row < cub3d->level->map_rows)
	{
		column = -1;
		while (++column < cub3d->level->map_columns)
			draw_correct_square(cub3d, row, column);
	}
}

void	draw_minimap_border(t_cub3d *cub3d)
{
	int	row;
	int	column;

	column = -1;
	while (++column < (int)cub3d->minimap.img->width)
	{
		mlx_put_pixel(cub3d->minimap.img, column, 0, RED);
		mlx_put_pixel(cub3d->minimap.img, column,
			cub3d->minimap.img->height - 1, RED);
	}
	row = -1;
	while (++row < (int)cub3d->minimap.img->height)
	{
		mlx_put_pixel(cub3d->minimap.img, 0, row, RED);
		mlx_put_pixel(cub3d->minimap.img,
			cub3d->minimap.img->width - 1, row, RED);
	}
}
