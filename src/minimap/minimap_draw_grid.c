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

void mlx_draw_horizontal_line(cub3d_t *cub3d, int x1, int x2, int y, int color) {
	while (x1 <= x2)
	{
		mlx_put_pixel(cub3d->minimap.img, x1, y, color);
		x1++;
	}
}

void draw_circle(cub3d_t *cub3d, int col, int row, int radius, int color) {
    vector_t center;
	int x;
    int y;
    int decision;

    center.x = col + radius;
    center.y = row + radius;
    x = radius;
    y = 0;
    decision = 1 - radius;
    
    while (x >= y) {
        mlx_draw_horizontal_line(cub3d, center.x - x, center.x + x, center.y + y, color);
        mlx_draw_horizontal_line(cub3d, center.x - x, center.x + x, center.y - y, color);
        mlx_draw_horizontal_line(cub3d, center.x - y, center.x + y, center.y + x, color);
        mlx_draw_horizontal_line(cub3d, center.x - y, center.x + y, center.y - x, color);
        y++;
        if (decision <= 0) {
            decision += 2 * y + 1;
        } else {
            x--;
            decision += 2 * (y - x) + 1;
        }
    }
}


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
		draw_square(cub3d,
			column * cub3d->minimap.tile_size,
			row * cub3d->minimap.tile_size,
			cub3d->minimap.tile_size, get_door_key_color(cub3d, index));
	} else if (cub3d->level->map[row][column] == '0' || get_key_index(cub3d->level->map[row][column]) > -1)
	{
		draw_square(cub3d,
			column * cub3d->minimap.tile_size,
			row * cub3d->minimap.tile_size,
			cub3d->minimap.tile_size, cub3d->minimap.color_floor);
	}
	else if (cub3d->level->map[row][column] == '1')
	{
		draw_square(cub3d,
			column * cub3d->minimap.tile_size,
			row * cub3d->minimap.tile_size,
			cub3d->minimap.tile_size, cub3d->minimap.color_wall);
	}
	else
	{
		draw_square(cub3d,
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
		draw_circle(cub3d,
			column * cub3d->minimap.tile_size,
			row * cub3d->minimap.tile_size,
			cub3d->minimap.tile_size / 2,
			get_door_key_color(cub3d, index));
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
		{
			draw_correct_square(cub3d, row, column);
			draw_extras(cub3d, row, column);
		}
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
