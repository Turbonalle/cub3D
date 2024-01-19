/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_level.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:42:39 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 17:10:43 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

/* int	find_member_of_set_from_string(char *set, char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (ft_strchr(set, string[i]) == 0)
		{
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
} */

static int	all_chars_are_valid(t_level *level, char *line)
{
	if (level->index == 0)
		return (find_member_of_set_from_string(MAP_ALL_ELEMENTS, line));
	else
		return (find_member_of_set_from_string(MAP_ALL_ELEMENTS_BONUS, line));
}

int	get_preliminary_map(t_level *level, int fd)
{
	t_map_node	*current_map_node;
	char		*line;

	level->map_list = NULL;
	level->map = NULL;
	line = get_next_line(fd);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		remove_newline(line);
		if (!all_chars_are_valid(level, line))
			return (free(line), err("Invalid character in map"));
		if (!add_map_line(&level->map_list, line))
			return (free(line), err("Failed to allocate memory for map"));
		line = get_next_line(fd);
		level->nodes++;
	}
	current_map_node = level->map_list;
	while (current_map_node)
		current_map_node = current_map_node->next;
	return (SUCCESS);
}

int	get_starting_point(t_level *level)
{
	int			starting_point_found;
	t_vector	pos;

	starting_point_found = FALSE;
	pos.y = -1;
	while (level->map[++pos.y])
	{
		pos.x = -1;
		while (level->map[pos.y][++pos.x])
		{
			if (ft_strchr(MAP_DIRECTIONS, level->map[pos.y][pos.x]))
			{
				level->starting_pos.x = pos.x;
				level->starting_pos.y = pos.y;
				level->starting_dir = level->map[pos.y][pos.x];
				level->map[pos.y][pos.x] = '0';
				if (starting_point_found == TRUE)
					return (err("Multiple starting points found"));
				starting_point_found = TRUE;
			}
		}
	}
	if (starting_point_found == FALSE)
		return (err("No starting point found"));
	return (SUCCESS);
}

int	get_map(t_level *level, int fd)
{
	if (!get_preliminary_map(level, fd))
		return (FAIL);
	if (!create_rectangular_map(level))
		return (FAIL);
	if (!get_starting_point(level))
		return (FAIL);
	return (SUCCESS);
}

int	read_cub_file(t_level *level, char *map_path)
{
	int	fd;

	if (!read_map(level, map_path))
		return (FAIL);
	fd = 0;
	while (level->map[fd])
		fd++;
	level->backup = ft_calloc(sizeof(char *), (fd + 1));
	if (!copy_array(level->map, level->backup))
		return (free_map_helper(level, 0));
	free_info(level->map);
	level->map = ft_calloc(sizeof(char *), (fd + 1));
	if (!copy_array(level->backup, level->map))
		return (free_map_helper(level, 1));
	zero_map(level->map);
	if (!check_map_validity(level->map))
		return (free_map_helper(level, 2));
	fd = 0;
	while (level->map[fd])
	{
		free(level->map[fd]);
		fd++;
	}
	free(level->map);
	return (SUCCESS);
}
