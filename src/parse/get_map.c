/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:55:36 by slampine          #+#    #+#             */
/*   Updated: 2023/11/28 14:13:36 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

//------------------------------------------------------------------------------

void copy_pointers(char **array_from, char **array_to, int pointers)
{
	int i;

	i = -1;
	while (++i < pointers)
		array_to[i] = array_from[i];
}

//------------------------------------------------------------------------------

int add_map_line(map_node_t **first_node, char *line)
{
	map_node_t *new_map_node;
	map_node_t *current_map_node;

	new_map_node = malloc(sizeof(map_node_t));
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

int get_preliminary_map(cub3d_t *cub3d, int fd)
{
	map_node_t	*current_map_node;
	char		*line;
	int			i;

	cub3d->map_list = NULL;
	cub3d->map = NULL;
	line = get_next_line(fd);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	i = 0;
	while (line)
	{
		remove_newline(line);
		if (!find_member_of_set_from_string(MAP_ALL_ELEMENTS, line))
			return (free(line), err("Invalid character in map"));
		if (!add_map_line(&cub3d->map_list, line))
			return (free(line), err("Failed to allocate memory for map"));
		line = get_next_line(fd);
		i++;
	}
	cub3d->nodes = i;
	current_map_node = cub3d->map_list;
	while (current_map_node)
		current_map_node = current_map_node->next;
	return (SUCCESS);
}

//------------------------------------------------------------------------------

int get_starting_point(cub3d_t *cub3d)
{
	int	starting_point_found;
	int	i;
	int	j;

	starting_point_found = FALSE;
	i = -1;
	while (cub3d->map[++i])
	{
		j = -1;
		while (cub3d->map[i][++j])
		{
			if (ft_strchr(MAP_DIRECTIONS, cub3d->map[i][j]))
			{
				cub3d->starting_pos.x = j;
				cub3d->starting_pos.y = i;
				cub3d->starting_dir = cub3d->map[i][j];
				cub3d->map[i][j] = '0';
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

int create_rectangular_map(cub3d_t *cub3d)
{
	map_node_t	*current_map_node;
	int			longest_length;
	int			i;
	int			j;

	cub3d->map = malloc(sizeof(char *) * (cub3d->nodes + 1));
	if (!cub3d->map)
		return (err("Failed to allocate memory for map"));
	longest_length = 0;
	current_map_node = cub3d->map_list;
	while (current_map_node)
	{
		if ((int)ft_strlen(current_map_node->line) > longest_length)
			longest_length = ft_strlen(current_map_node->line);
		current_map_node = current_map_node->next;
	}
	cub3d->map_columns = longest_length;
	cub3d->map_rows = cub3d->nodes;
	cub3d->map[cub3d->nodes] = NULL;
	current_map_node = cub3d->map_list;
	i = 0;
	while (current_map_node)
	{
		cub3d->map[i] = malloc(sizeof(char) * (longest_length + 1));
		if (!cub3d->map[i])
			return (err("Failed to allocate memory for map"));
		j = 0;
		while (current_map_node->line[j])
		{
			cub3d->map[i][j] = current_map_node->line[j];
			j++;
		}
		while (j < longest_length)
			cub3d->map[i][j++] = ' ';
		cub3d->map[i][j] = '\0';
		current_map_node = current_map_node->next;
		i++;
	}
	return (SUCCESS);
}

//------------------------------------------------------------------------------

int get_map(cub3d_t *cub3d, int fd)
{
	if (!get_preliminary_map(cub3d, fd))
		return (FAIL);
	create_rectangular_map(cub3d);
	if (!get_starting_point(cub3d))
		return (FAIL);
	if (!check_map_validity(cub3d->map))
		return (FAIL);
	return (SUCCESS);
}

//------------------------------------------------------------------------------

int read_cub_file(cub3d_t *cub3d, char *map_path)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (close(fd), err("Failed to open map file"));
	get_elements(cub3d, fd);
	if (!all_elements_found(cub3d->element_found))
		return (close(fd), err("Missing element(s) in map file"));
	if (!get_map(cub3d, fd))
		return (close(fd), free_info(cub3d->map), FAIL);
	close(fd);
	return (SUCCESS);
}