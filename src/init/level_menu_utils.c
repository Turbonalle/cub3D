/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_menu_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:01:56 by slampine          #+#    #+#             */
/*   Updated: 2024/01/17 11:40:43 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	set_preview_values(minilevel_t *minilevel, level_t *level)
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

void	set_number_values(minilevel_t *minilevel)
{
	int	number_rect_size;

	number_rect_size = minilevel->size * 0.15;
	minilevel->number_rect.width = number_rect_size;
	minilevel->number_rect.height = number_rect_size;
	minilevel->number_rect.pos.x = 0;
	minilevel->number_rect.pos.y = 0;
	printf("numrect pos: %d, %d\n", minilevel->number_rect.pos.x,
		minilevel->number_rect.pos.y);
	minilevel->number_rect.color = MINILEVEL_RECT_COLOR;
	minilevel->number.pos.x = minilevel->pos.x + number_rect_size
		/ 2 - minilevel->number.img->width / 2;
	minilevel->number.pos.y = minilevel->pos.y + number_rect_size
		/ 2 - minilevel->number.img->height / 2;
	printf("num pos: %d, %d\n", minilevel->number.pos.x,
		minilevel->number.pos.y);
}

static void	draw_right_square(int spec, minilevel_t *minilevel, vector_t coord)
{
	if (spec == '1' || spec == 'h' || spec == 'G' || spec == 'i'
		|| spec == 'j' || spec == 'k' || spec == 'l' || spec == 'r')
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

void	draw_preview_map(minilevel_t *minilevel, level_t *level, char **backup)
{
	int			row;
	int			column;
	vector_t	coord;

	row = -1;
	while (++row < level->map_rows)
	{
		column = -1;
		while (++column < level->map_columns)
		{
			coord.x = minilevel->preview_pos.x
				+ column * minilevel->square_size;
			coord.y = minilevel->preview_pos.y
				+ row * minilevel->square_size;
			draw_right_square(backup[row][column], minilevel, coord);
		}
	}
}

int	free_prev_level_menu(level_menu_t *menu, int i, int j)
{
	while (i > 0)
	{
		mlx_delete_texture(menu->minilevels[--i].number.texture);
	}
	mlx_delete_texture(menu->title.texture);
	if (j > 0)
		mlx_delete_texture(menu->back.texture);
	if (j > 1)
		mlx_delete_texture(menu->back_hover.texture);
	if (j > 2)
		mlx_delete_texture(menu->leaderboard.texture);
	if (j > 3)
		mlx_delete_texture(menu->leaderboard_hover.texture);
	return (FAIL);
}
