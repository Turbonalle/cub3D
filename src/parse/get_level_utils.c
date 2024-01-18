/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_level_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:41:12 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:15:34 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	create_map(t_level *level, t_map_node *current_map_node, int length)
{
	int			i;
	int			j;

	i = 0;
	while (current_map_node)
	{
		level->map[i] = malloc(sizeof(char) * (length + 1));
		if (!level->map[i])
			return (err("Failed to allocate memory for map"));
		j = 0;
		while (current_map_node->line[j])
		{
			level->map[i][j] = current_map_node->line[j];
			j++;
		}
		while (j < length)
			level->map[i][j++] = ' ';
		level->map[i][j] = '\0';
		current_map_node = current_map_node->next;
		i++;
	}
	return (SUCCESS);
}

int	create_rectangular_map(t_level *level)
{
	t_map_node	*current_map_node;
	int			longest_length;

	level->map = malloc(sizeof(char *) * (level->nodes + 1));
	if (!level->map)
		return (err("Failed to allocate memory for map"));
	longest_length = 0;
	current_map_node = level->map_list;
	while (current_map_node)
	{
		if ((int)ft_strlen(current_map_node->line) > longest_length)
			longest_length = ft_strlen(current_map_node->line);
		current_map_node = current_map_node->next;
	}
	level->map_columns = longest_length;
	level->map_rows = level->nodes;
	level->map[level->nodes] = NULL;
	current_map_node = level->map_list;
	create_map(level, current_map_node, longest_length);
	return (SUCCESS);
}

void	zero_map(char **map)
{
	int	row;
	int	column;

	row = -1;
	while (map[++row])
	{
		column = -1;
		while (map[row][++column])
		{
			if (map[row][column] != '1' && map[row][column] != ' ')
			{
				map[row][column] = '0';
			}
		}
	}
}

int	add_map_line(t_map_node **first_node, char *line)
{
	t_map_node	*new_map_node;
	t_map_node	*current_map_node;

	new_map_node = malloc(sizeof(t_map_node));
	if (!new_map_node)
		return (FAIL);
	new_map_node->line = line;
	new_map_node->next = NULL;
	if (!(*first_node))
	{
		*first_node = new_map_node;
		return (SUCCESS);
	}
	current_map_node = *first_node;
	while (current_map_node->next)
		current_map_node = current_map_node->next;
	current_map_node->next = new_map_node;
	return (SUCCESS);
}

int	null_textures(t_level *level)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		level->texture[i].path = NULL;
		level->texture[i].texture = NULL;
		i++;
	}
	return (FAIL);
}
