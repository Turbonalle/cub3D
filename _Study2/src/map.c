#include "../incl/raycaster.h"

void set_border(map_t *map)
{
	int column;
	int row;

	row = -1;
	while (++row < map->rows)
	{
		column = -1;
		while (++column < map->columns)
		{
			if (row == 0 || row == map->rows - 1 || column == 0 || column == map->columns - 1)
				map->grid[row][column] = WALL;
		}
	}
}

void draw_map(mlx_image_t *img, map_t *map)
{
	int column;
	int row;

	row = -1;
	while (++row < map->rows)
	{
		column = -1;
		while (++column < map->columns)
		{
			if (map->grid[row][column] == WALL)
				fill_box(img, map, row, column, WALL_COLOR);
			else if (map->grid[row][column] == EMPTY)
				fill_box(img, map, row, column, BG_COLOR);
		}
	}
}

//------------------------------------------------------------------------------

void reset_map(mlx_image_t *img, map_t *map)
{
	int column;
	int row;

	printf("Resetting map...\n");
	row = -1;
	while (++row < map->rows)
	{
		column = -1;
		while (++column < map->columns)
			map->grid[row][column] = EMPTY;
	}
	set_border(map);
	draw_map(img, map);
}

//------------------------------------------------------------------------------

void set_map(map_t *map)
{
	int column;
	int row;

	row = -1;
	while (++row < map->rows)
	{
		column = -1;
		while (++column < map->columns)
			map->grid[row][column] = EMPTY;
	}
}

//------------------------------------------------------------------------------

void init_relative_grid(mlx_image_t* img, map_t *map)
{
	int column;
	int row;

	map->grid_relative = malloc(sizeof(box_t *) * map->rows);
	if (!map->grid_relative)
		ft_error();
	row = -1;
	while (++row < map->rows)
	{
		map->grid_relative[row] = malloc(sizeof(box_t) * map->columns);
		if (!map->grid_relative[row])
			ft_error();
		column = -1;
		while (++column < map->columns)
		{
			map->grid_relative[row][column].x = img->width * column / map->columns;
			map->grid_relative[row][column].y = img->height * row / map->rows;
			map->grid_relative[row][column].end_x = img->width * (column + 1) / map->columns;
			map->grid_relative[row][column].end_y = img->height * (row + 1) / map->rows;
			map->grid_relative[row][column].value = EMPTY;
		}
	}
}

map_t* init_map(mlx_image_t *img, int columns, int rows)
{
	map_t *map;
	int i;

	map = malloc(sizeof(map_t));
	if (!map)
		ft_error();
	map->columns = columns;
	map->rows = rows;
	map->cell_size = img->width / columns;
	map->grid = malloc(sizeof(int *) * rows);
	if (!map->grid)
		ft_error();
	i = -1;
	while (++i < map->rows)
	{
		map->grid[i] = malloc(sizeof(int) * map->columns);
		if (!map->grid[i])
			ft_error();
	}
	set_map(map);
	init_relative_grid(img, map);
	return (map);
}

void print_map(map_t *map)
{
	int column;
	int row;

	printf(TERMINAL_CYAN_BOLD"Map:\n"TERMINAL_RESET);
	row = -1;
	while (++row < map->rows)
	{
		column = -1;
		while (++column < map->columns)
			printf("%d ", map->grid[row][column]);
		printf("\n");
	}
}

void free_map(map_t *map)
{
	int i;

	i = map->rows;
	while (--i >= 0)
		free(map->grid[i]);
	free(map->grid);
	i = map->rows;
	while (--i >= 0)
		free(map->grid_relative[i]);
	free(map->grid_relative);
}