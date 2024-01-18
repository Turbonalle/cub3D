/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_menu_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:01:56 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 14:57:45 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	set_preview_values(t_minilevel *minilevel, t_level *level)
{
	int	drawable_area_size;

	drawable_area_size = minilevel->size - MINILEVEL_MARGIN * 2;
	if (drawable_area_size < 0)
		drawable_area_size = 0;
	if (level->map_columns > level->map_rows)
	{
		minilevel->square_size = drawable_area_size / level->map_columns;
		minilevel->width = minilevel->square_size * level->map_columns;
		minilevel->height = minilevel->square_size * level->map_rows;
		minilevel->preview_pos.x = (minilevel->size - minilevel->width) / 2;
		minilevel->preview_pos.y = (minilevel->size - minilevel->height) / 2;
	}
	else
	{
		minilevel->square_size = drawable_area_size / level->map_rows;
		minilevel->width = minilevel->square_size * level->map_columns;
		minilevel->height = minilevel->square_size * level->map_rows;
		minilevel->preview_pos.x = (minilevel->size - minilevel->width) / 2;
		minilevel->preview_pos.y = (minilevel->size - minilevel->height) / 2;
	}
}

void	set_number_values(t_minilevel *minilevel)
{
	int	number_rect_size;

	number_rect_size = minilevel->size * 0.15;
	minilevel->number_rect.width = number_rect_size;
	minilevel->number_rect.height = number_rect_size;
	minilevel->number_rect.pos.x = 0;
	minilevel->number_rect.pos.y = 0;
	minilevel->number_rect.color = MINILEVEL_RECT_COLOR;
	minilevel->number.pos.x = minilevel->pos.x + number_rect_size
		/ 2 - minilevel->number.img->width / 2;
	minilevel->number.pos.y = minilevel->pos.y + number_rect_size
		/ 2 - minilevel->number.img->height / 2;
}

static void	draw_right_square(int spec, t_minilevel *minilevel, t_vector coord)
{
	if (spec)
	{
		draw_square(minilevel->img,
			coord,
			minilevel->square_size,
			PREVIEW_WALL_COLOR);
	}
	else
	{
		draw_square(minilevel->img,
			coord,
			minilevel->square_size,
			PREVIEW_FLOOR_COLOR);
	}
}

static int	check_adjacents(char **map, int row, int column, t_vector map_size)
{
	if (ft_strchr("1hGijklr", map[row][column]))
		return (1);
	if (row > 0 && ft_strchr("hr", map[row - 1][column]))
		return (1);
	if (row < map_size.y - 1 && ft_strchr("hr", map[row + 1][column]))
		return (1);
	if (column > 0 && ft_strchr("hr", map[row][column - 1]))
		return (1);
	if (column < map_size.x - 1 && ft_strchr("hr", map[row][column + 1]))
		return (1);
	return (0);
}

void	draw_preview_map(t_minilevel *minilevel, t_level *level, char **backup)
{
	t_vector	map_size;
	int			row;
	int			column;
	t_vector	coord;

	row = -1;
	map_size.y = level->map_rows;
	map_size.x = level->map_columns;
	while (++row < level->map_rows)
	{
		column = -1;
		while (++column < level->map_columns)
		{
			coord.x = minilevel->preview_pos.x
				+ column * minilevel->square_size;
			coord.y = minilevel->preview_pos.y
				+ row * minilevel->square_size;
			if (check_adjacents(backup, row, column, map_size))
				draw_right_square(1, minilevel, coord);
			else
				draw_right_square(0, minilevel, coord);
		}
	}
}
