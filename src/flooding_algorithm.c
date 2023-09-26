#include "../incl/cub3d.h"

void flood(char **map, int row, int column)
{
	if (map[row][column] == '1')
		map[row][column] = 'w';
	else
		return ;
	if (row != 0)
		flood(map, row - 1, column);
	if (column != 0)
		flood(map, row, column - 1);
	if (map[row + 1])
		flood(map, row + 1, column);
	if (map[row][column + 1])
		flood(map, row, column + 1);
}

//------------------------------------------------------------------------------

int all_walls_changed(char **map)
{
	int row;
	int column;

	row = -1;
	while (map[++row])
	{
		column = -1;
		while (map[row][++column])
		{
			if (map[row][column] == 'w')
				map[row][column] = '1';
			else if (map[row][column] == '1')
				return (FALSE);
		}
	}
	return (TRUE);
}

//------------------------------------------------------------------------------

int check_map_validity(char **map)
{
	int row;
	int column;

	row = 0;
	column = 0;
	while (map[row][column] == ' ')
		column++;
	printf(TERMINAL_CYAN"FLOODING:\n"TERMINAL_RESET);
	flood(map, row, column);
	print_map(map); // DEBUG
	if (!all_walls_changed(map))
		return (err("Map is not surrounded by walls"));
	return (SUCCESS);
}