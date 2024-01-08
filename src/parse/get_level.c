
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

int get_preliminary_map(level_t *level, int fd)
{
	map_node_t	*current_map_node;
	char		*line;
	int			i;

	level->map_list = NULL;
	level->map = NULL;
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
		if (!add_map_line(&level->map_list, line))
			return (free(line), err("Failed to allocate memory for map"));
		line = get_next_line(fd);
		i++;
	}
	level->nodes = i;
	current_map_node = level->map_list;
	while (current_map_node)
		current_map_node = current_map_node->next;
	return (SUCCESS);
}

//------------------------------------------------------------------------------

int get_starting_point(level_t *level)
{
	int	starting_point_found;
	int	i;
	int	j;

	starting_point_found = FALSE;
	i = -1;
	while (level->map[++i])
	{
		j = -1;
		while (level->map[i][++j])
		{
			if (ft_strchr(MAP_DIRECTIONS, level->map[i][j]))
			{
				level->starting_pos.x = j;
				level->starting_pos.y = i;
				level->starting_dir = level->map[i][j];
				level->map[i][j] = '0';
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

int create_rectangular_map(level_t *level)
{
	map_node_t	*current_map_node;
	int			longest_length;
	int			i;
	int			j;

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
	i = 0;
	while (current_map_node)
	{
		level->map[i] = malloc(sizeof(char) * (longest_length + 1));
		if (!level->map[i])
			return (err("Failed to allocate memory for map"));
		j = 0;
		while (current_map_node->line[j])
		{
			level->map[i][j] = current_map_node->line[j];
			j++;
		}
		while (j < longest_length)
			level->map[i][j++] = ' ';
		level->map[i][j] = '\0';
		current_map_node = current_map_node->next;
		i++;
	}
	return (SUCCESS);
}

//------------------------------------------------------------------------------

int get_map(level_t *level, int fd)
{
	if (!get_preliminary_map(level, fd))
		return (FAIL);
	if (!create_rectangular_map(level))
		return (FAIL);
	if (!get_starting_point(level))
		return (FAIL);
	return (SUCCESS);
}

//------------------------------------------------------------------------------

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
				printf("is %c\n",map[row][column]);
				map[row][column] = '0';
			}
		}
	}
}

int read_cub_file(level_t *level, char *map_path)
{
	int	fd;
	int	i;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (close(fd), err("Failed to open map file"));
	i = 0;
	while (i < 4)
	{
		level->texture[i].path = NULL;
		level->texture[i].texture = NULL;
		i++;
	}
	if (!get_elements(level, fd))
		return (free_delete_textures(level), FAIL);
	// return (free_delete_textures(level), close(fd), FAIL);
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
		return (FAIL);
	fd = 0;
	while (level->map[fd])
	{
		free(level->map[fd]);
		fd++;
	}
	free(level->map);
	return (SUCCESS);
}
