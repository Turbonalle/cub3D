/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_level.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:42:39 by slampine          #+#    #+#             */
/*   Updated: 2024/01/11 15:55:38 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"
//------------------------------------------------------------------------------

int	find_member_of_set_from_string(char *set, char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (ft_strchr(set, string[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

//------------------------------------------------------------------------------

int	get_preliminary_map(level_t *level, int fd)
{
	map_node_t	*current_map_node;
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
		if (!find_member_of_set_from_string(MAP_ALL_ELEMENTS, line))
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

//------------------------------------------------------------------------------

int	get_starting_point(level_t *level)
{
	int			starting_point_found;
	vector_t	pos;

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

//------------------------------------------------------------------------------

int	get_map(level_t *level, int fd)
{
	if (!get_preliminary_map(level, fd))
		return (FAIL);
	if (!create_rectangular_map(level))
		return (FAIL);
	if (!get_starting_point(level))
		return (FAIL);
	return (SUCCESS);
}

int read_cub_file(level_t *level, char *map_path)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (close(fd), err("Failed to open map file"));
	level->nodes = null_textures(level);
	if (!get_elements(level, fd))
		return (free_delete_textures(level), FAIL);
	if (!all_elements_found(level->element_found))
		return (close(fd), err("Missing element(s) in map file"));
	if (!get_map(level, fd))
	{
		free_delete_textures(level);
		free_list(level->map_list);
		return (close(fd), free_info(level->map), FAIL);
	}
	close(fd);
	fd = 0;
	while (level->map[fd])
		fd++;
	level->backup = ft_calloc(sizeof(char *), (fd + 1));
	fd = 0;
	while (level->map[fd])
	{
		level->backup[fd] = ft_strdup(level->map[fd]);
		free(level->map[fd]);
		fd++;
	}
	free(level->map);
	level->map = ft_calloc(sizeof(char *), (fd + 1));
	fd = 0;
	while (level->backup[fd])
	{
		level->map[fd] = ft_strdup(level->backup[fd]);
		fd++;
	}
	zero_map(level->map);
	if (!check_map_validity(level->map))
	{
		free_delete_textures(level);
		free_list(level->map_list);
		free_info(level->map);
		free_info(level->backup);
		return (FAIL);
	}
	fd = 0;
	while (level->map[fd])
	{
		free(level->map[fd]);
		fd++;
	}
	free(level->map);
	return (SUCCESS);
}
