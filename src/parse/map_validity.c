/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:09:19 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:27:52 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	flood(char **map, int row, int column, int elements)
{
	if (map[row][column] == '1' || map[row][column] == '0')
		map[row][column] += elements;
	else
		return ;
	if (row != 0)
		flood(map, row - 1, column, elements);
	if (column != 0)
		flood(map, row, column - 1, elements);
	if (map[row + 1])
		flood(map, row + 1, column, elements);
	if (map[row][column + 1])
		flood(map, row, column + 1, elements);
}

//------------------------------------------------------------------------------

int	all_walls_changed(char **map, int elements)
{
	int	row;
	int	column;

	row = -1;
	while (map[++row])
	{
		column = -1;
		while (map[row][++column])
		{
			if (map[row][column] == '0' + elements
				|| map[row][column] == '1' + elements)
				map[row][column] -= elements;
			else if (map[row][column] == '1')
				return (FALSE);
		}
	}
	return (TRUE);
}

//------------------------------------------------------------------------------

int	next_to_empty(char **map, int row, int column)
{
	return (map[row - 1][column - 1] == ' '
		|| map[row - 1][column] == ' '
		|| map[row - 1][column + 1] == ' '
		|| map[row][column - 1] == ' '
		|| map[row][column + 1] == ' '
		|| map[row + 1][column - 1] == ' '
		|| map[row + 1][column] == ' '
		|| map[row + 1][column + 1] == ' ');
}

//------------------------------------------------------------------------------

int	surrounded_by_walls(char **map)
{
	int	row;
	int	column;

	row = -1;
	while (map[++row])
	{
		column = -1;
		while (map[row][++column])
		{
			if (ft_strchr(MAP_ALL_BUT_WALL, map[row][column]))
			{
				if (row == 0 || !map[row + 1])
					return (FALSE);
				if (column == 0 || map[row][column + 1] == '\0')
					return (FALSE);
				if (next_to_empty(map, row, column))
					return (FALSE);
			}
		}
	}
	return (TRUE);
}

//------------------------------------------------------------------------------

int	check_map_validity(char **map)
{
	int	row;
	int	column;
	int	elements;

	row = 0;
	column = 0;
	while (map[row][column] == ' ')
		column++;
	if (!surrounded_by_walls(map))
		return (err("Map is not surrounded by walls"));
	elements = ft_strlen(MAP_ELEMENTS);
	flood(map, row, column, elements);
	if (!all_walls_changed(map, elements))
		return (err("Map is not connected"));
	return (SUCCESS);
}
