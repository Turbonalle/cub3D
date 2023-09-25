#include "../incl/cub3d.h"

void copy_pointers(char **tmp, char **map, int pointers)
{
	int i;

	i = -1;
	while (++i < pointers)
		tmp[i] = map[i];
}

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
	return (FAIL);
}

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

int get_map(cub3d_t *cub3d, int fd)
{
	get_preliminary_map(cub3d, fd);
	remove_newlines(cub3d);
	int i = -1;
	while (cub3d->map[++i])
	{
		printf("map[%d] = %s\n", i, cub3d->map[i]);
	}
	// get_starting_point(cub3d);
	return (SUCCESS);
}

int read_cub_file(cub3d_t *cub3d, char *map_path)
{
	int fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (err("Failed to open map file"));
	get_elements(cub3d, fd);
	get_map(cub3d, fd);
	// if (!get_elements(cub3d, fd) || !get_map(cub3d, fd))
		// handle_file_error(fd);
	close(fd);
	return (0);
}