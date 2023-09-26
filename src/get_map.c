#include "../incl/cub3d.h"

//------------------------------------------------------------------------------

void copy_pointers(char **tmp, char **map, int pointers)
{
	int i;

	i = -1;
	while (++i < pointers)
		tmp[i] = map[i];
}

//------------------------------------------------------------------------------

int get_preliminary_map(cub3d_t *cub3d, int fd)
{
	char	**tmp;
	char	*line;
	int		i;

	line = get_next_line(fd);
	if (line[0] == '\n')
	{
		free(line);
		while (line[0] == '\n')
		{
			line = get_next_line(fd);
			free(line);
		}
	}
	i = 0;
	while (line)
	{
		tmp = malloc(sizeof(char *) * i);
		if (i != 0 && !tmp)
			return (free(tmp), err("Failed to allocate memory for map"));
		copy_pointers(tmp, cub3d->map, i);
		if (i != 0)
			free(cub3d->map);
		cub3d->map = malloc(sizeof(char *) * (i + 2));
		if (!cub3d->map)
			return (free(cub3d->map), err("Failed to allocate memory for map"));
		copy_pointers(cub3d->map, tmp, i);
		cub3d->map[i] = line;
		cub3d->map[i + 1] = NULL;
		if (i != 0)
			free(tmp);
		i++;
		line = get_next_line(fd);
	}
	if (i == 0)
		return (free(cub3d->map), err("Empty map"));
	return (SUCCESS);
}

//------------------------------------------------------------------------------

void remove_newlines(cub3d_t *cub3d)
{
	int i;
	int j;

	i = -1;
	while (cub3d->map[++i])
	{
		j = -1;
		while (cub3d->map[i][++j])
		{
			if (cub3d->map[i][j] == '\n')
				cub3d->map[i][j] = '\0';
		}
	}
}

//------------------------------------------------------------------------------

int get_starting_point(cub3d_t *cub3d)
{
	int starting_point_found;
	int i;
	int j;

	starting_point_found = FALSE;
	i = -1;
	while (cub3d->map[++i])
	{
		j = -1;
		while (cub3d->map[i][++j])
		{
			if (cub3d->map[i][j] == 'N' || cub3d->map[i][j] == 'S' || cub3d->map[i][j] == 'W' || cub3d->map[i][j] == 'E')
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

int flood_map(char **map)
{
	int i;

	i = -1;
	while (map[0][i] == ' ')
		i++;
	if (map[0][i] != '1' || map[0][i] != '0')
		map[0][i] = 'x';
	return (SUCCESS);
}

//------------------------------------------------------------------------------

int create_rectangular_map(char ***old_map)
{
	char **new_map;
	int longest_line_len;
	int longest_line_pos;
	int len;
	int i;
	int j;

	// Find longest line
	longest_line_len = 0;
	i = -1;
	while ((*old_map)[++i])
	{
		len = ft_strlen((*old_map)[i]);
		if (len > longest_line_len)
		{
			longest_line_len = len;
			longest_line_pos = i;
		}
	}
	
	// Create new_map
	new_map = malloc(sizeof(char *) * (i + 1));
	if (!new_map)
		return (err("Failed to allocate memory for map"));
	new_map[i] = NULL;
	i = -1;
	while ((*old_map)[++i])
	{
		new_map[i] = malloc(sizeof(char) * (longest_line_len + 1));
		if (!new_map[i])
			return (free(new_map), err("Failed to allocate memory for map"));
		j = -1;
		while ((*old_map)[i][++j])
			new_map[i][j] = (*old_map)[i][j];
		while (j < longest_line_len)
			new_map[i][j++] = ' ';
		new_map[i][longest_line_len] = '\0';
	}
	
	// Free old_map and replace it with new_map
	free_info(*old_map);
	*old_map = new_map;
	return (SUCCESS);
}

//------------------------------------------------------------------------------

int get_map(cub3d_t *cub3d, int fd)
{
	if (!get_preliminary_map(cub3d, fd))
		return (FAIL);
	remove_newlines(cub3d);
	if (!get_starting_point(cub3d))
		return (FAIL);
	create_rectangular_map(&cub3d->map);

	// TODO: Check if map is surrounded by walls
	// flood_map(cub3d->map);

	return (SUCCESS);
}

//------------------------------------------------------------------------------

int read_cub_file(cub3d_t *cub3d, char *map_path)
{
	int fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (close(fd), err("Failed to open map file"));
	get_elements(cub3d, fd);
	if (!all_elements_found(cub3d->element_found))
		return (close(fd), err("Missing element(s) in map file"));
	if (!get_map(cub3d, fd))
		return (close(fd), free_info(cub3d->map), FAIL);
	close(fd);
	return (0);
}