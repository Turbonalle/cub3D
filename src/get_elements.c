#include "../incl/cub3d.h"

int elements_found(int *element_found)
{
	int i;

	i = -1;
	while (++i < 6)
	{
		if (!element_found[i])
			return (FAIL);
	}
	return (SUCCESS);
}

int get_color(cub3d_t *cub3d, int element, char **info)
{
	int i;
	int color;

	i = 0;
	while (info[1][i])
	{
		if (!ft_isdigit(info[1][i]))
			return (err("Invalid color"));
		i++;
	}
	color = ft_atoi(info[1]);
	if (color < 0 || color > 255)
		return (err("Invalid color"));
	if (element == F)
		cub3d->floor_color = color;
	else
		cub3d->ceiling_color = color;
	return (SUCCESS);
}

int get_element(cub3d_t *cub3d, int element, char **info)
{
	if (cub3d->element_found[element])
		return (err("Duplicate element found"));
	cub3d->element_found[element] = 1;
	if (element == F || element == C)
		return (get_color(cub3d, element, info));
	else
		return (get_texture(cub3d, element, info));
}

int find_element(cub3d_t *cub3d, char *line)
{
	char **split;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
		return (FAIL);
	if (ft_strcmp(split[0], "NO") == 0)
		return (get_element(cub3d, NO, split));
	else if (ft_strcmp(split[0], "SO") == 0)
		return (get_element(cub3d, SO, split));
	else if (ft_strcmp(split[0], "WE") == 0)
		return (get_element(cub3d, WE, split));
	else if (ft_strcmp(split[0], "EA") == 0)
		return (get_element(cub3d, EA, split));
	else if (ft_strcmp(split[0], "F") == 0)
		return (get_element(cub3d, F, split));
	else if (ft_strcmp(split[0], "C") == 0)
		return (get_element(cub3d, C, split));
}

int get_elements(cub3d_t *cub3d, int fd)
{
	char *line;
	int i;

	i = 0;
	while (i < 6)
		cub3d->element_found[i++] = 0;
	while (!elements_found(cub3d->element_found))
	{
		line = get_next_line(fd);
		if (!line)
			return (err("Failed to read map file"));
		if (line[0] == '\n')
			continue ;
		if (!find_element(cub3d, line))
		{
			free(line);	
			return (FAIL);
		}
		free(line);
	}
	return (SUCCESS);
}