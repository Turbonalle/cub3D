#include "../incl/raycaster.h"

//------------------------------------------------------------------------------

void fill_box(mlx_image_t *img, map_t *map, int row, int column, int color)
{
	int x;
	int y;

	// printf("Filling box...\n");
	if (row < 0 || row >= map->rows || column < 0 || column >= map->columns)
	{
		printf("Invalid box coordinates!\n");
		return ;
	}
	x = map->grid_relative[row][column].x;
	while (x < map->grid_relative[row][column].end_x)
	{
		y = map->grid_relative[row][column].y;
		while (y < map->grid_relative[row][column].end_y)
		{
			mlx_put_pixel(img, x, y, color);
			y++;
		}
		x++;
	}
}

//------------------------------------------------------------------------------

int get_hovered_box(map_t *map, vector_t mouse_pos, vector_t *box)
{
	int column;
	int row;

	row = -1;
	while (++row < map->rows)
	{
		column = -1;
		while (++column < map->columns)
		{
			if (mouse_pos.x >= map->grid_relative[row][column].x && mouse_pos.x <= map->grid_relative[row][column].end_x
				&& mouse_pos.y >= map->grid_relative[row][column].y && mouse_pos.y <= map->grid_relative[row][column].end_y)
			{
				box->x = column;
				box->y = row;
				return (SUCCESS);
			}
		}
	}
	printf("No box hovered!\n");
	box->x = -1;
	box->y = -1;
	return (FAIL);
}

//------------------------------------------------------------------------------

void destroy_wall(mlx_image_t *img, map_t *map, int row, int column, int color)
{
	if (map->grid[row][column] == 0)
		return ;
	map->grid[row][column] = 0;
	fill_box(img, map, row, column, color);
}

//------------------------------------------------------------------------------

void create_wall(mlx_image_t *img, map_t *map, int row, int column, int color)
{
	if (map->grid[row][column] == 1)
		return ;
	map->grid[row][column] = 1;
	fill_box(img, map, row, column, color);
}

//------------------------------------------------------------------------------

void empty_chosen_box(mlx_t *mlx, mlx_image_t *img, map_t *map, int color)
{
	vector_t mouse_pos;
	vector_t box;

	mlx_get_mouse_pos(mlx, &mouse_pos.x, &mouse_pos.y);
	if (get_hovered_box(map, mouse_pos, &box))
		destroy_wall(img, map, box.y, box.x, color);
}

//------------------------------------------------------------------------------

void fill_chosen_box(mlx_t *mlx, mlx_image_t *img, map_t *map, int color)
{
	vector_t mouse_pos;
	vector_t box;

	mlx_get_mouse_pos(mlx, &mouse_pos.x, &mouse_pos.y);
	if (get_hovered_box(map, mouse_pos, &box))
		create_wall(img, map, box.y, box.x, color);
}

//------------------------------------------------------------------------------

void draw_wall_border(mlx_image_t *img, map_t *map, int color)
{
	int column;
	int row;

	column = 0;
	while (column < map->columns)
	{
		create_wall(img, map, 0, column, color);
		create_wall(img, map, map->rows - 1, column, color);
		column++;
	}
	row = 1;
	while (row < map->rows - 1)
	{
		create_wall(img, map, row, 0, color);
		create_wall(img, map, row, map->columns - 1, color);
		row++;
	}
}