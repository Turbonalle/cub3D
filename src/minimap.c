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
			mlx_put_pixel(cub3d->img, col, row, color);
			col++;
		}
		row++;
	}
}

void draw_minimap(cub3d_t *cub3d)
{
	int row;
	int column;

	row = -1;
	while (++row < cub3d->map_rows)
	{
		column = -1;
		while (++column < cub3d->map_columns)
		{
			if (cub3d->map[row][column] == '0')
			{
				draw_square(cub3d,
							cub3d->minimap.pos.x + column * cub3d->minimap.tile_size,
							cub3d->minimap.pos.y + row * cub3d->minimap.tile_size,
							cub3d->minimap.tile_size, COLOR_EMPTY);
			}
			else if (cub3d->map[row][column] == '1')
			{
				draw_square(cub3d,
							cub3d->minimap.pos.x + column * cub3d->minimap.tile_size,
							cub3d->minimap.pos.y + row * cub3d->minimap.tile_size,
							cub3d->minimap.tile_size, COLOR_WALL);
			}
		}
	}
}

void draw_minimap_border(cub3d_t *cub3d)
{
	int row;
	int column;
	// draw red border
	column = -1;
	while (++column < cub3d->minimap.width)
	{
		mlx_put_pixel(cub3d->img, cub3d->minimap.pos.x + column, cub3d->minimap.pos.y, RED);
		mlx_put_pixel(cub3d->img, cub3d->minimap.pos.x + column, cub3d->minimap.pos.y + cub3d->minimap.height - 1, RED);
	}
	row = -1;
	while (++row < cub3d->minimap.height)
	{
		mlx_put_pixel(cub3d->img, cub3d->minimap.pos.x, cub3d->minimap.pos.y + row, RED);
		mlx_put_pixel(cub3d->img, cub3d->minimap.pos.x + cub3d->minimap.width - 1, cub3d->minimap.pos.y + row, RED);
	}
}

void draw_minimap_player(cub3d_t *cub3d)
{
	double row;
	double column;
	int size;

	size = cub3d->minimap.tile_size / 4;
	row = cub3d->minimap.pos.y + (cub3d->player.pos.y * cub3d->minimap.tile_size) - (size / 2);
	column = cub3d->minimap.pos.x + (cub3d->player.pos.x * cub3d->minimap.tile_size) - (size / 2);
	draw_square(cub3d, (int)column, (int)row, size, YELLOW);
}

void minimap(cub3d_t *cub3d)
{
	draw_minimap(cub3d);
	draw_minimap_border(cub3d);
	draw_minimap_player(cub3d);
	// draw_minimap_fov(cub3d);
}