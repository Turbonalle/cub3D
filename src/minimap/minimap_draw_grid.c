#include "../incl/cub3d.h"

int	get_door_key_color(cub3d_t *cub3d, int index)
{
	if (index == 0)
		return (cub3d->minimap.color_key_1);
	else if (index == 1)
		return (cub3d->minimap.color_key_2);
	else if (index == 2)
		return (cub3d->minimap.color_key_3);
	else
		return (cub3d->minimap.color_key_4);
}

void draw_correct_square(cub3d_t *cub3d, int row, int column)
{
	int index;

	index = get_door_index(cub3d->level->map[row][column]);
	if (index > -1)
	{
		draw_square(cub3d->minimap.img,
			column * cub3d->minimap.tile_size,
			row * cub3d->minimap.tile_size,
			cub3d->minimap.tile_size, get_door_key_color(cub3d, index));
	} else if (cub3d->level->map[row][column] == '0' || get_key_index(cub3d->level->map[row][column]) > -1 || cub3d->level->map[row][column] == 'm')
	{
		draw_square(cub3d->minimap.img,
			column * cub3d->minimap.tile_size,
			row * cub3d->minimap.tile_size,
			cub3d->minimap.tile_size, cub3d->minimap.color_floor);
	}
	else if (cub3d->level->map[row][column] == '1')
	{
		draw_square(cub3d->minimap.img,
			column * cub3d->minimap.tile_size,
			row * cub3d->minimap.tile_size,
			cub3d->minimap.tile_size, cub3d->minimap.color_wall);
	}
	else
	{
		draw_square(cub3d->minimap.img,
			column * cub3d->minimap.tile_size,
			row * cub3d->minimap.tile_size,
			cub3d->minimap.tile_size, cub3d->minimap.color_empty);
	}
}

void	draw_extras(cub3d_t *cub3d, int row, int column)
{
	int index;

	index = get_key_index(cub3d->level->map[row][column]);
	if (index > -1)
	{
		draw_circle(cub3d->minimap.img,
			column * cub3d->minimap.tile_size,
			row * cub3d->minimap.tile_size,
			cub3d->minimap.tile_size / 2,
			get_door_key_color(cub3d, index));
	}
	if (cub3d->level->map[row][column] == 'm')
	{
		draw_circle(cub3d->minimap.img,
			column * cub3d->minimap.tile_size,
			row * cub3d->minimap.tile_size,
			cub3d->minimap.tile_size / 2,
			MINIMAP_COLOR_SHROOM);
	}
}

void	draw_minimap(cub3d_t *cub3d)
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
